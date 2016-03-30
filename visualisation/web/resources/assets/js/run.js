var h = d3.time.format.utc("%H")
var ymd = d3.time.format.utc("%Y-%m-%d");
var charts = d3.selectAll('.chart');
var graphs = d3.selectAll('.graph');
function hexCode(d) { return d.charCodeAt(0).toString(16); }

if(charts[0].length > 2)
{
	d3.json('http://orange.app/api/get/hourly')
		.get(function(error, json){

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

				json.forEach( function(d){
					if(ymd(new Date(d.start)) == ymd(new Date(x.id.substring(1)))) {
						var date = new Date(d.start)
						var hour = date;
						hour.setHours(hour.getHours() + 1);
						clock_data.push([h(date) + "hour", 0, 1, (d.avg+15)])
						console.log(+d.avg+10);
					}
				})

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
} else if(graphs[0].length > 0) {
	var color = d3.scale.category20();
	var final = new Array();

	var ymd = d3.time.format.utc("%Y-%m-%d");
	var h = d3.time.format.utc("%H")

	var margin = {top: 20, right: 20, bottom: 30, left: 50},
		width = 960 - margin.left - margin.right,
		height = 500 - margin.top - margin.bottom;

	var x = d3.time.scale()
		.range([0, width]);

	var y = d3.scale.linear()
		.range([height, 0]);

	var xAxis = d3.svg.axis()
		.scale(x)
		.orient("bottom");

	var yAxis = d3.svg.axis()
		.scale(y)
		.orient("left");

	var line = d3.svg.line()
		.interpolate("basis")
		.x(function(d) { return x(new Date(d.timestamp)); })
		.y(function(d) { return y(d.reading*3); });

	var svg = d3.select(".graph").append("svg")
		.attr("width", width + margin.left + margin.right)
		.attr("height", height + margin.top + margin.bottom)
		.append("g")
		.attr("transform", "translate(" + margin.left + "," + margin.top + ")");


	var legend = svg.append("g")
		.attr("transform","translate(50,30)")
		.style("font-size","12px")
		.style("color","blue")
		.attr('fill', 'white')
		.attr('class', 'legend')
		.call(d3.legend)

	graph_time = d3.select(".graph").attr('id').substring(1);
	//Load in the CSV and run the data through the type() to format the date
	d3.json("/api/get/hourly/"+graph_time+"/"+(+graph_time+86400))
	.get(function(error, data){
		data.forEach(function(d){
			d.timestamp = new Date(d.start);
			d.reading = +d.avg;
			return d;
		})
		if (error) throw error;

		x.domain(d3.extent(data, function(d) { return d.timestamp; }));
		y.domain([0,100]);
		//Attatch the data to the correct axis


		svg.append("g")
			.attr("class", "x axis")
			.attr("transform", "translate(0," + height + ")")
			.call(xAxis);

		svg.append("g")
			.attr("class", "x axis")
			.attr("transform", "translate(0," + height + ")")
			.call(xAxis);

		svg.append("g")
			.attr("class", "y axis")
			.call(yAxis)
			.append("text")
			.attr("transform", "rotate(-90)")
			.attr("y", 6)
			.attr("dy", ".71em")
			.style("text-anchor", "end")
			.text("Level");


		svg.append("path")
			.datum(data)
			.attr("class", "line")
			.attr("d", line);
	});

}



