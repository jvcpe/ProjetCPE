/*
 * Gestion des fleches
 */

/*
 * Fonction reset_fleche Permet de reset l'affichage de l'ombre portée des
 * flèches
 */

var previous_x_robot = 0;
var previous_y_robot = 0;


/*
 * Fonction click_fleche_X Dessine une ombre portée sur la fleche cliquée par
 * l'utilisateur
 */


function click_up() {
	$.post("rest/cmd/UP",{},
		  function(data,status){
			myJson=data;
			MajCanvas();
			stop_deplacement==0;
	});   

	};


function click_down() {
	$.post("rest/cmd/DOWN",
		{},
		  function(data,status){
			myJson=data;
			MajCanvas();
			stop_deplacement==0;
	});    
	};

function click_left() {
	$.post("rest/cmd/LEFT",
		{},
		  function(data,status){
			myJson=data;
			MajCanvas();
			stop_deplacement==0;
	});    
	};

function click_right() {
	$.post("rest/cmd/RIGHT",
		{},
		  function(data,status){
			myJson=data;
			MajCanvas();
			stop_deplacement==0;
	});    
	};
	
function click_telecommande() {
	$.post("rest/cmd/TELECOMMANDE",
		{},
		  function(data,status){
			alert("Post Done received data: " + data + "\nStatus: " + status);
	});   
	};
	
function click_deco() {
	$.post("rest/cmd/DECONNEXION",
		{},
		  function(data,status){
			alert("Post Done received data: " + data + "\nStatus: " + status);
	}); 
	window.location.href = 'http://localhost:8080/Projet_Info_Annee4/JEE/userLogin.jsf';
	    
	};
	
function click_decoAdmin() {
	$.post("rest/cmd/DECONNEXIONADMIN",
		{},
		  function(data,status){
			alert("Post Done received data: " + data + "\nStatus: " + status);
	}); 
	window.location.href = 'http://localhost:8080/Projet_Info_Annee4/JEE/userLogin.jsf';
	    
	};



