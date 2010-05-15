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
#include "SortMerge.h"

#define QTE_ARGUMENTOS 5
/* Argumentos recebidos pelo programa:
       - Nome do arquivo de dados;
       - Nome do arquivo de saida, classificado;
       - Nome do Campo conforme descrito no arquivo de configura��o do arquivo
         de entrada pelo qual ser� feita a classifica��o;
       - Quantidade de mem�ria dispon�vel para o sort.                        */



int main(int argc, char* argv[]) {
    
    /* vari�veis */
    FILE* arqIn;                                 //arquivo de entrada
    FILE* arqOut;                                //sa�da
    FILE* arqCfg;                                //arquivo que contem o header do banco de dados
    FILE** ppFile;                               //vetor de arquivos tempor�rios
    Header* head;
    int numcorridas, numcampos, maxmem, maxreg, tamreg, key;
    

    if(argc != QTE_ARGUMENTOS) {
       printf("Erro argumentos\n");      //TEMPORARIO
       system("pause");
       exit (0);
    }
    
    /* arquivos de entrada e de configura��o */
    AbreArquivoFixo(argv[1], &arqIn, &arqCfg);
  
    /* leitura dos campos */                         
    CarregaHeader(&head, &numcampos, arqCfg);
    
    fclose(arqCfg);
    
    /* key recebe o n�mero do campo de Record usado como chave de ordena��o */
    key = LeChaveOrdena(argv[3], head, numcampos);
    
    if(key == -1) {
       printf("Erro chave\n");         //TEMPORARIO
       system("pause");
       exit (0);
    }

    /* tamanho de um registro do arquivo de entrada */
    tamreg = head[numcampos-1].inicio + head[numcampos-1].tamanho;

    /* n�mero m�ximo de registros que cabem na mem�ria */
    maxreg = ValidaTamMem(argv[4], tamreg);
    
    if(maxreg == -1) {
       printf("Erro memoria\n");         //TEMPORARIO
       system("pause");
       exit (0);
    }
    
    /* vetor de arquivos tempor�rios, j� classificados */
    ppFile = CriaCorrida(arqIn, maxreg, tamreg, key, head, &numcorridas);
    
    fclose(arqIn);
    
    /* arquivo final, classificado */
    //arqOut = SortMerge(ppFile, 0, numcorridas, maxreg, head, key);
    
    //fclose(arqOut);
    
    free(head);
    
    //system("pause");
    
    return 0;
    
}
