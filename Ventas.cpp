#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

struct Producto {
    int codigo;
    char descripcion[50];
    float precio;
    int stockActual;
};

struct Comanda {
    int idMozo;
    int codigoProducto;
    int cantidad;
    float comision;
};

struct Mozo {
    int idMozo;
    char nombre[50];
    char password[20];
    float totalComision;
};

const int clave_k = 5;              // desplazamiento de la "encriptacion"
const int MAX_VENTAS = 1000;        // tamaño fisico del array
const float PORCENTAJE = 0.10f;     // comision del 10%

// Busco al mozo en mozos.dat y verifica su clave.

bool validarMozo(int idMozo) {
    FILE *archivoMozos = fopen("mozos.dat", "rb");
    if (archivoMozos == NULL) {
        cout << "No se pudo abrir mozos.dat" << endl;
        return false;
    }

    Mozo mozo;
    bool valido = false;

    while (fread(&mozo, sizeof(Mozo), 1, archivoMozos) == 1) {
        if (mozo.idMozo == idMozo) {
            char clave[20];
            cout << "Mozo: " << mozo.nombre << endl;
            cout << "Ingrese la clave: ";
            cin >> clave;

            // Encripto la clave ingresada sumando clave_k a cada letra
            int i = 0;
            while (clave[i] != '\0') {
                clave[i] = clave[i] + clave_k;
                i++;
            }

            // Comparo contra la clave guardada (que ya esta encriptada)
            if (strcmp(clave, mozo.password) == 0) {
                valido = true;
            } else {
                cout << "Clave incorrecta." << endl;
            }
            break;  // ya encontre al mozo, no sigo leyendo
        }
    }

    fclose(archivoMozos);

    if (!valido) {
        cout << "No se pudo validar al mozo." << endl;
    }
    return valido;
}

// Busqueda binaria en inventario.dat (ordenado por codigo).
// Si lo encuentro, dejo el producto en "producto" y su posicion en "posicion".
bool buscarProducto(FILE *inventario, int codigo, Producto &producto, long &posicion) {
    fseek(inventario, 0, SEEK_END);
    long cantidad = ftell(inventario) / sizeof(Producto);

    long primero = 0;
    long ultimo = cantidad - 1;

    while (primero <= ultimo) {
        long medio = (primero + ultimo) / 2;

        fseek(inventario, medio * sizeof(Producto), SEEK_SET);
        fread(&producto, sizeof(Producto), 1, inventario);

        if (producto.codigo == codigo) {
            posicion = medio;
            return true;
        }
        if (codigo > producto.codigo) {
            primero = medio + 1;
        } else {
            ultimo = medio - 1;
        }
    }
    return false;
}

// Leo la planilla del dia, y lo ordeno por mozo y lo reescribe.
void ordenarPlanilla(const char *nombreArchivo) {
    Comanda ventas[MAX_VENTAS];
    int cantidad = 0;               

    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        cout << "No se pudo abrir la planilla para ordenar." << endl;
        return;
    }

    // Paso todo el archivo al array
    while (cantidad < MAX_VENTAS &&
           fread(&ventas[cantidad], sizeof(Comanda), 1, archivo) == 1) {
        cantidad++;
    }
    fclose(archivo);

    // Ordenamiento por seleccion
    for (int i = 0; i < cantidad - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < cantidad; j++) {
            if (ventas[j].idMozo < ventas[menor].idMozo) {
                menor = j;
            }
        }
        Comanda aux = ventas[i];
        ventas[i] = ventas[menor];
        ventas[menor] = aux;
    }

    // Reescribo el archivo ya ordenado
    archivo = fopen(nombreArchivo, "wb");
    fwrite(ventas, sizeof(Comanda), cantidad, archivo);
    fclose(archivo);

    cout << "Planilla ordenada por mozo." << endl;
}

int main() {
    char fecha[11];
    char nombreArchivo[40];

    // La fecha se pide una sola vez
    cout << "Ingrese la fecha (dd-mm-aaaa): ";
    cin >> fecha;

    // Armo el nombre: comandas_dd-mm-aaaa.dat
    strcpy(nombreArchivo, "comandas_");
    strcat(nombreArchivo, fecha);
    strcat(nombreArchivo, ".dat");

    FILE *inventario = fopen("inventario.dat", "rb+");
    if (inventario == NULL) {
        cout << "No se pudo abrir inventario.dat" << endl;
        return 1;
    }

    // "ab": si no existe la crea, si existe agrega al final
    FILE *archivoDia = fopen(nombreArchivo, "ab");
    if (archivoDia == NULL) {
        cout << "No se pudo abrir la planilla del dia." << endl;
        fclose(inventario);
        return 1;
    }

    int continuar = 1;

    while (continuar == 1) {
        int idMozo, codigo, cantidad;

        cout << "\n--- NUEVA VENTA ---" << endl;
        cout << "Numero de mozo: ";
        cin >> idMozo;

        if (validarMozo(idMozo)) {
            cout << "Codigo de producto: ";
            cin >> codigo;

            Producto producto;
            long posicion;

            if (buscarProducto(inventario, codigo, producto, posicion)) {
                cout << "Producto: " << producto.descripcion << endl;
                cout << "Precio: " << producto.precio << endl;
                cout << "Stock: " << producto.stockActual << endl;
                cout << "Cantidad: ";
                cin >> cantidad;

                if (cantidad <= 0) {
                    cout << "La cantidad debe ser mayor a cero." << endl;
                } else if (cantidad > producto.stockActual) {
                    cout << "No hay stock suficiente." << endl;
                } else {
                    // Armo la venta y calculo la comision
                    Comanda venta;
                    venta.idMozo = idMozo;
                    venta.codigoProducto = producto.codigo;
                    venta.cantidad = cantidad;
                    venta.comision = producto.precio * cantidad * PORCENTAJE;

                    // Descuento stock y lo guardo en su lugar
                    producto.stockActual = producto.stockActual - cantidad;
                    fseek(inventario, posicion * sizeof(Producto), SEEK_SET);
                    fwrite(&producto, sizeof(Producto), 1, inventario);

                    // Agrego la venta a la planilla del dia
                    fwrite(&venta, sizeof(Comanda), 1, archivoDia);

                    cout << "Venta cargada. Comision: " << venta.comision << endl;
                }
            } else {
                cout << "Producto no encontrado." << endl;
            }
        }

        cout << "\nDesea cargar otra venta? (1=Si / 0=No): ";
        cin >> continuar;
    }

    fclose(archivoDia);
    fclose(inventario);

    ordenarPlanilla(nombreArchivo);

    return 0;
}