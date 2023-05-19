/* 类似读者订阅报纸，读者相当于obserser，出版社相当于subject
一对多，当'一'发生变化时，'多'会同步更新*/
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

using std::find;
using std::make_unique;
using std::unique_ptr;
using std::vector;

/* Interface for Subject and Observer */
class Subject {
public:
    virtual void registerObserver(Observer &) = 0;
    virtual void removeObserver(Observer &) = 0;
    virtual void notifyObservers() const = 0;
    virtual ~Subject() = default;
};

class Observer {
public:
    virtual void update(double temp, double humidity, double pressure) = 0; // 每隔订阅者都会实现这个函数，用于Subject来调用
    virtual ~Observer() = default;                                          // 必须有虚析构函数，否则如果子类中有成员函数会被当做父类析构函数来释放资源，导致内存泄漏。
};

class DisplayElement {
public:
    virtual void display() const = 0;
};

class WeatherData : public Subject {
private:
    double             temperature;
    double             humidity;
    double             pressure;
    vector<Observer *> oblist; // `Observer` 是一个纯虚类，不能直接将 `Observer`
                               // 类型的对象存储在容器中

public:
    // 这里函数参数中的&obs是Observer对象的’引用‘，而emplace_back中的则是取地址……ChatGPT提供的修正
    void registerObserver(Observer &obs) override { oblist.emplace_back(&obs); }
    void removeObserver(Observer &obs) override {
        auto itr = find(oblist.begin(), oblist.end(), &obs);
        if (itr != oblist.end()) oblist.erase(itr);
    }
    void notifyObservers() const override {
        for (auto &itr : oblist) itr->update(temperature, humidity, pressure);
    }

    double getTemperature() { return temperature; }
    double getHumidity() { return humidity; }
    double getPressure() { return pressure; }
    void   measurementsChanges() { notifyObservers(); }
};

class CurrentConditions : public Observer, public DisplayElement {
public:
    CurrentConditions(WeatherData &sky) :
        weather(sky) {}
    void update(double temp, double humidity, double pressure) override {
    }
    void display() override {}

private:
    double      temperature;
    double      humidity;
    WeatherData weather;
};