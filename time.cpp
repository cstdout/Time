#include "time.h"

Time::Time()
{

}
Time::Time(uint64_t s)
{
    _seconds = s;
}
Time::Time(uint32_t hours, uint32_t minutes, uint32_t seconds)
{
    _seconds = ((hours % 24) * HOURS_SEC)  + ((minutes % 60) * MINUTES_SEC) + (seconds % 60);
}
Time::Time(const Time& t)
{
    setTotalSeconds(t.getTotalSeconds());
}
uint64_t Time::getTotalSeconds() const
{
    return _seconds;
}
uint64_t Time::getSeconds() const
{
    return _seconds % 60;
}
uint64_t Time::getMinutes() const
{
    return (_seconds / MINUTES_SEC) % MINUTES_SEC;
}
uint64_t Time::getHours() const
{
    return (_seconds / HOURS_SEC) % MINUTES_SEC;
}
void Time::setTotalSeconds(uint64_t s)
{
    _seconds = s;
}

void Time::setSeconds(uint32_t s)
{
    uint64_t currentSeconds = getSeconds();
    uint64_t t = _seconds;
    if (currentSeconds > 0)
    {
        t -= currentSeconds;
    }

    t += (s % 60);
    _seconds = t;
}
void Time::setHours(uint32_t h)
{
    uint64_t currentHours = getHours();
    uint64_t t = _seconds;
    if (currentHours > 0)
    {
        t -= currentHours * HOURS_SEC;
    }
    t += (HOURS_SEC * (h % 24));
    _seconds = t;
}
void Time::setMinutes(uint32_t m)
{
    uint64_t currentMinutes = getMinutes();
    uint64_t t = _seconds;
    if (currentMinutes > 0)
    {
        t -= currentMinutes * MINUTES_SEC;
    }

    t += (MINUTES_SEC * (m % 60));
    _seconds = t;
}

