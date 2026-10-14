# TP Integrador — Buffet Albert Einstein

Trabajo Práctico grupal de **Algoritmos y Estructuras de Datos** (UTN FRBA) — unidad de **archivos binarios en C/C++**.

> **Grupo:** 1
>
> **Integrantes:**
>
> * Burs Erik - erikor12 - resumen.cpp
> * Cristaldo Gimena Magali - gimenacristaldo-hub - normalizacion.cpp
> * Espinola Ingrid - Voyager1987 - normalizacion.cpp
> * Fernandez Milagros - lulifernandez1217 - cierre.cpp
> * Leon Britany - Brit019 - ventas.cpp

## Cómo trabajar

Los programas leen y escriben archivos `.dat` en la carpeta donde se ejecutan. Los archivos de `datos/` son los **originales** y no se modifican: copiálos a la carpeta donde vas a compilar y correr, y trabajá sobre esas copias.

```bash
cp datos/comandas_historicas.dat datos/inventario.dat .
```

### Compilar y correr cada programa 

(cada uno tiene su propio `main`, no hay `main.cpp`):

```bash
g++ -O2 -o normalizacion normalizacion.cpp
g++ -O2 -o ventas        ventas.cpp
g++ -O2 -o cierre        cierre.cpp
g++ -O2 -o resumen       resumen.cpp
```

### Orden de ejecución

(cada programa deja los archivos que usa el siguiente):

```
./normalizacion     # historicas + inventario  ->  mozos.dat, comandas_dd-mm-aaaa.dat (varios), inventario actualizado
./ventas            # carga interactiva de la semana  ->  agrega a las planillas del día
./cierre            # junta los días de la semana      ->  comandas_semana_sX-mm.dat
./resumen           # imprime el resumen por mozo + total del buffet
```
