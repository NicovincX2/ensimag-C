#include <stdint.h>
#include <stdbool.h>

#include "prime.h"

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