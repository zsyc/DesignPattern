# Strategie.py
from abc import ABC, abstractclassmethod

# Interface for fly and quack
# Fly
class FlyBehavior(ABC):
    @abstractclassmethod
    def fly(self):
        print("Error, it's base class")

class FlyWithWings(FlyBehavior):
    def fly(self):
        print("duck flying")

class FlyNoWay(FlyBehavior):
    def fly(self):
        print("duck cannot fly")        

class FlyRocketPowered(FlyBehavior):
    def fly(self):
        print("I'm flying with a rocket!")

# Quack
class QuackBehavior(ABC):
    @abstractclassmethod
    def quack(self):
        print("Error, it's base class")

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
class Duck(ABC):
    @abstractclassmethod
    def __init__(self) -> None:
        self.quackBehavior = QuackBehavior  # 非实例化，而是reference variable, 用于指导子类赋值，并且通过装饰器禁止了实体化
        self.flyBehavior = FlyBehavior
        print("parent")

    def swim(self):
        print("all ducks float")

    def display(self):
        pass
    
    def performQuack(self):
        self.quackBehavior.quack()

    def performFly(self):
        self.flyBehavior.fly()
    
    def setFlyBehavior(self, flyB):
        self.flyBehavior = flyB
        
    def setQuackBehavior(self, quackB):
        self.quackBehavior = quackB

print([object in Duck.__bases__,])

# TEST
# Child class
class MallardDuck(Duck):
    def __init__(self) -> None:
        self.quackBehavior = Quack()    # 这里有括号，是实例化
        self.flyBehavior = FlyWithWings()

class Modelduck(Duck):
    def __init__(self):
        self.flyBehavior = FlyNoWay()
        self.quackBehavior = Quack()
    
    def display(self):
        print("I'm a model duck")

test = Modelduck()
test.performQuack()
test.performFly()
test.setFlyBehavior(FlyRocketPowered()) # to test the dynamic Setter
test.performFly()