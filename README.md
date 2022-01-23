# stromatolites
## What?
These are the pieces of _DLA 3D EXT_ that I modified to include spike fields and allow for an attraction radius that goes to zero. Users can model particle accumulation over a single spike or a spike field and can control spike height and (in the case of a field) spike spacing. 
- Simulator: all modified Simulator files.
  - InitialSurfaceManager* -- includes spike creation code. 
  - InitialSurfaceDialog* -- allows user to create spikes in Simulator GUI.
  - SimulationSettings* -- allows user to set AR to 0.
  - FileManager* -- gives simulation files names that are a little more informative; esp. useful if you're running tons of simulations.
- Visualizer: all modified Visualizer files
  - FileManager* -- allows user to set AR to 0 and open simulation files.

## Why?
_DLA 3D EXT_ is an open-source program that models particle accumulation over a surface using diffusion-limited aggregation. It's a great analog for stromatolite formation! My goal with modifying this software was to model stromatolite formation in the distal slope facies of travertine hot springs, and then see whether we could quantify any uniquely biological characteristics using fractal analysis. <a href="https://scholarworks.umt.edu/etd/11766/">Read more here</a>.

## How?
My pieces of code need to be integrated with the full software. In order to obtain the full _DLA 3D EXT_ code, contact <a href="https://www.researchgate.net/profile/Eric_Verrecchia">Eric Verrecchia</a> or <a href="https://ch.linkedin.com/in/damien-chappatte-27087323">Damien Chappatte</a>. Also, fair warning if this is your first foray into C++ software programming: you will have to compile and recompile this a gajillion times to resolve all the references to C++ headers. Exactly how you do that will depend on what IDE you use (I used Eclipse) but essentially, look in the compile errors for which headers your IDE can't find, figure out where they live on your machine, and tell your IDE the correct path. It will be _very_ tedious. Put on some podcasts. The New Yorker Fiction podcast is pretty good!

## Who?
Contact me: stevensl@gonzaga.edu
