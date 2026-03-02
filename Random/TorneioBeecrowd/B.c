#include <stdio.h>

int main() {
    double r;
    scanf("%lf", &r);
    double volume = 3.14159*r*r*r*(4.0/3.0);
    printf("VOLUME = %.3lf\n", volume);

    return 0;
}