

typedef struct priorityNode {

    int patienttype;
    int arrivaltime;
    int servicetime;
    int servicestarttime;
    int ventilatorID;
    int patientgender;
    int patientagegroup;
    int priority; // Higher values indicate higher priority
    struct priorityNode* next;

} PNode; //PNode represents PriorityQueue Node.


// Function prototypes
PNode* NewNode(int , int  ,int ,int ,int ,int ,int ,int   );
void dequeue(PNode**) ;
PNode* enqueue(PNode* , int  ,int ,int ,int ,int ,int ,int );
int isQueueEmpty(PNode* ) ;
