namespace xmath{
/*
 * PolicyA_ & PolicyB_ are Policies generate A and B
 */
template<template<typename> class PolicyA_, 
  template<typename> class PolicyB_, 
  class PolicyOP_ = ADD, 
  typename T_ = int >
class Xmath{
  int counter_{0};
  std::pair<T_> a_limits_;
  std::pair<T_> b_limits_;
  int items_{30};
  std::string doc_{};
  bool valid(T_ a, T_ b, std::pair<T_> c_limit){
      
  }
  typedef PolicyA_<T_> PolicyA;
  typedef PolicyB_<T_> PolicyB;
public:
  //Ctor
  Xmath(int items, std::pair<T_> a_limits, std::pair<T_> b_limits, std::pair<T_> c_limits): items_(items), a_limits_(a_limits), b_limits_(b_limits){}
  void generate(){
    T_ a = PolicyA::gen(counter_, a_limits);
    T_ b = PolicyB::gen(counter_, b_limits);
    if(valid(a, b, c_limit)){
      counter_++;
      doc_ += std::to_string(a) + PolicyOP_::str() + std::to_string(b) + std::endl;
    }
  }
};

} //namespace xmath
