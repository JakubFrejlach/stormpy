import stormpy
import stormpy.logic
import math
from helpers.helper import get_example_path

from configurations import pars


@pars
class TestPLA:
    def test_pla(self):
        program = stormpy.parse_prism_program(get_example_path("pdtmc", "brp16_2.pm"))
        prop = "P<=0.84 [F s=5 ]"
        formulas = stormpy.parse_properties_for_prism_program(prop, program)
        model = stormpy.build_parametric_model(program, formulas)
        assert model.nr_states == 613
        assert model.nr_transitions == 803
        assert model.model_type == stormpy.ModelType.DTMC
        assert model.has_parameters
        env = stormpy.Environment()
        checker = stormpy.pars.create_region_checker(env, model, formulas[0].raw_formula)
        parameters = model.collect_probability_parameters()
        assert len(parameters) == 2
        region = stormpy.pars.ParameterRegion("0.7<=pL<=0.9,0.75<=pK<=0.95", parameters)
        result = checker.check_region(env, region)
        assert result == stormpy.pars.RegionResult.ALLSAT
        region = stormpy.pars.ParameterRegion("0.4<=pL<=0.65,0.75<=pK<=0.95", parameters)
        result = checker.check_region(env, region, stormpy.pars.RegionResultHypothesis.UNKNOWN,
                                      stormpy.pars.RegionResult.UNKNOWN, True)
        assert result == stormpy.pars.RegionResult.EXISTSBOTH
        region = stormpy.pars.ParameterRegion("0.1<=pL<=0.73,0.2<=pK<=0.715", parameters)
        result = checker.check_region(env, region)
        assert result == stormpy.pars.RegionResult.ALLVIOLATED

    def test_pla_bounds(self):
        program = stormpy.parse_prism_program(get_example_path("pdtmc", "brp16_2.pm"))
        prop = "P=? [F s=5 ]"
        formulas = stormpy.parse_properties_for_prism_program(prop, program)
        model = stormpy.build_parametric_model(program, formulas)
        assert model.has_parameters
        env = stormpy.Environment()
        checker = stormpy.pars.create_region_checker(env, model, formulas[0].raw_formula)
        parameters = model.collect_probability_parameters()
        assert len(parameters) == 2
        region = stormpy.pars.ParameterRegion("0.7<=pL<=0.9,0.75<=pK<=0.95", parameters)
        result = checker.get_bound(env, region, True)
        assert math.isclose(float(result.constant_part()), 0.8369631383670559)
        #result_vec = checker.get_bound_all_states(env, region, True)
        #result = result_vec.at(model.initial_states[0])
        #assert math.isclose(float(result.constant_part()), 0.8369631383670559)

    def test_pla_manual(self):
        program = stormpy.parse_prism_program(get_example_path("pdtmc", "brp16_2.pm"))
        prop = "P=? [F s=5 ]"
        formulas = stormpy.parse_properties_for_prism_program(prop, program)
        model = stormpy.build_parametric_model(program, formulas)
        assert model.has_parameters
        env = stormpy.Environment()
        checker = stormpy.pars.DtmcParameterLiftingModelChecker()
        checker.specify(env, model, formulas[0].raw_formula)
        parameters = model.collect_probability_parameters()
        assert len(parameters) == 2
        region = stormpy.pars.ParameterRegion("0.7<=pL<=0.9,0.75<=pK<=0.95", parameters)
        result = checker.get_bound(env, region, True)
        assert math.isclose(float(result.constant_part()), 0.8369631383670559)

    def test_pla_manual_no_simplification(self):
        program = stormpy.parse_prism_program(get_example_path("pdtmc", "brp16_2.pm"))
        prop = "P=? [F s=5 ]"
        formulas = stormpy.parse_properties_for_prism_program(prop, program)
        model = stormpy.build_parametric_model(program, formulas)
        assert model.has_parameters
        env = stormpy.Environment()
        checker = stormpy.pars.DtmcParameterLiftingModelChecker()
        checker.specify(env, model, formulas[0].raw_formula, allow_model_simplification=False)
        parameters = model.collect_probability_parameters()
        assert len(parameters) == 2
        region = stormpy.pars.ParameterRegion("0.7<=pL<=0.9,0.75<=pK<=0.95", parameters)
        result = checker.get_bound(env, region, True)
        assert math.isclose(float(result.constant_part()), 0.836963056082918)

    def test_pla_state_bounds(self):
        program = stormpy.parse_prism_program(get_example_path("pdtmc", "brp16_2.pm"))
        prop = "P=? [F s=5 ]"
        formulas = stormpy.parse_properties_for_prism_program(prop, program)
        model = stormpy.build_parametric_model(program, formulas)
        assert model.has_parameters
        env = stormpy.Environment()
        checker = stormpy.pars.DtmcParameterLiftingModelChecker()
        checker.specify(env, model, formulas[0].raw_formula, allow_model_simplification=False)
        parameters = model.collect_probability_parameters()
        assert len(parameters) == 2
        region = stormpy.pars.ParameterRegion("0.7<=pL<=0.9,0.75<=pK<=0.95", parameters)
        result_vec = checker.get_bound_all_states(env, region, True)
        assert len(result_vec.get_values()) == model.nr_states
        assert math.isclose(result_vec.at(model.initial_states[0]), 0.836963056082918)



