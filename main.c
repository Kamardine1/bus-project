//NOM prénom étudiant 1 : MIRGHANE MOHAMED Kamardine
//NOM prénom étudiant 2 : BECKER Pierre-Antoine

#include "SDL.h"
#include "maSDL.h"
#include "SDL_VSYNC.h"

#include "types.h"
#include "ligneBus.h"
#include "source.h"
#include "listeDouble.h"
#include "Tri.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>




/*--------- Main ---------------------*/
int main(int argc, char* argv[])
{
    int nbtotalStations=0,nbligneTotal=0;
    FILE *pFichier = NULL;
    pFichier = fopen("StationsEtLignesDeBus.data","r");

    fscanf(pFichier,"%d %d\n",&nbtotalStations,&nbligneTotal);
    fclose(pFichier);
    //SDL
    //fênetre dans windows
    SDL_Window *gWindow = NULL;
    SDL_Init(SDL_INIT_VIDEO);

    //la texture (chargée dans la ram de la carte graphique) target representant tout le jeu
    SDL_Renderer* gRenderer = NULL;

    //Les textures, le type Ltexture est défini dans SDL_VSYNC.h
    LTexture gSpriteBus;
    LTexture gSpriteArretBus;

    //Start up SDL and create window
	if( !init(&gWindow,&gRenderer) )  //initialise la fenetre SDL et charge UNE texture
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadAnimation(&gSpriteBus, gRenderer, "./data/4bus.png")
            || !loadSprite(&gSpriteArretBus, gRenderer, "./data/arret_bus_50x27.png"))
        {
			fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
		}
		else
		{

        /**********************************************************************/
        /*                                                                    */
        /*              DEFINISSEZ/INITIALISER ICI VOS VARIABLES              */
        /*                                                                    */
        /**********************************************************************/

        TlisteStation* monReseau = creerAllLigne();

        //Pour afficher les lignes :
        for(int i =0 ; i<nbligneTotal;i++){
            afficheListe(monReseau[i]);
        }


        /**********************************************/
        /*          Pour Fusionner 2 lignes           */
        /**********************************************/


        //nbligneTotal=Fusion2Ligne(monReseau,nbligneTotal,1,2);


        /**********************************************/
        /*          Pour Effacer une station          */
        /**********************************************/
        //Si la station est le depart de la ligne
        /*
        printf("Affichage avant la suppression \n");
        afficheListe(monReseau[1]);
        monReseau[1]=supprimerStationParId(monReseau[1],2,6);
        printf("\nAffichage apres la suppression \n");
        afficheListe(monReseau[1]);
        printf("\n");
        */

        //Si la station est n'importe où dans la ligne
        /*
        printf("Affichage avant la suppression \n");
        afficheListe(monReseau[1]);
        monReseau[1]=supprimerStationParId(monReseau[1],2,8);
        printf("\nAffichage apres la suppression \n");
        afficheListe(monReseau[1]);
        printf("\n");
        */

        //Si la station est le terminus de la ligne
        /*
        printf("Affichage avant la suppression \n");
        afficheListe(monReseau[1]);
        monReseau[1]=supprimerStationParId(monReseau[1],2,10);
        printf("\nAffichage apres la suppression \n");
        afficheListe(monReseau[1]);
        printf("\n");
        */

        /**********************************************/
        /*        Pour Rendre ligne Circulaire        */
        /**********************************************/

        //Ca boucle à l'infini car les fonctions de la bibliotheques des listes doublements chainés sont prevu pour travailler
        //avec des listes finis alors que la y'a pas de fin vu que c'est circulaire.
        /*
        printf("Affichage de la ligne avant l'operation\n");
        afficheListe(monReseau[2]);
        printf("\n");
        monReseau[2]=TransformCirculaire(monReseau[2],3);
        printf("Affichage de la ligne apres l'operation\n");
        afficheListe(monReseau[2]);
        */


        //création des bus
        Tbus bus1 = creeBus(1,monReseau[0]); //A commenter lorsque vous decommenter les blocs de codes pour avoir plusieurs bus

        // A decommenter pour avoir plusieurs bus
        //Note : nombre de bus = nombre de ligne

        /*
        Tbus depot[nbligneTotal];

        for(int i=0;i<nbligneTotal;i++){
            depot[i]=creeBus(i+1,monReseau[i]);
        }
        */

        //affiche sur la console les stations et troncons des lignes de bus

        for(int i=0;i<nbligneTotal;i++){
            afficheConsoleLigneBus(monReseau[i]);
        }

        //Current animation frame
        int frame = 0;

        //affiche et initialise le sprite du bus au départ
        //A commenter lorsque vous decommenter les blocs de codes pour avoir plusieurs bus
        Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( bus1 ), getPosYBus( bus1 ), getIdFrame(frame));

        // A decommenter pour avoir plusieurs bus
        /*
        for(int i =0;i<nbligneTotal;i++){
            Affiche_Sprite(&gSpriteBus,gRenderer,getPosXBus(depot[i]) ,getPosYBus(depot[i]),getIdFrame(frame));
        }
        */

        // boucle principale du jeu
        int cont = 1;

        //A commenter lorsque vous decommenter les blocs de codes pour avoir plusieurs bus
        int  incXDeplSpriteBus = 0, incYDeplSpriteBus = 0; //déplacement du sprite du bus à chaque passage dans la boucle principale

        // A decommenter pour avoir plusieurs bus
        /*
        int incXDeplSpriteBus[nbligneTotal];
        int incYDeplSpriteBus[nbligneTotal];

        for(int i = 0; i < nbligneTotal; i++) {
            incXDeplSpriteBus[i] = 0;
            incYDeplSpriteBus[i] = 0;
        }
        */


        while ( cont != 0 ){
                SDL_PumpEvents(); //do events

                /***********************************************************************/
                /*                                                                     */
                //APPELEZ ICI VOS FONCTIONS QUI FONT EVOLUER LE "JEU"
                /*                                                                     */
                /***********************************************************************/

                //deplaceBus gère le déplacement du bus sur sa ligne, selon son sens du parcours de la ligne;
                //met à jour les variations en X et Y pour déplacer le sprite du Bus (cf ligne 151)

                //A commenter lorsque vous decommenter les blocs de codes pour avoir plusieurs bus
                deplaceBus(bus1, getSensParcours(bus1), &incXDeplSpriteBus, &incYDeplSpriteBus);

                // A decommenter pour avoir plusieurs bus
                /*
                for(int i=0;i<nbligneTotal;i++){
                    deplaceBus(depot[i],getSensParcours(depot[i]), &incXDeplSpriteBus[i], &incYDeplSpriteBus[i]);
                }
                */

                //A commenter lorsque vous decommenter les blocs de codes pour avoir plusieurs bus (deja commenté car inutile et surcharge d'information)
                //afficheCoordonneesBus( bus1 );  //utile ? -> non , car affiche en boucle meme lorsque nous somme arrive au terminus

                // A decommenter pour avoir plusieurs bus
                /*
                for(int i = 0; i<nbtotalBus;i++){
                    afficheCoordonneesBus(depot[i]);
                }*/


                const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);
                if(pKeyStates[SDL_SCANCODE_T] ){
                    char choix;
                    char sens;
                    char modele;
                    int k;
                    printf("\nVeuillez entrer la ligne à trier :\n");
                    scanf("%d", &k);
                    printf("Tapez c pour trier par cout , d pour trier par date\n");
                    scanf(" %c", &modele);
                    printf("Tapez s pour ne prendre en compte que les stations , ou t pour uniquement les troncons : \n");
                    scanf(" %c", &choix);
                    printf("Tapez c trier par ordre croissant, ou d par ordre decroissant : \n");
                    scanf(" %c", &sens);

                    if(modele=='c'){
                        if(choix == 's' && sens == 'd') {
                            triSelectionListeParPointeur(monReseau[k-1], compCout_S1_sup_S2, ARRET);
                            //afficheListe(monReseau[k-1]); // pour voir le resultat
                        }else if (choix == 't' && sens == 'd'){
                            triSelectionListeParPointeur(monReseau[k-1], compCout_S1_sup_S2, TRONCON);
                            //afficheListe(monReseau[k-1]); // pour voir le resultat
                        }
                    }else if(modele=='d'){
                        triSelectionListeParPointeur(monReseau[k-1],compLastDate_S1_Avant_S2,ARRET);
                        //afficheListe(monReseau[k-1]); // pour voir le resultat
                    }

                }
                //les touches sont lues en Qwerty
                if ( pKeyStates[SDL_SCANCODE_UP] ){

                        printf("\nTouche haute, sens déplacement depart vers terminus\n");

                        //A commenter lorsque vous decommenter les blocs de codes pour avoir plusieurs bus
                        setSensParcours(bus1, depart_vers_arrivee );

                        // A decommenter pour avoir plusieurs bus
                        /*
                        for(int i=0;i<nbligneTotal;i++){
                            setSensParcours(depot[i], depart_vers_arrivee );
                        }
                        */

                }
                if ( pKeyStates[SDL_SCANCODE_DOWN] ){

                        printf("\nTouche basse, sens déplacement terminus vers depart\n");

                        //A commenter lorsque vous decommenter les blocs de codes pour avoir plusieurs bus
                        setSensParcours(bus1, arrivee_vers_depart );

                        // A decommenter pour avoir plusieurs bus
                        /*
                        for(int i=0;i<nbligneTotal;i++){
                            setSensParcours(depot[i], arrivee_vers_depart );
                        }
                        */

                }
                // A decommenter pour avoir plusieurs bus
                /*
                if ( pKeyStates[SDL_SCANCODE_0] ){

                        printf("\nTouche 0, Les Bus au depart des lignes correspondantes à leurs numéro\n");

                        for(int i =0;i<nbligneTotal;i++){
                            busSurStation(depot[i], monReseau[i], depart_vers_arrivee);
                            Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( depot[i] ), getPosYBus( depot[i] ), getIdFrame(frame));
                        }
                }*/
                if ( pKeyStates[SDL_SCANCODE_1] ){

                        printf("\nTouche 1, Bus 1 au départ de la ligne 1\n");

                        //A commenter lorsque vous decommenter les blocs de codes pour avoir plusieurs bus (les 2 lignes ci dessous)
                        busSurStation(bus1, monReseau[0], depart_vers_arrivee);
                        Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( bus1 ), getPosYBus( bus1 ), getIdFrame(frame));

                        // A decommenter pour avoir plusieurs bus
                        /*
                        busSurStation(depot[0], monReseau[0], depart_vers_arrivee);
                        Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( depot[0] ), getPosYBus( depot[0] ), getIdFrame(frame));
                        */

                }
                if ( pKeyStates[SDL_SCANCODE_2] ){

                        printf("\nTouche 2, Bus 1 au départ de la ligne 2\n");

                        //A commenter lorsque vous decommenter les blocs de codes pour avoir plusieurs bus (les 2 lignes ci dessous)
                        busSurStation(bus1, monReseau[0], depart_vers_arrivee);
                        Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( bus1 ), getPosYBus( bus1 ), getIdFrame(frame));

                        // A decommenter pour avoir plusieurs bus
                        /*
                        busSurStation(depot[0], monReseau[1], depart_vers_arrivee);
                        Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( depot[0] ), getPosYBus( depot[0] ), getIdFrame(frame));
                        */

                }
                if ( pKeyStates[SDL_SCANCODE_3] ){
                        printf("\nTouche 3, Bus 1 au départ de la ligne 3\n");

                        //A commenter lorsque vous decommenter les blocs de codes pour avoir plusieurs bus (les 2 lignes ci dessous)
                        busSurStation(bus1, monReseau[0], depart_vers_arrivee);
                        Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( bus1 ), getPosYBus( bus1 ), getIdFrame(frame));

                        // A decommenter pour avoir plusieurs bus
                        /*
                        busSurStation(depot[0], monReseau[2], depart_vers_arrivee);
                        Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( depot[0] ), getPosYBus( depot[0] ), getIdFrame(frame));
                        */

                }
                // A decommenter pour avoir plusieurs bus
                /*
                if ( pKeyStates[SDL_SCANCODE_4] ){

                        printf("\nTouche 4, Bus 2 au départ de la ligne 1\n");
                        busSurStation(depot[1], monReseau[0], depart_vers_arrivee);
                        Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( depot[1] ), getPosYBus( depot[1] ), getIdFrame(frame));

                }
                if ( pKeyStates[SDL_SCANCODE_5] ){

                        printf("\nTouche 5, Bus 2 au départ de la ligne 2\n");
                        busSurStation(depot[1], monReseau[1], depart_vers_arrivee);
                        Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( depot[1] ), getPosYBus( depot[1] ), getIdFrame(frame));

                }
                if ( pKeyStates[SDL_SCANCODE_6] ){

                        printf("\nTouche 6, Bus 2 au départ de la ligne 3\n");
                        busSurStation(depot[1], monReseau[2], depart_vers_arrivee);
                        Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( depot[1] ), getPosYBus( depot[1] ), getIdFrame(frame));

                }
                if ( pKeyStates[SDL_SCANCODE_7] ){

                        printf("\nTouche 7, Bus 3 au départ de la ligne 1\n");
                        busSurStation(depot[2], monReseau[0], depart_vers_arrivee);
                        Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( depot[2] ), getPosYBus( depot[2] ), getIdFrame(frame));

                }
                if ( pKeyStates[SDL_SCANCODE_8] ){

                        printf("\nTouche 8, Bus 3 au départ de la ligne 2\n");
                        busSurStation(depot[2], monReseau[1], depart_vers_arrivee);
                        Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( depot[2] ), getPosYBus( depot[2] ), getIdFrame(frame));

                }
                if ( pKeyStates[SDL_SCANCODE_9] ){

                        printf("\nTouche 9, Bus 3 au départ de la ligne 3\n");
                        busSurStation(depot[2], monReseau[2], depart_vers_arrivee);
                        Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( depot[2] ), getPosYBus( depot[2] ), getIdFrame(frame));

                }*/
                if ( pKeyStates[SDL_SCANCODE_ESCAPE] ){

                        printf("\nTouche ECHAP\n\n\n");
                        cont = 0;  //sortie de la boucle
                }

                //affichage du jeu à chaque tour

                //on efface toute la fenêtre
                efface_fenetre_texture(gRenderer);

                //Déplacement de sprite du bus sur la texture

                //A commenter lorsque vous decommenter les blocs de codes pour avoir plusieurs bus
                Deplace_Sprite(&gSpriteBus, gRenderer, incXDeplSpriteBus,incYDeplSpriteBus,getIdFrame(frame));

                // A decommenter pour avoir plusieurs bus
                /*
                for(int i =0;i<nbligneTotal;i++){
                    Deplace_Sprite(&gSpriteBus, gRenderer, incXDeplSpriteBus[i],incYDeplSpriteBus[i],getIdFrame(frame));
                }
                */


                //reaffichage à chaque tour de toutes les stations

                for(int i=0;i<nbligneTotal;i++){
                    DessineUneLigneBus(monReseau[i],gSpriteArretBus,gRenderer);
                }

                //affichage de la texture ainsi mis à jour
                maj_fenetre_texture(gRenderer);

                SDL_Delay(1); //valeur du délai modifiable en fonction de votre CPU
                ++frame;
            }
        //fin boucle du jeu
        }
	}


	//Free resources and close SDL

	free_Ltexture(&gSpriteBus);
	free_Ltexture(&gSpriteArretBus);
	//fclose(pFichier);
	close(gWindow, gRenderer);

    return 0;
}
