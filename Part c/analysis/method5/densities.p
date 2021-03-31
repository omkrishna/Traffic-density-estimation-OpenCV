set datafile separator ","
set terminal png size 800,800
set output 'method5-densities.png'
set title "Method 2 Dynamic densities with using dense and sparse optical flow"
set xlabel "Time (in s)"
set ylabel "Dynamic Density"
set style line 1 \
    linecolor rgb 'blue'
set style line 1 \
    linecolor rgb 'orange'

plot "baseline.txt" using 1:3 with line linestyle 1 title "dense", \
    "sparse.txt" using 1:3 with line linestyle 2 title "sparse"
