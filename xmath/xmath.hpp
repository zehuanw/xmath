#pragma once

#include "common.hpp"
#include "operand_policy.hpp"
#include "operation_policy.hpp"
#include <fstream>
#include <iostream>


namespace xmath{

template<int A_Config_, int B_Config_, int T_, int OP_>
struct param_trait;

template<int A_Config_, int B_Config_>
struct param_trait<A_Config_, B_Config_, OperandType::INT, Op::SUM>{
  typedef int Type;
  typedef OperandPolicy<A_Config_, Type> PolicyA;
  typedef OperandPolicy<B_Config_, Type> PolicyB;
  typedef OperationPolicy<Op::SUM, Type> PolicyOP;
  typedef std::pair<Type, Type> Pair;
  static Pair default_a(){
    return std::make_pair<Type, Type>(1,9);
  }
  static Pair default_b(){
    return std::make_pair<Type, Type>(9,1);
  }
  static Pair default_c(){
    return std::make_pair<Type, Type>(1,10);
  }
};

template<int A_Config_, int B_Config_>
struct param_trait<A_Config_, B_Config_, OperandType::FLOAT, Op::SUM>{
  typedef float Type;
  typedef OperandPolicy<A_Config_, Type> PolicyA;
  typedef OperandPolicy<B_Config_, Type> PolicyB;
  typedef OperationPolicy<Op::SUM, Type> PolicyOP;
  typedef std::pair<Type, Type> Pair;
  static Pair default_a(){
    return std::make_pair<Type, Type>(1.f,9.f);
  }
  static Pair default_b(){
    return std::make_pair<Type, Type>(1.f,1.f);
  }
  static Pair default_c(){
    return std::make_pair<Type, Type>(1.f,10.f);
  }
};

//TODO: implement other traits


template<typename T_>
struct Param{
  typedef T_ Type;
  int counter{0};
  int items;
  std::pair<T_, T_> a_limits;
  std::pair<T_, T_> b_limits;
  std::pair<T_, T_> c_limits;
  std::string doc;
  Param(int items_ = 30, 
    std::pair<T_, T_> a_limits_ = std::make_pair((T_)1,(T_)9), 
    std::pair<T_, T_> b_limits_ = std::make_pair((T_)1,(T_)1), 
    std::pair<T_, T_> c_limits_ = std::make_pair((T_)1,(T_)10), 
    std::string doc_ = "test.txt"): 
    items(items_), a_limits(a_limits_),
    b_limits(b_limits_), c_limits(c_limits_), doc(doc_)
  {
    //TODO: value check here;
  }
};


/*
 * PolicyA_ & PolicyB_ are Policies generate A and B
 */
template<class PolicyA_, class PolicyB_, 
  class PolicyOP_, typename T_ = int >
class Xmath{

  static bool valid(T_ a, T_ b, std::pair<T_,T_> c_limit){
    T_ c = PolicyOP_::calc(a, b);
    if(c_limit.first > c_limit.second){
      if(c >= c_limit.second && c <= c_limit.first){
	return true;
      }
      else{
	return false;
      }
    }
    else{
      if(c >= c_limit.first && c <= c_limit.second){
	return true;
      }
      else{
	return false;
      }
    }
    
  }
  typedef PolicyA_ PolicyA;
  typedef PolicyB_ PolicyB;
public:
  static void generate(Param<T_>& param){
    std::string doc_;
    int idx = 0;
    while(param.counter < param.items){
      T_ a = PolicyA::gen(idx, param.a_limits);
      T_ b = PolicyB::gen(idx, param.b_limits);
      if(valid(a, b, param.c_limits)){
	doc_ += std::to_string(a) + PolicyOP_::str() + std::to_string(b) + " =\n";
	param.counter++;
      }
      idx++;
    }
    std::ofstream fs(param.doc);
    fs << doc_;
    fs.close();
  }
};

} //namespace xmath
