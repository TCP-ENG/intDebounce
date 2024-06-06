# intDebounce
This is a library function for the Teensy 4.1 (this may work on other devices but has not been tested)

This library has 2 main functions

* ## Software debounce
    
    This sets up an interrupt for a given hardware pin so when the state changes the interrupt will start a debounce timer.
    ### Usage
    ```c++
    #include "intdebounce.h"

    int pin  = 6;

    void button()
    {
        Serial.println("button");
        if(digitalRead(pin) == HIGH)
        {
            Serial.println("relaesed");
        }
        else{
            Serial.println("pressed");
        }
    }
    intdebounce iDB;
    
    void setup() {
        iDB.setupPin(pin,button,50);
    }

    void loop() {
    iDB.handleTimers();
    }
    ```

* ## Software timer
    
    This sets up a timer that can be either countinious or one shot

    ```c++
    #include "intdebounce.h"

    uint64_t delay = 5000;

    void printsomething(void)
    {
        Serial.println("Something");
    }

    intdebounce iDB;
    
    void setup() {
        int timer = iDB.setupTimer(printsomething,continuios,delay);
        iDB.beginTimer(timer);
    }

    void loop() {
    iDB.handleTimers();
    }

    ```

    