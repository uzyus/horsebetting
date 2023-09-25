#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MIN_BET_AMOUNT 10

float loadCashBalance() {
    FILE* file = fopen("cash_balance.txt", "r");
    if (file == NULL) {
        return 200;
    }
    float cashBalance;
    fscanf(file, "%f", &cashBalance);
    fclose(file);
    return cashBalance;
}

void saveCashBalance(float cashBalance) {
    FILE* file = fopen("cash_balance.txt", "w");
    if (file == NULL) {
        printf("Error opening cash_balance.txt for writing.\n");
        return;
    }
    fprintf(file, "%.2f", cashBalance);
    fclose(file);
}

void listAllHorses(Horse* database, int size) {
    if (size == 0) {
        printf("The horse database is empty.\n");
        return;
    }

    printf("List of all horses:\n");
    for (int i = 0; i < size; i++) {
        printf("Name: %s\n", database[i].name);
        printf("Age: %d\n", database[i].age);
        printf("Speed: %.2f\n", database[i].speed);

        float odds = (database[i].speed);
        printf("Odds of Winning: %.2f%%\n", odds);

        float potentialGain = (((10)* size / (database[i].speed*10)) * 100);
        printf("Potential Money Gain (for $10 bet): $%.2f\n", potentialGain);
        printf("-----------\n");
    }
}

void searchHorseByName(Horse* database, int size, const char* name) {
    int found = 0;
    printf("Search results for horse with name '%s':\n", name);
    for (int i = 0; i < size; i++) {
        if (strcmp(database[i].name, name) == 0) {
            printf("Name: %s\n", database[i].name);
            printf("Age: %d\n", database[i].age);
            printf("Speed: %.2f\n", database[i].speed);
            printf("-----------\n");
            found = 1;
        }
    }
    if (!found) {
        printf("No horse with the name '%s' found in the database.\n", name);
    }
}

void addHorse(Horse** database, int* size) {
    (*size)++;
    *database = (Horse*)realloc(*database, (*size) * sizeof(Horse));

    if (*database == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    printf("Enter the name of the horse: ");
    scanf("%s", (*database)[*size - 1].name);
    printf("Enter the age of the horse: ");
    scanf("%d", &(*database)[*size - 1].age);
    printf("Enter the speed of the horse: ");
    scanf("%f", &(*database)[*size - 1].speed);
}

void removeHorse(Horse** database, int* size, char* name) {
    int found = -1;
    for (int i = 0; i < *size; i++) {
        if (strcmp((*database)[i].name, name) == 0) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        for (int j = found; j < *size - 1; j++) {
            (*database)[j] = (*database)[j + 1];
        }
        (*size)--;

        if (*size == 0) {
            free(*database);
            *database = NULL;
        }
        else {
            Horse* temp = (Horse*)realloc(*database, (*size) * sizeof(Horse));
            if (temp == NULL) {
                printf("Memory allocation failed.\n");
                exit(1);
            }
            *database = temp;
        }

        printf("Horse %s removed successfully.\n", name);
    }
    else {
        printf("Horse %s not found in the database.\n", name);
    }
}

void sortHorsesByAge(Horse* database, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (database[j].age > database[j + 1].age) {
                Horse temp = database[j];
                database[j] = database[j + 1];
                database[j + 1] = temp;
            }
        }
    }
}

void sortHorsesBySpeed(Horse* database, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (database[j].speed > database[j + 1].speed) {
                Horse temp = database[j];
                database[j] = database[j + 1];
                database[j + 1] = temp;
            }
        }
    }
}

void sortHorsesByName(Horse* database, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (strcmp(database[j].name, database[j + 1].name) > 0) {
                Horse temp = database[j];
                database[j] = database[j + 1];
                database[j + 1] = temp;
            }
        }
    }
}

void saveDatabaseToFile(Horse* database, int size, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }
    fwrite(database, sizeof(Horse), size, file);
    fclose(file);
    printf("Database saved to %s.\n", filename);
}

