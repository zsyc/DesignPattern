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
    void swim(){ cout<<"all ducks float";}
    void performQuack(){ quackBehavior->quack();}
    void performFly(){ flyBehavior->fly();}
    void setFlyBehavior(FlyBehavior *flyB){ flyBehavior = flyB;}
    void setQuackBehavior(QuackBehavior *quackB){ quackBehavior = quackB;}

    virtual ~Duck(){
        cout<<"Base Duck destructed\n";
    }

protected:
    FlyBehavior *flyBehavior;
    QuackBehavior *quackBehavior;
};

/* Test */
class Modelduck: public Duck{
public:
    Modelduck(){    // can't use initializer list for lack of [existence] of the two Pointer
        flyBehavior = new FlyNoWay(); // 带括号表明成员变量初始化,否则不一定,一般带上括号就好.
        quackBehavior = new Quack();
        cout<<"Modelduck constructed\n";
    }
    ~Modelduck(){
        delete flyBehavior;
        delete quackBehavior;
        flyBehavior = NULL;
        quackBehavior = NULL;
        cout<<"Modelduck destructed\n";
    }
};

int main (){
    Modelduck test;
    test.performQuack();
    test.performFly();
    test.setFlyBehavior(new FlyRocketPowered);
    test.performFly();

    return 0;
}