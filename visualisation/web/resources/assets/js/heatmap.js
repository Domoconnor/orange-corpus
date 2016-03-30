var heatmap = d3.selectAll('.heatmap');

//If there is a heatmap div on the page, select it.
if(heatmap[0].length > 0 )
{
	console.log("run")
	//standard date formats
	var hourFormat = d3.time.format('%H'),
		dayFormat = d3.time.format('%j'),
		timeFormat = d3.time.format('%Y-%m-%dT%X'),
		monthDayFormat = d3.time.format('%m.%d'),
		ymd = d3.time.format.utc("%a %e %b");
	var itemSize = 40,
		cellSize = itemSize-1,
		width = 1800,
		height = 1200,
		margin = {top:50,right:20,bottom:20,left:100};

	var dateExtent = null,
		data = null,
		dayOffset = 0,
		colorCalibration = ['#a6d96a','#d9ef8b','#ffffbf','#fee08b','#fdae61','#f03b20'],
		dailyValueExtent = {};


		//Setup axis
	var axisWidth = 0 ,
		axisHeight = itemSize*24,
		xAxisScale = d3.time.scale(),
		xAxis = d3.svg.axis()
			.orient('left')
			.ticks(d3.time.days)
			.tickFormat(ymd),
		yAxisScale = d3.scale.linear()
			.range([0,axisHeight])
			.domain([0,24]),
		yAxis = d3.svg.axis()
			.orient('top')
			.ticks(12)
			.tickFormat(d3.format('02d'))
			.scale(yAxisScale);

	initCalibration();

	var svg = d3.select('[role="heatmap"]');
	var heatmap = svg
		.attr('width',width)
		.attr('height',height)
		.append('g')
		.attr('width',width-margin.left-margin.right)
		.attr('height',height-margin.top-margin.bottom)
		.attr('transform','translate('+margin.left+','+margin.top+')');
	var rect = null;

	if (window.location.hash == '#25')
	{
		var file = 'http://orange.app/api/get/hourly/1450943537/2000000000'
	} else {
		var file = 'http://orange.app/api/get/hourly/0/1450943537'
	}
	var file
	//read in data
	d3.json(file)
		.get(function(err,data){

			data.forEach(function(d){
				d.reading_time = d.start;
				d.value = +d.avg;
				return d;
			})

			//Set bounds for graph
			data.forEach(function(valueObj){
				valueObj['date'] = new Date(valueObj['reading_time']);
				var day = valueObj['day'] = monthDayFormat(valueObj['date']);

				var dayData = dailyValueExtent[day] = (dailyValueExtent[day] || [1000,-1]);
				var pmValue = valueObj['value'];
				dayData[0] = d3.min([dayData[0],pmValue]);
				dayData[1] = d3.max([dayData[1],pmValue]);
			});

			dateExtent = d3.extent(data,function(d){
				return d.date;
			});

			axisWidth = itemSize*(dayFormat(dateExtent[1])-dayFormat(dateExtent[0])+1);

			//render axes
			xAxis.scale(xAxisScale.range([0,axisWidth]).domain([dateExtent[0],dateExtent[1]-5]));
			svg.append('g')
				.attr('transform','translate('+margin.left+','+margin.top+')')
				.attr('class','x axis')
				.call(xAxis)
				.append('text')


			svg.append('g')
				.attr('transform','translate('+margin.left+','+margin.top+')')
				.attr('class','y axis')
				.call(yAxis)
				.append('text')
				.text('Time')
				.attr('transform','translate('+axisWidth+',-30)');

			//render heatmap rects
			dayOffset = dayFormat(dateExtent[0]);
			rect = heatmap.selectAll('rect')
				.data(data)
				.enter().append('rect')
				.attr('width',cellSize)
				.attr('height',cellSize)
				.attr('x',function(d){
					return hourFormat(d.date)*itemSize;
				})
				.attr('y',function(d){
					return itemSize*(dayFormat(d.date)-dayOffset);
				})
				.attr('fill','#ffffff');

			rect.filter(function(d){ return d.value>0;})
				.append('title')
				.text(function(d){
					return monthDayFormat(d.date)+' '+d.value;
				});

			renderColor();
		});

		//Fill the boxes in with colour based on range data
	function renderColor(){

		rect
			.filter(function(d){
				return (d.value>=0);
			})
			.transition()
			.delay(function(d){
				return (dayFormat(d.date)-dayOffset)*15;
			})
			.duration(500)
			.attrTween('fill',function(d,i,a){
				//choose color dynamicly
				var colorIndex = d3.scale.quantize()
					.range([0,1,2,3,4,5])
					.domain(dailyValueExtent[d.day]);

				return d3.interpolate(a,colorCalibration[colorIndex(d.value)]);
			});
	}


	//Setup calibration
	function initCalibration(){
		d3.select('[role="calibration"] [role="example"]').select('svg')
			.selectAll('rect').data(colorCalibration).enter()
			.append('rect')
			.attr('width',cellSize)
			.attr('height',cellSize)
			.attr('x',function(d,i){
				return i*itemSize;
			})
			.attr('fill',function(d){
				return d;
			});

		//bind click event
		d3.selectAll('[role="calibration"] [name="displayType"]').on('click',function(){
			renderColor();
		});
	}
}
