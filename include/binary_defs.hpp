#ifndef BINARY_DEFS_HPP
#define BINARY_DEFS_HPP

#include <memory>
#include <string>

namespace Binary {

enum TYPE {
  ADD,
  SUBTRACT,
  MULTIPLY,
  DIVIDE,
  UNDEFINED
};

inline std::string typeToString( TYPE type ) {
  std::string typeString;
  switch(type) {
    case ADD:        typeString = "add";       break;
    case SUBTRACT:   typeString = "sub";       break;
    case MULTIPLY:   typeString = "mult";      break;
    case DIVIDE:     typeString = "div";       break;
    default:         typeString = "undefined"; break;
  }
  return typeString;
}

inline TYPE stringToType( const std::string &s ) {
  TYPE t;
  for( int i=ADD; i<UNDEFINED; ++i ) {
    t = static_cast<TYPE>(i);
    if( !s.compare(typeToString(t)) ) { 
      return t;
    }
  }
  return UNDEFINED;
}

inline std::shared_ptr<Operation> getOperation( const std::string & s ) {

  TYPE t = stringToType(s);
  std::shared_ptr<Operation> op;
  
  switch(t) {
    case ADD:      op = std::make_shared<Add>();      break;
    case SUBTRACT: op = std::make_shared<Subtract>(); break;
    case MULTIPLY: op = std::make_shared<Multiply>(); break;
    case DIVIDE:   op = std::make_shared<Divide>();   break;
    default:       op = nullptr;                      break;
  }
  return op;
}



} // namespace Binary


#endif // BINARY_DEFS_HPP
