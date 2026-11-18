#include <stdio.h>

#define MAX 10
#define EPS 0.000001

int equal(double a, double b)
{
if (a - b < EPS && b - a < EPS)
return 1;
else
return 0;
}

int main()
{
double A[MAX][MAX];
double x;
int m, n;
int i, j;

printf("Enter number of rows (7-10): ");
scanf("%d", &m);
printf("Enter number of columns (7-10): ");
scanf("%d", &n);

if (m < 7 || m > 10 || n < 7 || n > 10)
{
    printf("Error: matrix size must be from 7 to 10.\n");
    return 1;
}

printf("Enter matrix elements (1st row and last column in non-decreasing order):\n");
for (i = 0; i < m; i++)
{
    for (j = 0; j < n; j++)
    {
        scanf("%lf", &A[i][j]);
    }
}


for (j = 1; j < n; j++)
{
    if (A[0][j] < A[0][j - 1] - EPS)
    {
        printf("Error: first row is not sorted.\n");
        return 1;
    }
}

for (i = 1; i < m; i++)
{
    if (A[i][n - 1] < A[i - 1][n - 1] - EPS)
    {
        printf("Error: last column is not sorted.\n");
        return 1;
    }
}

printf("Enter X: ");
scanf("%lf", &x);

printf("\nEntered matrix:\n");
for (i = 0; i < m; i++)
{
    for (j = 0; j < n; j++)
    {
        printf("%8.2lf", A[i][j]);
    }
    printf("\n");
}

printf("\nSearch results for X = %.2lf:\n", x);


int left = 0;
int right = n - 1;
int steps_row = 0;

while (left < right)
{
    int middle = (left + right) / 2;
    steps_row++;
    if (A[0][middle] < x - EPS)
    {
        left = middle + 1;
    }
    else
    {
        right = middle;
    }
}

if (equal(A[0][left], x))
{
    printf("First row: found at (1, %d); steps = %d\n", left + 1, steps_row);
}
else
{
    printf("First row: not found; steps = %d\n", steps_row);
}


left = 0;
right = m - 1;
int steps_col = 0;

while (left < right)
{
    int middle = (left + right) / 2;
    steps_col++;
    if (A[middle][n - 1] < x - EPS)
    {
        left = middle + 1;
    }
    else
    {
        right = middle;
    }
}

if (equal(A[left][n - 1], x))
{
    printf("Last column: found at (%d, %d); steps = %d\n", left + 1, n, steps_col);
}
else
{
    printf("Last column: not found; steps = %d\n", steps_col);
}

return 0;
}