#include <stdio.h> 
#include <stdlib.h>

///In charges module , checks weight is greater than 50 , less than 20 , between 20 and 50.
// According to weight charges are added and passenger need to pay charges before check out
int charges(int wt)
{
	int fee =100;
	if(wt < 20)
	{
		printf("\n");
		printf("Weight is %d Kg\n",wt);
		printf("You need to pay Rs. %d\n",fee);	
	}
	else if((20 <= wt )&&( wt <= 50))
	{
		printf("\n");
		printf("Weight is %d Kg\n",wt);
		fee = fee+100;
		printf("You need to pay Rs. %d\n",fee);	
	}
	else if(wt > 50)
	{
		printf("\n");
		printf("Weight is %d Kg\n",wt);
		fee = fee+250;
		printf("You need to pay Rs. %d\n",fee);	
	}
	return fee;
}


//Here checks if passenger had paid charges correctly or not 
void paid(int fee,int input)
{
	if(fee == input)
	{
		printf("\nCharges are paid.\n\tThank You :)\n");
	}
	else
	{
		printf("\nOur security can throw you out!!!! \n");
		printf("\nYou need to pay Rs %d\n",fee);
		
		while(fee != input)
		{
			printf("Enter charges you have to pay : ");
			scanf("%d",&input);
			printf("\n");
		}
		printf("\nCharges are paid.\n\tThank You :)\n");
	}
}
