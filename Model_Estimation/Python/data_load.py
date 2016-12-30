import scipy.io
import matplotlib.pyplot as plt

input_data=scipy.io.loadmat("data_input.mat")['input_data']
output_data=scipy.io.loadmat("data_output.mat")['output_data']

u_11 = input_data[20:1450,1]
u_12 = input_data[20:1450,3]
u_13 = input_data[20:1450,2]

y_11 = output_data[20:1450,1]
y_12 = output_data[20:1450,2]

u11 = u_11/u_11.max()
u12 = u_12/u_12.max()
u13 = u_13/u_13.max()
y11 = y_11/y_11.max()
y12 = y_12/y_12.max()

plt.subplot(5, 1, 1)
plt.plot(u11)
plt.ylabel('Input 1')
plt.subplot(5, 1, 2)
plt.plot(u12)
plt.ylabel('Input 2')
plt.subplot(5, 1, 3)
plt.plot(u13)
plt.ylabel('Input 3')
plt.subplot(5, 1, 4)
plt.plot(y11)
plt.ylabel('Output 1')
plt.subplot(5, 1, 5)
plt.plot(y12)
plt.ylabel('Output 2')

plt.xlabel('Data Series')
plt.show()