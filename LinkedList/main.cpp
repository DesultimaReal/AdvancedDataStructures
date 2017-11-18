#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

//Here is the Singly-Linked-List data structure I built from the ground up to practice a bit.
//Capabilitys:
//I Implemented basic appends to the tail with the capability to append a vector of ints as well as single ints.
//I implemented two DeleteDuplicate functions. One is better for time and one is better for memory.
//I implemented a function that looks for the nth to last node in the LL using a slow and fast pointer.
//I Implemented a function to delete a node assuming I only have access to it.
//I Implemented a function to partition a LL around a given number.
//I Implemented a function that looks for loops and returns the node which starts them.
class Node{
public:
    Node * Next = NULL;
    int Data;

    Node(int d){
        Data = d;
    }
};
class LinkedList{
    public:
    Node * head;
    Node * tail;

    LinkedList(int data){
        head = new Node(data);
        tail = head;
    }
    void AppendToTail(int data){
        Node * InsertedNode = new Node(data);
        tail->Next = InsertedNode;
        tail = InsertedNode;
        //cout << "INSERTING: " << data << endl;
        //PrintList();
    }
    void AppendToTail(vector<int> database){
        for(int i : database){
           AppendToTail(i);
        }
    }
    void PrintList(){
        Node * current = head;
        cout << "LL: ";
        while(current != NULL){
            cout << current->Data << "-> ";
            current = current->Next;
        }cout << endl;
    }
    void DeleteNode(int n){
        cout<< "Deleting: " << n << endl;
        Node * Current = head;
        if(Current->Data == n){//IF WE ARE DELETING THE HEAD
            Node * NextNode = head->Next;
            head = NextNode;
            delete Current;//Delete our node now that it is detached from the list
        }
        else{//We are not deleting the head
            while(Current->Next != NULL){
                if(Current->Next->Data == n){//We've found our node to delete, and it is our next node
                    Node * NodeToDelete = Current->Next;//Prep for deletion
                    Current->Next = Current->Next->Next;
                    if(Current->Next == NULL){//If we deleted the tail and Current is our new Tail
                        tail = Current;
                    }
                    delete NodeToDelete;//delete our node now that it is detached from the linked list
                }
                else{//We need to keep checking
                    Current = Current->Next;
                }
            }//Theres no node with the data we are looking to delete
        }
        PrintList();
        }
    //These two functions delete all duplicates in our Linked-List, but do it with different methods, one using more space to save time, one using more time to save space.
    void DeleteDupSpaceIntensive(){
        unordered_set<int> UniqueInts;
        Node * current = head;
        UniqueInts.insert(current->Data);
        while(current->Next != NULL){
            int DupToCheck=current->Next->Data;
            unordered_set<int>::const_iterator it = UniqueInts.find(DupToCheck);
            if (it != UniqueInts.end()){
                Node * NodeToDelete = current->Next;//Prep for deletion
                current->Next = current->Next->Next;
                if(current->Next == NULL){//If we deleted the tail and Current is our new Tail
                    tail = current;
                }
                delete NodeToDelete;//delete our node now that it is detached from the linked list
                PrintList();
            }
            else{//This is our first time seeing it
              current = current->Next;
              UniqueInts.insert(DupToCheck);
            }

        }
    }
    void DeleteDupTimeIntensive(){
        Node * current = head;
        while(current->Next != NULL){//CURRENT IS OUR FIRST NODE AND PROGRESSES FORWARD
            Node * killer = current->Next;
            if(killer->Data == current->Data){//If our first and second match
                current->Next = current->Next->Next;
            }
            while(killer->Next != NULL){
                if(killer->Next->Data == current->Data){//If our first and second match
                    Node * NodeToDelete = killer->Next;//Setup our node to be deleted
                    killer->Next = killer->Next->Next;
                    if(killer->Next == NULL){//If we deleted the tail and Current is our new Tail
                        tail = killer;
                    }
                    cout << "Deleting: " << NodeToDelete->Data << endl;
                    delete NodeToDelete;//delete our node now that it is detached from the linked list
                }
                else{
                    killer=killer->Next;
                }
            }cout<<endl;
            current=current->Next;//MOVE 1 FORWARD
        }cout<<endl;
        PrintList();
    }
    //This function returns the nthToLast node in the set. 0 returns the last node. It uses a fast and slow pointer to accomplish this.
    Node * nthToLast(int k){
        Node * Slow = head;
        Node * Fast = head;
        for(int i = k; i > 0; i--){
            if(Fast == NULL)
                return NULL;
            Fast=Fast->Next;
        }if(Fast == NULL) return NULL;

        while(Fast->Next != NULL){
            Fast = Fast->Next;
            Slow = Slow->Next;
        }
        return Slow;
    }
    //This function deletes a node, assuming you only have access to it. It assumes you are not deleting the head as then there wouldn't be limited access to the Linked List.
    bool deletewithlimitedaccess(Node * ToBeDeleted){
        /*Returns true if it's possible to delete this node with only access to it and no head.
        /Assuming you donnot have access to the front of a LL,
        /and only have access to one specified node,
        /delete said node.*/

        //Check to see if it's possible
        if(ToBeDeleted == NULL || ToBeDeleted->Next == NULL){
            return false;
        }
        //Copy over the node to the right of us and then delete them as we now take their place.
        Node * NextNode = ToBeDeleted->Next;
        ToBeDeleted->Data=NextNode->Data;
        ToBeDeleted->Next=NextNode->Next;
        return true;
    }
    //This function partitions all your nodes by value to the right and left of a value and returns a new partitioned list. I.E. 1->3->2->  (int x)  -> 9->8->10->
    Node * PartitionAroundANode(int Partiation){
        Node * Current = head;
        Node * BeforeStart = NULL;
        Node * AfterStart = NULL;

        while(Current != NULL){
                Node * NextNode = Current->Next;
            if(Current->Data < Partiation){
                Current->Next = BeforeStart;
                BeforeStart = Current;
            }
            if(Current->Data > Partiation){
                Current->Next = AfterStart;
                AfterStart = Current;
            }
            Current = Current->Next;
        }
        if(BeforeStart == NULL){
            return AfterStart;
        }
        //Merge the before partition list and after partition lists
        Node * HeadOfPartition = BeforeStart;
        while(BeforeStart->Next != NULL){
            BeforeStart = BeforeStart->Next;
        }BeforeStart->Next = AfterStart;
        return HeadOfPartition;
    }
    //This function looks for a loop, returns NULL if there is none, and otherwise returns the Node that starts said loop.
    Node * FindLoopStart(){
        Node * Fast = NULL;
        Node * Slow = NULL;

        while(Fast != NULL && Fast->Next != NULL){
            Slow = Slow->Next;
            Fast = Fast->Next->Next;
            if(Slow == Fast){
                break;
            }
        }
        if(Fast == NULL || Fast->Next == NULL){
            return NULL;
        }
        Slow = head;
        while(Slow != Fast){
            Slow = Slow->Next;
            Fast=Fast->Next;
        }
        return Fast;
    }

};
int main()
{
    //Example LL
    LinkedList * L = new LinkedList(10);vector<int> v = {1,7,4,2,7};
    L->AppendToTail(v);
    L->PartitionAroundANode(3);
    L->PrintList();
    cout <<"Head: " <<L->head->Data << endl;
    cout <<"Tail: " <<L->tail->Data << endl;

    //Cleanup
    delete L;

    return 0;
}
