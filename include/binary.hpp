#ifndef BINARY_HPP
#define BINARY_HPP

// Binary operations on scalars

#include <cmath>

namespace Binary {

class Operation {
public:
  virtual double apply(const double& x, const double& y) const = 0;
}; // Operation

class Multiply : public Operation {
public:
  double apply( const double& x, const double& y ) const {
    return x*y;
  }
}; // Multiply

class Divide : public Operation {
public:
  double apply( const double& x, const double& y ) const {
    return x/y;
  }
}; // Divide

class Add : public Operation {
public:
  double apply( const double& x, const double& y ) const {
    return x+y;
  }
}; // Add

class Subtract : public Operation {
public:
  double apply( const double& x, const double& y ) const {
    return x-y;
  }
}; // Subtract


} // namespace Binary

#endif // BINARY_HPP
