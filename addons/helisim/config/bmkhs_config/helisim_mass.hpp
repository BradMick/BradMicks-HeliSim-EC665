/////////////////////////////////////////////////////////////////////////////////////////////
// Mass and Balance /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//PLACEHOLDER: the AH-64D's non-FCR empty mass, CG limits and datum.
//TODO(EC665): Tiger empty mass and moment, gross mass, datum and CG limits.

    //Core picks FCR or non-FCR by the AH-64's "fcr_enable" animation, which the Tiger does not
    //have - so it always takes the non-FCR pair. Both are declared the same so it cannot matter.
    emptyMassFCR      = 6314; //kg
    emptyMomFCR       = 32877.000;
    emptyMassNonFCR   = 6314; //kg
    emptyMomNonFCR    = 32877.000;

    //Maximum gross mass - bounds the fixed test weight
    maxGrossMass      = 10433; //kg

    //Fuselage station datum and CG limits
    fsDatum             = 6.4;      //m, station 0 reference
    fwdCgLimit          = 1.295;    //m
    aftCgLimit          = 1.142;    //m
    comCorrection[]     = {0.0, 0.0, 0.224};
    //Casual mode center of mass
    casualModeCom[]     = {0.0, 2.06, -0.075};

/////////////////////////////////////////////////////////////////////////////////////////////
// Indexed mass items ///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
    //Every mass item is {arm, mass}: arm[] is {lateral, longitudinal, vertical} in metres,
    //right-positive / nose-positive, in the same surveyed frame as fsDatum.

    //SEATS. Occupancy is resolved against fullCrew, so an empty seat adds no mass.
    //  role       - "driver" | "gunner" | "commander" | "turret" | "cargo"
    //  turret[]   - turret path for gunner/commander/turret seats; {} for the driver
    //  cargoIndex - cargo slot for role = "cargo"; -1 otherwise
    //PLACEHOLDER: AH-64D seat arms. TODO(EC665): the Tiger's pilot and gunner positions.
    numSeats = 2;
    class Seats {
        class Seat01 {  //gunner - BW-Mod's MainTurret
            arm[]      = {0.000, 4.312, 0.000};
            mass       = 100.0;
            role       = "gunner";
            turret[]   = {0};
            cargoIndex = -1;
        };
        class Seat02 {  //pilot
            arm[]      = {0.000, 2.760, 0.000};
            mass       = 100.0;
            role       = "driver";
            turret[]   = {};
            cargoIndex = -1;
        };
    };

    //WING STATIONS. The Tiger carries one store per station, so each station is one pylon.
    //Indices are 1-BASED and follow BW-Mod's pylon declaration order:
    //  1 PylonLeft1 (outer left)   2 PylonLeft2 (inner left)
    //  3 PylonRight2 (inner right) 4 PylonRight1 (outer right)
    //PLACEHOLDER: AH-64D station arms. TODO(EC665): the Tiger's stub-wing station positions.
    numStations = 4;
    class Stations {
        class Station01 { arm[] = {-2.160, 1.345, 0.000}; pylons[] = {1}; };
        class Station02 { arm[] = {-1.500, 1.345, 0.000}; pylons[] = {2}; };
        class Station03 { arm[] = { 1.500, 1.345, 0.000}; pylons[] = {3}; };
        class Station04 { arm[] = { 2.160, 1.345, 0.000}; pylons[] = {4}; };
    };

    //INTERNAL MAGAZINES. The Tiger's guns are pod-mounted on a station, so none here.
    numMagazines = 0;

/////////////////////////////////////////////////////////////////////////////////////////////
// Store masses /////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
    //Matched against BW-Mod's pylon magazine class names (case does not matter).
    //  launcherMass - kg of the launcher/pod itself, counted once per station
    //  massPerRound - kg per remaining round
    //  isTank       - 1 for a fuel tank; the Tiger carries none here
    //PLACEHOLDER masses - TODO(EC665): real launcher and round masses.
    numStores = 4;
    class Stores {
        class Store01 {  //Pylonweapon_4Rnd_PARS - AH-64D's M299 + Hellfire values stand in
            match        = "pars";
            launcherMass = 64.90;
            massPerRound = 46.71;
            isTank       = 0;
        };
        class Store02 {  //Pylonweapon_19Rnd_FZRockets - AH-64D's M261 + Hydra values stand in
            match        = "fzrockets";
            launcherMass = 39.40;
            massPerRound = 10.40;
            isTank       = 0;
        };
        class Store03 {  //Pylonweapon_400Rnd_127x99 - 12.7 mm gun pod, estimate
            match        = "127x99";
            launcherMass = 110.00;
            massPerRound = 0.12;
            isTank       = 0;
        };
        class Store04 {  //Pylonweapon_2Rnd_Fliegerfaust - Stinger pair, estimate
            match        = "fliegerfaust";
            launcherMass = 20.00;
            massPerRound = 10.00;
            isTank       = 0;
        };
    };
