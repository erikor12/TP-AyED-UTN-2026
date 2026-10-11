#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main() {
    char fecha[11];
    char nombreArchivo[40];
    printf ("Ingrese la fecha (dd-mm-aaaa): ");
    if (scanf ("%10s", fecha) != 1) {
        printf ("Error al leer la fecha.\n");
        return 1;
    }
    printf ("Ingrese el nombre del archivo: ");
    if (scanf ("%39s", nombreArchivo) != 1) {
        printf ("Error al leer el nombre del archivo.\n");
        return 1;
    }
    return 0;
}