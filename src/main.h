#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SPECIES 50      // Maximum number of species (can be adjusted)
#define MAX_POINTS 100     // Maximum data points per species (can be adjusted)

typedef struct {
    float temperature;
    float hatch_time;
} DataPoint;

typedef struct {
    char species_name[50];
    float min_temp;
    float max_temp;
    DataPoint data_points[MAX_POINTS];
    int data_count;
} Species;

// Global variables (declared in main.c)
extern Species species_list[MAX_SPECIES];
extern int species_count;

// Function prototypes
void main_menu(void);
void create_new_dataset(void);
void load_dataset_menu(void);
void species_submenu(Species *sp);
void help_menu(void);
void clear_screen(void);
void pause_screen(void);
void clear_input_buffer(void);

#endif // MAIN_H