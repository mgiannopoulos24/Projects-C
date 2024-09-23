#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEAMS 20
#define MAX_NAME_LEN 30

// Δομή που αναπαριστά μια ομάδα
typedef struct {
    char name[MAX_NAME_LEN];  // Όνομα ομάδας
    int points;               // Βαθμοί
    int goals_for;            // Γκολ υπέρ
    int goals_against;        // Γκολ κατά
} Team;

// Βρίσκει ή προσθέτει μια ομάδα στη λίστα
int find_or_add_team(Team teams[], int *team_count, const char *name) {
    for (int i = 0; i < *team_count; i++) {
        if (strcmp(teams[i].name, name) == 0) {
            return i;
        }
    }
    // Προσθήκη νέας ομάδας
    strcpy(teams[*team_count].name, name);
    teams[*team_count].points = 0;
    teams[*team_count].goals_for = 0;
    teams[*team_count].goals_against = 0;
    (*team_count)++;
    return *team_count - 1;
}

// Συνάρτηση σύγκρισης για την ταξινόμηση των ομάδων
int compare_teams(const void *a, const void *b) {
    Team *teamA = (Team *)a;
    Team *teamB = (Team *)b;
    
    // Σύγκριση βαθμών
    if (teamB->points != teamA->points) {
        return teamB->points - teamA->points;
    }
    
    // Σύγκριση διαφοράς γκολ
    int goal_diff_A = teamA->goals_for - teamA->goals_against;
    int goal_diff_B = teamB->goals_for - teamB->goals_against;
    return goal_diff_B - goal_diff_A;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", argv[1]);
        return 1;
    }

    Team teams[MAX_TEAMS];
    int team_count = 0;
    char line[100];

    // Ανάγνωση κάθε γραμμής από το αρχείο
    while (fgets(line, sizeof(line), file)) {
        char team1[MAX_NAME_LEN], team2[MAX_NAME_LEN];
        int goals1, goals2;

        // Ανάγνωση ονομάτων ομάδων και αποτελεσμάτων αγώνα
        if (sscanf(line, "%[^-]-%[^,],%d-%d", team1, team2, &goals1, &goals2) != 4) {
            printf("Error: Invalid file format\n");
            fclose(file);
            return 1;
        }

        // Βρες ή πρόσθεσε τις ομάδες στη λίστα
        int team1_idx = find_or_add_team(teams, &team_count, team1);
        int team2_idx = find_or_add_team(teams, &team_count, team2);

        // Ενημέρωση των γκολ
        teams[team1_idx].goals_for += goals1;
        teams[team1_idx].goals_against += goals2;
        teams[team2_idx].goals_for += goals2;
        teams[team2_idx].goals_against += goals1;

        // Ενημέρωση βαθμολογίας
        if (goals1 > goals2) {
            teams[team1_idx].points += 3;  // Νίκη για την ΟΜΑΔΑ1
        } else if (goals1 < goals2) {
            teams[team2_idx].points += 3;  // Νίκη για την ΟΜΑΔΑ2
        } else {
            teams[team1_idx].points += 1;  // Ισοπαλία
            teams[team2_idx].points += 1;  // Ισοπαλία
        }
    }

    fclose(file);

    // Ταξινόμηση των ομάδων με βάση τη βαθμολογία και τη διαφορά γκολ
    qsort(teams, team_count, sizeof(Team), compare_teams);

    // Εκτύπωση των ομάδων με τη βαθμολογία και τα γκολ
    for (int i = 0; i < team_count; i++) {
        printf("%s, %d, (%d - %d)\n", teams[i].name, teams[i].points, teams[i].goals_for, teams[i].goals_against);
    }

    return 0;
}

// Μεταγλώττιση:
// gcc league.c -o league
// Δοκιμές:
// ./league games.txt
