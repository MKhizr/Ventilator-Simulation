
typedef struct list_node
{
    int patienttype;
    int arrivaltime;
    int servicetime;
    int servicestarttime;
    int ventilatorID;
    int patientgender;
    int patientagegroup;
    struct list_node *nextptr; //Address of the next node

} LNode; //Patient list node


LNode* createNodeList(LNode* Prev , int maxarrivaltime , int maxservicetime);
void displayPatients(LNode* Head);
void PopPatientList(LNode** List_Head);
void sortPatients(LNode* Head);
