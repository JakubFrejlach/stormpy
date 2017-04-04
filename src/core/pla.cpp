#include "pla.h"
#include "src/helpers.h"

typedef storm::modelchecker::parametric::SparseDtmcParameterLifting<storm::models::sparse::Dtmc<storm::RationalFunction>, double> PLAChecker;
typedef storm::storage::ParameterRegion<storm::RationalFunction> Region;

// Thin wrappers
void specifyFormula(std::shared_ptr<PLAChecker>& checker, std::shared_ptr<const storm::logic::Formula> const& formula) {
    checker->specifyFormula(storm::modelchecker::CheckTask<storm::logic::Formula, storm::RationalFunction>(*formula, true));
}
storm::modelchecker::parametric::RegionCheckResult checkRegion(std::shared_ptr<PLAChecker>& checker, Region& region) {
    return checker->analyzeRegion(region, storm::modelchecker::parametric::RegionCheckResult::Unknown, true);
}

// Define python bindings
void define_pla(py::module& m) {
    
    // PLAChecker
    py::class_<PLAChecker, std::shared_ptr<PLAChecker>>(m, "PLAChecker", "Region model checker for sparse DTMCs")
        .def("__init__", [](PLAChecker& instance, std::shared_ptr<storm::models::sparse::Dtmc<storm::RationalFunction>> model) -> void {
                new (&instance) PLAChecker(*model);
            })
        //.def(py::init<storm::models::sparse::Dtmc<storm::RationalFunction>>)
        .def("specify_formula", &specifyFormula, "Specify formula", py::arg("formula"))
        .def("check_region", &checkRegion, "Check region", py::arg("region"))
    ;
    
    // Region
    py::class_<Region, std::shared_ptr<Region>>(m, "ParameterRegion", "Parameter region")
       .def("__init__", [](Region &instance, std::string const& regionString, std::set<Region::VariableType> const& variables) -> void {
                new (&instance) Region(Region::parseRegion(regionString, variables));
            })
        //.def(py::init<Region::VariableSubstitutionType &, Region::VariableSubstitutionType &>(), py::arg("lowerBounds"), py::arg("upperBounds"))
        //.def("result", &Region::getCheckResult, "Get check result")
    ;

    // RegionCheckResult 
    py::enum_<storm::modelchecker::parametric::RegionCheckResult>(m, "RegionCheckResult", "Types of region check results")
        .value("EXISTSSAT", storm::modelchecker::parametric::RegionCheckResult::ExistsSat)
        .value("EXISTSVIOLATED", storm::modelchecker::parametric::RegionCheckResult::ExistsViolated)
        .value("EXISTSBOTH", storm::modelchecker::parametric::RegionCheckResult::ExistsBoth)
        .value("CENTERSAT", storm::modelchecker::parametric::RegionCheckResult::CenterSat)
        .value("CENTERVIOLATED", storm::modelchecker::parametric::RegionCheckResult::CenterViolated)
        .value("ALLSAT", storm::modelchecker::parametric::RegionCheckResult::AllSat)
        .value("ALLVIOLATED", storm::modelchecker::parametric::RegionCheckResult::AllViolated)
        .value("UNKNOWN", storm::modelchecker::parametric::RegionCheckResult::Unknown)
        .def("__str__", &streamToString<storm::modelchecker::parametric::RegionCheckResult>)
    ;
}
