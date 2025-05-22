#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 1000
#define MAX_N 1000

int A[1000][1000];     
int ps[1010][1010];    

typedef long long ll;

ll count_subarrays_with_sum_k(int *nums, int size, int k) {
    ll count = 0;
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

ll solve(int m, int n, int k) {
    ll ans = 0;
    int temp[MAX_N];

    for (int top = 0; top < m; top++) {
        memset(temp, 0, sizeof(temp)); 

        for (int bottom = top; bottom < m; bottom++) {
            for (int j = 0; j < n; j++)
                temp[j] += A[bottom][j];

            ans += count_subarrays_with_sum_k(temp, n, k);
        }
    }

    return ans;
}

int main() {
    int k, m, n;
    scanf("%d %d %d", &k, &m, &n);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("%lld\n", solve(m, n, k));
    return 0;
}
