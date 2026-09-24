# EC665 Tiger - HeliSim

A HeliSim flight model for BW-Mod's Eurocopter EC665 Tiger. It is an aircraft
pack: Core (`bmkhs_helisim`) does the simulation, and this pack declares what
the Tiger is. It modifies `BWA3_Tiger_base`, so every Tiger variant BW-Mod ships
flies on it.

**No systems are modelled** (`useSystems = 0`): no electrical, APU, hydraulics or
drivetrain components, no cockpit switches. The aircraft starts cold and wakes on
the first collective input. Drivetrain torque limits still apply, and an
overtorque damages the rotors.

## Requires

| mod | why |
|---|---|
| BradMick's HeliSim 1.0.2.0 or later | the flight model this pack drives |
| BW-Mod | the Tiger itself (`bwa3_tiger`) |
| CBA_A3 | HeliSim's dependency |

Load all three in game. This pack loads after HeliSim and after BW-Mod's Tiger.

## Building

    hemtt build      # -> .hemttout/build/addons/bmkhs_ec665_helisim.pbo

Nothing else is needed: the HeliSim header this pack includes is committed in
`include/bmkhs_helisim/`. When moving to a new HeliSim version, refresh it as
described in HeliSim's `docs/AIRCRAFT_GUIDE.md`, "Building your mod against
Core's headers".

## Status: flying on AH-64D placeholder numbers

Every file in `addons/helisim/config/bmkhs_config/` started as the AH-64D's
values, so the Tiger flies from day one - like an Apache. Each file is headed with
what still has to become Tiger data; search for `TODO(EC665)`.

Known differences to deal with first:

- **Rotor direction.** The Tiger's main rotor turns clockwise (BW-Mod declares
  `mainRotorSpeed = -1`); the placeholder is the Apache's counter-clockwise set.
  Flip the rotor direction and the tail rotor's thrust together, then check it in
  a hover.
- **Stabiliser.** The Tiger's is fixed; the placeholder is the Apache's scheduled
  stabilator.
- **Crew.** The Tiger seats its pilot and gunner the opposite way round from the
  Apache; check the seat arms against BW-Mod's model.
- **Geometry.** Every position in the pack is in the Tiger's model space: rotor
  hubs, CG, tanks, seats, stations. None of it is read from the model.

What is already Tiger-specific: the base class, the four single-pylon wing
stations in BW-Mod's pylon order, and store entries matched to BW-Mod's pylon
magazines (PARS 3, FZ rockets, 12.7 mm gun pod, Fliegerfaust). The store masses
are still placeholders.
