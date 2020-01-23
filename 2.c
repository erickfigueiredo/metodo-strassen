#include <stdio.h>  // Entrada e saida padrao
#include <stdlib.h> // Inclui as quatro funcoes de alocacao dinamica

// Exibe a matriz
void imprimeMatriz(long long int **m, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            (j == tam - 1) ? printf("%lld", m[i][j]) : printf("%lld ", m[i][j]);
        }
        printf("\n");
    }
}

// Aloca matriz com o Malloc
long long int **alocaMatrizM(int tam)
{
    long long int **matriz;
    matriz = (long long int **)malloc(tam * sizeof(long long int *));
    for (int i = 0; i < tam; i++)
    {
        matriz[i] = (long long int *)malloc(tam * sizeof(long long int));
    }
    return matriz;
}

// Aloca matriz com o Calloc
long long int **alocaMatrizC(int tam)
{
    long long int **matriz;
    matriz = (long long int **)calloc(tam, sizeof(long long int *));
    for (int i = 0; i < tam; i++)
    {
        matriz[i] = (long long int *)calloc(tam, sizeof(long long int));
    }
    return matriz;
}

// Desaloca a matriz do monte
void desalocaMatriz(long long int **matriz, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}

// Soma os valores dos respectivos indices de duas matrizes e retorna seu ponteiro
long long int **somaMatriz(long long int **m1, long long int **m2, int tam)
{
    // Aloca a matriz auxiliar
    long long int **aux = alocaMatrizM(tam);

    for (int i = 0; i < tam; i++)
        for (int j = 0; j < tam; j++)
            aux[i][j] = m1[i][j] + m2[i][j];

    return aux;
}

// Subtrai os valores dos respectivos indices de duas matrizes e retorna seu ponteiro
long long int **subMatriz(long long int **m1, long long int **m2, int tam)
{
    // Aloca a matriz auxiliar
    long long int **aux = alocaMatrizM(tam);

    for (int i = 0; i < tam; i++)
        for (int j = 0; j < tam; j++)
            aux[i][j] = m1[i][j] - m2[i][j];

    return aux;
}

