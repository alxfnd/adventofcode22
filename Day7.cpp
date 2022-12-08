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
        long size = 0;
        void AddDirectory(Directory* Directory, string currentdir);
        void AddFile(File* File);
        int GetFiles();
        int GetDirs();
        void CalculateSize();
        string GetParent();
        long output();
        Directory(string name);
};

long Directory::output()
{
    long result = 0;
    if (this->GetDirs() == 0) {
        if (this->size <= 100000) {
            result += this->size;
        }
        return result;
    }
    for (int i = 0; i < _subdirs.size(); i++) {
        result += _subdirs[i]->output();
    }
    if (this->size <= 100000) {
        result += this->size;
        return result;
    }else{
        return result;
    }
}

/*
vector<Directory*>& Directory::output()
{
    vector<Directory*> UnderPar;
    if (this->GetDirs() == 0) {
        return UnderPar;
    }
    for (int i = 0; i < _subdirs.size(); i++) {
        vector<Directory*> curdir = _subdirs[i]->output();
        if (curdir.size() != 0) {
            for (int c = 0; c <= curdir.size(); c++) {
                if (curdir[c]->size <= 100000) {
                    cout << UnderPar.size();
                    UnderPar.push_back(curdir[c]);
                }
            }
        }
        //cout << _subdirs[i]->name << endl << _subdirs[i]->size << endl;
        //cout << _files[i]->name << endl << _files[i]->size << endl;
    }
    //for (int i = 0; i < UnderPar.size(); i++) {
    //    totalsize += UnderPar[i]->output()
    //}
    
    return UnderPar&;
}
*/

Directory::Directory(string name)
{
    this->name = name;
}

void Directory::AddDirectory(Directory* Directory, string currentdir)
{
    Directory->_parentdirectory = currentdir;
    _subdirs.push_back(Directory);
}

void Directory::AddFile(File* File)
{
    this->_files.push_back(File);
}

int Directory::GetFiles()
{
    return _files.size();
}

int Directory::GetDirs()
{
    return _subdirs.size();
}

void Directory::CalculateSize()
{
    this->size = 0;
    if (_subdirs.size() != 0) {
        for (int i = 0; i < _subdirs.size(); i++) {
            _subdirs[i]->CalculateSize();
            this->size += _subdirs[0]->size;
        }
    }
    if (_files.size() != 0) {
        for (int i = 0; i < _files.size(); i++) {
            this->size += _files[i]->size;
        }
    }
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
    string Command(string command, string input, Directory* PWD);
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

string Explorer::Command(string command, string input, Directory* PWD)
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
        return PWD->GetParent();
        break;
    case 2:
        // list current directory
        // for the puzzle, this is unnecessary because ls doesn't serve any real function
        cout << "Input is ls" << endl;
        break;
   }
   return "null";
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
    int a = (char)line[0];
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
                    Explorer.Command(wholeline[1], wholeline[2], SearchDirectories(AllDirectories, Explorer.GetDirectory()))
                );
                if (SearchDirectories(AllDirectories, wholeline[2])->name != wholeline[2]) {
                    AllDirectories.push_back(new Directory(wholeline[2]));
                }
            }else{
                break;
                //Explorer.Command(wholeline[1], "null", AllDirectories);
            }
            break;
        //dir = new directory
        case 100:
            //cout << "here it is: " <<Explorer.GetDirectory() << endl;
            Directory* CD = SearchDirectories(AllDirectories, Explorer.GetDirectory());
            Directory* newsubdir = new Directory(wholeline[1]);
            AllDirectories.push_back(newsubdir);
            CD->AddDirectory(newsubdir, Explorer.GetDirectory());
            break;
        //else must be an int = new file
    }
    // adding a third case statement was breaking the switch, so now I added an if at the end
    // lazy, I know
    if (!(a == 36 || a == 100)) {
        Directory* CD = SearchDirectories(AllDirectories, Explorer.GetDirectory());
        File* newfile = new File;
        newfile->name = wholeline[1];
        newfile->size = stol(wholeline[0]);
        CD->AddFile(newfile);
        //cout << newfile->size << endl;
    }
}

int main () 
{
    
    string currentdirectory = "null";
    Explorer Explorer(currentdirectory);
    //string input = "$ cd /";
    vector<Directory*> AllDirectories;
    AllDirectories.push_back(new Directory("/"));
    /*
    Processor(input, Explorer, AllDirectories);
    cout << Explorer.GetDirectory() << endl;
    input = "dir abcde";
    Processor(input, Explorer, AllDirectories);
    //input = "$ cd abcde";
    //Processor(input, Explorer, AllDirectories);
    cout << "marker" << endl << AllDirectories[1]->GetParent();// << AllDirectories[1]->name;
    //Explorer.Command(input, input);
    */
    // This is what it will actually be - above is for testing
    
    fstream Advent(".\\Day7.txt", ios::in | ios::out);
    string cur_line;
    while (getline(Advent, cur_line)) {
        //cout << cur_line << endl;
        Processor(cur_line, Explorer, AllDirectories);
        AllDirectories[0]->CalculateSize();
        //cout << "Current dirs = " << AllDirectories[0]->GetDirs() << endl;
        //cout << "Current files = " << AllDirectories[0]->GetFiles() << endl;
        //cout << "Current total = " << AllDirectories[0]->size << endl;
    }
    
    /*
    //long totalsize;
    //vector<Directory*> list = AllDirectories[0]->output();
    for (int i= 0; i < list.size(); i++) {
        totalsize += list[i]->size;
        cout << list[i]->name << endl;
    }
    cout << totalsize;
    //for (int i = 0; i < )
    */
    cout << AllDirectories[0]->output();



    return 0;
}
