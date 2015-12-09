#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include "functions.h"

#define MAX 13

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados
    clock_t start, end, elapsed;
    int i,nconsulta=atoi(argv[4]); //pega o numero de palavras seguintes
    int valorA,valorB,valorC;
    //char nome_arq[]=argv[1];
    FILE * entrada;


	struct Palavrabase *usavel;
	struct Palavrabase* tamanho[13];
	for(i=0;i<=13;i++) //inicializa as macro listas
        tamanho[i]=NULL;

    struct Palavrafilho *cabeca;

    char *palavra, *palavranova,linha[1000]; // linhas a serem lidas do arquivo
    char separador[]= {" 0123456789,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};

    struct Consulta *lista,*lista2;
    lista=lista2;

       if(argc!=5){  //se o numero de argumentos nao for correto, mostra mensagem de erro e fecha o programa
        printf("Numero errado de argumentos.\n");
        return 1;
        }

    if(argc!=5){  //se o numero de argumentos nao for correto, mostra mensagem de erro e fecha o programa
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

                if(strlen(palavra)>13+1){
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
    free(palavra);
    start=clock(); //inicia a contagem do tempo;

    entrada=fopen(argv[2],"r");
    if(entrada==NULL){
        printf("Erro ao abrir o arquivo %s",argv[2]);
        return 0;

    }
    else{
        while (fgets(linha,1000,entrada)){
            palavra = strtok (linha, separador); //considera qquer caractere n?o alfab?tico como separador
            palavra=tolower(palavra); //deixa em caixa aixa
            while (palavra != NULL){
                lista2->nome=palavra;  //aloca a palavra
                lista2->prox=malloc(sizeof(Consulta));  //aloca memoria pro ponteiro pra proxima
                lista2=lista2->prox; //coloca na proxima
                lista2->prox=NULL;  //deixa como nula
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
            palavra=lista->nome; //pega a palavra do momento
            fprintf(entrada,"Consulta: %s\n",palavra);
            if(strlen(palavra)>13+1)
                usavel=tamanho[13]; //se a palavra tiver mais de 13 caracteres, vai pra ultima lista
            else
                usavel=tamanho[strlen(palavra)]; //caso contrario, vai pra lista relevante
            while(usavel!=NULL){ //ate o fim da lista relevante
                if(usavel->nome==palavra){ //se achou a palavra dada
                    valorB=usavel->contador;  //pega o valor freq(a)
                    cabeca=usavel->filho;  //pega a lista de palavras consequentes
                    for(i=0;i<nconsulta;i++){ //com relação ao argv[4], repete o numero de vezes
                        valorC=ocorrencia(tamanho,cabeca->nome);//pega o valor freq(b)
                        valorA=cabeca->contador;  //pega o valor freq(a,b)
                        fprintf(entrada,"Sugestao: %s        (%0.9f)\n",cabeca->nome,valorA/(sqrt(valorB*valorC))); //printa
                        cabeca=cabeca->prox; //passa pra proxima palavra consequente da palavra dada
                    }
                }
                else
                    usavel=usavel->next;  //passa pra proxima

            }
            fprintf(entrada,"\n");
            lista=lista->prox; //passa pra proxima consulta
        }
    }




    end=clock(); //l� o tempo final
    elapsed = 1000 * (end - start) / (CLOCKS_PER_SEC); //calcula o tempo decorrido em milissegundos
    fprintf(entrada,"Tempo: %ld ms\n",elapsed); //escreve no arquivo
    fclose(entrada);  //fecha o arquivo




    return 0;
}
