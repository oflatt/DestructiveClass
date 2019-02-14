print("test")
from DestructiveClass import DestructiveClass
print("past first import")
from DestructiveClass import DestructiveBox

class TestClass(DestructiveClass):
    def __init__(self):
        self.v = 2

d = DestructiveBox()

print(d)
print(d.b)
