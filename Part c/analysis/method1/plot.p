set datafile separator ","
set terminal png size 800,800
set output 'method1-utility.png'
set title "Method-1 Utility Runtime Analysis with parameters (1,3,6,9,12,15,30)"
set xlabel "Error (absolute of the difference)"
set ylabel "Running Time (in s)"
set style line 1 \
    linecolor rgb '#0060ad' \
    linetype 1 linewidth 2 \
    pointtype 7 pointsize 1.5
plot "utility.txt" with linespoints linestyle 1

