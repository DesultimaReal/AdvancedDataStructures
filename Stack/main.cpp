#include <iostream>
using namespace std;
//My implementation of the stack data structure with Tower of Hannoi implemented


//Our maximum stack size!
#define MAX 1000

//push(), pop(), esEmpty() and peek() all O(1)
//Last in first out
class Stack{

    int top;
    string label;

    public:
    int a[MAX];
    Stack(string name){
        top = -1;
        label = name;
        cout << "Creating Stack: " << label << endl;
    }
    string printName(){
        return label;
    }
    bool push(int i){
        if(top >= MAX){
            cout << "Stack overflow.\n";
            return false;
        }
        //cout << "pushing to top of "<< label<<": " << i << endl;
        a[++top] = i;
        return true;
    }
    int pop(){
        if(top < 0){
            cout << "Stack overflow.\n";
            return false;
        }
        int x=a[top--];
        return x;

    }
    bool isEmpty(){
        return top < 0;
    }
    void printstack(){

        cout << "Label: " << label << "\nSize: " << top+1 << endl;
        cout<<"________\n";
        for(int i = top; i >= 0; i--){
            cout << a[i] <<" at "<< label <<"[" << i <<"]" << endl;
        }cout<<"________\n\n\n";
    }
    int getSize(){
        return top+1;
    }
};

stackAToB(Stack * A, Stack * B){
    int Pushed = A->pop();
    cout << "Pushing " << Pushed << " from " << A->printName() << " to " << B->printName() << endl;
    B->push(Pushed);
}

void TowersOfHannoi(int Discs, Stack * Start, Stack * Pivot, Stack * End){
    if(Discs == 1){//The final disc and our base case
        stackAToB(Start, End);
    }
    else{
        TowersOfHannoi(Discs-1, Start, End ,Pivot);
        stackAToB(Start, End);
        TowersOfHannoi(Discs-1, Pivot, Start, End);
    }
}
int main()
{
    //Towers of Hannoi using Stacks!
    //This implementation of Towers of Hannoi assumes the initial tower is stacked with decreasing size from top to bottom as it does not do a comparison before moving.
    //If given a properly stacked tower, it obeys all the rules required to solve said problem.

    //Example:
    Stack * Start = new Stack("Start");
    Stack * Pivot = new Stack("Pivot");
    Stack * End = new Stack("End");
    Start->push(3);
    Start->push(2);
    Start->push(1);
    cout << "\n";


    Start->printstack();
    Pivot->printstack();
    End->printstack();

    TowersOfHannoi(Start->getSize(), Start, Pivot, End);

    cout << endl;
    Start->printstack();
    Pivot->printstack();
    End->printstack();

    return 0;
}
