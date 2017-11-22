/*
 * Gestion du display
 */

$(function() {
	$('#pos_robot').change(function() {
		pos_robot();
	})
})

$(function() {
	$('#pos_mur').change(function() {
		pos_mur();
	})
})

$(function() {
	$('#parcourt_robot').change(function() {
		parcourt_robot();
	})
})

$(function() {
	$('#nav_auto').change(function() {
		nav_auto();
	})
})

$(function() {
	$('#pos_brouillard').change(function() {
		pos_brouillard();
	})
})




/*
 * Fonction position_robot
 * Permet d'afficher ou non la position du robot
 */


function pos_robot() {
	var id = "pos_robot";
	if (document.getElementById(id).checked == true) {
		document.getElementById('Robot').style.display = 'block';
	} else {
		document.getElementById('Robot').style.display = 'none';
	}
}

/*
 * Fonction parcours_robot
 * Permet d'afficher ou non le parcours du robot
 */

function parcourt_robot() {
	var id = "parcourt_robot";
	if (document.getElementById(id).checked == true) {
		document.getElementById('Trajectoire').style.display = 'block';
	} else {
		document.getElementById('Trajectoire').style.display = 'none';
	}
}

/*
 * Fonction position_mur
 * Permet d'afficher ou non la position des murs
 */

function pos_mur() {
	var id = "pos_mur";
	if (document.getElementById(id).checked == true) {
		document.getElementById('Mur').style.display = 'block';
	} else {
		document.getElementById('Mur').style.display = 'none';
	}
}

/*
 * Fonction position_mur
 * Permet d'afficher ou non la position du brouillard
 */
function pos_brouillard() {
	var id = "pos_brouillard";
	if (document.getElementById(id).checked == true) {
		document.getElementById('Brouillard').style.display = 'block';
	} else {
		document.getElementById('Brouillard').style.display = 'none';
	}
}

/*
 * Fonction navigation_automatique
 * Permet d'enclencher ou non la navigation automatique du robot
 */
/*
function nav_auto(){
	
	while(document.getElementById("nav_auto").checked == false && stop_deplacement==0)
		{
	

				var temp=Math.random();

				if(temp > (0.75)){
					alert("caca");
					click_up();
					stop_deplacement==1;
				}
				else{
					if(temp>0.5){
						alert("caca");
						click_down();
						stop_deplacement==1;
					}

					else{
						if(temp>0.25){
							alert("caca");
							click_right();
							stop_deplacement==1;
						}

						else{
							if(temp>0){
								alert("caca");
								click_left();
								stop_deplacement==1;
							}
						}
					}
				}
				sleep(10000);
				compareMaps();
			}
			}
 
*/





