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
    return (_seconds / MINUTES_SEC) % 60;
}
uint64_t Time::getHours() const
{
    return (_seconds / HOURS_SEC) % 24;
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
bool Time::militaryOutputModeOn() const
{
    return militaryOutputMode;
}
bool Time::operator==(const Time& other) const
{
    return _seconds == other.getTotalSeconds();
}
bool Time::operator!=(const Time& other) const
{
    return _seconds != other.getTotalSeconds();
}
bool Time::operator<(const Time& other) const
{
    return _seconds < other.getTotalSeconds();
}
bool Time::operator<=(const Time& other) const
{
    return _seconds <= other.getTotalSeconds();
}
bool Time::operator>(const Time& other) const
{
    return _seconds > other.getTotalSeconds();
}
bool Time::operator>=(const Time& other) const
{
    return _seconds >= other.getTotalSeconds();
}
void Time::setMilitaryOutputMode(bool flag)
{
    militaryOutputMode = flag;
}
Time& Time::operator+(const Time& other) const
{
    return *(new Time(_seconds + other.getTotalSeconds()));
}
Time& Time::operator-(const Time& other) const
{
    Time* t = new Time(_seconds);
    t->operator-=(other);
    return *t;
}
Time& Time::operator+=(const Time& other)
{
    _seconds += other.getTotalSeconds();
    return *this;
}
Time& Time::operator-=(const Time& other)
{
    uint64_t s = other.getTotalSeconds();
    if(_seconds < s)
    {
        uint64_t t = s - _seconds;
        _seconds = MAX_VAL_SEC - t;
    }
    else
    {
        _seconds -= s;
    }
    return *this;
}
std::string& Time::hoursString(bool military) const
{
    uint64_t h = getHours();
    if (!military)
    {
        h %= 12;
        if(!h)
        {
            h = 12;
        }
    }
    return *(new std::string((h < 10 ? "0" : "") + std::to_string(h)));
}
std::string& Time::minutesString() const
{
    uint64_t m = getMinutes();
    return *(new std::string((m < 10 ? "0" : "") + std::to_string(m)));
}
std::string& Time::secondsString() const
{
    uint64_t s = getSeconds();
    return *(new std::string((s < 10 ? "0" : "") + std::to_string(s)));
}
std::string& Time::getString(bool military) const
{
    std::string* res = new std::string("");
    res->operator+=(hoursString(military) + std::string(":") + minutesString() + std::string(":") + secondsString());
    if(!military)
    {
        uint64_t h = getHours();
        bool amRes = (h < 12);
        res->operator+=(amRes ? " am": " pm");
    }
    return *res;
}
std::ostream& operator<<(std::ostream& out, const Time& t)
{
    out << t.getString(t.militaryOutputMode);
    return out;
}
std::istream& operator>>(std::istream& in, Time& t)
{
    uint32_t h, m, s;
    in >> h >> m >> s;
    t.setHours(h);
    t.setMinutes(m);
    t.setSeconds(s);
    return in;
}
Time& Time::operator++()
{
    ++_seconds;
    return *this;
}
Time& Time::operator++(int)
{
    Time* t = new Time(getTotalSeconds());
    this->operator++();
    return *t;
}

Time& Time::operator--()
{
    if (!_seconds)
    {
        _seconds = MAX_VAL_SEC - 1;
    }
    else
    {
        --_seconds;
    }
    return *this;
}
Time& Time::operator--(int)
{
    Time* t = new Time(getTotalSeconds());
    this->operator--();
    return *t;
}

