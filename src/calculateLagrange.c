#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "func.h"


float lagrange_calc(Species *sp, float temp){
    char buffer[100];
    int numOfPoints;
    int valid_input = 0;

    while (!valid_input) {
        printf("Enter number of data points to use in calculation (at least 4): "); 
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &numOfPoints) == 1) {
            if (sscanf(buffer, "%d", &numOfPoints) == 1) {
                if (numOfPoints > sp->data_count) {
                    printf("Invalid input, not enough data points. Please enter a number less than or equal to %d.\n", sp->data_count);
                }
                else if (numOfPoints < 4) {
                    printf("Invalid input. Please enter a number greater than or equal to 4.\n");
                } else {
                    valid_input = 1;
                }
            } else {
                printf("Invalid input. Please enter a numeric integer.\n");
            }
        }
    }
    
    //EXTRACT POINTS
    DataPoint *dataPoints = malloc(sizeof(DataPoint) * numOfPoints); //data points for calculation
    for(int i=0; i<numOfPoints; i++){
        //getting data points from exitsing data set
    }

    printf("Using data points: ");

    /*for(int i=0; i<numOfPoints; i++){
        sp->data_points[i].temperature = sp->data_points[i].temperature;
        sp->data_points[i].hatch_time = sp->data_points[i].hatch_time;
    }*/


    return 0;
}

/*
double lagrange_eval(const Species *s, double x) {
    if (s->n == 0) return NAN;
    if (s->n == 1) return s->times[0]; // constant
    double result = 0.0;
    for (size_t i = 0; i < s->n; ++i) {
        double xi = s->temps[i];
        double yi = s->times[i];
        double Li = 1.0;
        for (size_t j = 0; j < s->n; ++j) {
            if (j == i) continue;
            double xj = s->temps[j];
            double denom = xi - xj;
            if (fabs(denom) < EPS) {
                // Duplicate x should have been prevented; fallback:
                denom = (denom >= 0 ? EPS : -EPS);
            }
            Li *= (x - xj) / denom;
        }
        result += yi * Li;
    }
    return result;
}*/