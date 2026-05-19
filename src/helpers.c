#include <stdio.h>
#include <stdbool.h>
#include "simulator.h"

// Evalua si una página está presente en los marcos de memoria. Devuelve el índice del marco si es un HIT, o -1 si es un MISS.
int find_page(int *frames, int n_frames, int page) {
    for (int i = 0; i < n_frames; i++) {
        if (frames[i] == page) {
            return i; // HIT: Retorna el índice del marco donde se encuentra la página
        }
    }
    return -1; // MISS: La pagina no está presente en los marcos
}

// Imprime el estado actual de los marcos de memoria después de cada referencia, indicando si fue un HIT o MISS, y cuál página fue expulsada si es un MISS.
void print_step(int step, int ref, bool is_hit, int *frames, int n_frames, int victim) {
    // Imprime el primer paso de la línea con el número de paso, la referencia, y si fue un HIT o MISS
    printf("%4d | %3d | %s | [", step, ref, is_hit ? "HIT " : "MISS");
    
    // Imprime el contenido actual de los marcos de memoria
    for (int i = 0; i < n_frames; i++) {
        if (frames[i] == -1) {
            // -1 significa vacio
            printf(" - "); 
        } else {
            printf("%2d ", frames[i]);
        }
        
        if (i < n_frames - 1) {
            printf(",");
        }
    }
    printf("]");

    // Si no fue un HIT, imprime la página víctima que fue expulsada
    if (!is_hit && victim != -1) {
        printf(" | Victim: %d", victim);
    }
    
    printf("\n");
}

// Imprime un resumen al final de la simulación, mostrando el total de hits, misses, y la tasa de aciertos para cada algoritmo.
void print_summary(const char *algo_name, int hits, int misses) {
    int total_requests = hits + misses;
    double hit_rate = 0.0;
    
    if (total_requests > 0) {
        hit_rate = ((double)hits / total_requests) * 100.0;
    }

    printf("Totals for %s: hits=%d misses=%d (Hit Rate: %.2f%%)\n", 
           algo_name, hits, misses, hit_rate);
    printf("==================================================\n");
}