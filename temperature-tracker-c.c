#include <stdio.h>

int main(void) {
    const int MAX_CAPACITY = 50;   // fixed-size array (per brief)
    double temps[50];              // stores up to 50 readings
    int daysRequested;             // user target days (1..30)
    int count = 0;                 // actual number stored (may stop early with -1)

    // --- Input phase (with -1 sentinel to finish early) ---
    printf("How many days do you want to record? (1-30): ");
    if (scanf("%d", &daysRequested) != 1 || daysRequested < 1 || daysRequested > 30) {
        printf("Invalid number of days.\n");
        return 1;
    }

    for (int i = 0; i < daysRequested && count < MAX_CAPACITY; i++) {
        double t;
        printf("Enter temperature for day %d (C) or -1 to finish early: ", i + 1);
        if (scanf("%lf", &t) != 1) { printf("Invalid input.\n"); return 1; }
        if (t == -1.0) break;      // sentinel to stop early
        temps[count++] = t;
    }

    // --- Menu loop (full set: 1..6 + 7=Exit) ---
    while (1) {
        int choice;
        printf("\nMenu\n");
        printf("1. Display all temperature readings\n");
        printf("2. Calculate and display the average temperature\n");
        printf("3. Find and display the highest and lowest temperature\n");
        printf("4. Count days above and below a threshold\n");
        printf("5. Weekly average temperature (every 7 days)\n");
        printf("6. Reverse the order and display as Today/Yesterday/...\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) { printf("Invalid input.\n"); return 1; }

        if (choice == 1) {
            // Display all (pointer traversal)
            if (count == 0) {
                printf("\nNo readings recorded.\n");
            } else {
                printf("\nAll temperature readings (%d):\n", count);
                double *p = temps;                 // points to first reading
                for (int i = 0; i < count; i++, p++) {
                    printf("Day %2d: %.2f C\n", i + 1, *p);
                }
            }

        } else if (choice == 2) {
            // Average (pointer sum)
            if (count == 0) {
                printf("\nNo readings to average.\n");
            } else {
                double sum = 0.0;
                for (double *p = temps; p < temps + count; p++) sum += *p;
                printf("\nAverage over %d day(s): %.2f C\n", count, sum / count);
            }

        } else if (choice == 3) {
            // Highest & lowest (pointer-based search)
            if (count == 0) {
                printf("\nNo readings to analyze.\n");
            } else {
                double *p = temps;
                double min = *p, max = *p;
                int minIdx = 0, maxIdx = 0;
                p++; // start from second element
                for (int i = 1; i < count; i++, p++) {
                    if (*p < min) { min = *p; minIdx = i; }
                    if (*p > max) { max = *p; maxIdx = i; }
                }
                printf("\nLowest temperature:  %.2f C (Day %d)\n", min, minIdx + 1);
                printf("Highest temperature: %.2f C (Day %d)\n", max, maxIdx + 1);
            }

        } else if (choice == 4) {
            // Threshold counts (pointer traversal)
            if (count == 0) {
                printf("\nNo readings to analyze.\n");
            } else {
                double threshold;
                printf("Enter threshold (C): ");
                if (scanf("%lf", &threshold) != 1) { printf("Invalid input.\n"); return 1; }

                int above = 0, below = 0;
                for (double *p = temps; p < temps + count; p++) {
                    if (*p > threshold) above++;
                    else if (*p < threshold) below++;
                }
                printf("\nDays above %.2f C: %d\n", threshold, above);
                printf("Days below %.2f C: %d\n", threshold, below);
            }

        } else if (choice == 5) {
            // Weekly averages (blocks of 7; last partial week averaged as-is)
            if (count == 0) {
                printf("\nNo readings to analyze.\n");
            } else {
                int week = 1;
                int i = 0;
                printf("\nWeekly averages:\n");
                while (i < count) {
                    int block = (count - i >= 7) ? 7 : (count - i);
                    double sum = 0.0;
                    double *q = temps + i;                 // start of block
                    for (int j = 0; j < block; j++, q++) sum += *q;
                    printf("Week %d (days %d-%d): avg = %.2f C\n",
                           week, i + 1, i + block, sum / block);
                    i += block;
                    week++;
                }
            }

        } else if (choice == 6) {
            // Reverse in-place using two pointers, then display as Today/Yesterday/...
            if (count == 0) {
                printf("\nNo readings to reverse.\n");
            } else {
                double *left = temps;
                double *right = temps + count - 1;
                while (left < right) {
                    double tmp = *left;
                    *left = *right;
                    *right = tmp;
                    left++; right--;
                }

                printf("\nReversed order (most recent first):\n");
                double *p = temps;
                for (int i = 0; i < count; i++, p++) {
                    if (i == 0)       printf("Today: %.0fC\n", *p);
                    else if (i == 1)  printf("Yesterday: %.0fC\n", *p);
                    else              printf("%d days ago: %.0fC\n", i, *p);
                }
            }

        } else if (choice == 7) {
            printf("Goodbye!\n");
            break;

        } else {
            printf("Invalid choice. Please select 1, 2, 3, 4, 5, 6, or 7.\n");
        }
    }

    return 0;
}