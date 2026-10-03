#include "\bmkhs_helisim\fmOverride.hpp"

class CfgVehicles {
    class Helicopter_Base_F;
    //The base Tiger, reopened with its own parent so its config is extended, not replaced.
    //Everything else about the aircraft - model, crew, weapons, fuel capacity - stays as it is.
    class BWA3_Tiger_base : Helicopter_Base_F {
        //Core owns the force coefficients - packs cannot tune them
        BMKHS_FM_OVERRIDE

        #include "bmkhs_ec665_config.hpp"
    };
};
