#include <stdio.h>
#include <string.h>

int amt[10] = {0}, total = 0;

struct package {
    int ch, pass, pass_new;
    char us_name[100], us_name_new[100];
} p1;

void displayBestPlaces(int cho);
void registerUser(const char *username, int pin);
int loginUser(const char *username, int pin);
void saveBookingAmount(const char *username, int dest_index, int cost);
void loadAmounts(const char *username);

int main() {
    int choice;
    int i;

    while (1) {
        printf("\n\t***********************************\n");
        printf("\t\t Trip Planner\n");
        printf("\t***********************************\n");
        printf(" 1. NEW USER\n");
        printf(" 2. LOGIN\n");
        printf(" 3. EXIT\n");
        printf(" ENTER YOUR CHOICE: ");

        if (scanf("%d", &p1.ch) != 1) {
            printf("\n INVALID INPUT. ENTER A NUMBER.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (p1.ch) {
            case 1: {
                printf("\n\t REGISTER");
                printf("\n ENTER USER NAME: ");
                scanf("%s", p1.us_name);
                printf(" ENTER YOUR PIN: ");
                scanf("%d", &p1.pass);

                registerUser(p1.us_name, p1.pass);
                printf("\nREGISTRATION SUCCESSFUL! YOU CAN NOW LOG IN.\n");
                break;
            }
            case 2: {
                printf("\n\t LOGIN");
                printf("\n ENTER USER NAME: ");
                scanf("%s", p1.us_name_new);
                printf(" ENTER YOUR PIN: ");
                scanf("%d", &p1.pass_new);

                if (loginUser(p1.us_name_new, p1.pass_new)) {
                    for(i = 0; i < 10; i++) {
                        amt[i] = 0;
                    }
                    loadAmounts(p1.us_name_new);

                    int loggedIn = 1;
                    while (loggedIn) {
                        printf("\n 1. BOOKING");
                        printf("\n 2. CHECK TOTAL");
                        printf("\n 3. VIEW DESTINATIONS MENU");
                        printf("\n 4. LOGOUT");
                        printf("\n ENTER YOUR CHOICE: ");
                        scanf("%d", &choice);

                        switch (choice) {
                            case 1: {
                                int cho, n, y;
                                printf("\n\t THE MENU");
                                printf("\n 1. Paris, France - Rs 400000");
                                printf("\n 2. Tokyo, Japan - Rs 600000");
                                printf("\n 3. Bangkok, Thailand - Rs 250000");
                                printf("\n 4. Abu Dhabi, UAE - Rs 380000");
                                printf("\n 5. Miami, USA - Rs 120000");
                                printf("\n 6. Rome, Italy - Rs 100000");
                                printf("\n 7. Munich, Germany - Rs 300000");
                                printf("\n 8. Madrid, Spain - Rs 320000");
                                printf("\n 9. Istanbul, Turkey - Rs 450000");
                                printf("\n 10. Gilgit, Pakistan - Rs 75000");
                                printf("\n ENTER A CHOICE: ");
                                scanf("%d", &cho);

                                if (cho >= 1 && cho <= 10) {
                                    displayBestPlaces(cho);
                                    printf("\n DO YOU WANT TO CONFIRM YOUR BOOKING \n 1. YES \n 2. NO : ");
                                    scanf("%d", &y);
                                    if (y == 1) {
                                        printf("\n ENTER THE NUMBER OF TICKETS: ");
                                        scanf("%d", &n);
                                        int cost = 0;
                                        switch (cho) {
                                            case 1: cost = n * 400000; break;
                                            case 2: cost = n * 600000; break;
                                            case 3: cost = n * 250000; break;
                                            case 4: cost = n * 380000; break;
                                            case 5: cost = n * 120000; break;
                                            case 6: cost = n * 100000; break;
                                            case 7: cost = n * 300000; break;
                                            case 8: cost = n * 320000; break;
                                            case 9: cost = n * 450000; break;
                                            case 10: cost = n * 75000; break;
                                        }
                                        amt[cho - 1] += cost;
                                        saveBookingAmount(p1.us_name_new, cho - 1, cost);
                                        printf("\n BOOKING COMPLETED! HAVE A SAFE TRIP :)");
                                        printf("\n THE AMOUNT FOR THIS BOOKING IS: %d\n", cost);
                                    } else {
                                        printf("\n BOOKING CANCELED!");
                                    }
                                } else {
                                    printf("\n INVALID CHOICE.");
                                }
                                break;
                            }
                            case 2: {
                                total = 0;
                                for (i = 0; i < 10; i++) {
                                    total += amt[i];
                                }
                                printf("\n YOUR TOTAL SPENT AMOUNT IS: %d\n", total);
                                break;
                            }
                            case 3: {
                                printf("\n\t THE MENU");
                                printf("\n 1. Paris, France - Rs 400000");
                                printf("\n 2. Tokyo, Japan - Rs 600000");
                                printf("\n 3. Bangkok, Thailand - Rs 250000");
                                printf("\n 4. Abu Dhabi, UAE - Rs 380000");
                                printf("\n 5. Miami, USA - Rs 120000");
                                printf("\n 6. Rome, Italy - Rs 100000");
                                printf("\n 7. Munich, Germany - Rs 300000");
                                printf("\n 8. Madrid, Spain - Rs 320000");
                                printf("\n 9. Istanbul, Turkey - Rs 450000");
                                printf("\n 10. Gilgit, Pakistan - Rs 75000\n");
                                break;
                            }
                            case 4:
                                printf("\n LOGGING OUT...\n");
                                loggedIn = 0;
                                break;
                            default:
                                printf("\n INVALID CHOICE. TRY AGAIN.\n");
                        }
                    }
                } else {
                    printf("\n WRONG USERNAME OR PASSWORD!!!! CHECK CORRECTLY\n");
                }
                break;
            }
            case 3:
                printf("\n EXITING...\n");
                return 0;
            default:
                printf("\n INVALID CHOICE. TRY AGAIN.\n");
        }
    }
}

void registerUser(const char *username, int pin) {
    FILE *file = fopen("users.txt", "a");
    if (file == NULL) return;
    fprintf(file, "%s %d\n", username, pin);
    fclose(file);
}

int loginUser(const char *username, int pin) {
    char storedUsername[100];
    int storedPin;
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) return 0;

    while (fscanf(file, "%s %d", storedUsername, &storedPin) != EOF) {
        if (strcmp(storedUsername, username) == 0 && storedPin == pin) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void saveBookingAmount(const char *username, int dest_index, int cost) {
    FILE *file = fopen("amounts.txt", "a");
    if (file == NULL) return;
    fprintf(file, "%s %d %d\n", username, dest_index, cost);
    fclose(file);
}

void loadAmounts(const char *username) {
    char storedUsername[100];
    int dest_index, cost;
    int current_total = 0;
    FILE *file = fopen("amounts.txt", "r");
    if (file == NULL) return;

    while (fscanf(file, "%s %d %d", storedUsername, &dest_index, &cost) != EOF) {
        if (strcmp(storedUsername, username) == 0 && dest_index >= 0 && dest_index < 10) {
            amt[dest_index] += cost;
            current_total += cost;
        }
    }
    fclose(file);
    printf("\n WELCOME BACK! YOUR HISTORICAL TOTAL SPENT IS: %d\n", current_total);
}

void displayBestPlaces(int cho) {
    switch (cho) {
        case 1:
            printf("\n FAMOUS PLACES IN PARIS, FRANCE:");
            printf("\n \t #1. Louvre Museum\n \t #2. Eiffel Tower\n \t #3. Arc de Triomphe");
            break;
        case 2:
            printf("\n FAMOUS PLACES IN TOKYO, JAPAN:");
            printf("\n \t #1. Tokyo Tower\n \t #2. Sensō-ji\n \t #3. Tokyo Skytree");
            break;
        case 3:
            printf("\n FAMOUS PLACES IN BANGKOK, THAILAND:");
            printf("\n \t #1. The Grand Palace\n \t #2. Wat Arun\n \t #3. Temple of Emerald Buddha");
            break;
        case 4:
            printf("\n FAMOUS PLACES IN ABU DHABI, UAE:");
            printf("\n \t #1. Sheikh Zayed Grand Mosque\n \t #2. Ferrari World\n \t #3. Emirates Palace");
            break;
        case 5:
            printf("\n FAMOUS PLACES IN MIAMI, USA:");
            printf("\n \t #1. South Beach\n \t #2. Vizcaya Museum and Gardens\n \t #3. Bayside Marketplace");
            break;
        case 6:
            printf("\n FAMOUS PLACES IN ROME, ITALY:");
            printf("\n \t #1. Colosseum\n \t #2. Pantheon\n \t #3. Trevi Fountain");
            break;
        case 7:
            printf("\n FAMOUS PLACES IN MUNICH, GERMANY:");
            printf("\n \t #1. English Garden\n \t #2. Nymphenburg Palace\n \t #3. Marienplatz");
            break;
        case 8:
            printf("\n FAMOUS PLACES IN MADRID, SPAIN:");
            printf("\n \t #1. Royal Palace of Madrid\n \t #2. Prado Museum\n \t #3. Retiro Park");
            break;
        case 9:
            printf("\n FAMOUS PLACES IN ISTANBUL, TURKEY:");
            printf("\n \t #1. Hagia Sophia\n \t #2. The Blue Mosque\n \t #3. Topkapi Palace");
            break;
        case 10:
            printf("\n FAMOUS PLACES IN GILGIT, PAKISTAN:");
            printf("\n \t #1. Attabad Lake\n \t #2. Hunza Valley\n \t #3. Naltar Valley");
            break;
        }
    }
