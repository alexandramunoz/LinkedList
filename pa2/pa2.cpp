//
//  pa2.cpp
//  pa2
//
//  Created by Alexandra Munoz on 3/14/16.
//  Copyright © 2016 Alexandra Munoz. All rights reserved.
//

#include <iostream>
#include <cstring>
#include "pa2.h"

using namespace std;

int main(int argc, char ** argv){
    string best;
    string worst;
    //Checks to determine whether user correctly inputted arguments to run the program
    if (argc > 2){
        cout<<"You have entered more than 2 arguments when only 2 are allowed.\n";
        return 0;
    }
    if(argc < 2){
        cout<<"You have entered less than 2 arguments when 2 are needed.\n";
        return 0;
    }
    if (argc == 2){
        //If user does not select worst or best fit, do not run program
        if(strcmp(argv[1],"best") != 0 && strcmp(argv[1], "worst") != 0){
            cout<<"Choose best or worst fit\n";
            return 0;
        }
        //Determine worst or best fit
        if (strcmp(argv[1],"best") == 0){
            cout<<"Using best fit algorithm"<<endl;
        }
        if (strcmp(argv[1], "worst") == 0){
            cout<<"Using worst fit algorithm"<<endl;
        }
        //Create new linked list
        LinkedList *linkedList = new LinkedList();
        string free;
        int choice;
            
        int num =0;
        //Create 32 nodes in linked list by calling insert method
        while(num < 32){
            linkedList -> insertLL(free);
            num ++;
        }
        
        do{
            //Gives user options
            cout <<"1. Add program" <<endl;
            cout<<"2. Kill program" <<endl;
            cout<<"3. Fragmentation" <<endl;
            cout<<"4. Print memory" <<endl;
            cout<<"5. Exit" <<endl;
            cout<<endl;
                
            cin>>choice;
            
            if(choice == 1 || choice == 2 || choice == 3 || choice == 4){
                cout<<"choice - ";
                cout<<choice;
                cout<<endl;
            }
            //Adds program if 1 is chosen
            if(choice == 1){
                string name;
                int size;
                //Asks user for program name and size
                cout<<"Program name - ";
                cin>>name;
                cout<<"Program size (KB) - ";
                cin>>size;
                
                //If name of program is not already found in linked list,
                if(linkedList->searchForName(name) == false){
                    //If best is used for argument for running
                    if(strcmp(argv[1],"best") == 0){
                        //If not enough memory is available once best fit algoritm is ran
                        if(linkedList->bestAdd(name, size) == false){
                            cout<<"Error, Not enough memory for Program " <<name << "\n";
                        }
                    }
                    //If worst is used for argument for running,
                    if(strcmp(argv[1], "worst") == 0){
                        //If not enough memory is avaialable once worst fit algorithm is ran
                        if(linkedList->worstAdd(name, size) == false){
                            cout<<"Error, Not enough memory for Program " <<name <<"\n";
                        }
                    }
                }
                else{
                    cout<<"Error, Program " <<name <<" already running\n";
                }
            }
            //Kill program if 2 is chosen
            if(choice == 2){
                linkedList->kill();
            }
            //Find number of fragments if 3 is chosen
            if(choice == 3){
                linkedList->frag();
            }
            //Print out linked list if 4 is chosen
            if(choice == 4){
                linkedList->printList();
            }
            //Checks for valid choice input
            if(cin.fail() || choice > 5 || choice < 1){
                cout<<"\nThat is not an valid choice option. Please enter an integer between 1 and 5.\n\n";
                }
             //Go through loop until user chooses 5 to quit
            }while(choice != 5);
        }
}
