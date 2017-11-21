import numpy as np
import matplotlib.pyplot as mpl

input=np.loadtxt('ecg.dat')
time=input[:,0]
input=input[:,1]
input=(input*2-4096)/500 //Gain of the data adquisition equipment


mpl.plot(time[80000:81000], input[80000:81000])
mpl.title('Zoomed input ECG ')
mpl.xlabel('time(ms)')
mpl.ylabel('amplitude (mV)')
mpl.savefig('zoomed_ecg.pdf')
