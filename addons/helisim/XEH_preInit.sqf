//This pack's airframe, from its own CfgPatches entry. Every installed pack schedules only its
//own aircraft, so this pack and any other loaded alongside it never touch each other's.
bmkhs_ec665_helisim_baseClass = getText (configFile >> "CfgPatches" >> "bmkhs_ec665_helisim" >> "bmkhsBaseClass");

//No event handler is registered: with no systems modelled there are no cockpit controls
//or lights for Core's events to drive, so they are ignored for this aircraft. Register one
//with bmkhs_fnc_utilNotifyRegister when there is something to animate or play.

//Every LOCAL Tiger, not just the one the player is sitting in - an AI Tiger flies the same
//model as a crewed one.
bmkhs_ec665_helisim_frameHandler = addMissionEventHandler ["EachFrame", {
    {
        if (alive _x && {_x getVariable ["bmkhs_initialised", false]}) then {
            [_x] call bmkhs_ec665_helisim_fnc_perFrame;
        };
    } forEach (vehicles select {local _x && {_x isKindOf bmkhs_ec665_helisim_baseClass}});
}];
