namespace xmath{

template<typename T_>  
struct ADD{
  static T_ calc(T_ a, T_ b){
    return a + b;
  } 
  static std::string str(){
    return " + "
  }
};

template<typename T_>  
struct SUB{
  static T_ calc(T_ a, T_ b){
    return a - b;
  } 
  static std::string str(){
    return " - "
  }
};

template<typename T_>  
struct MUL{
  static T_ calc(T_ a, T_ b){
    return a * b;
  } 
  static std::string str(){
    return " x "
  }
};

template<typename T_>  
struct DIV{
  static T_ calc(T_ a, T_ b){
    return a / b;
  } 
  static std::string str(){
    return " / "
  }
};

} //namespace xmath
