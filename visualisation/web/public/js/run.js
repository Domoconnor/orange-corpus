d3.json('http://orange.app/api/get/hourly')
	.get(function(error, json){
		console.log(json)
	})
//var circos = new circosJS({
//	container: '#chart',
//	width: 420,
//	height: 420,
//});
//
//layout_data = []
//
//final[0].values.forEach( function(d){
//	layout_data.push({"len":1, "id": h(new Date(d.key))+"hour"})
//})
//
//var clock_data =[]
//
//final[0].values.forEach( function(d){
//	var date = new Date(d.key)
//	var hour = date;
//	hour.setHours(hour.getHours() + 1);
//	clock_data.push([h(date)+"hour",0, 1, d.reading])
//})
//console.log(layout_data);
//circos
//	.layout(
//		{
//			innerRadius: 160,
//			outerRadius: 170,
//			ticks: {display: false},
//			labels: {
//				position: 'center',
//				display: true,
//				size: 14,
//				color: '#000',
//				radialOffset: 15,
//			}
//		},
//		layout_data
//	)
//	.heatmap('temperatures', {
//		innerRadius: 115,
//		outerRadius: 155,
//		min: '20',
//		max: '0',
//		colorPalette: 'RdYlGn',
//	}, clock_data)
//	.render();
//# sourceMappingURL=run.js.map
