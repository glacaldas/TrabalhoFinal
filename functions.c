#include <stdio.h>
#include <stdlib.h>
typedef struct Palavrabase {
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




void filho(Palavrafilho *base, char arr[]){
	while(base!= NULL){
		if(base->nome==arr){       //se achar um filho com o a palavra, adiciona uma ocorrencia e sai da função
			base->contador++;
			return 1;
			}
		else
			base=base->prox  ; //continua procurando o mesmo nome



	}
	Palavrafilho *filho=malloc(sizeof(Palavrafilho));
	base=filho;
	base->nome=arr;
	base->prox=NULL;
	base->contador=1;  //coloca nodo com ocorrencia 1
}

void addpalavraunica(Palavrabase *base, char arr[], char arrnova[]){
    while(base!=NULL){             //procura uma palavra unica igual a palavra dada
        if(base->nome==arr){         //se acha
            base->contador++;             //adiciona 1 ao nuemero de ocorrencias
            filho(base->filho,arrnova);//pega a proxima palavra e usa a função de adicionar filho
            mergeSort(&base->filho); //sorta a lista de palavras consequentes
            return 1;
            }
        else
            base=base->next;           //continua procurando

    }

	Palavrabase *foop=malloc(sizeof(Palavrabase))  ;//se nao achar, adiciona um nodo
    foop->nome=arr;
    foop->contador=1;
	foop->next=NULL;
	foop->filho=NULL;
	base=foop;
	filho(base->filho,arrnova);
}


int ocorrencia(struct Palavrabase** tamanho, char arr[]){
    struct Palavrabase *base;
    if(strlen(arr)>13+1)
        base=tamanho[13];
    else
        base=tamanho[strlen(arr)];
    while(base!=NULL){
        if(base->nome==arr)
            return base->contador;
        else
            base=base->next;

    }
}


void split(Palavrafilho *head, Palavrafilho **front, Palavrafilho **back){

	Palavrafilho * fast = head->prox;
	Palavrafilho * slow = head;

	while(fast){
		fast = fast->prox;
		if(fast){
			fast = fast->prox;
			slow = slow->prox;
		}
	}
	*front = head;
	*back = slow->prox;
	slow->prox = NULL;

}
Palavrafilho * merge(Palavrafilho *a, Palavrafilho *b){
    Palavrafilho *result = NULL;
    if(a ==  NULL)
        return b;
    else if(b == NULL)
        return a;


      if(a->contador <= b->contador){
         result = a;

         result->prox = merge(a->prox,b);
      }
      else {
        result = b;

        result->prox = merge(a,b->prox);
      }
      return result;
}
void mergeSort(Palavrafilho **headRef){
	Palavrafilho * front, *back;
	Palavrafilho * head  = *headRef;
	if(head == NULL || head->prox == NULL)
		return;

	split(head, &front, &back);
	mergeSort(&front);
	mergeSort(&back);

	*headRef = merge(front, back);
}
