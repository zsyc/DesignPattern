/* Strategie.cpp */
#include <iostream>
#include <memory>

using std::cout;
using std::unique_ptr;
using std::make_unique;

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
    void performQuack(){ sp_quackBehavior->quack();}
    void performFly(){ sp_flyBehavior->fly();}
    void setFlyBehavior(FlyBehavior *flyB){ sp_flyBehavior.reset(flyB);}
    void setFlyBehavior(unique_ptr<FlyBehavior> flyB){ sp_flyBehavior = std::move(flyB);}   // 重载，为传递普通指针与智能指针作准备

    virtual ~Duck(){
        cout<<"Base Duck destructed\n";
    }

protected:
    unique_ptr<FlyBehavior> sp_flyBehavior;
    unique_ptr<QuackBehavior> sp_quackBehavior;
};

/* Test */
class Modelduck: public Duck{
public:
    Modelduck(){    // can't use initializer list for lack of [existence] of the two Pointer
        sp_flyBehavior = make_unique<FlyNoWay>();
        sp_quackBehavior = make_unique<Quack>();
        cout<<"Modelduck constructed\n";
    }
    ~Modelduck(){
        cout<<"Modelduck destructed\n";
    }
};

int main (){
    Modelduck test;
    test.performQuack();
    test.performFly();
    test.setFlyBehavior(new FlyRocketPowered());
    test.performFly();
    test.setFlyBehavior(make_unique<FlyWithWings>());
    test.performFly();

    return 0;
}