#ifndef REDUCE_HPP
#define REDUCE_HPP

#include <limits>

namespace Reduce {

class Operation {
public:
  virtual void reduce( const double& input, double& output ) const = 0;
  virtual double initialValue() const = 0 ;

}; // Operation

class Min : public Operation {
public:
  void reduce( const double& input, double& output ) const {
    output = (input<output) ? input : output;
  }

  double initialValue() const {
    return std::numeric_limits<double>::max();  
  }

}; // Min


class Max : public Operation {
public:
  void reduce( const double& input, double& output ) const {
    output = (input>output) ? input : output;
  }

  double initialValue() const {
    return std::numeric_limits<double>::max();  
  }

}; // Max


class Sum : public Operation {
public:
  void reduce( const double& input, double& output ) const {
    output = output + input;
  }

  double initialValue() const {
    return 0.0;  
  }

}; // Sum





} // namespace Reduce


#endif // REDUCE_HPP
