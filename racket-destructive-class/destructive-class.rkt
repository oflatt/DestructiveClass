#lang racket
(require (except-in (submod racket/private/class-internal class-internal) class))
;; a destructive class is a class where all the methods have the destructive contract
;; the destructive contract is the contract that this object is the latest version of the object- each time 
;; raise error if they use field, only private fields allowed


(define fish%
  (class object%
    (field (color 'green))
    (field (destructive-box false))
    (init-field (size 2))
    (define/public (big?)
      (> size 4))
    (define/public (increment-size)
      (set! size (+ size 1)))
    (super-new)))


(define-syntax-rule (set-destructive destructive-object [id value] ...)
  (begin
    (set-box! (get-field destructive-box destructive-object) false)
    ;(set-field! destructive-box destructive-object (box true))
    (set-field! id destructive-object value) ...
    destructive-object))


(define (make-destructive-fish fish)
  (let ([fish-box (box true)])
    (define not-destroyed?
      (make-contract
       #:projection
       (lambda (blame)
         (lambda (m)
           (chaperone-procedure
            m
            (lambda (self . args)
              (unless (unbox fish-box)
                (error "Called method belonging to destroyed destructive object."))
              (apply values self args)))))))
    (define/contract fish-contract-obj
      (object/c #;[increment-size not-destroyed?]
                [big? not-destroyed?])
      fish)
    (set-field! destructive-box fish-contract-obj fish-box)
    fish-contract-obj))


;;(send my-fish big?)


;;(set-destructive my-fish [size 2])


;;(send my-fish big?)


#|
(define (make-class-destructive c)
  (set-class-method-ht!
   c
   (chaperone-hash (class-method-ht c)
                   ;; set the ref proc to call the chaperone
                   (lambda (hash key)
                     (begin
                       (println key)
                       (values key
                               (lambda (hash key val) val)))))))
|#


(define (hash-with-key-chaperone ht hook)
  (chaperone-hash
   ht
   ;; set the ref-proc to call the hook
   (lambda (self key)
     (begin
       (hook key)
       (values key (lambda (self key value) value))))
   ;; defaults for other procs
   (lambda (self key value) (values key value))
   (lambda (self key) key)
   (lambda (self key) key)))
   
  

(define (class-call-with-chaperone c hook)
  (chaperone-struct
   c
   class-method-ht
   (lambda (self table)
     (hash-with-key-chaperone table hook))))

(define (chaperone-object-method o key-method)
  (chaperone-struct
   o
   object-ref
   (lambda (self c)
     (begin
       (class-call-with-chaperone
        c
        key-method)))))


(define (class-access-with-chaperone c hook)
  (chaperone-struct
   c
   class-field-ht
   (lambda (self table)
     (hash-with-key-chaperone table hook))))


(define (chaperone-object-access o key-method)
  (chaperone-struct
   o
   object-ref
   (lambda (self c)
     (begin
       (class-access-with-chaperone
        c
        key-method)))))


;(define my-fish-test (chaperone-struct (new fish% [size 8])
;                         object-ref (lambda (self c) (begin (print 2) c))))

(define my-fish (chaperone-object-method (new fish% [size 6]) (lambda (key) (println key))))

(send my-fish big?)

(struct myclass (size f-table) #:mutable #:transparent)




