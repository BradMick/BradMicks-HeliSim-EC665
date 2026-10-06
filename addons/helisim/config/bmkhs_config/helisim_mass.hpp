/////////////////////////////////////////////////////////////////////////////////////////////
// Mass and Balance /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
    //Empty airframe. The Tiger declares no EmptyMassVariants - no fitted equipment changes it.
    emptyMass         = 3060; //kg
    emptyMom          = 21626.550;

    //Maximum gross mass - bounds the fixed test weight
    maxGrossMass      = 6000; //kg

    //Fuselage station datum and CG limits
    fsDatum             = 8.595;      //m, station 0 reference
    fwdCgLimit          = 1.615;    //m
    aftCgLimit          = 1.440;    //m
    comCorrection[]     = {0.0, 0.0, 0.224};
    //Casual mode center of mass
    casualModeCom[]     = {0.0, 1.56, 1.225};

/////////////////////////////////////////////////////////////////////////////////////////////
// Indexed mass items ///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
    //Every mass item is {arm, mass}: arm[] is {lateral, longitudinal, vertical} in metres,
    //right-positive / nose-positive, in the same surveyed frame as fsDatum.

    //SEATS. Occupancy is resolved against fullCrew, so an empty seat adds no mass.
    //  role       - "driver" | "gunner" | "commander" | "turret" | "cargo"
    //  turret[]   - turret path for gunner/commander/turret seats; {} for the driver
    //  cargoIndex - cargo slot for role = "cargo"; -1 otherwise
    numSeats = 2;
    class Seats {
        class Seat01 {  //gunner
            arm[]      = {0.000, 4.145, 0.000};
            mass       = 100.0;
            role       = "gunner";
            turret[]   = {0};
            cargoIndex = -1;
        };
        class Seat02 {  //pilot
            arm[]      = {0.000, 2.695, 0.000};
            mass       = 100.0;
            role       = "driver";
            turret[]   = {};
            cargoIndex = -1;
        };
    };

    //WING STATIONS. The Tiger carries one store per station, so each station is one pylon.
    //Indices are 1-BASED and follow the pylon declaration order:
    //  1 PylonLeft1 (outer left)   2 PylonLeft2 (inner left)
    //  3 PylonRight2 (inner right) 4 PylonRight1 (outer right)
    numStations = 4;
    class Stations {
        class Station01 { arm[] = {-2.335, 1.670,-0.440}; pylons[] = {1}; };
        class Station02 { arm[] = {-1.475, 1.670,-0.230}; pylons[] = {2}; };
        class Station03 { arm[] = { 1.475, 1.670,-0.230}; pylons[] = {3}; };
        class Station04 { arm[] = { 2.335, 1.670,-0.440}; pylons[] = {4}; };
    };

    //INTERNAL MAGAZINES. The Tiger's guns are pod-mounted on a station, so none here.
    numMagazines = 0;

/////////////////////////////////////////////////////////////////////////////////////////////
// Store masses /////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
    //Matched against the pylon magazine class names (case does not matter).
    //  launcherMass - kg of the launcher/pod itself, counted once per station
    //  massPerRound - kg per remaining round
    //  isTank       - 1 for a fuel tank; the Tiger carries none here
    numStores = 4;
    class Stores {
        class Store01 {  //Pylonweapon_4Rnd_PARS
            match        = "pars";
            launcherMass = 54.00;
            massPerRound = 49.00;
            isTank       = 0;
        };
        class Store02 {  //Pylonweapon_19Rnd_FZRockets
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
            launcherMass = 25.00;
            massPerRound = 10.10;
            isTank       = 0;
        };
    };
