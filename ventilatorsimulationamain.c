#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "Queue.c"
#include "LinkedList.c"

//parseInput function to parse the argv values
void parseInput(char *argv[],int *numberofpatients,int  *numberofventilators,int *maxarrivaltime,int *maxservicetime){

     if ( argv[1]!= NULL && argv[2]!= NULL && argv[3]!= NULL &&  argv[4]!= NULL) {

          //atoi function to convert string to integers.
         *numberofpatients=atoi(argv[1]);
         *numberofventilators=atoi(argv[2]);
         *maxarrivaltime=atoi(argv[3]);
         *maxservicetime=atoi(argv[4]);
     }

     else{
         printf("Give Proper input through argv values.\n");
         exit(1);
     }

}



//creating a list with random values..
LNode *createpatientlist(int numberofpatients ,int maxarrivaltime,int maxservicetime) {

     LNode *List_Head = NULL;
     LNode *new1;
     int i;
     for (i = 0; i < numberofpatients; i++)
     {
          if(i==0){ //condition for head i.e null value.
               List_Head = createNodeList(List_Head , maxarrivaltime, maxservicetime);
               new1 = List_Head;
               // printf("%d\n", new->arrivaltime);
          }
          else{
               new1 = createNodeList(new1 , maxarrivaltime,maxservicetime);
               // printf("%d\n",new->arrivaltime);
          }
     }
     // arranging the patient list according to arrival time
     sortPatients(List_Head);

     return List_Head;

}



PNode* initialiseSimulator(int* ventilators_available,int numberofventilators){

     int i;
     for ( i = 0; i < numberofventilators; i++)
     {
          ventilators_available[i] = 1; //availability of ventialtors as 1
     }

     PNode* Queue_Head = NULL; //initializing the queue.

     return Queue_Head;
}



PNode* newPatient(LNode** List_Head ,PNode** Queue_Head ){

     //list is already sorted based on arrival time.
     int patienttype = (*List_Head)->patienttype;
     int arrivaltime = (*List_Head)->arrivaltime;
     int servicetime = (*List_Head)->servicetime;
     int servicestarttime = (*List_Head)->servicestarttime;
     int ventilatorID = (*List_Head)->ventilatorID;
     int patientgender = (*List_Head)->patientgender;
     int patientagegroup = (*List_Head)->patientagegroup;

     //putting values from list to queue
     (*Queue_Head) = enqueue( (*Queue_Head) , patienttype , arrivaltime , servicetime , servicestarttime ,ventilatorID ,patientgender,patientagegroup);
     // printf("Queued data = %d\n" ,(*Queue_Head)->arrivaltime);

     //Removing top patient from list
     PopPatientList(List_Head);

     return (*Queue_Head);

}



int EmptyVentilator(int* ventilators_available , int numberofventilators ){

     int i;
     for (i = 0; i < numberofventilators; i++)
     {
          if(ventilators_available[i] != 1 ){
               continue;
          }
          return i; // if  empty return position of  empty ventilator
     }
     return -1; //if all positions are occupied. i.e all ventilators are busy
}



int isVentilatorFull(int* ventilators_available , int numberofventilators ){

     int i;
     for ( i = 0; i < numberofventilators; i++)
     {
          if(ventilators_available[i] == 0 ){ //0 means occupied
               continue;
          }
          return 0; // not full.
     }
     return 1; //if it is full
}



void CopyToReportFromQueue(PNode** Queue_Head ,LNode** Report,  int ventilatorID , int servicestarttime ){

    (*Report)->patienttype =  (*Queue_Head)->patienttype;
    (*Report)->arrivaltime = (*Queue_Head)->arrivaltime;
    (*Report)->servicetime = (*Queue_Head)->servicetime;
    (*Report)->servicestarttime = servicestarttime;
    (*Report)->ventilatorID = ventilatorID;
    (*Report)->patientgender = (*Queue_Head)->patientgender;
    (*Report)->patientagegroup = (*Queue_Head)->patientagegroup;

    (*Report)->nextptr = NULL; // links the next address

}



