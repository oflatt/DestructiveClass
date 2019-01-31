
from DestructiveBox import DestructiveBox

# a class like FrozenClass but packages the object in a DestructiveBox
class DestructiveClass(object):
    
    def __new__(*args):
        # create it using new
        o = super(DestructiveClass, args[0]).__new__(args[0])
        
        # initiate the object (self is the first arg, do not include it)
        o.__init__(*args[1:])
        
        # wrap the item in a destructive box
        return DestructiveBox(o)
    
    def __setattr__(self, key, value):
        object.__setattr__(self, key, value)

    
