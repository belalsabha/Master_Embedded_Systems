/*
 * main.c
 *
 *  Created on: 2 NOV 2025
 *      Author: Belal
 */
#include "School_System.h"

int main(){
	int choice;
	FIFO_BUF StdData;
	BUF_INIT(&StdData,Buffer); // init buffer 
	while(1)
	{
		Display_Menu();
		scanf("%d",&choice);
		printf("-------------------------------------------------------------------\n");
		switch(choice)
		{
		case 1:
		Add_the_Student_Details_manually(&StdData);
		break;
		case 2:
		Add_the_Student_Details_From_Text_File(&StdData);
		break;
		case 3:
		Find_the_Student_Details_By_Roll_Number(&StdData);
		break;
		case 4:
		Find_the_Student_Details_by_First_Name(&StdData);
		break;
		case 5:
		Find_the_Student_Details_by_Course(&StdData);
		break;
		case 6:
		Find_the_Total_number_of_Students(&StdData);
		break;
		case 7:
		Delete_the_Students_Details_by_Roll_Number(&StdData);
		break;
		case 8:
		Update_the_Students_Details_by_Roll_Number(&StdData);
		break;
	    case 9:
	    Show_all_information(&StdData);
		break;
		case 10:
		exit(1);
		break;
		default:
		printf("--------*ERROR Occurred* Enter valid Choice----------\n");
		break;


		}
		printf("-------------------------------------------------------------------\n");
			}






















	return 0;
}
