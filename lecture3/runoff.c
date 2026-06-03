#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
// 각 투표자의 선호도를 반영한다.
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
// 후보자 배열
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);
void populate_preferences(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [Type in candidate ...]\n");
        return 1;
    }else if(argc==2)
    {
        printf("Type in more than one candidate \n");
        return 1;
    }

    // A) 각 후보자 기준, preferences의 순위를 초기화해준다.
    populate_preferences();

    // B) Populate array of candidates
    // 후보자 초기화.
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // C) Keep querying for votes
    // 각 투표자의 선호도 반영.
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        // 각 투표자의 후보자에 대한 선호도 반영.
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalidㄴ
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // D) Keep holding runoffs until winner exists
    // 승리하는 사람이 나올 때까지, 
    // runoff를 진행한다. 
    // runoff를 진행 - tie가 나온다면 탈락한 표에서 다음 선호도 확인하기
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            printf("TIE\n");
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        // 가장 높은 선호도를 반영한 투표를 다시 하기 위해서, 
        // candidates 배열을 초기화한다.
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Ranked choice voting system
// Voters can vote for more than one candidate
// rank the candidates in order of preference
// vote for 1~3 preference


// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    // 1.candidate 배열에 1순위 기준 선호도 반영.
    // 2.preference 배열에 rank 기준 선호도 반영.
    for(int i=0; i<candidate_count; i++){
        if(strcmp(candidates[i].name, name) == 0){
            preferences[voter][i] = rank;
            return true;
        }
    }
    return false;
}


// Tabulate votes for non-eliminated candidates
// 제거되지 않는 후보자에 대한 표 집계(tabulate)
void tabulate(void)
{
    // TODO
    // 가장 선호도가 높은 후보한테 투표를 한다.
    for(int i=0; i<voter_count; i++){
        int highestrank = MAX_CANDIDATES+1;
        int candNum = -1;
        for(int j=0; j<candidate_count; j++){
            int pref = preferences[i][j];
            bool eliminated = candidates[j].eliminated;
            
            // 후보자가 아직 남아 있으면 선호도 갱신
            if(!eliminated && (highestrank > pref)) {
                highestrank = pref;
                candNum = j;
            }
        }

        // 가장 높은 선호도의 후보자에게 투표.
        candidates[candNum].votes += 1; 
    }
    return;
}

// Print the winner of the election, if there is one
// 현재 살아 있는 후보자 중에서 과반 이상을 차지하는 후보자가 있다면, 
// 뽑힌 사람을 출력한다.
bool print_winner(void)
{
    // TODO
    int maxcount = -1;
    int winner = -1;
    for(int i=0; i<candidate_count; i++)
    {
        // 후보자가 남아 있고 표가 더 많다면,
        // maxcount를 갱신한다.
        bool eliminated = candidates[i].eliminated;
        if(!eliminated && (maxcount < candidates[i].votes))
        {
            maxcount = candidates[i].votes;
            winner = i;
        }
    }

    // 과반이 넘었을 때 선출된 사람을 출력한다.
    double percent = (double) maxcount/voter_count;
    if(percent > 0.5){
        char *s = candidates[winner].name;

        printf("Winner: %s\n", s);
        return true;
    }
    
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int minvotes = MAX_VOTERS+1;

    for(int i=0; i<candidate_count; i++)
    {
        bool eliminated = candidates[i].eliminated;

        if(!eliminated){
            int votes = candidates[i].votes;
            if(minvotes>votes) minvotes = votes;        
        }

    }

    return minvotes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    // 남아 있는 후보 간 득표가 min으로 똑같다면, tie를 출력한다.
    bool tie = true;
    for(int i=0; i<candidate_count; i++){
        bool eliminated = candidates[i].eliminated;
        if(!eliminated)
        {
            int votes = candidates[i].votes;
            if(votes!=min) {
                tie = false;
                return tie;
            };
        }
    }

    return tie;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    // 가장 득표 수가 적은 후보를 eliminated 처리를 한다.
    for(int i=0; i<candidate_count; i++){
        int votes = candidates[i].votes;
        
        if(votes == min){
            candidates[i].eliminated = true;
        }
    }

    return;
}

// Rank 기준으로 preferences를 초기화해준다.
void populate_preferences(void)
{
    for (int i = 0; i < MAX_VOTERS; i++)
    {
        for (int j = 0; j < MAX_CANDIDATES; j++)
        {
            preferences[i][j] = MAX_CANDIDATES + 1;
        }
    }

}
