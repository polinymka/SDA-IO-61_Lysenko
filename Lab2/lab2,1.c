#include <stdio.h>

int main(void)
{
const double PI = 3.14159265358979323846;
long long n, i, j;
unsigned long long ops = 0;
double x, x2, pi2, s, P;

printf("Enter n (natural number): ");
if (scanf("%lld", &n) != 1 || n < 1) {
    printf("Error: n must be a natural number\n");
    return 1;
}

x   = 1.0 / 3.0;    ops += 2;
x2  = x * x;        ops += 2;
pi2 = PI * PI;      ops += 2;
P   = 1.0;          ops += 1;

for (i = 1, ops++; ops++, i <= n; i++, ops++) {
    s = 0.0;        ops += 1;
    for (j = 1, ops++; ops++, j <= i; j++, ops++) {
        s = s + (2 * j - 1);  ops += 4;
    }
    P = P * (1.0 - x2 / (pi2 * s));  ops += 5;
}

printf("P = %.7f\n", P);
printf("Operations: %llu\n", ops);
printf("Standard function calls: 0\n");
return 0;
}