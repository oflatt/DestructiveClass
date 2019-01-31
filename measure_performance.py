from DestructiveClass import DestructiveClass
from timeit import default_timer as timer

class TestClassDestructive(DestructiveClass):

    def __init__(self, val):
        self.val = val



class TestClassNormal():

    def __init__(self, val):
        self.val = val




number_of_sets = 1000000

start = timer()

destructive = TestClassDestructive(0)

for i in range(number_of_sets):
    destructive = destructive.destructiveset("val", i)

end = timer()

destructivesettime = end-start
print("Destructive set: " + str(destructivesettime))

start = timer()

normal = TestClassNormal(0)

for i in range(number_of_sets):
    normal.val = i

end = timer()

normalsettime = end-start
print("Normal set: " + str(normalsettime))

print("Destructive set is " + str(destructivesettime/normalsettime) + " times slower.")


#################### get

start = timer()

destructive = TestClassDestructive(0)

for i in range(number_of_sets):
    destructive.val

end = timer()

destructivesettime = end-start
print("Destructive set: " + str(destructivesettime))

start = timer()

normal = TestClassNormal(0)

for i in range(number_of_sets):
    normal.val

end = timer()

normalsettime = end-start
print("Normal set: " + str(normalsettime))

print("Destructive set is " + str(destructivesettime/normalsettime) + " times slower.")
