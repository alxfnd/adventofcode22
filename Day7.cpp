#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct File
{
    string name;
    long size;
};

class Directory
{
    private:
        string _parentdirectory;
        vector<Directory*> _subdirs;
        vector<File*> _files;
    public:
        string name;
        long size;
        void SetParent(string name);
        void AddDirectory(Directory* Directory, string currentdir);
        void AddFile(File* File);
        void CalculateSize();
        string GetParent();
        Directory(string name);
};

Directory::Directory(string name)
{
    this->name = name;
}
void Directory::SetParent(string name) 
{
    this->_parentdirectory = name;
}

void Directory::AddDirectory(Directory* Directory, string currentdir)
{
    _subdirs.push_back(Directory);
    Directory->SetParent(currentdir);
}

void Directory::AddFile(File* File)
{
    this->_files.push_back(File);
}

void Directory::CalculateSize()
{
    // this will be a recursive function that iterates
    // through all subdirs and sums the total file sizes
    // adding the total to the current file size

    // in the solution part, I'll add size
    // to an array, sort it, and count
    // total under X amount
}

string Directory::GetParent()
{
    return _parentdirectory;
}

class Explorer
{
    private:
    string currentdirectory;
    public:
    void SetDirectory(string input);
    string GetDirectory();
    string Command(string command, string input);
    Explorer(string directory);
};

Explorer::Explorer(string directory)
{
    this->currentdirectory = directory;
}

void Explorer::SetDirectory(string input)
{
    this->currentdirectory = input;
}

string Explorer::GetDirectory()
{
    return currentdirectory;
}

string Explorer::Command(string command, string input)
{
    /*
    Two possible commands:
        cd - move directory
        ls - list contents of current directory
    */

   // could create an array and use index location to determine
   // the command. however there are only two commands so I used
   // a less robust method.
   int s;
   if (command == "cd") {
        s = 0;
        if (input == "..") {
            s = 1;
        }
   }else{
        s = 2;
   }
   switch(s)
   {
    case 0:
        // enter a directory
        //cout << "Input is cd" << endl;
        return input;
        break;
    case 1:
        // go up a directory
        break;
    case 2:
        // list current directory
        // for the puzzle, this is unnecessary because ls doesn't serve any real function
        cout << "Input is ls" << endl;
        break;
   }
}

// this function isn't the problem (the part where it compares the name)
// seems the issue is that the directory name isn't getting set correctly and it can't be called
Directory* SearchDirectories(vector<Directory*>& AllDirectories, string Directory)
{
    for (int i = 0; i < AllDirectories.size(); i++) {
        if (AllDirectories[i]->name == Directory) {
            return AllDirectories[i];
        }
    }
    return AllDirectories[0];
}

void Processor(string line, Explorer& Explorer, vector<Directory*>& AllDirectories) {
    char a = line[0];
    string word;
    stringstream ss(line);
    vector<string> wholeline;
    while(getline(ss, word, ' ')) {
        wholeline.push_back(word);
    }
    switch (a)
    {
        //command
        case 36:
            if (wholeline.size() == 3) {
                Explorer.SetDirectory(
                    Explorer.Command(wholeline[1], wholeline[2])
                );
                if (SearchDirectories(AllDirectories, wholeline[2])->name != wholeline[2]) {
                    AllDirectories.push_back(new Directory(wholeline[2]));
                }
            }else{
                Explorer.Command(wholeline[1], "null");
            }
            break;
        //dir = new directory
        case 100:
            Directory* CD = SearchDirectories(AllDirectories, Explorer.GetDirectory());
            Directory* newsubdir = new Directory(wholeline[1]);
            AllDirectories.push_back(newsubdir);
            CD->AddDirectory(newsubdir, Explorer.GetDirectory());
            break;
        //else must be an int = new file
    }
    // adding a third case statement was breaking the switch, so now I added an if at the end
    // lazy I know
    if (a < 10) {
        Directory* CD = SearchDirectories(AllDirectories, Explorer.GetDirectory());
        File* newfile = new File;
        newfile->name = wholeline[1];
        newfile->size = stol(wholeline[0]);
        CD->AddFile(newfile);
    }
}

int main () 
{
    string currentdirectory = "null";
    Explorer Explorer(currentdirectory);
    string input = "$ cd /";
    vector<Directory*> AllDirectories;
    AllDirectories.push_back(new Directory("/"));
    Processor(input, Explorer, AllDirectories);
    cout << Explorer.GetDirectory() << endl;
    input = "$ cd abcde";
    Processor(input, Explorer, AllDirectories);
    cout << "Dir changed" << endl << AllDirectories[1]->GetParent() << AllDirectories[1]->name;
    //Explorer.Command(input, input);
    return 0;
}
