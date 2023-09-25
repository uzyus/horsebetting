#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include <stdio.h>
#include <stdlib.h>



int main() {
    Horse* database = NULL;
    int size = 0;
    loadDatabaseFromFile(&database, &size, "horse_database.dat");
    float cashBalance = loadCashBalance();
    int choice;
    while (1) {
        printf("1. User Menu (Betting)\n");
        printf("2. Admin Menu (Manage Horses)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            userMenu(database, size, &cashBalance);
            break;
        case 2:
            adminMenu(&database, &size);
            break;
        case 3:
            free(database);
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
