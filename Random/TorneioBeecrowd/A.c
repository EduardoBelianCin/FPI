#include <stdio.h>

int main() {
    double d;
    scanf("%lf", &d);
    double area = 3.14159*d*d;
    printf("A=%.4lf\n", area);

    return 0;
}