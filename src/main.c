#include <stdio.h>
#include <stdlib.h>
#include "simulator.h"


void demo_beladys_anomaly() {
    printf("\n==================================================\n");
    printf("Creditos Extras\n");
    printf("==================================================\n");
    printf("Belady's Anomalmente da un proceso más a memoria \n");
    printf("(frames) aveces puede cuasar mas fallos de pagina en FIFO.\n\n");

    // Secuencia clasica conocida 
    int belady_seq[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int seq_len = sizeof(belady_seq) / sizeof(belady_seq[0]);

    printf("--- Corriendo con N=3 Frames ---\n");
    simulate_FIFO(3, belady_seq, seq_len);

    printf("\n--- Corriendo con N=4 Frames ---\n");
    simulate_FIFO(4, belady_seq, seq_len);
    
    printf("\nCONCLUSION: Notifica como N=3 tiene 9 misses, pero incremente\n");
    printf("memoria a N=4 actualmente causa 10 misses!\n");
    printf("==================================================\n\n");
}


int main() {
    int n_frames = 3;
    int reference_string[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int seq_len = sizeof(reference_string) / sizeof(reference_string[0]);

    printf("Empezando el Simulador de Reemplazo de Páginas...\n");
    printf("Frames (N): %d\n", n_frames);
    printf("Longitud de la Secuencia: %d\n", seq_len);

    // Algoritmos
    simulate_FIFO(n_frames, reference_string, seq_len);
    simulate_MIN(n_frames, reference_string, seq_len);
    simulate_LRU(n_frames, reference_string, seq_len);

    // Algoritmo extra 
    simulate_SECOND_CHANCE(n_frames, reference_string, seq_len);

    // Demostracion
    demo_beladys_anomaly();

    return 0;
}