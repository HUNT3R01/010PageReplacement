#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <stdbool.h>

// Funciones de ayuda
int find_page(int *frames, int n_frames, int page);
void print_step(int step, int ref, bool is_hit, int *frames, int n_frames, int victim);
void print_summary(const char *algo_name, int hits, int misses);

// Algoritmos Principales
void simulate_FIFO(int n_frames, int *sequence, int seq_len);
void simulate_MIN(int n_frames, int *sequence, int seq_len);
void simulate_LRU(int n_frames, int *sequence, int seq_len);

// Algoritmos Opcionales
void simulate_SECOND_CHANCE(int n_frames, int *sequence, int seq_len); 
void demo_beladys_anomaly();

#endif