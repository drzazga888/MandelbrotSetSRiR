set size 1,1; set origin 0,0
set grid layerdefault
set xlabel "x"
set ylabel "y"

set sample 11
set isosamples 11
set pm3d map
set palette
set colorbox
set lmargin 0
set size ratio -1
set terminal png size 1920,1080 enhanced font 'Verdana,10'
set output 'result.png'

set pm3d flush begin
splot 'data.txt' u 1:2:3
