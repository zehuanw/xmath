#pragma once
#include <ctime>
#include <random>
namespace xmath{
/*
 * Generate numbers 
 */
template<int OperandConfig_, typename T_> 
struct OperandPolicy;

template<>
struct OperandPolicy<OperandConfig::SEQ, int>{
  static int gen(int idx, std::pair<int, int> limits){
    int bigger = limits.first >= limits.second ? limits.first : limits.second;
    int smaller = limits.first < limits.second ? limits.first : limits.second;
    int local_id = idx % (bigger - smaller + 1);

    int num = limits.first >= limits.second ? (bigger - local_id):(smaller + local_id);
    return num; 
  }
};

template<>
struct OperandPolicy<OperandConfig::RAND, int>{
  static int gen(int idx, std::pair<int, int> limits){
    int bigger = limits.first >= limits.second ? limits.first : limits.second;
    int smaller = limits.first < limits.second ? limits.first : limits.second;
    std::default_random_engine e(time(0));
    std::uniform_int_distribution<int> u(smaller, bigger);
    return u(e);
  }
};

template<>
struct OperandPolicy<OperandConfig::RAND, float>{
  static float gen(int idx, std::pair<float, float> limits){
    float bigger = limits.first >= limits.second ? limits.first : limits.second;
    float smaller = limits.first < limits.second ? limits.first : limits.second;
    std::default_random_engine e(time(0));
    std::uniform_real_distribution<float> u(smaller, bigger);
    return u(e);
  }
};
} //namespace xmath
