#include "miniGit.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>


using namespace std;

int main(int argc, char * argv[]){

    int option =-1;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Fake Menu to check if .miniGit was initialized
    int optionTemp = -1;
    do{
        cout << endl;
        cout <<"******************************MiniGit******************************" << endl;
        cout << "Option 1. Initialize a Repository" << endl;
        cout << "Option 2. Add files to current commit" << endl;
        cout << "Option 3. Remove files from current commit" << endl;
        cout << "Option 4. Commit changes" << endl;
        cout << "Option 5. See commit history" << endl;
        cout << "Option 6. Checkout" << endl;
        cout << "Option 7. Quit" << endl << endl;
        cin >> optionTemp;
        if(optionTemp == 1){
            break;
        }
        if(optionTemp == 7){
            return 0;
        }
        while(cin.fail()){
            // cout << "Input failed." << endl;
            cin.clear();
            cin.ignore();
            cin >> optionTemp;
        }
        while(optionTemp <=5 && optionTemp >=2){
            cout << "No repository has been initialized. " << endl;
            cin >> optionTemp;
        }
        if(optionTemp == 7){
            return 0;
        }

    }
    while(optionTemp!= 1);
    cout << endl;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Initializing Repository

Test miniGitProgram;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    do{
            option = -1;
            string fileName;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Menu
        cout << endl;
        cout <<"******************************MiniGit******************************" << endl;
        cout << "Option 1. Initialize a Repository" << endl;
        cout << "Option 2. Add files to current commit" << endl;
        cout << "Option 3. Remove files from current commit" << endl;
        cout << "Option 4. Commit changes" << endl;
        cout << "Option 5. See commit history" << endl;
        cout << "Option 6. Checkout" << endl;
        cout << "Option 7. Quit" << endl << endl;
        
        
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Testing
        if(miniGitProgram.SLLHEAD() != NULL){
        cout << "FILES IN CURRENT COMMIT:   ";
        singlyNode * filesToAddTemp123 = miniGitProgram.SLLHEAD();
        while(filesToAddTemp123 != NULL){
            cout << filesToAddTemp123->fileName << "  ";
            filesToAddTemp123 = filesToAddTemp123->next;
        }
        cout << endl << endl;
        miniGitProgram.printDLL();
        }
        cout <<"*******************************************************************" << endl;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        cin >> option;
        while((cin.fail() == true)){ //while loop for invalid cin
            cin.clear();
            cin.ignore();
            cin >> option;
        }
        switch(option){
            case 1: 
            cout << "Repository has already been initialized." << endl;
            break;
            case 2:
            miniGitProgram.addFile();
            break;
            case 3:
            miniGitProgram.removeFile();
            break;
            case 4:

            miniGitProgram.commitFiles();
            break;

            case 5:
            miniGitProgram.printDLL();

            break;

            case 6:
            miniGitProgram.checkout();
            break;

            case 7:
            //DELETE SLL
            miniGitProgram.~Test();
            return 0;
            break;

            default:
            cout << "Invalid Input." << endl;
            break;
        } 

    }
    while(option !=7);
    return 0;
    }

