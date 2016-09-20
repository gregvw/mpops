#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include "Python.h"
#include "numpy/arrayobject.h"

#include "unary.hpp"
#include "unary_defs.hpp"

#include "binary.hpp"
#include "binary_defs.hpp"

#include "reduce.hpp"
#include "reduce_defs.hpp"


static PyObject* applyUnary( PyObject* self, PyObject* args );

static char applyUnary_doc[] = 
  "applyUnary(x,op,d) : Applies a parallel unary operation of the form x<-f(x),where "
  "where x is a NumPy array and f is a function determined by the string op. Some operations "
  "require an additional parameter d, which is expected to be of double type."
  "The array x is modified in place. Implemented values of op are: \n" 
  "    fill   - sets every element to d \n"
  "    scale  - multiplies every element to d\n"
  "    shift  - adds d to every element\n"
  "    pow    - raises every element to the power d\n"
  "    exp    - computes the exponential of every element\n"
  "    log    - computes the logarithm of evert element\n";


static PyObject* applyBinary( PyObject* self, PyObject* args );

static char applyBinary_doc[] = 
  "applyBinary(x,y,op) : Applies a parallel binary operation of the form x<-f(x,y), "
  "where x and y are NumPy arrays and f is a function that takes two arguments defined in by "
  "the string op. The array x is modified in place. Implemented values of op are:\n "
  "    add    - adds the array x to y, stores result in x\n"
  "    sub    - subtracts the array y from x, stores result in x\n"
  "    mult   - multiplies the array x by y elementwise, stores result in x\n"
  "    div    - divides the array x by y elementwise, stores the result in x\n";
 
 
static PyObject* reduce( PyObject* self, PyObject* args );

static char reduce_doc[] = 
  "reduce(x,op) : Performs a parallel reduction operation on the NumPy array x and returns "
  "a double where op is a string. Implemented values of op are min, max, and sum";

static PyMethodDef module_functions[] = {
  {"applyUnary",(PyCFunction)applyUnary,METH_VARARGS,applyUnary_doc},
  {"applyBinary",(PyCFunction)applyBinary,METH_VARARGS,applyBinary_doc},
  {"reduce",(PyCFunction)reduce,METH_VARARGS,reduce_doc},
  {NULL,NULL,0,NULL}
};


static struct PyModuleDef moduledef = {
  PyModuleDef_HEAD_INIT,
  "operations",
  "Elementwise operations of NumPy arrays",
  -1, 
  module_functions,
  NULL,
  NULL,
  NULL,
  NULL
};


PyMODINIT_FUNC
PyInit_operations(void) {
  return PyModule_Create(&moduledef);
}


#endif // OPERATIONS_HPP
