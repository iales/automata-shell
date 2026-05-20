#include <stdio.h>

int main() {
    int c;
    goto N;

N:
    c = getchar();
    if (c == EOF) return 0;
    if (c == '/') goto SE;
    if (c == '"') { putchar(c); goto STR; }
    if (c == '\'') { putchar(c); goto CHR; }
    putchar(c);
    goto N;

SE:
    c = getchar();
    if (c == EOF) return 0;
    if (c == '/') goto LC;
    if (c == '*') goto BC;
    if (c == '"') { putchar('/'); putchar(c); goto STR; }
    if (c == '\'') { putchar('/'); putchar(c); goto CHR; }
    putchar('/'); putchar(c);
    goto N;

LC:
    c = getchar();
    if (c == EOF) return 0;
    if (c == '\n') { putchar(' '); putchar(c); goto N; }
    goto LC;

BC:
    c = getchar();
    if (c == EOF) return 0;
    if (c == '*') goto BCS;
    goto BC;

BCS:
    c = getchar();
    if (c == EOF) return 0;
    if (c == '/') { putchar(' '); goto N; }
    if (c == '*') goto BCS;
    goto BC;

STR:
    c = getchar();
    if (c == EOF) return 0;
    if (c == '\\') { putchar(c); goto ESC_STR; }
    if (c == '"') { putchar(c); goto N; }
    putchar(c);
    goto STR;

ESC_STR:
    c = getchar();
    if (c == EOF) return 0;
    putchar(c);
    goto STR;

CHR:
    c = getchar();
    if (c == EOF) return 0;
    if (c == '\\') { putchar(c); goto ESC_CHR; }
    if (c == '\'') { putchar(c); goto N; }
    putchar(c);
    goto CHR;

ESC_CHR:
    c = getchar();
    if (c == EOF) return 0;
    putchar(c);
    goto CHR;
}
