/**
 * @brief Number of Submatrices that Sum to K
 * @details Problem A, 23, Solução com Paralelismo.
 * @authors Eduardo Takashi Missaka (10417877), Tiago Silveira Lopes (10417600), Vitor Alves Pereira (10410862).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>

typedef long long ll;

int **A;

/**
 * @brief Conta subarrays com soma igual a k
 * @details Complexidade de Tempo de O(n^2)
 * @param nums subarray
 * @param size tamanho do subarray
 * @param k valor k para comparacao
 * @return total de 1 subarray com soma equivalente a k
 */
ll count_subarrays_with_sum_k(int *nums, int size, int k) {
    ll count = 0;

    #pragma omp parallel for reduction(+:count)
    for (int start = 0; start < size; start++) {
        int sum = 0;
        for (int end = start; end < size; end++) {
            sum += nums[end];
            if (sum == k)
                count++;
        }
    }
    return count;
}

/**
 * @brief Calcula submatrizes com soma igual a k
 * @details Complexidade de Tempo de O(n^3)
 * @param m dimensao m da matriz
 * @param n dimensao n da matriz
 * @param k valor k para comparacao
 * @return total de subarrays com soma equivalente a k
 */
ll solve(int m, int n, int k) {
    ll ans = 0;
    int *temp = (int *)malloc(n * sizeof(int));

    #pragma omp parallel for reduction(+:ans) private(temp)
    for (int top = 0; top < m; top++) {
        int *temp = (int *)calloc(n, sizeof(int));

        for (int bottom = top; bottom < m; bottom++) {
            for (int j = 0; j < n; j++)
                temp[j] += A[bottom][j];

            ans += count_subarrays_with_sum_k(temp, n, k);
        }

        free(temp);
    }

    return ans;
}

int main() {
    FILE *pont_arq;
    int i, j;
    int k, m, n;
    ll solution;

    /*
    printf("Digite K, M e N (ex: 5 1000 1000): ");
    scanf("%d %d %d", &k, &m, &n);

    A = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        A[i] = (int *)malloc(n * sizeof(int));
    }

    srand(time(NULL));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = rand() % 10; 

    double tempo_init = omp_get_wtime();

    solution = solve(m, n, k);
    printf("Total de submatrizes com soma = k: %lld\n", solution);

    double tempo_fim = omp_get_wtime();
    printf("Tempo total de execução = %f segundos.\n", tempo_fim - tempo_init);
    */

    pont_arq = fopen("./test/matrix5.in", "r");
    if (pont_arq == NULL) {
        printf("Arquivo nao foi carregado...\n");
        return 1;
    }

    if (fscanf(pont_arq, "%d %d %d", &k, &m, &n) != 3) {
        printf("Erro ao ler k, m e n do arquivo.\n");
        fclose(pont_arq);
        return 1;
    }

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (fscanf(pont_arq, "%d", &A[i][j]) != 1) {
                printf("Erro ao ler elemento A[%d][%d].\n", i, j);
                fclose(pont_arq);
                return 1;
            }
        }
    }

    fclose(pont_arq);

    solution = solve(m, n, k);
    printf("Total de submatrizes com soma %d: %lld\n", k, solution);


    for (int i = 0; i < m; i++)
        free(A[i]);
    free(A);

    return 0;
}

