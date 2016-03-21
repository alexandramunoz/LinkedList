//
//  pa2.h
//  pa2
//
//  Created by Alexandra Munoz on 3/20/16.
//  Copyright © 2016 Alexandra Munoz. All rights reserved.
//

#ifndef pa2_h
#define pa2_h

using namespace std;

class Node{
    
public:
    string data;
    bool nodeUsed;
    
    Node * next;
//Node constructor
    Node(string name){
        data = name;
        next = NULL;
        nodeUsed = false;
    }
};

class LinkedList{
    
private:
    Node *head;
    
public:
    //Adds program to linked list using worst fit algorithm
    bool worstAdd(string name, int size){
        bool added = false;
        int pages = 0;
        
        //Determines number of pages needed for program
        if(size % 4 == 0){
            pages = size/4;
        }
        else{
            pages = (size/4) + 1;
        }
        
        Node *temp  = head;
        Node *greatest = temp;
        Node *first = temp;
        int freeNodeCount = 0;
        int largestNodeCount = 0;
        //Sees how many empty nodes are available and where program can be inserted
        while(temp != NULL){
            Node*next = temp->next;
            //Checks to see if space is not used
            if (!temp -> nodeUsed){
                freeNodeCount++;
                //Finds how many free nodes in total in linked list
                if(next == NULL && freeNodeCount > largestNodeCount && freeNodeCount >= pages){
                    freeNodeCount++;
                    largestNodeCount = freeNodeCount;
                    greatest = first;
                    break;
                }
                temp = temp->next;
            }
            //Checks to see if space is used. The whole worst fit algorithm is used to look for where the most space is available to place program
            else if(temp -> nodeUsed){
                freeNodeCount++;
                if(freeNodeCount > pages && freeNodeCount > largestNodeCount){
                    largestNodeCount = freeNodeCount;
                    greatest = first;
                    freeNodeCount = 0;
                    temp = temp-> next;
                    first = temp;
                }
                else if(freeNodeCount <= pages || freeNodeCount <= largestNodeCount){
                    freeNodeCount = 0;
                    temp = temp-> next;
                    first = temp;
                }
            }
        }
        Node*beginning = greatest;
        //If enough space available, start inserting data into needed nodes
        if(largestNodeCount > pages){
            for(int i = 0; i < pages; i++){
                beginning->nodeUsed = true;
                beginning->data = name;
                added = true;
                beginning = beginning->next;
            }
            cout<<"\nProgram " <<name <<" added successfully: " <<pages <<" page(s) used.\n\n";
        }
        else{
            added = false;
        }
        return added;
    }
//Adds program to linked list using best fit algorithm
    bool bestAdd(string name, int size){
        bool added = false;
        int pages = 0;
        
        //Finds number of pages needed to fit program into linked list
        if(size % 4 == 0){
            pages = size/4;
        }
        else{
            pages = (size/4) + 1;
        }
        
        Node *temp  = head;
        Node *greatest = temp;
        Node *first = temp;
        int freeNodeCount = 0;
        int nodeMinimum = 33;
        
        
        while(temp != NULL){
            //Finds number of free nodes available in linked list
            if (!temp->nodeUsed){
                Node*next = temp->next;
                freeNodeCount++;
                if(next == NULL && freeNodeCount < nodeMinimum && freeNodeCount >= pages){
                    freeNodeCount++;
                    nodeMinimum = freeNodeCount;
                    greatest = first;
                    break;
                }
                temp = temp->next;
            }
            else if(temp->nodeUsed){
                freeNodeCount++;
                if(freeNodeCount > pages && freeNodeCount < nodeMinimum){
                    nodeMinimum = freeNodeCount;
                    greatest = first;
                    freeNodeCount = 0;
                    first = temp;
                }
                else{
                    freeNodeCount = 0;
                    temp = temp->next;
                    first = temp;
                }
            }
        }
        Node*beginning = greatest;
        //If consecutive number of pages closes to how many are needed is found, insert data into linked list
        if(nodeMinimum > pages){
            for(int i = 0; i < pages; i++){
                beginning->nodeUsed = true;
                beginning->data = name;
                beginning = beginning->next;
                added = true;
            }
            cout<<"\nProgram " <<name <<" added successfully: " <<pages <<" page(s) used.\n";
        }
        else{
            added = false;
        }
        printList();
        return added;
    }
    
    //Print out linked list
    void printList(){
        string free = "free";
        Node * temp = head;
        int nodeCount = 0;
        int x = 0;
        while(temp != NULL){
            //Print Free to unused nodes
            if(temp->nodeUsed == false){
                cout<<"Free" << " ";
                temp = temp -> next;
                nodeCount++;
            }
            else{
                //Print name of nodes for used nodes
                cout<< temp->data <<" ";
                temp = temp -> next;
                nodeCount++;
            }
            x++;
            if(x%8 == 0){
                cout<<endl;
            }
        }
        cout<<endl;
    }
    
    void frag(){
        int fragCount = 0;
        Node*temp = head;
        Node*lastNode = temp;
        //Determines fragments by finding how many times linked list switches from used node to free node and free node to used node
        while(temp != NULL){
            if(!temp->nodeUsed){
                Node*next = temp->next;
                if(next != NULL){
                    if(next->nodeUsed){
                        fragCount++;
                    }
                }
            }
            lastNode = temp;
            temp = temp-> next;
        }
        bool lastNodeUsed = false;
        lastNodeUsed = lastNode->nodeUsed;
        if(lastNode->nodeUsed){
            cout<<"There are " <<fragCount <<" fragment(s).\n";
        }
        cout<<"There are " <<fragCount + 1<<" fragment(s).\n";
    }
    //Inserts nodes into linked list
    void insertLL(string name){
        //Creates head of linked list
        if(head == NULL){
            head = new Node(name);
            return;
        }
        Node*temp = head;
        //Inserts new nodes
        while (temp -> next != NULL){
            temp = temp -> next;
        }
        temp-> next = new Node(name);
    }
    //Searches linked list to determine if program with desired name already exists
    bool searchForName(string name){
        Node*temp = head;
        while(temp != NULL){
            if(temp->data == name){
                return true;
            }
            temp = temp->next;
        }return false;
    }
    //Deletes program from linked list
    void kill(){
        string name;
        cout<<"Program name - ";
        cin>>name;
        int nodeCount = 0;
        Node *temp = head;
        //Searches linked list to find name and deletes node's data when node with name is found 
        while(temp !=NULL){
            if(temp->data == name){
                temp->data = "";
                temp->nodeUsed = false;
                temp=temp->next;
                nodeCount++;
            }
            else{
                temp = temp->next;
            }
        }
        cout<<"Program " <<name  <<" successfully killed, " <<nodeCount <<" page(s) reclaimed.\n";
    }
    
    
};


#endif /* pa2_h */
