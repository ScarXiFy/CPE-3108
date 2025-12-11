#include "main.h"

// Global variables definition
Species species_list[MAX_SPECIES];
int species_count = 0;

int main() {
    char input_buffer[100];
    int choice;

    while (1) {
        clear_screen();
        main_menu();
        
        printf("Enter choice: ");
        if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
            if (input_buffer[0] == '\n') {
                printf("Please enter a number.\n");
                pause_screen();
                continue;
            }
            
            if (sscanf(input_buffer, "%d", &choice) != 1) {
                printf("Invalid input. Please enter a number.\n");
                pause_screen();
                continue;
            }
        }

        switch (choice) {
            case 1: create_new_dataset(); break;
            case 2: load_dataset_menu(); break;
            case 3: help_menu(); break;
            case 0:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please select 0-3.\n");
                pause_screen();
        }
    }
    return 0;
}