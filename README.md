# Thermo Solver
Thermal conduction simulator using a Finite Volumes solver for *Gas Dynamics and Heat and Mass Trasnsfer*

![Temperatures Evolution with Time](plots/map.gif)

## Instructions
First of all, make sure [`g++-6`](https://launchpad.net/~ubuntu-toolchain-r/+archive/ubuntu/test) is installed and available in the `$PATH`. Then:
```bash
make # compile all them files
./thermo # run the simulator!
```

## Features
- 2D transient conduction analysis
- With multiple materials
- Easily configurable boundary conditions

#### Improvements
- Read input data from user-supplied `config.dat`
- Divide in as many regions as CPUs (use `std::thread::hardware_concurrency()`)
- Solve each region with a line-by-line solver with supposed `Tboundaries`
- Each region communicates the new `Tboundaries` to the surrounding ones (and back)
- Polymorphism for the `Condition` class: make derived `Convection`, `Isotherm`, `Flow` `Adiabatic` classes
- Create a `Matrix` class using `std::vector` with smart indexing
