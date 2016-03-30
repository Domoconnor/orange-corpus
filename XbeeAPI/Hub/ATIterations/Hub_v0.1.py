import serial, threading, time
 
class HTTPConnection:
 
   def __init__(self, host, port):
      self.host = host
      self.port = port
 
   def sendToHost(self, payload):
 	print "hello"
 
 
class Serial:
 
   def __init__(self, usbdev):
      self.usbdev = usbdev
      self.serial = serial.Serial(usbdev)
     # self.serial = serial.Serial(usbdev)
 
   def readSerial(self):
      print "Reading"
      tdata = s.read()           # Wait forever for anything
      time.sleep(5)              # Sleep (or inWaiting() doesn't give the correct value)
      data_left = s.inWaiting()  # Get the number of characters ready to be read
      tdata += self.serial.read(data_left) # Do the read and combine it with the first character
      print "Finished reading", data_left, "bytes =", tdata
 

   def writeSerial(self, payload):
      print "Writing Payload"
      self.serial.write(payload)
      print "Wrote", payload
      time.sleep(5)
	
   def testClock(self):
      while True:
         value = randint(1, 95)
         print "Sending value", value
         self.serial.write(value)
         time.sleep(1)

   def startThread(self):
      try:
         self.writeThread = threading.Thread(target=writeSerial, args = ("Hello World")).start()
         self.readThread = threading.Thread(target=readSerial).start()
      except:
         print "Error: unable to start thread"
 
   def test(self):
      print "Hello"

   def stopThread(self):
      self.writeThread.stop()
      self.readThread.stop()

print "Hello World!"
test = Serial("/dev/ttyAMA0").writeSerial("Hey")
