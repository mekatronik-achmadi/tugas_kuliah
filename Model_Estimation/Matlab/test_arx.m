% http://www-rohan.sdsu.edu/doc/matlab/toolbox/ident/ch3tut24.html

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

% persamaan ARMAX
% A(q)y(t) = B(q)u(t-nk) + C(q)e(t)

% parameter ARMAX
%na = 10; % derajat polinomial A
%nb = 10; % derajat polinomial B untuk setiap input
%nc = 10; % derajat polinomial C
%nk = 10; % jarak mundur input variable
na = [2 1;2 2];
nb = [2 3 0;1 1 2];
nk = [4 0 0;0 4 1];

% model MISO y11 dan y12 kemudian merge
arxmod = arx(obj_data(1:n_learn,:,:),[na nb nk]);
compare(obj_data(n_learn+1:n_total,:,:),arxmod);
