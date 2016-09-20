#ifndef REDUCE_DEFS_HPP
#define REDUCE_DEFS_HPP

#include <memory>

namespace Reduce {

enum TYPE {
  MIN,
  MAX,
  SUM,
  UNDEFINED
};

inline std::string typeToString( TYPE type ) {
  std::string typeString;
  switch(type) {
    case MIN: typeString = "min";       break;
    case MAX: typeString = "max";       break;
    case SUM: typeString = "sum";       break;
    default:  typeString = "undefined"; break;
  }
  return typeString;
}


inline TYPE stringToType( const std::string& s ) {
  TYPE t;
  for( int i=MIN; i<UNDEFINED; ++i ) {
    t = static_cast<TYPE>(i);
    if( !s.compare(typeToString(t)) ) {
      return t;
    }
  }
  return UNDEFINED;
}

inline std::shared_ptr<Operation> getOperation( const std::string& s ) {
  
  TYPE t = stringToType(s);
  std::shared_ptr<Operation> op;

  switch(t) {
    case MIN: op = std::make_shared<Min>();  break;
    case MAX: op = std::make_shared<Max>();  break;
    case SUM: op = std::make_shared<Sum>();  break;
    default: op = nullptr;                   break;
  }
  return op;
}



} // namespace Reduce

#endif // REDUCE_DEFS_HPP
