#include <c8051f020.h>
#include "CMD_Servomoteur.h"
#include "Declarations_GPIO_BSE.h"
#include <intrins.h>
#include "detection.h"
#include <stdio.h>
#include "Putchar_Getchar.h"
#include "Detec_Obstacle.h"

 
struct INFORMATIONS detection_obstacles (struct INFORMATIONS informations,struct COMMANDES commandes)
{
     
    int angle,ind_AV,ind_AR,Nbre_Val;
    unsigned int Distance_AV = 0, Distance_AR=0;      
    int pas=commandes.DCT_Obst_Resolution;
    unsigned char temps_estime;
		Nbre_Val=2*(180/pas+1)-1;
		ind_AV=90/pas;
		if(90%pas!=0)
			ind_AR=(Nbre_Val-2)-ind_AV;
		else
			ind_AR=(Nbre_Val-1)-ind_AV;
 
		informations.Nbre_Val_obst=0;
    if ( commandes.Etat_DCT_Obst == oui_180 )
    {
        for (angle=-90; angle<=90; angle=angle+pas)
         {
            // position du télémètre
            temps_estime = CMD_Servo_H(angle);
//            tempo_servo(temps_estime);
             
            // calcul de distance
            Distance_AV=MES_Dist_AV();
						*(informations.Tab_Val_Obst+informations.Nbre_Val_obst)=Distance_AV;
            informations.Nbre_Val_obst++; 
             
        }
    }
     
    else if ( commandes.Etat_DCT_Obst == oui_360 )
    {
        for (angle=-90; angle<90; angle=angle+pas)
        {
            // position du télémètre
            temps_estime = CMD_Servo_H(angle);
          //  tempo_servo(temps_estime);
         
            // calcul de distance
            Distance_AV=MES_Dist_AV ();
            Distance_AR=MES_Dist_AR ();

						*(informations.Tab_Val_Obst+ind_AV)=Distance_AV;
						ind_AV++;
            informations.Nbre_Val_obst++;		
					
						if(ind_AR==Nbre_Val-1)
						{
							*(informations.Tab_Val_Obst+ind_AR)=Distance_AR;
							informations.Nbre_Val_obst++;
							ind_AR=0;
						}
						*(informations.Tab_Val_Obst+ind_AR)=Distance_AR;
						ind_AR++;
            informations.Nbre_Val_obst++;
        }
    }
    return informations;
     
}
	
	
	
	
	