
amp=1;
fs=44100;  % sampling frequency
duration=8;
freq=440;
values=0:1/fs:duration;
a=amp*sin(2*pi* freq*values);
plot(values,a)
%Adding 1000 imppulse noises
size_impulse = 100;
n_impulses = 1000;
rand_pos = randi([0 length(a)],1,n_impulses);
for i=1:n_impulses
    rand_pos_neg = randi([1 2],1,1);
    pos = rand_pos(i);
    if rand_pos_neg==1
        %pos
        a(pos)=size_impulse;
    else
        a(pos)= - size_impulse;
    end
end

time = values;
plot(values,a);
A=[time;a];
fileID = fopen('impulseSignal.dat','w');
fprintf(fileID,'%6.2f %12.8f\n',A);