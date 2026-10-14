#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct comandahistorica {
    char fecha[11];
    char nombreMozo[50];
    int codigoProducto;
    int cantidad;
    float comision;
};

struct Producto {
    int codigo;
    char descripcion[50];
    float precio;
    int stockActual;     
};
int main() {
    char fecha[11];
    char nombreArchivo[50];
    //Ingresar fecha y nombre del mozo
    printf("Ingrese la fecha (dd-mm-aaaa): ");
    if (scanf ("%10s", fecha) != 1) {
        printf ("Error al leer la fecha.\n");
        return 1;
    }
    printf ("Ingrese el nombre del mozo: ");
    if (scanf ("%49s", nombreMozo) != 1) {
        printf ("Error al leer el nombre del mozo.\n");
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
        

        long posicion=ftell (inventario) - sizeof(Producto);
        if (fwrite (&venta, sizeof(Venta), 1, archivoDia)!=1) {
            printf ("Error al guardar venta.\n");
        } else {

        producto.stockActual -= cantidad;
        if (fseek (inventario, posicion, SEEK_SET)!=0) 
        fwrite (&producto, sizeof(Producto), 1, inventario)!=1) {
            printf ("Error al actualizar el inventario.\n");
            printf ("La venta ya fue registrada.\n");
        } else { 
            fflush (inventario);
            std::printf ("\nVenta registrada correctamente.\n");
            std::printf ("Comision del mozo: %.2f\n", venta.comision);
        }
        }
    }
}
 
    std::printf ("\nDesea registrar otra venta? (1=Si, 0=No): ");
if (scanf ("%d", &continuar)!=1) {
    continuar=0; 
}

std::fclose (archivoDia);
fclose (inventario);

FILE *archivoDia=fopen (nombreArchivo, "rb");
    if (archivoLectura==NULL) {
  vector <venta> ventasVector;
  venta vtemp;
  while (fread (&vtemp, sizeof(venta),1, archivoLectura)==1) {
    ventasVector.push_back(vtemp);
  }
 
  std::fclose (archivoLectura);
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


    
   
   

