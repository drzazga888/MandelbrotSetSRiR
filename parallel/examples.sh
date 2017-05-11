#!/bin/bash

dataDir="."
outDataFile="data.txt"
case_labels=("Quad_Spiral_Valley" "Double_Scepter_Valley" "Seahorse_Valley" "Mini_Mandelbrot" "Basic_Mandelbrot")
xmin_limits=(0.273 -0.104 -0.8 -2 -2)
xmax_limits=(0.276 -0.100 -0.7 -1.5 1) 
ymin_limits=(0.484 0.835 0.1 -0.02 -1)
ymax_limits=(0.486 0.8385 0.2 0.02 1)
step_sizes=(0.000005 0.000005 0.00025 0.0025 0.005)
if [ ! -f /opt/nfs/mpich-3.2/bin/mpiexec ]; 
then
	echo "Ostrzeżenie: w ścieżce /opt/nfs/mpich-3.2/bin/ nie znaleziono poprawnego mpiexec"
	#exit
fi
run_command="/opt/nfs/mpich-3.2/bin/mpiexec -n 4 ./mandelbrot.run"
run_command="mpiexec -n 4 ./mandelbrot.run"

if [ ! -d "$dataDir" ];
then
	mkdir $dataDir;
fi

for ((i=0; i < 5;i++))
do
	params="${xmin_limits[$i]} ${xmax_limits[$i]} ${ymin_limits[$i]} ${ymax_limits[$i]} ${step_sizes[$i]}"
	label="${case_labels[$i]}"
	$run_command $params && gnuplot plot.plt && mv result.png $dataDir/$label.png && rm $outDataFile
done
