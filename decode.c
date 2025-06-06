#include <stdio.h>
#include <string.h>
#include "./huf.h"



/*=============================================================
*
UNIFAL = Universidade Federal de Alfenas .
*
BACHARELADO EM CIENCIA DA COMPUTACAO.
* Trabalho . . : Decodificador do formato PGH
* Professor . : Luiz Eduardo da Silva
* Aluno . . . . . : Felipe Araújo Correia
* Data . . . . . . : 09/06/2025
*=============================================================*/


int achaPixel(int root, char byte){
    if(byte == 0){
        return node[root].left;
    }
    return node[root].right;


}

void ler_histograma(FILE *file, int ml, int *hist){
    int valor;
    unsigned char byte[4];
    for(int i = 0; i <=ml; i++){
        valor = 0;
        fread(byte, 1,sizeof(byte), file);
        for (int j = 0; j < 4; j++){
            valor |= byte[j] << j * 8;
        }
        hist[i] = valor;
        //printf("%d\n", byte[i]);    
    }
}

void ler_cores(FILE *file, int *ml){
    fscanf(file, "%d ", ml);
}

void ler_cabecalho(char *line,FILE *file){

    fgets(line, 80, file);

    fgets(line, 80, file);
    while (strchr(line, '#')){
        fgets(line, 80, file);
    }

}

void ler_tamanho(char *line, int *m, int*n){
    sscanf(line, "%d %d", m, n);
}


int achar_tamanho_arquivo(char *filename){
    FILE *file = fopen(filename, "rb");
    fseek(file, 0L, SEEK_END);
    int fim = ftell(file);
    fclose(file);

    return fim;
    
}

int main(int argc, char* argv[]) {
  
    char filename[100] = "";
    strcat(filename, argv[1]);
    
    FILE *file = fopen(filename, "rb");

    

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int fimDoArquivo = achar_tamanho_arquivo(filename);



    char *ponto = strrchr(filename, '.');
    *ponto = '\0'; 


    char line[100];
    int nl;
    int nc;
    int ml;
    
    ler_cabecalho(line, file);

    ler_tamanho(line,&nl,&nc);
    
    ler_cores(file, &ml);
    
    unsigned int hist[ml];

    ler_histograma(file,ml, hist);

    int atual = ftell(file);
    
    int tamanhoRestante = fimDoArquivo - atual;
    unsigned char huff[tamanhoRestante];

    fread(huff, tamanhoRestante,sizeof(huff), file);

    int raizHuff = buildTree(hist, ml);
    unsigned char byte;

   

    int percorreHuff = raizHuff;
    int n = 0;
    int conta = 0;

    strcat(filename, ".pgm");
    FILE *img = fopen(filename,"wt");
    fprintf(img, "P2\n");
    fprintf(img, "%d %d \n", nl, nc);
    fprintf(img, "%d \n", ml);

    while(conta < tamanhoRestante){
        for(int j = 7; j >= 0; j--){
            byte = (huff[conta] >> j) & 1;
            percorreHuff = achaPixel(percorreHuff, byte);
            if(node[percorreHuff].left == -1 && node[percorreHuff].right == -1){
                fprintf(img,"%d ", percorreHuff);
                percorreHuff = raizHuff;
                n++;
            }
            if(n == nc){
                fprintf(img,"\n");
                n = 0;
            }
            
                        
        }
        conta++;
   
    }

   fclose(img);
    

    

    

    return 0;
}
