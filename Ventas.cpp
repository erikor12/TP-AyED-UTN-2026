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
   FILE *archivoDia=fopen (nombreArchivo, "ab");
   if (archivoDia==NULL) {
    printf ("No se pudo abrir la planilla del dia.\n");
    fclose (inventario);
    return 1;
   }
   int continuar=1;
   while(continuar==1) {
    int numeroMozo;
    int codigoProducto;
    int cantidad;
    printf ("\n===Nueva Venta====\n");
    printf ("Numero de Mozo: ");
    if (scanf ("%d", &numeroMozo)!=1) {
        printf ("Entrada invalida para el numero de mozo.\n");
        break;
        
    };
    printf ("Codigo de Producto: ");
    if (scanf ("%d", &codigoProducto)!=1) {
        printf ("Entrada invalida para el codigo de producto.\n");
        break;
    }
    
   }
   Producto producto;
   int encontrado=0;
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
    if (scanf ("%d",&cantidad)!=1) {};
    printf ("Cantidad invalida.\n");
    break;
   }
    if (cantidad<=0) {
        printf ("La cantidad debe ser mayor a cero.\n");
    } else if (cantidad>producto.stock) { 
        printf ("No hay suficiente stock disponible.\n");

    } else { 
        Venta venta;
        
        venta.numeroMozo=numeroMozo,
        venta.codProducto=codigoProducto;
        venta.cant=cantidad;
        venta.comision=
        producto.precio*cantidad*0.10;

        long posicion=ftell (inventario) - sizeof(Producto);
        if (fwrite (&venta, sizeof(Venta), 1, archivoDia)!=1) {
            printf ("Error al guardar venta.\n");
        } else {

        producto stock -= cantidad;
        if (fseek (inventario, posicion, SEEK_SET)!=0) 
        fwrite (&producto, sizeof(Producto), 1, inventario)!=1) {
            printf ("Error al actualizar el inventario.\n");
            printf ("La venta ya fue registrada.\n");
        } else { 
            fflush (inventario);
            printf ("\nVenta registrada correctamente.\n");
            printf ("Comision del mozo: %.2f\n", venta.comision);
        }
        }
    }
}
 
printf ("\nDesea registrar otra venta? (1=Si, 0=No): ");
if (scanf ("%d", &continuar)!=1) {
    continuar=0; 
}

fclose (archivoDia);
fclose (inventario);

FILE *archivoDia=fopen (nombreArchivo, "rb");
if (archivoLectura==NULL) {
  vector <venta> ventasVector;
  venta vtemp;
  while (fread (&vtemp, sizeof(venta),1, archivoLectura)==1) {
    ventasVector.push_back(vtemp);
  }
 
  fclose (archivoLectura);
  sort (ventasVector.begin(), ventasVector.end(), [](const venta &a, const venta &b) {
    return a.numeroMozo < b.numeroMozo;
  });

  FILE *archivoEscritura=fopen (nombreArchivo, "wb");
  if (archivoEscritura!=NULL) {
    for (const auto & venta; ventasVector) {
        fwrite (&venta, sizeof(venta), 1, archivoEscritura);
    }
    fclose (archivoEscritura);
  }
}

printf ("\nPlanilla del dia '%s' cerrada y ordenada correctamente.\n", nombreArchivo);
return 0;


    
   
   

