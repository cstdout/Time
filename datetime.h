#ifndef DATETIME_H
#define DATETIME_H
#include "time.h"

class DateTime : public Time
{
    static uint32_t daysInMonth(uint64_t month, bool leapYear = false);
    static uint64_t secondsPassedFromEpochToYear(uint64_t year);
    static uint64_t secondsPassedFromNewYearToMonth(uint64_t month, bool leapYear = false);

public:
    static const uint64_t DAY_SEC = 86400;
    DateTime();
    DateTime(const DateTime& d);
    DateTime(uint64_t s);
    DateTime(uint32_t year,
             uint32_t month = 0,
             uint32_t day = 0,
             uint32_t hours = 0,
             uint32_t minutes = 0,
             uint32_t seconds = 0);

    static bool isLeap(uint64_t year);

    uint64_t getYear() const;
    uint64_t getMonth() const;
    uint64_t getDay() const;

    void setDate(uint64_t year = 0,
                 uint64_t month = 0,
                 uint64_t day = 0,
                 uint64_t hours = 0,
                 uint64_t minutes = 0,
                 uint64_t seconds = 0);
    void setYear(uint32_t year);
    void setMonth(uint32_t month);
    void setDay(uint32_t day);

    DateTime& shift(int32_t year = 0,
                    int32_t month = 0,
                    int32_t day = 0,
                    int32_t hour = 0,
                    int32_t minute = 0,
                    int32_t secodns = 0) const;

    //prefix
    DateTime& operator++();

    // postfix
    DateTime& operator++(int);

    //prefix
    DateTime& operator--();

    // postfix
    DateTime& operator--(int);

    std::string& yearString() const;
    std::string& monthString() const;
    std::string& dayString() const;
    std::string& getString(bool military = true) const;


    friend std::ostream& operator<<(std::ostream& out, const DateTime& t);
    friend std::istream& operator>>(std::istream& in, DateTime& t);

};

#endif // DATETIME_H
