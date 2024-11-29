#include <iostream>
#include "time.h"
using namespace std;

int main()
{
    Time t(5, 12, 0);
    cout << t.getSeconds() << endl;
    t.setHours(23);
    cout << t.getHours();
    return 0;
}
