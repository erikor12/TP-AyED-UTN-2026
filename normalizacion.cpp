#include <iostream>
#include <cstdio>  //para los archivos bin(fopen, fread,fwrite..)
#include <cstring> //para el manejo de textos(strcmp,strcpy..)
using namespace std;

// lo que nos dio la catedra para ordenar
struct ComandaHistorica
{ // Mayusculas -eli
    // los datos que nos dio la catedra * eli rellenó
    char fecha[11];
    char nombreMozo[50];
    int codigoProducto;
    int cantidad;
    float comision;
};

// donde guardaremos a los mozos.dat
struct Mozo
{
    int idMozo;
    char nombre[50];
    char password[20]; // tuve que cambiar contraseña por password, por mi compilador.li
    float totalComision = 0;
};
// aca iria el struct de la nueva comanda historica que nos pide para ordenar* Listo
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

// valor que nos dan para encriptar las claves(corrimiento k)
const int clave_k = 5;

// funcion que toma el texto y le suma 5
void encriptarClave(const char *clave_original, char *clave_destino, int k)
{
    int i = 0;
    // revisa el texto letra por letra*//
    while (clave_original[i] != 0)
    {                                             // el bucle se repite hasta que el texto termina
        clave_destino[i] = clave_original[i] + k; // suma k en cada letra
        i++;
    }
    clave_destino[i] = 0; // avisa que acá termina el texto
}

/* No solo creamos la lista de mozos, también creamos la función -eli
Bool porque Gimena más adelante retorna true o false - eli */
bool crearArchivoMozos()
{
    Mozo listaMozos[10]; // creo una lista de 10 lugares para los mozos
    int cantidadMozos = 0;
    ComandaHistorica comandaLeida; // aca arranca vacia

    FILE *archivoviejo = fopen("comandas_historicas.dat", "rb");
    // Por si no abre el archivo -eli
    if (archivoviejo == NULL)
    {
        cout << "No se pudo abrir el archivo" << endl;
        return false;
    }

    while (fread(&comandaLeida, sizeof(ComandaHistorica), 1, archivoviejo) == 1)
    { // del archivo "archivoviejo" saco un elemento de lo que mida en comanda_historica y guardo dentro de la variable registro
        // ya se guardo este mozo en la lista?
        bool yaExiste = false;
        int indiceMozo = -1; // guarda la posicion si ya existe

        for (int i = 0; i < cantidadMozos; i++)
        {
            if (strcmp(listaMozos[i].nombre, comandaLeida.nombreMozo) == 0)
            {
                /*strcpm no existe! registro tampoco, declaraste "lectura" (Lo voy a cambiar por comandaLeída) - eli*/
                yaExiste = true;
                indiceMozo = i; // verifica en que posicion de la lista está
                break;          // break porque corta el for si ya lo encontró
            }
        }

        if (yaExiste)
        { // SI ya existe, no se crea otro id. Solo suma la comision //le quité el ! pq la lógca estaba invertida .li
            listaMozos[indiceMozo].totalComision += comandaLeida.comision;
        }

        else
        { // Si es un mozo nuevo, ahi recien se le crea un id
            Mozo nuevo;
            nuevo.idMozo = cantidadMozos + 1;              // aca asigna un id(mozo1,mozo2,etc) - id incremental
            strcpy(nuevo.nombre, comandaLeida.nombreMozo); // agarra el nuevo nombre y lo copia y pega
            nuevo.totalComision = comandaLeida.comision;   // arranca con la comision de su 1er ticket
            // crea su contraseña inicial
            char clave_texto[10];
    int auxiliarId=nuevo.idMozo;//para no perder el valor incremental
    int j=0;
    
    if(auxiliarId==0){ //el Id es 0?
        clave_texto[j++]='0';
    } else{
        char alReves[10];
        int k=0;
        while(auxiliarId>0){
        alReves[k] = (auxiliarId%10) + '0';//lo pasa a char 
        auxiliarId = auxiliarId/10;
        k++;
        }
        //da vuelta los digitos para que queden en orden
        while(k>0){
            k--;
            clave_texto[j] = alReves[k];
            j++;
        }
    }
    clave_texto[j]='\0'; //fin de la cadena.
    encriptarClave(clave_texto,nuevo.password,clave_k);//nro de idMozo guardado en la variable
            listaMozos[cantidadMozos] = nuevo;
            cantidadMozos++; // la cantiaad de mozos aunmenta de uno en uno
        }
    }

    fclose(archivoviejo); // cierro el archivo anterior

    // creo mozo.dat para poder escribir
    FILE *pMozos = fopen("mozos.dat", "wb");
    if (!pMozos)
    {
        cout << "no se pudo crear mozos.dat" << endl;
        return false; // por si el archivo no se pudo crear, lo frena ahi
    }
    for (int i = 0; i < cantidadMozos; i++)
    {
        fwrite(&listaMozos[i], sizeof(Mozo), 1, pMozos);
    }
    fclose(pMozos);

    cout << "Se guardaron correctamente: " << cantidadMozos << " mozos en mozos.dat" << endl; // mensaje modificado.li
    return true;
}

// creación fx busqueda para creación comandas/archivos .li

