#include<iostream>
#include<cstdio>//para los archivos bin(fopen, fread,fwrite..)
#include<cstring>//para el manejo de textos(strcmp,strcpy..)
using namespace std;


//lo que nos dio la catedra para ordenar
struct ComandaHistorica{ //Mayusculas -eli
    //los datos que nos dio la catedra * eli rellenó 
    char fecha[11];
    char nombreMozo[50];
    int codigoProducto;
    int cantidad;
    float comision;

};

//donde guardaremos a los mozos.dat
struct Mozo{
int idMozo;
char nombre [50];
char contraseña [20];
float totalComision =0;
};
//aca iria el struct de la nueva comanda historica que nos pide para ordenar* Listo
struct Comanda {
    int idMozo;
    int codigoProducto;
    int cantidad;
    float comision;
};

//valor que nos dan para encriptar las claves(corrimiento k)
const int clave_k=5;

//funcion que toma el texto y le suma 5
void encriptarClave(const char* clave_original,char*clave_destino, int k){
int i=0;
//revisa el texto letra por letra*//
while(clave_original[i]!=0){ //el bucle se repite hasta que el texto termina
clave_destino[i]=clave_original[i]+k; //suma k en cada letra
i++;
}
clave_destino[i]=0; //avisa que acá termina el texto
}

/* No solo creamos la lista de mozos, también creamos la función -eli
Bool porque Gimena más adelante retorna true o false - eli */
bool crearArchivoMozos() {
Mozo listaMozos[10]; //creo una lista de 10 lugares para los mozos
int cantidadMozos=0;
ComandaHistorica comandaLeida; // aca arranca vacia

FILE* archivoviejo = fopen("comandas_historicas.dat","rb");

while(fread(&lectura,sizeof(ComandaHistorica),1,archivoviejo)){//del archivo phist saco un elemento de lo que mida en comanda_historica y guardo dentro de la variable registro
    //ya se guardo este mozo en la lista?
    bool yaExiste=false;
    for(int i=0;i<cantidadMozos;i++){
        if(strcmp(listaMozos[i].nombre, comandaLeida.nombreMozo)==0){
             /*strcpm no existe! registro tampoco, declaraste "lectura" (Lo voy a cambiar por comandaLeída) - eli*/ 
            yaExiste=true;
        }
        }

    if(!yaExiste){
    Mozo nuevo;
    nuevo.idMozo=cantidadMozos+1;//aca asigna un id(mozo1,mozo2,etc)
    strcpy(nuevo.nombre, comandaLeida.nombreMozo);//agarra el nuevo nombre y lo copia y pega

    //crea su contraseña inicial
    char clave_texto[10];
    sprintf(clave_texto, nuevo.idMozo);
    encriptarClave(clave_texto,nuevo.contraseña,clave_k);//nro de idMozo guardado en la variable

 listaMozos[cantidadMozos]=nuevo;
 cantidadMozos++;
    }
}



fclose(archivoviejo); //cierro el archivo anterior

//creo mozo.dat para poder escribir
FILE*pMozos=fopen("mozos.dat","wb");
if(!pMozos){
  cout<<"no se pudo crear mozos.dat"<<endl;
  return false;  //por si el archivo no se pudo crear, lo frena ahi
}
for (int i = 0; i < cantidadMozos; i++) {
        fwrite(&listaMozos[i], sizeof(Mozo), 1, pMozos);
    }
    fclose(pMozos);

    cout <<"se guardo correctamente"<<cantidadMozos<<" mozos en mozos.dat" << endl;
    return true;
}

int main(){
cout<<"--INICIO DE NORMALIZACION--"<<endl;

//aca van nuestras llamadas
crearArchivoMozos();
return 0;
}
