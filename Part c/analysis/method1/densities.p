set datafile separator ","
set terminal png size 800,800
set output 'method1-densities.png'
set title "Method 1 Queue densities with parameters 1, 3, 6, 9, 12, 15, 30"
set xlabel "Time (in s)"
set ylabel "Queue Density"
set style line 1 \
    linecolor rgb 'black' \
    linetype 1 linewidth 1 
set style line 3 \
    linecolor rgb 'red' \
    linetype 1 linewidth 1 
set style line 6 \
    linecolor rgb 'orange' \
    linetype 1 linewidth 1 
set style line 9 \
    linecolor rgb 'yellow' \
    linetype 1 linewidth 1 
set style line 12 \
    linecolor rgb 'green' \
    linetype 1 linewidth 1 
set style line 15 \
    linecolor rgb 'cyan' \
    linetype 1 linewidth 1 
set style line 30 \
    linecolor rgb 'violet' \
    linetype 1 linewidth 1 

plot "baseline.txt" with linespoints linestyle 1 title "1", \
    "3.txt" with linespoints linestyle 3 title "3", \
    "6.txt" with linespoints linestyle 6 title "6", \
    "9.txt" with linespoints linestyle 9 title "9", \
    "12.txt" with linespoints linestyle 12 title "12", \
    "15.txt" with linespoints linestyle 15 title "15", \
    "30.txt" with linespoints linestyle 30 title "30 

