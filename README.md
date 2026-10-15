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
cp datos/comandas_historicas.dat comandas_historicas.dat
cp datos/inventario.dat inventario.dat 
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

## Resolución de partes claves

### Normalizacion.cpp

**Integrantes**: Gimena Magali Cristaldo Fleitas e Ingrid Elena Espínola:
 
**Tareas**: Función de normalización, lectura del archivo binario (comandas_historicas.dat), control de IDs únicos y generación de archivo maestro (mozos.dat), buscar ID por mozo, crear comandas diarias, actualizar stock y ordenar mozo por ID.

**Explicación por partes**: 

- Procesamiento de binarios: Se leen comandas historicas registro por registro con fread.
- Control de duplicados: Se utiliza la función strcmp para comparar los nombres y evitar duplicar mozos en memoria. 
- Asignación de IDs: Si el mozo no existe, se le asigna un ID incremental (es decir, cantidadMozos + 1)  y su respectiva clave encriptada.
- Encriptar Clave: Aplica un corrimiento de cinco posiciones a cada carácter de la clave.
- Crear Archivo Mozos: Identifica los mozos sin repetirlos, asigna sus IDs, acumula sus comisiones y genera mozos.dat.
- Buscar ID por mozo: Recorre mozos.dat con fread y compara los nombres con strcmp. Si coinciden, devuelve el ID del mozo.
- Crear Comandas Diarias: Recorre el archivo histórico, transforma cada registro al formato nuevo y lo guarda en el archivo correspondiente a su fecha.
- Actualizar Stock: Busca el producto por código, descuenta la cantidad vendida y sobrescribe el registro utilizando fseek y fwrite.
- Ordenar Mozos por ID: Aplica un ordenamiento por burbujeo, comparando e intercambiando las comandas directamente en el archivo.

### Ventas.cpp

texto

### Cierre.cpp

texto

### Resumen.cpp

texto