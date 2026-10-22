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

**Integrantes:** Gimena Magali Cristaldo Fleitas e Ingrid Elena Espínola:

**Tareas:** Función de normalización, lectura del archivo binario `comandas_historicas.dat`, control de IDs únicos y generación de archivo maestro `mozos.dat`, buscar ID por mozo, crear comandas diarias, actualizar stock y ordenar mozo por ID.

#### Explicación por partes

* **Procesamiento de binarios:** Se leen comandas historicas registro por registro con `fread`.
* **Control de duplicados:** Se utiliza la función `strcmp` para comparar los nombres y evitar duplicar mozos en memoria.
* **Asignación de IDs:** Si el mozo no existe, se le asigna un ID incremental (es decir, cantidadMozos + 1)  y su respectiva clave encriptada.
* **Encriptar Clave:** Aplica un corrimiento de cinco posiciones a cada carácter de la clave.
* **Crear Archivo Mozos:** Identifica los mozos sin repetirlos, asigna sus IDs, acumula sus comisiones y genera `mozos.dat`.
* **Buscar ID por mozo:** Recorre `mozos.dat` con `fread` y compara los nombres con `strcmp`. Si coinciden, devuelve el ID del mozo.
* **Crear Comandas Diarias:** Recorre el archivo histórico, transforma cada registro al formato nuevo y lo guarda en el archivo correspondiente a su fecha.
* **Actualizar Stock:** Busca el producto por código, descuenta la cantidad vendida y sobrescribe el registro utilizando `fseek` y `fwrite`.
* **Ordenar Mozos por ID:** Aplica un ordenamiento por burbujeo, comparando e intercambiando las comandas directamente en el archivo.

### Ventas.cpp

**Integrantes:** Britany Jazmin Leon Navarro

**Tareas:** Pide la fecha del dia una sola vez al empezar y abre (o crea) la planilla de ese dia. Despues, por cada venta pide el numero de mozo y su clave para validarlos, busca el precio y el stock en el inventario, calcula la comision, actualiza el stock y agrega la venta a la planilla del dia. Al finalizar, la deja ordenada por mozo.

#### Explicación por partes

* **Inicio y planilla del día:** solicito la fecha y creo el nombre `comandas_dd-mm-aaaa.dat`. Abro la planilla en modo "ab" para agregar ventas sin borrar las anteriores.
* **Validación del mozo y clave:** con `validarMozo()`, busco al mozo en "mozos.dat" y verifico su clave mediante un corrimiento de 5 caracteres y la función `strcmp()`.
* **Búsqueda en el inventario:** con `buscarProducto()`, utilizo búsqueda binaria en "inventario.dat" para encontrar el producto por código y obtener su precio y stock.
* **Validación de cantidad y stock:** comprueba que la cantidad ingresada sea mayor que cero y que no supere el stock disponible.
* **Cálculo de comisión:** calcula la comisión del mozo aplicando el 10 % al precio del producto multiplicado por la cantidad vendida.
* **Actualización de stock y guardado:** descuenta del inventario la cantidad vendida y guarda los datos de la venta en la planilla del día.
* **Cierre y ordenamiento:** cuando el usuario termina de cargar ventas, cierra los archivos y ejecuta `ordenarPlanilla`, que lee las comandas, las ordena por número de mozo mediante el método de selección y vuelve a guardarlas en el archivo.

### Cierre.cpp

**Integrante:** Fernandez Milagros.

**Tareas:** Junta las planillas de todos los dias de la semana en una sola planilla semanal,ordenada por mozo.
Entonces tenemos q generar(comandas_semana_sx-mm.dat) pero necesitamos leer (comandas_dd_mm_aaaa.dat(varios)).

#### Explicación por partes

* **Juntar los días:** use apareo, porque las planillas diarias ya vienen ordenadas por mozo. Así no hace falta volver a ordenarlas.
* **Recorrer los días de la semana:** el apareo une solo dos archivos y una semana tiene hasta siete planillas, por eso uso un "for" que va acumulando las planillas de los distintos días, de a una.
* **Leer y escribir:** como no se puede leer y escribir el mismo archivo a la vez, guardo el resultado del apareo en un archivo temporal, y la función `copiar_archivo` lo pega en la planilla semanal.
* **Planillas diarias:** las genera `ventas.cpp`, por eso `cierre.cpp` solo recibe el nombre de cada una y la busca.
* **Validación de datos:** la hace la función `pedir_datos`, que controla con `if` que la semana, el mes y la cantidad de días estén dentro de un rango válido. Si algún dato es incorrecto, el programa avisa y termina.
* **Casos raros:** hice la función `estado_archivo`, que evalúa el estado de una planilla y devuelve un número: "0" si el archivo no existe (la planilla del día todavía no se creó), "1" si existe pero está vacío (ese día no se cargaron ventas) y "2" si tiene registros. Si no existe o está vacía, el programa avisa y la saltea; si tiene registros, la une a la semanal.

### Resumen.cpp

**Integrantes:** Erik Ian Burs

**Tareas:** Pide que muestre en pantalla por cada mozo individualmente cuantos productos vendió en la semana y cuanta plata de comision hay que pagar, y al final de todo, pide la cantidad total de productos que el buffet vendió.

#### Explicación por partes

* **Pedir numero de semana y mes:** Primero se pide el numero de samana (de 1 a 4) y luego, el mes (de 1 a 12), con el objetivo de poder usar el archivo `comandas_semana_sX-MM.dat` correspondiente. En el caso que se introduzcan mal los valores o que no se encuentren los archivos, se mostrará el error correspondiente.
* **Verificación de Mozos y Productos:** Antes de ejecutar los productos se realiza una verificación para ver si existen los mozos, usando la funcion `buscarMozo`, y los productos, usando la función `buscarProducto` con sus respectivos archivos(`mozos.dat` e `inventario.dat`), esas funciones sirven tambien para poder saber los nombres de los mozos y los precios de los productos.
* **Operaciones predidas:** Si la verificación resulta exitosa, se realizan las operaciones pedidas.
* **Muestra en pantalla:** Una vez realizadas las operaciones para cada mozo, se van a mostrar los resultados. Y finalmente, cuandos toda la informacion de los mozos se mostró, se presenta la cantidad total vendida y los ingresos totales (incluyendo la comisión) del buffet.
