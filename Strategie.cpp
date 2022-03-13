/* Strategie.cpp */
#include <iostream>

using std::cout;

/* Interface for fly and quack */
/* Fly */
class FlyBehavior{
public:
    virtual void fly() = 0;
    virtual ~FlyBehavior() = default;
};

class FlyWithWings: public FlyBehavior{
public:
    void fly(){ cout<<"duck flying~\n";}
};

class FlyNoWay: public FlyBehavior{
public:
    void fly(){ cout<<"duck cannot fly\n";}
};

class FlyRocketPowered: public FlyBehavior{
public:
    void fly(){ cout<<"I'm flying with a rocket!\n";}
};

/* Quack */
class QuackBehavior{
public:
    virtual void quack() = 0;
    virtual ~QuackBehavior() = default;
};

class Quack: public QuackBehavior{
public:
    void quack(){ cout<<"duck quacking\n";}
};

class Squeak: public QuackBehavior{
public:
    void quack(){ cout<<"duckie squeak\n";}
};

class MuteQuack: public QuackBehavior{
public:
    void quack(){ cout<<"mute\n";}
};

/* Base class */
class Duck{
public:

};

int main (){
    FlyRocketPowered flytest;
    flytest.fly();
    Squeak quacktest;
    quacktest.quack();

    return 0;
}