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
    float memory_utilization = 100*(MemTotal - MemFree)/MemTotal;
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
  return {};
}


// TODO: Read and return the user ID associated with a process
// reference: https://man7.org/linux/man-pages/man5/proc.5.html
string LinuxParser::Uid(int pid) {
  std::ifstream ifs(kProcDirectory + "/" + std::to_string(pid) + kStatusFilename);
  
  if (ifs.is_open()){
    std::string line;
    std::string key, value;

    if(std::getline(ifs, line)){
      std::istringstream iss(line);
      iss >> key >> value;
      key.pop_back();
      if (key == "uid"){
        return value;
      }
    }
  }
  return string(); 
}


// TODO: Read and return the user associated with a process
// Reference: https://man7.org/linux/man-pages/man5/passwd.5.html
string LinuxParser::User(int pid) {
  std::string uid = Uid(pid);
  std::ifstream ifs(kPasswordPath);

  if (ifs.is_open()){
    std::string line;
    if(std::getline(ifs, line)){
      std::istringstream iss(line);
      std::string token, username, userid;
      int word_count = 0;

      while(std::getline(iss, token, ':')){
        if (word_count==0){
          username = token;
        } else if(word_count == 2){
          userid = token; 
        }

        word_count++;
        
        if (word_count > 2){
          break;
        }
      }

      if(userid==uid){
        return username;
      }

    }
  }
  return string(); 
}

// TODO: Read and return the command associated with a process.
// Notes: Linux stores the command used to launch the function in the /proc/[pid]/cmdline file.
string LinuxParser::Command(int pid) {
  std::ifstream ifs(kProcDirectory+ "/" + std::to_string(pid) + kCmdlineFilename);
  
  if (ifs.is_open()){
    std::string line;
    if (std::getline(ifs, line)){
      return line;
    }
  }
  return string(); 
}

// TODO: Read and return the uptime of a process
// Notes: Linux stores the process up time in /proc/[pid]/stat. (Time of start from system boot)
long LinuxParser::UpTime(int pid) {
  std::ifstream ifs(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
  
  if (ifs.is_open()){
    std::string line;
    if (std::getline(ifs, line)){
      std::istringstream iss(line);
      std::string token;

      long clockticks;

      int word_count = 0;
      while (std::getline(iss, token, ' ')){
        
        if (word_count==21){
          clockticks = std::stol(token);
          return clockticks/sysconf(_SC_CLK_TCK);
        }
        word_count ++;
      }
    }
  }
  return 0;
}

// TODO: Read and return the memory used by a process (RAM)
string LinuxParser::Ram(int pid) {
  std::ifstream ifs(kProcDirectory + "/" + std::to_string(pid) + kStatusFilename);
  
  if (ifs.is_open()){
    std::string line;

    std::string key;
    float ram;
    std::string kB;
    while (std::getline(ifs, line)){
      std::istringstream iss(line);
      iss >> key >> ram >> kB;
      key.pop_back();
      if (key=="VmSize"){
        ram *= 0.001;   // convert from kB to MB
        ram = roundf(ram * 100)/100;   // round to two decimal places
        return  std::to_string(ram);
      }
    }
  }
  return string();
}




// // TODO: Read and return the number of jiffies for the system
// long LinuxParser::Jiffies() {return 0; }

// // TODO: Read and return the number of active jiffies for a PID
// // REMOVE: [[maybe_unused]] once you define the function
// long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// // TODO: Read and return the number of active jiffies for the system
// long LinuxParser::ActiveJiffies() { return 0; }

// // TODO: Read and return the number of idle jiffies for the system
// long LinuxParser::IdleJiffies() { return 0; }
