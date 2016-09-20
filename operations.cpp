#include <exception>
#include "operations.hpp"

#include  <iostream>


PyObject* applyUnary(PyObject* self, PyObject* args) {

  // Get number of input arguments
  Py_ssize_t narg = PyTuple_Size(args);

  PyObject*      pyX;       
  PyArrayObject* pyArrayX;
  char*          str; 
  double         param = 0.0;

  double         *xdata;

  import_array();

  if( narg == 3 ) { // A double-valued parameter is being supplied
    if( !PyArg_ParseTuple(args,"Osd",&pyX,&str,&param) ) {
      return NULL;
    }
  }
  else if( narg == 2 ) { // no extra parameter given
    if( !PyArg_ParseTuple(args,"Os",&pyX,&str) ) { 
     return NULL;
    }
  }
  else { // Unsupported number of arguments 
    throw std::logic_error("Usage must conform to applyUnary(string,double) or applyUnary(string)");
  }
  pyArrayX = (PyArrayObject*)PyArray_FROM_OTF(pyX,NPY_DOUBLE,NPY_ARRAY_C_CONTIGUOUS);


  if( pyArrayX == NULL ) return NULL;

  std::shared_ptr<Unary::Operation> op = Unary::getOperation(str,param);

  int xsize = PyArray_SIZE(pyArrayX);

  xdata = static_cast<double*>(PyArray_DATA(pyArrayX));

  #pragma omp parallel for 
    for(npy_intp i=0;i<xsize;++i) { 
      xdata[i] = op->apply(xdata[i]);
  }

  return Py_None;
}



PyObject* applyBinary(PyObject* self, PyObject* args) {

  PyObject* pyX;  
  PyObject* pyY; 

  PyArrayObject* pyArrayX;
  PyArrayObject* pyArrayY;

  char   *str;
  double *xdata;
  double *ydata;

  import_array();

  if( !PyArg_ParseTuple(args,"OOs",&pyX,&pyY,&str) ) {
    return NULL;
  }
  
  pyArrayX = (PyArrayObject*)PyArray_FROM_OTF(pyX,NPY_DOUBLE,NPY_ARRAY_C_CONTIGUOUS);
  pyArrayY = (PyArrayObject*)PyArray_FROM_OTF(pyY,NPY_DOUBLE,NPY_ARRAY_C_CONTIGUOUS);

  std::shared_ptr<Binary::Operation> op = Binary::getOperation(str);

  int xsize = PyArray_SIZE(pyArrayX);
  int ysize = PyArray_SIZE(pyArrayY);

  if( xsize != ysize ) {
    throw std::logic_error("Given NumPy arrays must have the same number of elements");
  }

  xdata = static_cast<double*>(PyArray_DATA(pyArrayX));
  ydata = static_cast<double*>(PyArray_DATA(pyArrayY));
 
  #pragma omp parallel for
  for(npy_intp i=0;i<xsize;++i) {
    xdata[i] = op->apply(xdata[i],ydata[i]);
  }

  return Py_None;
}



PyObject* reduce(PyObject* self, PyObject* args) {

  PyObject*      pyX;
  PyArrayObject* pyArrayX;

  char*   str;
  double* xdata; 
  double  result;

  PyObject* pyResult = nullptr;

  import_array();

  if( !PyArg_ParseTuple(args,"Os",&pyX,&str) ) return NULL;

  pyArrayX = (PyArrayObject*)PyArray_FROM_OTF(pyX,NPY_DOUBLE,NPY_ARRAY_C_CONTIGUOUS);

  std::shared_ptr<Reduce::Operation> op = Reduce::getOperation(str);

  int xsize = PyArray_SIZE(pyArrayX);

  xdata = static_cast<double*>(PyArray_DATA(pyArrayX));

  result = op->initialValue();
 
  Reduce::TYPE type = Reduce::stringToType(str);

  switch(type) {
    case Reduce::MIN:
    #pragma omp parallel for reduction(min:result)
    for(npy_intp i=0;i<xsize;++i) {
      op->reduce(xdata[i],result);
    }

    break;
    case Reduce::MAX:
    #pragma omp parallel for reduction(max:result)
    for(npy_intp i=0;i<xsize;++i) {
      op->reduce(xdata[i],result);
    }

    break;
    case Reduce::SUM:
    #pragma omp parallel for reduction(+:result)
    for(npy_intp i=0;i<xsize;++i) {
      op->reduce(xdata[i],result);
    }

    break;
    default:
    break;
  }

  pyResult = PyFloat_FromDouble(result);

  return pyResult;
}
