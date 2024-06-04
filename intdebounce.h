#ifndef _INTDEBOUNCE_H_
#define _INTDEBOUNCE_H_


#include <map>
#include <string>
#include <functional>
#include <vector>


enum timer_type_t 
{
    oneshot = 0,
    continuous = 1
};


struct _gpi_timer_t
{
    uint8_t pin;
    uint64_t timer;
    uint64_t delay;
    timer_type_t tType;
};


class intdebounce
{
private:
    /* data */
    int timerCount;
    std::map<std::string, std::function<int(const std::string&, int)>> functions;
    std::vector<std::function<int(const std::string&, int)>> functionList;
    std::map <int,std::function<void(void)>> callbackMap;
public:
    void beginTimer(int timer);
    void endTimer(int timer);
    void handleTimers(void);
    int setupTimer(std::function<void(void)> func,timer_type_t tType); 
    int setupTimer(std::function<void(void)> func, timer_type_t tType, uint64_t delay);
    void setupPin(uint8_t pin, std::function<void(void)> func);
    void setupPin(uint8_t pin, std::function<void(void)> func, uint64_t delay);
    intdebounce(/* args */);
    ~intdebounce();
};

 




#endif