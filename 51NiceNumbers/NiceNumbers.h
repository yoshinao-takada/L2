#if !defined(NICENUMBERS_H)
#define NICENUMBERS_H
#include <math.h>

typedef struct {
    double xmin, xmax, xrange, step;
    int count;
} NiceNumberConf_t, *NiceNumberConf_pt;

double* Numbers(NiceNumberConf_pt conf);
#endif
