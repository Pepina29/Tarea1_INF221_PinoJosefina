# Documentación

## Entrega

La entrega se realiza por medio de un .txt que contiene los link para github y onedrive.

## Multiplicación de matrices
* Naive: Implementa la multiplicación de matrices usando tres bucles anidados. Calcula cada elemento como la suma de productos fila × columna.
* Strassen: Divide las matrices en 4 submatrices y realiza combinaciones de sumas y restas para reducir el número de multiplicaciones de 8 a 7 por nivel recursivo.

### Programa principal
Matrix_multiplication: Codigo principal que ejecuta los algoritmos Naive y Strassen para medir el tiempo de ejecución y memoria. Además genera archivos de las matrices resultantes y de las mediciones. 
### Scripts
* Matrix_generator: Script en python que genera matrices de diferentes tamaños con distintas distribuciones.
* Plot_generator: Script en python que genera 3 gráficos para comparar los algoritmos ( Tiempo de ejecución, memoria y distribución).

## Ordenamiento de arreglo unidimensional

Algoritmos: MergeSort, QuickSort, std::sort.
* Merge sort: Divide el arreglo en mitades, ordena cada mitad de manera recursiva y luego junta las mitades ordenadas.
* Quick sort: Selecciona un pivote aleatorio, luego reorganiza el arreglo separando menores y mayores al pivote. Esto se hace recursivamente hasta que todo el arreglo esta ordenado.
* Sort: Algoritmo de la biblioteca estandar de c++, utiliza iteradores ( begin() y end()) para mayor eficiencia y optimización.

### Programa principal
Sorting: Codigo principal que ejecuta Merge sort, Quick sort y Sort lo que permite evaluar y comparar eficiencia entre distintos algoritmos de ordenamiento. Además genera archivos de los arreglos resultantes y de las mediciones. 
### Scripts
* Array_generator: Script en python que genera arreglos de diferentes tamaños con distintas distribuciones.
* Plot_generator: Script en python que genera 6 gráficos para comparar los algoritmos ( Tiempo de ejecución, memoria y distribución).
