#ifndef UNARY_HPP
#define UNARY_HPP

// Unary operations on scalars

#include <cmath>

namespace Unary {

class Operation {

public:
  virtual double apply(const double& value) const = 0; 

}; // Operation


class Fill :  public Operation {
private:
  double x;
public:
  Fill(const double& x_) : x(x_) {}
  
  double apply(const double& value) const { 
    return x;
  }
}; // Fill 


class Scale : public Operation {
private:
  double x;
public:
  Scale(const double& x_) : x(x_) {}

  double apply(const double& value) const {
    return value*x;     
  }
}; // Scale

class Shift : public Operation {
private:
  double x;
public:
  Shift(const double& x_) : x(x_) {}

  double apply(const double& value) const {
    return value+x;
  } 
}; // Shift

class Power : public Operation {
private:
  double x;
public:
  Power(const double& x_) : x(x_) {}

  double apply(const double& value) const {
    return std::pow(value,x);
  }  
}; // Power

class Exponential : public Operation {
public:
  double apply(const double& value) const {
    return std::exp(value);
  }
}; // Exponential

class Logarithm : public Operation {
public:
  double apply(const double& value) const {
    return std::log(value);
  }

}; // Logarithm


} // namespace Unary







#endif // UNARY_HPP

