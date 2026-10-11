
/*datos claves:
normalizacion:arma la lista de mozos con su comision(deja
las ventas x dia con id de mozoy stock al dia(segun el prog
viejo))

ventas: pide la fecha del dia crea la planilla de ese dia.
pide(mozo,clave) y pone(comision, precio y agrega la venta)
de cada dia. deja ordenada por mozo.
(comandas_dd_mm_aaaa.dat(varios)
*/

/*enunciado:junta las planillas de todos los dias de la semana
en una sola planilla semanal,ordenada por mozo.
entonces tenemos q generar(comandas_semana_sx-mm.dat) pero
necesitamos leer (comandas_dd_mm_aaaa.dat(varios))*/

// libreriias
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

// estuctura q me da la catedra
struct Comanda {
  int idMozo;
  int cantidad;
  int codigoProducto;
  float comision;
};

/*fucion que me devuelve ordenado apareo ya que tengo ordenadas las
planillas de los dias por mozo, enotonces podemos buscar por el idmozo
y generar una nueva planilla ordenada con todas las ventas de la sem*/

/*estructura de apareo de la catedra
void apareo(const char* nomA, const char* nomB, const char* nomC) {
 FILE* a = fopen(nomA, "rb");
 FILE* b = fopen(nomB, "rb");
 FILE* c = fopen(nomC, "wb");
 Registro ra, rb;
 int la = fread(&ra, sizeof(Registro), 1, a);
 int lb = fread(&rb, sizeof(Registro), 1, b);
 while (la == 1 && lb == 1) { // mientras haya en AMBOS
 if (ra.clave < rb.clave) {
 fwrite(&ra, sizeof(Registro), 1, c);
 la = fread(&ra, sizeof(Registro), 1, a); // avanzo A
 } else {
 fwrite(&rb, sizeof(Registro), 1, c);
 lb = fread(&rb, sizeof(Registro), 1, b); // avanzo B
 }
 }
 while (la == 1) { // agoto A (si fue el que sobró)
 fwrite(&ra, sizeof(Registro), 1, c);
 la = fread(&ra, sizeof(Registro), 1, a);
 }
 while (lb == 1) { // agoto B
 fwrite(&rb, sizeof(Registro), 1, c);
 lb = fread(&rb, sizeof(Registro), 1, b);
 }
 fclose(a); fclose(b); fclose(c);
}*/

// esqueleto de funcion de orden
void apareo(const char* nomA, const char* nomB, const char* planilla_nueva) {
  FILE* a = fopen(nomA, "rb");
  FILE* b = fopen(nomB, "rb");
  FILE* pln = fopen(planilla_nueva, "wb");

  Comanda ra, rb;

  int la = fread(&ra, sizeof(Comanda), 1, a);
  int lb = fread(&rb, sizeof(Comanda), 1, b);

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

// main(tengo que tratar de estar lo mas vacia posible)
int main(int argc, char const* argv[]) {
  /* code */
  return 0;
}
