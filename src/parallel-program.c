/**
 * @brief Number of Submatrices that Sum to K
 * @details Problem A, 23, Solução com Paralelismo.
 * @authors Eduardo Takashi Missaka (10417877), Tiago Silveira Lopes (10417600), Vitor Alves Pereira (10410862).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define MAX_M 1000
#define MAX_N 1000

int A[1000][1000];

typedef long long ll;

/**
 * @brief Realiza a contagem dos elementos dos subarrays que possuem soma equivalente a k
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
 * @brief Calcula o total de subarrays com soma equivalente a k
 * @details Complexidade de Tempo de O(n^3)
 * @param m dimensao m da matriz
 * @param n dimensao n da matriz
 * @param k valor k para comparacao
 * @return total de subarrays com soma equivalente a k
 */
ll solve(int m, int n, int k) {
    ll ans = 0;
    int temp[MAX_N];

    #pragma omp parallel for reduction(+:ans)
    for (int top = 0; top < m; top++) {
        memset(temp, 0, sizeof(temp)); // temp[0..n] = temp[0,0,0,...,0]

        for (int bottom = top; bottom < m; bottom++) {
            for (int j = 0; j < n; j++)
                temp[j] += A[bottom][j];

            ans += count_subarrays_with_sum_k(temp, n, k);
        }
    }

    return ans;
}

int main() {

    int k, m, n; // Valor de k e Dimensoes da Matriz
    ll solution;

    scanf("%d %d %d", &k, &m, &n);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    solution = solve(m, n, k);
    printf("%lld\n", solution);
    
    return 0;
}
