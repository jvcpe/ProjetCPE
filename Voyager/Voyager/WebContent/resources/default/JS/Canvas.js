/**
 * Gestion du Canvas
 */
// Variables globales utilisées pour éviter le rechargement des charts en même
// temps que la demande de déplacement
var isLocked = false;
var isUpdatingCharts = false;

// Longueur d'un cote d'un carre du quadrillage
var carre;
// Marge du quadrillage
var marge = 30;

var robot = {
	x_px_robot : 0,
	y_px_robot : 0,
	robot_img : new Image()
};

/*
 * Fonction taille_map Envoie en paramètre dans l'URL la taille de la map Utile
 * pour lancement.xhtml
 */
var lignes = 1;
var colonnes = 1;
function taille_map() {
	lignes = document.getElementById('taille_x').value;
	colonnes = document.getElementById('taille_y').value;
	document.location.href = "cmd.html?x=" + lignes + "&y=" + colonnes;
}

/*
 * Fonction dessine_canvas Dessine le Canvas (map) grace a un ensemble de
 * rectangle Parametre : nombre de lignes, nombre de colonnes Retour : void
 */
function dessine_canvas() {

	// Récupère la taille de la map grâce à l'url
	/*
	var t = location.search.substring(1).split('&');
	var f = [];
	for (var i = 0; i < t.length; i++) {
		var x = t[i].split('=');
		f[x[0]] = x[1];
	}
	lignes = f['y'];
	colonnes = f['x'];
	*/

	lignes = 15;
	colonnes = 15;

	var canvas = document.getElementById('Grille');
	var context = canvas.getContext('2d');
	// Noir transparent
	context.strokeStyle = "rgba(0, 0, 0, 0.5)";
	// Police d'ecriture
	context.font = "15px Helvetica";

	// Taille du rectangle en fonction de la taille du Canvas et
	// du nombre de lignes et colonnes
	var largeur_rect = (canvas.getAttribute("height") - marge) / lignes;
	var longueur_rect = (canvas.getAttribute("width") - marge) / colonnes;
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
	var x_px_mur, y_px_mur;

	// Conversion des coordonnées
	x_px_mur = map_to_px(x_map_mur);
	y_px_mur = map_to_px(y_map_mur);

	// Image du mur
	var mur_img = new Image();
	mur_img.src = "Images/Wall/wall.png";
	mur_img.onload = function() {
		context.drawImage(mur_img, 0, 0, 50, 50, x_px_mur, y_px_mur, carre,
				carre);
	}
}

/*
 * Fonction dessine_trajectoire Dessine la trajectoire du robot sur la map
 * Parametre : position de début et de fin de position du robot SUR LA MAP (x,y)
 * (pas en pixel) Retour : void
 */
function dessine_trajectoire(x_map_debut, y_map_debut, x_map_fin, y_map_fin) {
	var canvas = document.getElementById('Trajectoire');
	var context = canvas.getContext('2d');
	// Bleu
	context.strokeStyle = "rgba(0, 0, 255, 1)";
	// Taille de ligne
	context.lineWidth = 4;

	// Conversion des coordonnées
	var x_px_debut = map_to_px(x_map_debut) + carre / 2;
	var y_px_debut = map_to_px(y_map_debut) + carre / 2;
	var x_px_fin = map_to_px(x_map_fin) + carre / 2;
	var y_px_fin = map_to_px(y_map_fin) + carre / 2;

	// Début du trace
	context.beginPath();
	// Ligne
	context.moveTo(x_px_debut, y_px_debut);
	context.lineTo(x_px_fin, y_px_fin);
	// Dessin de la ligne
	context.stroke();
}

/* recuperation JSON */
function recupere_json()
{
	var req = new XMLHttpRequest();
	req.open("GET", "robotControlerExemple.json", true); 
	req.onreadystatechange = monCode;   // la fonction de prise en charge
	req.send(null); 
}

function monCode() 
{ 
   if (req.readyState == 4) 
   { 
        var doc = eval('(' + req.responseText + ')'); 
   }
} 