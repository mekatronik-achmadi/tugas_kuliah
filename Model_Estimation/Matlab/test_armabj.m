% https://www.mathworks.com/help/ident/ref/bj.html
% http://www.itl.nist.gov/div898/handbook/pmc/section4/pmc445.htm

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

% persamaan ARMA BJ

% parameter ARMA BJ
 nb = [2 2 2; 2 2 2];
 nc = [2;2];
 nd = [2;2];
 nf = [2 2 2; 2 2 2];
 nk = [2 2 2; 2 2 2];
 
% shit, there's no arima function in Matlab 7 (2009)
armabj = bj(obj_data(1:n_learn,'y11',:),[nb nc nd nf nk]);
compare(obj_data(n_learn+1:n_total,'y11',:),armabj);
