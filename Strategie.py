from abc import ABC, abstractclassmethod
from re import M

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
        self.quackBehavior = QuackBehavior  # 非实例化，而是reference variable, 用于指导子类赋值
        self.flyBehavior = FlyBehavior

    def swim(self):
        print("all ducks float")

    def display(self):
        pass
    
    def performQuack(self):
        self.quackBehavior.quack()

    def performFly(self):
        self.flyBehavior.fly()

# Child class
class MallardDuck(Duck):
    def __init__(self) -> None:
        self.quackBehavior = Quack()    # 这里有括号，是实例化
        self.flyBehavior = FlyWithWings()

print([object in Duck.__bases__,])
# test = Duck()
# test.performQuack()
mtest = MallardDuck()
mtest.performQuack()
mtest.performFly()

