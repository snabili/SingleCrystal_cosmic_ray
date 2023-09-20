Installation instructions:

source /cvmfs/sft.cern.ch/lcg/views/LCG_102b/x86_64-centos7-gcc11-opt/setup.sh
git clone https://github.com/AIDASoft/DD4hep.git
cd DD4hep/examples
git clone https://github.com/Mekhpar/SingleCrystal_cosmic_ray.git

edit CMakeLists.txt (inside DD4hep/examples) and add SingleCrystal_cosmic_ray to (in this case, line 45)
SET(DD4HEP _EXAMPLES "AlignDet CLICSiD ClientTests Conditions DDCMS DDCodex DDDigi DDG4 DDG4_MySensDet LHeD Optica\
lSurfaces Persistency DDCAD SimpleDetector SingleCrystal_cosmic_ray "
CACHE STRING "List of DD4hep Examples to build")

(if you created a new hit class, need to add it in CMakelists.txt in your top area for your checked out code on the line SOURCES $(DD4hep_DIR}include/root/Warnings.h)

cd ..
mkdir build
mkdir install
cd build/
cmake -DDD4HEP_USE_GEANT4=ON -DBoost_NO_BOOST_CMAKE=ON -DDD4HEP_USE_LCIO=ON -DBUILD_TESTING=ON -DROOT_DIR=$ROOTSYS -D CMAKE_BUILD_TYPE=Release -DDD4HEP_BUILD_EXAMPLES=ON ..
make -j4
make install
cd ..
source bin/thisdd4hep.sh

And for setup every time the files are changed or a new terminal is opened: (go to the DD4hep directory)
source /cvmfs/sft.cern.ch/lcg/views/LCG_102b/x86_64-centos7-gcc11-opt/setup.sh
source bin/thisdd4hep.sh

Example of command for interactive display:
ddsim --steeringFile junkst2.py --compact DRJunk.xml --runType vis --part.userParticleHandler='' -G --gun.position="x y z" --gun.direction "x' y' z'" --gun.energy value*units --gun.particle=particle -O output_file
And then upon receiving the command prompts,
/control/execute vis.mac 

/run/beamOn 1

For batch mode:
ddsim --steeringFile junkst2.py --compact DRJunk.xml --runType batch --part.userParticleHandler='' -G --gun.position="x y z" --gun.direction "x' y' z'" --gun.energy value*units --gun.particle=particle -O output_file -N num_evts

Job files to be used:
condor-job.jdl for event generation
Med_calc.jdl for median calculation, Plot_med.C for the corresponding angular dependence plots
Time_calc.jdl and Wave_calc.jdl for timing and wavelength distributions respectively
