#!/bin/bash

dataDir="."
outDataFile="data.txt"
case_labels=("Quad_Spiral_Valley" "Double_Scepter_Valley" "Seahorse_Valley" "Mini_Mandelbrot" "Scepter_Variant" "Basic_Mandelbrot")
xmin_limits=(0.273 -0.104 -0.75 -2 0 -2)
xmax_limits=(0.276 -0.100 -0.74 -1.5 30 1) 
ymin_limits=(0.484 0.835 0 -0.02 -0.007 -1)
ymax_limits=(0.486 0.8385 0.2 0.02 0.007 1)
step_sizes=(0.0000025 0.0000025 0.000025 0.00025 0.001 0.0008)
if [ ! -f /opt/nfs/mpich-3.2/bin/mpiexec ]; 
then
	echo "Ostrzeżenie: w ścieżce /opt/nfs/mpich-3.2/bin/ nie znaleziono poprawnego mpiexec"
	exit
fi
run_command="/opt/nfs/mpich-3.2/bin/mpiexec -n 4 ./mandelbrot.run"

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
