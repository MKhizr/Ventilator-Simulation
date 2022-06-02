#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "LinkedList.h"

LNode* createNodeList(LNode* Prev , int maxarrivaltime , int maxservicetime)
{
   // srand(time(NULL));
    LNode* patient = (LNode* ) malloc (sizeof(LNode));

    patient->patienttype= rand() %3 + 1;  //S=1,D=2,M=3
    patient->arrivaltime= rand() %maxarrivaltime; //within maxarrivaltime
    patient->servicetime= rand() %maxservicetime + 1; //within maxservicetime
    patient->servicestarttime= 0;
    patient->ventilatorID=0;
    patient->patientgender= rand() %2; //0 male 1 female
    patient->patientagegroup=rand() %3; // 0 elderly 1 adult 2 young
    patient->nextptr = NULL; // links the next address

    if(Prev != NULL) //check whether the patient is HEAD/NULL
    {
        Prev->nextptr = patient;
        return patient;
    }
    else{
        // printf("It is the head pointer.");
        Prev = patient;
        return Prev;
    }

}

void displayPatients(LNode* Head)
{
    if(Head == NULL)
    {
        printf(" List is empty.");
    }
    else
    {
        printf("patienttype arrivaltime  servicetime    servicestarttime    ventilatorID     patientgender      patientagegroup\n");
        while(Head != NULL)
        {
            printf(" %d\t\t", Head->patienttype);       // prints the patienttype of current node
            printf(" %d\t\t", Head->arrivaltime);       // prints the arrivaltime of current node
            printf(" %d\t\t", Head->servicetime);       // prints the servicetime of current node
            printf(" %d\t\t", Head->servicestarttime);       // prints the servicestarttime of current node
            printf(" %d\t\t", Head->ventilatorID);       // prints the ventilatorID of current node
            printf(" %d\t\t", Head->patientgender);       // prints the patientgender of current node
            printf(" %d\n", Head->patientagegroup);       // prints the patientagegroup of current node

            Head = Head->nextptr; // advances the position of current node
            if(Head == NULL){
                printf("List ended!\n");
            }
        }
    }
}

void PopPatientList(LNode** List_Head){
    LNode* temp;
    temp = (*List_Head);

    (*List_Head) = (*List_Head)->nextptr;
    free(temp);
}

void sortPatients(LNode* Head)
{
    //using bubble sort to sort patients.
    int a;

    LNode* temp1;
    LNode* temp2;

    for(temp1=Head;temp1!=NULL;temp1=temp1->nextptr)
    {
        for(temp2=temp1->nextptr;temp2!=NULL;temp2=temp2->nextptr)
        {
            if(temp1->arrivaltime >= temp2->arrivaltime){

                a = temp1->patienttype;
                temp1->patienttype = temp2->patienttype;
                temp2->patienttype = a;

                a = temp1->arrivaltime;
                temp1->arrivaltime = temp2->arrivaltime;
                temp2->arrivaltime = a;

                a = temp1->servicetime;
                temp1->servicetime = temp2->servicetime;
                temp2->servicetime = a;

                a = temp1->servicestarttime;
                temp1->servicestarttime = temp2->servicestarttime;
                temp2->servicestarttime = a;

                a = temp1->ventilatorID;
                temp1->ventilatorID = temp2->ventilatorID;
                temp2->ventilatorID = a;

                a = temp1->patientgender;
                temp1->patientgender = temp2->patientgender;
                temp2->patientgender = a;

                a = temp1->patientagegroup;
                temp1->patientagegroup = temp2->patientagegroup;
                temp2->patientagegroup = a;

            }
        }
    }
}

