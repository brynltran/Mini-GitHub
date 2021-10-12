#include "miniGit.hpp"
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
namespace fs = std::filesystem;

using namespace std;

Test::Test(){
    cout << "creating .minigit directory" << endl;
    fs::create_directory(".minigit");

    dHead = new doublyNode;                                //sets the doubly list node head to NULL
    dHead->commitNumber = 0;
    dHead->sHead = NULL;
    dHead->prev = NULL;
    dHead->next = NULL;
}
Test::~Test(){
    doublyNode * DLLPTR = dHead;
    while(DLLPTR!= NULL){
        singlyNode * temp = DLLPTR->sHead;
        singlyNode * prev = NULL;
        while(temp!=NULL){
            prev = temp->next;
            delete temp;
            temp = prev;
        }
        doublyNode * TEMP = DLLPTR->prev;
        delete DLLPTR;
        DLLPTR = TEMP;
    }

    fs::remove_all(".minigit");

}

singlyNode * Test::SLLHEAD(){
    return dHead->sHead;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Test::deepCopy(singlyNode *tempSLL){




/////////////////////////////////////////////////////////////////////////////////////
        // dHead->sHead = tempSLL; //redundant because we passed dHead->sHead as tempSLL
        singlyNode * copyHead = new singlyNode; //can always assume there is at least one node in the SLL 
        copyHead->fileName = tempSLL->fileName;
        dHead->sHead = copyHead;
        copyHead->fileVersion = tempSLL->fileVersion;
        // copyHead = false;
        copyHead->next = NULL;
        singlyNode * copyPTR = copyHead;

        tempSLL = tempSLL->next;

        while(tempSLL!= NULL){
            copyPTR->next = new singlyNode;
            copyPTR = copyPTR->next;
            // copyPTR = false;
            copyPTR->fileName = tempSLL->fileName;
            copyPTR->fileVersion = tempSLL->fileVersion;
            copyPTR->next = NULL;

            tempSLL=tempSLL->next;
        }
    return;
}

void Test::askAndRetrieveCommitMessage(){

    string message;
    cin.ignore();
    cout << "Type a short message for this commit: " << endl;

    getline(cin, message);
    dHead->commitMessage = message;
    return;
}



bool Test::needToCommit(){
    if(dHead->commitNumber == 0){
        return false;
    }
    else{
        int x;
        cin >> x;
        bool hasNewFile = false;
        singlyNode * temp = dHead->sHead;
        singlyNode * tempPrev = dHead->prev->sHead;
        while(temp != NULL){
            tempPrev = dHead->prev->sHead;

            while(tempPrev != NULL){
                if(tempPrev->fileName == temp->fileName){

                    ifstream newFile;
                    newFile.open(temp->fileName);

                    ifstream oldFile;
                    string fullFileName = ".minigit/" + temp->fileName + "__" + tempPrev->fileVersion;
                    oldFile.open(fullFileName);

                    string line1, line2;

                    while(getline(newFile, line1)){
                        getline(oldFile, line2);
                        if(line1.compare(line2) != 0){
                            newFile.close();
                            oldFile.close();
                            return true;
                        }
                    }
                    newFile.close();
                    oldFile.close();

                    break;
                }


                tempPrev = tempPrev -> next;
                if(tempPrev == NULL && tempPrev->fileName != temp->fileName){
                    hasNewFile = true;
                    return true;
                }
            }

            temp = temp->next;

        }


    }
    return false;
}


void Test::checkout(){
    if(dHead->commitNumber == 0){
        return;
    }

    cout << "Warning. You are about to override your files. would you still like to checkout?" << endl;
    cout << "type 'yes' or 'no'" << endl;
    string ans;
    cin >> ans;
    if(cin.fail() == true){
        while(cin.fail() == true){
            cin.ignore();
            cin.clear();
            cin >> ans;
        } 
    }
    while(true){
        if(ans == "no" || ans == "No" || ans == "NO" || ans == "nO"){
            cout << "Returning to main menu." << endl;
            return;
        }
        else if(ans == "yes" || ans == "Yes" || ans == "YES" || ans == "YEs" || ans == "yEs" || ans == "yeS"){
            break;
        }
        cin.ignore();
        cin.clear();
        cin >> ans;
    }
    printDLL();
    cout << "Enter a commit number:" << endl;
    cin.ignore();
    cin.clear();
    int x = -1;
    cin >> x;

    while(cin.fail() || x >= dHead->commitNumber || x < 0){
        printDLL();
        cout << "Invalid input. Please enter another commit number" << endl;
        cin.ignore();
        cin.clear();
        cin >> x;
        if(x == dHead->commitNumber){
            cout << "Invalid input. Commit number must be lower than current commit." << endl;
        }
    }
    if(dHead->sHead != NULL){
    singlyNode * tempSingly = dHead->sHead->next;
    singlyNode * tempSinglyPrev = dHead->sHead;
        while(tempSinglyPrev != NULL){
            delete tempSinglyPrev;
            tempSingly = tempSingly->next;
            tempSinglyPrev = tempSingly;
            // tempSinglyPrev = tempSingly;
        }
    dHead->sHead = nullptr;
    }
    doublyNode * tempDLL = dHead;
    while(tempDLL != NULL){
        tempDLL = tempDLL->prev;
        if(tempDLL->commitNumber == x){
            deepCopy(tempDLL->sHead);
            return;
        }
    }
    cout << "SOMETHING WENT WRONG WITH THE CHECKOUT" << endl;
    return;


////////////////////////////////////////////////////////////////////
    // bool needToCommit_ = true;

    // if(needToCommit_==true){
    //     cout << "Warning. You are about to override your files. Would you still like to checkout? Type yes or no" << endl;
    //     string ans;
    //     cin >> ans;
    //     while(cin.fail()==true){
    //         cin.ignore();
    //         cin.clear();
    //         cin >> ans;
    //     }
    //     while(true){
    //         if(ans.compare("Yes") == 0 || ans.compare("yes") == 0 || ans.compare("no") == 0 || ans.compare("No") == 0){
    //             break;
    //         }
    //         cout << "Please enter yes or no." << endl;
    //         cin.ignore();
    //         cin.clear();
    //         cin >> ans;
    //         if(ans.compare("Yes") == 0 || ans.compare("yes") == 0 || ans.compare("no") == 0 || ans.compare("No") == 0){
    //             break;
    //         }
    //     }
    //     if(ans == "No" || ans == "no"){
    //         return;
    //     }
    //     if(ans == "Yes" || ans == "yes"){//hard copy the linked lists 


    //     cout << "Enter a commit number: " << endl;
    //     cin.ignore();
    //     cin.clear();
    //     int x;
    //     cin >> x;
    //     if(x>=dHead->commitNumber){
    //         return;
    //     }
    //     cout << "MADE IT HERE" << endl;
    //     int ACTUALCOMMITNUMBER = x + 1;



    //     doublyNode * DLLPTR = dHead;
    //     singlyNode * HEAD = DLLPTR->sHead; //////////////////

    //     //destruct the SLL;
    //     singlyNode * curr = HEAD;

    //     while(curr != NULL){
    //         singlyNode * next = curr->next;
    //         delete curr;
    //         curr = next;
    //     }

        //now HEAD points


    //     while(DLLPTR->commitNumber!= x){
    //         if(DLLPTR->commitNumber > x){
    //         DLLPTR = DLLPTR->prev;
    //         }
    //         else{
    //             DLLPTR = DLLPTR->next;
    //         }
    //     }
    //     deepCopy(DLLPTR->sHead);
    //     return;



    //     }
    // }
    //     else{
    //         return;
    //     }
            
}
string charToString(char one, char two){
    string temp;
    temp.push_back(one);
    temp.push_back(two);
    return temp;
}

string Test::getLatestFile(string fileName, bool & fileExists){ //given a file name, return the latest version in the repository
    vector <string> fileNames;
    string ans = "00";
    for(auto & x : fs::directory_iterator(".minigit")){
        fileNames.push_back(x.path());
    } // this puts all fileNames into a vector of strings
    int vectorSize = fileNames.size();

        fileExists = false;
        int latestFileVersion = 0;

    for(int i = 0; i < vectorSize; i++){
        int fileNameSize = fileNames[i].size();
        int index = 0;

        string INDIVIDUALFILE = fileNames[i];
        char first = INDIVIDUALFILE[INDIVIDUALFILE.size()-2];
        char second = INDIVIDUALFILE[INDIVIDUALFILE.size()-1];
        string currentVersionNumber = charToString(first, second); //convert to string



        int fileVersion = stoi(currentVersionNumber);

        for(int j = 9; j < fileNameSize -5; j++){
            if(fileNames[i][j]!=fileName[index]){
                break;
            }
            if(j == (fileNameSize-6)){
                fileExists = true;
                if(latestFileVersion < fileVersion){ //king of the hill
                    latestFileVersion = fileVersion;
                    ans = currentVersionNumber;
                }
            }
            index++;
        }

    }
    return ans; //it works

}


void Test::addFile(){ 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Code to initialize
            string fileName;
            cout << "Enter a file to add: " << endl;
            cin >> fileName;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//case to check whether there is the correct file in the directory;
    while(fs::exists(fileName)==false){
        cout << "file does not exist." << endl;
        cout << "Enter a correct file name or type 'return' to exit to the main menu." << endl;
        cin.clear();
        cin.ignore();
        cin >> fileName;
            if(fileName == "return"){
                return;
            }
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//case when file exists in directory and will be the head
    if(dHead->sHead == NULL){
        singlyNode * temp = new singlyNode;
        // temp = false;
        temp->fileName = fileName;
        temp->fileVersion = "00";
        dHead->sHead = temp;
        return;
    }
    singlyNode * prev = NULL;
    singlyNode * curr = dHead->sHead;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//case where it's not the head

    // else{

        while(curr!=NULL){
            if(curr->fileName == fileName){
                
                //check whether it's the same version.



                cout << curr->fileName << " has already been added. Returning to main menu." << endl;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        singlyNode * temp2 = new singlyNode;
        temp2->fileName = fileName;
        temp2->fileVersion = "00";
        prev->next = temp2;
        temp2->next = curr;
        return;
    // }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






void Test::printDLL(){
cout << endl << endl;
doublyNode * dPointer = dHead;
while(dPointer!=NULL){
    singlyNode * sPointer = dPointer->sHead;
    cout << "commit number: {" <<dPointer->commitNumber << "}       " ;

    while(sPointer!= NULL){
        cout << sPointer->fileName << "__" << sPointer->fileVersion << " -> ";
        sPointer = sPointer->next;
        if(sPointer== NULL){
            cout << "{";
                cout << dPointer->commitMessage;
            cout << "}"; 
        }
    }
    cout <<endl;
    cout <<"|" << endl;
    dPointer = dPointer->prev;
}
    return;
}



void Test::removeFile(){
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//case for if SLL is null

    if(dHead->sHead == NULL){
        cout << "There are no files to be deleted." << endl;
        return;
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//code to initialize
    cout << "Enter a file name to delete" << endl;
    string fileName;
    cin >> fileName;
    singlyNode * curr = dHead->sHead;
    singlyNode * prev = NULL;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//code to find if file is head
    if(curr->fileName == fileName){
        dHead->sHead = curr->next;
        delete curr;
        curr = NULL;
        return;
    }
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//case'
    else{

        while(curr!= NULL){
            if(curr->next == NULL && curr->fileName != fileName){
                cout << " Please enter a valid file name. Enter 'return' to return to the main menu. " << endl;
                cin.clear();
                cin.ignore();
                cin >> fileName;
                    if(fileName == "return"){
                    return;
                    }
                curr = dHead->sHead;
                prev = NULL;
                    if(curr->fileName == fileName){ //case for the head
                        dHead->sHead = curr->next;
                        delete curr;
                        curr = NULL;
                        return;
                    }
            }
            if(curr->fileName == fileName){
                prev -> next = curr->next;
                delete curr;
                curr = NULL;
                return;
            }
                prev = curr;
                curr = curr->next;

        }//while

    cout << "something went wrong " << endl;
    return;

    } //else

}


void Test::commitFiles(){
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool isNewCommit = false;
    string underScore = "__";
    string fullFileName;
    string line, line2;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //case where there are no files to commit
    if(dHead->sHead == NULL){
        cout << "There are no files to commit. " << endl;
        return;
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//case where it's the first commit
//1)while loop to copy every file and give them a name
//1.5) Need to open a file using fstream
//2) also make sure to update their file version using stoi
//3) update commit number, the heads
//4) make a new DLL Node
//5) make sure to close files

    if(dHead->commitNumber == 0){
        // dHead->commitNumber = 1;
        singlyNode * temp = dHead->sHead;
        while(temp!= NULL){
            if(stoi(temp->fileVersion) < 10)//this if statement will make it so we can add a max of 99 files without getting a bug (not important here since its the head)
            {
                ofstream newFile;
                ifstream oldFile;
                // fullFileName = ".minigit/0" + temp->fileVersion + underScore + temp->fileName;
                fullFileName = ".minigit/" + temp->fileName + underScore + temp->fileVersion ;
                newFile.open(fullFileName);
                oldFile.open(temp->fileName);

                while(getline(oldFile, line)){
                    newFile << line;
                    newFile << "\n";
                }
                oldFile.close();
                newFile.close();
                //increment?
                temp->fileVersion = "00";
            }
            temp = temp->next;

        }
        askAndRetrieveCommitMessage();
        doublyNode * newDLL = new doublyNode;
        newDLL->next = NULL;
        dHead->next = newDLL;
        newDLL->prev = dHead;
        newDLL->commitNumber = 1;
        //now hard copy the singlylinkedlist
        singlyNode * tempSLL = dHead->sHead;


        singlyNode * copyHead = new singlyNode; //can always assume there is at least one node in the SLL 
        // copyHead = false;
        copyHead->fileName = tempSLL->fileName;
        copyHead->fileVersion = tempSLL->fileVersion;
        copyHead->next = NULL;
        singlyNode * copyPTR = copyHead;

        tempSLL = tempSLL->next;

        while(tempSLL!= NULL){
            copyPTR->next = new singlyNode;
            // copyPTR = false;
            copyPTR = copyPTR->next;
            copyPTR->fileName = tempSLL->fileName;
            copyPTR->fileVersion = tempSLL->fileVersion;
            copyPTR->next = NULL;

            tempSLL=tempSLL->next;
        }
        newDLL->sHead = copyHead;
                // askAndRetrieveCommitMessage();
        dHead = newDLL;
        // askAndRetrieveCommitMessage();
        return;
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//case where the commit isnt zero
//1)Make a while loop of pointer to the SLL head
//2)iterate each SLL and check whether this is the file's first time being committed
//3)do everything from last step
    else{

        isNewCommit = false;
        bool fileFound = false;
        bool FILESARETHESAME = true;
        doublyNode * DLLPTR = dHead;
        DLLPTR = DLLPTR->prev;
        singlyNode * tempSCURR = dHead->sHead;

        singlyNode *testForRemoval = DLLPTR->sHead;

        while(testForRemoval != NULL){ //reset all the previous commit's nodes
            testForRemoval->wasChecked = false;
            testForRemoval = testForRemoval->next;
        }


        while(tempSCURR !=NULL){
                            fileFound = false;
                            singlyNode * tempS = DLLPTR->sHead;
                            while(tempS!= NULL){
                                if(tempS->fileName == tempSCURR->fileName){/////////////
                                tempS->wasChecked = true;
                                fileFound = true;
                                    fullFileName = ".minigit/" + tempS->fileName + underScore + tempS->fileVersion;

                                    ifstream oldVersion;
                                    oldVersion.open(fullFileName);

                                    ifstream newVersion;
                                    newVersion.open(tempS->fileName);

                                    bool isNewFile = false;

                                    while(std::getline(newVersion, line)){
                                        std::getline(oldVersion, line2);
                                        if(line2 != line){ //if the files are not the same. 1)
                                            isNewCommit = true;
                                            isNewFile = true;
                                            // FILESARETHESAME = false;
                                            break;
                                        }
                                    }
                                    std::getline(oldVersion,line);

                                    if(isNewFile == true){
                                        int x = stoi(tempSCURR->fileVersion);
                                        if(x <=8){
                                            x++;
                                            tempSCURR->fileVersion = "0";
                                            tempSCURR->fileVersion += to_string(x);
                                        }
                                        else if (x >=9){
                                            x++;
                                            tempSCURR->fileVersion = to_string(x);
                                        }
                                        // cout << temp->fileVersion << "--------------------------------" << endl;
                                        ofstream NEWFILE;
                                        fullFileName = ".minigit/" + tempSCURR->fileName + underScore + tempSCURR->fileVersion;
                                        NEWFILE.open(fullFileName);
                                        ifstream currentFile;
                                        currentFile.open(tempSCURR->fileName);
                                            while(std::getline(currentFile, line)){
                                                NEWFILE << line;
                                                NEWFILE << "\n";
                                            }
                                        currentFile.close();
                                        NEWFILE.close();
                                    }

                                    else if(isNewFile == false){
                                        //do nothing
                                    }
                                oldVersion.close();
                                newVersion.close();
                                }
                                // tempS = tempS->next;
                                if(tempS->next == NULL && fileFound == false){ //if it's a new file

                                    //check to see its latest version
                                    bool fileExistsAlready;

                                    tempSCURR ->fileVersion = getLatestFile(tempSCURR->fileName, fileExistsAlready);
                                    bool isDifferentVersion = false;
                                                                                                                                                        // int x;
                                                                                                                                                        //  cin >> x;

                                    if(fileExistsAlready == true){

                                    
                                        ifstream asdf;
                                        asdf.open(tempSCURR->fileName);

                                        ifstream qwer;

                                        string fileNAME = ".minigit/" + tempSCURR->fileName + underScore + tempSCURR->fileVersion;

                                        qwer.open(fileNAME);

                                        while(getline(qwer, line)){
                                            getline(asdf, line2);
                                            if((line.compare(line2) != 0)){
                                                isDifferentVersion = true;
                                                if(isDifferentVersion == true){
                                                }
                                            }
                                        }
                                       getline(qwer,line2);

                                        if(line2.compare(line) == false){
                                                                                                                                                        //                                             if(isDifferentVersion == false){
                                                                                                                                                        //     cout << false << endl;
                                                                                                                                                        // }
                                                                                                                                                        // else{
                                                                                                                                                        //     cout << true << endl;
                                                                                                                                                        // }

                                            // cout << "OLDERVERSION----------------------------------------------------------" << line2 << endl;
                                            isDifferentVersion = true;
                                        }
                                        qwer.close();
                                        asdf.close();
                                    
                                    }


                                    if(isDifferentVersion == true){
                                        // cout << "--------------------------------THIS IS A DIFFERENT VERSION" << endl;
                                        int x; 
                                        cin >> x;
                                        char one = tempSCURR->fileVersion[0];
                                        char two = tempSCURR->fileVersion[1];

                                        char oneN = one - 48;
                                        char twoN = two-48;

                                        int newNum = oneN*10 + twoN;
                                        newNum++;

                                        if(newNum <10){
                                            tempSCURR->fileVersion = "0" + to_string(newNum);
                                        }
                                        else{
                                            tempSCURR->fileVersion = to_string(newNum);
                                        }
                                    isNewCommit = true;
                                    ofstream NEWFILE_;
                                    string fileName_ = ".minigit/" + tempSCURR->fileName + underScore + tempSCURR->fileVersion;
                                    
                                    ifstream OLDFILE_;
                                    OLDFILE_.open(tempSCURR->fileName);
                                    NEWFILE_.open(fileName_);

                                    while(std::getline(OLDFILE_, line)){
                                        NEWFILE_ << line;
                                        NEWFILE_ << "\n";
                                    }

                                    OLDFILE_.close();
                                    NEWFILE_.close();




                                    }


                                    if(isDifferentVersion == false){
                                    isNewCommit = true;
                                    ofstream NEWFILE_;
                                    string fileName_ = ".minigit/" + tempSCURR->fileName + underScore + tempSCURR->fileVersion;
                                    
                                    ifstream OLDFILE_;
                                    OLDFILE_.open(tempSCURR->fileName);
                                    NEWFILE_.open(fileName_);

                                    while(std::getline(OLDFILE_, line)){
                                        NEWFILE_ << line;
                                        NEWFILE_ << "\n";
                                    }

                                    OLDFILE_.close();
                                    NEWFILE_.close();
                                    }

                                }
                                tempS = tempS->next;
                            }


                            tempSCURR = tempSCURR->next;
        }

        //now update commit and DLL
        if(isNewCommit == false){
            cout << "There were no new changes to commit." << endl;
            return;
        }
        else if(isNewCommit == true){
            askAndRetrieveCommitMessage();
        doublyNode * newDLL = new doublyNode;
        newDLL->next = NULL;
        // askAndRetrieveCommitMessage();
        dHead->next = newDLL;
        newDLL->prev = dHead;
        newDLL->commitNumber =dHead->commitNumber + 1;
        //now hard copy the singlylinkedlist
        singlyNode * tempSLL = dHead->sHead;


        singlyNode * copyHead = new singlyNode; //can always assume there is at least one node in the SLL 
        copyHead->fileName = tempSLL->fileName;
        copyHead->fileVersion = tempSLL->fileVersion;
        // copyHead = false;
        copyHead->next = NULL;
        singlyNode * copyPTR = copyHead;

        tempSLL = tempSLL->next;

        while(tempSLL!= NULL){
            copyPTR->next = new singlyNode;
            copyPTR = copyPTR->next;
            // copyPTR = false;
            copyPTR->fileName = tempSLL->fileName;
            copyPTR->fileVersion = tempSLL->fileVersion;
            copyPTR->next = NULL;

            tempSLL=tempSLL->next;
        }
        newDLL->sHead = copyHead;
        dHead = newDLL;
        return;

        }
    }
}
