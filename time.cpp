// Online C compiler to run C program online
#include <iostream>
#include <string>
#include <cstdint>
using namespace std;

class Time {
    uint64_t _seconds;
    public:
        static const uint64_t DAY_SEC = 86400;
        static const uint64_t HOURS_SEC = 3600;
        static const uint64_t MINUTES_SEC = 60;
     
        
        Time(uint64_t seconds = 0) {
            _seconds = seconds;
        }
        Time(Time& t) {
            //
        }
        Time(int32_t hours = 0,
                   int32_t minutes = 0,
                   int32_t seconds = 0) {
            _seconds = HOURS_SEC * hours + MINUTES_SEC * minutes + seconds;
    
        }
        
        
        void setSeconds(int32_t s) {
            uint64_t t =  _seconds - (_seconds % MINUTES_SEC);
            _seconds = t + s;
        }
        void setMinutes(int32_t m) {
             uint64_t t =  _seconds - (_seconds % HOURS_SEC);
            _seconds = t + MINUTES_SEC * m;
        }
        void setHours(int32_t h) {
            uint64_t t =  _seconds - (_seconds % DAY_SEC);
            _seconds = t + HOURS_SEC * h;
        }
        uint32_t getHours() const {
            return _seconds % DAY_SEC;
        }
        uint32_t getMinutes() const {
            return _seconds % HOURS_SEC;
        }
        uint32_t getSeconds() const {
            return _seconds % MINUTES_SEC;
        }
        uint64_t getTotalSeconds() const {
            return _seconds;
        }

        string& getMinutesStr() const {
            int32_t m = getMinutes();
            string* mStr = new string(to_string(m));
            (*mStr) += ((m < 10 ? string("0") : string("")) + (*mStr));
            return *mStr;
        }
        string& getHoursStr() const {
            int32_t h = getHours();
            cout << h << endl;
            string* hStr = new string(to_string(h));
            (*hStr) += ((h < 10 ? string("0") : string("")) + (*hStr));
            return *hStr;
        }
    
        string& toString(bool military = true) {
            string* res = new string("");
            if (military) {
                (*res) += getHoursStr() + string(":") + getMinutesStr();
            }
            else {
                //    
            }
            return *res;
            
        }
    
    
};



int main() {
    Time t(12, 30);
    
    cout << t.toString();

    return 0;
}
