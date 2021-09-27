  /*

g++ -O3 -Wall -shared -std=c++11 -undefined dynamic_lookup $(python3 -m pybind11 --includes) -fPIC $(python3 -m pybind11 --includes) python_wrapper.cpp -o holdEm$(python3-config --extension-suffix)


  NOTES :
      - The module name must be the same as the output file name or we get the error
        ``ImportError: dynamic module does not define module export function''
      - Pybind11 does not accept multi dimensional arrays as function inputs.
 */

// pybind11 wrapper for all routines
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

#include "src/holdem/hand.h"

namespace py = pybind11;

int add(int i, int j) {
    return i + j;
}

PYBIND11_MODULE(holdEm, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("add", &add, "A function which adds two numbers");

    py::class_<hand>(m, "hand")
      .def(py::init<>())
      .def("pSetCardsFull", &hand::pSetCardsFull)
      .def("getBestHand",  &hand::getBestHand);


    
      // .def("setCardsFull",
      // 	   [](std::array<int, 7> face_in, std::array<int, 7> suit_in)
      // 	   { return &hand::getBestHand(face_in.data(),suit_in.data()); })

  // static int best_face[5];
  // static int best_suit[5];  
  
    
}  


