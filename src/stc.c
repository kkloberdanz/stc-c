#include <stdio.h>
#include <stdlib.h>

#define MAX(A, B) ((A) > (B)) ? (A) : (B)
#define MIN(A, B) ((A) < (B)) ? (A) : (B)

int main(void) {
    char *line = NULL;
    size_t zero = 0;
    size_t lines = 0;
    double sum = 0.0;
    double max;
    double min;
    int first_time = 1;
    ssize_t nread = 0;

    while ((nread = getline(&line, &zero, stdin)) != -1) {
        double as_double;
        char *end = NULL;

        lines++;

        as_double = strtod(line, &end);
        if (end == line) {
            /* ignore non-numerical lines */
        } else {
            if (first_time) {
                first_time = 0;
                max = as_double;
                min = as_double;
            }
            sum += as_double;
            max = MAX(max, as_double);
            min = MIN(min, as_double);
        }
    }
    if (lines > 0) {
        printf(
            "lines: %lu sum: %f mean: %f max: %f min: %f\n",
            lines,
            sum,
            sum / lines,
            max,
            min
        );
    } else {
        fprintf(stderr, "no lines in input\n");
    }
    free(line);
    return 0;
}
