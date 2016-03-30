##Clock
###Description

![Final Clock](Images/Clock%20Images/clock_final.jpg)


The clock is our form of ambient data visualisation, and is designed to engage and notify the user. It is the physical counterpart to our front end visualisation, and uses a simplified system of visual data to represent noise levels. It is designed to complement the more technical premise of the web server. 

It uses a series of 24 LEDs arranged in a ring, which, every hour are lit to a colour corresponding to the average sound levels for that hour. This is a lightweight way of giving the user a quick glance at the sound levels, and allows for comparisons and references to be made across a 24 hour period. 

The light display is handled by an Adafruit NeoPixel Ring 24 x WS2812, which is interfaced through an Adafruit Flora used as the microcontroller. The interaction of the clock with the rest of the system involves an XBee device configured as a router. Resultantly the clock can receive values from the hub, and stay up to date in terms of the data it is presenting.  
Every hour, the clock communicates with the hub to receive the average sound level across that hour. The clock turns on a light for that hour, depending upon the corresponding sound level. Over time, this builds a picture of the day’s sound activity, mirroring the data visualisation on the web server as a physical model. 

Components: Adafruit NeoPixel Ring 24 x WS2812, Adafruit Flora, Communication/XBee (Lilypad XBee), Case. 

####Adafruit NeoPixel Ring 24 x WS2812

The central hardware component of the clock is the Adafruit NeoPixel Ring. One of several NeoPixel models provided by Adafruit, the 24 x WS2812 is a collection of 24 addressable LEDs arranged in a ring. The LEDs were directly addressed by the Arduino code written for the Adafruit Flora, allowing direct control over the display, and timings that each LEDs came on. 

####Adafruit Flora

Lightweight and circular in design, the Adafruit Flora was an effective choice for maintaining the streamlined structure of the clock’s components. Since it is typically used in wearable tech, the Flora is a microcontroller which is smaller than the NeoPixel Ring. This meant the overall size of the clock could be kept compact, allowing more focus to be on the visual display of the NeoPixel Ring. Moreover, it offered the functionality we needed of similar microcontrollers such as the Arduino Uno, but stripped away the unnecessary features. Since the clock device could be powered by mains, the power consumption was not too much of an issue. 

####Communication/XBee (Lilypad XBee)

As with the other devices in the network, the clock communicated using the Zigbee protocol; using an XBee RF module attached to its microcontroller. It was configured as a router on the network, allowing it to receive the data transmission it required from the hub. Through the iterations, the XBee was interfaced using either a straight connection in the RX/TX ports, or through a Lilypad XBee board. 

####Case

The clock’s hardware components are housed in a 3D printed case. As well as maintaining its security, this feature allows the clock to be seen more clearly; using a base to keep it upright. As a result, the clock can be viewed like most normal clocks, and from a multitude of angles in a room. The transparent covering holds the components in place, and optimises the appearance of the lights for viewing by using a frosting film. This was used to prevent glare from the LEDs, and to clearly distinguish one light from another. Since the clock is unique in appearance, it was necessary to develop a case which served its requirements and matched its specific dimensions. Towards the later iterations, the case underwent several changes, and was finalised with the above appearance.    

###Previous Work

####Iteration 1: Design and concepting phase
Since we have decided upon a web based method of visualising data, we want to explore several other means for outputting data to our clients. To engage more with the user, we want to explore methods of ambient data visualisation. 

From our bank of data visualisation ideas, the “clock” design incorporates the use of a coloured light system and a clock face display. The clock would receive the average noise level on the hour, and mark it on its face as a coloured segment. Over a 12 hour period, this would produce an overall chart of ambience. To get coverage over 24 hours, we would have two separate clocks displaying data for AM and PM. 

One option for this would be to involve the clock display in the website visualisation; offering the client a more ambient counterpart to graphs and charts. Since a few of our data visualisation for the five sketches phase featured a crossover of similar clock ideas, it is worth us looking further into how we could combine our sketches.  Since the clock design is simple, it could work quite effectively alongside more technical data formats. 

We could also implement something physical in hardware, which could be read similarly to a clock which tells the time. We discussed a few scenarios in which this would prove useful. Firstly, if a client returned home after being away from the house all day, a quick check of the clock could provide a straightforward spread of activity during their absence; drawing their attention to colours of greater intensity. 