void CopyToReportFromList(LNode** List_Head ,LNode** Report,  int ventilatorID , int servicestarttime ){

    (*Report)->patienttype =  (*List_Head)->patienttype;
    (*Report)->arrivaltime = (*List_Head)->arrivaltime;
    (*Report)->servicetime = (*List_Head)->servicetime;
    (*Report)->servicestarttime = servicestarttime;
    (*Report)->ventilatorID = ventilatorID;
    (*Report)->patientgender = (*List_Head)->patientgender;
    (*Report)->patientagegroup = (*List_Head)->patientagegroup;

    (*Report)->nextptr = NULL; // links the next address
}



void reportStatistics(LNode* Report_Head ,int numberofpatients, int numberofventilators){

     int severe=0,moderate=0,mild=0, patientsOnEachVentilator[numberofventilators]; //S=1,D=2,M=3
     int completionTime , waitingTime[numberofpatients] , numberofMales , numberofFemales; //0 male 1 female
     int numberofElderly ,numberofAdults , numberofYoungs;  // 0 elderly 1 adult 2 young
     int maxwaittime=0;
     float waittime=0;
     float avgwaittime;
     int maxcompletiontime=0;
     int i;

     for (i = 0; i < numberofventilators; i++)
     {
          patientsOnEachVentilator[i] = 0 ;
     }

     int patientno=0;

     while(Report_Head != NULL){

          if(Report_Head->patienttype == 3){
               severe++;
          }
          else if (Report_Head->patienttype == 2)
          {
               moderate++;
          }
          else if(Report_Head->patienttype == 1){
               mild++;
          }

          patientsOnEachVentilator[Report_Head->ventilatorID]++;

          completionTime = Report_Head->servicestarttime + Report_Head->servicetime;

          if(completionTime >= maxcompletiontime ){
               maxcompletiontime = completionTime;
          }

          waitingTime[patientno] = Report_Head->servicestarttime - Report_Head->arrivaltime;
          waittime += waitingTime[patientno];

          if(waitingTime[patientno] >= maxwaittime ){
               maxwaittime = waitingTime[patientno];
          }

          if(Report_Head->patientgender == 0){
               numberofMales++;
          }
          else if (Report_Head->patientgender == 1)
          {
               numberofFemales++;
          }

          if(Report_Head->patientagegroup == 0){
               numberofElderly++;
          }
          else if (Report_Head->patientagegroup == 1)
          {
               numberofAdults++;
          }
          else if(Report_Head->patientagegroup == 2){
               numberofYoungs++;
          }

          patientno++;
          Report_Head = Report_Head->nextptr;
     }

     printf("*****************Report*****************\n");
     printf("The number of ventilators: %d\n",numberofventilators);
     printf("The number of patients: %d\n",numberofpatients);
     printf("Number of patients of each type: \n");
     printf("Severe: %d\n",severe);
     printf("Moderate: %d\n",moderate);
     printf("Mild: %d\n",mild);
     printf("Number of patients for each ventilator:\n");


     for (i = 0; i < numberofventilators; i++) {

          printf("Ventilator %d : %d\n", i+1, patientsOnEachVentilator[i]);
     }

     printf("Completion time: %d\n",maxcompletiontime);

     avgwaittime = (float)waittime/(float)numberofpatients;
     printf("Average time spent in the queue: %.2f\n" , avgwaittime);
     printf("Maximum waiting time: %d\n" , maxwaittime);

     if(numberofMales > numberofFemales) {
          printf("Most Gender Usage: Male\n");
     }
     else if (numberofFemales > numberofMales){
          printf("Most Gender Usage: Female\n");
     }
     else{
          printf("Most Gender Usage: Equal Usage Male/Female\n");
     }

     if (numberofElderly >= numberofAdults && numberofElderly >= numberofYoungs)
        printf("Most Age Usage : Elderly");

    if (numberofAdults >= numberofElderly && numberofAdults >= numberofYoungs)
        printf("Most Age Usage : Adults");

    if (numberofYoungs >= numberofElderly && numberofYoungs >= numberofAdults)
        printf("Most Age Usage : Youngs");

}



