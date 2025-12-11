#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"

int sort_times(const void* a, const void* b) {
    float time1 = ((DataPoint*)a)->hatch_time;
    float time2 = ((DataPoint*)b)->hatch_time;
    if (time1 > time2)
        return 1;
    else if (time2 > time1)
        return -1;
    else
        return 0;
}

void time_calc(Species *sp, float temp, int numOfPoints, DataPoint *dataPoints){
    //EXTRACT NEAREST POINTS
    int polationMode; //0=inter, 1=min extrapolation, 2=max extrapolation
    
    if (temp < sp->data_points[0].temperature){
        polationMode = 1;
    }
    else if(temp > sp->data_points[sp->data_count-1].temperature){
        polationMode = 2;
    }
    else{
        polationMode=0;
    }

    
    int starting_i; 
    int i = 0;
    float absDistance[sp->data_count];
    int sortedIndex[sp->data_count];
    switch(polationMode){
        case 0:
            for(i=0; i<sp->data_count; i++){
                absDistance[i]=fabs(sp->data_points[i].temperature - temp); //Get absolute distance between temperature to find and 
            }

            for(i=0; i<sp->data_count; i++){
                sortedIndex[i]=i;           //initialize index values corresponding to data point index. to be sorted according to distance 
            }

            for(i=0; i<sp->data_count-1; i++){          //sort index according to ascending distance
                for(int j=i+1; j<sp->data_count; j++){
                    if(absDistance[sortedIndex[j]] < absDistance[sortedIndex[i]]){
                        int holder = sortedIndex[j];
                        sortedIndex[j] = sortedIndex[i];
                        sortedIndex[i] = holder;
                    }
                }
            }

            for(i=0; i<numOfPoints; i++){        //initialize dataPoints to be used in calculations with datapoints closest to temp to be checked
                dataPoints[i] = sp->data_points[sortedIndex[i]];
            }

            break;
        case 1:
            for(i=0; i<numOfPoints; i++){
                dataPoints[i] = sp->data_points[i];
            }
            break;
        case 2:
            starting_i = sp->data_count-numOfPoints;
            for(i=0; i < numOfPoints; i++){
                dataPoints[i] = sp->data_points[starting_i + i];
            }
            break;
    }
}

void temp_calc(Species *sp, float time, int numOfPoints, DataPoint *dataPoints){
    //datapointsinitial[] //copy of original data points but sort according to time
    DataPoint *dp_tempsorted = malloc(sizeof(DataPoint) * sp->data_count);
    for(int i=0; i<sp->data_count; i++){
        dp_tempsorted[i] = sp->data_points[i];
    }
    qsort(dp_tempsorted, sp->data_count, sizeof(DataPoint), sort_times); //sort data points in increasing order of time

    int polationMode; //0=inter, 1=min extrapolation, 2=max extrapolation
    
    if (time < dp_tempsorted[0].hatch_time){    //determine interpolation mode
        polationMode = 1;
    }
    else if(time > dp_tempsorted[sp->data_count-1].hatch_time){
        polationMode = 2;
    }
    else{
        polationMode=0;
    }
    
    int starting_i; 
    int i = 0;
    float absDistance[sp->data_count];
    int sortedIndex[sp->data_count];
    switch(polationMode){
        case 0:
            for(i=0; i<sp->data_count; i++){
                absDistance[i]=fabs(dp_tempsorted[i].hatch_time - time); //Get absolute distance between temperature to find and 
            }

            for(i=0; i<sp->data_count; i++){
                sortedIndex[i]=i;           //initialize index values corresponding to data point index. to be sorted according to distance 
            }

            for(i=0; i<sp->data_count-1; i++){          //sort index according to ascending distance
                for(int j=i+1; j<sp->data_count; j++){
                    if(absDistance[sortedIndex[j]] < absDistance[sortedIndex[i]]){
                        int holder = sortedIndex[j];
                        sortedIndex[j] = sortedIndex[i];
                        sortedIndex[i] = holder;
                    }
                }
            }

            for(i=0; i<numOfPoints; i++){        //initialize dataPoints to be used in calculations with datapoints closest to time to be checked
                dataPoints[i] = dp_tempsorted[sortedIndex[i]];
            }

            break;
        case 1:
            for(i=0; i<numOfPoints; i++){
                dataPoints[i] = dp_tempsorted[i];
            }
            break;
        case 2:
            starting_i = sp->data_count-numOfPoints;
            for(i=0; i < numOfPoints; i++){
                dataPoints[i] = dp_tempsorted[starting_i + i];
            }
            break;
    }

    free(dp_tempsorted);
}

