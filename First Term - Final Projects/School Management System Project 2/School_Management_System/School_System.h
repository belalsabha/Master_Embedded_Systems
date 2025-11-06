/*
 * School_System.h
 *
 *  Created on: 2 NOV 2025
 *      Author: Belal
 */

#ifndef SCHOOL_SYSTEM_H_
#define SCHOOL_SYSTEM_H_

#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define SIZE 50 //  size of Buffer
#define DPRINTF(...)		{fflush(stdin);\
							fflush(stdout);\
							printf(__VA_ARGS__);\
							fflush(stdin);\
							fflush(stdout);}
// Structure to represent Student Data
typedef struct {
		char first_name[20];
		char last_name[20];
		unsigned int roll;
		float GPA;
		char course_id[10];
	}S_Std_Data;


	// Structure to represent FIFO buffer
	typedef struct {
		S_Std_Data *Base;        // Ptr from structure type  to buffer base &array[0]
		S_Std_Data *Head;        // Ptr from structure type to next  position (write)
		S_Std_Data *Tail;        // Ptr from structure type to next  position (read)
	    unsigned int Count;    // number of elements in buffer
	} FIFO_BUF;

	// Enum to represent FIFO status
	typedef enum {
	    BUF_NO_ERROR,
	    BUF_FULL,
	    BUF_EMPTY,
	    BUF_NULL
	} BUF_status;
	BUF_status BUF_Status;
extern S_Std_Data Buffer [SIZE];


               /****************APIs*******************/
                       //for FIFO Buffer
BUF_status BUF_INIT(FIFO_BUF* Init_Buf,S_Std_Data* Buf);
BUF_status Is_BUF_FULL(FIFO_BUF *Full_buf);

                     //for displaying
void Display_Menu();
                          //for students
void Add_the_Student_Details_manually(FIFO_BUF* FIFO_Buf);
void Add_the_Student_Details_From_Text_File(FIFO_BUF* FIFO_Buf);
void Find_the_Student_Details_By_Roll_Number(FIFO_BUF* FIFO_Buf);
void Find_the_Student_Details_by_First_Name(FIFO_BUF* FIFO_Buf);

                          // for Courses
void Find_the_Student_Details_by_Course(FIFO_BUF* FIFO_Buf);
void Find_the_Total_number_of_Students(FIFO_BUF* FIFO_Buf);
void Delete_the_Students_Details_by_Roll_Number(FIFO_BUF* FIFO_Buf);
void Update_the_Students_Details_by_Roll_Number(FIFO_BUF* FIFO_Buf);
void Show_all_information(FIFO_BUF* FIFO_Buf);
int check_Roll_Number(FIFO_BUF* FIFO_Buf, int rollNumber);


#endif /* SCHOOL_SYSTEM_H_ */
