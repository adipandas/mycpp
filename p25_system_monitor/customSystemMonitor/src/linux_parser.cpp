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
  std::ifstream meminfo(kProcDirectory + kMeminfoFilename);
  std::string line;
  int MemTotal=0, MemFree=0; //MemAvailable=0, Buffers=0;

  if (meminfo.is_open()){
    std::string varname;
    long int m;
    std::string kb;

    int assigned = 0;
    while (std::getline(meminfo, line)){
      std::istringstream iss(line);
      iss >> varname >> m >> kb;

      if (varname == "MemTotal:"){
        MemTotal = m;
        assigned++;
      } else if (varname == "MemFree:"){
        MemFree = m;
        assigned++;
      } 

      if (assigned == 2){
        break;
      }
    }
    float memory_utilization = 100.0 * (MemTotal - MemFree)/MemTotal;
    return memory_utilization;
  }

  return 0.0;
}


// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  long uptime=0, idle_time=0;

  std::ifstream ifs(kProcDirectory+kUptimeFilename);

  if (ifs.is_open()){
    std::string line;
    if (std::getline(ifs, line)){
      std::istringstream iss(line);
      iss >> uptime >> idle_time;
    }
  }
  return uptime; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
    std::ifstream ifs(kProcDirectory+kStatFilename);
    
    if (ifs.is_open()){
      std::string line;
      long int n_processes;
      std::string processes_key;
      while (std::getline(ifs, line)){
        std::istringstream iss(line);
        
        iss >> processes_key >> n_processes;
        if (processes_key == "processes") {
          return n_processes;
        }
      }
    }
    return 0;
}


// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  std::ifstream ifs(kProcDirectory+kStatFilename);
    
    if (ifs.is_open()){
      std::string line;
      long int n_processes;
      std::string processes_key;
      while (std::getline(ifs, line)){
        std::istringstream iss(line);
        
        iss >> processes_key >> n_processes;
        if (processes_key == "procs_running") {
          return n_processes;
        }
      }
    }
   return 0;
}


// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  std::ifstream ifs(kProcDirectory+kStatFilename);
  if (ifs.is_open()){
    std::string line;
    std::string cpu;
    std::string user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    if (std::getline(ifs, line)){
      std::istringstream iss(line);
      iss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;

      return vector<std::string>{user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice};
    }
  }

  // May need in future.
  // PrevIdle = previdle + previowait
  // Idle = idle + iowait
  // PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal
  // NonIdle = user + nice + system + irq + softirq + steal
  // PrevTotal = PrevIdle + PrevNonIdle
  // Total = Idle + NonIdle
  // # differentiate: actual value minus the previous one
  // totald = Total - PrevTotal
  // idled = Idle - PrevIdle
  // CPU_Percentage = (totald - idled)/totald

   return {}; 
}


// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }