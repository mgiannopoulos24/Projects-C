#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voting.h"

static const char *state_to_string(ElectionState state) {
    switch (state) {
        case ELECTION_NOT_STARTED: return "Not Started";
        case ELECTION_RUNNING:     return "Running";
        case ELECTION_ENDED:       return "Ended";
        default:                   return "Unknown";
    }
}

static int read_int(const char *prompt) {
    int value;
    char line[64];

    printf("%s", prompt);
    if (read_line(line, sizeof(line)) != 0) {
        return -1;
    }

    if (sscanf(line, "%d", &value) != 1) {
        return -1;
    }

    return value;
}

int main(void) {
    Election election;
    init_election(&election);

    load_election(&election);

    int running = 1;

    printf("=== Online Voting System ===\n\n");

    while (running) {
        printf("State: %s\n", state_to_string(election.state));
        printf("1. Add Candidate\n");
        printf("2. Add Voter\n");
        printf("3. Start Election\n");
        printf("4. Cast Vote\n");
        printf("5. End Election\n");
        printf("6. View Candidates\n");
        printf("7. View Results\n");
        printf("8. Save Election\n");
        printf("9. Reset Election\n");
        printf("10. Exit\n");

        int choice = read_int("Enter choice: ");
        if (choice < 0) {
            printf("Invalid input.\n\n");
            continue;
        }

        switch (choice) {
            case 1: {
                char name[MAX_NAME_LEN];
                printf("Enter candidate name: ");
                if (read_line(name, sizeof(name)) != 0 || strlen(name) == 0) {
                    printf("Invalid name.\n\n");
                    break;
                }
                add_candidate(&election, name);
                break;
            }
            case 2: {
                char name[MAX_NAME_LEN];
                char password[MAX_PASS_LEN];
                printf("Enter voter name: ");
                if (read_line(name, sizeof(name)) != 0 || strlen(name) == 0) {
                    printf("Invalid name.\n\n");
                    break;
                }
                printf("Enter password: ");
                if (read_line(password, sizeof(password)) != 0 || strlen(password) == 0) {
                    printf("Invalid password.\n\n");
                    break;
                }
                add_voter(&election, name, password);
                break;
            }
            case 3:
                start_election(&election);
                break;
            case 4: {
                if (election.state != ELECTION_RUNNING) {
                    printf("Error: Election is not running.\n\n");
                    break;
                }

                int voter_id = read_int("Enter voter ID: ");
                if (voter_id < 0) {
                    printf("Invalid input.\n\n");
                    break;
                }

                char password[MAX_PASS_LEN];
                printf("Enter password: ");
                if (read_line(password, sizeof(password)) != 0) {
                    printf("Invalid input.\n\n");
                    break;
                }

                if (!authenticate_voter(&election, voter_id, password)) {
                    printf("Error: Authentication failed.\n\n");
                    break;
                }

                print_candidates(&election);
                int candidate_id = read_int("Enter candidate ID: ");
                if (candidate_id < 0) {
                    printf("Invalid input.\n\n");
                    break;
                }
                cast_vote(&election, voter_id, candidate_id);
                break;
            }
            case 5:
                end_election(&election);
                break;
            case 6:
                print_candidates(&election);
                break;
            case 7:
                display_results(&election);
                break;
            case 8:
                save_election(&election);
                break;
            case 9: {
                char confirm[4];
                printf("Are you sure? This will delete all data (yes/no): ");
                if (read_line(confirm, sizeof(confirm)) == 0 && strcmp(confirm, "yes") == 0) {
                    init_election(&election);
                    printf("Election reset.\n\n");
                } else {
                    printf("Reset cancelled.\n\n");
                }
                break;
            }
            case 10: {
                char confirm[4];
                printf("Save before exit? (yes/no): ");
                if (read_line(confirm, sizeof(confirm)) == 0 && strcmp(confirm, "yes") == 0) {
                    save_election(&election);
                }
                running = 0;
                printf("Exiting. Goodbye!\n");
                break;
            }
            default:
                printf("Invalid choice.\n\n");
                break;
        }
    }

    return 0;
}
