#include "NiceNumbers.h"
#include <malloc.h>
#include <stdio.h>

int NumbersCount(NiceNumberConf_pt conf)
{
    int count = 0;
    conf->xrange = conf->xmax - conf->xmin;
    double stepLogValue = floor(log10(conf->xrange));
    conf->step = pow(10.0, stepLogValue);
    if (conf->xrange / conf->step < 2.0) { conf->step /= 5.0; }
    else if (conf->xrange / conf->step < 5.0) { conf->step /= 2.0; }
    double x = conf->step * ceil(conf->xmin / conf->step);
    count++;
    int more_x = 1;
    do {
        x += conf->step;
        if (x <= conf->xmax)
        {
            count++;
        }
        else
        {
            more_x = 0;
        }
    } while (more_x);
    conf->count = count;
    return count;
}

double* Numbers(NiceNumberConf_pt conf)
{
    int count = NumbersCount(conf);
    double* numbers = (double*)calloc(count, sizeof(double));
    double x = conf->step * ceil(conf->xmin / conf->step);
    for (int index = 0; index < count; index++)
    {
        numbers[index] = x;
        x += conf->step;
    }
    return numbers;
}

int main()
{
    int ret = 0;
    do {
        NiceNumberConf_t conf = { -33, 105 };
        double* numbers = Numbers(&conf);
        for (int i = 0; i < conf.count; i++) 
        {
            printf("number[%d] = %f\n", i, numbers[i]);
        }
    } while (0);
    return ret;
}