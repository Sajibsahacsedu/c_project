#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for player details
struct Player {
    char name[50];
    int age;
    float batting_avg;
    float bowling_avg;
};

// Structure for team details
struct Team {
    char name[50];
    char captain_name[50];
    int num_players;
    struct Player players[20]; // Assuming maximum 20 players per team
};

// Function prototypes
void createNewTeam();
void addPlayer();
void removePlayer();
void updatePlayerDetails();
void displayTeamDetails();
void displayPlayerDetails();
void saveTeamToFile(struct Team team);
struct Team loadTeamFromFile(char *team_name);

int main() {
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Create a new team\n");
        printf("2. Add player\n");
        printf("3. Remove player\n");
        printf("4. Update player details\n");
        printf("5. Display team details\n");
        printf("6. Display player details\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                createNewTeam();
                break;
            case 2:
                addPlayer();
                break;
            case 3:
                removePlayer();
                break;
            case 4:
                updatePlayerDetails();
                break;
            case 5:
                displayTeamDetails();
                break;
            case 6:
                displayPlayerDetails();
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 7);

    return 0;
}

// Function to create a new team
void createNewTeam() {
    struct Team team;
    printf("Enter team name: ");
    scanf("%s", team.name);
    printf("Enter captain name: ");
    scanf("%s", team.captain_name);
    printf("Enter number of players: ");
    scanf("%d", &team.num_players);
    
    for (int i = 0; i < team.num_players; i++) {
        printf("Enter player %d name: ", i + 1);
        scanf("%s", team.players[i].name);
        printf("Enter player %d age: ", i + 1);
        scanf("%d", &team.players[i].age);
        printf("Enter player %d batting average: ", i + 1);
        scanf("%f", &team.players[i].batting_avg);
        printf("Enter player %d bowling average: ", i + 1);
        scanf("%f", &team.players[i].bowling_avg);
    }

    saveTeamToFile(team);
}

// Function to add a player to a team
void addPlayer() {
    char team_name[50];
    printf("Enter team name: ");
    scanf("%s", team_name);

    struct Team team = loadTeamFromFile(team_name);
    if (strcmp(team.name, "") == 0) {
        printf("Team not found!\n");
        return;
    }

    struct Player player;
    printf("Enter player name: ");
    scanf("%s", player.name);
    printf("Enter player age: ");
    scanf("%d", &player.age);
    printf("Enter player batting average: ");
    scanf("%f", &player.batting_avg);
    printf("Enter player bowling average: ");
    scanf("%f", &player.bowling_avg);
    
    if (team.num_players < 20) {
        team.players[team.num_players++] = player;
        saveTeamToFile(team);
        printf("Player added successfully.\n");
    } else {
        printf("Maximum players reached!\n");
    }
}

// Function to remove a player from a team
void removePlayer() {
    char team_name[50];
    printf("Enter team name: ");
    scanf("%s", team_name);

    struct Team team = loadTeamFromFile(team_name);
    if (strcmp(team.name, "") == 0) {
        printf("Team not found!\n");
        return;
    }

    char player_name[50];
    printf("Enter player name to remove: ");
    scanf("%s", player_name);

    int i, found = 0;
    for (i = 0; i < team.num_players; i++) {
        if (strcmp(team.players[i].name, player_name) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        for (; i < team.num_players - 1; i++) {
            team.players[i] = team.players[i + 1];
        }
        team.num_players--;
        saveTeamToFile(team);
        printf("Player removed successfully.\n");
    } else {
        printf("Player not found!\n");
    }
}

// Function to update player details
void updatePlayerDetails() {
    char team_name[50];
    printf("Enter team name: ");
    scanf("%s", team_name);

    struct Team team = loadTeamFromFile(team_name);
    if (strcmp(team.name, "") == 0) {
        printf("Team not found!\n");
        return;
    }

    char player_name[50];
    printf("Enter player name to update: ");
    scanf("%s", player_name);

    int i, found = 0;
    for (i = 0; i < team.num_players; i++) {
        if (strcmp(team.players[i].name, player_name) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        int choice;
        printf("Select field to update:\n");
        printf("1. Batting average\n");
        printf("2. Bowling average\n");
        printf("3. Age\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter new batting average: ");
                scanf("%f", &team.players[i].batting_avg);
                break;
            case 2:
                printf("Enter new bowling average: ");
                scanf("%f", &team.players[i].bowling_avg);
                break;
            case 3:
                printf("Enter new age: ");
                scanf("%d", &team.players[i].age);
                break;
            default:
                printf("Invalid choice!\n");
        }
        saveTeamToFile(team);
        printf("Player details updated successfully.\n");
    } else {
        printf("Player not found!\n");
    }
}

// Function to display team details
void displayTeamDetails() {
    char team_name[50];
    printf("Enter team name: ");
    scanf("%s", team_name);

    struct Team team = loadTeamFromFile(team_name);
    if (strcmp(team.name, "") == 0) {
        printf("Team not found!\n");
        return;
    }

    printf("\nTeam Name: %s\n", team.name);
    printf("Captain: %s\n", team.captain_name);
    printf("Number of players: %d\n", team.num_players);
    printf("Players:\n");
    for (int i = 0; i < team.num_players; i++) {
        printf("Name: %s, Age: %d, Batting Avg: %.2f, Bowling Avg: %.2f\n",
               team.players[i].name, team.players[i].age,
               team.players[i].batting_avg, team.players[i].bowling_avg);
    }
}

// Function to display player details
void displayPlayerDetails() {
    char team_name[50];
    printf("Enter team name: ");
    scanf("%s", team_name);

        struct Team team = loadTeamFromFile(team_name);
    if (strcmp(team.name, "") == 0) {
        printf("Team not found!\n");
        return;
    }

    char player_name[50];
    printf("Enter player name: ");
    scanf("%s", player_name);

    int i, found = 0;
    for (i = 0; i < team.num_players; i++) {
        if (strcmp(team.players[i].name, player_name) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("\nPlayer Details:\n");
        printf("Name: %s\n", team.players[i].name);
        printf("Age: %d\n", team.players[i].age);
        printf("Batting Average: %.2f\n", team.players[i].batting_avg);
        printf("Bowling Average: %.2f\n", team.players[i].bowling_avg);
    } else {
        printf("Player not found!\n");
    }
}

// Function to save team details to a file
void saveTeamToFile(struct Team team) {
    FILE *file;
    char filename[100];
    sprintf(filename, "%s.txt", team.name);
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%s\n", team.name);
    fprintf(file, "%s\n", team.captain_name);
    fprintf(file, "%d\n", team.num_players);
    for (int i = 0; i < team.num_players; i++) {
        fprintf(file, "%s %d %.2f %.2f\n", team.players[i].name,
                team.players[i].age, team.players[i].batting_avg,
                team.players[i].bowling_avg);
    }
    fclose(file);
}

// Function to load team details from a file
struct Team loadTeamFromFile(char *team_name) {
    FILE *file;
    struct Team team;
    char filename[100];
    sprintf(filename, "%s.txt", team_name);
    file = fopen(filename, "r");
    if (file == NULL) {
        strcpy(team.name, "");
        return team;
    }
    fscanf(file, "%s", team.name);
    fscanf(file, "%s", team.captain_name);
    fscanf(file, "%d", &team.num_players);
    for (int i = 0; i < team.num_players; i++) {
        fscanf(file, "%s %d %f %f", team.players[i].name,
               &team.players[i].age, &team.players[i].batting_avg,
               &team.players[i].bowling_avg);
    }
    fclose(file);
    return team;
}
