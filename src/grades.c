#include "grades.h"

/* Exercise 1 */
/* Function to load student data from file */
void studentsLoadDataFromFile(const char* filename, tStudentsTable *studentsTable, bool *isRead)
{
	FILE *fin=0;
	char line[MAX_LINE];
	char buffer[MAX_LINE];
	tStudent newStudent;
	int i;

	/* Open the input file */
	if ((fin = fopen(filename,"r")) != NULL) {
		/* Read all the students */
        /* Initializations */
		studentsTable -> nStudents = 0;

		while (!feof(fin) && studentsTable -> nStudents < MAX_STUDENTS) {
			/* Remove any content from the line */
			line[0] = '\0';

			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets (line,MAX_LINE - 1, fin);

			/* Ensure that the string is ended by 0*/
			line[MAX_LINE - 1] = '\0';

			if (strlen(line) > 0) {
				/* Obtain the id and name data from file line*/
				sscanf(line, "%d %s %[^\n]s", &newStudent.studentId, newStudent.name, buffer);

				/* Read the grades ant its state and add them to the table */
				for (i = 0; i < NUM_ACTIVITIES; i++) {
                    /* Read mark and state of the activity */
                    sscanf(buffer, "%f %u %[^\n]s", &newStudent.activities[i].mark, &newStudent.activities[i].state, buffer);
                    /* Assign activity name */
                    newStudent.activities[i].name = (i < NUM_CAA_ACTIVITIES) ? (CAA1 + i) : (PR1 + i - NUM_CAA_ACTIVITIES);
				}

				/* Add student to students table*/
				studentsTable -> students[studentsTable -> nStudents] = newStudent;
                /* Increment the counter. */
				studentsTable -> nStudents++;
			}
		}
		/* Close the file */
		fclose(fin);
		*isRead = true;
	}
	else {
		*isRead = false;
	}
}

/* Exercise 2 */
/* Action to calculate a student's CAA and PR marks */
void calculateFinalGrade (tActivity activities[], float *finalCaaMark, float *finalPrMark) {
    tActivityType activityType;
    float activityWeight;
    float caaWeightedMarks;
    float caaWeightsSum;
    float prWeightedMarks;
    float prWeightsSum;
    int i;

    /* Initialize variables */
    caaWeightedMarks = 0.0;
    caaWeightsSum = 0.0;
    prWeightedMarks = 0.0;
    prWeightsSum = 0.0;

    /* Calculate the weighted marks and the summation of weights for CAA and PR */
    for (i = 0; i < NUM_ACTIVITIES; i++) {
        /* Get activity type and weight */
        getActivityInfo(activities[i].name, &activityType, &activityWeight);

        if (activityType == CAA) {
            caaWeightedMarks += activities[i].mark * activityWeight;
            caaWeightsSum += activityWeight;
        } else {
            if (activityType == PR) {
                prWeightedMarks += (activities[i].mark * activityWeight);
                prWeightsSum += activityWeight;
            }
        }
    }

    /* Calculate the final mark for CAA and PR */
    *finalCaaMark = caaWeightsSum > 0 ? caaWeightedMarks / caaWeightsSum : 0.0;
    *finalPrMark = prWeightsSum > 0 ? prWeightedMarks / prWeightsSum : 0.0;
}


/* Exercise 3 */
/* Action that returns the type of activity and its weight */
void getActivityInfo (tActivityName activityName, tActivityType *activityType, float *activityWeight) {
    if (activityName == CAA1) {
        *activityType = CAA;
        *activityWeight = CAA1_WEIGHT;
    } else {
        if (activityName == CAA2) {
            *activityType = CAA;
            *activityWeight = CAA2_WEIGHT;
        } else {
            if (activityName == CAA3) {
                *activityType = CAA;
                *activityWeight = CAA3_WEIGHT;
            } else {
                if (activityName == CAA4) {
                    *activityType = CAA;
                    *activityWeight = CAA4_WEIGHT;
                } else {
                    if (activityName == PR1) {
                        *activityType = PR;
                        *activityWeight = PR1_WEIGHT;
                    } else {
                        if (activityName == PR2) {
                            *activityType = PR;
                            *activityWeight = PR2_WEIGHT;
                        } else {
                            if (activityName == PR3) {
                                *activityType = PR;
                                *activityWeight = PR3_WEIGHT;
                            } else {
                                *activityType = 0;
                                *activityWeight = 0.0;
                            }
                        }
                    }
                }
            }
        }
    }
}



/* Exercise 4 */
/* Action to calculate a student's CAA and PR marks */
void getSubmittedActivities (tActivity activities[], int *caaSubmittedCount, int *prSubmittedCount) {
    tActivityType activityType;
    float activityWeight;

    /* Initialize variables */
    *caaSubmittedCount = 0;
    *prSubmittedCount = 0;

    for (int i = 0; i < NUM_ACTIVITIES; i++) {
        if (activities[i].state == SUBMITTED) {
            /* Get activity type */
            getActivityInfo(activities[i].name, &activityType, &activityWeight);
            if (activityType == CAA) {
                (*caaSubmittedCount)++;
            } else {
                if (activityType == PR) {
                    (*prSubmittedCount)++;
                }
            }
        }
    }
}



/* Exercise 5 */
/* Action that writes a student's ID, name and grades in both numeric and letter format. */
void writeStudentData (tStudent student, float markCaa, float markPr, int nCaa, int nPr) {

	/* Data output */
    printf("%d %s %.2f %.2f %d %d %d\n",
           student.studentId,
           student.name,
           markCaa,
           markPr,
           nCaa,
           nPr,
           areAllPrSubmitted(student.activities));
}


/* Exercise 6 */
/* Function that test all PR activities are submitted */
bool areAllPrSubmitted (tActivity activities[]) {
    for (int i = 0; i < NUM_ACTIVITIES; i++) {
        if (activities[i].name >= PR1 && activities[i].name <= PR3 && activities[i].state != SUBMITTED) {
            return false;
        }
    }
    return true;
}
