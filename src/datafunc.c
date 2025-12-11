#include "main.h"

// CREATE NEW DATASET
void create_new_dataset(void) {
    clear_screen();
    
    if (species_count >= MAX_SPECIES) {
        printf("Maximum species limit reached.\n");
        pause_screen();
        return;
    }

    char input_buffer[100];
    int menu_choice;
    
    printf("=== CREATE NEW DATASET ===\n\n");
    printf("[1] Start new dataset\n");
    printf("[0] Back to Main Menu\n\n");

    int valid_input = 0;
    while (!valid_input) {
        printf("Enter choice: ");
        if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
            if (sscanf(input_buffer, "%d", &menu_choice) == 1) {
                if (menu_choice == 0 || menu_choice == 1) {
                    valid_input = 1;
                } else {
                    printf("Invalid choice. Please enter 0 or 1.\n");
                }
            } else {
                printf("Invalid input. Please enter a number.\n");
            }
        }
    }

    if (menu_choice == 0) {
        return;
    }

    clear_screen();
    printf("=== CREATE NEW DATASET ===\n\n");
    
    Species *sp = &species_list[species_count];
    
    printf("Enter species name: ");
    if (fgets(sp->species_name, sizeof(sp->species_name), stdin) != NULL) {
        sp->species_name[strcspn(sp->species_name, "\n")] = 0;
    }

    // ---------------- TEMPERATURE THRESHOLD INPUT ----------------
    valid_input = 0;
    
    // Input for minimum temperature
    while (!valid_input) {
        printf("\nEnter minimum allowed temperature (C): ");
        if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
            if (sscanf(input_buffer, "%f", &sp->min_temp) == 1) {
                valid_input = 1;
            } else {
                printf("Invalid input. Please enter a numeric value.\n");
            }
        }
    }
    
    // Input for maximum temperature
    valid_input = 0;
    while (!valid_input) {
        printf("Enter maximum allowed temperature (C): ");
        if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
            if (sscanf(input_buffer, "%f", &sp->max_temp) == 1) {
                valid_input = 1;
            } else {
                printf("Invalid input. Please enter a numeric value.\n");
            }
        }
    }

    if (sp->max_temp <= sp->min_temp) {
        printf("\nInvalid Threshold. Max temperature must be greater than min temperature.\n");
        pause_screen();
        return;
    }

    printf("\nTemperature Threshold: %.2f C to %.2f C\n",
           sp->min_temp, sp->max_temp);

    // ---------------- NUMBER OF DATA POINTS ----------------
    int n;
    valid_input = 0;
    while (!valid_input) {
        printf("\nEnter number of data points: ");
        if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
            if (sscanf(input_buffer, "%d", &n) == 1) {
                if (n >= 1 && n <= MAX_POINTS) {
                    valid_input = 1;
                } else {
                    printf("Invalid number. Please enter a value between 1 and %d.\n", MAX_POINTS);
                }
            } else {
                printf("Invalid input. Please enter a numeric value.\n");
            }
        }
    }

    sp->data_count = 0;

    // ---------------- ENTER DATA POINTS ----------------
    for (int i = 0; i < n; i++) {
        float t, h;

        printf("\n--- Data Point %d ---\n", i + 1);

        // Input for temperature
        valid_input = 0;
        while (!valid_input) {
            printf("  Enter Temperature (C): ");
            if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
                if (sscanf(input_buffer, "%f", &t) == 1) {
                    if (t >= sp->min_temp && t <= sp->max_temp) {
                        valid_input = 1;
                    } else {
                        printf("  ERROR: Temperature must be between %.2f and %.2f C.\n",
                               sp->min_temp, sp->max_temp);
                    }
                } else {
                    printf("  Invalid input. Please enter a numeric value.\n");
                }
            }
        }

        // Input for hatch time
        valid_input = 0;
        while (!valid_input) {
            printf("  Enter Hatching Time (hrs): ");
            if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
                if (sscanf(input_buffer, "%f", &h) == 1) {
                    if (h > 0) {
                        valid_input = 1;
                    } else {
                        printf("  Hatch time must be positive.\n");
                    }
                } else {
                    printf("  Invalid input. Please enter a numeric value.\n");
                }
            }
        }

        sp->data_points[i].temperature = t;
        sp->data_points[i].hatch_time = h;
        sp->data_count++;
    }

    species_count++;

    printf("\n\nDataset for '%s' created successfully.\n", sp->species_name);
    printf("Total data points: %d\n", sp->data_count);
    pause_screen();
}

// LOAD DATASET MENU
void load_dataset_menu(void) {
    char input_buffer[100];
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

        // Input validation
        int valid_input = 0;
        while (!valid_input) {
            printf("\nEnter choice: ");
            if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
                // Check for empty input
                if (input_buffer[0] == '\n') {
                    printf("Please enter a number: ");
                    continue;
                }
                
                if (sscanf(input_buffer, "%d", &choice) == 1) {
                    valid_input = 1;
                } else {
                    printf("Invalid input. Please enter a number.\n");
                }
            }
        }

        if (choice == 0) return;

        if (choice < 1 || choice > species_count) {
            printf("Invalid choice. Please select a valid option (1-%d).\n", species_count);
            pause_screen();
            continue;
        }

        // Directly open submenu for chosen species
        species_submenu(&species_list[choice - 1]);
    }
}

