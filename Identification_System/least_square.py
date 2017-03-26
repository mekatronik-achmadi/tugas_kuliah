# -*- coding: utf-8 -*-
"""
Created on Mon Mar 27 01:30:26 2017

@author: achmadi
"""

import numpy as np
import scipy.io as sio
import matplotlib.pyplot as plt

# load semua data
in_fuel_flow = sio.loadmat("data_uji_mesin.mat")['mass_fuel_flow']
in_comb_start = sio.loadmat("data_uji_mesin.mat")['comb_start']
in_tps = sio.loadmat("data_uji_mesin.mat")['tps']

in_afr = sio.loadmat("data_uji_mesin.mat")['afr']
in_rpm = sio.loadmat("data_uji_mesin.mat")['rpm']
in_torque = sio.loadmat("data_uji_mesin.mat")['torque']

# normalisasi rentang nilai
fuel_flow = in_fuel_flow/in_fuel_flow.max()
comb_start = in_comb_start/in_comb_start.max()
tps = in_tps/in_tps.max()

afr = in_afr/in_afr.max()
rpm = in_rpm/in_rpm.max()
torque = in_torque/in_torque.max()

# jumlah total data
T = tps.size

##########################################

# y = rpm
# y1 = rpm telat 1
# u = tps
# u1 = tps telat 1
# v = comb_start
# v1 = comb_start telat 1
# w = fuel_flow
# w = fuel_flow telat 1

# y = a.y1 + b.u + c.u1 + d.v + e.v1 + f.w + g.w1

# bentukan matrix
# ambil 125 data untuk cari persamaan dan 24 data untuk validasi
N = 125
y = rpm[1:N]
y1 = rpm[0:N-1]
u = tps[1:N]
u1 = tps[0:N-1]
v = comb_start[1:N]
v1 = comb_start[0:N-1]
w = fuel_flow[1:N]
w1 = fuel_flow[0:N-1]

# proses least mean square
VT = np.hstack((y1,u,u1,v,v1,w,w1))
V = VT.transpose()
VM = np.dot(V,VT)
iVM = np.linalg.inv(VM)
VY = np.dot(V,y)
H = np.dot(iVM,VY)

###################################################

# urutan sample
x = np.arange(1,T-N,1)

# nilai pengukuran
y_meas = rpm[N+1:T]

# ambil koefisien
a = H[0]
b = H[1]
c = H[2]
d = H[3]
e = H[4]
f = H[5]
g = H[6]

# ambil variabel
y_v = rpm[N+1:T]
y1_v = rpm[N:T-1]
u_v = tps[N+1:T]
u1_v = tps[N:T-1]
v_v = comb_start[N+1:T]
v1_v = comb_start[N:T-1]
w_v = fuel_flow[N+1:T]
w1_v = fuel_flow[N:T-1]

# hitung estimasi
y_estim = np.zeros(x.size)
for i in range(0,x.size):
    y_estim = a*y1_v + b*u_v + c*u1_v + d*v_v + e*v1_v + f*w_v + g*w1_v
    
# plot sebagai komparasi

plt.figure()
plt.title('Compare')
plt.plot(x,y_meas, 'r', label='measured')
plt.plot(x,y_estim, 'b', label='estimation')
plt.legend(loc='best')
plt.grid()
plt.show()