/* 工厂模式*/
#include <iostream>
#include <memory>

using std::string;
using std::cout;
using std::unique_ptr;
using std::make_unique;
using std::endl;

class Pizza {
public:
    string name = "Pizza Prototype";

public:
    virtual void   prepare() { cout << "preparing " << name << endl; }
    virtual void   bake() { cout << "baking " << name << endl; }
    virtual void   cut() { cout << "cutting " << name << endl; }
    virtual void   box() { cout << "boxing " << name << endl; }
    virtual string getName() { return name; }
};

class NYstyleCheesePizza : public Pizza {
public:
    NYstyleCheesePizza() { name = "NY Style Cheese Pizza"; }
};
class NYstylePepperoniPizza : public Pizza {
public:
    NYstylePepperoniPizza() { name = "NY style Pepperoni Pizza"; }
};
class NYstyleClamPizza : public Pizza {
public:
    NYstyleClamPizza() { name = "NY style Clam Pizza"; }
};

class PizzaStore {
protected:
    virtual unique_ptr<Pizza> createPizza(const string &typ) = 0;

public:
    virtual ~PizzaStore() = default;
    virtual unique_ptr<Pizza> orderPizza(const string &typ) final {
        unique_ptr<Pizza> pizza = createPizza(typ);
        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();

        return pizza;
    }
};

class NYstylePizzaStore : public PizzaStore {
public:
    unique_ptr<Pizza> createPizza(const string &typ) override {
        unique_ptr<Pizza> pizza = nullptr;
        if (typ == "cheese")
            pizza = make_unique<NYstyleCheesePizza>();
        else if (typ == "pepperoni")
            pizza = make_unique<NYstylePepperoniPizza>();
        else if (typ == "clam")
            pizza = make_unique<NYstyleClamPizza>();
        return pizza;
    }
};

int main() {
    unique_ptr<PizzaStore> nyStore = make_unique<NYstylePizzaStore>();
    unique_ptr<Pizza>      pizza = nyStore->orderPizza("clam");
    cout << "U ordered a " << pizza->getName() << endl;

    return 0;
}