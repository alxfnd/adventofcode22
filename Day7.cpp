#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct File
{
    string parentdir;
    string name;
    long size;
};

class Directory
{
    private:
        string _parentdirectory;
        vector<Directory> _subdirs;
    public:
        string name;
        long size;
        void SetParent(string name);
        void AddDirectory(Directory Directory);
        Directory(string name);
};

Directory::Directory(string name)
{
    name = name;
}
void Directory::SetParent(string name) 
{
    _parentdirectory = name;
}

void Directory::AddDirectory(Directory Directory)
{
    _subdirs.push_back(Directory);
    Directory.SetParent(name);
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
    currentdirectory = directory;
}

void Explorer::SetDirectory(string input)
{
    cout << input << endl;
    currentdirectory = input;
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
bool SearchDirectories(vector<Directory*>& AllDirectories, string Directory)
{
    if (AllDirectories.size() == 0) {
        return false;
    }
    cout << "here";
    int b = 0;
    cout << AllDirectories[b]->name.size();
    for (int i = 0; i <= AllDirectories.size(); i++) {
        if (AllDirectories[i]->name.size() == Directory.size()) {
            return true;
        }
    }
    return false;
}

void Processor(string line, Explorer& Explorer, vector<Directory*>& AllDirectories) {
    char a = line[0];
    //cout << type_info(line[0]);
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
                if (! SearchDirectories(AllDirectories, wholeline[2])) {
                    AllDirectories.push_back(new Directory(wholeline[2]));
                }
            }else{
                Explorer.Command(wholeline[1], "null");
            }
            break;
        //dir = new directory
        case 100:
            break;
        //else must be an int = new file
        default:
            break;
    }
}

int main () 
{
    string currentdirectory = "null";
    Explorer Explorer(currentdirectory);
    string input = "$ cd /";
    vector<Directory*> AllDirectories;
    Processor(input, Explorer, AllDirectories);
    cout << Explorer.GetDirectory() << endl << AllDirectories.size() << endl;
    input = "$ cd abc";
    //Processor(input, Explorer, AllDirectories);
    cout << "Dir changed" << endl << Explorer.GetDirectory() << endl << AllDirectories[0]->name;
    //Explorer.Command(input, input);
    return 0;
}
