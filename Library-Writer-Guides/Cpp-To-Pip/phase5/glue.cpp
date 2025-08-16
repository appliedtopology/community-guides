#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/numpy.h>

#include "union-find.hpp"

namespace py = pybind11;

// wrapper functions that handle python type casting

std::vector<node> py_make_nodes(const py::array_t<double>& coords) {
  if(coords.ndim() != 2)
    throw std::runtime_error("Must be a 2d numpy array");
  if(coords.shape()[1] != 2)
    throw std::runtime_error("Must have shape (N,2)");
  
  std::vector<std::array<float,2> > points(coords.size());
  std::memcpy(points.data(), coords.data(), coords.size()*sizeof(double));
  return make_nodes(points, coords.shape()[0]);
}

std::vector<std::vector<float> > py_make_distances(const py::array_t<double>& coords) {
  if(coords.ndim() != 2)
    throw std::runtime_error("Must be a 2d numpy array");
  if(coords.shape()[1] != 2)
    throw std::runtime_error("Must have shape (N,2)");
  
  std::vector<std::array<float,2> > points(coords.size());
  std::memcpy(points.data(), coords.data(), coords.size()*sizeof(double));
  return make_distances(points, coords.shape()[0]);
}


PYBIND11_MODULE(unionfind, m) {
  m.doc() = "Example glue code to build PyBind11 Python Bindings out of existing research code.";

  m.def("find", &find, "The Find step - traverse parent pointer links until you find the root.");
  m.def("unite", &unite, "The Union step - splice one union-find-tree onto another one, fusing the corresponding sets.");
  m.def("make_nodes", &py_make_nodes, "Initiate node objects to represent all entries in a point cloud.");
  m.def("make_distances", &py_make_distances, "Compute all pairwise distances, naively.");
  m.def("sorted_edges", &sorted_edges, "Returns edges sorted by edge length according to the naive distance function.");
  m.def("find_deaths_criticals", &find_deaths_criticals, "Construct the union-find tree and compute persistent H0 death times and H1 birth times.");
  py::class_<node>(m, "node")
    .def_readwrite("dataindex", &node::dataindex)
    .def_readwrite("parent", &node::parent);
}
