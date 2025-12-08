#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SPECIES 50      // Maximum number of species (can be adjusted)
#define MAX_POINTS 100     // Maximum data points per species (can be adjusted)

typedef struct {
    float temperature;
    float hatch_time;
} DataPoint;

typedef struct {
    char species_name[50];
    DataPoint data_points[MAX_POINTS];
    int data_count;
} Species;

// GLOBAL DATA STORAGE
Species species_list[MAX_SPECIES];
int species_count = 0;

// FUNCTION PROTOTYPES
void main_menu();
void create_new_dataset();
void load_dataset_menu();
void species_submenu();
void help_menu();
void clear_screen();
void pause_screen();

// MAIN FUNCTION
int main() {
    int choice;

    while (1) {
        clear_screen();
        main_menu();
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: create_new_dataset(); break;
            case 2: load_dataset_menu(); break;
            case 3: help_menu(); break;
            case 0:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Press Enter.\n");
                getchar(); getchar();
        }
    }

    return 0;
}

// MAIN MENU
void main_menu() {
    printf("=====================================\n");
    printf("       ADAPTIVE HATCH ESTIMATOR      \n");
    printf("=====================================\n");
    printf(" [1] Create New Dataset\n");
    printf(" [2] Load Existing Dataset\n");
    printf(" [3] Help\n");
    printf(" [0] Exit\n");
    printf("=====================================\n");
}

// ------------------------------------------------------ SUBMENUS ------------------------------------------------------

// CREATE NEW DATASET
void create_new_dataset() {
    int choice;

    while (1) {
        clear_screen();
        printf("=== CREATE NEW DATASET ===\n");
        printf("[1] Start new dataset\n");
        printf("[0] Back to Main Menu\n");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 0) {
            return;
        }

        if (choice != 1) {
            printf("Invalid choice.\n");
            pause_screen();
            continue;
        }

        // ========== START DATASET CREATION PROCESS ==========

        if (species_count >= MAX_SPECIES) {
            printf("Maximum species limit reached.\n");
            pause_screen();
            return;
        }

        Species *sp = &species_list[species_count];

        printf("Enter species name: ");
        getchar();
        fgets(sp->species_name, sizeof(sp->species_name), stdin);
        sp->species_name[strcspn(sp->species_name, "\n")] = 0;

        int n;
        printf("Enter number of data points: ");
        scanf("%d", &n);

        if (n < 1 || n > MAX_POINTS) {
            printf("Invalid number of data points.\n");
            pause_screen();
            continue;
        }

        sp->data_count = 0;

        for (int i = 0; i < n; i++) {
            printf("\n--- Data Point %d ---\n", i + 1);
            printf("  Temperature (C): ");
            scanf("%f", &sp->data_points[i].temperature);
            printf("  Hatching Time (hrs): ");
            scanf("%f", &sp->data_points[i].hatch_time);

            sp->data_count++;
        }

        species_count++;
        printf("\nDataset for '%s' created with %d data points.\n",
               sp->species_name, sp->data_count);

        pause_screen();
        return;
    }
}

// LOAD DATASET MENU
void load_dataset_menu() {
    int choice;

    while (1) {
        clear_screen();
        printf("=== LOAD DATASET ===\n");

        if (species_count == 0) {
            printf("No datasets available.\n");
            pause_screen();
            return;
        }

        for (int i = 0; i < species_count; i++) {
            printf("[%d] %s\n", i + 1, species_list[i].species_name);
        }
        printf("[0] Back to Main Menu\n");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 0) return;

        if (choice < 1 || choice > species_count) {
            printf("Invalid choice.\n");
            pause_screen();
            continue;
        }

        // Directly open submenu for chosen species
        species_submenu(&species_list[choice - 1]);
    }
}

// SPECIES SUBMENU
void species_submenu(Species *sp) {
    int choice;

    while (1) {
        clear_screen();
        printf("=== SPECIE: %s ===\n", sp->species_name);
        printf("[1] Get Hatching Time \n");
        printf("[2] Het Required Temperature\n");
        printf("[3] Add Data Point\n");
        printf("[4] View Data\n");
        printf("[0] Back to Load Dataset Menu\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                float temp;
                printf("Enter Temperature (C): ");
                scanf("%f", &temp);

                // Placeholder - implement interpolation/extrapolation logic here
                printf("Estimated Hatching Time at %.2f C: [IMPLEMENT LOGIC] hrs\n", temp);
                pause_screen();
                break;
            }

            case 2: {
                float hatch_time;
                printf("Enter Desired Hatching Time (hrs): ");
                scanf("%f", &hatch_time);

                // Placeholder - implement reverse interpolation/extrapolation logic here
                printf("Required Temperature for %.2f hrs: [IMPLEMENT LOGIC] C\n", hatch_time);     // IMPLEMENT LOGIC KAY MAO NANG COMPUTED VALUE
                pause_screen();
                break;
            }

            case 3: {
                if (sp->data_count >= MAX_POINTS) {
                    printf("Maximum data points reached.\n");
                    pause_screen();
                    break;
                }

                float temp, hatch_time;
                printf("Enter Temperature (C): ");
                scanf("%f", &temp);
                printf("Enter Hatching Time (hrs): ");
                scanf("%f", &hatch_time);

                sp->data_points[sp->data_count].temperature = temp;
                sp->data_points[sp->data_count].hatch_time = hatch_time;
                sp->data_count++;

                printf("Data point added/updated.\n");
                pause_screen();
                break;
            }

            case 4: {
                clear_screen();
                printf("=== DATASET: %s ===\n", sp->species_name);

                if (sp->data_count == 0) {
                    printf("No data points available.\n");
                } else {
                    for (int i = 0; i < sp->data_count; i++) {
                        printf("[%d] : Temperature = %.2f C, Hatching Time = %.2f hrs\n",
                               i + 1, sp->data_points[i].temperature, sp->data_points[i].hatch_time);
                    }
                }

                pause_screen();
                break;
            }

            case 0:
                return;

            default:
                printf("Invalid choice.\n");
                pause_screen();
        }
    }
    
}

// HELP MENU
void help_menu() {
    int back = 0;

    while (!back) {
        clear_screen();
        printf("=== HELP ===\n");
        printf("This program estimates fish egg hatching time.\n");
        printf("Uses interpolation and extrapolation.\n\n");
        printf("[0] Back to Main Menu\n");

        printf("\nEnter choice: ");
        int choice;
        scanf("%d", &choice);

        if (choice == 0) back = 1;
    }
}

// Clear screen (Windows / Linux / Mac)
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// PAUSE
void pause_screen() {
    printf("Press Enter to continue...");
    getchar(); getchar();
}
