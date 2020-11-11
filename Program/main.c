#include "PJ_RPI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// void finish_with_error(MYSQL *conn){
//         fprintf(stderr, "%s\n",mysql_error(conn));
//         mysql_close(conn);
//         exit(1);
//     }

// int main(int args, char **argv)
// {
// 	MYSQL *conn = mysql_init(NULL);
	
// 	if(conn == NULL)
// 	{
// 		fprintf(stderr, "%s\n",mysql_error(conn));
//         mysql_close(conn);
//         exit(1);
// 	}

// 	if(mysql_real_connect(conn,"Localhost","pi","raspberry","Lab_embeded2_1",0,NULL,0) == NULL)
// 	{
// 		fprintf(stderr, "%s\n",mysql_error(conn));
//         mysql_close(conn);
//         exit(1);
// 	}

// 	int status =1;
// 	char operation[56];

// 	INP_GPIO(27);

// 	while(1){

// 		if(GPIO_READ(27) == 1){
// 			printf("de pin is hoog");
// 		}
// 		else{
// 			printf("de pin is laag");
// 		}
// 		scanf("fdkjsgb");
		
// 		// sprintf(operation,"INSERT INTO GPIO_Uitlezen VALUES(NULL,%d,%d,NULL)",status); // versturen naar db
// 		// if (mysql_query(conn,operation)) {
// 		// finish_with_error(conn);
// 		// }
// 	}
	

// 	mysql_close(conn);
//   	exit(0);
// }


int main()
{
	if(map_peripheral(&gpio) == -1) 
	{
       	 	printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
        	return -1;
    	}

	// Define gpio 17 as output
	// INP_GPIO(17);
	// OUT_GPIO(17);
	int oudestatus = 0;
	int nieuwestatus = 0;

	INP_GPIO(26);
	while(1)
	{
		
		if(GPIO_READ(26))
		{
			nieuwestatus = 1;
		}
		else
		{
			nieuwestatus = 0;
		}
		
		if(oudestatus != nieuwestatus)
		{
			if(GPIO_READ(26)){
			printf("de pin is hoog\n");
			}
			else{
			printf("de pin is laag\n");
			}
			oudestatus = nieuwestatus;
		}
		
		
			

	}

	return 0;	

}
