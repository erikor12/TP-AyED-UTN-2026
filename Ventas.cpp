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
   Producto producto;
   rewind (Inventario);
   int encontrado=0;
   while (fread (&producto,sizeof(Producto),1,inventario)==1) {
    if (producto.codigo==codigoProducto) {
        encontrado=1
        break;
    }
   }
   if (!encontrado) {
    printf("El producto no existe en el inventario.\n");
   } else {
    printf ("Producto:%s\n", producto.descripcion);
    printf ("Precio:%.2f\n",producto.precio);
    printf ("Stock disponible:%d\n", producto.stock);

    printf ("Cantidad:");
    scanf ("%d",&cantidad);
    if (cantidad<=0) { 
        printf ("La cantidad debe ser mayor a cero.\n");
    } else if (cantidad>producto.stock) {
        printf ("No hay stock suficiente.\n");
    
    } else { 
        Venta venta;
        
        venta.numeroMozo=numeroMozo,
        venta.codProducto=codigoProducto;
        venta.cant=cantidad;
        venta.comision=
        producto.precio*cantidad*0.10;

        producto stock -= cantidad;
        fseek (inventario, -sizeof(Producto), seek_cur);
        fwrite (&producto, sizeof(Producto), 1, inventario);

        FILE*archivoDia= fopen (nombreArchivo, "ab");
        if (archivoDia==NULL) { 
            printf ("No se pudo abrir la planilla del dia.");
            
        }
    }
   
   
}
