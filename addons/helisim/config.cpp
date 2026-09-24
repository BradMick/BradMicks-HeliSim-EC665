class CfgPatches
{
    class bmkhs_ec665_helisim
    {
        units[] = {};
        author = "BradMick";
        weapons[] = {};
        requiredVersion = 2.10;
        //HeliSim Core, and BW-Mod's Tiger - this pack modifies its class, so it must load after it.
        requiredAddons[] = {"bmkhs_helisim", "bwa3_tiger"};
        //The airframe this pack drives. Every Tiger variant inherits from it.
        bmkhsBaseClass   = "BWA3_Tiger_base";
        #include "version.hpp"
    };
};

#include "CfgFunctions.hpp"
#include "config\CfgEventHandlers.hpp"
#include "config\cfgVehicles.hpp"
