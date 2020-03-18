#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "utils.h"

char *strdup (const char *str) {
    size_t len = strlen(str) + 1;
    void *new = malloc(len);
    if (new == NULL)
        return NULL;
    return (char *)memcpy(new, str, len);
}

/*
    renvoi si x est premier
*/
static bool is_prime(const uintmax_t nombre) {
    if (nombre <= 3) {
        return nombre >= 2;
    }
    if ((nombre % 2) == 0) {
        return false;
    }
    uintmax_t q = nombre;
    for (uintmax_t i = 3; i * i <= q; i += 2) {
        if ((nombre % i) == 0) {
            return false;
        }
        q = nombre / i;
    }
    return true;
}

/*
    renvoi le prochain non premier après nombre
*/
uintmax_t next_prime(uintmax_t nombre) {
    while (is_prime(nombre) != 1) {
        nombre++;
    }
    return nombre;
}
