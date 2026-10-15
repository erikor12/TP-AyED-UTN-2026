/*Arma el resumen del cierre: por cada mozo, cuántos productos
vendió y cuánta comisión le corresponde; y el total del buffet.
en donde lo datos entren por el archivo de datos de comandas_semana_sX-mm.dat
y que muestre todo en pantalla*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

struct Comanda
{
    int idMozo;
    int codigoProducto;
    int cantidad;
    float comision;
};

struct Mozo
{
    int idMozo;
    char nombre[50];
    char password[20];
    float totalComision = 0;
};
struct Producto
{
    int codigo;
    char descripcion[50];
    float precio;
    int stockActual;
};

// bool porque si lo encuentra, pasa el struct por ref.
bool buscarMozo(int idMozo, Mozo &mozo) 
{
    FILE *mozos = fopen("mozos.dat", "rb");
    if (mozos == NULL)
        return false;

    bool encontrado = false;
    while (fread(&mozo, sizeof(Mozo), 1, mozos) == 1)
    {
        if (mozo.idMozo == idMozo)
        {
            encontrado = true;
            break;
        }
    }
    fclose(mozos);
    return encontrado;
}

// bool porque si lo encuentra, pasa el struct por ref.
bool buscarProducto(int codigo, Producto &producto)
{
    FILE *inventario = fopen("inventario.dat", "rb");
    if (inventario == NULL)
    {
        cout << "No se pudo abrir el archivo." << endl;
        return false;
    }
    fseek(inventario, 0, SEEK_END);
    long cantidadRegistros = ftell(inventario) / sizeof(Producto);
    long primero = 0, ultimo = cantidadRegistros - 1;
    bool encontrado = false;
    while (primero <= ultimo)
    {
        long medio = (primero + ultimo) / 2;
        fseek(inventario, medio * sizeof(Producto), SEEK_SET);
        if (fread(&producto, sizeof(Producto), 1, inventario) != 1)
            break;
        if (producto.codigo == codigo)
        {
            encontrado = true;
            break;
        }
        else if (codigo > producto.codigo)
            primero = medio + 1;
        else
            ultimo = medio - 1;
    }
    fclose(inventario);
    return encontrado;
}

void mostrarResumen(int semana, int mes)
{
    char nombreArchivo[40] = "comandas_semana_s0-00.dat";
    nombreArchivo[17] = '0' + semana;
    nombreArchivo[19] = '0' + mes / 10;
    nombreArchivo[20] = '0' + mes % 10;

    FILE *comandas = fopen(nombreArchivo, "rb");
    if (comandas == NULL)
    {
        cout << "No se pudo abrir " << nombreArchivo << "." << endl;
        return;
    }

    Comanda comanda;
    int leido = fread(&comanda, sizeof(Comanda), 1, comandas);
    float totalBuffet = 0;

    cout << "\nResumen de " << nombreArchivo << endl;
    while (leido == 1)
    {
        int idMozo = comanda.idMozo;
        int cantidadVendida = 0;
        float comisionMozo = 0;
        float totalMozo = 0;

        // cierre.cpp genera este archivo ordenado por idMozo.
        while (leido == 1 && comanda.idMozo == idMozo)
        {
            Producto producto;
            cantidadVendida += comanda.cantidad;
            comisionMozo += comanda.comision;

            if (buscarProducto(comanda.codigoProducto, producto))
                totalMozo += producto.precio * comanda.cantidad;
            else
                cout << "Advertencia: no existe el producto "
                     << comanda.codigoProducto << "." << endl;

            leido = fread(&comanda, sizeof(Comanda), 1, comandas);
        }

        Mozo mozo;
        totalBuffet += totalMozo;
        cout << "\nMozo: ";
        if (buscarMozo(idMozo, mozo))
            cout << mozo.nombre;
        else
            cout << "ID " << idMozo;
        cout << " (ID " << idMozo << ")" << endl;
        cout << "Cantidad vendida: " << cantidadVendida << endl;
        cout << "Comision a pagar: " << comisionMozo << endl;
        cout << "Total vendido: " << totalMozo << endl;
    }

    cout << "\nTotal del buffet: " << totalBuffet << endl;
    fclose(comandas);
}

int main()
{
    int semana, mes;
    cout << "Ingrese el numero de semana (1-4): ";
    cin >> semana;
    cout << "Ingrese el mes (1-12): ";
    cin >> mes;

    if (!cin || semana < 1 || semana > 4 || mes < 1 || mes > 12)
    {
        cout << "La semana o el mes no son validos." << endl;
        return 1;
    }

    mostrarResumen(semana, mes);
    return 0;
}
