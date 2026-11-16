#include <stdio.h>
int main(void)
{
    double x;
    double y;

    printf("Введіть x: ");
    scanf("%lf", &x);

    if (x > -15) {
        if (x <= 3) {
            y = 4 * x * x + 2;
            printf("y = %.4f\n", y);
        } else {
            if (x > 20) {
                y = 3 * x * x * x / 4 - 5;
                printf("y = %.4f\n", y);
            } else {
                printf("Функція не визначена\n");
            }
        }
    } else {
        if (x <= -30) {
            y = 3 * x * x * x / 4 - 5;
            printf("y = %.4f\n", y);
        } else {
            printf("Функція не визначена\n");
        }
    }

    return 0;
}