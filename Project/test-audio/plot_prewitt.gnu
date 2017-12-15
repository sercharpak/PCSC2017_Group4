set term x11 persist
plot 'highLowSignal.dat' with linespoints, 'prewitt_bandPass_Filtered.dat' with linespoints
