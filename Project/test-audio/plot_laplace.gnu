set term x11 persist
plot 'laplace_highPass_Filtered.dat' with linespoints, 'highLowSignal.dat' with linespoints