In both cases, the red and orange lights could serve as flags to the user, as they indicate a high concentration of noise activity picked up by the sensor. Meanwhile, the lighter colours provide coverage for quieter hours. This offered the user a complete coverage of each 24-hour period, allowing the possibility to view previous hours and draw comparisons between them. 
Overall, we felt that there was an advantage to having a physical clock, as it is a physical artefact and therefore has greater potential to engage with the user. Furthermore, it could provide effective reinforcement to the data displayed on the web server. 

#####Lo-fi prototyping and sketches
In order to visualise a few different clock concepts, we created some sketches of the clock being represented in different ways. This was a way of gauging how the interface for the clock should look, as well as exploring some aspects such as colour, granularity, and the general visual layout for the user. 
Some of the design sketches we produced later in this iteration explored the placement of a clock as a “widget” on a tablet or webpage. Since our client could rely on mobile or tablet, we also concepted how our designs could be scaled and combined depending on where they are displayed. 

####What we need 
The premise behind the clock is to provide a visual stimulus to the user in a simplified data format for quick reference. It also needs to be interconnected with other devices on the network to accurately display data. Since the device is going to be running a series of lights, it is likely that power usage will be high; which is a consideration for how it will be powered in the user’s home. We also need to decide what sort of hardware we are looking at using to implement this idea, and what limitations and/or advantages each particular technology would give us. The main requirements of the clock are therefore: 
To provide an ambient visualisation of data which is engaging with the user 
Be easily implemented with the rest of the system 
Display data in a format that is easily grasped by the user
To have a feasible hardware solution which complements our other means of data visualisation

![Sketch 1](Images/Clock%20Images/IMAGE_1.png)

	Initial design sketches of the clock. Early iterations of the design featured a dual 12 hour display to represent AM and PM time notations respectively. 

![Sketch 2](Images/Clock%20Images/IMAGE_2.jpg)

	Cardboard prototyping of the clock, and sketches of data formats. The cardboard prototype uses coloured panels to represent hourly averages. Using these, we established a colour spectrum to use for the physical display. The right side image explores how averages are processed and visualised.  

![Sketch 3](Images/Clock%20Images/IMAGE_3.jpg)

	Exploring data continuity. The presence of the clock as a simplified data format complements the more technical aspects of the graphs and charts that we concepted. 

![Sketch 4](Images/Clock%20Images/IMAGE_4.jpg)

	Design sketch for clock display options. In this sketch, we looked at the block sizes for data; whether we would work in 10-30-60 minute intervals. We also considered how this format could also be translated into a webpage display.  

![Sketch 5](Images/Clock%20Images/IMAGE_5.jpg)

	Design sketch for the clock on a webpage, or tablet. Since we wanted the data available on different formats, we started to consider how we could scale different designs together. 


This device would in a sense act as an notifier to be coupled alongside the more detail-specific web server, and is designed to be more attention drawing. This was prototyped initially in lo-fidelity using card and coloured paper to simulate time segments, allowing us to explore how frequently data would be output to the clock. Through this prototyping phase, we began to develop our colour spectrum, and specifically how attention can be drawn to noisier time periods. As well as this, we considered whether updates would be formatted as 5/30/60 minute chunks, and how this could be replicated in hardware. 


####Outcome of Iteration
We have produced several different design proposals for the clock, and have began to consider how a physical device could be produced. We have evaluated what benefits the clock can bring to the project, in that it reinforces the more accurate data and makes for an engaging notifier for the user. There is also potential for this to create data continuity - in the sense that data from a physical device can be cross referenced with that on the web server. Overall, this iteration has set up the requirements for the clock, and given us a few interesting paths to take when developing it. 

####Iteration 2: Hardware and setup phase

After having collected our ideas from lo-fi prototyping, we are now exploring how our clock system can be physically implemented with hardware. 
The last iteration saw us investigating some requirements regarding the clock’s transition into hardware. This iteration involves our research into hardware, and comparisons between methods of implementing the system. 

#####Adafruit NeoPixel Ring

![clock models](Images/Clock%20Images/clock_models.png)

	Hardware models for the Adafruit NeoPixel Ring. Above, from left to right are the 24, 16 and 12 LED models. During the project we considered using various sizes, ultimately deciding upon the 24 x WS2812 (left). 

