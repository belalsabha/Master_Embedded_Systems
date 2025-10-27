/*
 * main.c
 *
 *  Created on: 3 Oct 2025
 *      Author: Eng - Belal Hani Abu Sabha
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Sdata {
    int ID;
    char NAME[30];
    float height;
};

struct Sstudent {
    struct Sstudent *P_nextStudent;
    struct Sdata *P_student;
};

struct Sstudent *GP_FirstStd = NULL;

/*----------------------------------*/
void Fill_Data(struct Sstudent *New_Std) {
    char array[20];

    printf("\n-------- Enter ID : -------- ");
    gets(array);
    New_Std->P_student->ID = atoi(array);

    printf("\n-------- Enter Full Name : -------- ");
    gets(New_Std->P_student->NAME);

    printf("\n-------- Enter Height : -------- ");
    gets(array);
    New_Std->P_student->height = atof(array);
}

/*----------------------------------*/
void Add_Std() {
    struct Sstudent *P_LastStd, *P_NewStd;

    P_NewStd = (struct Sstudent*) malloc(sizeof(struct Sstudent));
    P_NewStd->P_student = (struct Sdata*) malloc(sizeof(struct Sdata));
    P_NewStd->P_nextStudent = NULL;

    Fill_Data(P_NewStd);

    if (GP_FirstStd == NULL) {
        GP_FirstStd = P_NewStd;
    } else {
        P_LastStd = GP_FirstStd;
        while (P_LastStd->P_nextStudent)
            P_LastStd = P_LastStd->P_nextStudent;
        P_LastStd->P_nextStudent = P_NewStd;
    }
}

/*----------------------------------*/
int Delete_Std() {
    char array[20];
    int selected_ID;

    printf("\n-------- Enter Student ID for Deleting it : -------- ");
    gets(array);
    selected_ID = atoi(array);

    struct Sstudent *P_Current = GP_FirstStd;
    struct Sstudent *P_Previous = NULL;

    while (P_Current) {
        if (P_Current->P_student->ID == selected_ID) {
            if (P_Previous) 
                P_Previous->P_nextStudent = P_Current->P_nextStudent;
            else 
                GP_FirstStd = P_Current->P_nextStudent;

            free(P_Current->P_student);
            free(P_Current);
            printf("\nStudent Deleted Successfully!\n");
            return 1;
        }
        P_Previous = P_Current;
        P_Current = P_Current->P_nextStudent;
    }
    printf("\n-------- Cannot find Student ID --------\n");
    return 0;
}

/*----------------------------------*/
void Display_Std() {
    int count = 0;
    struct Sstudent *P_CurrentStd = GP_FirstStd;

    if (GP_FirstStd == NULL) {
        printf("\n-------- List is Empty --------\n");
        return;
    }

    while (P_CurrentStd) {
        printf("\nRecord Number: %d", ++count);
        printf("\nID: %d", P_CurrentStd->P_student->ID);
        printf("\nName: %s", P_CurrentStd->P_student->NAME);
        printf("\nHeight: %.2f\n", P_CurrentStd->P_student->height);

        P_CurrentStd = P_CurrentStd->P_nextStudent;
    }
}

/*----------------------------------*/
void Delete_all_Std() {
    struct Sstudent *P_CurrentStd = GP_FirstStd;

    if (GP_FirstStd == NULL) {
        printf("\n-------- List is Empty --------\n");
        return;
    }

    while (P_CurrentStd) {
        struct Sstudent *P_TempStd = P_CurrentStd;
        P_CurrentStd = P_CurrentStd->P_nextStudent;
        free(P_TempStd->P_student);
        free(P_TempStd);
    }
    GP_FirstStd = NULL;
    printf("\n-------- All Students Deleted --------\n");
}
/*-----------------------------------*/
void GetNth() {
    int count = 1,index; char array[20];
    struct Sstudent *P_CurrentStd = GP_FirstStd;

    if (GP_FirstStd == NULL) {
        printf("\n-------- List is Empty --------");
        return ;
    }
    printf("\nEnter Index");
    gets(array);
    while (P_CurrentStd != NULL) {
        if (count == atoi(array)) {
            printf("\n-------- Student at index %d --------", atoi(array));
            printf("\nID: %d", P_CurrentStd->P_student->ID);
            printf("\nName: %s", P_CurrentStd->P_student->NAME);
            printf("\nHeight: %f", P_CurrentStd->P_student->height);
            return;
        }
        count++;
        P_CurrentStd = P_CurrentStd->P_nextStudent;
    }

    printf("\n-------- Index %d Not Valid --------",atoi(array));
}


/*----------------------------------*/


int getCount(struct Sstudent* head) {
     
    if (head == NULL)
        return 0;
    return 1 + getCount(head->P_nextStudent);
}
/*----------------------------------*/
void ReverseList() {
    struct Sstudent* P_PreviouStd = NULL;
    struct Sstudent* P_CurrentStd = GP_FirstStd;
    struct Sstudent* P_nextStudent = NULL;

    while (P_CurrentStd != NULL) {
        P_nextStudent = P_CurrentStd->P_nextStudent;   
        P_CurrentStd->P_nextStudent = P_PreviouStd;   
        P_PreviouStd = P_CurrentStd;        
        P_CurrentStd = P_nextStudent;         
    }

    GP_FirstStd =P_PreviouStd; 
    printf("\nLinked list reversed successfully");
}

/*----------------------------------*/
int main() {
    char array[20];
    while (1) {
        printf("\n----------------------");
        printf("\n-------- Choose one of THE Following : --------");
        printf("\n1 - ADD Student");
        printf("\n2 - Delete Student");
        printf("\n3 - Display Students");
        printf("\n4 - Delete All Students");
        printf("\n5 - Get Nth Student");
        printf("\n6 - Get Length of List");
        printf("\n7 - Reverse a Linke List");
        printf("\nEnter Your Choice: ");

        gets(array);
        printf("\n----------------------");

        switch (atoi(array)) {
        case 1:
            Add_Std();
            break;
        case 2:
            Delete_Std();
            break;
        case 3:
            Display_Std();
            break;
        case 4:
            Delete_all_Std();
            break;
        case 5:GetNth();
            break;
        case 6:
            printf("Length of Linked List : %d ",getCount( GP_FirstStd));
            break; 
       case 7:ReverseList();
            break;      
        default:
            printf("\nNot Valid Choice");
            break;
        }
    }
    return 0;
}
