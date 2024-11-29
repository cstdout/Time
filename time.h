#ifndef TIME_H
#define TIME_H
#include <cstdint>

class Time
{
    uint64_t _seconds = 0;

public:
    static const uint32_t MINUTES_SEC = 60;
    static const uint32_t HOURS_SEC = 3600;
//    static const uint32_t DAY_SEC = 86400;
    Time();
    Time(uint64_t s);
    Time(uint32_t hours, uint32_t minutes = 0, uint32_t seconds = 0);
    Time(const Time&);

    uint64_t getSeconds() const;
    uint64_t getMinutes() const;
    uint64_t getHours() const;
    uint64_t getTotalSeconds() const;

    void setSeconds(uint32_t s);
    void setTotalSeconds(uint64_t s);
    void setHours(uint32_t h);
    void setMinutes(uint32_t m);

    bool operator==(const Time& other) const;
    bool operator!=(const Time& other) const;
    bool operator<(const Time& other) const;
    bool operator<=(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator>=(const Time& other) const;

};

#endif // TIME_H
