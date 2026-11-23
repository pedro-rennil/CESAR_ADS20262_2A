#include <stdio.h>

#define PI 3.14159f

float area(float r);

float area(float r) {
    return 4.0f * PI * r * r;
}

int main(void) {
    float raio;
    scanf("%f", &raio);
    printf("Area = %.2f\n", area(raio));
    return 0;
}
