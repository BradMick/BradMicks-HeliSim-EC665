/////////////////////////////////////////////////////////////////////////////////////////////
// Fuel //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//PLACEHOLDER: the AH-64D's two main cells - capacities, arms and low-fuel thresholds. The
//AH-64D's centre (IAFS) cell and wing aux tanks are left out; the Tiger has neither.
//TODO(EC665): Tiger tank layout, capacities and arms in model space.

/////////////////////////////////////////////////////////////////////////////////////////////
// Fuel tanks ///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  variableName - the aircraft names its own tank variables. Core prefixes bmkhs_ and appends
//              the field: "fwdTank" publishes bmkhs_fwdTankMass, bmkhs_fwdTankMax,
//              bmkhs_fwdTankLow. Names must be unique. Do not include the bmkhs_ prefix.
//  arm[]     - {lateral, longitudinal, vertical} in m, right-positive / nose-positive
//  capacity  - kg of usable fuel
//  lowFuelKg - low-level caution threshold in kg; 0 for no caution on this tank
//  removable - 1 if the tank can be taken out; 0 is always fitted
//  role      - "main" (an engine can draw from it) or "xfer" (feeds the mains only)

    //CROSSFEED positions - which main each engine feeds from in each valve position, by
    //position among the "main" tanks. The first entry is the default.
    numCrossfeedModes = 3;
    class CrossfeedModes {
        class Norm { position = "NORM"; engSources[] = {0, 1}; };
        class Fwd  { position = "FWD";  engSources[] = {0, 0}; };
        class Aft  { position = "AFT";  engSources[] = {1, 1}; };
    };

    //Which main tank the APU draws from. Unused with no APU modelled, but Core reads it.
    apuFuelSource = 1;

    //XFER pump destinations, in main order.
    xferDestinations[] = {"FWD", "AFT"};

    numFuelTanks = 2;
    class FuelTanks {
        class FuelTank01 {
            variableName = "fwdTank";
            arm[]     = {0.000, 2.542, 0.000};
            capacity  = 473.1;
            lowFuelKg = 109.0;
            removable = 0;
            role      = "main";
        };
        class FuelTank02 {
            variableName = "aftTank";
            arm[]     = {0.000, -0.077, 0.000};
            capacity  = 668.6;
            lowFuelKg = 118.0;
            removable = 0;
            role      = "main";
        };
    };

    numAuxTanks = 0;
