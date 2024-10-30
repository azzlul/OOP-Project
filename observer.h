#pragma once
#include "vector"
#include "algorithm"
using std::vector;
class Observer{
public:
    virtual void update_cart() = 0;
};

class Observable{
private:
    std::vector<Observer*> observers;
public:
    void attachObserver(Observer* obs)
    {
        observers.push_back(obs);
    }
    void detachObserver(Observer* obs)
    {
        observers.erase(std::find(observers.begin(), observers.end(),obs));
    }
    void notify()
    {
        for(auto &obs:observers)
            obs->update_cart();
    }
};