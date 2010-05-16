/******************************************************************************/
/* Grupo 2:                                                                   */
/*          Felipe Augusto da Silva    RA 096993                              */
/*          Lucas Barbi Rezende        RA 097042                              */
/*          Luiz Claudio Carvalho      RA 800578                              */
/*                                                                            */
/* MC236EF  1o semestre 2010                                           UNICAMP*/
/* Laborat�rio    03 
      - Processamento Co-Sequencial de arquivos
      - Implementa��o de Sort-Merge
   
/******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "envelope.h"

#define tamPrimCampoHd 20
#define tamUltCampoHd 40


/* Defini��o de tipo booleano */
typedef enum {false, true} Boolean;


/* Defini��o de um vetor de ponteiros para caractere. Uma vez inicializados,
   cada um dos ponteiros do vetor ir� apontar para a posi��o inicial do
   conte�do do campo[i] do registro correspondente. Caso seja necess�rio
   carregar mais de um registro do banco de dados na mem�ria, cada um de seus 
   campos poder� ser acessado por: registro[m].campo[n]   */
typedef char** Record;


/* Defini��o de estrutura que armazena as caracter�sticas de um campo de um
   arquivo de dados. Estas caracter�sticas devem ser extra�das de um arquivo de
   configura��o ou de uma se��o espec�fica do arquivo de dados */
typedef struct {
        char nome[tamPrimCampoHd+1];
        char tipo;
        int inicio;
        int tamanho;
        Boolean obrig;
        char msg[tamUltCampoHd+1];
        } Header;



typedef struct Ordena {
  Record  reg;
  int  index;
  struct Ordena *prox;
} Ordena, *RecSM;




void AbreArquivoFixo(char* nome, FILE** arqIn, FILE** arqCfg);
/* Abre o arquivo de entrada e seu respectivo arquivo de configura��o (.cfg) */ 
  
void CarregaHeader(Header** h, int* numcampos, FILE* arqCfg);
/* Carrega o vetor head com os campos do banco de dados definido por arqCfg */
  
int LeChaveOrdena(char* nomecampo, Header* head, int numcampos);  
/* Retorna o �ndice do campo chave de ordena��o para uso em Record.
   Retorna -1 se n�o houver tal campo nas configura��es do arquivo de dados */

int ValidaTamMem(char* arg, int tamreg);
/* Verifica se arg representa um inteiro != 0 e retorna seu valor dividido
   por tam. Retorna -1 em caso de erro. */

int NumRegs(FILE* arq, int tamreg);
/*  Retorna o numero total de registros de tamanho 'tamreg' em 'arq' */

FILE** CriaCorrida(FILE* arq, int maxreg, int tamreg, int key, Header* h, int numcampos, int* n, int totalregs, int* nread, int* nwrite);
/* Retorna um vetor de arquivos (corrida) cada um deles com max registros de arq,
   de tamanho tam, ordenados por key. Coloca em n o n�mero de arquivos da 
   corrida */

void ImprimeRegFixo(Record rec, FILE* arq, int numcampos);
/* Grava, na posi��o corrente em arq, os dados de rec.                        */

void OrdenaRegistros(Record** rec, int i, int key);
/* Ordena um vetor de registros com i elementos, usando o campo indicado por
   key como chave de ordena��o                                                */

FILE* SortMerge(FILE** ppFile, int inf, int sup, int max, Header h, int key);
/* Invoca CriaOrdNulo() para inicializar um vetor de estruturas de ordena��o 
      (RecSM). Utiliza para isso os dados de h para alocar a mem�ria necess�ria.
   Carrega este vetor com os registros de topo dos 'max' 1o.s arquivos
      a partir de ppFile[inf], inserindo os elementos na ordem determinada
      pela chave de ordena��o
   Cria um novo arquivo tempor�rio e invoca CospePuxa() para inserir neste o 'menor'
      dos registros do vetor de ordena��o neste arquivo, puxar o pr�ximo registro
      do arquivo de onde ele veio, inseri-lo na estrutura de ordena��o na posi��o
      correta e cuspir o pr�ximo para o arquivo tempor�rio, at� que os 'max' arquivos
      tenham sido esgotados. Utiliza uma vari�vel local (acabou), inicialmente 
      igual a max, decrementando esta vari�vel cada vez que encontrar um eof e parando
      quando chegar a zero.
   Acabando de tratar estes 'max' arquivos, a fun��o apaga os 'max' arquivos 
      tratados. Altera os �ndices de ppFile para que os arquivos ainda n�o tratados
      ocupem as posi��es 'inf+1', 'inf+2', etc at� o fim. Os �ndices que n�o 
      est�o mais em uso devem passar a apontar para NULL.
   Se o novo 'sup' (�ndice do �ltimo arquivo v�lido de ppFile) for menor que o 
      antigo 'inf' � porque esta corrida acabou. Se for este o caso, chama a si 
      mesma com inf = 0. Sen�o chama com inf = 1 para acabar a corrida.
*/














