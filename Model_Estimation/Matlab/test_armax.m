% https://www.mathworks.com/help/ident/examples/dealing-with-multi-variable-systems-identification-and-analysis.html
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
na = 10; % derajat polinomial A
nb = 10; % derajat polinomial B untuk setiap input
nc = 10; % derajat polinomial C
nk = 10; % jarak mundur input variable

% model MISO y11 dan y12 kemudian merge
armaxmod11 = armax(obj_data(1:n_learn,'y11',:),'na',na,'nb',[nb nb nb],'nc',nc,'nk',[nk nk nk]);
armaxmod12 = armax(obj_data(1:n_learn,'y12',:),'na',na,'nb',[nb nb nb],'nc',nc,'nk',[nk nk nk]);
armaxmod = merge(armaxmod11,armaxmod12)

% bandingkan hasil untuk validasi
figure('Name','MISO ARMAX Y11','NumberTitle','off')
compare(obj_data(n_learn+1:n_total,'y11',:),armaxmod11);

figure('Name','MISO ARMAX Y12','NumberTitle','off')
compare(obj_data(n_learn+1:n_total,'y12',:),armaxmod12);

figure('Name','MIMO','NumberTitle','off')
subplot(211);
compare(obj_data(n_learn+1:n_total,'y11',:),armaxmod);
grid;
subplot(212);
compare(obj_data(n_learn+1:n_total,'y12',:),armaxmod);
