#include <stdio.h>
#include <stdlib.h>

int main() {
    int choice;

    while (1) {
        clear_screen();
        main_menu();
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: create_dataset_menu(); break;
            case 2: load_dataset_menu(); break;
            case 3: edit_dataset_menu(); break;
            case 4: estimate_menu(); break;
            case 5: help_menu(); break;
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

// --- SUBMENUS ------------------------------------------------------

// CREATE DATASET MENU
void create_dataset_menu() {
    int back = 0;

    while (!back) {
        clear_screen();
        printf("=== CREATE NEW DATASET ===\n");
        printf("[1] Enter species name\n");
        printf("[2] Enter data points\n");
        printf("[0] Back to Main Menu\n");

        printf("\nEnter choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter species name: ");
                // TODO
                getchar(); getchar();
                break;
            case 2:
                printf("Enter data points...\n");
                // TODO
                getchar(); getchar();
                break;
            case 0:
                back = 1;
                break;
            default:
                printf("Invalid choice.\n");
                getchar(); getchar();
        }
    }
}

// LOAD DATASET MENU
void load_dataset_menu() {
    int back = 0;

    while (!back) {
        clear_screen();
        printf("=== LOAD DATASET ===\n");
        printf("[1] Species 1\n");
        printf("[2] Species 2\n");
        printf("[0] Back to Main Menu\n");

        printf("\nEnter choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Loading species 1...\n");
                getchar(); getchar();
                break;
            case 2:
                printf("Loading species 2...\n");
                getchar(); getchar();
                break;
            case 0:
                back = 1;
                break;
            default:
                printf("Invalid choice.\n");
                getchar(); getchar();
        }
    }
}

// EDIT DATASET MENU
void edit_dataset_menu() {
    int back = 0;

    while (!back) {
        clear_screen();
        printf("=== EDIT DATASET ===\n");
        printf("[1] Modify data\n");
        printf("[2] Delete data\n");
        printf("[0] Back to Main Menu\n");

        printf("\nEnter choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Modify data...\n");
                getchar(); getchar();
                break;
            case 2:
                printf("Delete data...\n");
                getchar(); getchar();
                break;
            case 0:
                back = 1;
                break;
            default:
                printf("Invalid choice.\n");
                getchar(); getchar();
        }
    }
}

// ESTIMATE MENU
void estimate_menu() {
    int back = 0;

    while (!back) {
        clear_screen();
        printf("=== ESTIMATE HATCH TIME ===\n");
        printf("[1] Get hatching time from temperature\n");
        printf("[2] Get required temperature\n");
        printf("[0] Back to Main Menu\n");

        printf("\nEnter choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Estimating hatching time...\n");
                getchar(); getchar();
                break;
            case 2:
                printf("Estimating required temperature...\n");
                getchar(); getchar();
                break;
            case 0:
                back = 1;
                break;
            default:
                printf("Invalid choice.\n");
                getchar(); getchar();
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


// MAIN MENU
void main_menu() {
    printf("=====================================\n");
    printf("       ADAPTIVE HATCH ESTIMATOR      \n");
    printf("=====================================\n");
    printf(" [1] Create New Dataset\n");
    printf(" [2] Load Existing Dataset\n");
    printf(" [3] Edit Dataset\n");
    printf(" [4] Estimate Hatch Time\n");
    printf(" [5] Help\n");
    printf(" [0] Exit\n");
    printf("=====================================\n");
}