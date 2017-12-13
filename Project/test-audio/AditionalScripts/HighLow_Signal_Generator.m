
amp=1;
fs=44100;  % sampling frequency
duration=8;
freq=10;
values=0:1/fs:duration;
a=amp*sin(2*pi* freq*values);

freq=200;
values=0:1/fs:duration;
b=amp*sin(2*pi* freq*values);

a= a + b;

plot(values,a)


time = values;
plot(values,a);
A=[time;a];
fileID = fopen('highLowSignal.dat','w');
fprintf(fileID,'%6.2f %12.8f\n',A);