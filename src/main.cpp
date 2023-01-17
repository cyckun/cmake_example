#include <pybind11/pybind11.h>
#include "PSI/include/psitest.h"
#include <iostream>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

int add(int i, int j) {
    return i + j;
}

int psi_sender(int x, int y) {
    int res = 0;
    res = 2*x + y;
    return res;
}

int psi(int x, int y) {
    std::cout << "psi api." << std::endl;
    auto res = psi_sender(x, y);
    return res;
}

namespace py = pybind11;


PYBIND11_MODULE(cmake_example, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: cmake_example

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

    m.def("add", &add, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc");

    m.def("psi", &psi, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc");
    m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers

        Some other explanation about the subtract function.
    )pbdoc");

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
