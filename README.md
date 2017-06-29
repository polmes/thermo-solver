# Thermodynamics Simulation
Heat Transfer simulator using a Finite Volumes solver for *Gas Dynamics*

## Phase 1 (*currently under development*)
- 2D transient conduction analysis with multiple materials

### Phase 1A
- Smallest mesh discretization for all materials, using a line-by-line solver
- Parallel computation of horizontal and vertical lines

### Phase 1B
- Independent mesh discretization for each material, using a Gauss-Seidel solver for internal boundary nodes
- Parallel computation of each material region

## Phase 2
- Navier-Stokes discretization: mass + momentum + (energy)

## Phase 3
- Convection with 2D laminar flow

## Phase 4
- Convection with 3D turbulent flow
