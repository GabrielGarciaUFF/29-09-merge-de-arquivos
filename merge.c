#include <stdio.h>

void imprime_arquivo(char *nomeArq){
    FILE *arq; //declara ponteiro para arquivo
    //abre arquivo para leitura
    arq = fopen(nomeArq, "r");
    if (arq != NULL){// checa se não deu erro na abertura do arquivo
        char s[10];
        fscanf(arq, "%s", s);
        while (!feof(arq)) {//testa se chegou ao final do arquivo
            printf("%s\n", s);
            fscanf(arq, "%s", s);
        }
        fclose(arq); //fecha arquivo
    }
    else printf("Erro ao abrir arquivo\n");
}

void merge(char *nomeArq1, char *nomeArq2, char *nomeArqMerge) {
    FILE *arq1 = fopen(nomeArq1, "r");
    FILE *arq2 = fopen(nomeArq2, "r");
    FILE *arqMerge = fopen(nomeArqMerge, "w");

    if (arq1 == NULL || arq2 == NULL || arqMerge == NULL) {
        if (arq1) fclose(arq1);
        if (arq2) fclose(arq2);
        if (arqMerge) fclose(arqMerge);
        return;
    }

    int n1, n2;
    int leu1 = fscanf(arq1, "%d", &n1);
    int leu2 = fscanf(arq2, "%d", &n2);

    while (leu1 == 1 && leu2 == 1) {
        if (n1 < n2) {
            fprintf(arqMerge, "%d\n", n1);
            leu1 = fscanf(arq1, "%d", &n1);
        } else if (n2 < n1) {
            fprintf(arqMerge, "%d\n", n2);
            leu2 = fscanf(arq2, "%d", &n2);
        } else { // n1 == n2: grava apenas uma vez para não repetir
            fprintf(arqMerge, "%d\n", n1);
            leu1 = fscanf(arq1, "%d", &n1);
            leu2 = fscanf(arq2, "%d", &n2);
        }
    }

    while (leu1 == 1) {
        fprintf(arqMerge, "%d\n", n1);
        leu1 = fscanf(arq1, "%d", &n1);
    }

    while (leu2 == 1) {
        fprintf(arqMerge, "%d\n", n2);
        leu2 = fscanf(arq2, "%d", &n2);
    }

    fclose(arq1);
    fclose(arq2);
    fclose(arqMerge);
}

int main(int argc, char **argv) {
    merge("numeros1.txt", "numeros2.txt", "merge.txt");
    imprime_arquivo("merge.txt");
}
