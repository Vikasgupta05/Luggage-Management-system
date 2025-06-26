#include <stdio.h> 
#include <stdlib.h>

// In charges module, checks weight and applies charges accordingly.
// Under 40 kg → No charge; 40–50 kg → ₹100; Over 50 kg → ₹250
int charges(int wt)
{
    int fee = 0;
    
    if (wt < 40)
    {
        printf("\nWeight is %d Kg\n", wt);
        printf("No charges. You are good to go!\n");
    }
    else if (wt <= 50)
    {
        fee = 100;
        printf("\nWeight is %d Kg\n", wt);
        printf("You need to pay Rs. %d\n", fee);	
    }
    else // wt > 50
    {
        fee = 250;
        printf("\nWeight is %d Kg\n", wt);
        printf("You need to pay Rs. %d\n", fee);	
    }
    
    return fee;
}

// Checks if passenger has paid charges correctly
void paid(int fee, int input)
{
    if (fee == 0)
    {
        printf("\nNo payment required. Thank You :)\n");
        return;
    }

    if (fee == input)
    {
        printf("\nCharges are paid.\n\tThank You :)\n");
    }
    else
    {
        printf("\nIncorrect amount paid!\n");
        printf("You need to pay Rs %d\n", fee);
        
        while (fee != input)
        {
            printf("Enter charges you have to pay: ");
            scanf("%d", &input);
            printf("\n");
        }
        printf("\nCharges are paid.\n\tThank You :)\n");
    }
}
