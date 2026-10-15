#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

struct Producto{
    int codigo;
    char descripcion [50];
    float precio;
    int stock;
};

struct Venta{
    int numeroMozo;
    int codProd;
    int cant;
    float comision;
};

struct Mozo{
    int idMozo;
    char nombre[50];
    char password[20];
    float totalcomision;
};

const int clave_k = 5;

//Validar si existe el mozo y si su clave es correcta
bool validarMozo(int numeroMozo) {
    FILE *archivoMozos = fopen("mozos.dat", "rb");
    if (archivoMozos == NULL) {
        printf("No se pudo abrir mozos.dat.\n");
        return false;
    }

    Mozo mozoLeido;
    bool mozoEncontrado = false;
    bool claveCorrecta = false;
    char claveIngresada[20];

    while (fread(&mozoLeido, sizeof(Mozo), 1, archivoMozos) == 1) {
        if (mozoLeido.idMozo == numeroMozo) {
            mozoEncontrado = true;
            printf("Mozo encontrado: %s\n", mozoLeido.nombre);
            printf("Ingrese la clave: ");
            if (scanf("%19s", claveIngresada) != 1) {
                fclose(archivoMozos);
                return false;
            }

            // Encriptar clave ingresada
            char claveEncriptada[20];
            int i = 0;
            while (claveIngresada[i] != '\0') {
                claveEncriptada[i] = claveIngresada[i] + clave_k;
                i++;
            }
            claveEncriptada[i] = '\0';

            if (strcmp(claveEncriptada, mozoLeido.password) == 0) {
                claveCorrecta = true;
            }
            break;
        }
    }
    fclose(archivoMozos);

    if (!mozoEncontrado) {
        printf("Error: El numero de mozo no existe.\n");
        return false;
    }
    if (!claveCorrecta) {
        printf("Error: Clave incorrecta. Acceso denegado.\n");
        return false;
    }

    return true;
}
