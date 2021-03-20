#include "linux_parser.h"
#include "processor.h"

using namespace LinuxParser;

std::vector<float> Processor::ConvertVectorStringToFloat(const std::vector<std::string>  & vecString){ // convert vector of strings to vector of floats
    std::vector<float> vecFloat{};
    for (auto s : vecString){
        vecFloat.push_back(std::stof(s));
    }
    
    return vecFloat;
}


float Processor::Idle(const std::vector<float> & cpuUtilization) const {
    return cpuUtilization[CPUStates::kIdle_] + cpuUtilization[CPUStates::kIOwait_];
}

float Processor::NonIdle(const std::vector<float> & cpuUtilization) const{
    float nonIdle = cpuUtilization[CPUStates::kUser_] + cpuUtilization[CPUStates::kNice_] + cpuUtilization[CPUStates::kSystem_] + cpuUtilization[CPUStates::kIRQ_] + cpuUtilization[CPUStates::kSoftIRQ_]+cpuUtilization[CPUStates::kSteal_];
    return nonIdle;
}


Processor::Processor(){
    std::vector<std::string> _utilization{};
    while(_utilization.empty()){
        _utilization = CpuUtilization();
    }
    previousCpuUtilization = ConvertVectorStringToFloat(_utilization);
}


// TODO: Return the aggregate CPU utilization
// Reference: https://stackoverflow.com/a/23376195
float Processor::Utilization() {

    std::vector<std::string> _utilization{};
    while(_utilization.empty()){
        _utilization = CpuUtilization();
    }

    cpuUtilization = ConvertVectorStringToFloat(_utilization);
    float _CurrentIdle = Idle(cpuUtilization);
    float _CurrentNonIdle = NonIdle(cpuUtilization);
    float _CurrentTotal = _CurrentIdle + _CurrentNonIdle;
    float _PreviousIdle = Idle(previousCpuUtilization);
    float _PreviousNonIdle = NonIdle(previousCpuUtilization);
    float _PreviousTotal = _PreviousIdle + _PreviousNonIdle;
    
    float _TotalLoad = _CurrentTotal - _PreviousTotal;
    float _Idled = _CurrentIdle - _PreviousIdle;
    
    float utilization_percent = (_TotalLoad - _Idled)/_TotalLoad;

    // float utilization_percent = (_CurrentTotal - _CurrentIdle)/_CurrentTotal;
    
    previousCpuUtilization = cpuUtilization;
    return utilization_percent; 
}
