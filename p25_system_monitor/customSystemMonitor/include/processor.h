#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <string>

class Processor {
 public:
  Processor();  // constructor

  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
  private:
    std::vector<float> ConvertVectorStringToFloat(const std::vector<std::string> &);
    
    std::vector<float> cpuUtilization{};
    
    std::vector<float> previousCpuUtilization{};   // previous CPU utilization
 
    // loads on CPU
    float Idle(const std::vector<float> & cpuUtilization) const;
    float NonIdle(const std::vector<float> & cpuUtilization) const;
};

#endif
