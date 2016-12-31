import scipy.io as sio
import matplotlib.pyplot as plt

class DataLoad:
    def __init__(self):
        input_data=sio.loadmat("data_input.mat")['input_data']
        output_data=sio.loadmat("data_output.mat")['output_data']
        
        u_11 = input_data[20:1450,1]
        u_12 = input_data[20:1450,3]
        u_13 = input_data[20:1450,2]
        
        y_11 = output_data[20:1450,1]
        y_12 = output_data[20:1450,2]
        
        self.u11 = u_11/u_11.max()
        self.u12 = u_12/u_12.max()
        self.u13 = u_13/u_13.max()
        self.y11 = y_11/y_11.max()
        self.y12 = y_12/y_12.max()
        
    def plot(self):
        plt.subplot(5, 1, 1)
        plt.plot(self.u11)
        plt.ylabel('Input 1')
        plt.subplot(5, 1, 2)
        plt.plot(self.u12)
        plt.ylabel('Input 2')
        plt.subplot(5, 1, 3)
        plt.plot(self.u13)
        plt.ylabel('Input 3')
        plt.subplot(5, 1, 4)
        plt.plot(self.y11)
        plt.ylabel('Output 1')
        plt.subplot(5, 1, 5)
        plt.plot(self.y12)
        plt.ylabel('Output 2')
        
        plt.xlabel('Data Series')
        plt.show()