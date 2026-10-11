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
   sprintf(nombreArchivo,"comandas_%s.dat", fecha);
   File *Inventario=fopen ("Inventario.dat", "rb+");
   if (Inventario==NULL){
    printf("No se pudo abrir inventario.dat\n");
    return 1;
   }
   int continuar=1;
   while(continuar==1) {
    int numeroMozo;
    int codigoProducto;
    int cantidad;
    printf ("\n===Nueva Venta====\n");
    printf ("Numero de Mozo: ");
    scanf ("%d", &numeroMozo);
    printf ("Codigo de Producto: ");
    scanf ("%d", &codigoProducto);
    printf ("Cantidad: ");  
    
   }
}
