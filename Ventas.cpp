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
//Ordena el archivo de ventas al terminar el dia
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
//funcion principal
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
   //Abrir el inventario.
   FILE* Inventario=fopen ("Inventario.dat", "rb+");
   if (Inventario==NULL){
    printf("No se pudo abrir inventario.dat\n");
    return 1;
   }
   //Abrir el archivo historico para agregar la venta.
   FILE *historico= fopen ("Historico.dat", "ab");
    if (historico==NULL) { 
    printf ("No se pudo abrir comandas_historicas.dat\n");
    fclose (Inventario);
    return 1;
   }
   // Registrar ventas.
    int continuar=1;
   while(continuar==1) {
    int codigoProducto;
    int cantidad;
    int encontrado=0;
    long posicion=0;

    Producto producto;

    printf ("\n===Nueva Venta====\n");
    printf ("Numero de Producto: ");
    if (scanf ("%d", &codigoProducto)!=1) {
    printf ("Entrada invalida para el codigo de producto.\n");
        break;
        
    }
    //Buscar el producto en el inventario.
    rewind (Inventario);
    while (true) {
        posicion=ftell (Inventario);
        if (fread (&producto, sizeof(Producto), 1, Inventario)!=1) {
            break;
        }
        if (producto.codigo==codigoProducto) {
            encontrado=1;
            break;
        }
    }
    
   }

   if (!encontrado) {
    printf("El producto no existe en el inventario.\n");
   } else {
    printf ("Producto:%s\n", producto.descripcion);
    printf ("Precio:%.2f\n", producto.precio);
    printf ("Stock disponible:%d\n", producto.stockActual);

    printf ("Cantidad:");
    if (scanf ("%d", &cantidad)!=1) {};
    printf ("Cantidad invalida.\n");
    break;
   }
    if (cantidad<=0) {
        printf ("La cantidad debe ser mayor a cero.\n");
    } else if (cantidad>producto.stockActual) { 
        printf ("No hay suficiente stock disponible.\n");

    } else { 
        //Preparar el registro historico.
        ComandaHistorica registro;
        strcpy (registro.fecha, fecha);
        registro.codigoPorducto=codigoProducto;
        registro.cantidad=cantidad;
        registro.comision=producto.precio*cantidad*0.10;

        //Guardar la venta en el historico.
        if (fwrite (&registro, sizeof(ComandaHistorica), 1, historico)!=1) {
            printf ("Error al guardar la venta en el historico.\n");
        break;
        }
        //verificar que los datos se escrbieron.

        if (fflush (historico)!=0){
            printf ("Error al guardar los datos\n");
            printf ("Verifique el archivo historico antes de continuar.\n");
            break;
        
        }
            //Descontar la cantidad vendida.
            producto.stockActual-=cantidad;

            //Volver a la posicion de producto.
            if (fseek(Inventario, posicion, SEEK_SET)!=0) {
                printf("Error al posicionar el inventario.\n");
                printf("La venta ya se guardo. Revise los archivos.\n");
                    break;
            }

    //Actualizar el inventario.
    if (fwrite(&producto, sizeof(Producto),1, Inventario)!=1) {
        printf ("La venta ya se guardo. Revise los archivos.\n");
        break;
    }

    if (fflush(Inventario)!=0) {
        printf ("Error al confirmar el inventario.\n");
        break;
    }
    printf("\nVenta registrada correctamente.\n");
    printf("Comision del mozo:%.2f\n", registro.comision);
   }
   
        long posicion=ftell (inventario) - sizeof(Producto);
        if (fwrite (&venta, sizeof(Venta), 1, archivoDia)!=1) {
            printf ("Error al guardar venta.\n");
        } else {

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