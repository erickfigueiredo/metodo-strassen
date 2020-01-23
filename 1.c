#include <stdio.h> // Entrada e saida padrao
#include <stdlib.h> // Inclui as quatro funcoes de alocacao dinamica

int main(){
    long long int tam, **mA, **mB, **mC;

    scanf("%lld", &tam);

    // O int* serve para fazer um cast do ponteiro void* que a funcao malloc returna
    // Aprendi que Calloc eh mais lento por zerar o conteudo das posicoes no momento de alocacao, porem na matriz resultante eh interessante utilizar
    mA = (long long int **)malloc(tam * sizeof(long long int*));
    mB = (long long int **)malloc(tam * sizeof(long long int*));
    // Na funcao malloc fazemos a multiplicacao pelo tamanho, ja na calloc, passamos como parametros separados
    mC = (long long int **)calloc(tam, sizeof(long long int*));
    
    // Alocamos as colunas da matriz
    for(int i = 0; i < tam; i++){
        mA[i] = (long long int *)malloc(tam * sizeof(long long int));
        mB[i] = (long long int *)malloc(tam * sizeof(long long int));
        mC[i] = (long long int *)calloc(tam, sizeof(long long int));
    }

    // Le elementos da matriz A
    for(int i = 0; i < tam; i++)
        for(int j = 0; j < tam; j++)
            scanf("%lld", &mA[i][j]);


    //Le elementos da matriz B
    for(int i = 0; i < tam; i++)
        for(int j = 0; j < tam; j++)
            scanf("%lld", &mB[i][j]);

    // Realizamos a multiplicacao pela definicao, como apresentado no trabalho
    for(int i = 0; i < tam; i++)
        for(int j = 0; j < tam; j++)
            for(int k = 0; k < tam; k++)
                mC[i][j] += mA[i][k] * mB[k][j];

    // Exibe a nova matriz obtida
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            (j == tam-1)? printf("%lld", mC[i][j]) : printf("%lld ", mC[i][j]);
        }
        printf("\n");
    }

    // Desaloca memoria apos calculo e exibicao
    for(int i = 0; i < tam; i++){
        free(mA[i]);
        free(mB[i]);
        free(mC[i]);
    }

    free(mA);
    free(mB);
    free(mC);
    return 0;
}