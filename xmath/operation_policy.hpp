namespace xmath{

template<int OP_, typename T_>
struct OperationPolicy;

template<typename T_>  
struct OperationPolicy<Op::SUM, T_>{
  static T_ calc(T_ a, T_ b){
    return a + b;
  } 
  static std::string str(){
    return std::string(" + ");
  }
};

template<typename T_>  
struct OperationPolicy<Op::SUB, T_>{
  static T_ calc(T_ a, T_ b){
    return a - b;
  } 
  static std::string str(){
    return std::string(" - ");
  }
};

template<typename T_>  
struct OperationPolicy<Op::MUL, T_>{
  static T_ calc(T_ a, T_ b){
    return a * b;
  } 
  static std::string str(){
    return std::string(" x ");
  }
};

template<typename T_>  
struct OperationPolicy<Op::DIV, T_>{
  static T_ calc(T_ a, T_ b){
    return a / b;
  } 
  static std::string str(){
    return std::string(" / ");
  }
};

} //namespace xmath
