# Sorting Algorithms — Comparativa de Rendimiento

Implementación y comparación de cuatro algoritmos clásicos de ordenamiento en **C++** y **Python**, con medición de tiempo real de ejecución para distintos tamaños de entrada.

---

## Algoritmos implementados

### 1. Bubble Sort

Recorre el arreglo comparando pares adyacentes e intercambiándolos si están en el orden incorrecto. El elemento mayor "burbujea" hacia el final en cada pasada.

**Optimización:** si en una pasada completa no ocurre ningún intercambio, el arreglo ya está ordenado y el algoritmo termina anticipadamente.

| Caso | Complejidad |
|---|---|
| Mejor | O(n) — arreglo ya ordenado |
| Promedio | O(n²) |
| Peor | O(n²) |
| Espacio | O(1) |

- **Estable:**  Sí — nunca intercambia elementos iguales
- **Salida temprana:**  Sí — con la bandera `swapped`

---

### 2. Selection Sort

En cada pasada busca el elemento mínimo del subarreglo no ordenado y lo coloca en su posición correcta mediante un único intercambio.

No tiene ninguna optimización para entradas parcialmente ordenadas: siempre realiza exactamente `n(n-1)/2` comparaciones.

| Caso | Complejidad |
|---|---|
| Mejor | O(n²) |
| Promedio | O(n²) |
| Peor | O(n²) |
| Espacio | O(1) |

- **Estable:**  No — el swap puede saltar sobre elementos iguales.
- **Ventaja práctica:** realiza solo `n-1` intercambios, útil cuando mover datos es costoso.

---

### 3. Insertion Sort

Toma cada elemento y lo inserta en su posición correcta dentro de la parte izquierda ya ordenada, desplazando los mayores hacia la derecha.

Es el algoritmo más eficiente de los cuatro cuando el arreglo está **casi ordenado**, ya que el bucle interno apenas itera.

| Caso | Complejidad |
|---|---|
| Mejor | O(n) — arreglo casi ordenado |
| Promedio | O(n²) |
| Peor | O(n²) |
| Espacio | O(1) |

- **Estable:**  Sí — desplaza solo con `>` estricto, nunca mueve iguales
- **Nota:** es la base del algoritmo **Timsort** (usado internamente en Python y Java) para subarreglos pequeños

---

### 4. Shell Sort

Mejora de Insertion Sort que trabaja con saltos de distancia `gap`, reduciéndolo progresivamente hasta llegar a 1. Los saltos grandes ordenan el arreglo "a grosso modo" primero, de modo que cuando `gap = 1` (Insertion Sort puro) queda muy poco trabajo por hacer.

```
gap: n/2 → n/4 → n/8 → ... → 1
```

| Caso | Complejidad |
|---|---|
| Mejor | O(n log n) |
| Promedio | O(n log² n) |
| Peor | O(n²) — depende de la secuencia de gaps |
| Espacio | O(1) |

- **Estable:**  No — los saltos pueden reordenar elementos iguales
- **Ventaja:** mejor rendimiento general sin necesidad de recursión

---

## Comparativa de rendimiento

```
                  ARREGLO ALEATORIO (n = 1000, aproximado)

  Más lento  ████████████████████████  Bubble Sort     ~4500 μs
             ███████████████████       Selection Sort  ~1800 μs
             ████████████              Insertion Sort  ~900  μs
  Más rápido ████                      Shell Sort      ~90   μs
```

> Los tiempos varían según el hardware. La diferencia se vuelve más pronunciada al aumentar `n`.

---

## Estabilidad

Un algoritmo es **estable** si preserva el orden relativo de elementos con el mismo valor.

```
Entrada:   [3a, 3b, 1]   (3a y 3b tienen el mismo valor pero distinto origen)

Estable:   [1, 3a, 3b]   ← 3a sigue antes que 3b  ✅
Inestable: [1, 3b, 3a]   ← el orden relativo se perdió  ❌
```

| Algoritmo | Estable |
|---|---|
| Bubble Sort | ✅ |
| Insertion Sort | ✅ |
| Selection Sort | ❌ |
| Shell Sort | ❌ |

---

## ¿Cuándo usar cada uno?

| Situación | Algoritmo recomendado | Razón |
|---|---|---|
| Arreglo pequeño (n < 20) | Insertion Sort | Overhead mínimo, supera a O(n log n) |
| Arreglo casi ordenado | Insertion Sort | Se comporta como O(n) |
| Pocos intercambios permitidos | Selection Sort | Solo hace n-1 swaps |
| Tamaño mediano, sin recursión | Shell Sort | Mejor complejidad sin stack overhead |
| Se requiere estabilidad | Bubble o Insertion Sort | Únicos estables de los cuatro |
| Datos grandes en general | Quicksort / Mergesort | Fuera del alcance de este proyecto |

---

## Estructura del proyecto

```
sorting-algorithms/
├── Algoritmos_orden.cpp      # Implementación en C++
├── Algoritmos_orden.py       # Implementación en Python
└── README.md
```


### Salida esperada (ejemplo)

```
--- Size: 10 ---
Bubble Sort    took   3.00 μs
Selection Sort took   2.00 μs
Insertion Sort took   1.50 μs
Shell Sort     took   1.20 μs

--- Size: 100 ---
Bubble Sort    took  120.00 μs
Selection Sort took   80.00 μs
Insertion Sort took   45.00 μs
Shell Sort     took   15.00 μs

--- Size: 1000 ---
Bubble Sort    took 4500.00 μs
Selection Sort took 1800.00 μs
Insertion Sort took  900.00 μs
Shell Sort     took   90.00 μs
```

---

## Referencias

- Astrachan, O. L. (2003). *Bubble sort: An archaeological algorithmic analysis*. ACM SIGCSE Bulletin, 35(1), 1–5.
- Machkasova, E. (2011). *Why insertion sort works best for small inputs*. University of Minnesota, Morris.
- Reddy, R. G. et al. (2017). *An empirical study and analysis on sorting algorithms*. IJMET, 8(8), 488–498.
- Silas Faki, M. et al. (2016). *An empirical analysis of internal sorting algorithms*. JAMCS, 16(2), 1–12.
- Global Scientific Journal. (2021). *Performance evaluation of sorting techniques*. GSJ, 9(4), 103–112.