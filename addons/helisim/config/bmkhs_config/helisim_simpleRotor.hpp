/////////////////////////////////////////////////////////////////////////////////////////////
// Rotors - Simple //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//A rotor is a hub at a position turning blades of a given size, so its geometry, its blade
//and what it does with the controls are defined together here. Core reads numSimpleRotors
//and loops; nothing downstream indexes by rotor NUMBER.
//
//The simple model works four fixed blade positions and scales by blade count, so the lift
//and drag tables carry what the rotor does rather than deriving it per blade element.
//
//  type         - "main" or "tail". What the rotor IS, so Core never assumes rotor 0 is
//                 the main one.
//  direction    - "ccw" or "cw", seen from above.
//  numBlades    - the four modelled positions are scaled to this.
//  pivot[]      - hub position, {lateral, longitudinal, vertical} in m,
//                 right-positive / nose-positive / up-positive
//  rotation[]   - disc orientation, {pitch, roll, yaw} in deg
//  mastLength   - m along the disc's own up axis, from pivot to hub
//  gearRatio    - rotor to engine shaft; shared with the transmission model
//  torqueTau    - s, torque filter time constant
//
//  BLADE
//  bladeRadius  - m
//  bladeChord   - m
//  bladeMass    - kg, one blade
//
//  DISC TILT - min / mid / max in deg, interpolated from the centred stick. A rotor whose
//  disc does not tilt declares zeroes.
//
//  coneAngle    - deg at full collective. Coning lifts the tips, so the thrust position
//                 moves inboard and the disc carries a vertical arm.
//  flapBackRollMax / flapBackPitchMax - deg at an advance ratio of 1.0. The advancing blade
//                 lifts more than the retreating one, so the disc tilts as speed builds.
//                 Applied as blade flap, which moves both the thrust position and its
//                 direction - it is NOT also applied to the lift coefficient.
//  rollLiftCoef / pitchLiftCoef - the cyclic lift coefficient, independent of the
//                 collective's. This is what makes the fore/aft and left/right blades carry
//                 different lift, so the pitch and roll moments come out of real forces at
//                 real positions rather than being applied as a torque.
//  gndEffValue  - thrust multiplier on the deck, fading to 1.0 by one rotor diameter up.
//                 A rotor that does not sit in ground effect declares 1.0.
//  reacTqScalar - scales the tangential blade drag that produces the yaw reaction. The same
//                 drag drives the transmission, which this does not touch.
//
//  liftCoefTable / dragCoefTable - rows are the control axis that loads this rotor
//  (collective for a main, pedal for a tail), columns are the airspeeds in the header row,
//  m/s. The drag table carries induced and profile together, and its airspeed columns carry
//  how they vary with speed - that is what the transmission feels.

    numSimpleRotors = 2;
    //Rotor limits, Nr - {normal low, normal high, high rotor, maximum}; below and above normal is transient.
    nrLimits[] = {0.937, 1.060, 1.079, 1.102};
    class SimpleRotors {
        class SimpleRotor01 {
            type             = "main";
            direction        = "cw";
            numBlades        = 4;
            pivot[]          = {0.00, 1.56, 1.27};
            rotation[]       = {0.00, 0.00, 0.00};
            mastLength       = 0.66;      //m
            gearRatio        = 25.397;
            torqueTau        = 0.10;      //s

            bladeRadius      = 6.500;     //m
            bladeChord       = 0.450;     //m
            bladeMass        = 72.108;    //kg

            pitchFlapMin     = -10.0;     //deg
            pitchFlapMid     =   0.0;
            pitchFlapMax     =  20.0;
            rollFlapMin      = -10.5;
            rollFlapMid      =   0.0;
            rollFlapMax      =   7.0;

            coneAngle        = 12.0;  //deg at full collective
            flapBackRollMax  = 15.0;  //deg per unit advance ratio
            flapBackPitchMax =  9.0;  //deg per unit advance ratio
            rollLiftCoef     = 0.19;
            pitchLiftCoef    = 0.72;
            gndEffValue      = 1.225;
            reacTqScalar     = 0.50;
            autoTorque       = 80.0;

            //------------Coll----0.00---10.29---20.58---36.01---46.30---51.44---61.73---66.88---72.02
            liftCoefTable[] = {
                        {"A/S", 0.00,   10.29,  20.58,  36.01,  46.30,  51.44,  61.73,  66.88,  72.02}
                        ,{0.00, 0.1000, 0.1000, 0.1000, 0.1000, 0.1000, 0.1000, 0.1000, 0.1000, 0.1000}
                        ,{0.20, 0.1543, 0.1577, 0.1716, 0.1865, 0.1897, 0.1902, 0.1918, 0.1882, 0.1716}
                        ,{0.40, 0.2086, 0.2154, 0.2431, 0.2731, 0.2794, 0.2803, 0.2837, 0.2763, 0.2433}
                        ,{0.64, 0.2629, 0.2731, 0.3147, 0.3596, 0.3691, 0.3705, 0.3755, 0.3645, 0.3149}
                        ,{0.80, 0.4855, 0.5496, 0.6451, 0.7709, 0.8343, 0.8627, 0.9216, 0.9376, 0.9149}
                        ,{1.00, 0.5155, 0.5796, 0.6751, 0.8009, 0.8643, 0.8927, 0.9516, 0.9676, 0.9449}
                        };
            //------------Coll----0.00---10.29---20.58---36.01---46.30---51.44---61.73---66.88---72.02
            dragCoefTable[] = {
                        {"A/S", 0.00,   10.29,  20.58,  36.01,  46.30,  51.44,  61.73,  66.88,  72.02}
                        ,{0.00, 0.0078, 0.0078, 0.0060, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005}
                        ,{0.20, 0.0190, 0.0181, 0.0160, 0.0149, 0.0160, 0.0160, 0.0154, 0.0144, 0.0144}
                        ,{0.40, 0.0301, 0.0285, 0.0259, 0.0293, 0.0315, 0.0315, 0.0303, 0.0283, 0.0284}
                        ,{0.64, 0.0413, 0.0388, 0.0359, 0.0436, 0.0471, 0.0470, 0.0451, 0.0423, 0.0423}
                        ,{0.80, 0.0918, 0.0880, 0.0839, 0.0898, 0.0921, 0.0914, 0.0883, 0.0849, 0.0843}
                        ,{1.00, 0.1550, 0.1550, 0.1550, 0.1550, 0.1550, 0.1550, 0.1550, 0.1550, 0.1550}
                        };
        };

        class SimpleRotor02 {
            type             = "tail";
            direction        = "cw";
            numBlades        = 3;
            pivot[]          = {0.00, -6.577, 1.225};
            rotation[]       = {0.00, -90.00,  0.000};
            mastLength       = -0.56;     //m
            gearRatio        = 5.277;
            torqueTau        = 0.10;      //s

            bladeRadius      = 1.350;     //m
            bladeChord       = 0.180;     //m
            bladeMass        = 5.131;     //kg

            //The tail disc does not tilt - pedal changes its pitch, not its plane.
            pitchFlapMin     = 0.0;
            pitchFlapMid     = 0.0;
            pitchFlapMax     = 0.0;
            rollFlapMin      = 0.0;
            rollFlapMid      = 0.0;
            rollFlapMax      = 0.0;

            coneAngle        = 0.0;
            flapBackRollMax  = 0.0;
            flapBackPitchMax = 0.0;
            rollLiftCoef     = 0.0;
            pitchLiftCoef    = 0.0;
            gndEffValue      = 1.0;
            reacTqScalar     = 0.25;
            autoTorque       = 0.0;

            //Pedal through controlMap is the table key: the map is the feel (the H-60's), the
            //three rows are left / mid / right. Lift is the old full-throw rows x0.65, which puts
            //the yaw moment per pedal at the hover with the AH-64D and H-60, then x0.8 from flight
            //test. The main rotor turns
            //clockwise, so right pedal carries the torque and the drag rises to the right.
            controlMap[] = {
                {-1.00, -1.0000},
                {-0.75, -0.8875},
                {-0.50, -0.6250},
                {-0.25, -0.2700},
                { 0.00,  0.0000},
                { 0.25,  0.3900},
                { 0.50,  0.7000},
                { 0.75,  0.8900},
                { 1.00,  1.0000}
            };
            //-----------Pedal----0.00---10.29---20.58---36.01---46.30---51.44---61.73---66.88---72.02
            liftCoefTable[] = {
                         {"A/S", 0.00,  10.29,  20.58,  36.01,  46.30,  51.44,  61.73,  66.88,  72.02}
                        ,{-1.00,-2.3297,-2.5606,-2.7641,-3.0326,-3.1932,-3.2692,-3.4142,-3.4831,-3.5499}
                        ,{ 0.00, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000}
                        ,{ 1.00, 2.3297, 2.5606, 2.7641, 3.0326, 3.1932, 3.2692, 3.4142, 3.4831, 3.5499}
                        };
            //-----------Pedal----0.00---10.29---20.58---36.01---46.30---51.44---61.73---66.88---72.02
            dragCoefTable[] = {
                         {"A/S", 0.00,  10.29,  20.58,  36.01,  46.30,  51.44,  61.73,  66.88,  72.02}
                        ,{-1.00, 0.0084, 0.0084, 0.0084, 0.0084, 0.0084, 0.0084, 0.0084, 0.0084, 0.0084}
                        ,{ 0.00, 0.0273, 0.0273, 0.0273, 0.0273, 0.0273, 0.0273, 0.0273, 0.0273, 0.0273}
                        ,{ 1.00, 0.2519, 0.2519, 0.2519, 0.2519, 0.2519, 0.2519, 0.2519, 0.2519, 0.2519}
                        };
        };
    };
