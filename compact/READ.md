To generate GEANT4 root files using dd4hep:

ddsim --steeringFile /data/users/snabili/CalVision/DD4HEP_simulation_05282024/DD4hep/examples/SingleCrystal_cosmic_ray/compact/junkst2.py --compact /data/users/snabili/CalVision/DD4HEP_simulation_05282024/DD4hep/examples/SingleCrystal_cosmic_ray/compact/DRJunk.xml --runType batch --part.userParticleHandler='' -G --gun.position="0.,-15.,0." --gun.direction "0 1 0" --gun.energy "2*GeV" --gun.particle="e-" -N 1 -O test.root >& test.log

To analyse the root file and make signal vs time plot:

root -l -b 'Timing_ana.C(<angle>)'
