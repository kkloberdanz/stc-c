#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#define MAX(A, B) ((A) > (B)) ? (A) : (B)
#define MIN(A, B) ((A) < (B)) ? (A) : (B)

static void conversion_error(const char * const line) {
    fprintf(
        stderr,
        "failed to convert '%s' to a number, ignoring future warnings.\n",
        line
    );
}

int main(void) {
    char *line = NULL;
    size_t zero = 0;
    size_t lines = 0;
    double sum = 0.0;
    double max = 0.0;
    double min = 0.0;
    int first_time = 1;
    int first_conversion_warning = 1;
    ssize_t nread = 0;

    while ((nread = getline(&line, &zero, stdin)) != -1) {
        double as_double;
        char *end = NULL;

        as_double = strtod(line, &end);
        if (end == line) {
            /* ignore non-numerical lines */
            if (first_conversion_warning) {
                if (nread > 1) {
                    line[nread - 1] = '\0';
                }
                conversion_error(line);
                first_conversion_warning = 0;
            }
        } else {
            lines++;

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
        const double mean = sum / lines;
        const double epsilon = 0.000001;
        const char * const fmt_string =
            ((mean < epsilon) || (min < epsilon) || (max < epsilon))
            ? "lines: %lu sum: %g mean: %g max: %g min: %g\n"
            : "lines: %lu sum: %f mean: %f max: %f min: %f\n"
            ;

        printf(
            fmt_string,
            lines,
            sum,
            mean,
            max,
            min
        );
    } else {
        fprintf(stderr, "no lines in input\n");
    }
    free(line);
    return 0;
}
