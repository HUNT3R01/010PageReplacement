#include <stdio.h>
#include <stdbool.h>
#include "simulator.h"


// FIFO (First-In, First-Out)
void simulate_FIFO(int n_frames, int *sequence, int seq_len) {
    printf("\n--- FIFO (N=%d) ---\n", n_frames);
    printf("Step | Ref | Result | Frames             | Evicted\n");
    
    int frames[n_frames];
    // Inicializamos los marcos con -1 para indicar que están vacíos
    for(int i = 0; i < n_frames; i++) frames[i] = -1; // -1 means empty
    
    int hits = 0, misses = 0;
    // Puntero que rastrea cuál es el marco más antiguo
    int fifo_ptr = 0; 

    for (int step = 1; step <= seq_len; step++) {
        int ref = sequence[step - 1];
        // Buscamos si la página ya está en memoria
        int hit_idx = find_page(frames, n_frames, ref);

        if (hit_idx != -1) {
            // Acierto, la pagina ya está en memoria
            hits++;
            print_step(step, ref, true, frames, n_frames, -1);
        } else {
            // Fallo, la página no está en memoria
            misses++;
            int victim = -1;
            
            // Verificamos si hay un marco vacío para colocar la nueva página
            int empty_idx = -1;
            for (int i = 0; i < n_frames; i++) {
                if (frames[i] == -1) { empty_idx = i; break; }
            }

            if (empty_idx != -1) {
                frames[empty_idx] = ref; 
            } else {
                // La memoria está llena, debemos expulsar la página más antigua
                victim = frames[fifo_ptr];
                frames[fifo_ptr] = ref;
                fifo_ptr = (fifo_ptr + 1) % n_frames; // Mover el puntero FIFO al siguiente marco   
            }
            print_step(step, ref, false, frames, n_frames, victim);
        }
    }
    print_summary("FIFO", hits, misses);
}

// MIN / Optimal
void simulate_MIN(int n_frames, int *sequence, int seq_len) {
    printf("\n--- MIN/Optimal (N=%d) ---\n", n_frames);
    printf("Step | Ref | Result | Frames             | Evicted\n");
    
    int frames[n_frames];
    for(int i = 0; i < n_frames; i++) frames[i] = -1;
    
    int hits = 0, misses = 0;

    for (int step = 1; step <= seq_len; step++) {
        int ref = sequence[step - 1];
        int hit_idx = find_page(frames, n_frames, ref);

        if (hit_idx != -1) {
            // Acierto, la página ya está en memoria
            hits++;
            print_step(step, ref, true, frames, n_frames, -1);
        } else {
            // Fallo, la página no está en memoria
            misses++;
            int victim = -1;
            int empty_idx = -1;
            for (int i = 0; i < n_frames; i++) {
                if (frames[i] == -1) { empty_idx = i; break; }
            }

            if (empty_idx != -1) {
                frames[empty_idx] = ref;
            } else {
                // Memoria llena, encontrar la página que se usará más lejos en el futuro
                int farthest_idx = -1;
                int farthest_dist = -1;

                for (int i = 0; i < n_frames; i++) {
                    int next_use = 999999; // Assume it's never used again
                    for (int j = step; j < seq_len; j++) { // Observamos el futuro a partir del siguiente paso
                        if (sequence[j] == frames[i]) {
                            next_use = j;
                            break;
                        }
                    }
                    // Si esta página se usará más lejos que la página actualmente considerada como la más lejana, actualizamos el candidato a víctima
                    if (next_use > farthest_dist) {
                        farthest_dist = next_use;
                        farthest_idx = i;
                    }
                }
                victim = frames[farthest_idx];
                frames[farthest_idx] = ref;
            }
            print_step(step, ref, false, frames, n_frames, victim);
        }
    }
    print_summary("MIN", hits, misses);
}


