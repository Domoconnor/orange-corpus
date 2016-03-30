##Initial Ideas

At this point we had spoken to enough individuals to have a good place to start working on a potential prototype. We needed to plan how we would efficiently tackle the problem ahead of us. We first had to make a list of requirements based on our aims <span class="todo">link to aims</span>

* We needed multiple sensors 
* We needed the sensors to be self-sustainable for a long period of time.
* We needed the sensors to be out of the way but effective (Out of mind, not reminders to the clients), so no wires running everywhere.
* We needed a way to visualise all the data from these sensors into a form that was easily understandable
* We needed control over the network, and ideally a way to configure it.
* We needed cases that could ensure the endurance of the devices in different conditions.

Translating this to a solution we can work with:

* We were looking at some form of wireless solution, we could not afford to have wires running everywhere when the clients wanted the solution ‘out of mind’. With wireless comes many different solutions, we investigated the best options available to us.
* We know we had to sample sound - we did not know how often to sample however so we went to investigate that also.
* A microphone is needed with any other electronic circuitry that comes with it. 
* A way to display this data, we decided to investigate ways to do such a thing.
* We had to ensure some form of data backup also.
* Some of the requested locations for these sensors were completely unreachable by permanent power supplies, which led us to the investigation of long term battery solutions.
* We needed a case that could survive harsh weather and conditions, one that would be of a suitable Ingress Protection Rating.
* 

### Minutes

Below are the minutes taken for every meeting that we, personally had between us as a group. They are a rough summary of what decisions we chose to take and how we followed up on them in the weeks after.

Weekly Minutes (September 27th - 25th March 2016)

<b> 27/9/2015 </b>
* Project begins.
* Meeting with supervisor, arranging a meeting with clients.
* Research into general hardware understanding.
* Research into general electronics understanding.

<b>3/10/2015</b>
* Research into sensor amplifier, this is required for our sensor to accurately measure noise.
* Reading Portigal Book, this is required to interview our clients in the best format possible.

<b>10/10/2015</b>
* Working on sensor amplifier, have to calculate accurate values for use.
* Concluding on client meetings, taking notes from the important moments in the meeting.
* Sensors are required as expected, multiple of them will be used to gather data on sound.
* Starting to learn 3D print, will need case designs for components in the project. 
* Start researching potential solutions in system architecture to the problem.

<b>18/10/2015</b>
* A Basic sensor has been created using the amplifier circuit, can now use this act as a sensor temporarily.
* Program needs to be written to sample sound from the current sensor.
* Researching sound waves and understanding of sampling, need a better technical understanding of sampling sound waves and sound in general.
* Researching into potential networking solutions, we need a way of transferring this data from the sensor to the website.
* Researching into hardware boards, Arduinos, MBEDs, any particular board that could be used to handle the sensors requirements.

<b>25/10/2015</b>
* Using the written program for sampling data from the sensor, taking this sampled data and working out how to gather the values we need in order to demonstrate a sound level.
* Using the FRDM K64F as a guide - 3D printing a case for this board.
* Decision to use the XBee as our networking module, offers great customisation and low power cost.

<b>2/11/2015</b>
* Started using Github to handle different elements of the project code base.
* Started getting XBees S2 talking to each other, sending dummy data between two modules.
* Began discussing how often we wish to sample data, how many samples to take and the accuracy of our data. 
* Researching into very low boards to act in place of the sensor.

<b>9/11/2015</b>
* Discussed the potential of using the MBED as a Hub as we are familiar with it.
* Looking into XBees and their configurability, discussing whether encryption or the alike is necessary.
* Researching into converting sound values into decibel levels.

<b>16/11/2015</b>
* Still working with XBees, looking into setting up multiple on a network with a mesh topology as opposed to point to point.
* Discussed the battery concerns, clients ideally want a rechargeable set of batteries. Looking into battery solutions.
* Sketching visualisation ideas.  
* Decided on using the Rocket scream board for the sensor, but going to use Arduino Uno for the time being.

<b>23/11/2015</b>
* Attempting to get an Arduino board communicating to an XBee, wiring the module up ourselves as it’s likely we’ll use an Arduino board.
* After showing 5 sketches produced from each other, we concepted some form of clock that displays noise levels.
* Researching into different solutions for a Hub, potentially FRDM K64F. 

<b>30/11/2015</b>
* Mapping locations for sensors, where are we likely place them - what sort of problems does this raise?
* Concepting case designs for the Arduino Uno.
* Researching components for a clock like device.

<b>7/12/2015</b>
* Going to use AT mode for XBee for Hub and sensor, simpler to set up and then focus on API mode of XBee. 
Research into XBee settings, API mode.
* Clock components decided, visualising components and how to use them. Going to use 24 LEDS on the clock for 24 hours.

<b>14/12/2015</b>
* Clock testing and programming, deciding what colours to use, frequency of them.
* Case design tested, researching into weatherproofing the case.
* Raspberry Pi decided for the Hub.
* Prototype of sensor is going to be placed in client's house over Christmas break.
* Prototype will use local SD card instead of network due to power restrictions with the board being used.
* Decided to sample once a minute and average to use as a representation of that minute.

<b>21/12/2015</b>
* Final meeting before Christmas break, sensor has been placed in Client's house on Orange Street. 
* Rocket scream board arrived, testing with rechargeable batteries is next step
* AT Networking finalised.

<b>20/1/2016</b>
* First meeting since end of Christmas break, sensor has been collected and data returned for evaluation.
* From result it is hard to determine accuracy of noise, sampling needs to be more accurate
* Increasing sampling rate to 3 times a minute.
* Work commencing on creating the Hub, and arranging networked solutions.

<b>27/1/2016</b>
* Clock case design prototyping started.
* Raspberry Pi Model B+ acquired, programming beginning in Python with Jessie Lite as the Operating System.
* Investigating how to visualise data on the website.
* Order requested for components to build more sensors.
* Sampling rate is now much more accurate.

<b>3/2/2016</b>
* Programming the RocketScream, research into power usage with the board (disabling/enabling features).
* Researching sleep mode configuration on XBee modules.
* Case design for Hub started.
* Hub to backup data if network fails.

<b>10/2/2016</b>
* Finished hub, need to test with all components under different circumstances.
* Sensor finished, accuracy lacking - looking into solutions.
* Case design for clock on-going.
* Colour sensitive users for clock.

<b>17/2/2016</b>
* Light intensity as opposed to different colours for users of colour blind nature.
* New sensor prototype almost finished, solution to accuracy is a 16bit ADC.
* New case design for sensor, directional microphone.

<b>24/2/2016</b>
* Testing entire system in the ‘wild’, sensor outside, clock on the side and Hub routing traffic.
* If goes to plan, place in Client's house during this week.
* Case finished for sensor, case for clock next.
* Current networking is AT mode.
* Live visualization being worked on.

<b>31/2/2016</b>
* Designing initial poster for project fair.
* Programming API mode for network.
* Design for clock case finished. Need a way to diffuse light.

<b>7/3/2016</b>
* Visualisation of data on website finished.
* Planning on testing website with users.
* Hub API mode finished.

<b>14/3/2016</b>
* Sensor API mode finished.
* Building of a dummy sensor working with API mode to demonstrate capabilities.
* Visualisation of data finished.
* Clock case finished.
* Plans for poster to test the clock and demonstrate our visualisation.

<b>18/3/2016</b>
* Use clock to demonstrate noise levels and visualisation.
* Laptops and tablets for visualising website.
* Dummy sensor to demonstrate range and error correction.
* Hand out flyers on the project.

<b>25/3/2016</b>
* Formating corpus and technical report for project.







