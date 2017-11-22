/**
 * Gestion du Canvas
 */
//Variables globales utilisées pour éviter le rechargement des charts en même
//temps que la demande de déplacement

//Initialisation des variables
var largeur_rect = null;
var longueur_rect=null;
var H=0;
var L=0 ;
var lignes = 1;
var colonnes = 1;
var myJson;
var nbre_obstacle = 0;
var nbre_deplacement = 0;
var nbre_obstacle_ren = 0;
var distance = 0;
var stop_deplacement=0;
//Longueur d'un cote d'un carre du quadrillage
var carre;
//Marge du quadrillage
var marge = 30;

var robot = {
		x_px_robot : 0,
		y_px_robot : 0,
		robot_img : new Image()
};


//recupération de la map de départ
$.post("rest/cmd/gen",{},function(data){
	myJson=data;
	dessine_canvas();
	MajCanvas();
});


//dessine_robot(0,1,1);
function dessine_canvas() {


	H = myJson.robot[0].hauteurMap;
	L = myJson.robot[0].largeurMap;
	var canvas = document.getElementById('Grille');
	var context = canvas.getContext('2d');
	//context.clearRect(0, 0, canvas.width, canvas.height);



	lignes = L;
	colonnes = H;




	// Noir transparent
	context.strokeStyle = "rgba(0, 0, 0, 0.5)";
	// Police d'ecriture
	context.font = "15px Helvetica";

	// Taille du rectangle en fonction de la taille du Canvas et
	// du nombre de lignes et colonnes
	largeur_rect = (canvas.getAttribute("height") - marge) / lignes;
	longueur_rect = (canvas.getAttribute("width") - marge) / colonnes;
	carre = Math.min(largeur_rect, longueur_rect);
	// Mise en place des rectangle
	for (var i = 0; i < colonnes; i++) {
		for (var j = 0; j < lignes; j++) {
			// Dessine le rectangle
			context.strokeRect(i * carre + marge, j * carre + marge, carre,
					carre);
		}
		// Numero de colonne
		context.fillText(i, i * (carre) + marge + carre / 2, 20);
	}

	// Numero de ligne
	for (var j = 0; j < lignes; j++) {
		context.fillText(j, 10, j * (carre) + marge + carre / 2);
	}

}

/*
 * Fonction map_to_px Donne le coin haut gauche d'un carre en pixel (abs,ord) a
 * partir d'un point de map Paramètre : Coordonnées de map (x,y) Retour :
 * Coordonnées en pixel (x,y)
 */
function map_to_px(coord_map) {
	return coord_map * (carre) + marge;
}


/*
 * Fonction dessine_robot Dessine la position du robot sur la map Parametre :
 * position du robot SUR LA MAP (x,y) (pas en pixel) Retour : void
 */
function dessine_robot(x_map_robot, y_map_robot, orientation_robot) {
	var canvas = document.getElementById('Robot');
	var context = canvas.getContext('2d');
	context.clearRect(0, 0, canvas.width, canvas.height);


	// Conversion des coordonnées
	robot.x_px_robot = map_to_px(x_map_robot);
	robot.y_px_robot = map_to_px(y_map_robot);

	// Image du robot
	robot.robot_img.src = "Images/Robot/robot_" + orientation_robot + ".png";
	robot.robot_img.onload = function() {
		context.drawImage(robot.robot_img, 0, 0, 40, 40, robot.x_px_robot,
				robot.y_px_robot, carre, carre);
	}
}

/*
 * Fonction dessine_mur Dessine la position d'un mur sur la map Parametre :
 * position du mur SUR LA MAP (x,y) (pas en pixel) Retour : void
 */
function dessine_mur(x_map_mur, y_map_mur) {
	var canvas = document.getElementById('Mur');
	var context = canvas.getContext('2d');
	context.clearRect(0, 0, canvas.width, canvas.height);
	var x_px_mur, y_px_mur;

	// Conversion des coordonnées
	x_px_mur = map_to_px(x_map_mur);
	y_px_mur = map_to_px(y_map_mur);

	// Image du mur
	var mur_img = new Image();
	mur_img.src = "Images/Wall/poub.png";
	mur_img.onload = function() {
		context.drawImage(mur_img, 0, 0, 32, 32, x_px_mur, y_px_mur, carre,
				carre);
	}
}


function dessine_trajectoire(x_map_traj, y_map_traj) {

	var canvas = document.getElementById('Trajectoire');
	var context = canvas.getContext('2d');
	context.clearRect(0, 0, canvas.width, canvas.height);
	var x_px_traj, y_px_traj;

	// Conversion des coordonnées
	x_px_traj = map_to_px(x_map_traj);
	y_px_traj = map_to_px(y_map_traj);

	// Image du mur
	var mur_img = new Image();
	mur_img.src = "Images/Traj/pierre.png";
	mur_img.onload = function() {
		context.drawImage(mur_img, 0, 0, 32, 32, x_px_traj, y_px_traj, carre,
				carre);
	}

}


