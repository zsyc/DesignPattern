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
using std::cout;
using std::endl;

/* Interface for Subject and Observer */
class Observer;

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
    void   setMeasurements(double temp, double humidity, double pressure) {
        this->temperature = temp;
        this->humidity = humidity;
        this->pressure = pressure;
        measurementsChanges();
    }
};

// 这里把display也视为一个Observer
class CurrentConditionsDisplay : public Observer, public DisplayElement {
private:
    double   temperature;
    double   humidity;
    double   pressure;
    Subject &weather;

public:
    /*传递Subject而不是WeatherData是因为，CurrentConditionsDisplay类只跟Subject打交道，它并不关心Subject究竟是哪一个具体的类，
    也就是说它跟具体的实现解耦。这样做也方便后续的扩展，如果将来有其他类型的Subject实现，我们不需要更改CurrentConditionsDisplay类的代码。*/
    CurrentConditionsDisplay(Subject &weat) :
        weather(weat) {
        weather.registerObserver(*this);
    }
    ~CurrentConditionsDisplay() { weather.removeObserver(*this); }
    void update(double temp, double humidity, double pressure) override {
        this->temperature = temp;
        this->humidity = humidity;
        this->pressure = pressure;
        display();
    }
    void display() const override {
        cout << "Current Temperatur is " << temperature << endl
             << "Humidity is " << humidity << endl
             << "Pressure is " << pressure << endl;
    }
};

int main() {
    WeatherData              sky;
    CurrentConditionsDisplay currentSky(sky);

    sky.setMeasurements(32, 45, 1.04);
    /*在这段代码中，虽然没有显式地调用 `currentSky` 对象的成员函数，但是在 `registerObserver` 函数中，我们将 `currentSky` 对象注册为 `sky` 对象的观察者。
    当我们调用 `sky.setMeasurements` 函数时，该函数会调用 `notifyObservers` 函数，进而调用 `update` 函数通知当前的观察者，即 `currentSky` 对象。
    在 `update` 函数中，我们调用了 `display` 函数，所以 `display` 函数被调用了。

    也就是说，如果将一个对象注册为观察者，只要该对象实现了 `update` 函数，并且在 `update` 函数中调用了 `display` 函数，那么在被观察者的数据变化时，`display` 函数就会被自动调用。
    因此，在这段代码中，虽然没有对 `currentSky` 对象进行其他操作或调用其成员函数，但是 `display` 函数仍然会被正确调用，因为 `currentSky` 已经被注册为观察者，并且实现了 `update` 函数和 `display` 函数。*/

    return 0;
}