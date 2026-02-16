#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}


void generate_random(int a[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 1000;
    }
}


int Partition(int a[], int l, int h) {
    int pivot = a[l];
    int i = l;
    int j = h + 1;

    while (1) {
        do {
            i++;
        } while (i <= h && a[i] < pivot);

        do {
            j--;
        } while (a[j] > pivot);

        if (i >= j) break;
        swap(&a[i], &a[j]);
    }
    swap(&a[l], &a[j]);
    return j;
}


void Quicksort(int a[], int m, int n) {
    if (m < n) {
        int s = Partition(a, m, n);
        Quicksort(a, m, s - 1);
        Quicksort(a, s + 1, n);
    }
}

int main() {
    int a[100000], i, ch, n;
    struct timeval t;
    double start, end;
    FILE *fp;

    printf("Enter the type of operation:\n");
    printf("1 - Benchmark (10,000 to 100,000 elements)\n");
    printf("2 - Sort a specific number of values\n");
    scanf("%d", &ch);

    switch (ch) {
        case 1:
            fp = fopen("quicksort.txt", "w");
            if (fp == NULL) {
                printf("Error opening file!\n");
                return 1;
            }
            printf("Elements\tTime (seconds)\n");
            for (i = 10000; i <= 100000; i += 5000) {
                generate_random(a, i);

                gettimeofday(&t, NULL);
                start = t.tv_sec + (t.tv_usec / 1000000.0);

                Quicksort(a, 0, i - 1);

                gettimeofday(&t, NULL);
                end = t.tv_sec + (t.tv_usec / 1000000.0);

                printf("%d\t\t%lf\n", i, end - start);
                fprintf(fp, "%d\t%lf\n", i, end - start);
            }
            fclose(fp);
            break;

        case 2:
            printf("Enter the number of values to be generated: ");
            scanf("%d", &i);
            if (i > 100000) i = 100000; // Cap to array size

            generate_random(a, i);

            gettimeofday(&t, NULL);
            start = t.tv_sec + (t.tv_usec / 1000000.0);

            Quicksort(a, 0, i - 1);

            gettimeofday(&t, NULL);
            end = t.tv_sec + (t.tv_usec / 1000000.0);

            printf("\nSorted numbers are:\n");
            for (n = 0; n < i; n++) {
                printf("%d ", a[n]);
            }
            printf("\n\nTime taken: %lf seconds\n", end - start);
            break;

        default:
            printf("Invalid choice\n");
    }

    return 0;
}