# Lab010 - Simulador de Reemplazo de Páginas (Page Replacement)

## 📌 Descripción del Proyecto
Este proyecto es un simulador escrito en **C** que modela cómo un sistema operativo gestiona la memoria física limitada (marcos de página) durante la ejecución de un proceso. 

El simulador lee una secuencia de referencias de memoria (virtual page numbers) y evalúa el rendimiento de diferentes algoritmos de reemplazo de páginas, contabilizando los **aciertos (hits)** y los **fallos (misses)**. El programa genera una traza detallada paso a paso del estado de la memoria RAM (marcos) y muestra qué página fue desalojada (evicted) en caso de un fallo con memoria llena.

## 🚀 Algoritmos Implementados
Se implementaron los siguientes algoritmos base requeridos por el laboratorio:
1. **FIFO (First-In, First-Out):** Desaloja la página que lleva más tiempo en memoria.
2. **MIN (Óptimo):** Desaloja la página que tardará más tiempo en volver a ser utilizada en el futuro (usado como referencia ideal).
3. **LRU (Least Recently Used):** Desaloja la página que no ha sido utilizada por el mayor tiempo en el pasado.

### 🌟 Puntos Extra Implementados
- **Algoritmo de Segunda Oportunidad (Reloj):** Una mejora sobre FIFO que utiliza un bit de referencia para dar una "segunda oportunidad" a las páginas que han sido accedidas recientemente antes de desalojarlas.
- **Demostración de la Anomalía de Belady:** Una simulación especial que comprueba matemáticamente cómo, en FIFO, aumentar la cantidad de memoria física (de 3 a 4 marcos) puede provocar *más* fallos de página en lugar de menos.

## 📂 Estructura del Proyecto
El código sigue una estructura profesional de múltiples archivos para mantener el orden y la modularidad:

```text
10-PageRepleacement/
├── Makefile                 # Script de compilación automatizada
├── include/
│   └── simulator.h          # Declaraciones de funciones y estructuras
├── src/
│   ├── main.c               # Punto de entrada, configuración y demo de Belady
│   ├── algorithms.c         # Lógica central de FIFO, MIN, LRU y Segunda Oportunidad
│   └── helpers.c            # Funciones utilitarias para búsqueda y formateo de tablas
└── bin/                     # Directorio auto-generado para archivos objeto y el ejecutable