float li(DataPoint *dataPoints, int numOfPoints, float unknown, int i, int mode){
    float product=1;
    float term;

    switch(mode){
        case 1:
            for(int j=0; j<numOfPoints; j++){
                if(i!=j){
                    term = (unknown - dataPoints[j].temperature)/(dataPoints[i].temperature - dataPoints[j].temperature);
                    product *= term;
                }
            }
            break;
        case 2:
            for(int j=0; j<numOfPoints; j++){
                if(i!=j){
                    term = (unknown - dataPoints[j].hatch_time)/(dataPoints[i].hatch_time - dataPoints[j].hatch_time);
                    product *= term;
                }
            }
            break;
    }
    
    return product;
}

float lagrange_calc(Species *sp, float unknown_x, int mode){ //unknwon = either temp or time      mode 1 = given temp get time        mode 2 = given time get temp
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
    
    float value;
    DataPoint *dataPoints = malloc(sizeof(DataPoint) * numOfPoints);
    float y[numOfPoints];
    switch(mode){
        case 1:
            time_calc(sp, unknown_x, numOfPoints, dataPoints);
            break;
        case 2:
            temp_calc(sp, unknown_x, numOfPoints, dataPoints);
            break;
    }

    printf("\n\n--------DATA POINTS TO BE USED--------\n");
    for(int i=0; i<numOfPoints; i++){
        if(mode==1)
            printf("x(i) = %.2f, y(i) = %.2f\n", dataPoints[i].temperature, dataPoints[i].hatch_time);
        else
            printf("x(i) = %.2f, y(i) = %.2f\n", dataPoints[i].hatch_time, dataPoints[i].temperature);
    }
    printf("--------------------------------------\n");
    //Get y values for each data point
    for(int i=0; i<numOfPoints; i++){ 
        if(mode==1)
            y[i] = dataPoints[i].hatch_time;
        else
            y[i] = dataPoints[i].temperature;
    }

    //Get Li(x) for each data point
    float lix[numOfPoints];
    printf("\n");
    for(int i=0; i<numOfPoints; i++){
        lix[i] = li(dataPoints, numOfPoints, unknown_x, i, mode); 
        printf("L%d(x) = %.2f \n", i, lix[i]);
    }
    
    //Display and calculate each term of the lagrange polynomial
    float term[numOfPoints];
    printf("\nf(x) = ");
    for(int i=0; i<numOfPoints; i++){
        printf(" (%.2f)(%.2f) +", lix[i], y[i]);
        term[i] = lix[i]*y[i];
    }
    printf("\b \n");

    //Display and calculate the final lagrange polynomial
    float fx = 0;
    printf("\nf(x) = ");
    for(int i=0; i<numOfPoints; i++){
        printf(" %.2f +", term[i]);
        fx += term[i];
    }
    printf("\b \n");
    
    return fx;
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
}
    
void selectNearestPoints(Species *sp, float temp, int numOfPoints, DataPoint *outPoints) {
    int n = sp->data_count;

    if (numOfPoints >= n) {
        // use all points
        for (int i = 0; i < n; i++)
            outPoints[i] = sp->data_points[i];
        return;
    }

    // find position where temp would fit
    int pos = 0;
    while (pos < n && sp->data_points[pos].temperature < temp) pos++;

    int left = pos - 1;
    int right = pos;
    int count = 0;

    // pick points alternately left and right until numOfPoints selected
    while (count < numOfPoints) {
        if (left < 0) {
            outPoints[count++] = sp->data_points[right++];
        } else if (right >= n) {
            outPoints[count++] = sp->data_points[left--];
        } else {
            float dl = fabs(temp - sp->data_points[left].temperature);
            float dr = fabs(sp->data_points[right].temperature - temp);
            if (dl <= dr) outPoints[count++] = sp->data_points[left--];
            else outPoints[count++] = sp->data_points[right++];
        }
    }

    // sort selected points by temperature ascending for Lagrange
    for (int i = 1; i < numOfPoints; i++) {
        DataPoint key = outPoints[i];
        int j = i - 1;
        while (j >= 0 && outPoints[j].temperature > key.temperature) {
            outPoints[j + 1] = outPoints[j];
            j--;
        }
        outPoints[j + 1] = key;
    }
}

*/