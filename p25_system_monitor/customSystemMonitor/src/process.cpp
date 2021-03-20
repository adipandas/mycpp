#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid): pid(pid), command_(LinuxParser::Command(pid)), user_(LinuxParser::User(pid)){}

// TODO: Return this process's ID
int Process::Pid() { return pid; }

// TODO: Return the command that generated this process
string Process::Command() { return command_; }

// TODO: Return the user (name) that generated this process
string Process::User() { return user_; }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid); }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    std::ifstream ifs(LinuxParser::kProcDirectory + "/" + std::to_string(pid) + LinuxParser::kStatFilename);

    if (ifs.is_open()){
        std::string line;
        if (std::getline(ifs, line)){

            std::istringstream iss(line);
            std::string token;

            long total_time;
            long utime, stime, cutime, cstime, starttime;

            int word_count = 0;
            while (std::getline(iss, token, ' ')){
                if (word_count==13){
                    utime = std::stol(token);
                } else if (word_count == 14){
                    stime = std::stol(token);
                } else if (word_count == 15){
                    cutime = std::stol(token);
                } else if (word_count == 16){
                    cstime = std::stol(token);
                } else if (word_count == 21){
                    starttime = std::stol(token);
                }
                
                word_count ++;
                if (word_count > 21){
                    break;
                }
            }
            total_time = utime + stime;
            total_time += cutime + cstime;
            auto seconds = LinuxParser::UpTime() - (starttime / sysconf(_SC_CLK_TCK));
            float cpu_usage = 100.0 * ((total_time / sysconf(_SC_CLK_TCK)) / seconds);
            cpu_utilization_ = cpu_usage;
            return cpu_usage;
        }
    }
    return 0.0; 
}

// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
    return cpu_utilization_ < a.cpu_utilization_;
}
