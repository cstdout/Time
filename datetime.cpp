#include "datetime.h"
#include <climits>
DateTime::DateTime()
{

}
DateTime::DateTime(const DateTime& d)
{
    _seconds = d.getTotalSeconds();
}
DateTime::DateTime(uint64_t s)
{
    _seconds = s;
}
uint32_t DateTime::daysInMonth(uint64_t m, bool leapYear)
{
    if(m == 2)
    {
        return (leapYear ? 29 : 28);
    }
    if(((m < 8) && (m & 1)) || ((m >= 8) && !(m & 1)))
    {
        return 31;
    }
    return 30;
}
uint64_t DateTime::secondsPassedFromEpochToYear(uint64_t year)
{
    uint64_t days = 0;
    for(uint64_t i = 1970; i < year; ++i)
    {
        days += (isLeap(i) ? 366 : 365);
    }
    return days * DAY_SEC;
}
uint64_t DateTime::secondsPassedFromNewYearToMonth(uint64_t month, bool leap)
{
    uint64_t days = 0;
    for(uint64_t i = 1; i < month; ++i)
    {
        days += daysInMonth(i, leap);
    }
    return days * DAY_SEC;
}
void DateTime::setDate(uint64_t year, uint64_t month, uint64_t day, uint64_t hours, uint64_t minutes, uint64_t seconds)
{
    uint64_t yearSec = secondsPassedFromEpochToYear(year);
    uint64_t monthSec = secondsPassedFromNewYearToMonth(month, isLeap(year));
    _seconds = yearSec + monthSec + (day - 1) * DAY_SEC + hours * HOURS_SEC + minutes * MINUTES_SEC + seconds;
}
DateTime::DateTime(uint32_t year, uint32_t month, uint32_t day, uint32_t hours, uint32_t minutes, uint32_t seconds)
{
    setDate(year, month, day, hours, minutes, seconds);
    std::cout << _seconds << std::endl;

}
bool DateTime::isLeap(uint64_t year)
{
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}
void DateTime::setYear(uint32_t year)
{
    setDate(year, getMonth(), getDay(), getHours(), getMinutes(), getSeconds());
}
void DateTime::setMonth(uint32_t month)
{
    setDate(getYear(), month, getDay(), getHours(), getMinutes(), getSeconds());
}
void DateTime::setDay(uint32_t day)
{
    setDate(getYear(), getMonth(), day, getHours(), getMinutes(), getSeconds());
}
uint64_t DateTime::getYear() const
{
    uint64_t days = _seconds / DAY_SEC;
    uint32_t y = 1970;
    for(; !(days < (isLeap(y) ? 366 : 365)) && (days > 364); ++y)
    {
        days -= (isLeap(y) ? 366 : 365);
    }
    return y;
}
uint64_t DateTime::getMonth() const
{
    uint64_t y = getYear();
    uint64_t days = (_seconds - secondsPassedFromEpochToYear(y)) / DAY_SEC;
    uint64_t m = 1;
    uint32_t d = daysInMonth(m, isLeap(y));
    while(days >= d)
    {
        days -= d;
        ++m;
        d = daysInMonth(m, isLeap(y));
    }
    return m;
}
uint64_t DateTime::getDay() const
{
   uint64_t y = getYear();
   uint64_t m = getMonth();
   uint64_t day = (_seconds - secondsPassedFromEpochToYear(y) - secondsPassedFromNewYearToMonth(m)) / DAY_SEC;
   if(m < 3)
   {
       ++day;
   }
   return day;
}
std::string& DateTime::yearString() const
{
    std::string* s = new std::string(std::to_string(getYear()));
    return *s;
}
std::string& DateTime::monthString() const
{
    std::string* s = new std::string(std::to_string(getMonth()));
    return *s;
}
std::string& DateTime::dayString() const
{
    std::string* s = new std::string(std::to_string(getDay()));
    return *s;
}
std::string& DateTime::getString(bool military) const
{
    std::string* s = new std::string("");
    s->operator+=(yearString() + std::string("/") + monthString() + std::string("/") + dayString() + std::string("/") + " " + Time::getString(military));
    return *s;
}
std::ostream& operator<<(std::ostream& out, const DateTime& t)
{
    out << t.getString(t.militaryOutputModeOn());
    return out;
}
std::istream& operator>>(std::istream& in, DateTime& t)
{
    uint32_t y, m, d, h, _m, s;
    in >> y >> m >> d >> h >> _m >> s;
    t.setDate(y, m, d, h, _m, s);
    return in;
}
DateTime& DateTime::shift(int32_t year,
                          int32_t month,
                          int32_t day,
                          int32_t hour,
                          int32_t minute,
                          int32_t seconds) const
{
    DateTime* d = new DateTime(getTotalSeconds());
    d->setDate(getYear() + year,
               getMonth() + month,
               getDay() + day,
               getHours() + hour,
               getMinutes() + minute,
               getSeconds() + seconds);
}
DateTime& DateTime::operator++()
{
    ++_seconds;
    return *this;
}
DateTime& DateTime::operator++(int)
{
    DateTime* t = new DateTime(getTotalSeconds());
    this->operator++();
    return *t;
}

DateTime& DateTime::operator--()
{
    if (!_seconds)
    {
        _seconds = UINT64_MAX - 1;
    }
    else
    {
        --_seconds;
    }
    return *this;
}
DateTime& DateTime::operator--(int)
{
    DateTime* t = new DateTime(getTotalSeconds());
    this->operator--();
    return *t;
}
