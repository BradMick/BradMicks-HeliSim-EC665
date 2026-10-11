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
//  damageRole   - the hitpoint role that destroys this rotor. A rotor that declares none
//                 cannot be destroyed.
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
            damageRole       = "mainRotor";
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

            //Airfoil-style collective shape: lift rises in a straight line to its peak at 0.85, then
            //falls off; drag bends up through the hover points and climbs past the peak. Sea level,
            //15 C, OGE: 4,923 kg 0.597 / 66.9%, 6,000 kg 0.753 / 86.6%, 6,650 kg 0.85 / ~99% (lets
            //4,923 kg hover OGE at 8,000 ft, 15 C). Each airspeed column (one per standard power curve
            //point, kt in m/s) scales that shape: drag held, bar a 5% fall through ETL, so a collective
            //is a torque; lift solved so 4,923 kg flies the standard power curve (max endurance 70 kt
            //43.3%, max range 129 kt), 5 deg nose low at 129 kt. Generated by Core's
            //python/dev/rotortables.py --cg 0 1.625 0.224 --hover 4923:66.9 6000:86.6 6650:99.2
            //--me 70:43.3 --mr 129 --cruise-pitch -5. Full-down collective falls from the hover's idle
            //torque to 1/36 of it by 60 kt, so power-on autos overrun the engines.
            liftCoefTable[] = {
                        {"A/S", 0.00, 5.30, 10.59, 15.89, 21.18, 26.48, 31.77, 36.01, 36.85, 41.07, 45.29, 49.50, 53.72, 57.93, 62.15, 66.36, 71.10, 75.84, 92.60}
                        ,{0.000, 0.0379, 0.0401, 0.0437, 0.0472, 0.0499, 0.0509, 0.0521, 0.0524, 0.0525, 0.0531, 0.0527, 0.0515, 0.0502, 0.0484, 0.0469, 0.0450, 0.0420, 0.0407, 0.0362}
                        ,{0.850, 0.3579, 0.3781, 0.4122, 0.4453, 0.4709, 0.4801, 0.4919, 0.4946, 0.4954, 0.5013, 0.4976, 0.4859, 0.4737, 0.4570, 0.4423, 0.4245, 0.3962, 0.3842, 0.3419}
                        ,{0.900, 0.3425, 0.3618, 0.3945, 0.4261, 0.4506, 0.4595, 0.4707, 0.4733, 0.4741, 0.4798, 0.4762, 0.4650, 0.4534, 0.4374, 0.4232, 0.4062, 0.3792, 0.3677, 0.3272}
                        ,{0.950, 0.3160, 0.3339, 0.3640, 0.3932, 0.4158, 0.4240, 0.4343, 0.4367, 0.4375, 0.4427, 0.4393, 0.4290, 0.4183, 0.4036, 0.3905, 0.3748, 0.3498, 0.3393, 0.3019}
                        ,{1.000, 0.2742, 0.2896, 0.3158, 0.3411, 0.3607, 0.3678, 0.3768, 0.3789, 0.3795, 0.3840, 0.3811, 0.3722, 0.3629, 0.3501, 0.3388, 0.3251, 0.3035, 0.2943, 0.2619}
                        };
            dragCoefTable[] = {
                        {"A/S", 0.00, 5.30, 10.59, 15.89, 21.18, 26.48, 31.77, 36.01, 36.85, 41.07, 45.29, 49.50, 53.72, 57.93, 62.15, 66.36, 71.10, 75.84, 92.60}
                        ,{0.000, 0.0078, 0.0038, 0.0019, 0.0012, 0.0006, 0.0004, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002}
                        ,{0.597, 0.0413, 0.0408, 0.0401, 0.0395, 0.0392, 0.0392, 0.0392, 0.0392, 0.0392, 0.0392, 0.0392, 0.0392, 0.0392, 0.0392, 0.0392, 0.0392, 0.0403, 0.0413, 0.0413}
                        ,{0.753, 0.0539, 0.0533, 0.0523, 0.0515, 0.0512, 0.0512, 0.0512, 0.0512, 0.0512, 0.0512, 0.0512, 0.0512, 0.0512, 0.0512, 0.0512, 0.0512, 0.0526, 0.0539, 0.0539}
                        ,{0.850, 0.0616, 0.0609, 0.0598, 0.0589, 0.0585, 0.0585, 0.0585, 0.0585, 0.0585, 0.0585, 0.0585, 0.0585, 0.0585, 0.0585, 0.0585, 0.0585, 0.0601, 0.0616, 0.0616}
                        ,{0.900, 0.0801, 0.0792, 0.0777, 0.0765, 0.0761, 0.0761, 0.0761, 0.0761, 0.0761, 0.0761, 0.0761, 0.0761, 0.0761, 0.0761, 0.0761, 0.0761, 0.0781, 0.0801, 0.0801}
                        ,{0.950, 0.1109, 0.1096, 0.1076, 0.1060, 0.1053, 0.1053, 0.1053, 0.1053, 0.1053, 0.1053, 0.1053, 0.1053, 0.1053, 0.1053, 0.1053, 0.1053, 0.1081, 0.1109, 0.1109}
                        ,{1.000, 0.1602, 0.1583, 0.1554, 0.1531, 0.1522, 0.1522, 0.1522, 0.1522, 0.1522, 0.1522, 0.1522, 0.1522, 0.1522, 0.1522, 0.1522, 0.1522, 0.1562, 0.1602, 0.1602}
                        };
        };

        class SimpleRotor02 {
            type             = "tail";
            direction        = "cw";
            damageRole       = "tailRotor";
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