We were directed towards the tech solutions offered by Adafruit (https://www.adafruit.com) which distributes the NeoPixel product; an assortment of addressable miniature LEDs arranged in rings, strips and boards (https://www.adafruit.com/category/168). We feel that this is a good platform for developing our system in hardware.
The Adafruit NeoPixel device is a chainable collection of LEDs which can be interfaced with the NeoPixel Arduino library for support. Example code provided with the library demonstrated several of the device’s capabilities; notably the ability to manipulate timings of individual lights to come on. Conveniently, this was exactly what we were looking for as it provided a loose way of interfacing more complex tasks if we needed to. 

The setup of this device requires the use of a breadboard to interface the NeoPixel ring with an Arduino Uno microcontroller, and the use of a PC to upload code from the Arduino libraries to the Uno. After setup, our first concern was to establish the range of colours we could use to recreate our “ambience” colour spectrum.

We then displayed a spectrum of our proposed colours running from white (least ambient) through green, yellow, and orange to red (most ambient) recreating this colour wheel using the addressable LEDs. 

####Display Model
During our concepting of the clock display, we came up with several different possibilities of data accuracy that we could 
use. The main two directions for this were inspired by the 24 and 60 LED NeoPixel models respectively. 

#####24-Hour Display
The go-to approach that we looked into involved the 24-hour display clock, which averaged data over hourly periods, potentially transitioning to sleep mode between readings to save power. Adafruit’s solution to this offered an LED ring of 2.6” diameter; which is a relatively small display and could be mounted onto a small case or hub and unhooked for inspection. Early low fidelity prototypes of casing for this were modelled using cardboard, with emphasis being placed on the majority of the face being easily visible.  

#####Hour-By-Hour Display
There are also considerations to use other models of NeoPixel Ring. Of note is the NeoPixel Ring 60 x WS2812 model which offered 60 addressable LEDs; with which we can update more frequently to give an hour-by-hour display. A light would come on every minute after the averaged sample data was sent to the device until all 60 were lit; at which point it would rollover 
for the next hour. 

This idea could be combined with an LCD real time digital clock to keep track of which hour the data was referring to. This kind of display could also be interfaced with the clock itself to serve as the rollover point to be synched with the pixel 
reset at each hour. 

####NeoPixel Library and Code Iterations
After having chosen the NeoPixel 24 LED model, we have began to interface with the Arduino library to build a test program. 
From our test program, we intend to evaluate the capabilities of the NeoPixel Ring, and determine whether it could be used for our clock system. 

So far, we have found we can address individual LEDs and their brightnesses, and manipulate timings that certain lights come on. We are also looking into how we could implement our colour spectrum into the system, including the range of colours the hardware offers us. 

We knew the device would somehow have to read in data from our system. Writing a couple of test programs explained below, we require a data reading component to read in decibel values and convert them to a corresponding light
Reading clock data from a file
Initially, we constructed a program using the “Processing” IDE to work as a simple file reader which transmitted data via serial. Interfacing this with the microcontroller, a set of arbitrary values ranging from 0-9 were read into a switch statement on the arduino; 0 representing low ambience with a white light, and red expressing high ambience upwards towards 9.

![Neopixel Ring](Images/Clock%20Images/IMAGE_7.jpg)

	Adafruit NeoPixel Ring 24 x WS2812. Here the ring is powered by an Arduino Uno, and displaying a range of colours. The rings comes with adjustable brightness settings, and each LED is individually addressable. 

The code for this iteration can be found here: [Clock_Cycle_V1b]

#####Reading clock data from a pre-programmed array

Since the clock will be working with real values, we investigated the ways that we could test it without interaction of the real system. This would involve using dummy values, and setting 
A separate program we developed involved reading in dummy values from a pre-programmed array. The program would iterate through a size 24 integer array (consisting of integers from 0-100), and transfer data to a corresponding colour scale in the “setHourColour()” method. To fall within the case statements 0-10, each value was divided by 10 so that it would match a corresponding statement. The index positions of the array, which ranged from 0-23, matched each “hour” that the clock was displaying data for. This way, the clock display was to start from midnight, and iterate round to 11pm providing data coverage for all hours in between. 

The code for this iteration can be found here: [Clock_Cycle_V1b]

![setHourColour Code check](Images/Clock%20Images/IMAGE_8.png)

	Arduino code for “setHourColour()”. If the value exceeded -1 (which was always true unless an error case occurred - see below) then it gets divided by 10 to match the case statement. 

![Dummy code](Images/Clock%20Images/IMAGE_9.png)

	Arduino code for displaying “dummy” data lights. The loop() method simply iterates through the array of dummy values called “clockValues[]”, takes each individual value and converts it to a colour based upon which case it falls into. 

This simple setup will be the basis of a more complicated program, which will involve reading data in over serial, averaging values across an hour’s worth of data and turning on a light. This method of doing things was relatively straightforward to implement once we knew what form the data being transferred to the clock was in.    

For our data to be accurately represented, we had to somehow establish the colour spectrum which we developed in the initial design phase of the clock. Having looked into the NeoPixel library, the main method for handling the colour of individual LEDs was the “setPixelColor()” method, which took 4 parameters. Firstly, the position of the pixel you are addressing, and then RGB values for the colour. 
We determined our RGB parameters by using a HTML colour picker, which allowed us to pick and particular colour and read off the values. Using this, we established each of different parameters corresponding to the colours in our spectrum.  

![Colour picker](Images/Clock%20Images/IMAGE_10.png)

	We chose the colours using a HTML colour picker. Since the NeoPixel Ring method, “setPixelColor” requires RGB values for arguments, we determined which colour values to use based off of this website. (http://www.w3schools.com/colors/colors_picker.asp) 

####Simplifying the colour spectrum

Initially, we found the parameters for 10 different colours which would be used in progressively more intense hues. We will potentially reduce this to 6 different colours which provided the clock with better granularity. 

![Colour Spectrum 1](Images/Clock%20Images/Colour_spec_comparison.png)

<img src = "Images/Clock%20Images/Colour_spec_comparison.png" align = "middle">

	Simplified colour spectrum. Going in a clockwise 
	direction, the colour converges more towards red, 	hinting at greater noise activity. The right image 	is displaying data for arbitrary values to test the 	granularity between colours.

The code for this iteration can be found here: [Clock_Cycle_V1b]

#####Colour-blindness spectrum 

There is an issue with using purely colour based visualisation. When catering for users who might have trouble distinguishing between colours, there is particular difficulty with telling the difference between green and red. Since our spectrum uses this two values as lower and upper bounds, it would be particularly problematic if the user couldn’t tell them apart. 

A method we could use is an intensity spectrum. Choosing one particular colour, the noise intensity would instead be represented by the intensity of each colour shade. For example, with red, quieter hours would be represented with very pale shades, and louder hours by more intense shades. 

![Colour intensity 1](Images/Clock%20Images/Intensity_spec_comparison.png)

<img src = "Images/Clock%20Images/Intensity_spec_comparison.png" align = "middle">
		
	NeoPixel Ring displaying the intensity spectrum. 

#####Colour intensity spectrum. 

Similarly to the colour spectrum, the intensity increases as greater noise intensity values are read in. We have opted for red here, but it can be implemented in any colour.

We felt having the option to display data in these varying formats could be useful to the user, and opens up possibilities for new ways our visualisation could be implemented. There are potentially ways that these two formats could be used in conjunction.

The code for this iteration can be found here: [Clock_Cycle_RedIntensity]

####Problems

We faced some issues in this iteration based upon our hardware choices. Although only used for prototyping, the Arduino Uno board has a lot of functionality which the clock doesn’t require, when ideally we want to condense down and use something simpler. Furthermore, dimensions wise the Uno is quite bulky - which may present further issues concerning the casing of the clock. Another problem concerned the starting point of the first LED that is lit. Since the NeoPixel Ring LEDs are addressed by the arduino code using integer index position, the starting LED, which remains fixed at 0, has been a current issue to change. If we can’t change the starting position, there could be potential problems regarding the orientation of the clock. For example, would we have to always have the clock at a fixed orientation? What would happen if it had to be rotated somehow? 

####Outcome of iteration
After this iteration was completed, we had managed to set up the NeoPixel ring to display some spoofed data values. This is promising as far as the full implementation of the clock goes, as we can now use this data format for structuring communications between the clock and other devices. Furthermore, we have decided upon a direction to take the hardware choices. Currently the clock is running off of an Arduino Uno as the NeoPixel ring is supported by Arduino code, but since it won’t be battery dependent, there is room for other microcontrollers to be considered. Also, this iteration has provided some interesting issues for us to consider; which we intend to solve in future iterations. 

####Iteration 3: Interlinking phase

####Adafruit Flora
To alleviate the issue of the Arduino Uno, we decided to change our board choice to the Adafruit Flora; a much more compact device. This significantly reduces the dimensions of the clock components, leading to a much more streamlined layout. This changeover will be particularly important for when we consider case design; during which a more condensed layout will be favoured. Furthermore, the Flora offers us the same functionality required of the Arduino Uno, minus the unnecessary features. 

####Interfacing with XBee and Networking
After we had successfully set the NeoPixel ring up to display some dummy values, and having decided upon a colour spectrum in our last iteration, our next task is to integrate the clock with the rest of the network.

The networking involved hooking up the XBee device to the Adafruit Flora microcontroller using the RX and TX ports, allowing the two devices to communicate over serial. The XBee was attached to an Lilypad board at this point, allowing for easy interfacing with the microcontroller. This was simply to keep the XBee in place. 

![Systems communication](Images/Clock%20Images/IMAGE_15.jpg)

	Hardware setup for clock. Above is the clock interfaced with the Adafruit Flora microcontroller, which, in turn is interfaced with the lilypad board.  

####Networking with the clock

To establish the clock device communicating over a network, we are going to start by writing simple sender-receiver code. This will be uploaded to the clock and a separate microcontroller - both of which will be  interfaced with XBees, so that messages can be sent back and forth between them. This is intended to simulate how clock would communicate with the hub, and pick up on any errors in transition that we may encounter. This will utilise a simple acknowledgement based format, which we could potentially use as foundation for how the clock requests hub data on the hour.

This sender-receiver code will then be implemented into the clock’s real interaction with the hub. The clock will send a request (formatted as “R:!”) which will then be accepted by the hub. The hub  then sends the data over in an integer array - which will be used to populate the clock’s “clockValues[]” array for storing data. 

The code for this iteration can be found here: [Receiver_Code]

![Systems communication](Images/Clock%20Images/IMAGE_16.jpg)

	Communication between the clock,  hub and web server. Once data from the web server has been sent to the clock, the clockValues[] array is populated with the values. 

![Clock hub communication](Images/Clock%20Images/IMAGE_17.png) - 
	
	Arduino code for the prototype clock-hub communication. This involved us establishing serial connections to the XBee device, and reading in values that were received from the sending XBee interfaced with the hub. The hub was simply configured to send the same pre-programmed array values over the network.

####Signposting with the clock
The clock, being a very visual component in the system, should implement some form of user signposting. Before the data display phase begins, we discussed adding a few intermediary stages to show the clock transitioning between states - if for some reason it has trouble reaching the data. 
IMAGE 18 - Clock display. This shows the clock reading in a value every minute from the hub, and plotting it as a light. The architecture pictured shows the NeoPixel ring, Adafruit Flora, and Lilypad interfaced together. 

![signposting flowchart](Images/Clock%20Images/IMAGE_19.png)

	Signposting flowchart. This chart shows that for every reading the clock takes on the hour, it runs the initialisation phase, and moves through the different signposts according to the state. 

We then planned what sort of signposting we might implement. This chart shows that for every reading the clock takes on the hour, it runs the initialisation phase. This phase consists of white lights circling round. After this, if data reading is successful, the first light is plotted. For subsequent readings, the appropriate states are reflected in the clock’s display. Before we implemented signposting, if there were errors in transmission of data, or communication to the hub, the clock would freeze its current display -  instead of reflect the nature of the problem. 

![Arduino error cases](Images/Clock%20Images/IMAGE_20.png)

	Arduino code for “error cases”. Here we introduced the specific cases which might occur. The comments clearly describe which case applies to which scenario. 

Once the modified case statement was developed, we tested the clock in isolation with specific error values, and observed the light output. This was to ensure that the signposting was effective, and clearly conveyed different messages. 

![case 1](Images/Clock%20Images/IMAGE_21.jpg)

	Display for error case 1. The clock outputs a white display of lights and holds it there for a few seconds. 

![case 2](Images/Clock%20Images/IMAGE_22.jpg)

	Display for error case 2 - if the hub cannot be reached. The clock outputs a red “colour wheel” of light to indicate that there is an error. 

![case 3](Images/Clock%20Images/IMAGE_23.jpg)
	
	Display for error case 3 - if the hub cannot be reach the server. The clock outputs a blue “colour wheel” of light to indicate that there is a problem.

The above cases show the clock displaying errors whilst working with dummy values, so our next stage is to make it work with the hub. This is fairly straightforward - we just have to send dummy data packets from the hub over to the clock over the Zigbee network to test it.

The code for this iteration can be found here: [Clock_Cycle_V1b] 

At this point, much of the clock’s functionality is working as intended. So far, we have tested the clock in isolation, and simulated its interactions with the hub device. We have also established a communication platform from our sender-receiver code, which we will adapt to integrate the clock into the system. 

The code for this iteration can be found here: [Clock_Cycle_V1]

####Integrating the clock with the whole system

Now that we have developed the main functionality of the clock, we have to integrate it with the rest of the system. To do this, we must carefully optimise a few of the clock’s features - such as wait times in between reading values; in order to synchronise it with other system events such as the sensor reading in data, or the hub communicating with the web server. This process involves refactoring some of the arduino code for efficiency reasons, and beginning to consider how we could use protective casing when it came to deploying the clock. 

Since the data format for the clock has already been decided upon, the integration of it into the system is more a matter for the other components. Here, there were discussions about how the web server could send packets tailored specifically for the clock via serial, whilst maintaining the format that the clock expects.

The first integration step was to adjust delay times: 

![delay code](Images/Clock%20Images/IMAGE_24.png)

	Arduino code for delays. The variables represent different lengths of time that we could delay the clock for between reading values, as determined by the number of miliseconds. 

The clock is designed to display average readings on an hourly basis. For the sake of testing its functionality over a shorter timescale, we are running the clock in shorter iterations; e.g. minute by minute displays (for a total of 24 minutes) and second by second delays (24 seconds). This reduced time whilst testing, and saved having to wait 24 hours just to see the output of a day’s data. 

There are currently further plans to test the clock over an extended time period, once it has been fully integrated with the whole system.

The code for this iteration can be found here: [Clock_Cycle_V2]

####Previous Problems

<ul>
<li> Arduino Uno board has a lot of functionality which the clock doesn’t require, when ideally we want to condense down and use something simpler. </li>
<li> Starting point of the first LED that is lit. Since the NeoPixel Ring LEDs are addressed by the arduino code using integer index position, the starting LED, which remains fixed at 0, has been a current issue to change. </li>
<li> Lack of error displays if e.g. the clock can’t communicate with the hub, data can’t be transmitted etc.</li>
</ul>

Early in this iteration, we moved from our choice of board for prototyping; the Arduino Uno, over to a more concrete choice. The Adafruit Flora currently fits our needs for a stable, yet compact board, and has the added bonus of fitting inside the NeoPixel Ring. The Flora is compatible with our previous Arduino code, and has exactly the ports we need for interfacing with the NeoPixel Ring. This makes it a more efficient, and aesthetically suitable choice for the clock. 

We resolved the issue of the starting point by making a very simple adjustment to our code. For any iterative structures looping over the LEDs, rather than starting at position 0 (the first LED), we simply offset that number by an amount depending upon where we wish to start (- e.g. + 3 if we wanted to start from the third LED going clockwise), storing that in the “startpos” variable. When it came to iterating from this new start position, we iterated over the LEDs as normal, calculating the shift in LED indexes. (see code below).

To add a degree of error displays, we added a new light system for the clock to provide signposting. These operated similarly to other devices which use warning lights, and intended to direct user attention based on colour. 


![case 1](Images/Clock%20Images/IMAGE_25.png)

	LED index changes


####Current Problems

During this iteration, some of the main challenges concerned setting up the clock on the network, and maintaining the format of the data it received so as to not trigger errors. The clock uses a very specific format in which it expects data, so a particular challenge has been in normalising the structure of packets to match this expectation. Fortunately, however, if there are genuine issues regarding the web server’s connection to the hub, or the hub’s communication with the clock, we have established signposting to inform the user. 

####Outcome of iteration

After this iteration was completed, we had managed to set up the NeoPixel ring to display some pre-calculated data values. This is promising as far as the full implementation of the clock goes, as we can now use this data format for structuring communications between the clock and other devices. Furthermore, we have decided upon a direction to take the hardware choices. Currently the clock is running off of an Arduino Uno as the NeoPixel ring is supported by Arduino code, but since it won’t be battery dependent, there is room for other microcontrollers to be considered. Also, this iteration has provided some interesting issues for us to consider; which we intend to solve in future iterations.

####Iteration 4: Casing and finalisation phase

In the previous the functionality of the clock was integrated with the rest of the system in the previous iteration, 
Since the NeoPixel ring by itself is quite a fragile piece of hardware, it is necessary to build some form of casing to protect it whilst still maintaining its visibility. We came up with a few ideas for this using cardboard to easily mould shapes together; most of the principle designs consisting of a base and a clear perspex glass “face”, to protect the components. 

We also looked into how the device could be mounted, since ideally our focus was on its attention drawing aspect which would be less effective if it had to be picked up or consciously interacted with. This could be achieved with a clip or some form of hook for a wall mount possibility, or perhaps a subtle stand so as to not rely too much on modifying a client’s home to accommodate for it. 

####Designing the case

When it came to designing the case to house the clock, we have several things to bear in mind: 
<ul>
<li> It has to be robust enough to protect the hardware</li>
<li> Easy to mount and/or stand up</li>
<li> Of reasonable size</li> 
<li> Good visibility of the clock display</li>
<li> Feasible to manufacture/3D print</li>
</ul>
With these points, we set about producing some design mockups using google sketchup. Since we weren’t looking at modelling straight away, it was good to use this program to conceptualise some of properties of its general appearance.

#####Iteration 1


![Design 1 a](Images/Clock%20Images/IMAGE_26.jpg) ![Design 1 b](Images/Clock%20Images/IMAGE_27.jpg)

	Sketchup designs of first prototypes. The general shape of the case is established here. The isometric view on the left shows the layers where the NeoPixel Ring could sit.

In this iteration we designed the general shape of the case, and considered a transparent perspex “face” to promote the visibility of the lights. It was designed so the NeoPixel Ring would fit securely around the inner ring, with a space in the middle for the Flora to sit. The purpose of the base here is twofold. Whilst it doesn’t yet stand up, the base holds the components for the XBee module, and features a detachable back.  

#####Iteration 2

![Design 2 a](Images/Clock%20Images/IMAGE_28.jpg) ![Design 2 b](Images/Clock%20Images/IMAGE_29.jpg)

	Iteration 2. Here we began to establish how the case could use a stand to support the clock, and make the viewing angle easier. 

This iteration features our first implementation of a stand. This is important to the evolution of the clock, as it greatly increases visibility of the lights, and therefore aids the user’s engagement with it. The stand here is fairly small, so in future design iterations we will have to consider making more robust changes.

#####Iteration 3

![Design 3 a](Images/Clock%20Images/IMAGE_30.jpg) ![Design 3 b](Images/Clock%20Images/IMAGE_31.jpg)

	Iteration 3. This design uses a pull out stand which would potentially provide greater stability than the stand in the previous iteration. This would also be a useful feature for wall mounting the clock. 

This iteration implements a more sturdy stand to keep the clock upright. We were considering having a flip out stand, which can be put away based on user preference. Besides that, much of the general design is the same. 

#####Final iteration

We finalised our case design to have a more sturdy base and used the 3D printer to construct it. The final case consisted of three major 3D printed parts which slotted together. For more information, see casing. 

####Previous Problems
Setting up the clock on the network, and maintaining the format of the data it received so as to not trigger errors. 

We solved this issue this iteration by incorporating a strict data format that the clock received values in. This was an integer array of 24 values, containing sound averages for each hour of the day. This format was utilised by the hub; meaning that when sending data, the clock received it in a format it “understood”. 

####Outcome of iteration
At the end of this iteration, we had successfully developed a case for the clock; precisely matching its dimensions and storing all the necessary components. 




