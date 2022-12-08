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
    int size;
};

class Directory
{
    private:
        
        int parentdirectory;
        vector<Directory*> _subdirs;
        vector<File*> _files;
    public:
        int id;
        string name;
        int size = 0;
        void AddDirectory(Directory* Directory);
        void AddFile(File* File);
        int GetFiles();
        int GetDirs();
        int GetParent();
        int GetChild(string name);
        void CalculateSize();
        int output();
        Directory(string name, int id, int parent);
};

Directory::Directory(string name, int id, int parent)
{
    this->id = id;
    this->name = name;
    this->parentdirectory = parent;
}

void Directory::AddDirectory(Directory* Directory)
{
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

int Directory::GetParent()
{
    return parentdirectory;
}

int Directory::GetChild(string name)
{
    for (int i = 0; i < _subdirs.size(); i++) {
        if (_subdirs[i]->name == name) {
            return _subdirs[i]->id;
        }
    }
}

void Directory::CalculateSize()
{
    /*
    if (this->name == "/") {
    this->size = 0;
    if (_subdirs.size() != 0) {
        for (int i = 0; i < _subdirs.size(); i++) {
            _subdirs[i]->CalculateSize();
            cout << this->name << this->id << endl << "DIR: " << _subdirs[i]->name << endl << _subdirs[i]->size << endl << endl;
            this->size += _subdirs[i]->size;
            cout << this->size << " so far.." << endl << endl;
        }
    }
    if (_files.size() != 0) {
        for (int i = 0; i < _files.size(); i++) {
            cout << this->name << this->id << endl << "File: " <<_files[i]->name << endl << _files[i]->size << endl << endl;
            this->size += _files[i]->size;
        }
    }
    cout << this->size << endl << endl;
    }else{*/
        this->size = 0;
    if (_subdirs.size() != 0) {
        for (int i = 0; i < _subdirs.size(); i++) {
            _subdirs[i]->CalculateSize();
            this->size += _subdirs[i]->size;
        }
    }
    if (_files.size() != 0) {
        for (int i = 0; i < _files.size(); i++) {
            this->size += _files[i]->size;
        }
    }
    //}
}

int Directory::output()
{
    int result = 0;
    //cout << this->name << endl << this->size << endl;
    if (this->GetDirs() == 0) {
        if (this->size <= 100000) {
            cout << this->name << endl << this->size << endl;
            result += this->size;
        }
        return result;
    }
    for (int i = 0; i < _subdirs.size(); i++) {
        result += _subdirs[i]->output();
    }
    if (this->size <= 100000) {
        result += this->size;
        cout << this->name << endl << this->size << endl;
        return result;
    }else{
        //cout << endl << endl << "special: " << result << endl << endl;
        return result;
    }
}

class Explorer
{
    public:
        int currentdirectory;
        Explorer(int directory);
        int Command(string command, string input, Directory* PWD);
        void SetDirectory(int input);
};

Explorer::Explorer(int directory)
{
    this->currentdirectory = directory;
}

void Explorer::SetDirectory(int input)
{
    this->currentdirectory = input;
}

int Explorer::Command(string command, string input, Directory* PWD)
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
        return PWD->GetChild(input);
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
   return 0;
}

Directory* SearchDirectories(vector<Directory*>& AllDirectories, int Directory)
{
    for (int i = 0; i < AllDirectories.size(); i++) {
        if (AllDirectories[i]->id == Directory) {
            return AllDirectories[i];
        }
    }
    return AllDirectories[0];
}

void Processor(string line, Explorer& Explorer, vector<Directory*>& AllDirectories, int count) {
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
                    Explorer.Command(wholeline[1], wholeline[2], SearchDirectories(AllDirectories, Explorer.currentdirectory))
                );
            }
            break;
        case 100:
            //cout << "here it is: " <<Explorer.GetDirectory() << endl;
            Directory* CD = SearchDirectories(AllDirectories, Explorer.currentdirectory);
            Directory* newsubdir = new Directory(wholeline[1], count, Explorer.currentdirectory);
            AllDirectories.push_back(newsubdir);
            CD->AddDirectory(newsubdir);
            
            cout << "Directory name: " << SearchDirectories(AllDirectories, Explorer.currentdirectory)->name << endl;
            cout << "Current Dir id is: " << SearchDirectories(AllDirectories, Explorer.currentdirectory)->id << endl;
            cout << "New dir is: " << newsubdir->name << endl;
            cout << "Id is: " << newsubdir->id << endl;
            cout << "Directory parent: " << SearchDirectories(AllDirectories, (SearchDirectories(AllDirectories, Explorer.currentdirectory)->GetParent()))->name << endl << endl;
            break;
        //else must be an int = new file
    }
    // adding a third case statement was breaking the switch, so now I added an if at the end
    // lazy, I know
    if (!(a == 36 || a == 100)) {
        Directory* CD = SearchDirectories(AllDirectories, Explorer.currentdirectory);
        File* newfile = new File;
        newfile->name = wholeline[1];
        newfile->size = stoi(wholeline[0]);
        CD->AddFile(newfile);
        //cout << "Directory name: " <<  SearchDirectories(AllDirectories, Explorer.currentdirectory)->name << endl;
        //cout << "Current Dir id is: " << SearchDirectories(AllDirectories,  Explorer.currentdirectory)->id << endl;
        cout << newfile->name << endl << newfile->size << endl << endl;
    }
}



int main () 
{
    string currentdirectory = "null";
    int count = 0;
    Explorer Explorer(count);
    vector<Directory*> AllDirectories;
    AllDirectories.push_back(new Directory("/", 0, -1));
    fstream Advent(".\\Day7.txt", ios::in | ios::out);
    string cur_line;
    
    while (getline(Advent, cur_line)) {
        count++;
        Processor(cur_line, Explorer, AllDirectories, count);
        
    }
    AllDirectories[0]->CalculateSize();
    cout << AllDirectories[0]->output();
    return 0;
}
