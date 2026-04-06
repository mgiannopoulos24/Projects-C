#ifndef VOTING_H
#define VOTING_H

#define MAX_CANDIDATES 10
#define MAX_VOTERS 100
#define MAX_NAME_LEN 50
#define MAX_PASS_LEN 32
#define DATA_FILE "election.dat"

typedef enum {
    ELECTION_NOT_STARTED,
    ELECTION_RUNNING,
    ELECTION_ENDED
} ElectionState;

typedef struct {
    char name[MAX_NAME_LEN];
    int votes;
    int id;
} Candidate;

typedef struct {
    char name[MAX_NAME_LEN];
    char password[MAX_PASS_LEN];
    int id;
    int has_voted;
} Voter;

typedef struct {
    Candidate candidates[MAX_CANDIDATES];
    Voter voters[MAX_VOTERS];
    int candidate_count;
    int voter_count;
    ElectionState state;
} Election;

void init_election(Election *election);
int add_candidate(Election *election, const char *name);
int add_voter(Election *election, const char *name, const char *password);
int authenticate_voter(const Election *election, int voter_id, const char *password);
int cast_vote(Election *election, int voter_id, int candidate_id);
void display_results(const Election *election);
void print_candidates(const Election *election);
int save_election(const Election *election);
int load_election(Election *election);
int start_election(Election *election);
int end_election(Election *election);
void clear_input_buffer(void);
int read_line(char *buffer, int max_len);

#endif
