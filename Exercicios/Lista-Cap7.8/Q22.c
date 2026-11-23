#include <stdio.h>

typedef struct { float x, y; } Ponto;
typedef struct { Ponto inf_esq; Ponto sup_dir; } Retangulo;

float area(Retangulo r);
float perimetro(Retangulo r);
int contemPonto(Retangulo r, Ponto p);

float area(Retangulo r) { return (r.sup_dir.x - r.inf_esq.x) * (r.sup_dir.y - r.inf_esq.y); }
float perimetro(Retangulo r) { return 2 * ((r.sup_dir.x - r.inf_esq.x) + (r.sup_dir.y - r.inf_esq.y)); }
int contemPonto(Retangulo r, Ponto p) {
    return p.x >= r.inf_esq.x && p.x <= r.sup_dir.x &&
           p.y >= r.inf_esq.y && p.y <= r.sup_dir.y;
}

int main(void) {
    Retangulo r1, r2; Ponto p;
    scanf("%f%f%f%f%f%f", &r1.inf_esq.x, &r1.inf_esq.y,
          &r1.sup_dir.x, &r1.sup_dir.y, &p.x, &p.y);
    r2 = r1;
    printf("Area: %.2f\nPerimetro: %.2f\n%s\n",
           area(r1), perimetro(r1), contemPonto(r2, p) ? "Ponto dentro" : "Ponto fora");
    return 0;
}

