# Mini-GitHub

Project Goal:
Creating a Miniaturized Version of GitHub that allows the user to 1) Initialize a Repository 2) Add Files to the Current Commit 3) Remove files from the current commit 4) Commit Changes 

In order to use the miniGit, the user must first declare to initialize ./minigit program. 
The program will now allow the user to access any other functions other than initializing the program
and quitting the program.

The user must compile the code with c++ std 17 (in order to use the filesystem library):
g++ -std=c++17 miniGit.cpp driver.cpp



Once the user initializes miniGit, the user will now have access to the 5 remaining functions:

-initializing will create a new doublyLL as well as a .minigit subdirectory.
-The user will not be allowed to access the initialization of miniGit again.

The user now has access to the rest of the main menu, including a list of file in the current commit.

    1) initialize 
Does not do anything. 

    2)add file
-User is prompted to enter a file name to save in the future.
-The user may not enter an incorrect phrase nor a file name that does not exist in the current directory.
-If the user wishes to return to the main menu instead of adding a file, the user may type "return" to do so.
-Once a file is entered, the system will not allow any files with the same name to be added twice. Otherwise,
the system will add the file to the repository structure. The current commit will be shown to the user in the main menu.

    3)Remove a file
-The user is prompted to enter a file name to remove. The user may return to the main menu if he/she wishes to do so.
-The user may not enter a file name that does not exist in the repository structure.

    4)commit
-The user may ask to commit changes; however, if there have been no changes since the last commit, the commit 
function not run. If there was a change -- whether that be to an existing file in the current commit, or adding a new file, the system will
commit the changes, as well as ask the user to enter a commit message. 
-The commit function will also check to see if a file was deleted in previous commits, but was later re-added.
If the re-added file had no changes done, the file version will be the same as the past. If there was work done, then
the file version will be incremented by one.
-The commit will lastly create a new doublyLL with a deep copy of contents of the previous commit.

    5)See commit history
-If the user chooses to look at the previous commit history as well as the commit messages, this function will 
preview the structure of the past commits, past file versions, as well as commit messages.

    6)
-User may go back to any previous commit. If the user tries to commit to the current commit, or tries to checkout while the commit current is at 0, the 
program will return.
--NEED TO MAKE CHANGES TO addFile so that it will actually overwrite the texts.
    7)
-User will destruct the list. Then the program will remove .minigit
