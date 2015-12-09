#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Palavrabase {
  char  *nome;
  struct Palavrabase *next;
  struct Palavrafilho *filho;
  int contador;
} Palavrabase;

typedef struct Palavrafilho{
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

int ocorrencia(struct Palavrabase** tamanho, char arr[]);


                  //  fprintf(entrada,"Consulta: %s\n",palavra);
                    //fprintf(entrada,"Sugestao: %s                  %.9f",calculo);
