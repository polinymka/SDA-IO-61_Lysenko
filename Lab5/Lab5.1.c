#include <stdio.h>
#include <stdlib.h>
#define N 8
int cmp, swp;
void shaker_sort(int a[N][N])
{
    int left = 0, right = N - 1, last, i, t;
    cmp = 0;
    swp = 0;
    while (left < right) {
        last = left;
        for (i = left; i < right; i++) {
            cmp++;
            if (a[i][i] < a[i + 1][i + 1]) {
                t = a[i][i];
                a[i][i] = a[i + 1][i + 1];
                a[i + 1][i + 1] = t;
                swp++;
                last = i;
            }
        }
        right = last;
        last = right;
        for (i = right; i > left; i = i - 1) {
            cmp++;
            if (a[i - 1][i - 1] < a[i][i]) {
                t = a[i - 1][i - 1];
                a[i - 1][i - 1] = a[i][i];
                a[i][i] = t;
                swp++;
                last = i;
            }
        }
        left = last;
    }
}
void print_matrix(int a[N][N])
{
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++)
            printf("%5d", a[i][j]);
        printf("\n");
    }
    printf("Main diagonal: ");
    for (i = 0; i < N; i++)
        printf("%d ", a[i][i]);
    printf("\n");
}
int main(void)
{
    int a[N][N], i, j, k;
    srand(14);
    for (k = 1; k <= 3; k++) {
        printf("\n==== Case %d ====\n", k);
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                a[i][j] = rand() % 90 + 10;
        if (k == 1)
            for (i = 0; i < N; i++)
                a[i][i] = 100 - 5 * i;
        if (k == 3)
            for (i = 0; i < N; i++)
                a[i][i] = 10 + 5 * i;
        printf("Initial matrix:\n");
        print_matrix(a);
        shaker_sort(a);
        printf("Matrix after sorting:\n");
        print_matrix(a);
        printf("Comparisons: %d, swaps: %d\n", cmp, swp);
    }
    return 0;
}