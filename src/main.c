/*
* File: main.c
* Author: UOC & cterrasid
* Course: 20241
* Description: PR3
*/

/* System header files */
#include "grades.h"

/*Constant for file reading */
#define MAX_FILE_NAME 100+1


/* main */
int main(int argc, char **argv)
{
	tStudentsTable studentsTable;
	int i;
	char filename[MAX_FILE_NAME];
	bool isRead = false;
    float finalCaaMark, finalPrMark;
    int caaSubmittedCount, prSubmittedCount;
	
	/* load data from file*/ 
    printf("LOAD DATA FROM FILE. ENTER FILE NAME >>\n");
    scanf("%s", filename);

    /* Exercise 1 */	
    studentsLoadDataFromFile(filename, &studentsTable, &isRead);
	
	if (isRead) { /* Data successfully loaded */

           printf ("\nRESULTS:\n");
           printf("ID NAME PEC_MARK PR_MARK N_PEC N_PR ALL_PR?(1=YES)\n");
           
           for(i = 0; i < studentsTable.nStudents; i++) {
               /* Exercise 2 */          
               calculateFinalGrade(studentsTable.students[i].activities, &finalCaaMark, &finalPrMark);
               /* Exercise 4 */
               getSubmittedActivities(studentsTable.students[i].activities, &caaSubmittedCount, &prSubmittedCount);
               /* Exercise 5 */
               writeStudentData(studentsTable.students[i], finalCaaMark, finalPrMark, caaSubmittedCount, prSubmittedCount);
           }
		
	}
	else {
		/* No data recovered */
		printf("NO STUDENTS RECOVERED\n");	
	}
		
	return 0;
}
