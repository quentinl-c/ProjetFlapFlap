#include <stdio.h>
#include <stdlib.h>

/** This function writes the maximum score on a file
**/
void scoreMaxRecording(int score){
	FILE *fichier = NULL;
	fichier = fopen("FichierScore.txt", "w");
	if(fichier == NULL){
		fprintf(stderr, "Impossible d'ouvrir le fichier score \n" );
	}
	else{
		fprintf(fichier,"%d", score);
		fclose(fichier);
	}

}

/** This function reads the maximum score written before on the file so that we can show it during the game
**/
int getScoreMax(){
    FILE *fichier = NULL;
    fichier = fopen("FichierScore.txt", "r");
    if(fichier == NULL){
		fprintf(stderr, "Impossible d'ouvrir le fichier score \n" );
		return 1;
	}
	else{
		int scoreRead;
		fscanf(fichier,"%d",&scoreRead);
		fclose(fichier);
		return scoreRead;
	}
	fclose(fichier);
}
