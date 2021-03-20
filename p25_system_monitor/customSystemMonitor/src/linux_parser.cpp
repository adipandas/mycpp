#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;


// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}


// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}


// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}


// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  float MemTotal, MemFree;
  std::string line, kb, key, value;

  std::ifstream meminfo(kProcDirectory + kMeminfoFilename);
  if (meminfo.is_open()){
    while (std::getline(meminfo, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream iss(line);
      while (iss >> key >> value >> kb){
        if (key == "MemTotal"){ MemTotal = std::stof(value); }
        if (key == "MemFree"){ MemFree = std::stof(value); }
      }
    }
  }
  return (MemTotal - MemFree)/MemTotal;
}


// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  std::string line, uptime_str, idletime_str;
  std::ifstream ifs(kProcDirectory + kUptimeFilename);
  if (ifs.is_open()){
    if (std::getline(ifs, line)){
      std::istringstream iss(line);
      if(iss >> uptime_str >> idletime_str){
        return std::stol(uptime_str);
      }
    }
  }
  return 0;
}


// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  std::string line, token;
  std::vector<string> cpu_stats;
  std::ifstream ifs(kProcDirectory + kStatFilename);
  if (ifs.is_open()){
    if (std::getline(ifs, line)){
      std::istringstream iss(line);  // take first line
      while(iss>>token){              // iterate on first line        
        if (token != "cpu"){
          cpu_stats.push_back(token); // grab all values except "cpu"
        }
      }
    }
  }
  return cpu_stats;
}


// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  std::string line, processes_key, process_val;
  std::ifstream ifs(kProcDirectory+kStatFilename);
  if (ifs.is_open()){
    while (std::getline(ifs, line)){
      std::istringstream iss(line);
      while(iss >> processes_key >> process_val){
        if (processes_key == "processes") { return std::stoi(process_val); }
      }
    }
  }
  return 0;
}


// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  std::string line, processes_key, processes_val;
  std::ifstream ifs(kProcDirectory + kStatFilename);
  if (ifs.is_open()){
    while (std::getline(ifs, line)){
      std::istringstream iss(line);
      while(iss >> processes_key >> processes_val){
        if (processes_key == "procs_running") {
          return std::stoi(processes_val);
        }
      }
    }
  }
  return 0;
}


// TODO: Read and return the command associated with a process.
// Notes: Linux stores the command used to launch the function in the /proc/[pid]/cmdline file.
string LinuxParser::Command(int pid) {
  std::string line;
  std::ifstream ifs(kProcDirectory+ "/" + std::to_string(pid) + kCmdlineFilename);
  if (ifs.is_open()){
    if (std::getline(ifs, line)){
      return line;
    }
  }
  return string();
}


// TODO: Read and return the memory used by a process (RAM)
string LinuxParser::Ram(int pid) {
  std::string line, key, value, kb;
  int vmsize;
  std::ifstream ifs(kProcDirectory + "/" + std::to_string(pid) + kStatusFilename);
  if (ifs.is_open()){
    while (std::getline(ifs, line)){
      std::istringstream iss(line);
      while(iss >> key >> value >> kb){
        if (key=="VmSize:"){
          vmsize = std::stoi(value);
          vmsize /= 1000;                   // convert from kB to MB
          return  std::to_string(vmsize);
        }
      }
    }
  }
  return string();
}


// TODO: Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) {
  std::string line, token;
  vector<string> process_stats;
  long total_time, utime, stime, cutime, cstime;
  std::ifstream ifs(LinuxParser::kProcDirectory + "/" + std::to_string(pid) + LinuxParser::kStatFilename);
  if (ifs.is_open()){
    if (std::getline(ifs, line)){
      std::istringstream iss(line);
      while (iss >> token) { process_stats.push_back(token); }
    }
  }
  utime = std::stol(process_stats[13]);
  stime = std::stol(process_stats[14]);
  cutime = std::stol(process_stats[15]);
  cstime = std::stol(process_stats[16]);
  total_time = (utime + stime + cutime + cstime);
  return total_time;
}


// TODO: Read and return the user ID associated with a process
// reference: https://man7.org/linux/man-pages/man5/proc.5.html
string LinuxParser::Uid(int pid) { 
  string key, value, uid, user, line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)){
  		std::istringstream linestream(line);
    	while (linestream >> key >> value) {
        	if (key == "Uid:") { 
              	uid = value;
               }
        	}
      	}
    }
  return uid;
}


// TODO: Read and return the user associated with a process
// Reference: https://man7.org/linux/man-pages/man5/passwd.5.html
string LinuxParser::User(int pid) {
  string usr, passwd, uid, line;
  string uid_ = LinuxParser::Uid(pid);
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
    	while (linestream >> usr >> passwd >> uid) {
               if (uid==uid_){
                return usr;
               }
        	}
      	}
    }
  return string();
}


// TODO: Read and return the uptime of a process
// Notes: Linux stores the process up time in /proc/[pid]/stat. (Time of start from system boot)
long LinuxParser::UpTime(int pid) {
  std::string line, token;
  long start_time, uptime;
  vector<string> process_stats;

  std::ifstream ifs(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
  
  if (ifs.is_open()){
    if (std::getline(ifs, line)){
      std::istringstream iss(line);
      while (iss >> token){
        process_stats.push_back(token);
      }
    }std::cout << usr;
  }

  start_time = std::stol(process_stats[21])/ sysconf(_SC_CLK_TCK);
  uptime = LinuxParser::UpTime() - start_time;
  return uptime;
}
