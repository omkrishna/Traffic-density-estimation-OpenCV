set datafile separator ","
set terminal png size 1000,1000
set output 'method4-densities.png'
set title "Method 4 Queue densities with parameters 1, 2, 3, 4, 5"
set xlabel "Time (in s)"
set ylabel "Queue Density"
set style line 1 \
    linecolor rgb 'black' \
    linetype 1 linewidth 1 
set style line 2 \
    linecolor rgb 'red' \
    linetype 1 linewidth 1 
set style line 3 \
    linecolor rgb 'orange' \
    linetype 1 linewidth 1 
set style line 4 \
    linecolor rgb 'blue' \
    linetype 1 linewidth 1 
set style line 5 \
    linecolor rgb 'green' \
    linetype 1 linewidth 1 


plot "baseline.txt" with linespoints linestyle 1 title "1", \
    "2.txt" with linespoints linestyle 2 title "2", \
    "3.txt" with linespoints linestyle 3 title "3", \
    "4.txt" with linespoints linestyle 4 title "4", \
    "5.txt" with linespoints linestyle 5 title "5",

