#include <stdio.h>
#include <string.h>
#include "voting.h"

void init_election(Election *election) {
    election->candidate_count = 0;
    election->voter_count = 0;
    election->state = ELECTION_NOT_STARTED;
    memset(election->candidates, 0, sizeof(election->candidates));
    memset(election->voters, 0, sizeof(election->voters));
}

int add_candidate(Election *election, const char *name) {
    if (election->state == ELECTION_RUNNING) {
        printf("Error: Cannot add candidates while election is running.\n");
        return -1;
    }

    if (election->state == ELECTION_ENDED) {
        printf("Error: Election has ended. Reset to add candidates.\n");
        return -1;
    }

    if (election->candidate_count >= MAX_CANDIDATES) {
        printf("Error: Maximum number of candidates reached.\n");
        return -1;
    }

    if (strlen(name) == 0) {
        printf("Error: Candidate name cannot be empty.\n");
        return -1;
    }

    for (int i = 0; i < election->candidate_count; i++) {
        if (strcmp(election->candidates[i].name, name) == 0) {
            printf("Error: Candidate '%s' already exists.\n", name);
            return -1;
        }
    }

    Candidate *c = &election->candidates[election->candidate_count];
    strncpy(c->name, name, MAX_NAME_LEN - 1);
    c->name[MAX_NAME_LEN - 1] = '\0';
    c->votes = 0;
    c->id = election->candidate_count + 1;
    election->candidate_count++;

    printf("Candidate '%s' added with ID %d.\n", name, c->id);
    return c->id;
}

int add_voter(Election *election, const char *name, const char *password) {
    if (election->state == ELECTION_RUNNING) {
        printf("Error: Cannot add voters while election is running.\n");
        return -1;
    }

    if (election->state == ELECTION_ENDED) {
        printf("Error: Election has ended. Reset to add voters.\n");
        return -1;
    }

    if (election->voter_count >= MAX_VOTERS) {
        printf("Error: Maximum number of voters reached.\n");
        return -1;
    }

    if (strlen(name) == 0) {
        printf("Error: Voter name cannot be empty.\n");
        return -1;
    }

    if (strlen(password) == 0) {
        printf("Error: Password cannot be empty.\n");
        return -1;
    }

    if (strlen(password) > MAX_PASS_LEN - 1) {
        printf("Error: Password too long (max %d characters).\n", MAX_PASS_LEN - 1);
        return -1;
    }

    for (int i = 0; i < election->voter_count; i++) {
        if (strcmp(election->voters[i].name, name) == 0) {
            printf("Error: Voter '%s' already exists.\n", name);
            return -1;
        }
    }

    Voter *v = &election->voters[election->voter_count];
    strncpy(v->name, name, MAX_NAME_LEN - 1);
    v->name[MAX_NAME_LEN - 1] = '\0';
    strncpy(v->password, password, MAX_PASS_LEN - 1);
    v->password[MAX_PASS_LEN - 1] = '\0';
    v->id = election->voter_count + 1;
    v->has_voted = 0;
    election->voter_count++;

    printf("Voter '%s' added with ID %d.\n", name, v->id);
    return v->id;
}

int authenticate_voter(const Election *election, int voter_id, const char *password) {
    if (voter_id < 1 || voter_id > election->voter_count) {
        return 0;
    }

    const Voter *v = &election->voters[voter_id - 1];
    return strcmp(v->password, password) == 0;
}

int cast_vote(Election *election, int voter_id, int candidate_id) {
    if (election->state != ELECTION_RUNNING) {
        printf("Error: Election is not running.\n");
        return -1;
    }

    if (voter_id < 1 || voter_id > election->voter_count) {
        printf("Error: Invalid voter ID.\n");
        return -1;
    }

    if (candidate_id < 1 || candidate_id > election->candidate_count) {
        printf("Error: Invalid candidate ID.\n");
        return -1;
    }

    Voter *v = &election->voters[voter_id - 1];
    if (v->has_voted) {
        printf("Error: Voter '%s' has already voted.\n", v->name);
        return -1;
    }

    v->has_voted = 1;
    election->candidates[candidate_id - 1].votes++;

    printf("Vote cast successfully: '%s' voted for '%s'.\n", v->name, election->candidates[candidate_id - 1].name);
    return 0;
}

