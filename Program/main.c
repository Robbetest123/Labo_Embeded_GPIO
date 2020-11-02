#include "PJ_RPI.h"
#include <stdio.h>
#include <mysql/mysql.h>

int main()
{
	if(map_peripheral(&gpio) == -1) 
	{
       	 	printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
        	return -1;
    	}

	// Define gpio 17 as output
	INP_GPIO(17);
	OUT_GPIO(17);

	while(1)
	{
		// Toggle 17 (blink a led!)
		GPIO_SET = 1 << 17;
		printf("AAN\n");
		// code naar db
		sleep(1);

		GPIO_CLR = 1 << 17;
		printf("UIT\n");
		sleep(1);
		
		GPIO_READ(17);
	}

	return 0;	

}
