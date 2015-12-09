#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include "functions.h"

#define MAX 13


/* Exemplo de abertura e tokeniza??o de um arquivo texto*/

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados
    clock_t start, end, elapsed;
    int lineno=0,i,nconsulta=atoi(argv[4]); //pega o numero de palavras seguintes

    //char nome_arq[]=argv[1];
    FILE * entrada;


	struct Palavrabase *usavel;
	struct Palavrabase *tamanho[MAX];
	for(i=0;i<=MAX;i++) //inicializa as macro listas
        tamanho[i]=NULL;

    char *palavra, *palavranova,linha[1000]; // linhas a serem lidas do arquivo
    char separador[]= {" 0123456789,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};
    char *consultada;

    struct Consulta *lista,*lista2;
    lista=lista2;

    if(argc!=4){
        printf("Numero errado de argumentos.\n");
        return 1;

    }

    entrada = fopen (argv[1], "r"); // abre o arquivo para leitura
    if (entrada == NULL) //se n?o conseguiu abrir o arquivo
    {
        printf ("Erro ao abrir o arquivo %s",argv[1]);
        return 1;
    }
    else // arquivo OK
    {
                                         //percorre todo o arquivo lendo linha por linha
        while (fgets(linha,1000,entrada))
        {
            palavra = strtok (linha, separador); //considera qquer caractere n?o alfab?tico como separador
            palavra=tolower(palavra);
            while (palavra != NULL)
            {
                palavranova = strtok (NULL, separador);  //pega a proxima palavra tambem
                palavranova=tolower(palavra);

                if(strlen(palavra)>14){
                    usavel=tamanho[13];
                    addpalavraunica(usavel, palavra, palavranova);  //ativa a função de adicionar as palavras maiores que 13 caracteres
                }
                else{
                    usavel=tamanho[strlen(palavra)-1];
                    addpalavraunica(usavel,palavra,palavranova);
                }
                palavra= palavranova;  //coloca a proxima palavra como a atual
            }
        }
    }
    fclose (entrada); //fecha o arquivo

    start=clock(); //inicia a contagem do tempo;

    entrada=fopen(argv[2],"r");
    if(entrada==NULL){
        printf("Erro ao abrir o arquivo %s",argv[2]);
        return 0;

    }
    else{
        while (fgets(linha,1000,entrada)){
            palavra = strtok (linha, separador); //considera qquer caractere n?o alfab?tico como separador
            palavra=tolower(palavra);
            while (palavra != NULL){
                lista2->nome=palavra;
                lista2->prox=malloc(sizeof(Consulta));
                lista2=lista2->prox;
                lista2->prox=NULL;
            }
        }


    }
    fclose(entrada);

    entrada=fopen(argv[3],"w"); //abre o arquivo de saída para escrita
    if(entrada==NULL){   //se nao conseguiu abrir o arquivo
        printf("Erro ao abrir o arquivo %s",argv[3]);
        return -1;
    }
    else{  //arquivo ok
        while(lista!=NULL){  //passa por todas as palavras pedidas na consulta
            palavra=lista->nome;
            if(strlen(palavra)>14)
                    usavel=tamanho[13];
            else
                usavel=tamanho[strlen(palavra)-1];  //acha em qual arvore de tamanho esta a palavra de consulta
            while(usavel!=NULL){         //passa por todas as palavras na arvore
                if(usavel->nome==palavra){
                    fprintf(entrada,"Consulta: %s",palavra);

                }
                else
                    usavel=usavel->next;
                if(usavel=NULL)
                    fprintf(entrada,"Palavra %s não se encontra no arquivo\n",lista->nome);
            }

        }
    }




    end=clock(); //l� o tempo final
    elapsed = 1000 * (end - start) / (CLOCKS_PER_SEC); //calcula o tempo decorrido em milissegundos
    fprintf(entrada,"Tempo: %ld ms\n",elapsed); //escreve no arquivo
    fclose(entrada);  //fecha o arquivo




    return 0;
}
