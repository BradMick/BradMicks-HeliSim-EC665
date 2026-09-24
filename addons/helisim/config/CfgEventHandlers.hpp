class Extended_PreInit_EventHandlers {
    class bmkhs_ec665_helisim_preInit {
        init = "call compile preprocessFileLineNumbers 'bmkhs_ec665_helisim\XEH_preInit.sqf';";
    };
};

//The pack starts itself. Nothing outside it calls in.
class Extended_Init_EventHandlers {
    class BWA3_Tiger_base {
        class bmkhs_ec665_helisim_init_eh {
            init = "_this call bmkhs_ec665_helisim_fnc_setup";
        };
    };
};

class Extended_GetIn_EventHandlers {
    class BWA3_Tiger_base {
        class bmkhs_ec665_helisim_getin_eh {
            getIn = "_this call bmkhs_fnc_eventGetIn";
        };
    };
};
