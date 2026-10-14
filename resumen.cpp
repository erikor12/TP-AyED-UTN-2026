/*Arma el resumen del cierre: por cada mozo, cuántos productos
vendió y cuánta comisión le corresponde; y el total del buffet.
en donde lo datos entren por el archivo de datos de comandas_semana_sX-mm.dat
y que muestre todo en pantalla*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct Comanda
{
    int idMozo;
    int codigoProducto;
    int cantidad;
    float comision;
};

struct Producto
{
    int codigo;
    char descripcion[50];
    float precio;
    int stockActual;
};

int main(int argc, char const *argv[])
{


    return 0;
}

void mostrar(const char *nombre)
{
    FILE *f = fopen(nombre, "rb");
    if (f == NULL) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }
    Comanda r;
    Producto p;
    int leido = fread(&r, sizeof(Comanda), 1, f); // lectura anticipada
    while (leido == 1)
    {
        // Procesar el grupo
        int claveGrupo = r.idMozo; // clave de control
        int cantidad = 0;          // contador del grupo
        float comision = 0;          // acumulador del grupo
        float total = 0;          // acumulador del grupo
        while (leido == 1 && r.idMozo == claveGrupo)
        {
            cantidad += r.cantidad;
            fread(&p, sizeof(Producto), 1, f);
            total += p.precio * r.cantidad;
            comision += r.comision;
            leido = fread(&r, sizeof(Comanda), 1, f);
        }
        cout << "ID del mozo: " << claveGrupo << endl;
        cout << "Cantidad Vendida: " << cantidad << endl;
        cout << "Comision a pagar: " << comision << endl;
        cout << "Total vendido: " << total << endl;
    }
    fclose(f);
}
