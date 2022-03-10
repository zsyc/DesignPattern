# Interface for fly and quack
class FlyBehavior(object):
    def fly(self):
        pass

class FlyWithWings(FlyBehavior):
    def fly(self):
        print("fly")

class FlyNoWay(FlyBehavior):
    def fly(self):
        print("cannot fly")        

class QuackBehavior(object):
    def quack(self):
        pass

class Quack(QuackBehavior):
    def quack(self):
        print("duck quacking")

class Squeak(QuackBehavior):
    def quack(self):
        print("duckie squeak")

class MuteQuack(QuackBehavior):
    def quack(self):
        print("mute")

# Base class
class Duck(object):
    def __init__(self) -> None:
        self.quackBehavior = QuackBehavior()
        self.flyBehavior = FlyBehavior()

    def swim(self):
        pass
    def display(self):
        pass
    def performQuack(self):
        self.quackBehavior.quack()

    def performFly(self):
        self.flyBehavior.fly()

# child class
class MallardDuck(Duck):
    def __init__(self) -> None:
        super().__init__()
        self.quackBehavior = Quack()
        self.flyBehavior = FlyWithWings()