#include <string>
#include "format.h"
using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) { 
    long int minutes = seconds / 60;
    long int hours = minutes / 60;
    minutes = int(minutes%60);
    seconds = int(seconds % 60);
    string HH = std::to_string(hours);
    string MM = std::to_string(minutes);
    string SS = std::to_string(seconds);
    HH = (HH.length() == 1)? "0"+HH : HH;
    MM = (MM.length() == 1)? "0"+MM : MM;
    SS = (SS.length() == 1)? "0"+SS : SS;
    string time_ = HH + ":" + MM + ":" + SS;
    return time_;
}
