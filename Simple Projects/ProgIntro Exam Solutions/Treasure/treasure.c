#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[]) {
    // Έλεγχος αν υπάρχουν αρκετά ορίσματα
    if (argc < 3) {
        fprintf(stderr, "Usage: %s goal_x,goal_y point1_x,point1_y [point2_x,point2_y ...]\n", argv[0]);
        return 1;
    }

    // Παρσάρισμα του στόχου
    double goal_x, goal_y;
    if (sscanf(argv[1], "%lf,%lf", &goal_x, &goal_y) != 2) {
        fprintf(stderr, "Error: Invalid goal coordinate '%s'\n", argv[1]);
        return 1;
    }

    // Αποθήκευση των σημείων και των αποστάσεών τους
    int num_points = argc - 2;
    double *points_x = malloc(num_points * sizeof(double));
    double *points_y = malloc(num_points * sizeof(double));
    double *distances = malloc(num_points * sizeof(double));
    if (!points_x || !points_y || !distances) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 1;
    }

    // Παρσάρισμα και υπολογισμός αποστάσεων
    for (int i = 0; i < num_points; i++) {
        double x, y;
        if (sscanf(argv[i + 2], "%lf,%lf", &x, &y) != 2) {
            fprintf(stderr, "Error: Invalid coordinate '%s'\n", argv[i + 2]);
            free(points_x);
            free(points_y);
            free(distances);
            return 1;
        }
        points_x[i] = x;
        points_y[i] = y;
        double dx = x - goal_x;
        double dy = y - goal_y;
        distances[i] = sqrt(dx * dx + dy * dy);
    }

    // Δημιουργία πίνακα για την ταξινόμηση
    int *indices = malloc(num_points * sizeof(int));
    if (!indices) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        free(points_x);
        free(points_y);
        free(distances);
        return 1;
    }
    for (int i = 0; i < num_points; i++) {
        indices[i] = i;
    }

    // Ταξινόμηση με βάση τις αποστάσεις (Selection Sort)
    for (int i = 0; i < num_points - 1; i++) {
        for (int j = i + 1; j < num_points; j++) {
            if (distances[indices[i]] > distances[indices[j]]) {
                // Ανταλλαγή των δεικτών
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    // Εκτύπωση των αποτελεσμάτων
    for (int i = 0; i < num_points; i++) {
        int idx = indices[i];
        printf("%d. Point %.2f,%.2f is %.2f steps away from the goal\n",
               i + 1, points_x[idx], points_y[idx], distances[idx]);
    }

    // Απελευθέρωση μνήμης
    free(points_x);
    free(points_y);
    free(distances);
    free(indices);

    return 0;
}

// Μεταγλώττιση: 
// gcc treasure.c -o treasure -lm
// Εκτέλεση:
// ./treasure 17,42 3.01,50.5 27.27,7 32,65.1 25,4 77,42.42 50,50 30.30,12