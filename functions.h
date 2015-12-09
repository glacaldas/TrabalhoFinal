#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char  *nome;
  struct Palavrabase *next;
  struct Palavrafilho *filho;
  int contador;
} Palavrabase;

typedef struct PalavraSeguinte{
    char *nome;
    struct Palavrafilho *prox;
    int contador;

}Palavrafilho;

typedef struct Consulta{
    char *nome;
    struct Consulta *prox;

} Consulta;


void filho(Palavrafilho *base, char arr[]);

void addpalavraunica(Palavrabase *base, char arr[], char arrnova[]);