int buscarIdMozo(const char *nombreBuscado)
{

    FILE *archivoMozos = fopen("mozos.dat", "rb"); // abro mozos.dat, lecturabin .li
    if (archivoMozos == NULL)
    {
        cout << "No se pudo abrir el archivo de Mozos." << endl;
        return -1; // la típica .li
    }

    Mozo mozoLeido;
    while (fread(&mozoLeido, sizeof(Mozo), 1, archivoMozos) == 1)
    {
        if (strcmp(mozoLeido.nombre, nombreBuscado) == 0)
        { // si coinciden los nombres:
            int IdEncontrado = mozoLeido.idMozo;
            fclose(archivoMozos);
            return IdEncontrado; // devuelve el id que corresponde .li
        }
    }
    fclose(archivoMozos);
    return -1;
}
bool actualizarStock(int cdgBuscado, int cantVendida)
{
    FILE *archivoInventario = fopen("inventario.dat", "rb+");

    if (archivoInventario == NULL)
    {
        cout << "No se pudo abrir el archivo del inventario." << endl;
        return false;
    }

    Producto productoActualizado;
    while (fread(&productoActualizado, sizeof(Producto), 1, archivoInventario) == 1)
    {
        if (productoActualizado.codigo == cdgBuscado)
        {
            productoActualizado.stockActual -= cantVendida;

            int bytesProducto = sizeof(Producto); // indica cuántos bytes ocupa 1 producto
            fseek(archivoInventario, -bytesProducto, SEEK_CUR);
            fwrite(&productoActualizado, sizeof(Producto), 1, archivoInventario);

            fclose(archivoInventario);
            return true;
        }
    }
    fclose(archivoInventario);
    return false;
}
// me di cuenta re tarde que tenía que ordenarlo por mozos, la re .li
bool ordenarxIdMozo(const char *nombreArchivo)
{
    FILE *archivoComandas = fopen(nombreArchivo, "rb+");
    if (archivoComandas == NULL)
    {
        cout << "No se pudo abrir el archivo de Comandas." << endl;
        return false;
    }

    int cantsComandas = 0; // Inicializo contador para saber cuántas comandas hay que ordenar.li
    Comanda comandaAuxiliar;

    while (fread(&comandaAuxiliar, sizeof(Comanda), 1, archivoComandas) == 1)
    {
        cantsComandas++;
    }
    Comanda comActual;
    Comanda comSig;
    // solo conozco burbujeo así que.li
    for (int i = 0; i < cantsComandas - 1; i++)
    {
        for (int j = 0; j < cantsComandas - 1; j++) //-1 para que no intenten leer dsp del final </3.li
        {
            fseek(archivoComandas, j * sizeof(Comanda), SEEK_SET);

            fread(&comActual, sizeof(Comanda), 1, archivoComandas);
            fread(&comSig, sizeof(Comanda), 1, archivoComandas);

            if (comActual.idMozo > comSig.idMozo)
            {
                int bytesARetroceder = 2 * sizeof(Comanda); // guarda cuántos bytes ocupan 2 comandas.li
                fseek(archivoComandas, -bytesARetroceder, SEEK_CUR);

                fwrite(&comSig, sizeof(Comanda), 1, archivoComandas);
                fwrite(&comActual, sizeof(Comanda), 1, archivoComandas);
                // intercambia los mozos en caso de que estén desordenados.li
            }
        }
    }
    fclose(archivoComandas);
    return true;
}

bool crearComandasDiarias()
{ // es parecido a buscarIdMozo tbh -li
    FILE *archivoViejo = fopen("comandas_historicas.dat", "rb");

    if (archivoViejo == NULL)
    {
        cout << "No se pudo abrir el archivo de Comandas antiguo." << endl;
        return false;
    }

    ComandaHistorica comandaLeida;
    while (fread(&comandaLeida, sizeof(ComandaHistorica), 1, archivoViejo) == 1)
    {
        int idMozo = buscarIdMozo(comandaLeida.nombreMozo);
        if (idMozo == -1)
        {
            cout << "No se encontró el mozo: " << comandaLeida.nombreMozo << endl;
            fclose(archivoViejo);
            return false;
        }

        Comanda ComandaNueva;
        ComandaNueva.idMozo = idMozo;
        ComandaNueva.codigoProducto = comandaLeida.codigoProducto;
        ComandaNueva.cantidad = comandaLeida.cantidad;
        ComandaNueva.comision = comandaLeida.comision;

        char nombreArchivo[40];
        sprintf(nombreArchivo, "comandas_%s.dat", comandaLeida.fecha);

        FILE *archivoDelDia = fopen(nombreArchivo, "ab");

        if (archivoDelDia == NULL)
        {
            cout << "No se pudo crear." << endl;
            fclose(archivoViejo);
            return false;
        }

        fwrite(&ComandaNueva, sizeof(Comanda), 1, archivoDelDia);
        fclose(archivoDelDia);
        ordenarxIdMozo(nombreArchivo); // ordena por mozo cada que se agrega una comanda oaoaoaoaoa.li

        actualizarStock(comandaLeida.codigoProducto, comandaLeida.cantidad);
    }
    fclose(archivoViejo);
    return true;
}
int main()
{
    cout << "--INICIO DE NORMALIZACION--" << endl;

    // aca van nuestras llamadas
    crearArchivoMozos();
    crearComandasDiarias();

    return 0;
}
