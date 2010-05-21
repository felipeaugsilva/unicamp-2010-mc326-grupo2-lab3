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
#include <ctype.h>


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

FILE** CriaCorrida(FILE* arq, int maxreg, int tamreg, int key, Header* h, int numcampos, int* n, int* totalregs, int* nread, int* nwrite);
/* Retorna um vetor de arquivos (corrida) cada um deles com max registros de arq,
   de tamanho tam, ordenados por key. Coloca em n o n�mero de arquivos da 
   corrida */

FILE* SortMerge(FILE** ppFile, int* corridas, int max, Header* h, int key, 
   int ncampos, int tamreg, int* nread, int* nwrite, int* nfases, char* saida);
/* Efetua Merge dos '*corridas' arquivos de 'ppFile', todos com 'ncampos' campos, 
   registros de tamanho total tamreg e leiaute indicado em 'h'. Os registros s�o 
   ordenados pela chave 'key'. O n�mero m�ximo de registros simultaneamente em 
   mem�ria � indicado por 'max'. Atualiza em 'corridas', 'nwrite', 'nread' e
   'nfases' o n�mero de arquivos tempor�rios criados, escritas e leituras de
   registros e fases de merge realizadas. Grava o resultado com nome 'saida'.
*/
