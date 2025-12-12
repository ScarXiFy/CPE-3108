#include "main.h"

// MAIN MENU
void main_menu(void) {
    printf("=====================================\n");
    printf("       ADAPTIVE HATCH ESTIMATOR      \n");
    printf("=====================================\n");
    printf(" [1] Create New Dataset\n");
    printf(" [2] Load Existing Dataset\n");
    printf(" [3] Help\n");
    printf(" [0] Exit\n");
    printf("=====================================\n");
}

// Clear screen (Windows / Linux / Mac)
void clear_screen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// PAUSE
void pause_screen(void) {
    printf("\nPress Enter to continue...");
    char temp[10];
    if (fgets(temp, sizeof(temp), stdin) == NULL) {
        // Handle EOF or error
        clear_input_buffer();
    }
}

// Helper function to clear input buffer
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// HELP MENU
void help_menu(void) {
    char input_buffer[100];
    int choice;

    while (1) {
        clear_screen();
        printf("=== HELP ===\n");
        printf("This program estimates fish egg hatching time and temperature.\n");
        printf("Uses interpolation and extrapolation using Lagrange method to estimate the values.\n\n");
        printf("[0] Back to Main Menu\n");

        int valid_input = 0;
        while (!valid_input) {
            printf("\nEnter choice: ");
            if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
                if (sscanf(input_buffer, "%d", &choice) == 1) {
                    valid_input = 1;
                } else {
                    printf("Invalid input. Please enter a number.\n");
                }
            }
        }

        if (choice == 0) return;
        
        printf("Invalid choice. Please enter 0 to go back.\n");
        pause_screen();
    }
}

void title() {
    system("title Hatch Estimator");
}