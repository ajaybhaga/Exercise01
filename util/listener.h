// Listeners.h : Defines the entry point for the console application.

#ifndef EANN_SIMPLE_LISTENER_H
#define EANN_SIMPLE_LISTENER_H


#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include <string>

using namespace std;

// an event holds a vector of subscribers
// when it fires, each is called

template<class... Args>
class SubscriberBase {
public:
    virtual void call(Args... args) = 0;
    virtual bool instanceIs(void* t) = 0;
    virtual ~SubscriberBase() { };
};

template<class T, class... Args>
class Subscriber : public SubscriberBase<Args...> {
private:
    T* t;
    void(T::*f)(Args...);
public:
    Subscriber(T* _t, void(T::*_f)(Args...)) : t(_t), f(_f) { }
    void call(Args... args)   final { (t->*f)(args...); }
    bool instanceIs(void* _t) final { return _t == (void*)t; }
    ~Subscriber()             final { cout << "~Subscriber() hit! \n"; }
};

// our Listener will derive from EventListener<Listener>
// which holds a list of a events it is subscribed to.
// As these events will have different sigs, we need a base-class.
// We will store pointers to this base-class.
class EventBase {
public:
    virtual void removeSubscriber(void* t) = 0;
};

template<class... Args>
class Event : public EventBase {
private:
    using SmartBasePointer = unique_ptr<SubscriberBase<Args...>>;
    std::vector<SmartBasePointer> subscribers;
public:
    void fire(Args... args) {
        for (auto& f : subscribers)
            f->call(args...);
    }

    template<class T>
    void addSubscriber(T* t, void(T::*f)(Args... args)) {
        auto s = new Subscriber <T, Args...>(t, f);
        subscribers.push_back(SmartBasePointer(s));
    }

    //template<class T>
    void removeSubscriber(void* t) final {
        auto to_remove = std::remove_if(
                subscribers.begin(),
                subscribers.end(),
                [t](auto& s) { return s->instanceIs(t); }
        );
        subscribers.erase(to_remove, subscribers.end());
    }
};

// derive your listener classes: struct MyListener : EventListener<MyListener>, i.e. CRTP
template<class Derived>
class EventListener {
private:
    // all events holding a subscription to us...
    std::vector<EventBase*> events;

public:
    template<class... Args>
    void connect(Event<Args...>& ev, void(Derived::*listenerMethod)(Args... args)) {
        ev.addSubscriber((Derived*)this, listenerMethod);
        events.push_back(&ev);
    }

    // ...when the listener dies, we must notify them all to remove subscription
    ~EventListener() {
        for (auto& e : events)
            e->removeSubscriber((void*)this);
    }
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// example usage:
class Publisher {
private:
    string name;
public:
    Event<float> eventFloat;
    Event<bool, int> eventB;

    Publisher(string _name) : name(_name) { }

    void triggerEvent() {
        cout << name << "::triggerEvent() ~ Firing event with: 42\n";
        eventFloat.fire(42.0f);
    }
};

struct Listener : EventListener<Listener> {
    string name;
    Listener(string _name)
            : name(_name) {
        cout << name << "()\n";
    }
    ~Listener() {
        cout << "~" << name << "()\n";
        //emitter.eventFloat.removeSubscriber(this);
    }

    void gotEvent(float x) { cout << name << "::gotEvent hit with value: " << x << endl; }
};

#endif //EANN_SIMPLE_LISTENER_H
