#ifndef UNARY_DEFS_HPP
#define UNARY_DEFS_HPP

#include <memory>
#include <string>

namespace Unary {

enum TYPE {
  FILL,
  SCALE,
  SHIFT,
  POW,
  EXP,
  LOG,
  UNDEFINED
}; 

inline std::string typeToString( TYPE type ) {
  std::string typeString;
  switch(type) {
    case FILL:     typeString = "fill";      break;
    case SCALE:    typeString = "scale";     break;
    case SHIFT:    typeString = "shift";     break;
    case POW:      typeString = "pow";       break;
    case EXP:      typeString = "exp";       break;
    case LOG:      typeString = "log";       break;
    default:       typeString = "undefined"; break;
  }
  return typeString;
}

inline TYPE stringToType( const std::string& s ) {
  TYPE t;
  for( int i=FILL; i<UNDEFINED; ++i ) {
    t = static_cast<TYPE>(i);
    if( !s.compare(typeToString(t)) ) {
      return t;
    }
  }
  return UNDEFINED;
}

inline std::shared_ptr<Operation> getOperation( const std::string& s,
                                                double param=0.0 ) {
  TYPE t = stringToType(s);
  std::shared_ptr<Operation> op;

  switch(t) {
    case FILL:  op = std::make_shared<Fill>(param);   break;
    case SCALE: op = std::make_shared<Scale>(param);  break;
    case SHIFT: op = std::make_shared<Shift>(param);  break;
    case POW:   op = std::make_shared<Power>(param);  break;
    case EXP:   op = std::make_shared<Exponential>(); break;
    case LOG:   op = std::make_shared<Logarithm>();   break;
    default:    op = nullptr;                         break;

  }

  return op;
}

} // unary

#endif // UNARY_DEFS_HPP
