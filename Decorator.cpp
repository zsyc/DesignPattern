/*咖啡价格，美式、摩卡、浓缩、加糖、加奶……*/
#include <iostream>
#include <memory>
#include <string>

using std::string;
using std::unique_ptr;
using std::make_unique;
using std::cout;
using std::endl;

class Beverage {
public:
    string         description = "Unknown Beverage";
    virtual string getDescription() const { return description; }
    virtual double cost() const = 0;
    virtual ~Beverage() = default;
};

class Espresso : public Beverage {
public:
    Espresso() { description = "Espresso"; }
    double cost() const override { return 1.99; }
};

class HouseBlend : public Beverage {
public:
    HouseBlend() { description = "House Blend Coffee"; }
    double cost() const override { return 0.89; }
};

class DarkRoast : public Beverage {
public:
    DarkRoast() { description = "Dark Roast Coffee"; }
    double cost() const override { return 0.99; }
};

class CondimentDecorator : public Beverage {
public:
    virtual string getDescription() const override = 0;
    virtual ~CondimentDecorator() = default;
};

class Mocha : public CondimentDecorator {
public:
    Beverage &beverage;
    Mocha(Beverage &param_beverage) :
        beverage(param_beverage) {}
    string getDescription() const override { return beverage.description + ", Mocha"; }
    double cost() const override { return 0.2 + beverage.cost(); }
};

class Soy : public CondimentDecorator {
public:
    Beverage &beverage;
    Soy(Beverage &param_beverage) :
        beverage(param_beverage) {}
    string getDescription() const override { return beverage.description + ", Soy"; }
    double cost() const override { return 0.15 + beverage.cost(); }
};

class Whip : public CondimentDecorator {
public:
    Beverage &beverage;
    Whip(Beverage &param_beverage) :
        beverage(param_beverage) {}
    string getDescription() const override { return beverage.description + ", Whip"; }
    double cost() const override { return 0.10 + beverage.cost(); }
};

int main() {
    unique_ptr<Beverage> bev1 = make_unique<Espresso>(); // （）使用无参数constructor
    cout << bev1->getDescription() << " $" << bev1->cost() << endl;

    unique_ptr<Beverage> bev2 = make_unique<HouseBlend>();
    bev2 = make_unique<Mocha>(*bev2);
    // bev2 = make_unique<Mocha>(*bev2);
    // bev2 = make_unique<Whip>(*bev2);
    cout << bev2->getDescription() << " $" << bev2->cost() << endl;

    return 0;
}