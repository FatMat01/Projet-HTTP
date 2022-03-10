#include "parseur.h"



void tester(){
	char chemin[100]="testFile/test";
	char request[250];
	int curseur = 13;
	char nombre[5];
	FILE *fichier;
	int i =0,a=0,retour =0;;
	

	for(i=0;i<1000;i++){
		sprintf(nombre,"%d",i);
		a =0;
		curseur=13;
		while(a<strlen(nombre)){
			chemin[curseur]=nombre[a];
			a++;
			curseur++;
		}
		chemin[curseur] = '.';
		chemin[curseur+1] = 't';
		chemin[curseur+2] = 'x';
		chemin[curseur+3] = 't';
		chemin[curseur+4] = '\0';

		fichier = fopen(chemin,"r+");
		if (fichier != NULL){
			fgets(request,249,fichier);
			fclose(fichier);
			retour = parseur(request);
			printf("%d : %s : %s\n",retour,chemin,request);
		}
		else{
			printf("erreur ouverture fichier");
		}
	}

}


/* Renvoie le nouvel élément créé dans l'arbre */
stockage* add_node(stockage* tree,char* ptr ,char type){
	stockage *new_elm;
	new_elm = malloc(sizeof(stockage));
	new_elm->ptr_prec = tree;
	tree->ptr_suiv = new_elm;
	new_elm->type = type;
	new_elm->ptr = ptr;
	return new_elm;
}


stockage* delete_node(stockage* tree){
	stockage *new_elm;
	new_elm = tree->ptr_prec;
	new_elm->ptr_suiv=NULL;
	free(tree);
	return new_elm;
}

int parseur(char request[250]){
	
	int repetition = 0,retour=0,erreur=0;
	int fin = 0;
	stockage *tree;
	char *ptr = request;
	if(is_debut(&ptr)){ 												
		while(!is_taille_depasse(ptr) && !fin && !erreur){				
			if(!is_taille_depasse(ptr) && is_mot(&ptr)){	
				tree = add_node(tree,ptr,MOT);		
				if(!is_taille_depasse(ptr) && is_ponc(&ptr)){
					repetition++;
				}
				else{
					erreur = 1;
				}
			}
			else if (!is_taille_depasse(ptr) && is_number(&ptr)){
				
				if(!is_taille_depasse(ptr) && is_separateur(&ptr)){
					repetition++;
				}
				else{
					erreur = 1;
				}
			}
			else{
				if(!is_ponc(&ptr)){
					erreur=1;
				}
				else{
					fin = is_fin(ptr);
					if(fin == 0)  /* si ce n'est pas la fin apres le [ponct]*/
						erreur =1;	/*alors il y a une erreur*/
				}
			}

			fin = is_fin(ptr);
		}
		
	}
	else{
		erreur =1;
	}
	/*si le début et la fin sont correctes*/
	/*si il y a un ordre correcte des séparateur, des mots, des nombres et de la ponctuation*/
	/*et si il y a au moins 2 fois la partie du milieu*/
	if(fin==1 && erreur ==0 && repetition >1){
		retour = 1;			/*alors la requête est syntaxiquement correcte*/
	}

	return retour;
}

/*retourne 1 si le caractère courant est une ponctuation, 0 sinon*/
/*incrémente la position du pointeur de la requête jusqu'au prochain champs*/
int is_ponc(char **ptr){
	int retour=0;
	if((*ptr)[0] == ',' || (*ptr)[0] == '.' || (*ptr)[0] == '!' || (*ptr)[0] == '?' || (*ptr)[0] == ':'){
		retour =1;
		(*ptr)++;
	}
	return retour;
}
/*retourne 1 si le caractère courant est un séparateur, 0 sinon*/
/*incrémente la position du pointeur de la requête jusqu'au prochain champs*/
int is_separateur(char **ptr){
	int retour = 0;
	if ((*ptr)[0] == '-' || (*ptr)[0] == '_' || (*ptr)[0] == '\t' || (*ptr)[0] == ' '){
		retour = 1;
		(*ptr)++;
	}
	return retour;
}
/*retourne 1 si il s'agit d'un début correcte de requête, 0 sinon*/
/*incrémente la position du pointeur de la requête jusqu'au prochain champs*/
int is_debut(char **ptr){
	int retour = 0;

	if(((*ptr)[0] == 's' || (*ptr)[0] == 'S') && ((*ptr)[1] == 't' || (*ptr)[1] == 'T')){
		if (((*ptr)[2] == 'a' || (*ptr)[2] == 'A') && ((*ptr)[3] == 'r' || (*ptr)[3] == 'R') &&((*ptr)[4] == 't' || (*ptr)[4] == 'T'))
			retour = 1;
		(*ptr)+=5;
	}
	return(retour);
}

/*retourne 1 si il s'agit d'une fin correcte de requête, 0 sinon*/
int is_fin(char *ptr){
	int retour = 0;

	if((ptr[0] == 'f' || ptr[0] == 'F') && (ptr[1] == 'i' || ptr[1] == 'I')){
		if ((ptr[2] == 'n' || ptr[2] == 'N') && ptr[3] == '\n')
			retour = 1;
	}
	return(retour);
}

/*retourne 1 si le caractère ourant est une lettre (minuscule ou majuscule), 0 sinon*/
int is_alpha(char **ptr){
	char alphabet[53] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int retour = 0;
	int index = 0;
	while(index<53 && !retour){
		if((*ptr)[0] == alphabet[index]){
			retour = 1;
			(*ptr)++;
		}
		index++;
	}
	return retour;
}

/*retourne 1 si le champs est un mot (peut importe la taille), 0 sinon*/
/*incrémente la position du pointeur de la requête jusqu'au prochain champs*/
int is_mot(char **ptr){
	int retour = 0;
	while(is_alpha(ptr)){
		retour = 1;
	}
	if(retour == 0 || !is_separateur(ptr)){
		retour = 0;
	}
	return retour;
}

/*retourne 1 si le caractère ourant est un chiffre,0 sinon*/
int is_chiffre(char **ptr){
	char nombre[11] = "0123456789";
	int retour = 0;
	int index = 0;
	while(index<10 && !retour){
		if((*ptr)[0] == nombre[index]){
			retour = 1;
			(*ptr)++;
		}
		index++;
	}
	return retour;
}

/*retourne 1 si le champs est un nombre (peut importe la taille)*/
/*incrémente la position du pointeur de la requête jusqu'au prochain champs*/
int is_number(char **ptr){
	int retour = 0;
	while(is_chiffre(ptr)){
		retour = 1;
	}
	return retour;
}

/*on s'assure de ne pas dépasser la taille de la chaine*/
/*retourne 1 si il y a dépassement, 0 sinon*/
int is_taille_depasse(char *ptr){
	return (ptr[0] == '\0');
}
