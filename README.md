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
#### Integrante: 
Fernandez Milagros.

#### Tareas:
junta las planillas de todos los dias de la semana
en una sola planilla semanal,ordenada por mozo.
Entonces tenemos q generar(comandas_semana_sx-mm.dat) pero
necesitamos leer (comandas_dd_mm_aaaa.dat(varios)).

#### Explicación por partes

- **Juntar los días:** use apareo, porque las planillas diarias ya vienen ordenadas por mozo. Así no hace falta volver a ordenarlas.

- **Recorrer los días de la semana:** el apareo une solo dos archivos y una semana tiene hasta siete planillas, por eso uso un "for" que va acumulando las planillas de los distintos días, de a una.

- **Leer y escribir:** como no se puede leer y escribir el mismo archivo a la vez, guardo el resultado del apareo en un archivo temporal, y la función `copiar_archivo` lo pega en la planilla semanal.

- **Planillas diarias:** las genera `ventas.cpp`, por eso `cierre.cpp` solo recibe el nombre de cada una y la busca.

- **Validación de datos:** la hace la función `pedir_datos`, que controla con `if` que la semana, el mes y la cantidad de días estén dentro de un rango válido. Si algún dato es incorrecto, el programa avisa y termina.

- **Casos raros:** hice la función `estado_archivo`, que evalúa el estado de una planilla y devuelve un número: "0" si el archivo no existe (la planilla del día todavía no se creó), "1" si existe pero está vacío (ese día no se cargaron ventas) y "2" si tiene registros. Si no existe o está vacía, el programa avisa y la saltea; si tiene registros, la une a la semanal.

### Resumen.cpp

texto