// LRU (Least Recently Used)
void simulate_LRU(int n_frames, int *sequence, int seq_len) {
    printf("\n--- LRU (N=%d) ---\n", n_frames);
    printf("Step | Ref | Result | Frames             | Evicted\n");
    
    int frames[n_frames];
    int last_used[n_frames]; // tiempo del último uso de cada marco
    for(int i = 0; i < n_frames; i++) {
        frames[i] = -1;
        last_used[i] = 0; 
    }
    
    int hits = 0, misses = 0;

    for (int step = 1; step <= seq_len; step++) {
        int ref = sequence[step - 1];
        int hit_idx = find_page(frames, n_frames, ref);

        if (hit_idx != -1) {
            // Acierto, la página ya está en memoria
            hits++;
            last_used[hit_idx] = step; // Actualizamos el tiempo de último uso para esta página
            print_step(step, ref, true, frames, n_frames, -1);
        } else {
            // Fallo, la página no está en memoria
            misses++;
            int victim = -1;
            int empty_idx = -1;
            for (int i = 0; i < n_frames; i++) {
                if (frames[i] == -1) { empty_idx = i; break; }
            }

            if (empty_idx != -1) {
                frames[empty_idx] = ref;
                last_used[empty_idx] = step;
            } else {
                // Memoria llena, encontrar la página que se usó hace más tiempo
                int lru_idx = 0;
                for (int i = 1; i < n_frames; i++) {
                    if (last_used[i] < last_used[lru_idx]) {
                        lru_idx = i;
                    }
                }
                victim = frames[lru_idx];
                frames[lru_idx] = ref;
                last_used[lru_idx] = step; // Actualizamos el tiempo de último uso para la nueva página
            print_step(step, ref, false, frames, n_frames, victim);
        }
    }
    print_summary("LRU", hits, misses);
}
}

// SECOND CHANCE / CLOCK (Extra Credit)
void simulate_SECOND_CHANCE(int n_frames, int *sequence, int seq_len) {
    printf("\n--- Second Chance (N=%d) ---\n", n_frames);
    printf("Step | Ref | Result | Frames             | Evicted\n");
    
    int frames[n_frames];
    int ref_bits[n_frames]; // reciente = 1, no reciente = 0
    for(int i = 0; i < n_frames; i++) {
        frames[i] = -1;
        ref_bits[i] = 0;
    }
    
    int hits = 0, misses = 0;
    int clock_ptr = 0;

    for (int step = 1; step <= seq_len; step++) {
        int ref = sequence[step - 1];
        int hit_idx = find_page(frames, n_frames, ref);

        if (hit_idx != -1) {
            hits++;
            ref_bits[hit_idx] = 1; // Da una segunda oportunidad a esta página al marcarla como reciente
            print_step(step, ref, true, frames, n_frames, -1);
        } else {
            misses++;
            int victim = -1;
            int empty_idx = -1;
            for (int i = 0; i < n_frames; i++) {
                if (frames[i] == -1) { empty_idx = i; break; }
            }

            if (empty_idx != -1) {
                frames[empty_idx] = ref;
                ref_bits[empty_idx] = 1;
            } else {
                // Avanza el puntero del reloj hasta encontrar una página con bit de referencia 0 para expulsar
                while (true) {
                    if (ref_bits[clock_ptr] == 1) {
                        // Encontramos una página con bit de referencia 1, le damos una segunda oportunidad y la marcamos como no reciente
                        ref_bits[clock_ptr] = 0;
                        clock_ptr = (clock_ptr + 1) % n_frames;
                    } else {
                        // Encontramos una página con bit de referencia 0, esta es la víctima
                        victim = frames[clock_ptr];
                        frames[clock_ptr] = ref;
                        ref_bits[clock_ptr] = 1; // New page gets a 1
                        clock_ptr = (clock_ptr + 1) % n_frames;
                        break;
                    }
                }
            }
            print_step(step, ref, false, frames, n_frames, victim);
        }
    }
    print_summary("Second Chance", hits, misses);
}
