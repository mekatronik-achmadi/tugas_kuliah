% bersihkan segala-galanya
close all
clc
clear all

% load semua paket
pkg load all

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

% persamaan ARX
% A(q) y(t) = B(q) u(t) + e(t)

% parameter ARMAX
%na = 10; % derajat polinomial A
%nb = 10; % derajat polinomial B untuk setiap input
%nc = 10; % derajat polinomial C
%nk = 10; % jarak mundur input variable
na = [2;2];
nb = [2 3 0;1 1 2];
nk = 4;

% model MIMO
arxmod = arx(obj_data(1:n_learn,:,:),'na',na,'nb',nb,'nk',nk);
