import serial
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import matplotlib.pyplot as plt
from matplotlib.figure import Figure
import numpy as np
import tkinter as tk
#--------------Global variables
dataAcX = np.array([])
dataAcY = np.array([])
dataAcZ = np.array([])

dataGyroX = np.array([])
dataGyroY = np.array([])
dataGyroZ = np.array([])
cond = False

#--------------plot data

#--------------function for Accelerometer
def plot_data():
    global cond, dataAcX, dataAcY, dataAcZ, dataGyroX, dataGyroY, dataGyroZ
    try:

        if (cond == True):
            a = ser.readline().decode('ascii') #read serial
            a = a.replace('\x00','') # getting rid of empty data in buffer
            a = a.split(",") #split data by coma
            a1 = a[0] # accelerometer X axis
            a2 = a[1] # accelerometer Y axis
            a3 = a[2] # accelerometer Z axis
            g1 = a[3] # gyro X axis
            g2 = a[4] # gyro Y axis
            g3 = a[5] # gyro Z axis

            if(len(dataAcX) < 100):
                dataAcX = np.append(dataAcX, float(a1)/16000)
            if(len(dataAcY) < 100):
                dataAcY = np.append(dataAcY, float(a2)/16000)
            if(len(dataAcZ) < 100):
                dataAcZ = np.append(dataAcZ, float(a3)/16000)
            if(len(dataGyroX) < 100):
                dataGyroX = np.append(dataGyroX, float(g1))
            if(len(dataGyroY) < 100):
                dataGyroY = np.append(dataGyroY, float(g2))
            if(len(dataGyroZ) < 100):
                dataGyroZ = np.append(dataGyroZ, float(g3))
            else:
                dataAcX[0:99] = dataAcX[1:100]
                dataAcY[0:99] = dataAcY[1:100]
                dataAcZ[0:99] = dataAcZ[1:100]
                dataGyroX[0:99] = dataGyroX[1:100]
                dataGyroY[0:99] = dataGyroY[1:100]
                dataGyroZ[0:99] = dataGyroZ[1:100]
                dataAcX[99] = float(a1)/16000
                dataAcY[99] = float(a2)/16000
                dataAcZ[99] = float(a3)/16000
                dataGyroX[99] = float(g1)
                dataGyroY[99] = float(g2)
                dataGyroZ[99] = float(g3)

    except (ValueError,IndexError):
        pass
# do nothing!
    lines1.set_xdata(np.arange(0,len(dataAcX)))
    lines2.set_xdata(np.arange(0,len(dataAcY)))
    lines3.set_xdata(np.arange(0,len(dataAcZ)))
    lines4.set_xdata(np.arange(0,len(dataGyroX)))
    lines5.set_xdata(np.arange(0,len(dataGyroY)))
    lines6.set_xdata(np.arange(0,len(dataGyroZ)))
    lines1.set_ydata(dataAcX)
    lines2.set_ydata(dataAcY)
    lines3.set_ydata(dataAcZ)
    lines4.set_ydata(dataGyroX)
    lines5.set_ydata(dataGyroY)
    lines6.set_ydata(dataGyroZ)
    canvas.draw()

    root.after(1,plot_data)
#    root.after(1,plot_dataAcY)
#    root.after(1,plot_dataAcZ)
#--------------function for Gyro
# def plot_dataAcY():
#    global cond, dataAcY
#    try:
#
#        if (cond == True):
#            a = ser.readline().decode('ascii')
#            a = a.replace('\x00','')
#            a = a.split(",")
#            a2 = a[1]
#
#            if(len(dataAcY) < 100):
#                dataAcY = np.append(dataAcY, float(a2)/16000)
#
#            else:
#                dataAcY[0:99] = dataAcY[1:100]
#                dataAcY[99] = float(a2)/16000
#
#    except (ValueError,IndexError):
#        if (len(dataAcY) < 100):
#            pass
#        else:
#            dataAcY[99] = dataAcY[98]# do nothing!
#    lines2.set_xdata(np.arange(0,len(dataAcY)))
#    lines2.set_ydata(dataAcY)
#
#    canvas.draw()
#
#    root.after(1,plot_dataAcY)

#--------------functions for the Buttons
def plot_start():
    global cond
    cond = True
    ser.reset_input_buffer()
def plot_stop():
    global cond
    cond = False

#--------------Main GUI code
root = tk.Tk()
root.title('Pavels Real Time Plot')
root.configure(background = 'gray24')
root.geometry('700x500') # set the window size

#-------------Create Plot object on GUI
fig = Figure()
accelPlot = fig.add_subplot(221) #1st subplot
gyroPlot = fig.add_subplot(223) #2nd subplot

#-------------first subplot
accelPlot.set_title('Accelerometer')
#accelPlot.set_xlabel('Sample')
accelPlot.set_ylabel('Acceleration [G]')
accelPlot.set_xlim(0,100)
accelPlot.set_ylim(-2,2)
lines1 = accelPlot.plot([],[])[0]
lines2 = accelPlot.plot([],[])[0]
lines3 = accelPlot.plot([],[])[0]

canvas = FigureCanvasTkAgg(fig, master = root)
canvas.get_tk_widget().place(x = 0, y = 0, width = 700, height = 500)
canvas.draw()

#-----------second subplot
gyroPlot.set_title('Gyro')
#gyroPlot.set_xlabel('Sample')
gyroPlot.set_ylabel('Angular Rate [grad/s]')
gyroPlot.set_xlim(0,100)
gyroPlot.set_ylim(-16000,16000)
lines4 = gyroPlot.plot([],[])[0]
lines5 = gyroPlot.plot([],[])[0]
lines6 = gyroPlot.plot([],[])[0]

#canvas2 = FigureCanvasTkAgg(fig, master = root)
#canvas2.get_tk_widget().place(x = 300, y = 10, width = 300, height = 200)
#canvas2.draw()

#-------------Create Button
root.update()
start = tk.Button(root, text = 'Start', font = ('calibri', 12), command = lambda:plot_start())
start.place(x = 100, y = 469)

root.update()
stop = tk.Button(root, text = 'Stop', font = ('calibri', 12), command = lambda:plot_stop())
stop.place(x = 250, y = 469)

#-----------------------Serial Port
ser = serial.Serial('/dev/ttyACM0', baudrate = 115200, timeout = 0)
ser.reset_input_buffer()


root.after(1,plot_data)
#root.after(1,plot_dataAcY)
#root.after(1,plot_dataAcZ)

root.mainloop()









#ser = serial.Serial('/dev/ttyACM1', baudrate = 115200, timeout = 1)




#plt.axis([0, 100, 0, 100])
#y = ser_bytes
#  plt.plot(y)

#plt.ion()
#fig, ax = plt.subplots()
#line, = ax.plot(y_var)
#while True:
#    ser_bytes = ser.readline().decode('ascii')
#y = ser_bytes
#plt.plot(y)

#plt.show()
