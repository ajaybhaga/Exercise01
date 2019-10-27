// Listeners.cpp : Defines the entry point for the console application.

#include "listener.h"
//

void test1() {
    // event source and listener unaware of each other's existence
    Publisher publisherA("publisherA");

    Listener listener1("listener1");
    listener1.connect(publisherA.eventFloat, &Listener::gotEvent);

    {
        Listener listener2("listener2");
        listener2.connect(publisherA.eventFloat, &Listener::gotEvent);

        publisherA.triggerEvent();
    }

    publisherA.triggerEvent();
}

