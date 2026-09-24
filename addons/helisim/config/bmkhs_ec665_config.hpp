//EC665 Tiger HeliSim configuration. Core reads this class.
//
//PLACEHOLDER BASELINE: every file under bmkhs_config/ started as the AH-64D's values, so the
//Tiger flies from day one. Each file says what still has to become Tiger data.

class BMKHS_HeliSim {
    //No systems modelled: no electrical, APU, hydraulics or drivetrain components, no
    //cockpit controls. The aircraft starts cold and wakes on the first collective input.
    useSystems = 0;

    //Drivetrain ratings - with useSystems = 0 these are the ONLY torque limits, and an
    //overtorque damages the rotors (HitHRotor / HitVRotor). Worst first: {fraction of rated
    //torque, seconds it will hold there, divisor}.
    //PLACEHOLDER: AH-64D ratings.
    xmsnTqLimits[]   = {{2.30, 0, 20}, {2.00, 6, 10}};
    ngbTqLimitsSE[]  = {{1.25, 0, 40}, {1.22, 6, 20}, {1.10, 150, 10}};

    #include "bmkhs_config\helisim_airfoils.hpp"
    #include "bmkhs_config\helisim_engine.hpp"
    #include "bmkhs_config\helisim_flightControls.hpp"
    #include "bmkhs_config\helisim_fuel.hpp"
    #include "bmkhs_config\helisim_fuselage.hpp"
    #include "bmkhs_config\helisim_mass.hpp"
    #include "bmkhs_config\helisim_misc.hpp"
    #include "bmkhs_config\helisim_rotor.hpp"
    #include "bmkhs_config\helisim_simpleRotor.hpp"
    #include "bmkhs_config\helisim_wings.hpp"
};
