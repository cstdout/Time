#ifndef TIME_H
#define TIME_H
#include <cstdint>
#include <string>
#include <iostream>
class Time
{
private:
    bool militaryOutputMode = true;
protected:
    uint64_t _seconds = 0;
public:
    static const uint32_t MINUTES_SEC = 60;
    static const uint32_t HOURS_SEC = 3600;
    static const uint32_t MAX_TIME_VAL_SEC = 24 * HOURS_SEC;
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
    void setMilitaryOutputMode(bool flag);

    bool militaryOutputModeOn() const;

    bool operator==(const Time& other) const;
    bool operator!=(const Time& other) const;
    bool operator<(const Time& other) const;
    bool operator<=(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator>=(const Time& other) const;
    Time& operator+(const Time& other) const;
    Time& operator-(const Time& other) const;
    Time& operator+=(const Time& other);
    Time& operator-=(const Time& other);

    //prefix
    Time& operator++();

    // postfix
    Time& operator++(int);

    //prefix
    Time& operator--();

    // postfix
    Time& operator--(int);

    std::string& hoursString(bool military = true) const;
    std::string& minutesString() const;
    std::string& secondsString() const;
    std::string& getString(bool military = true) const;

    friend std::ostream& operator<<(std::ostream& out, const Time& t);
    friend std::istream& operator>>(std::istream& in, Time& t);

};

#endif // TIME_H
