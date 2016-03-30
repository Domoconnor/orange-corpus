
<a name="visualisation"></a>
## Visualisation 

[Back to contents](#contents)

### Description

The web visualisation aspect of the system allows users to both get a quick overview of that data that has been recorded but also dive into the data for a much more detailed view of it. This was an important part of the system as it had to make noise levels clear while also providing the raw data that would be used to back that up.

We created a user account system with the aim of allowing users to recieve next notifications for each of the devices. This system lets users register, sign ing, update their information and view the data. Another reason we did this wasm initially, the residents were concerned that the bars may look at this data in some way and use it to try and benefit them. The account system allows only certain people to view the data while also allowing the residents to let people sign up such as council members. The accounts system used Laravel, which was what was also being used for the API.

Another part of the web visualisation was a sensor status section. From here the residents could check on things such as battery status and last reading so they could be happy it was working.

![](images/visualisation/status.png)
The finised web visualisation used D3.js to create a number of different ways of displaying the data. The main three it uses are the clock, graph, and compare.

####Clock interface
The clock is intened to bridge the gap between the phyical parts of the system and the digital parts. It provides a consistent representation of data between the two in an effort to make the user more comfortable. An image of the phyical and digital clocks can be seen below:


![](images/visualisation/clock.jpeg)
![](images/visualisation/clocks.png)

The clock view is meant as an overview for the entire system, at a glance you can see what has been chosen. The clock allows you to then click through to a more detialed graph.

####Graph
The graph shows a more detailed view of the day allowing you to see what numerical levels the noise reached. It also includes a list of the raw data which consists of timestamps, the raw reading, and decibels. 

![](images/visualisation/graph.png)
![](images/visualisation/data.png)

The graph combined with the raw data output shows the noise level in an easy to understand way while displying important information. 

####Compare
The compare section of the website was created as a way of viewing multiple days worth of data on one page. We previously tried this with graphs but found that it was messy and didn't get the point across. To solve this we created a view that which, like the clock, displayed the data using colours based on the sound level. It displayed hours across the x axis and days on the y axis.

![](images/visualisation/compare.png)

As you can see in the image above, on saturday and wednesday evening it was louder than other evenings as they have a yellow colour rather than green.

###Previous Work
#### Iteration 1 - Initial Work
We wnanted something that we could use to show the data we had gathered from the sensors in an easy way. We began by sing the 5-sketches-or-else method. This started with us each sketching 5 ways we could display this data individually. After we had done that we came together to present our ideas to eachother and discussed what we liked about each one. We then worked together to merge the best elements from all of our designs into new designs. After this we continued to improve these designs until we got to a point we were happy with. You can view all of our initial sketches and improvements [here](sketches/)

The main things that came out of this process were the clock, line graphs and a calendar style view. 

After this we decided to start to consider implementing them. We found that some members of the group had experience graphing data and made the most of that experience.We decided that we would generate the graphs and charts using JavaScript rather than generating them on the server as it would move load from the server to the client and also make it much easier to create as we were familiar with JavaScript. We also decided to use a library as it would allow us to quickly get something out there as we wouldn't have to create it form scratch. Based on the sketches and ideas we made and came up with we came up with the simple library comparison chart seen below.

<table>
	<tr>
		<th>Name</th>
		<th>Difficulty</th>
		<th>Line Graphs?</th>
		<th>Calendar Style?</th>
		<th>Clock/circular Style?</th>
		<th>Well documented?</th>
	</tr>
	<tr>
		<td>Chart.js</td>
		<td>Easy</td>
		<td>Yes</td>
		<td>No</td>
		<td>Yes</td>
		<td>No</td>
	</tr>
	<tr>
		<td>Highcharts</td>
		<td>Medium</td>
		<td>Yes</td>
		<td>No</td>
		<td>Yes</td>
		<td>Yes</td>
	</tr>
	<tr>
		<td>D3.js</td>
		<td>Medium</td>
		<td>Yes</td>
		<td>Yes</td>
		<td>Yes</td>
		<td>Yes</td>
	</tr>
	<tr>
		<td>Flot</td>
		<td>Easy</td>
		<td>Yes</td>
		<td>No</td>
		<td>No</td>
		<td>Yes</td>
	</tr>
	<tr>
		<td>jscharts</td>
		<td>Easy</td>
		<td>Yes</td>
		<td>No</td>
		<td>No</td>
		<td>No</td>
	</tr>
</table>

After looking at this we decided to go with D3. It would give us the flexibility to add more complex charts such as one in the style of a calendar as well as being relatively easy to use, well known and well documented.


##### Result of iteration
We created a simple page that would display a graph of a single day along with all of it's points. This is very simplistic and is just to ensure that we can get our data in the correct format.

####Iteration 2 - Displaying Data over multiple days
During this iteration we wanted to display multiple days worth of data on the same graph.

#####Issues with previous iteration
Processing the data is taking large amounts of time on every page refresh

#####Result of iteration
We now have a graph which can display multiple days worth of data. To select these days there is a calendar which you can click on, clicking on the same date again will then deselct it. The graph updates without needing to refresh the page. It is also much quicker than before as we moved the processing of the data from the frontend to the API.  More on this can be found in the [Server section](#server)


####Iteration 3 - Clock visualisation
We wanted to make a bridge between the clock and the website so we decided to create a digital version of the clock that could be displayed on the website. 

#####Issues with previous iteration
The previous iteration worked fine techinically, however there were some issues with the way the data was displayed. Any more than 3 lines was complicated and meant it's difficult to see what data you are looking. We will improve on this in a future iteration.

#####Result of iteration
We created a visualisation that looks similar to the clock as you can see below:

![](images/visualisation/clock1.png)

This was created from the test data we recieved over christmas.

The clock is built on top of D3 using an extension called Circos.js. Below is the code that is used to create these circles

```javascript
//Get the data from the API
d3.json('http://orange.app/api/get/hourly')
		.get(function(error, json){

			//Loop over each set of data recieved and convert it into a clock
			charts[0].forEach(function(x){
				data = json;
				parent = d3.select("#"+x.id)[0][0].parentNode;
				width = parent.offsetWidth - 50;
				height = parent.offsetHeight ;
				var circos = new circosJS({
					container: "#"+ x.id,
					width: width,
					height: height,
				});


				layout_data = []
				
				//Create the layout data used by Circos.js by creating array of 
				//divs with ids 0 - 23 which represent hours
				for (i = 0; i < 23; i++)
				{
					if(i < 10)
					{
						layout_data.push({"len":1, "id":'0'+i+'hour'});
					}
					else
					{
						layout_data.push({"len":1, "id":i+'hour'});
					}

				}

				var clock_data =[]

				//Turn the data recieved from the api into the correct format and 
				//add it to an array containing all the data from our clock
				json.forEach( function(d){
					if(ymd(new Date(d.start)) == ymd(new Date(x.id.substring(1)))) {
						var date = new Date(d.start)
						var hour = date;
						hour.setHours(hour.getHours() + 1);
						clock_data.push([h(date) + "hour", 0, 1, (d.avg+15)])
						console.log(+d.avg+10);
					}
				})

				//Construct the circos object
				circos
					.layout(
						{
							cornerRadius: 3,
							innerRadius: width/4+25,
							outerRadius: width/4+30,
							ticks: {display: false},
							labels: {
								position: 'center',
								display: true,
								size: 14,
								color: '#000',
								radialOffset: 15,
							}
						},
						layout_data
					)
					//Show what colours you want the sections to be
					//based on colorBrewer
					.heatmap('temperatures', {

						innerRadius: width/4,
						outerRadius: width/4+25,
						min: '23',
						max: '0',
						colorPalette: 'RdYlGn',
					}, clock_data)
					.render();
			})
		})
```
####Iteration 4 - Fixing the line graph
The multiple line graph that we created in iteration 2 was confusing hard to understand. We planned to fix this in this iteration.

#####Issues with previous iteration
None

#####Resut of this iteration
We changed the way data was graphed so you could no longer select multiple dates. This made the graph much easier to read but we would need another way to compare data. We began to look at ways of comparing however there are no obvious ways and our sketches don't really help with that.

####Iteration 5 - Fixing data comparison
As mentioned in the previous iteration, we removed the feature from our line graph that would allow us to compare multiple days. This comparison is an important part of the website as without it the results can be hard to understand. 

#####Issues with previous iteration
None

##### Result of this iteration
After looking at several sources we decided that we liked how GitHub show
how often someone commits. You can see an image of one of those graphs below:

![](images/visualisation/github.png)

As we are working with data where time is important we cannot simply show the day so we changed it to include hours on the x axis and days on the y axis. You can see the graph we created below:

![](images/visualisation/compare2.png)

####Iteration 6 - Turning graphs into a website

Up until this point all of the graphs had been standalone, pulling the data from the API but all separate. We needed to create a website where all of these could be viewable and make sense together.

#####Issues with previous iteration
There were some issues with aligning the graph labels however this will be left until a future iteration.

#####Result of this iteration
We created a website that was built in laravel and using bootstrap to improve the interface. We created a user accounts system that would allow access control in the future. The code for the website can be found [here](visualisation/web/resources/assets/js/)