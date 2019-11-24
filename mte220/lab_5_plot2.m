clear all;
close all;
clc;

Av = tf([0 -330/3.9], [.33 1]);

Measured = [5e-2 38.03173;            
            6e-2 38.03173;
            7e-2 38.03173;
            8e-2 38.99014;
            9e-2 37.82854;
            1e-1 37.82854;
            2e-1 37.1888;
            3e-1 36.73453;
            4e-1 35.74784;
            5e-1 35.20901;
            6e-1 34.33237;
            7e-1 33.69459;
            8e-1 32.54656;
            9e-1 32.16046;
            1 31.33261;
            2 26.89563;
            3 24.39686;
            4 22.21397;
            5 20.87503];

semilogx(Measured(:,1)*2*pi, Measured(:,2), 'r--')
hold on;
bode(Av);
