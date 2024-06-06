#!/bin/bash

cd /data/users/mparanjp/DD4hep/examples/SingleCrystal_cosmic_ray/compact/

START_TIME=`/bin/date`
echo "started at $START_TIME"


# setup software environment at UMD
#

source /cvmfs/sft.cern.ch/lcg/views/LCG_102b/x86_64-centos7-gcc11-opt/setup.sh
echo "ran setup"
source  /data/users/mparanjp/DD4hep/bin/thisdd4hep.sh
echo "ran thisdd4hep"
#
# run 
#

#for((i=65;i<=85;i+=5))
#i = argument
#echo $i
for((i=${1};i<=${1};i+=5))
do
echo "Angle value : ${1}"
pi=$(echo "scale=10; 4*a(1)" | bc -l) #value of pi from tan-1(1)
j=$(echo "scale=10; s($i*$pi/180.)/c($i*$pi/180.)" | bc -l)

#k=$(echo "-(15-12.5)*$j" | bc -l) #passing through center of long face
k=$(echo "-(15)*$j" | bc -l) # passing through center of crystal

echo "Value of pi $pi"
echo "Value of tan $j value of gun position z $k"
echo "ddsim --steeringFile /data/users/mparanjp/DD4hep/examples/SingleCrystal_cosmic_ray/compact/junkst2.py --compact /data/users/mparanjp/DD4hep/examples/SingleCrystal_cosmic_ray/compact/DRJunk.xml --runType batch --part.userParticleHandler='' -G --gun.position="0.,-15.,$k" --gun.direction "0 1 $j" --gun.energy "120*GeV" --gun.particle="proton" -N 100 -O Root_files/Protons/PbWO4/0811_100_ev/out_0811_$i.root >& Spew_files/Protons/PbWO4/0811_100_ev/out_cndr_0811_$i.log"

ddsim --steeringFile /data/users/mparanjp/DD4hep/examples/SingleCrystal_cosmic_ray/compact/junkst2.py --compact /data/users/mparanjp/DD4hep/examples/SingleCrystal_cosmic_ray/compact/DRJunk.xml --runType batch --part.userParticleHandler='' -G --gun.position="0.,-15.,$k" --gun.direction "0 1 $j" --gun.energy "120*GeV" --gun.particle="proton" -N 100 -O Root_files/Protons/PbWO4/0811_100_ev/out_0811_$i.root >& Spew_files/Protons/PbWO4/0811_100_ev/out_cndr_0811_$i.log

done

exitcode=$?


#
# end run
#

echo ""
END_TIME=`/bin/date`
echo "finished at $END_TIME"
exit $exitcode