long long int **multMatriz(long long int **mA, long long int **mB, int tam)
{

    if (tam == 64)
    {
        long long int **resultante = alocaMatrizC(tam);

        for (int i = 0; i < tam; i++)
            for (int j = 0; j < tam; j++)
                for (int k = 0; k < tam; k++)
                    resultante[i][j] += mA[i][k] * mB[k][j];

        return resultante;
    }
    //Pegamos a metade do tamanho da matriz
    tam /= 2;

    // Alocamos os valores que receberao os valores particionados das matrizes mA e mB
    long long int **a11, **a12, **a21, **a22, **b11, **b12, **b21, **b22;

    //Erro verificado aqui na quebra de matrizes
    a11 = alocaMatrizM(tam);
    a12 = alocaMatrizM(tam);
    a21 = alocaMatrizM(tam);
    a22 = alocaMatrizM(tam);
    b11 = alocaMatrizM(tam);
    b12 = alocaMatrizM(tam);
    b21 = alocaMatrizM(tam);
    b22 = alocaMatrizM(tam);

    // Quebramos as matrizes mA e mB e distribuimos nas matrizes alocadas anteriormente

    // Primeiro Quadrante
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            a11[i][j] = mA[i][j];
            b11[i][j] = mB[i][j];
        }
    }

    // Segundo Quadrante
    for (int i = 0; i < tam; i++)
    {
        for (int j = tam; j < (2 * tam); j++)
        {
            a12[i][j - tam] = mA[i][j];
            b12[i][j - tam] = mB[i][j];
        }
    }

    // Terceiro Quadrante
    for (int i = tam; i < (2 * tam); i++)
    {
        for (int j = 0; j < tam; j++)
        {
            a21[i - tam][j] = mA[i][j];
            b21[i - tam][j] = mB[i][j];
        }
    }

    //Quarto Quadrante
    for (int i = tam; i < (2 * tam); i++)
    {
        for (int j = tam; j < (2 * tam); j++)
        {
            a22[i - tam][j - tam] = mA[i][j];
            b22[i - tam][j - tam] = mB[i][j];
        }
    }

    // Alocamos espaco para as matrizes m1...m7 e duas auxiliares
    long long int **m1, **m2, **m3, **m4, **m5, **m6, **m7, **aux, **aux1;

    // calculamos do m1...m7 como foi apresentado na definicao
    aux = somaMatriz(a11, a22, tam);
    aux1 = somaMatriz(b11, b22, tam);
    m1 = multMatriz(aux, aux1, tam);
    desalocaMatriz(aux, tam);
    desalocaMatriz(aux1, tam);

    aux = somaMatriz(a21, a22, tam);
    m2 = multMatriz(aux, b11, tam);
    desalocaMatriz(aux, tam);

    aux = subMatriz(b12, b22, tam);
    m3 = multMatriz(a11, aux, tam);
    desalocaMatriz(aux, tam);

    aux = subMatriz(b21, b11, tam);
    m4 = multMatriz(a22, aux, tam);
    desalocaMatriz(aux, tam);

    aux = somaMatriz(a11, a12, tam);
    m5 = multMatriz(aux, b22, tam);
    desalocaMatriz(aux, tam);

    aux = subMatriz(a21, a11, tam);
    aux1 = somaMatriz(b11, b12, tam);
    m6 = multMatriz(aux, aux1, tam);
    desalocaMatriz(aux, tam);
    desalocaMatriz(aux1, tam);

    aux = subMatriz(a12, a22, tam);
    aux1 = somaMatriz(b21, b22, tam);
    m7 = multMatriz(aux, aux1, tam);
    desalocaMatriz(aux, tam);
    desalocaMatriz(aux1, tam);

    //As matrizes que compoem os quadrantes de A e de B ja foram utilizadas, entao desalocamos
    desalocaMatriz(a11, tam);
    desalocaMatriz(a12, tam);
    desalocaMatriz(a21, tam);
    desalocaMatriz(a22, tam);
    desalocaMatriz(b11, tam);
    desalocaMatriz(b12, tam);
    desalocaMatriz(b21, tam);
    desalocaMatriz(b22, tam);

    // Alocamos aqui as matrizes que guardarao o resultado
    long long int **c11, **c12, **c21, **c22;

    aux = somaMatriz(m1, m4, tam);
    aux1 = subMatriz(aux, m5, tam);
    c11 = somaMatriz(aux1, m7, tam);
    desalocaMatriz(aux, tam);
    desalocaMatriz(aux1, tam);

    c12 = somaMatriz(m3, m5, tam);

    c21 = somaMatriz(m2, m4, tam);

    aux = subMatriz(m1, m2, tam);
    aux1 = somaMatriz(aux, m3, tam);
    c22 = somaMatriz(aux1, m6, tam);
    desalocaMatriz(aux, tam);
    desalocaMatriz(aux1, tam);

    //Desalocamos as matrizes m1...m7
    desalocaMatriz(m1, tam);
    desalocaMatriz(m2, tam);
    desalocaMatriz(m3, tam);
    desalocaMatriz(m4, tam);
    desalocaMatriz(m5, tam);
    desalocaMatriz(m6, tam);
    desalocaMatriz(m7, tam);

    // Criamos a matriz resultante que tem o dobro de tamanho da matriz que calculamos
    long long int **resultante = alocaMatrizM(2 * tam);

    //Monstamos a matriz dos resultados

    // Primeiro Quadrante
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            resultante[i][j] = c11[i][j];
        }
    }

    // Segundo Quadrante
    for (int i = 0; i < tam; i++)
    {
        for (int j = tam; j < (2 * tam); j++)
        {
            resultante[i][j] = c12[i][j - tam];
        }
    }

    // Terceiro Quadrante
    for (int i = tam; i < (2 * tam); i++)
    {
        for (int j = 0; j < tam; j++)
        {
            resultante[i][j] = c21[i - tam][j];
        }
    }

    // Quarto Quadrante
    for (int i = tam; i < (2 * tam); i++)
    {
        for (int j = tam; j < (2 * tam); j++)
        {
            resultante[i][j] = c22[i - tam][j - tam];
        }
    }
    // Desalocamos as matrizes que formavam os resultados dos quadrantes
    desalocaMatriz(c11, tam);
    desalocaMatriz(c12, tam);
    desalocaMatriz(c21, tam);
    desalocaMatriz(c22, tam);

    // Retorna a matriz apos o calculo
    return resultante;
}

// Metodo principal
int main()
{
    int tam, novoTam = 1;
    long long int **mA, **mB, **mC;
    
    scanf("%d", &tam);

    // Encontra uma potencia de dois mais proxima do valor digitado para ser ordem da matriz
    while (novoTam < tam) novoTam *= 2;

    // Como a matriz digitada pelo usuario pode ser <= a uma potencia de 2 vou precisar das outras posicoes alocadas vazias
    mA = alocaMatrizC(novoTam);
    mB = alocaMatrizC(novoTam);

    // Para a leitura voltamos a considerar a ordem da matriz informada pelo usuario

    // Le elementos da matriz A
    for (int i = 0; i < tam; i++)
        for (int j = 0; j < tam; j++)
            scanf("%lld", &mA[i][j]);

    // Le elementos da matriz B
    for (int i = 0; i < tam; i++)
        for (int j = 0; j < tam; j++)
            scanf("%lld", &mB[i][j]);

    // Concluida a leitura das matrizes

    /****************CALCULO DA MULTIPLICACAO*****************/
    mC = multMatriz(mA, mB, novoTam);

    // Exibicao da matriz C, calculada
    imprimeMatriz(mC, tam);

    // Desaloca memoria apos calculo e exibicao
    desalocaMatriz(mA, novoTam);
    desalocaMatriz(mB, novoTam);
    desalocaMatriz(mC, novoTam);

    return 0;
}
