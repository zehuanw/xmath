#include "common.hpp"
#include "xmath.hpp"
#include <map>
#include <stdexcept>

std::string usage("Usage: xmath [Option]...\n Generage math examination for different level.\n \n   --a-config=CONFIG         Config operand A which can be either RAND / SEQ\n   --b-config=CONFIG         Config operand B which can be either RAND / SEQ\n   --a-range=PAIR            Set a's range: e.g. 1,10\n   --b-range=PAIR            Set b's range: e.g. 10,1\n   --c-range=PAIR            Set c's range: e.g. 10,1\n   --operation=OP            OP should be either SUM / MUL / SUB / DIV\n   --type=TYPE               TYPE can be INT or FLOAT\n   --help                    Show these information");

using namespace xmath;
int main(int argc, char* argv[]){
  try
  {
    enum class OPT {A_RANGE, B_RANGE, C_RANGE, DOC_NAME, ITEMS};
    std::vector<std::pair<std::string, OPT>> option_map = {
      {"--a-range=", OPT::A_RANGE},
      {"--b-range=", OPT::B_RANGE},
      {"--c-range=", OPT::C_RANGE},
      {"--doc=", OPT::DOC_NAME},
      {"--items=", OPT::ITEMS}
    };

    //default config
    constexpr OperandConfig::E a_config = OperandConfig::SEQ;
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

    for(int i = 1; i < argc; i++){
      std::string option(argv[i]);
      for(auto option_pair: option_map){
	auto pos = option.find(option_pair.first);
	if(pos != std::string::npos){
	  //found in option_map
	  pos = pos+option_pair.first.size();
	  std::string args_string = option.substr(pos);
	  switch(option_pair.second){
	  case OPT::A_RANGE:
	    {
	      auto pos_comma = args_string.find(",");
	      int start = std::stoi(args_string.substr(0, pos_comma));
	      int end = std::stoi(args_string.substr(pos_comma + 1));
	      a_limits = param_trait::Pair(start, end);
	    }
	    break;
	  case OPT::B_RANGE:
	    {
	      auto pos_comma = args_string.find(",");
	      int start = std::stoi(args_string.substr(0, pos_comma));
	      int end = std::stoi(args_string.substr(pos_comma + 1));
	      b_limits = param_trait::Pair(start, end);
	    }
	    break;
	  case OPT::C_RANGE:
	    {
	      auto pos_comma = args_string.find(",");
	      int start = std::stoi(args_string.substr(0, pos_comma));
	      int end = std::stoi(args_string.substr(pos_comma + 1));
	      c_limits = param_trait::Pair(start, end);
	    }
	    break;
	  case OPT::ITEMS:
	    {
	      items = std::stoi(args_string);
	    }
	    break;
	  case OPT::DOC_NAME:
	    {
	      doc = args_string;
	    }
	    break;
	  default:
	    {
	      //wrong input
	      std::cout << usage;
	      throw std::runtime_error("Error: No such option");
	    }
	  }
	}
      }
      //cannot find in option_map
    }


    //arg parsing
    xmath::Param<param_trait::Type> param(items, a_limits, b_limits, c_limits, doc);

    //generating
    xmath::Xmath<param_trait::PolicyA, param_trait::PolicyB, param_trait::PolicyOP, param_trait::Type>::generate(param);
  }
  catch(const std::runtime_error& e){
    std::cout << e.what() << std::endl;
  }
  return 0;
}
