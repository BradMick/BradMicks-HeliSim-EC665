/* ----------------------------------------------------------------------------
Function: bmkhs_ec665_helisim_fnc_perFrame

Description:
    Per-frame tick. The pack owns the schedule; Core only crunches numbers.

Parameters:
    _heli - The helicopter [Object]

Returns:
    Nothing
---------------------------------------------------------------------------- */
params ["_heli"];

//coreUpdate computes this frame's delta, so it goes first.
[_heli] call bmkhs_fnc_coreUpdate;
//With useSystems = 0 the solve does nothing, but the drivetrain torque limits still run here.
[_heli] call bmkhs_fnc_systemsUpdate;
[_heli] call bmkhs_fnc_coreUpdateFlightModel;

//The control input visualiser, which reads what the above just published.
[_heli] call bmkhs_fnc_ctrlVisUpdate;

//Restores the state that goes with a repair. Exits immediately unless one was flagged.
[_heli] call bmkhs_fnc_repair;
