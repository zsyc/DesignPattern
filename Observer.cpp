/* Observer.cpp */
#include <vector>

using std::vector;

/* Interface */
class Observer;

class Subject{
public:
    virtual void registerObserver(Observer *o) = 0; // 抽象类对象不能作为参数，因为抽象类不存在对象！
    virtual void removeObserver(Observer *o)=0;
    virtual void notifyObserver() const = 0;
    virtual ~Subject() = default;
};

class Observer{
public:
    virtual void update(float temp, float humudity, float pressure) = 0;
    virtual ~Observer() = default;
};

class DisplayElement{
public:
    virtual void display() = 0;
    virtual ~DisplayElement() = default;
};

/* Inplement */
class WeatherDate: public Subject{
public:
    WeatherDate(): observers({}){}
    void registerObserver(Observer *o) override{observers.push_back(o);}
    void removeObserver(Observer *o) override{
        for (auto i=observers.begin(); i<observers.end(); ++i)
            if (*i == o){
                observers.erase(i);
                break;
            }
    }

    void notifyObserver() const override{
        for (auto i : observers) i->update(temperature, humidity, pressure);
    }

    void setMeasurements(float t, float h, float p){
        temperature = t;
        humidity = h;
        pressure = p;
    }


private:
    vector<Observer*> observers;    // Abstract class has no Object! Pointer instead.
    float temperature;
    float humidity;
    float pressure;
};