<style>
	.todo{ color:red }
</style>

#Orange Street

### <a name="hub"></a>Hub [cont.](#contents)

Image Here
(The finished Hub, requiring only ethernet and power it is capable of coordinating the entire network.)

The Hub, a Raspberry Pi Model B+ running Raspbian Jessie Lite, is the coordinator on the network. All traffic is sent to it. It handles data coming in from the sensor and requests from the clock. The clock can request decibel averages of the past 24 hours using the Hub as a middleman, the Hub then forwards this request to the web server and returns the result to the clock. The sensors submit their sampled data to the hub in order for this to then be sent forward to the web server. 
The Hub takes into account that it may not be able to reach the web server for various reasons, and will try multiple times to connect. If it fails with sensor data it will save this in the SD card on the Pi, if it cannot request data for the clock it will return an error instead and the clock can react accordingly. 
Upon a series of failed attempts, once a successful attempt is made the Hub will transmit all stored data and delete it afterwards to clear space in memory. 
The Hub was able to handle data coming in from multiple sources at once, packet fragmentation and assembly and identifying nodes on the network.
The Hub required a case that could the XBee module in, we 3D printed a case that could handle this requirement and leave space to fit other modules in as well.

#### Initial Premise

The hub was required to be a middleman between sensors and the web server, forwarding traffic onto the website over ethernet and handling any heavy processing. Initially we planned on using an FRDM-K64F board due to familiarity and easy access to them within the University. 

#### Hub Hardware

Image Here
(FRDM K64F Board)


Unlike the sensor, power consumption was not an issue so we could use any feasible board for this role. We needed a board that could offer the most useful functionality towards our project.

The FRDM-K64F board had a lot of unneeded functionality. Although it has the ability to interface with an XBee via pins on an application shield which connects to the K64F. We decided to use a Raspberry Pi (Model B+ 512MB) over the K64F. The Pi offered a full operating system, better secure networking and remote access for updating on the network. This meant that if a bug was found in our code we could remotely update in on the hub, we would also be able to access any logged debug information from the program.

####Pi (Model B+)
The Model B+ was supplied by the university, the operating system of choice was Raspbian Jessie Lite as it was recommended by the developers of the Pi. The Pi is connected to the XBee over serial, however in order to use these ports they had to be masked by systemd to force them to be free on startup. 

Then we needed to write a program capable of handling incoming AT packets from serial, interpret them and respond accordingly. This program was written in Python 3 as its easily available on the Pi and offers all the functionality required to create a robust networking program. We then modified to /etc/rc.local to contain “sudo python hub.py” so that the script would start every time the Pi was started. If the network was down, or errors occurred on transmit then the Pi would save data locally, and retry on its next attempt.

####Language of Choice: Python

We used Python to program the Pi and handle incoming data from serial as well sending data over the internet. In order to read over serial, we used a library called PySerial and to send GET and POST requests to a web server we used a library called Requests. These simplified any complications we may have had from writing our own initial libraries as well as having organised documentation to support them. Python was also an easy language to understand compared to C, which can become confusing to someone who is not familiar with it. Python is formed so that someone will little programming knowledge could understand it.

####Coordinator on Network

The Hubs most important role was that of the coordinator on the network, it was the centre point. Due to how XBees address each other, it was very easy to send data straight to coordinator using its predefined 64bit address (0x0000000000000000).  The Hub could address any node on the network and with this could determine who nodes were and if they were still within range.

<p class="todo">insert picture system diagram pi with zigbee</p>

####AT Mode 
Image Here
(1 sensor to Hub to the server. Hub reads in all data it receives which is only from one source, no errors.)

Initially we used AT mode for working with one sensor, however problems would soon arise when we planned to add multiple sensors to one our network. The problem was that it would become impossible to identify who was sending data causing different sensor readings to become mixed up across transmissions. Using one sensor was fine because only one source of traffic with sensor readings was expected, the clock wouldn’t interfere as this was a different format of data. The solution to this was to expand into API mode, which allowed us to identify individual sensors on the network and solve this particular problem

Image HERE
(Multiple sensors to Hub to server, Hub reads in data without knowing sources, data is merged together and becomes inoperable.)


####API Mode

With AT mode packets were formed for us and the payload was the only part we submitted in forming it. This lead us into problems as we would not be able to access information in the packet header that could be crucial to determining who sent the packet and other details. 

With API mode we were able to form the packets entirely ourselves, however this meant we required an API to handle this for us, which is what we set out to create. The API we created was able to determine different destinations, sources, error checking and packet fragmentation We had to work with the packet format the XBee expected which was found in its data sheet. This also gave us the ability to work with different types of packets such as status packets which gave us the insight of knowing whether a packet was received or not. 

The written API could handle multiple packets at once and organise them according to their sources. We could also handle packet assembly and fragmentation, so large payloads would no longer be an issue.

(Multiple sensors to Hub to server, Hub reads in data using API provided and is able to distinguish incoming packets and sources.)
 
However the XBee did not accommodate packet fragmentation itself, so in order for this to work we had to manually number each packet from each source when being fragmented and sent across the network. We also needed to be able to determine which was the final frame, this was done using an ‘!’ character, which would never naturally appear in any of our normal packets. 

Image Here
(Showing simple-flow approach to packet fragmentation. Message is split into frames, each frame is acknowledged when received and the process repeats until all frames are received successfully.)

####Node Discovery 

Being able to determine what sensors already exist on a network would offer us much more functionality. We would be able to ping nodes on the network and offer more functionality in the written API to message individual nodes. 

On startup the program running on the hub would find every current node on the network and save them. It will also load from memory any nodes it has previously found. This way, it could determine if a node was missing (Maybe a sensor was moved) and could report this back to the client. The hub would periodically send heartbeats across the network to see any changes on the nodes. If a change was detected (such as a node disappearing) it would report this back to the server, this way we could display on the website that a sensor was out of range or had run out for battery. 

With node discovery it simplified sending messages from the coordinator to sensors, instead of requiring individuals addresses. You could pass names of nodes into the “sendMessage” function and it will conclude the address based on this.