void print_candidates(const Election *election) {
    printf("\n--- Candidates ---\n");
    if (election->candidate_count == 0) {
        printf("No candidates registered.\n");
    } else {
        for (int i = 0; i < election->candidate_count; i++) {
            printf("ID: %d | Name: %s\n", election->candidates[i].id, election->candidates[i].name);
        }
    }
    printf("------------------\n\n");
}

void display_results(const Election *election) {
    printf("\n=== Election Results ===\n");

    if (election->candidate_count == 0) {
        printf("No candidates in this election.\n");
        printf("========================\n\n");
        return;
    }

    int max_votes = -1;
    int winner_count = 0;
    int winner_indices[MAX_CANDIDATES];

    for (int i = 0; i < election->candidate_count; i++) {
        printf("Candidate: %-20s | Votes: %d\n", election->candidates[i].name, election->candidates[i].votes);

        if (election->candidates[i].votes > max_votes) {
            max_votes = election->candidates[i].votes;
            winner_count = 0;
            winner_indices[winner_count++] = i;
        } else if (election->candidates[i].votes == max_votes && max_votes > 0) {
            winner_indices[winner_count++] = i;
        }
    }

    printf("\nTotal voters: %d | Voted: ", election->voter_count);
    int voted_count = 0;
    for (int i = 0; i < election->voter_count; i++) {
        if (election->voters[i].has_voted) voted_count++;
    }
    printf("%d | Remaining: %d\n", voted_count, election->voter_count - voted_count);

    if (winner_count == 1 && max_votes > 0) {
        printf("\nWinner: %s with %d votes!\n", election->candidates[winner_indices[0]].name, max_votes);
    } else if (winner_count > 1 && max_votes > 0) {
        printf("\nTie between: ");
        for (int i = 0; i < winner_count; i++) {
            printf("%s", election->candidates[winner_indices[i]].name);
            if (i < winner_count - 1) printf(", ");
        }
        printf(" with %d votes each!\n", max_votes);
    } else {
        printf("\nNo votes were cast.\n");
    }

    printf("========================\n\n");
}

int save_election(const Election *election) {
    FILE *fp = fopen(DATA_FILE, "wb");
    if (!fp) {
        printf("Error: Could not open file for saving.\n");
        return -1;
    }

    fwrite(election, sizeof(Election), 1, fp);
    fclose(fp);

    printf("Election data saved to %s.\n", DATA_FILE);
    return 0;
}

int load_election(Election *election) {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (!fp) {
        printf("No saved election data found.\n");
        return -1;
    }

    if (fread(election, sizeof(Election), 1, fp) != 1) {
        printf("Error: Could not read election data.\n");
        fclose(fp);
        return -1;
    }

    fclose(fp);
    printf("Election data loaded from %s.\n", DATA_FILE);
    return 0;
}

int start_election(Election *election) {
    if (election->state == ELECTION_RUNNING) {
        printf("Error: Election is already running.\n");
        return -1;
    }

    if (election->candidate_count < 2) {
        printf("Error: Need at least 2 candidates to start an election.\n");
        return -1;
    }

    if (election->voter_count == 0) {
        printf("Error: Need at least 1 voter to start an election.\n");
        return -1;
    }

    election->state = ELECTION_RUNNING;
    printf("Election started! Voting is now open.\n");
    return 0;
}

int end_election(Election *election) {
    if (election->state != ELECTION_RUNNING) {
        printf("Error: Election is not running.\n");
        return -1;
    }

    election->state = ELECTION_ENDED;
    printf("Election ended. Results are final.\n");
    return 0;
}

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int read_line(char *buffer, int max_len) {
    if (!fgets(buffer, max_len, stdin)) {
        return -1;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        clear_input_buffer();
    }

    return 0;
}
