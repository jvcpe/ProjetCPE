/*
 * Dessine les graphiques
 */


window.onload = function() {
	/*
	 * Tableau de données
	 */
	var dps_averageLoad = []; // dataPoints
	var dps_cpuLoad = []; // dataPoints
	var dps_freeMemory = []; // dataPoints

	/*
	 * Declaration des graph
	 */
	var chart_averageLoad = new CanvasJS.Chart("averageLoad", {
		title : {
			text : "Average Load"
		},
		data : [ {
			type : "line",
			dataPoints : dps_averageLoad
		} ]
	});

	var chart_cpuLoad = new CanvasJS.Chart("cpuLoad", {
		title : {
			text : "Cpu Load"
		},
		data : [ {
			type : "line",
			dataPoints : dps_cpuLoad
		} ]
	});

	var chart_freeMemory = new CanvasJS.Chart("freeMemory", {
		title : {
			text : "Free Memory"
		},
		data : [ {
			type : "line",
			dataPoints : dps_freeMemory
		} ]
	});

	/*
	 * Settings
	 */
	var updateInterval = 7000;
	var dataLength = 50; // number of dataPoints visible at any point

	var xVal_averageLoad = 0;
	var xVal_cpuLoad = 0;
	var xVal_freeMemory = 0;
	var yVal_averageLoad = 0;
	var yVal_cpuLoad = 0;
	var yVal_freeMemory = 0;

	/*
	 * Fonction de maj de averageLoad
	 */
	var updateChart_averageLoad = function(count) {

		count = count || 1;
		// count is number of times loop runs to generate random dataPoints.

		$(document).ready(function() {
			// Récupération JSON contenant AverageLoad
			// var jsonAverageLoad = {"averageload":12};
			$.post("http://localhost:8080/Projet_IWOC/PostMe", {
				cmd : "PostInfo",
				data : "GET_AVERAGE_LOAD"
			}, function(data, status) {
				// alert("\nStatus average load: " + status);
				jsonAverageLoad = data;
				yVal_averageLoad = jsonAverageLoad.averageload;

				for (var j = 0; j < count; j++) {

					dps_averageLoad.push({
						x : xVal_averageLoad,
						y : yVal_averageLoad
					});
					xVal_averageLoad++;

				}
				;
				if (dps_averageLoad.length > dataLength) {
					dps_averageLoad.shift();
				}

				chart_averageLoad.render();
			}, "json");
			
		});
		
		isUpdatingCharts = false;
	};

	/*
	 * Fonction de maj de cpuLoad
	 */
	var updateChart_cpuLoad = function(count) {

		count = count || 1;
		// count is number of times loop runs to generate random dataPoints.

		var jsonCpuLoad = null;

		for (var j = 0; j < count; j++) {

			// Appel au serveur
			// yVal_freeMemory = 5;// yVal + Math.round(5 + Math.random() * (-5
			// - 5));

			// Récupération JSON contenant FreeMemory
			var jsonCpuLoad = {"cpuload" : 0.14366841817421191};
			yVal_cpuLoad = jsonCpuLoad.cpuload;

			dps_cpuLoad.push({
				x : xVal_cpuLoad,
				y : yVal_cpuLoad
			});
			xVal_cpuLoad++;
		}
		;
		if (dps_cpuLoad.length > dataLength) {
			dps_cpuLoad.shift();
		}

		chart_cpuLoad.render();


	};

	/*
	 * Fonction de maj de freeMemory
	 */
	var updateChart_freeMemory = function(count) {
		count = count || 1;
		// count is number of times loop runs to generate random dataPoints.

		for (var j = 0; j < count; j++) {

			// Appel au serveur
			// yVal_freeMemory = 5;// yVal + Math.round(5 + Math.random() * (-5
			// - 5));

			// Récupération JSON contenant FreeMemory
			var jsonFreeMemory = {
				"freememory" : 12923043840
			};
			yVal_freeMemory = jsonFreeMemory.freememory;

			dps_freeMemory.push({
				x : xVal_freeMemory,
				y : yVal_freeMemory
			});
			xVal_freeMemory++;
		}
		;
		if (dps_freeMemory.length > dataLength) {
			dps_freeMemory.shift();
		}

		chart_freeMemory.render();
	};

	/*
	 * Maj des graphs
	 */
	// generates first set of dataPoints
	updateChart_averageLoad(dataLength);
	updateChart_cpuLoad(dataLength);
	updateChart_freeMemory(dataLength);

	// update chart after specified time.
	setInterval(function() {
		if (isLocked == false && isUpdatingCharts==false) {
			isUpdatingCharts = true;
			$(document).ready(function() {
				updateChart_averageLoad();
			});
		}
		// updateChart_cpuLoad();
		// updateChart_freeMemory();
	}, updateInterval);

}


// /*
// * Fonction de maj de cpuLoad
// */
// var updateChart_cpuLoad = function(count) {
// count = count || 1;
// // count is number of times loop runs to generate random dataPoints.
//
// // Récupération JSON contenant CPULoad
// // var jsonCpuLoad = {"cpuload" : 0.14366841817421191};
// var jsonCpuLoad = null;
// $(document).ready(function() {
// $.post("http://localhost:8080/Projet_IWOC/PostMe", {
// cmd : "PostInfo",
// data : "GET_CPU_USAGE"
// }, function(data, status) {
// alert("\nStatus CPU load: " + status);
// jsonCpuLoad = data;
// yVal_cpuLoad = jsonCpuLoad.cpuload;
//
// // for (var j = 0; j < count; j++) {
// dps_cpuLoad.push({
// x : xVal_cpuLoad,
// y : yVal_cpuLoad
// });
// xVal_cpuLoad++;
// // }
// // ;
// if (dps_cpuLoad.length > dataLength) {
// dps_cpuLoad.shift();
// }
//
// chart_cpuLoad.render();
// }, "json");
// });
// };
//
// /*
// * Fonction de maj de freeMemory
// */
// var updateChart_freeMemory = function(count) {
// count = count || 1;
// // count is number of times loop runs to generate random dataPoints.
//
// // Récupération JSON contenant FreeMemory
// // var jsonFreeMemory = {"freememory" : 12923043840};
// var jsonFreeMemory = null;
// $(document).ready(function() {
// $.post("http://localhost:8080/Projet_IWOC/PostMe", {
// cmd : "PostInfo",
// data : "GET_FREE_MEMORY"
// }, function(data, status) {
// alert("\nStatus free memory: " + status);
// jsonFreeMemory = data;
//
// yVal_freeMemory = jsonFreeMemory.freememory;
// // for (var j = 0; j < count; j++) {
// dps_freeMemory.push({
// x : xVal_freeMemory,
// y : yVal_freeMemory
// });
// xVal_freeMemory++;
// // }
// // ;
// if (dps_freeMemory.length > dataLength) {
// dps_freeMemory.shift();
// }
//
// chart_freeMemory.render();
// }, "json");
// });
// };
