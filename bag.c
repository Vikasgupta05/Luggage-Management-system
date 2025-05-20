#include <stdio.h>
#include <stdlib.h>

#include "charges.h" 

// Structure to create a node with bag_id and next pointer
struct node {
    int bag_id;
    int weight;
    struct node *next;
};

struct node *check_in[4] = {NULL, NULL, NULL, NULL};
struct node *check_out[4] = {NULL, NULL, NULL, NULL};

// Function to enqueue a bag
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



// Main function
int main() {
    int choice, bag_id, weight;
    int counter, input;
    int keep_running = 1;
    int bag_count[4] = {0, 0, 0, 0}; // bag ids for 4 counters

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
