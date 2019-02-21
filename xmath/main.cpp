#include "common.hpp"
#include "xmath.hpp"

std::string usage("Usage: xmath [Option]...\n Generage math examination for different level.\n \n   --a-config=CONFIG         Config operand A which can be either RAND / SEQ\n   --b-config=CONFIG         Config operand B which can be either RAND / SEQ\n   --a-range=PAIR            Set a's range: e.g. 1,10\n   --b-range=PAIR            Set b's range: e.g. 10,1\n   --c-range=PAIR            Set c's range: e.g. 10,1\n   --operation=OP            OP should be either SUM / MUL / SUB / DIV\n   --type=TYPE               TYPE can be INT or FLOAT\n   --help                    Show these information");

using namespace xmath;
int main(int argc, char* argv[]){
  //default config
  constexpr OperandConfig::E a_config = OperandConfig::RAND;
  constexpr OperandConfig::E b_config = OperandConfig::SEQ;
  constexpr Op::E op = Op::SUM;
  constexpr OperandType::E type = OperandType::INT;
  
  //param initilization
  int items = 30;
  
  typedef xmath::param_trait<a_config, b_config, type, op> param_trait;
  param_trait::Pair a_limits = param_trait::default_a(); 
  param_trait::Pair b_limits = param_trait::default_b(); 
  param_trait::Pair c_limits = param_trait::default_c();
  std::string doc = "test.txt";

  //arg parsing
  xmath::Param<param_trait::Type> param(items, a_limits, b_limits, c_limits, doc);

  //generating
  for(int i=0; i<10; i++){
    xmath::Xmath<param_trait::PolicyA, param_trait::PolicyB, param_trait::PolicyOP, param_trait::Type>::generate(param);
  }
  return 0;
}
