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
#include "src/holdem/deck.h"

namespace py = pybind11;

int add(int i, int j) {
    return i + j;
}

PYBIND11_MODULE(holdEm, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("add", &add, "A function which adds two numbers");

    py::class_<hand>(m, "hand")
      .def(py::init<>())
      .def("pSetCards",     &hand::pSetCards)
      .def("pSetCardsFull", &hand::pSetCardsFull)
      .def("findBestHand",  &hand::findBestHand)
      .def("getCardsFace",  &hand::getCardsFace)
      .def("getCardsSuit",  &hand::getCardsSuit)
      .def("getBestFace",   &hand::getBestFace)
      .def("getBestSuit",   &hand::getBestSuit)
      .def("getHandCode",   &hand::getHandCode);

    py::class_<deck>(m, "deck")
      .def(py::init<>())
      .def("setDeckFull",    &deck::setDeckFull)
      .def("setDeckPartial", &deck::setDeckPartial)
      .def("setDeckIndex",   &deck::setDeckIndex)
      .def("remCards",       &deck::remCards)
      .def("shuffleI",       &deck::shuffleI)
      .def("dealCards",      &deck::dealCards)
      .def("getDeckSet",     &deck::getDeckSet)
      .def("getDeckFace",    &deck::getDeckFace)
      .def("getDeckSuit",    &deck::getDeckSuit)
      .def("getDeckIndex",   &deck::getDeckIndex)
      .def("getNumCards",    &deck::getNumCards)
      .def("getDealFace",    &deck::getDealFace)
      .def("getDealSuit",    &deck::getDealSuit);

}  


