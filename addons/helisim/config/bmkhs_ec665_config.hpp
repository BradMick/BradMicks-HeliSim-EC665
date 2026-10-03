//EC665 Tiger HeliSim configuration. Core reads this class.

class BMKHS_HeliSim {
    //No systems modelled: no electrical, APU, hydraulics or drivetrain components, no
    //cockpit controls. The aircraft starts cold and wakes on the first collective input.
    useSystems = 0;

    //How many engines. No hitpoints are declared, so this is where the count comes from.
    numEngines = 2;

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
