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

for((i=${1};i<=${1};i+=5))
do
echo "Angle value : ${1}"
echo "
root -b 'Wavelength_ana.C("$i")' .> /data/users/mparanjp/DD4hep/examples/SingleCrystal_cosmic_ray/compact/Med_files/0811_100_ev/Output_Files/wave_0811_$i.log
"

root -b 'Wavelength_ana.C('$i')' .> /data/users/mparanjp/DD4hep/examples/SingleCrystal_cosmic_ray/compact/Med_files/0811_100_ev/Output_Files/wave_0811_$i.log

done

exitcode=$?


#
# end run
#

echo ""
END_TIME=`/bin/date`
echo "finished at $END_TIME"
exit $exitcode
