#include "synthesis.h"

#include "storm-synthesis/pomdp/PomdpManager.h"

// Define python bindings
void define_pomdp(py::module& m) {

    py::class_<storm::synthesis::PomdpManager<double>>(m, "PomdpManager", "POMDP manager")
        .def(py::init<storm::models::sparse::Pomdp<double> const&>(), "Constructor.", py::arg("pomdp"))
        .def("construct_mdp", &storm::synthesis::PomdpManager<double>::constructMdp, "Unfold memory model (a priori memory update) into the POMDP.")
        .def("construct_mdp_aposteriori", &storm::synthesis::PomdpManager<double>::constructMdpAposteriori, "Unfold memory model (a posteriori memory update) into the POMDP.")
        .def("set_observation_memory_size", &storm::synthesis::PomdpManager<double>::setObservationMemorySize, "Set memory size to a selected observation.", py::arg("observation"), py::arg("memory_size"))
        .def("set_global_memory_size", &storm::synthesis::PomdpManager<double>::setGlobalMemorySize, "Set memory size to all observations.", py::arg("memory_size"))
        .def_property_readonly("state_prototype", [](storm::synthesis::PomdpManager<double>& manager) {return manager.state_prototype;}, "TODO")
        .def_property_readonly("state_memory", [](storm::synthesis::PomdpManager<double>& manager) {return manager.state_memory;}, "TODO")
        .def_property_readonly("observation_memory_size", [](storm::synthesis::PomdpManager<double>& manager) {return manager.observation_memory_size;}, "TODO")
        .def_property_readonly("observation_actions", [](storm::synthesis::PomdpManager<double>& manager) {return manager.observation_actions;}, "TODO")
        .def_property_readonly("observation_successors", [](storm::synthesis::PomdpManager<double>& manager) {return manager.observation_successors;}, "TODO")
        .def_property_readonly("max_successor_memory_size", [](storm::synthesis::PomdpManager<double>& manager) {return manager.max_successor_memory_size;}, "TODO")
        .def_property_readonly("num_holes", [](storm::synthesis::PomdpManager<double>& manager) {return manager.num_holes;}, "TODO")
        .def_property_readonly("action_holes", [](storm::synthesis::PomdpManager<double>& manager) {return manager.action_holes;}, "TODO")
        .def_property_readonly("memory_holes", [](storm::synthesis::PomdpManager<double>& manager) {return manager.memory_holes;}, "TODO")
        .def_property_readonly("hole_options", [](storm::synthesis::PomdpManager<double>& manager) {return manager.hole_options;}, "TODO")
        .def_property_readonly("row_action_hole", [](storm::synthesis::PomdpManager<double>& manager) {return manager.row_action_hole;}, "TODO")
        .def_property_readonly("row_action_option", [](storm::synthesis::PomdpManager<double>& manager) {return manager.row_action_option;}, "TODO")
        .def_property_readonly("row_memory_hole", [](storm::synthesis::PomdpManager<double>& manager) {return manager.row_memory_hole;}, "TODO")
        .def_property_readonly("row_memory_option", [](storm::synthesis::PomdpManager<double>& manager) {return manager.row_memory_option;}, "TODO")
        ;
}
