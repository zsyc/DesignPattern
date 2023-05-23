/*咖啡价格，美式、摩卡、浓缩、加糖、加奶……*/
#include <iostream>
#include <memory>
#include <string>

using std::string;
using std::unique_ptr;
using std::shared_ptr;
using std::make_unique;
using std::make_shared;
using std::cout;
using std::endl;
using std::move;

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
    unique_ptr<Beverage> sp_beverage;
    Mocha(unique_ptr<Beverage> param_beverage) :
        sp_beverage(move(param_beverage)) {}
    string getDescription() const override { return sp_beverage->getDescription() + ", Mocha"; }
    double cost() const override { return 0.2 + sp_beverage->cost(); }
};

class Soy : public CondimentDecorator {
public:
    unique_ptr<Beverage> sp_beverage;
    Soy(unique_ptr<Beverage> param_beverage) :
        sp_beverage(move(param_beverage)) {}
    string getDescription() const override { return sp_beverage->getDescription() + ", Soy"; }
    double cost() const override { return 0.15 + sp_beverage->cost(); }
};

class Whip : public CondimentDecorator {
public:
    unique_ptr<Beverage> sp_beverage;
    Whip(unique_ptr<Beverage> param_beverage) :
        sp_beverage(move(param_beverage)) {}
    string getDescription() const override { return sp_beverage->getDescription() + ", Whip"; }
    double cost() const override { return 0.10 + sp_beverage->cost(); }
};

int main() {
    unique_ptr<Beverage> sp_bev1 = make_unique<Espresso>(); // （）使用无参数constructor
    cout << sp_bev1->getDescription() << " $" << sp_bev1->cost() << endl;

    unique_ptr<Beverage> sp_bev2 = make_unique<HouseBlend>();
    sp_bev2 = make_unique<Mocha>(move(sp_bev2));
    sp_bev2 = make_unique<Mocha>(move(sp_bev2));
    sp_bev2 = make_unique<Whip>(move(sp_bev2));
    cout << sp_bev2->getDescription() << " $" << sp_bev2->cost() << endl;

    return 0;
}