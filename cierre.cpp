
/*datos claves:

/*enunciado:junta las planillas de todos los dias de la semana
en una sola planilla semanal,ordenada por mozo.
entonces tenemos q generar(comandas_semana_sx-mm.dat) pero
necesitamos leer (comandas_dd_mm_aaaa.dat(varios))*/

// librerias
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

// estuctura q me da la catedra
struct Comanda {
  int idMozo;
  int codigoProducto;
  int cantidad;
  float comision;
};

const char* TEMPORAL = "semana_tmp.dat";

// declaro a los esqueletos de las funciones
bool pedir_datos(int& semana, int& mes, int& cantdias);
void apareo(const char* nomA, const char* nomB, const char* planilla_nueva);
bool copiar_archivo(const char* origi, const char* destin);
int estado_archivo(const char* nombre);

// main
int main() {
  int semana, mes, cantdias;

  if (!pedir_datos(semana, mes, cantdias)) {
    cout << "datos incorrectos" << endl;
    return 1;
  }

  char nombreSemanal[30] = "comandas_semana_s0-00.dat";
  nombreSemanal[17] = '0' + semana;    // digito de la semana
  nombreSemanal[19] = '0' + mes / 10;  // decena del mes
  nombreSemanal[20] = '0' + mes % 10;  // unidad del mes

  if (estado_archivo(nombreSemanal) == 2) {
    cout << nombreSemanal << " ya existe, se vuelve a armar" << endl;
  }

  // creo la planilla semanal vacia ("wb" crea el archivo o lo vacia)
  FILE* f = fopen(nombreSemanal, "wb");
  if (f == NULL) {
    cout << "No se pudo crear " << nombreSemanal << endl;
    return 1;
  }
  fclose(f);
  cout << "Archivo creado: " << nombreSemanal << endl;

  char nombreDia[100];

  int unidos = 0;
  for (int i = 1; i <= cantdias; i++) {
    cout << "ingrese el nombre de la planilla del dia " << i
         << " (ej: comandas_03-06-2025.dat): " << endl;
    cin >> nombreDia;

    int estado = estado_archivo(nombreDia);
    if (estado == 0) {
      cout << nombreDia << " no existe (la planilla todavia no esta creada)"
           << endl;
    } else if (estado == 1) {
      cout << nombreDia << " esta vacia, se saltea" << endl;
    } else {
      // semanal (lo acumulado) + dia nuevo -> temporal, ordenado por mozo
      apareo(nombreSemanal, nombreDia, TEMPORAL);
      // el temporal pasa a ser la nueva planilla semanal
      if (copiar_archivo(TEMPORAL, nombreSemanal)) {
        cout << nombreDia << " unido" << endl;
        unidos++;
      } else {
        cout << "no se pudo copiar el resultado de " << nombreDia << endl;
      }
    }
  }

  cout << "se unieron " << unidos << " dia(s) en " << nombreSemanal << endl;
  return 0;
}

// funciones
bool pedir_datos(int& semana, int& mes, int& cantdias) {
  cout << "ingrese el numero de la semana(1-4): " << endl;
  cin >> semana;
  if (semana < 1 || semana > 4) {
    return false;
  }

  cout << "ingrese el mes(1-12): " << endl;
  cin >> mes;
  if (mes < 1 || mes > 12) {
    return false;
  }

  cout << "ingrese la cantidad de dias que tiene la semana a cerrar" << endl;
  cin >> cantdias;
  if (cantdias < 1 || cantdias > 7) {
    return false;
  }

  return true;
}

int estado_archivo(const char* nombre) {
  FILE* f = fopen(nombre, "rb");
  if (f == NULL) {
    return 0;
  }

  Comanda r;
  int leido = fread(&r, sizeof(Comanda), 1, f);
  fclose(f);

  if (leido == 1) {
    return 2;
  } else {
    return 1;
  }
}

void apareo(const char* nomA, const char* nomB, const char* planilla_nueva) {
  FILE* a = fopen(nomA, "rb");
  FILE* b = fopen(nomB, "rb");
  FILE* pln = fopen(planilla_nueva, "wb");

  Comanda ra, rb;

  int la = fread(&ra, sizeof(Comanda), 1, a);
  int lb = fread(&rb, sizeof(Comanda), 1, b);

  while (la == 1 && lb == 1) {  // mientras haya en AMBOS
    if (ra.idMozo < rb.idMozo) {
      fwrite(&ra, sizeof(Comanda), 1, pln);
      la = fread(&ra, sizeof(Comanda), 1, a);  // avanzo A
    } else {
      fwrite(&rb, sizeof(Comanda), 1, pln);
      lb = fread(&rb, sizeof(Comanda), 1, b);  // avanzo B
    }
  }

  while (la == 1) {  // agoto A (si fue el que sobró)
    fwrite(&ra, sizeof(Comanda), 1, pln);
    la = fread(&ra, sizeof(Comanda), 1, a);
  }

  while (lb == 1) {  // agoto B
    fwrite(&rb, sizeof(Comanda), 1, pln);
    lb = fread(&rb, sizeof(Comanda), 1, b);
  }

  fclose(a);
  fclose(b);
  fclose(pln);
}

bool copiar_archivo(const char* origi, const char* destin) {
  FILE* o = fopen(origi, "rb");
  FILE* d = fopen(destin, "wb");

  if (o == NULL) {
    return false;
  }

  if (d == NULL) {
    return false;
  }

  Comanda r;  // guarda de a uno

  while (fread(&r, sizeof(Comanda), 1, o) == 1) {
    fwrite(&r, sizeof(Comanda), 1, d);
  }

  fclose(o);
  fclose(d);

  return true;
}