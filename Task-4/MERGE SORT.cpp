#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

void simplemerge(int a[], int low, int mid, int high) {
    int i, j, k, c[10000];
    i = low;
    j = mid + 1;
    k = low;

    while (i <= mid && j <= high) {
        if (a[i] < a[j]) {
            c[k] = a[i];
            i++;
        } else {
            c[k] = a[j];
            j++;
        }
        k++;
    }

    while (i <= mid) {
        c[k++] = a[i++];
    }

    while (j <= high) {
        c[k++] = a[j++];
    }

    for (k = low; k <= high; k++) {
        a[k] = c[k];
    }
}

void merge(int a[], int low, int high) {
    int mid;
    if (low < high) {
        mid = (low + high) / 2;

        
        #pragma omp parallel sections
        {
            #pragma omp section
            merge(a, low, mid);
            
            #pragma omp section
            merge(a, mid + 1, high);
        }

        simplemerge(a, low, mid, high);
    }
}

void getnumber(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 10000;
    }
}

int main() {
    FILE *fp;
    int a[10000], i;
    struct timeval tv;
    double start, end, elapse;

    fp = fopen("m.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("Num\tTime\n");

    for (i = 100; i < 10000; i += 100) {
        getnumber(a, i);

        gettimeofday(&tv, NULL);
        start = tv.tv_sec + (tv.tv_usec / 1000000.0);

        merge(a, 0, i - 1);

        gettimeofday(&tv, NULL);
        end = tv.tv_sec + (tv.tv_usec / 1000000.0);

        elapse = end - start;

        if (elapse >= 0) {
            fprintf(fp, "%d\t%lf\n", i, elapse);
            printf("%d\t%lf\n", i, elapse);
        }
    }

    fclose(fp);
    printf("Data written to m.txt. You can now use gnuplot to plot the results.\n");

    return 0;
}