set datafile separator ","
set terminal png size 800,800
set output 'method3-densities.png'
set title "Method 3 Queue densities with parameters 1, 2, 4, 8, 16"
set xlabel "Time (in s)"
set ylabel "Queue Density"
set style line 1 \
    linecolor rgb 'black' \
    linetype 1 linewidth 1 
set style line 2 \
    linecolor rgb 'red' \
    linetype 1 linewidth 1 
set style line 4 \
    linecolor rgb 'orange' \
    linetype 1 linewidth 1 
set style line 8 \
    linecolor rgb 'yellow' \
    linetype 1 linewidth 1 
set style line 16 \
    linecolor rgb 'green' \
    linetype 1 linewidth 1 
set style line 15 \
    linecolor rgb 'cyan' \
    linetype 1 linewidth 1 


plot "baseline.txt" with linespoints linestyle 1 title "1", \
    "2.txt" with linespoints linestyle 2 title "2", \
    "4.txt" with linespoints linestyle 4 title "4", \
    "8.txt" with linespoints linestyle 8 title "8", \
    "16.txt" with linespoints linestyle 16 title "16",

