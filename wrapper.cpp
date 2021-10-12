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
#include "src/holdem/table.h"

namespace py = pybind11;

PYBIND11_MODULE(holdEm, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    py::class_<hand>(m, "hand")
      .def(py::init<>())
      .def("SetCards",      &hand::SetCards)
      .def("SetCardsFull",  &hand::SetCardsFull)
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

    py::class_<table>(m, "table")
      .def(py::init<int>())
      .def("setHoldCards",      &table::setHoldCards)
      .def("setHoldCard",       &table::setHoldCard)
      .def("setFlop",           &table::setFlop)
      .def("setTurn",           &table::setTurn)
      .def("setRiver",          &table::setRiver)
      .def("shuffleDeckIndex",  &table::shuffleDeckIndex)
      .def("dealFlopTurnRiver", &table::dealFlopTurnRiver)
      .def("dealHold",          &table::dealHold)
      .def("dealAll",           &table::dealAll)
      .def("dealAllP",          &table::dealAllP)
      .def("dealAllI",          &table::dealAllI)
      .def("findWinner",        &table::findWinner)
      .def("findWinnerP",       &table::findWinnerP)
      .def("findWinnerI",       &table::findWinnerI)
      .def("resetTableToKnown", &table::resetTableToKnown)
      .def("resetTable",        &table::resetTable)
      .def("MC",                &table::MC)
      .def("MCP",               &table::MCP)
      .def("getPlayerHoldFace", &table::getPlayerHoldFace)
      .def("getPlayerHoldSuit", &table::getPlayerHoldSuit)
      .def("getNumRuns",        &table::getNumRuns)
      .def("getWins",           &table::getWins)
      .def("getWinsP",          &table::getWinsP)
      .def("getDraws",          &table::getDraws)
      .def("getDrawsP",         &table::getDrawsP)
      .def("getWinsPP",         &table::getWinsPP)
      .def("getWinsPPp",        &table::getWinsPPp)
      .def("getDrawsPP",        &table::getDrawsPP)
      .def("getDrawsPPp",       &table::getDrawsPPp)
      .def("getHandsPP",        &table::getHandsPP)
      .def("getHandsPPp",       &table::getHandsPPp)
      .def("getNumCardsInDeck", &table::getNumCardsInDeck);


}  