// SPECIES SUBMENU
void species_submenu(Species *sp) {
    char input_buffer[100];
    int choice;
    int valid_input;
    float temp, hatch_time;

    while (1) {
        clear_screen();
        printf("=== SPECIES: %s ===\n", sp->species_name);
        printf("Temperature Threshold: %.2f C to %.2f C\n", sp->min_temp, sp->max_temp);
        printf("Data Points: %d\n", sp->data_count);
        printf("=================================\n");
        printf("[1] Get Hatching Time \n");
        printf("[2] Get Required Temperature\n");
        printf("[3] Add Data Point\n");
        printf("[4] View Data\n");
        printf("[0] Back to Load Dataset Menu\n");
        printf("=================================\n");
        
        // Menu choice input
        valid_input = 0;
        while (!valid_input) {
            printf("Enter choice: ");
            if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
                // Check for empty input
                if (input_buffer[0] == '\n') {
                    printf("Please enter a number: ");
                    continue;
                }
                
                if (sscanf(input_buffer, "%d", &choice) == 1) {
                    valid_input = 1;
                } else {
                    printf("Invalid input. Please enter a number.\n");
                }
            }
        }

        switch (choice) {
            case 1: {
                // Get Hatching Time
                valid_input = 0;
                while (!valid_input) {
                    printf("Enter Temperature (C): ");
                    if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
                        if (sscanf(input_buffer, "%f", &temp) == 1) {
                            // Check if temperature is within threshold
                            if (temp < sp->min_temp) {
                                printf("ERROR: Temperature %.2f C is below minimum threshold (%.2f C).\n", 
                                       temp, sp->min_temp);
                                printf("Please enter a temperature between %.2f and %.2f C.\n", 
                                       sp->min_temp, sp->max_temp);
                            } else if (temp > sp->max_temp) {
                                printf("ERROR: Temperature %.2f C is above maximum threshold (%.2f C).\n", 
                                       temp, sp->max_temp);
                                printf("Please enter a temperature between %.2f and %.2f C.\n", 
                                       sp->min_temp, sp->max_temp);
                            } else {
                                valid_input = 1;
                            }
                        } else {
                            printf("Invalid input. Please enter a numeric value.\n");
                        }
                    }
                }

                // Placeholder - implement interpolation/extrapolation logic here
                printf("Estimated Hatching Time at %.2f C: [IMPLEMENT LOGIC] hrs\n", temp);
                pause_screen();
                break;
            }

            case 2: {
                // Get Required Temperature
                valid_input = 0;
                while (!valid_input) {
                    printf("Enter Desired Hatching Time (hrs): ");
                    if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
                        if (sscanf(input_buffer, "%f", &hatch_time) == 1) {
                            if (hatch_time > 0) {
                                valid_input = 1;
                            } else {
                                printf("Hatching time must be positive.\n");
                            }
                        } else {
                            printf("Invalid input. Please enter a numeric value.\n");
                        }
                    }
                }

                // Placeholder - implement reverse interpolation/extrapolation logic here
                printf("Required Temperature for %.2f hrs: [IMPLEMENT LOGIC] C\n", hatch_time);
                pause_screen();
                break;
            }

            case 3: {
                // Add Data Point
                if (sp->data_count >= MAX_POINTS) {
                    printf("Maximum data points reached (%d). Cannot add more.\n", MAX_POINTS);
                    pause_screen();
                    break;
                }

                // Temperature input
                valid_input = 0;
                while (!valid_input) {
                    printf("Enter Temperature (C): ");
                    if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
                        if (sscanf(input_buffer, "%f", &temp) == 1) {
                            // Check if temperature is within threshold
                            if (temp < sp->min_temp) {
                                printf("ERROR: Temperature %.2f C is below minimum threshold (%.2f C).\n", 
                                       temp, sp->min_temp);
                                printf("Please enter a temperature between %.2f and %.2f C.\n", 
                                       sp->min_temp, sp->max_temp);
                            } else if (temp > sp->max_temp) {
                                printf("ERROR: Temperature %.2f C is above maximum threshold (%.2f C).\n", 
                                       temp, sp->max_temp);
                                printf("Please enter a temperature between %.2f and %.2f C.\n", 
                                       sp->min_temp, sp->max_temp);
                            } else {
                                valid_input = 1;
                            }
                        } else {
                            printf("Invalid input. Please enter a numeric value.\n");
                        }
                    }
                }

                // Hatching time input
                valid_input = 0;
                while (!valid_input) {
                    printf("Enter Hatching Time (hrs): ");
                    if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
                        if (sscanf(input_buffer, "%f", &hatch_time) == 1) {
                            if (hatch_time > 0) {
                                valid_input = 1;
                            } else {
                                printf("Hatching time must be positive.\n");
                            }
                        } else {
                            printf("Invalid input. Please enter a numeric value.\n");
                        }
                    }
                }

                // Add the data point
                sp->data_points[sp->data_count].temperature = temp;
                sp->data_points[sp->data_count].hatch_time = hatch_time;
                sp->data_count++;

                printf("\nData point added successfully!\n");
                printf("Temperature: %.2f C, Hatching Time: %.2f hrs\n", temp, hatch_time);
                printf("Total data points: %d\n", sp->data_count);
                pause_screen();
                break;
            }

            case 4: {
                // View Data
                clear_screen();
                printf("=== DATASET: %s ===\n", sp->species_name);
                printf("Temperature Threshold: %.2f C to %.2f C\n", sp->min_temp, sp->max_temp);
                printf("==================================================\n");

                if (sp->data_count == 0) {
                    printf("No data points available.\n");
                } else {
                    printf("No. | Temperature (C) | Hatching Time (hrs)\n");
                    printf("----|----------------|---------------------\n");
                    for (int i = 0; i < sp->data_count; i++) {
                        printf("%3d | %14.2f | %19.2f\n",
                               i + 1, 
                               sp->data_points[i].temperature, 
                               sp->data_points[i].hatch_time);
                    }
                }

                pause_screen();
                break;
            }

            case 0:
                return;

            default:
                printf("Invalid choice. Please select 0-4.\n");
                pause_screen();
        }
    }
}