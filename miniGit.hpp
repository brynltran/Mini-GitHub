#ifndef TEST_HPP
#define TEST_HPP
#include <iostream>
#include <filesystem>
#include <vector>


struct singlyNode;

struct doublyNode{
    int commitNumber;
    std::string commitMessage;
    singlyNode * sHead;
    doublyNode * prev;
    doublyNode * next;
};

struct singlyNode{
    public:
    std::string fileName;
    std::string fileVersion;
    singlyNode * next;
    // private:
    bool wasChecked;

};

class Test{
    public:
    Test();
    ~Test();/////////////////////////////////////////////////////////////////////////
    void addFile();
    void printDLL();
    singlyNode * SLLHEAD();
    void removeFile();
    void commitFiles();
    std::string getLatestFile(std::string fileName, bool & exists); //return fileVersion as a string //
    void askAndRetrieveCommitMessage();
    bool needToCommit();
    void deepCopy(singlyNode * copy);
    void checkout();

    private:
    doublyNode * dHead;
    // void askAndRetrieveCommitMessage();
    // std::string getMessage(char*);
};



#endif
