
#include <Python.h>

// ####################### destructivebox

typedef struct{
  PyObject_HEAD
    PyObject *first,
    PyObject *last,
    int number;
} DestructiveBox;

static int
DestructiveBox_init(CustomObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"first", "last", "number", NULL};
    PyObject *first = NULL, *last = NULL, *tmp;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|OOi", kwlist,
                                     &first, &last,
                                     &self->number))
        return -1;

    if (first) {
        tmp = self->first;
        Py_INCREF(first);
        self->first = first;
        Py_XDECREF(tmp);
    }
    if (last) {
        tmp = self->last;
        Py_INCREF(last);
        self->last = last;
        Py_XDECREF(tmp);
    }
    return 0;
}

static PyTypeObject DestructiveBoxType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "destructiveclass.DestructiveBox",
    .tp_doc = "Custom objects",
    .tp_basicsize = sizeof(DestructiveBox),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc) DestructiveBox_init,
};


//################## destructive class


typedef struct {
    PyObject_HEAD
    /* Type-specific fields go here. */
} DestructiveClass;

// make it wrap in a destructive box
static PyObject *
DestructiveClass_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
  DestructiveBox *self;
  self = (DestructiveBox *) type->tp_alloc(type, 0);
  return (PyObject *) self;
}

static PyTypeObject DestructiveClassType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "destructiveclass.DestructiveClass",
    .tp_doc = "Custom objects",
    .tp_basicsize = sizeof(DestructiveClass),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = DestructiveClass_new,
};

static PyModuleDef destructiveclassmodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "DestructiveClass",
    .m_doc = "Example module that creates an extension type.",
    .m_size = -1,
};




PyMODINIT_FUNC
PyInit_DestructiveClass(void)
{
    
    if (PyType_Ready(&DestructiveClassType) < 0)
        return NULL;

    PyObject *m;
    m = PyModule_Create(&destructiveclassmodule);
    if (m == NULL)
        return NULL;

    
    if (PyType_Ready(&DestructiveBoxType) < 0)
        return NULL;


    Py_INCREF(&DestructiveClassType);
    Py_INCREF(&DestructiveBoxType);
    PyModule_AddObject(m, "DestructiveClass", (PyObject *) &DestructiveClassType);
    PyModule_AddObject(m, "DestructiveBox", (PyObject *) &DestructiveBoxType);
    return m;
}
