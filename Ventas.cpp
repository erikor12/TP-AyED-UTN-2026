#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct Producto {
    int codigo;
    char descripcion[50];
    float precio;
    int stock;
};

struct Venta {
    int numeroMozo;
    int codProd;
    int cant;
    float comision;
};

struct Mozo {
    int idMozo;
    char nombre[50];
    char password[20];
    float totalComision;
};

const int CLAVE_K = 5;

// --- FUNCIONES AUXILIARES (Fuera del main para mantener el orden) ---

// Valida si el mozo existe y su clave es correcta
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
                claveEncriptada[i] = claveIngresada[i] + CLAVE_K;
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

// Ordena el archivo de ventas al finalizar la jornada
void ordenarPlanillaDiaria(const char* nombreArchivo) {
    FILE *archivoLectura = fopen(nombreArchivo, "rb");
    if (archivoLectura == NULL) return;

    std::vector<Venta> ventasVector;
    Venta vTemp;
    
    while (fread(&vTemp, sizeof(Venta), 1, archivoLectura) == 1) {
        ventasVector.push_back(vTemp);
    }
    fclose(archivoLectura);

    // Ordenar por número de mozo
    std::sort(ventasVector.begin(), ventasVector.end(), [](const Venta& a, const Venta& b) {
        return a.numeroMozo < b.numeroMozo;
    });

    FILE *archivoEscritura = fopen(nombreArchivo, "wb");
    if (archivoEscritura != NULL) {
        for (const auto& venta : ventasVector) {
            fwrite(&venta, sizeof(Venta), 1, archivoEscritura);
        }
        fclose(archivoEscritura);
    }
}

// --- FUNCIÓN PRINCIPAL (Ahora mucho más limpia y fácil de leer) ---
int main() {
    char fecha[11];
    char nombreArchivo[40];

    printf("Ingrese la fecha (dd-mm-aaaa): ");
    if (scanf("%10s", fecha) != 1) {
        printf("Error al leer la fecha.\n");
        return 1;
    }

    sprintf(nombreArchivo, "comandas_%s.dat", fecha);

    FILE *inventario = fopen("inventario.dat", "rb+");
    if (inventario == NULL) {
        printf("No se pudo abrir inventario.dat\n");
        return 1;
    }

    FILE *archivoDia = fopen(nombreArchivo, "ab");
    if (archivoDia == NULL) {
        printf("No se pudo abrir la planilla del dia.\n");
        fclose(inventario);
        return 1;
    }

    int continuar = 1;

    while (continuar == 1) {
        int numeroMozo;
        printf("\n===== NUEVA VENTA =====\n");
        printf("Numero de mozo: ");
        if (scanf("%d", &numeroMozo) != 1) {
            printf("Entrada invalida.\n");
            break;
        }

        // Llamamos a la función modularizada del mozo
        if (!validarMozo(numeroMozo)) {
            printf("¿Desea intentar otro mozo? (1=Si / 0=No): ");
            scanf("%d", &continuar);
            continue;
        }

        int codigoProducto;
        printf("Codigo de producto: ");
        if (scanf("%d", &codigoProducto) != 1) {
            printf("Entrada invalida.\n");
            break;
        }

        Producto producto;
        int encontrado = 0;
        rewind(inventario);

        while (fread(&producto, sizeof(Producto), 1, inventario) == 1) {
            if (producto.codigo == codigoProducto) {
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("El producto no existe.\n");
        } else {
            printf("Producto: %s\n", producto.descripcion);
            printf("Precio: %.2f\n", producto.precio);
            printf("Stock disponible: %d\n", producto.stock);

            int cantidad;
            printf("Cantidad: ");
            if (scanf("%d", &cantidad) != 1) {
                printf("Cantidad invalida.\n");
                break;
            }

            if (cantidad <= 0) {
                printf("La cantidad debe ser mayor a cero.\n");
            } else if (cantidad > producto.stock) {
                printf("No hay stock suficiente.\n");
            } else {
                Venta venta;
                venta.numeroMozo = numeroMozo;
                venta.codProd = producto.codigo;
                venta.cant = cantidad;
                venta.comision = producto.precio * cantidad * 0.10;

                long posicion = ftell(inventario) - sizeof(Producto);

                if (fwrite(&venta, sizeof(Venta), 1, archivoDia) != 1) {
                    printf("Error al guardar la venta.\n");
                } else {
                    producto.stock -= cantidad;

                    if (fseek(inventario, posicion, SEEK_SET) != 0 ||
                        fwrite(&producto, sizeof(Producto), 1, inventario) != 1) {
                        printf("Error al actualizar el inventario.\n");
                    } else {
                        fflush(inventario);
                        printf("\nVenta cargada correctamente.\n");
                        printf("Comision: %.2f\n", venta.comision);
                    }
                }
            }
        }

        printf("\n¿Desea cargar otra venta? (1=Si / 0=No): ");
        if (scanf("%d", &continuar) != 1) {
            continuar = 0;
        }
    }

    fclose(archivoDia);
    fclose(inventario);

    // Llamamos a la función modularizada para ordenar
    ordenarPlanillaDiaria(nombreArchivo);

    printf("\nPlanilla del dia '%s' cerrada y ordenada correctamente.\n", nombreArchivo);

    return 0;
}