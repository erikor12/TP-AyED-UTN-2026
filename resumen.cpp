/*Arma el resumen del cierre: por cada mozo, cuántos productos
vendió y cuánta comisión le corresponde; y el total del buffet.
en donde lo datos entren por el archivo de datos de comandas_semana_sX-mm.dat
y que muestre todo en pantalla*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct Semana
{
    // clave del mozo
    // clave del producto
    // cantidad vendida
    // precio unitario
    // comisión del mozo
};

int main(int argc, char const *argv[])
{
    FILE *f = fopen("alumnos.dat", "rb");
    if (f == NULL)
    {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }
    fclose(f);
    return 0;
}

void corteControl(const char *nombre)
{
    FILE *f = fopen(nombre, "rb");
    if (f == NULL) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }
    Semana r;
    int leido = fread(&r, sizeof(Semana), 1, f); // lectura anticipada
    while (leido == 1)
    {
        // Procesar el grupo
        int claveGrupo = r.clave; // clave de control
        int cantidad = 0;          // contador del grupo
        float comision = 0;          // acumulador del grupo
        float total = 0;          // acumulador del grupo
        while (leido == 1 && r.clave == claveGrupo)
        {
            cantidad += r.cantidadprod;
            total += r.precio * r.cantidadprod;
            comision += r.comision;
            leido = fread(&r, sizeof(Semana), 1, f);
        }
        cout << "ID del mozo: " << claveGrupo << endl;
        cout << "Cantidad Vendida: " << cantidad << endl;
        cout << "Comision a pagar: " << comision << endl;
        cout << "Total vendido: " << total << endl;
    }
    fclose(f);
}