LNode* servePatient(LNode* List_Head , PNode* Queue_Head ,int* ventilators_available , int numberofventilators , int maxarrivaltime , int maxservicetime){

     int flag=1;
     LNode* Report = (LNode*)malloc(sizeof(LNode)); //to maintain report list at the end.
     LNode* Report_Head; //saving the report head.

     int first_patient_arrival_time = List_Head->arrivaltime; //first patient arrival time for loop.
     int completion_time[numberofventilators]; //maintains completion time of ventilators
     int i;
     for (i = 0; i < numberofventilators; i++)
     {
          completion_time[i] = -1; //initializing completetion of service time of ventialtors to -1
     }

     // printf("\t Ventilator Completion\n"); //use for checking

     //maintaining time simulation for the queue.
     for (i = first_patient_arrival_time; ; i++)
     {
          //breaking for loop when patient list is complete and queue empties
          if(List_Head == NULL && isQueueEmpty(Queue_Head)){
               break;
          }

          // condition where two/more patients at same arrival time.
          if(List_Head != NULL && i > List_Head->arrivaltime ){
               i = List_Head->arrivaltime;
               // printf("Repeated i value is %d\n",i);
          }

          //check whether any service of ventilator is completed.
          int j;
          for (j = 0; j < numberofventilators; j++)
          {
               if(completion_time[j] == i){ //if ventilator is empty at time i then...

                   if(!isQueueEmpty(Queue_Head)){  //if queue has patients then add them first.

                         completion_time[j]= i + Queue_Head->servicetime;

                         LNode* temp;
                         temp = (LNode*)malloc (sizeof(LNode)); //maintaining a list for reportStatistics.
                         Report->nextptr = temp;
                         CopyToReportFromQueue(&Queue_Head, &temp , j , i);
                         Report = temp;

                         dequeue(&Queue_Head);
                         // printf("At time %d - \t%d\t",i, j);
                         // printf("%d\n", completion_time[j]);
                   }
                   else{
                         ventilators_available[j] = 1; //if queue has no patients then make ventilators free.
                         completion_time[j] = 0;
                   }
               }
          }

          //At arrival time of a patient.
          if(List_Head!= NULL && i == List_Head->arrivaltime ){

               if( isVentilatorFull(ventilators_available , numberofventilators) != 1 ){ //if ventilator is not full

                    if(!isQueueEmpty(Queue_Head)){

                         Queue_Head = newPatient(&List_Head , &Queue_Head ); //If Queue not empty wait in queue;

                    }
                    else{   //If queue  is empty
                         int ventilator_no = EmptyVentilator(ventilators_available , numberofventilators); //position of empty ventilator

                         ventilators_available[ventilator_no] = 0;    //making ventilator not available
                         completion_time[ventilator_no] = List_Head->arrivaltime + List_Head->servicetime;

                         //adding Patient to report list.
                         LNode* temp = Report;
                         if(flag == 0){
                              temp = (LNode*)malloc (sizeof(LNode)); //maintaining a list for reportStatistics.
                              Report->nextptr = temp;
                         }
                         CopyToReportFromList(&List_Head, &temp , ventilator_no , i);
                         Report = temp;

                         //Saving report head
                         if(i==first_patient_arrival_time && flag == 1){
                              Report_Head = Report;
                              flag = 0;
                         }

                         PopPatientList(&List_Head); //removing patient from list

                         // printf("At time %d - \t%d\t",i ,ventilator_no);
                         // printf("%d\n", completion_time[ventilator_no]); //used for checking
                    }
               }
               else{ //If ventilator is full
                    Queue_Head = newPatient(&List_Head , &Queue_Head); //adding to queue;
                    // printf("At time %d - \t queued \n",i );
               }

          }

     }

     return Report_Head;

}





int main(int argc, char *argv[]){

     int numberofpatients,numberofventilators,maxarrivaltime,maxservicetime;
     parseInput(argv,&numberofpatients,&numberofventilators,&maxarrivaltime,&maxservicetime);


     //creating a list of patients
     LNode* head_of_list;
     head_of_list = createpatientlist(numberofpatients,maxarrivaltime,maxservicetime);

     // displayPatients(head_of_list); // use while checking/debugging


     PNode* head_of_queue;
     int ventilators_available[numberofventilators]; //available ventilators array



     head_of_queue = initialiseSimulator(ventilators_available,numberofventilators);


     //takes a patient from the queue based on the queue to ventilator.
     // newpatient function inside servepatient
     LNode* Report_Head = servePatient( head_of_list , head_of_queue ,ventilators_available, numberofventilators , maxarrivaltime , maxservicetime);


     //to calculate report using final list of Report_Head.
     // displayPatients(Report_Head); // use while checking/debugging
     reportStatistics(Report_Head , numberofpatients ,numberofventilators);



     return 0;
}
