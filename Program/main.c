#include "PJ_RPI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void finish_with_error(MYSQL *conn){
        fprintf(stderr, "%s\n",mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

int main(int args, char **argv)
{
	if(map_peripheral(&gpio) == -1) 
	{
       	 	printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
        	return -1;
    	}
		MYSQL *conn = mysql_init(NULL);
	
	if(conn == NULL)
	{
		fprintf(stderr, "%s\n",mysql_error(conn));
        mysql_close(conn);
        exit(1);
	}

	if(mysql_real_connect(conn,"Localhost","pi","raspberry","Lab_embeded2_1",0,NULL,0) == NULL)
	{
		fprintf(stderr, "%s\n",mysql_error(conn));
        mysql_close(conn);
        exit(1);
	}
	char operation[50];
	int pin;
	int oudestatus = 0;
	int nieuwestatus = 0;
	int oudestatusP19 = 0;
	int nieuwestatusP19 = 0;
	INP_GPIO(26);
	INP_GPIO(19);
	while(1)
	{
		// PIO 26 uitlezen + naar db sturen;
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
			printf("de pin 26 is hoog\n");
			pin = 26;
			sprintf(operation,"INSERT INTO GPIO_Uitlezen VALUES(NULL,'%d','%d',NULL)",pin, nieuwestatus); // versturen naar db
			if (mysql_query(conn,operation)) {
			finish_with_error(conn);
			}
			}
			else{
			printf("de pin 26 is laag\n");
			pin = 26;
			sprintf(operation,"INSERT INTO GPIO_Uitlezen VALUES(NULL,'%d','%d',NULL)",pin, nieuwestatus); // versturen naar db
			if (mysql_query(conn,operation)) {
			finish_with_error(conn);
			}
			}
			oudestatus = nieuwestatus;
		}





		// PIO 19 uitlezen + naar db sturen;
		if(GPIO_READ(19))
		{
			nieuwestatusP19 = 1;
		}
		else
		{
			nieuwestatusP19 = 0;
		}
		if(oudestatusP19 != nieuwestatusP19)
		{
			if(GPIO_READ(19)){
			printf("de pin 19 is hoog\n");
			pin = 19;
			sprintf(operation,"INSERT INTO GPIO_Uitlezen VALUES(NULL,'%d','%d',NULL)",pin, nieuwestatus); // versturen naar db
			if (mysql_query(conn,operation)) {
			finish_with_error(conn);
			}
			}
			else{
			printf("de pin 19 is laag\n");
			pin = 19;
			sprintf(operation,"INSERT INTO GPIO_Uitlezen VALUES(NULL,'%d','%d',NULL)",pin, nieuwestatus); // versturen naar db
			if (mysql_query(conn,operation)) {
			finish_with_error(conn);
			}
			}
			oudestatusP19 = nieuwestatusP19;
		}



		
	}

	return 0;	

}
