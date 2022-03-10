#include <stdio.h>
#include <string.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#define MOT 1
#define PONCT 2
#define NOMBRE 3
#define SEPARATEUR 4


typedef struct stockage stockage;
struct stockage{
	stockage *ptr_prec; /* Pointe vers le noeud precedent */
	stockage *ptr_suiv; /* Pointe vers le noeud suivant */
	char* ptr; /* Pointeur vers le char */
	char type;
};

/* message = debut 2*((mot ponct )/(nombre separateur)) [ponct] fin LF */

int parseur(char request[100]);
int is_ponc(char **ptr);
int is_separateur(char **ptr);
int is_debut(char **ptr);
int is_fin(char *ptr);
int is_alpha(char **ptr);
int is_mot(char **ptr);
int is_chiffre(char **ptr);
int is_number(char **ptr);
int is_taille_depasse(char *ptr);
void tester();
stockage* add_node(stockage* tree,char* ptr ,char type);
stockage* delete_node(stockage* tree);

