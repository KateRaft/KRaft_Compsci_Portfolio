#include <library>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
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

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
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

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
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
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Compare name given to candidates listed, if candidate exists increase their vote by one
        if (strcmp(candidates[i].name, name) == true)
        {
            // from (preferences[i][j] is jth preference for voter i)
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}


// Tabulate votes for non-eliminated candidates
// preferences array --> preferences[i][j] --> preferences[voter][rank] aka 'j'th preference for voter 'i'

void tabulate(void)
{
    for (int i = 0; i < voter_count; i ++)
    {
        for (int j = 0; j < candidate_count; j ++)
        {
            //for voter i, candidate choice j is increased if its less than the total number of candidates
            // if candidate from array of candidates who are preferred by voters is not eliminated in this round then increase vote count for candidate
            if (candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes += 1;
                // Terminate loop
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // if any candidate has more than half the vote ( > 50 votes because MAX CANDIDATES is 100...note: doesnt include 50), their name should be printed to stdout and the function should return true
    // If nobody has won election yet function should return false to main
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > 50)
        {
            printf("%s/n",candidates[i].name);
            return true;
        }
    }
// No winner so function shouldnt print out anything and return false to main
    return false;
}

// Return the minimum number of votes any remaining candidate has
// Use to figure out who we need to eliminate in runoff process (person with least amount of votes currently)
int find_min(void)
{
    // Loop through candidates list to find one that is still in election (NOT eliminated) AND and has fewest number of votes

    int min = MAX_VOTERS;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes <= min)
        {
            min = candidates[i].votes;
        }
    }
    // Function should RETURN minimum total value therefore return min amount
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Take min result from find_min function and return true if every candidate REMAINING (bool elimination == false) in election has same number of votes
    // Therefore false is returned if a candidate's number of votes is not equal to the minimum because then a tie cannot exist
    for (int i = 0; i < candidate_count; i ++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes != min)
        {
            return false;
        }
    }
    // Otherwise return true to main
    return true;
}

// Eliminate the candidate (or candidates) in last place
// Take min result from find_min and eliminate candidate who has that certain number of votes stored in find_min (the least number of votes)
void eliminate(int min)
{
    // Iterate through REMAINING candidates whose votes = min
    for (int i = 0; i < candidate_count; i ++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
