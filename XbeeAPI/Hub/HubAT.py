
#!/usr/bin/python
 
# Try to send via post
# If failed, receive then save on disk
# Next attempt try to send again
# Each time data is sent request latest average
# Send average to Jack

# Clock messages
# -2 Means that there is no average for this hour
# -3 Means unable to connect to the server

# Testing...
# Test sensor sending data to hub and forwarding onwards
# Test clock asking for hour to hub and hub asking server and backpedaling to clock
# Test failing to reach server and sending clock -3
# Test failing to reach server and sending updated post payload
# Test failing to reach server but connection reestablished
# Test concat sensor data from file
# Test splitting by \n

# When receiving data from GET should ONLY be the value and nothing else
# No fancy bits, just a blank page and the response in text for the script to scrub

# Start up details are in /etc/rc.local 
# Much use 'which' command to determine absolute location of commands/scripts
# Also access as root aka sudo 
 
import random, serial, time, threading, requests, os
 
class HTTPConnection:
 
   def __init__(self, host, port, postURL, getURL, getTimeout, fileName):
      self.host = host
      self.port = port
      self.file = fileName
      self.getURL = host+getURL
      self.postURL = host+postURL
      self.getTimeout = getTimeout

   def getClockHourAverage(self):
	print "Fetching clock average for hours."
	try:
		request = requests.get(self.getURL)
		timeout=0
		while request.status_code != 200 and timeout < 5:
			request = requests.get(self.getURL)
			timeout+=1
			time.sleep(5) # Try 5 times in 30 seconds
		
		if timeout == 5:
			print "Failed to reach server."	   
	   		return "-3" # Can't reach server
		else:
			print "Returning data..."
	   		return request.text
	except:
		print "Failed to get data from getURL:",self.getURL
		return -3

   def sendToHost(self, payload):
      postPayload = ""
      if (self.isFile(self.file) and self.is_non_zero_file(self.file)): #If there is previous data stored on file
         f = open(self.file) 
         postPayload = f.read()
         f.close()
         os.remove(self.file) # Delete file
         print "Retreived backlogged data... deleted file."
 

      postPayload+=payload
      print "Payload:",postPayload
      
      try:
      
	      r = requests.post(self.postURL, data={"data":postPayload}) 
	 
	      #if r.status_code != 200:
	      if random.randint(1,5) == 3:	      
	         # Failed to reach server
	         # Save to memory
		timeout=0
		#while timeout<5 and r.status_code != 200:
		while timeout<5 and random.randint(1,20) == 3:
			timeout+=1
			r = requests.post(self.postURL, data={"data":postPayload})
			time.sleep(5)
	
		if timeout == 5: # Failed to reach server after 5 attempts
	           with open(self.file, 'a') as f: # Append to file
	         	f.write(postPayload)
		   print "Failed to reach server...",r.url,"-",r.status_code
		   return
	        print "Managed to transmit data."
	      else: 
		print "Successfully sent payload to server."
		return # Ideally change
	        response = requests.get(self.getURL) # Get clock average
	        if response.status_code != 200: # Server is offline
	            timeout=0
		    while timeout < self.getTimeout and response.status_code != 200:
			# Start timeout to contact server
			# 
			print "Failed to get response from server, attempting again."
			response = requests.get(self.getURL)
			timeout+=1
			time.sleep(10)
	
		    if timeout == self.getTimeout:
			print "Failed", self.getTimeout, "times to contact server for clock reading."
		        return "-3"
		    else:
			return response.text
			   
	        else:
	           print "Successfully managed to retrieve clock reading."
	           return response.text 
      except:
		 print "ERROR 103 - connection aborted no route to host"
		 with open(self.file, 'a') as f: # Append to file
	         	f.write(postPayload)
	         print "Saved data to file due to failure, will reattempt on next pass."

   def is_non_zero_file(self, fpath):  # Is the file empty
      return True if self.isFile(fpath) and os.path.getsize(fpath) > 0 else False
   
   def isFile(self, fpath): # Does the file exist
      return True if os.path.isfile(fpath) else False
 
class Serial:
 
   # Class constructor
   # Takes serial port parameter
   # Constructs the server connection
   # starts a thread
   def __init__(self, usbdev):
      self.usbdev = usbdev #default serial port (ttyAMA0)
      self.serial = serial.Serial(usbdev)
      #self.httpCon = HTTPConnection("http://178.62.43.107/orange/api", "80", "/readings?key=611f13f1-92ac-4b28-9f38-0834a8ee67bd", "/get.php", 10, "Failed.txt")
      self.httpCon = HTTPConnection("http://raptor.kent.ac.uk/~dja30", "80", "/post.php", "/get.php", 10, "Failed.txt")
      self.startThread()
      self.blockingClockRequest = False
	

   # Used
   # Reads data incoming from serial
   # Will talk to the web server and clock from here
   # Determines what to do with data coming in
   def readSerial(self):
      while True:
      	     # decibels = self.httpCon.getClockHourAverage()
	     # print "Returning...",decibels
	      self.serial.flushOutput() # Get rid of any incoming/outgoing data
	      self.serial.flushInput() 
	      print "Waiting for serial input..."
	      endbyte = self.serial.read()           # Wait forever for anything
	      print "Received, forming buffer..."
	      tdata = endbyte
              print " >",endbyte
              while not endbyte == '!':
		 tdata+=endbyte
		 endbyte = self.serial.read()

	      print "Finished reading", tdata, "bytes =", len(tdata),"."
 	      self.serial.write(tdata) 
	      self.requestFromClock = False
	      if "R:" in tdata:
		 print "Detected clock request..."
		 self.requestFromClock = True
		 tdata.replace("R:","")

	      if self.requestFromClock == True and not self.blockingClockRequest == True: # Clock has requested data
		 self.blockingClockRequest = True
		 decibels = self.httpCon.getClockHourAverage() #Request decibel values from webserver
                 self.serial.write(decibels)
		 print "Responded with: ", decibels,"." 
		 self.blockingClockRequest = False
		 time.sleep(1) #Sleep to allow request to go through

	      if self.blockingClockRequest == True:
		 print "Blocking incoming request."
		 return
	      
	      # Send to web server
	      print "Sending to server..."
	      response = self.httpCon.sendToHost(tdata)
 
   # Unused
   # Was for testing serial
   def writeSerial(self, payload):
      while True:   	      
  	      
	      print "Writing Payload"
	      self.serial.write(payload)
	      print "Wrote", payload
	      #self.httpCon.testHost("Test")
	      time.sleep(5)
 

   def startThread(self):
         self.readThread = threading.Thread(target=self.readSerial).start()
 
   def stopThread(self):
      self.writeThread.stop()
      self.readThread.stop()
 
print "Starting..."
serial = Serial("/dev/ttyAMA0")