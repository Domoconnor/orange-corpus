import serial, threading, time
 
def test(): 
    print "Testing thread"

print "Hello World!"
threading.Thread(target=test).start()