function brouillard(x_map_fog, y_map_fog) {

	var canvas = document.getElementById('Brouillard');
	var context = canvas.getContext('2d');
	context.clearRect(0, 0, canvas.width, canvas.height);
	var x_px_fog, y_px_fog;

	// Conversion des coordonnées
	x_px_fog = map_to_px(x_map_fog);
	y_px_fog = map_to_px(y_map_fog);

	// Image du mur
	var mur_img = new Image();
	mur_img.src = "Images/Brouillard/fog2.png";
	mur_img.onload = function() {
		context.drawImage(mur_img, 0, 0, 50, 50, x_px_fog, y_px_fog, carre,
				carre);
	}

}


function dessine_sol(x_map_sol, y_map_sol) {

	var canvas = document.getElementById('Grille');
	var context = canvas.getContext('2d');
	var x_px_sol, y_px_sol;

	// Conversion des coordonnées
	x_px_sol = map_to_px(x_map_sol);
	y_px_sol = map_to_px(y_map_sol);

	// Image du mur
	var sol_img = new Image();
	sol_img.src = "Images/Sol/sol.png";
	sol_img.onload = function() {
		context.drawImage(sol_img, 0, 0, 32, 32, x_px_sol, y_px_sol, carre,
				carre);
	}

}

function MajCanvas() {


	nbre_obstacle = myJson.robot[3].nbObstaclesVisibles;
	nbre_deplacement = myJson.robot[3].nbCommandes;
	nbre_obstacle_ren = myJson.robot[3].nbObstaclesRencontres;
	distance = myJson.robot[3].distanceParcourue;


	var x_map_robot = myJson.robot[0].y;
	var y_map_robot = myJson.robot[0].x;

	var orientation_robot = myJson.robot[0].orientation;
	dessine_robot(x_map_robot, y_map_robot, orientation_robot);

	for (var i5 = 0; i5 < L; i5++) { // 24 = nombre de cases à
		// parcourir envoyées par le
		// sonar
		for (var y5 = 0; y5 < H; y5++) {
			dessine_sol(y5,i5);
		}
	}


	// Affichage des obstacles
	for (var i = 0; i < L; i++) { // 24 = nombre de cases à
		// parcourir envoyées par le
		// sonar
		for (var y = 0; y < H; y++) {
			if (myJson.robot[2].map[i][y] == 2) {
				// Coordonnées de mur

				var x_map_wall = y;// Veritables
				// coordonnées dans la
				// map
				var y_map_wall = i;// Veritables
				// coordonnées dans la
				// map
				dessine_mur(x_map_wall, y_map_wall);

			}
		}
	}


	// Affichage des trajectoires
	for (var i2 = 0; i2 < L; i2++) { // 24 = nombre de cases à
		// parcourir envoyées par le
		// sonar
		for (var y2 = 0; y2 < H; y2++) {
			if (myJson.robot[2].mapVisitee[i2][y2] == 1) {
				// Coordonnées de trajectoire

				var x_map_traj = y2;// Veritables
				// coordonnées dans la
				// map
				var y_map_traj = i2;// Veritables
				// coordonnées dans la
				// map
				dessine_trajectoire(x_map_traj, y_map_traj);
			}
		}
	}

	// Affichage du brouillard
	for (var i3 = 0; i3 < L; i3++) { // 24 = nombre de cases à
		// parcourir envoyées par le
		// sonar
		for (var y3 = 0; y3 < H; y3++) {
			if (myJson.robot[2].map[i3][y3] == 4) {
				// Coordonnées de trajectoire

				var x_map_fog = y3;// Veritables
				// coordonnées dans la
				// map
				var y_map_fog = i3;// Veritables
				// coordonnées dans la
				// map
				brouillard(x_map_fog, y_map_fog);
			}
		}
		
	}
	/*
	while(document.getElementById("nav_auto").checked == false && stop_deplacement==0)
	{
			var temp=Math.random();
			
			if(temp > (0.75)){
				
				click_up();
			}
			else{
				if(temp>0.5){
					click_down();
				}

				else{
					if(temp>0.25){
						click_right();
					}

					else{
						if(temp>0){
							click_left();
						}
					}
				}
			}
			sleep(1000);
			compareMaps();
		}
*/
		compareMaps();
	}

	function compareMaps(){

		$.post("rest/cmd/comp",{},function(data){
		if(data=="true"){
			var canvas = document.getElementById('Brouillard');
			var context = canvas.getContext('2d');
			context.clearRect(0, 0, canvas.width, canvas.height);
			stop_deplacement=1;
			alert("Map découverte!");
			}

		});


	}
/*
	function sleep(milliseconds) {
		var start = new Date().getTime();
		for (var i = 0; i < 1e7; i++) {
			if ((new Date().getTime() - start) > milliseconds){
				break;
			}
		}
	}
*/
