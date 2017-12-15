set term x11 persist
plot 'highLowSignal.dat' with linespoints, 'mean_lowPass_Filtered.dat' with linespoints
