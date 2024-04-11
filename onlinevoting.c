#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

typedef struct Candidate {
    char name[50];
    int votes;
} Candidate;

void initializeCandidate(Candidate *candidate, const char *name) {
    strcpy(candidate->name, name);
    candidate->votes = 0;
}

void voteForCandidate(Candidate *candidates, int numCandidates, int candidateNumber) {
    printf("\nBefore Vote:\n");
    for (int i = 0; i < numCandidates; i++) {
        printf("%d. %s: %d votes\n", i + 1, candidates[i].name, candidates[i].votes);
    }

    if (candidateNumber >= 1 && candidateNumber <= numCandidates) {
        candidates[candidateNumber - 1].votes++;
        printf("Your vote for %s has been recorded.\n", candidates[candidateNumber - 1].name);
        printf("\nAfter Vote:\n");
        for (int j = 0; j < numCandidates; j++) {
            printf("%d. %s: %d votes\n", j + 1, candidates[j].name, candidates[j].votes);
        }
#ifdef _WIN32
        Beep(1000, 300);
#else
        printf("\a");
#endif
    } else {
        printf("Invalid candidate number. Please try again.\n");
    }
}

void displayResultsAndWinner(Candidate *candidates, int numCandidates) {
    printf("\nVoting Results:\n");
    int maxVotes = 0;
    int winnerIndex = -1;
    for (int i = 0; i < numCandidates; i++) {
        printf("%d. %s: %d votes\n", i + 1, candidates[i].name, candidates[i].votes);
        if (candidates[i].votes > maxVotes) {
            maxVotes = candidates[i].votes;
            winnerIndex = i;
        }
    }
    if (winnerIndex != -1) {
        printf("\nWinner: %s\n", candidates[winnerIndex].name);
    } else {
        printf("\nNo winner yet.\n");
    }
}

int main() {
    int numCandidates;
    printf("Enter the number of candidates: ");
    scanf("%d", &numCandidates);

    Candidate *candidates = (Candidate*)malloc(numCandidates * sizeof(Candidate));
    if (candidates == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        return 1;
    }

    for (int i = 0; i < numCandidates; i++) {
        char name[50];
        printf("Enter the name of candidate %d: ", i + 1);
        scanf("%s", name);
        initializeCandidate(&candidates[i], name);
    }

    int choice;
    int candidateNumber;
    do {
        printf("\nMenu:\n");
        printf("1. Vote\n");
        printf("2. Display Results and Winner\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter the number of the candidate you want to vote for (between 1 and %d): ", numCandidates);
                scanf("%d", &candidateNumber);
                voteForCandidate(candidates, numCandidates, candidateNumber);
                break;
            case 2:
                displayResultsAndWinner(candidates, numCandidates);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    free(candidates);

    return 0;
}
