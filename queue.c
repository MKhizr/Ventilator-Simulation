#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

// Function to Create A New Node
PNode* NewNode(int priority , int patienttype ,int arrivaltime,int servicetime,int servicestarttime,int ventilatorID,int patientgender,int patientagegroup  )
{
    PNode* temp = (PNode*)malloc(sizeof(PNode));

    temp->priority = priority;

    temp->patienttype = patienttype;
    temp->arrivaltime = arrivaltime;
    temp->servicetime = servicetime;
    temp->servicestarttime = servicestarttime;
    temp->ventilatorID = ventilatorID;
    temp->patientgender = patientgender;
    temp->patientagegroup = patientagegroup;

    temp->next = NULL;

    return temp;
}

// Removes the element with the
// highest priority form the list
void dequeue(PNode** Queue_Head)
{
    PNode* temp = (*Queue_Head);
    (*Queue_Head) = (*Queue_Head)->next;
    free(temp);
    return;
}

// Function to enqueue according to priority
PNode* enqueue(PNode* Queue_Head , int patienttype ,int arrivaltime,int servicetime,int servicestarttime,int ventilatorID,int patientgender,int patientagegroup)
{

    // Create new Node
    //1st parameter i.e patienttype is for priority and 2nd parameter is actual patienttype.
    PNode* temp = NewNode( patienttype , patienttype , arrivaltime, servicetime, servicestarttime, ventilatorID, patientgender, patientagegroup);
    int priority = temp->priority;
    PNode* start;

    if(Queue_Head == NULL){
        // printf("Head node here\n");
        Queue_Head = temp;
        return temp;
    }


    //enqueing node according to priority
    //special case if new temp's priority is more than head.
    if (Queue_Head->priority < priority) {
        // Insert New Node before head
        temp->next = Queue_Head;
        Queue_Head = temp;
        return temp;
    }

    else {

        start = Queue_Head;

        // Traverse the list and find a position to insert new node
        while (start->next != NULL && start->next->priority >= priority) {
            start = start->next;
        }

        // Either at the ends of the list
        // or at required position
        temp->next = start->next;
        start->next = temp;

        // printf("%d %d\n" , start->arrivaltime , start->patienttype);
        return  Queue_Head;
    }
}

// Function to check is list is empty
int isQueueEmpty(PNode* head)
{
    return head == NULL;
}
