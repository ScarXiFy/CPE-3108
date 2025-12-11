#ifndef FUNC_H
#define FUNC_H
#define MAX_POINTS 100   

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

float lagrange_calc(Species *sp, float temp);

#endif
