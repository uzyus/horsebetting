#ifndef HORSE_DATABASE_H
#define HORSE_DATABASE_H

typedef struct {
    char name[50];
    int age;
    float speed;
} Horse;

int simulateHorseRace(Horse* database, int size);
float loadCashBalance();
float calculatePayout(float stake, int numHorses, float horseSpeed);
void saveCashBalance(float cashBalance);
void addHorse(Horse** database, int* size);
void removeHorse(Horse** database, int* size, char* name);
void sortHorsesByAge(Horse* database, int size);
void sortHorsesBySpeed(Horse* database, int size);
void sortHorsesByName(Horse* database, int size);
void saveDatabaseToFile(Horse* database, int size, const char* filename);
void loadDatabaseFromFile(Horse** database, int* size, const char* filename);
void listAllHorses(Horse* database, int size);
void searchHorseByName(Horse* database, int size, const char* name);
void userMenu(Horse* database, int size);
void adminMenu(Horse** database, int* size);
#endif
