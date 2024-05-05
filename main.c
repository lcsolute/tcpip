#include <stdio.h>
#include <stddef.h>

struct Example {
    char c;
    int i;
    double d;
};

int main() {
    printf("Size of struct Example: %zu\n", sizeof(struct Example));
    printf("Offset of c: %zu\n", offsetof(struct Example, c));
    printf("Offset of i: %zu\n", offsetof(struct Example, i));
    printf("Offset of d: %zu\n", offsetof(struct Example, d));
    return 0;
}
