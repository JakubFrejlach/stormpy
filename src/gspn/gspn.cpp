#include "gspn.h"
#include "src/helpers.h"
#include "storm-gspn/storage/gspn/GSPN.h"
#include "storm-gspn/storage/gspn/GspnBuilder.h"
#include "storm/settings/SettingsManager.h"


using GSPN = storm::gspn::GSPN;
using GSPNBuilder = storm::gspn::GspnBuilder;
using LayoutInfo = storm::gspn::LayoutInfo;


void define_gspn(py::module& m) {
    // LayoutInfo class
    py::class_<LayoutInfo>(m, "LayoutInfo")
            .def(py::init<>())
            .def(py::init<double, double, double>(), py::arg("x"), py::arg("y"), py::arg("rotation") = 0.0)  //todo add rotation predefined
            .def_readwrite("x", &LayoutInfo::x)
            .def_readwrite("y", &LayoutInfo::y)
            .def_readwrite("rotation", &LayoutInfo::rotation)
    ;

    // GSPN class
    py::class_<GSPN, std::shared_ptr<GSPN>>(m, "GSPN", "Generalized Stochastic Petri Net")
        .def("name", &GSPN::getName, "Name of GSPN")
        .def("set_name", &GSPN::setName, "Set name of GSPN")

        //todo constructor
        // .def(py::init<std::string const&, std::vector<Place>, ... >())

        // todo write tests:
        .def_static("timed_transition_id_to_transition_id", &GSPN::timedTransitionIdToTransitionId)
        .def_static("immediate_transition_id_to_transition_id", &GSPN::immediateTransitionIdToTransitionId)
        .def_static("transition_id_to_timed_transition_id", &GSPN::transitionIdToTimedTransitionId)
        .def_static("transition_id_to_immediate_transition_id", &GSPN::transitionIdToImmediateTransitionId)

        // getNumberOfPlaces, getNumberOfImmediateTransitions, getNumberOfTimedTransitions, ...

        //todo private?
    ;

    // GSPN_Builder class
    py::class_<GSPNBuilder, std::shared_ptr<GSPNBuilder>>(m, "GSPNBuilder", "Generalized Stochastic Petri Net Builder")
            .def(py::init(), "Constructor")
            .def("set_name", &GSPNBuilder::setGspnName, "Set name of GSPN", py::arg("name"))

            // todo: boost::optional<uint64_t> capacity
            //.def("add_place", &GSPNBuilder::addPlace, "Add a place to the GSPN", py::arg("capacity") = 1, py::arg("initialTokens") = 0, py::arg("name") = "")

            //.def("set_place_layout_info", &GSPNBuilder::setPlaceLayoutInfo, "Set place layout information", py::arg("placeId"), py::arg("layoutInfo"))

            .def("add_immediate_transition", &GSPNBuilder::addImmediateTransition, "Adds an immediate transition to the GSPN", py::arg("priority") = 0, py::arg("weight") = 0, py::arg("name") = "")

            // todo: boost::optional<uint64_t>
            .def("add_timed_transition", py::overload_cast<uint_fast64_t const&, double const& , std::string const&>(&GSPNBuilder::addTimedTransition), "Adds an timed transition to the GSPN", py::arg("priority"), py::arg("rate"), py::arg("name") = "")
            .def("add_timed_transition", py::overload_cast<uint_fast64_t const&, double const& , boost::optional<uint64_t>, std::string const&>(&GSPNBuilder::addTimedTransition), "Adds an timed transition to the GSPN", py::arg("priority"), py::arg("rate"), py::arg("numServers"), py::arg("name") = "")

            // todo add descriptions
            .def("add_input_arc", py::overload_cast<uint_fast64_t const&, uint_fast64_t const&, uint_fast64_t const&>(&GSPNBuilder::addInputArc), py::arg("from"),  py::arg("to"),  py::arg("multiplicity"))
            .def("add_input_arc", py::overload_cast<std::string const&, std::string const&, uint64_t>(&GSPNBuilder::addInputArc), py::arg("from"),  py::arg("to"),  py::arg("multiplicity"))
            .def("add_inhibition_arc", py::overload_cast<uint_fast64_t const&, uint_fast64_t const&, uint_fast64_t const&>(&GSPNBuilder::addInhibitionArc), py::arg("from"),  py::arg("to"),  py::arg("multiplicity"))
            .def("add_inhibition_arc", py::overload_cast<std::string const&, std::string const&, uint64_t>(&GSPNBuilder::addInhibitionArc), py::arg("from"),  py::arg("to"),  py::arg("multiplicity"))
            .def("add_output_arc", py::overload_cast<uint_fast64_t const&, uint_fast64_t const&, uint_fast64_t const&>(&GSPNBuilder::addOutputArc), py::arg("from"),  py::arg("to"),  py::arg("multiplicity"))
            .def("add_output_arc", py::overload_cast<std::string const&, std::string const&, uint64_t>(&GSPNBuilder::addOutputArc), py::arg("from"),  py::arg("to"),  py::arg("multiplicity"))

            // todo LayoutInfo
            //.def("set_transition_layout_info", &GSPNBuilder::setTransitionLayoutInfo, "set transition layout information", py::arg("transitionId"), py::arg("layoutInfo"))

            .def("add_normal_arc", &GSPNBuilder::addNormalArc, "Add normal arc from a named element to a named element", py::arg("from"), py::arg("to"), py::arg("multiplicity") = 1)

            .def("build_gspn", &GSPNBuilder::buildGspn, "Construct GSPN", py::arg("exprManager") = nullptr, py::arg("constantsSubstitution") = std::map<storm::expressions::Variable, storm::expressions::Expression>())



    ;
}