void loadDatabaseFromFile(Horse** database, int* size, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("File not found or database is empty. Starting with an empty database.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    *size = fileSize / sizeof(Horse);
    *database = (Horse*)malloc(fileSize);

    if (*database == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    fread(*database, sizeof(Horse), *size, file);
    fclose(file);
    printf("Database loaded from %s.\n", filename);
}

float calculatePayout(float stake, int numHorses, float horseSpeed) {
    return (((stake * numHorses) / horseSpeed)*100);
}

int simulateHorseRace(Horse* database, int size) {
    srand(time(NULL));
    int winningHorse = -1;
    float maxDistance = 0.0;

    for (int i = 0; i < size; i++) {
        float distance = (rand() % 100 + 1) * database[i].speed;
        if (distance > maxDistance) {
            maxDistance = distance;
            winningHorse = i;
        }
    }

    return winningHorse;
}

void userMenu(Horse* database, int size) {
    float cashBalance = loadCashBalance();
    char chosenHorseName[50];
    int betAmount;

    while (1) {
        printf("\nUser Menu:\n");
        printf("1. Place Bet\n");
        printf("2. List All Horses\n");
        printf("3. Check Cash Balance\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter the name of the horse you want to bet on: ");
            scanf("%s", chosenHorseName);
            printf("Enter the bet amount (minimum $%d): ", MIN_BET_AMOUNT);
            scanf("%d", &betAmount);

            if (betAmount < MIN_BET_AMOUNT || betAmount > cashBalance) {
                printf("Invalid bet amount.\n");
            }
            else {
                int chosenHorseIndex = -1;
                for (int i = 0; i < size; i++) {
                    if (strcmp(database[i].name, chosenHorseName) == 0) {
                        chosenHorseIndex = i;
                        break;
                    }
                }

                if (chosenHorseIndex != -1) {
                    int winningHorseIndex = simulateHorseRace(database, size);

                    if (chosenHorseIndex == winningHorseIndex) {
                        float payout = (calculatePayout(betAmount, size, (database[chosenHorseIndex].speed)*10));
                        cashBalance += payout;
                        saveCashBalance(cashBalance);
                        printf("Congratulations! Your horse (%s) won! You won $%.2f\n", chosenHorseName, payout);
                    }
                    else {
                        cashBalance -= betAmount;
                        saveCashBalance(cashBalance);
                        printf("Sorry, your horse (%s) lost. You lost $%d\n", chosenHorseName, betAmount);
                    }

                    printf("Winning Horse: %s\n", database[winningHorseIndex].name);
                }
                else {
                    printf("Horse not found in the database.\n");
                }
            }
            break;
        case 2:
            listAllHorses(database, size);
            break;
        case 3:
            printf("Cash Balance: $%.2f\n", cashBalance);
            break;
        case 4:
            return;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}

void adminMenu(Horse** database, int* size) {
    while (1) {
        printf("\nAdmin Menu (Manage Horses):\n");
        printf("1. Add Horse\n");
        printf("2. Remove Horse\n");
        printf("3. List All Horses\n");
        printf("4. Sort Horses\n");
        printf("5. Search Horse by Name\n");
        printf("6. Save Database\n");
        printf("7. Return to Main Menu\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addHorse(database, size);
            break;
        case 2:
            printf("Enter the name of the horse to remove: ");
            char nameToRemove[50];
            scanf("%s", nameToRemove);
            removeHorse(database, size, nameToRemove);
            break;
        case 3:
            listAllHorses(*database, *size);
            break;
        case 4:
            printf("Sort Horses By:\n");
            printf("1. Age\n");
            printf("2. Speed\n");
            printf("3. Name\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            switch (choice) {
            case 1:
                sortHorsesByAge(*database, *size);
                break;
            case 2:
                sortHorsesBySpeed(*database, *size);
                break;
            case 3:
                sortHorsesByName(*database, *size);
                break;
            default:
                printf("Invalid choice for sorting.\n");
                break;
            }
            break;
        case 5:
            printf("Enter the name of the horse to search: ");
            char searchName[50];
            scanf("%s", searchName);
            searchHorseByName(*database, *size, searchName);
            break;
        case 6:
            saveDatabaseToFile(*database, *size, "horse_database.dat");
            printf("Database saved successfully.\n");
            break;
        case 7:
            return;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}