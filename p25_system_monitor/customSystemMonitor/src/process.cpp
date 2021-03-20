#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;


Process::Process(int pid): pid_(pid){
    cpu_utilization_ = Process::CpuUtilization();
    command_ = LinuxParser::Command(pid);
    user_ = LinuxParser::User(pid);
}


// TODO: Return this process's ID
int Process::Pid() {
    return pid_; 
}


// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    long hertz = sysconf(_SC_CLK_TCK);
    float total_time=0., seconds=0.;
    total_time = LinuxParser::ActiveJiffies(pid_) / hertz;
    seconds = LinuxParser::UpTime(pid_);
    return (total_time/seconds);
}


// TODO: Return the command that generated this process
string Process::Command() {
    return command_; 
}


// TODO: Return this process's memory utilization
string Process::Ram() {
    return LinuxParser::Ram(pid_);
}


// TODO: Return the user (name) that generated this process
string Process::User() {
    return LinuxParser::User(pid_);
}


// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {
    return LinuxParser::UpTime(pid_);
}


// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator< (Process const& a) const {
    return cpu_utilization_ > a.cpu_utilization_;
}
