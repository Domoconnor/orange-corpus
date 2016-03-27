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

The hub acts as the coordinator for all the data going through pour network. It sits in our clients house wired into the internet and power to make sure that it is constantly running. It is always listening for data coming from our sensor and clock. If data is collected form either of our devices in the clients home the hub has to decide what to do with it. <span class="todo">I wrote this as a brief summary is it okay? what I wanted to do is break down the final version of the hub from what you have written into the sections below?</span>

The hub is comprised of multiple parts: [Board](#hub_board), [Communication / XBee](#hub_xbee), [Case](#hub_case)

######<a name="hub_board"></a>Board

The hub uses a Raspberry Pi Model B+ running Raspbian Jessie Lite

######<a name="hub_xbee"></a>Communication / XBee
######<a name="hub_case"></a>Case

#### Initial Premise

Unlike the sensor, power consumption was not an issue as the client said that we were able to be connected to a power outlet, also it does not have to be outside the clients premisses. This means we could use any feasible board for this role. We needed a board that could offer the most useful functionality towards our project.

The hub was required to be a middleman between sensors and the web server, forwarding traffic onto the website over ethernet and handling any heavy processing. Initially we planned on using an FRDM-K64F board due to familiarity and easy access to them within the University. 

#### Hub Hardware
#####Iteration ONE
######FRDM K64F

Image Here
(FRDM K64F Board)

The FRDM-K64F board had a lot of unneeded functionality. It has an unnecessary amount of sensors on the board itself such as temperature sensor and accelerometer. Although as previously stated we are testing this board because of its availability and our familiarity with it. Because we are familiar with the board we know that it has a shield that has the ability to interface with an XBee which is what we decided to use for our networking. <span class="todo">(insert link to networking decisions)</span> We are also comfortable programming the board. Including the shield in our hub would add yet more unnecessary features like another temperature sensor and potentiometers, but it would include an lcd which could be useful for displaying information back to our user. Having the shield could be considered a good thing because all of our components of the hub would interface together meaning we wouldn't have to wire anything up.

<p class="todo">Here I was going to include my case design implementation for the hub, but it went on for a while, would you like me to do that in its own page?</p>

####Research Into other Boards

#####Arduino Uno

Considering the Arduino Uno for the hub as a likely candidate for the fact that the board itself does not have any sensors that would be considered unnecessary like on the FRDM K64F. It is programmable in C much like the K64F so will essentially use the same code. The main reason for choosing this board would be to trim the unessential things from our current solution. Also, the Uno is a well known board that is well documented. 

Although unlike the K64F the Arduino Uno does not have an ethernet port built in. To remedy this we would have to add an Arduino shield such as the Arduino Ethernet shield. The shield while similar to the MBED Application shield provides the ability to transmit more than just data along ethernet, it could provide power too, although this means adding the PoE (Power over Ethernet) component. This added functionality means the possibility for less wires, this means easier instillation for the client as only one connection would be required. Also, there are libraries that exist to help use the shield and it’s functionality. The board offers a lot of useful debug information regarding current status with sending data, making it easier to work with.

With the problem of ethernet solved this only leaves connection to XBee out. In order to fix this we would have to either, include another [shield](http://uk.rs-online.com/web/p/products/6961670/?grossPrice=Y&cm_mmc=UK-PLA-_-google-_-PLA_UK_EN_Semiconductors-_-Semiconductor_Development_Kits&mkwid=s8484M9Xf_dc|pcrid|88057061283|pkw||pmt||prd|6961670&gclid=Cj0KEQjwid63BRCswIGqyOubtrUBEiQAvTol0WdagHobLZ9zO5iXOsR0-jdPUrM43OJ-dTZv86HIMcgaAkHy8P8HAQ) that had a breakout for the XBee or physically wiring up an XBee. Wiring up an XBee would require soldering the required pins on the XBee to wires that we could plug into the headers of the ethernet shield. If we choose to have the ethernet shield with the PoE module the XBee shield would probably not fit therefore we would have to physically wire it in (meaning we would not be able to reconfigure the XBee without desoldering it). If not we could use the shield meaning we could reconfigure the XBee at any time.

#####Micro Server

It is plausible to use a Micro Server in place of the Hub. The server could have a serial programmer connected to a XBee and use programs to read and access the data coming in. Using a Micro server would give huge benefits in terms of processing power, data storage and security. We could have our own choice of operating system and hardware. Data could come in and be backed up internally, then processed to be sent off. However price and size could cause issues, as these servers do not often come cheap and are a lot larger than other potential solutions. They can also be loud too and considering noise is what we are trying to help our client with it is probably not an ideal solution furthermore it would draw a lot more power than a development board meaning it could have a visible cost impact on the client.

#####Raspberry Pi

The Raspberry Pi is a well known mini computer in its own right and full of IoT uses too. Following on from the Microserver idea, the premise of having an operating system was very appealing. Especially the idea of being able to remotely access the Hub, in which both the Microserver and Pi could provide this. The Pi while being smaller and considerably cheaper than its Microserver counterpart did lack internal hardware to boot, but for the purpose we had planned it was more than adequate. It wouldn’t be noisy either. 

The Pi didn’t have as many Operating Systems to chose from compared to the Microserver (due to its Arm architecture) but it did offer a good selection of Operating Systems in terms of networking. 

Internal storage could be managed using a SD card of any size meaning data logging was possible as well. With this being built in as well as an ethernet port it has many advantages over the Arduino Uno. The only piece of hardware that is lacking for what we need is an XBee connection. Although solutions are the same as the Arduino Uno, either we use a shield with XBee breakouts or we physically wire an XBee up.

However with all this, the Pi did lack the speed of other boards that didn’t require a OS to maintain.

#####Conclusion

We decided to use a Raspberry Pi (Model B+ 512MB) over other solutions. While the Arduino and FRDM K64F boards offered speed, they lacked remote accessing and long term storage and would require more adaptions to work around this.The Microserver was too large, expensive and potentially noisy. The Pi offered a full operating system while maintaining a small size, better secure networking and remote access for updating on the network. This meant that if a bug was found in our code we could remotely update in on the hub, we would also be able to access any logged debug information from the program.

#####Iteration Two (FINAL)
######Raspberry Pi (Model B+)
We decided to use a Raspberry Pi (Model B+ 512MB). The Pi offered a full operating system, better secure networking and remote access for updating on the network. This means that if a bug is found in our code while the hub is deployed in our clients house we could remotely update in on said hub. In the same way we would also be able to access any logged debug information from the program.

######How to move forward with the pi

The Model B+ will be supplied by the university. The operating system of choice was Raspbian Jessie Lite because it is the officially supported OS of the Pi therefore, recommended by the developers of the Pi. The Pi will have to be connected to the XBee over serial, however in order to use these ports they had to be masked by systemd to force them to be free on startup. 

Then we need to write a program capable of handling incoming AT packets from serial, interpret them and respond accordingly. <span class="todo"><- link to code for this</span> 

This program was written in Python 3 as its easily available on the Pi and offers all the functionality required to create a robust networking program. We then modified to /etc/rc.local to contain “sudo python hub.py” so that the script would start every time the Pi was started. If the network was down, or errors occurred on transmit then the Pi would save data locally, and retry on its next attempt.

####Language of Choice: Python <span class="todo">is this description of code or why python was chosen?</span>

We used Python to program the Pi and handle incoming data from serial as well sending data over the internet. In order to read over serial, we used a library called PySerial and to send GET and POST requests to a web server we used a library called Requests. These simplified any complications we may have had from writing our own initial libraries as well as having organised documentation to support them. Python was also an easy language to understand compared to C, which can become confusing to someone who is not familiar with it. Python is formed so that someone will little programming knowledge could understand it.

####Coordinator on Network

The Hubs most important role was that of the coordinator on the network, it was the centre point. Due to how XBees address each other, it was very easy to send data straight to coordinator using its predefined 64bit address (0x0000000000000000).  The Hub could address any node on the network and with this could determine which nodes were which and if they were still within range.

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

~~~python
# Send message with API, sensor1 lets the API know which 64bit
# address we’re looking for, returns successful or not
response = xbee.sendMessage("sensor1", "Hello World")
~~~

Sending ‘sensor1’ - “Hello world!”, the program will fetch the associated 64bit address of sensor1.






