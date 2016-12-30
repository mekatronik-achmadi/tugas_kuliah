% https://www.mathworks.com/help/econ/arma-models.html

% bersihkan segala-galanya
close all
clc
clear all

% ambil data ternormalisasi ke memory
data_load;

% jangkauan learning data
% n_learn << n_total
n_total = numel(u11);
n_learn = 1000;

% bentuk data objek sebagai time-series data
obj_data = iddata([y11,y12],[u11,u12,u13],1);
obj_data.InputName  = {'u11';'u12';'u13'};
obj_data.OutputName  = {'y11';'y12'};

% ARMA (ARIMA with I = 0) model
% shit, there's no arima function in Matlab 7 (2009)
mdl = arima(1,0,1)
