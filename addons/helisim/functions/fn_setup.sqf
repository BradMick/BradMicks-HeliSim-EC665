/* ----------------------------------------------------------------------------
Function: bmkhs_ec665_helisim_fnc_setup

Description:
    Initialises HeliSim Core for the Tiger and hands it this aircraft's
    configuration. Called once per aircraft at init.

Parameters:
    _heli - The helicopter [Object]

Returns:
    Nothing
---------------------------------------------------------------------------- */
params ["_heli"];

//Once per aircraft. The pack's own init EH is what fires this.
if (_heli getVariable ["bmkhs_initialised", false]) exitWith {};

[_heli] call bmkhs_fnc_coreInit;
[_heli, configOf _heli >> "BMKHS_HeliSim"] call bmkhs_fnc_coreConfig;
