#include "intdebounce.h"
#include "Arduino.h"
#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <vector>


//std::map <int,std::function<void(void)>> callbackMap;
std::map <int, uint64_t> dbDelay;
std::map <int, timer_type_t> timerType;
std::map <int, _gpi_timer_t> gpi_timer;



void isrcallbackX(uint8_t pin)
{
    gpi_timer[pin].pin = pin;
    gpi_timer[pin].timer = millis();
    gpi_timer[pin].delay = dbDelay[pin];
}



void isrcallback0(void)
{
    isrcallbackX(0);
}
void isrcallback1(void)
{
    isrcallbackX(1);
}
void isrcallback2(void)
{
    isrcallbackX(2);
}
void isrcallback3(void)
{
    isrcallbackX(3);
}
void isrcallback4(void)
{
    isrcallbackX(4);
}
void isrcallback5(void)
{
    isrcallbackX(5);
}
void isrcallback6(void)
{
    isrcallbackX(6);
}
void isrcallback7(void)
{
    isrcallbackX(7);
}
void isrcallback8(void)
{
    isrcallbackX(8);
}
void isrcallback9(void)
{
    isrcallbackX(9);
}
void isrcallback10(void)
{
    isrcallbackX(10);
}
void isrcallback11(void)
{
    isrcallbackX(11);
}
void isrcallback12(void)
{
    isrcallbackX(12);
}
void isrcallback13(void)
{
    isrcallbackX(13);
}
void isrcallback14(void)
{
    isrcallbackX(14);
}
void isrcallback15(void)
{
    isrcallbackX(15);
}
void isrcallback16(void)
{
    isrcallbackX(16);
}
void isrcallback17(void)
{
    isrcallbackX(17);
}
void isrcallback18(void)
{
    isrcallbackX(18);
}
void isrcallback19(void)
{
    isrcallbackX(19);
}
void isrcallback20(void)
{
    isrcallbackX(20);
}
void isrcallback21(void)
{
    isrcallbackX(21);
}
void isrcallback22(void)
{
    isrcallbackX(22);
}
void isrcallback23(void)
{
    isrcallbackX(23);
}
void isrcallback24(void)
{
    isrcallbackX(24);
}
void isrcallback25(void)
{
    isrcallbackX(25);
}
void isrcallback26(void)
{
    isrcallbackX(26);
}
void isrcallback27(void)
{
    isrcallbackX(27);
}
void isrcallback28(void)
{
    isrcallbackX(28);
}
void isrcallback29(void)
{
    isrcallbackX(29);
}
void isrcallback30(void)
{
    isrcallbackX(30);
}
void isrcallback31(void)
{
    isrcallbackX(31);
}
void isrcallback32(void)
{
    isrcallbackX(32);
}
void isrcallback33(void)
{
    isrcallbackX(33);
}
void isrcallback34(void)
{
    isrcallbackX(34);
}
void isrcallback35(void)
{
    isrcallbackX(35);
}
void isrcallback36(void)
{
    isrcallbackX(36);
}
void isrcallback37(void)
{
    isrcallbackX(37);
}
void isrcallback38(void)
{
    isrcallbackX(38);
}
void isrcallback39(void)
{
    isrcallbackX(39);
}
void isrcallback40(void)
{
    isrcallbackX(40);
}
void isrcallback41(void)
{
    isrcallbackX(41);
}

void (*isrcallback[42])() = {
isrcallback0,
isrcallback1,
isrcallback2,
isrcallback3,
isrcallback4,
isrcallback5,
isrcallback6,
isrcallback7,
isrcallback8,
isrcallback9,
isrcallback10,
isrcallback11,
isrcallback12,
isrcallback13,
isrcallback14,
isrcallback15,
isrcallback16,
isrcallback17,
isrcallback18,
isrcallback19,
isrcallback20,
isrcallback21,
isrcallback22,
isrcallback23,
isrcallback24,
isrcallback25,
isrcallback26,
isrcallback27,
isrcallback28,
isrcallback29,
isrcallback30,
isrcallback31,
isrcallback32,
isrcallback33,
isrcallback34,
isrcallback35,
isrcallback36,
isrcallback37,
isrcallback38,
isrcallback39,
isrcallback40,
isrcallback41
};

void intdebounce::setupPin(uint8_t pin,  std::function<void(void)> func )
{
    pinMode(pin,INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pin),isrcallback[pin],CHANGE);
    callbackMap[pin] = func;
    dbDelay[pin] = 50;
}

void intdebounce::setupPin(uint8_t pin,  std::function<void(void)> func, uint64_t delay)
{
    pinMode(pin,INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pin),isrcallback[pin],CHANGE);
    callbackMap[pin] = func;
    //Serial.printf("Pin %x is mapped\r\n",pin);
    dbDelay[pin] = delay;
}

int intdebounce::setupTimer(std::function<void(void)> func, timer_type_t tType) 
{
    setupTimer(func,tType,100);
}
int intdebounce::setupTimer(std::function<void(void)> func, timer_type_t tType, uint64_t delay)
{
    callbackMap[timerCount] = func;
    dbDelay[timerCount] = delay;
    timerType[timerCount] = tType;
    timerCount++;
    return (timerCount - 1);
}

void intdebounce::handleTimers(void)
{
    for(auto it = gpi_timer.begin(); it != gpi_timer.end(); )
    {
        uint8_t pin = it->first;       
        const _gpi_timer_t& tempStruct = it->second;
        if (tempStruct.delay == 0)
        {
            it = gpi_timer.erase(it);
        }
        else if((millis() - tempStruct.timer) > tempStruct.delay)
        {
            callbackMap[pin]();
            if(tempStruct.tType == 0)
            {
                it = gpi_timer.erase(it);
            }
            else
            {
                it++;
                gpi_timer[pin].timer = millis();
            }
        }
        else
        {
            it++;
        }


    }
}

intdebounce::intdebounce(/* args */)
{
    timerCount = 256;  // we jump to 256 to skip where gpis use the timers
}

intdebounce::~intdebounce()
{
}

void intdebounce::beginTimer(int id)
{
    gpi_timer[id].pin = id;
    gpi_timer[id].timer = millis();
    gpi_timer[id].delay = dbDelay[id];
    gpi_timer[id].tType = timerType[id];
}

void intdebounce::endTimer(int id)
{
    gpi_timer[id].tType = oneshot;
    gpi_timer[id].delay = 0;
}