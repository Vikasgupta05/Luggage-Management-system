#include <stdio.h>
#include <stdlib.h>
#include <time.h>          
#include "charges.h"        

// Node structure for queue
struct node {
    int bag_id;
    int weight;
    struct node *next;
};

struct node *check_in[4] = {NULL, NULL, NULL, NULL};
struct node *check_out[4] = {NULL, NULL, NULL, NULL};

// Function to get current timestamp as string
void get_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

// Enqueue function 

void enqueue(int id, int wt, int counter) {
    if (counter < 1 || counter > 4) {
        printf("Invalid counter number.\n");
        return;
    }

    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    ptr->bag_id = id;
    ptr->weight = wt;
    charges(ptr->weight);
    ptr->next = NULL;

    int idx = counter - 1;
    if (check_in[idx] == NULL && check_out[idx] == NULL) {
        check_in[idx] = check_out[idx] = ptr;
    } else {
        check_out[idx]->next = ptr;
        check_out[idx] = ptr;
    }

    // Log to file
    FILE *fp = fopen("bags_log.txt", "a");
    if (fp != NULL) {
        char timestamp[50];
        get_timestamp(timestamp, sizeof(timestamp));
        fprintf(fp, "[%s] CHECK-IN | Counter: %d | Bag ID: %d | Weight: %d\n", timestamp, counter, id, wt);
        fclose(fp);
    }

    // Display trolley
    printf("\nTrolley at Counter %d:\n", counter);
    printf("====================================================================\n");
    struct node *temp = check_in[idx];
    printf("<-");
    while (temp) {
        printf("__%d__", temp->bag_id);
        temp = temp->next;
    }
    printf("<-\n");
    printf("====================================================================\n");
}

// Dequeue function with logging
int dequeue(int counter) {
    if (counter < 1 || counter > 4) {
        printf("Invalid counter number.\n");
        return -1;
    }

    int idx = counter - 1;
    if (check_in[idx] == NULL) {
        printf("\nUnderflow (No bags at Counter %d)\n", counter);
        return -1;
    }

    struct node *temp = check_in[idx];
    int fee = charges(temp->weight);

    // Show trolley before checkout
    printf("\nTrolley at Counter %d before checkout:\n", counter);
    printf("====================================================================\n");
    struct node *display_temp = check_in[idx];
    printf("<-");
    while (display_temp) {
        printf("__%d__", display_temp->bag_id);
        display_temp = display_temp->next;
    }
    printf("<-\n");
    printf("====================================================================\n");

    int input;
    printf("Enter charges you have to pay: ");
    scanf("%d", &input);
    paid(fee, input);

    // Log to file
    FILE *fp = fopen("bags_log.txt", "a");
    if (fp != NULL) {
        char timestamp[50];
        get_timestamp(timestamp, sizeof(timestamp));
        fprintf(fp, "[%s] CHECK-OUT | Counter: %d | Bag ID: %d | Weight: %d | Charges Paid: %d\n",
                timestamp, counter, temp->bag_id, temp->weight, input);
        fclose(fp);
    }

    int bag_id = temp->bag_id;
    check_in[idx] = check_in[idx]->next;
    free(temp);

    return bag_id;
}

// Display current queue at a counter
void display(int counter) {
    if (counter < 1 || counter > 4) {
        printf("Invalid counter number.\n");
        return;
    }

    int idx = counter - 1;
    if (check_in[idx] == NULL && check_out[idx] == NULL) {
        printf("\nQueue is Empty at Counter %d\n", counter);
        return;
    }

    printf("\nTrolley at Counter %d:\n", counter);
    printf("====================================================================\n");
    struct node *temp = check_in[idx];
    printf("<-");
    while (temp) {
        printf("__%d__", temp->bag_id);
        temp = temp->next;
    }
    printf("<-\n");
    printf("====================================================================\n");
}

// Main program
int main() {
    int choice, bag_id, weight;
    int counter, input;
    int keep_running = 1;
    int bag_count[4] = {0, 0, 0, 0}; // Track bag IDs for each counter

    while (keep_running) {
        printf("1. Check In\n2. Check Out\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n==== Insert Bags ==== \n");
                while (1) {
                    printf("\nCounters:\n1. Air India\n2. Goa to Delhi\n3. Mumbai to Goa\n4. US\n5. Go to Main Menu\n");
                    printf("Select Counter: ");
                    scanf("%d", &counter);

                    if (counter == 5) break;
                    if (counter < 1 || counter > 4) {
                        printf("\nInvalid Counter!\n");
                        continue;
                    }

                    bag_id = ++bag_count[counter - 1];
                    printf("Enter weight of bag to insert: ");
                    scanf("%d", &weight);
                    enqueue(bag_id, weight, counter);
                }
                break;

            case 2:
                printf("\n==== Check Out Bags ==== \n");
                while (1) {
                    printf("\nCounters:\n1. Air India\n2. Goa to Delhi\n3. Mumbai to Goa\n4. US\n5. Go to Main Menu\n");
                    printf("Select Counter: ");
                    scanf("%d", &counter);

                    if (counter == 5) break;
                    if (counter < 1 || counter > 4) {
                        printf("\nInvalid Counter!\n");
                        continue;
                    }

                    int removed_bag = dequeue(counter);
                    if (removed_bag != -1)
                        printf("Checked out bag ID: %d\n", removed_bag);
                    display(counter);
                }
                break;

            default:
                printf("\nInvalid Choice!\n");
                break;
        }

        printf("\nWant to try more? (1: Yes / 0: No): ");
        scanf("%d", &keep_running);
        printf("\n");
    }

    printf("Thank you!\n");
    return 0;
}
