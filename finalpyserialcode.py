#import time
from datetime import datetime
import csv
import serial
port = serial.Serial("COM3", 9600)


try:
    
    while True:
        line = port.readline()
        file =open('sensorfinal.csv','a',newline='')
        filewriter = csv.writer(file)
        line = str(datetime.now().date()) + "," + str(datetime.now().time()) + "," + line.decode("utf-8").rstrip()
        print(line)
        filewriter.writerow(line.split(","))
        file.close()
except KeyboardInterrupt:
	port.close()
