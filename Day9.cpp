#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int concat(int a, int b)
{
 
    // Convert both the integers to string
    string s1 = to_string(a);
    string s2 = to_string(b);
 
    // Concatenate both strings
    string s = s1 + s2;
 
    // Convert the concatenated string
    // to integer
    int c = stoi(s);
 
    // return the formed integer
    return c;
}

class Rope {
    public:
    int* headx;
    int* heady;
    int tailx;
    int taily;
    vector<int> visits;
    Rope(int& hy, int& hx);
    void LookForHeads(int** Grid, int c);
    void UpdateTails();
};

Rope::Rope(int& hy, int& hx)
{
    this->heady = &hy;
    this->headx = &hx;
    taily = *this->heady;
    tailx = *this->headx;
    this->visits.push_back((taily * tailx));
}

void Rope::LookForHeads(int** Grid, int c)
{
    //using more variables because using the same ones keeps breaking
    int locx = 0;
    int locy = 0;
    //check if heads is in range
    bool inrange = false;
    int scanx = (this->tailx - 1);
    int scany = (this->taily - 1);
    while (scany < (this->taily + 2)) {
        int scanx = (this->tailx - 1);
        while (scanx < (this->tailx + 2)) {
            if (Grid[scany][scanx] == 1) {
                inrange = true;
                break;
            }
            scanx++;
        }
        if (inrange == true) {
            break;
        }
        scany++;
    }
    if (inrange == true) {
        //doesn't move
        return;
    }
    
    //heads is not in range - tails must move
    //determine location
    bool found = false;
    scanx = (this->tailx - 2);
    scany = (this->taily - 2);
    while (scany != (this->taily + 3)) {
        int scanx = (this->tailx - 2);
        while (scanx != (this->tailx + 3)) {
            if (Grid[scany][scanx] == 1) {
                locx = scanx;
                locy = scany;
                found = true;
                break;
            }
            scanx++;
        }
        if (found == true) {
            break;
        }
        scany++;
    }
    //heads must be found, or code is wrong elsewhere
    //here come lots of ifs/switch statements
    if (locx == this->tailx) {
        //heads is directly up or down
        if (locy > this->taily) {
            this->taily++;
        }else{
            this->taily--;
        }
        this->visits.push_back(concat(taily, tailx));
        return;
    }
    if (locy == this->taily) {
        //heads is directly left or right
        if (locx > this->tailx) {
            this->tailx++;
        }else{
            this->tailx--;
        }
        this->visits.push_back(concat(taily, tailx));
        return;
    }
    //if here, heads is diagonally elsewhere
    if (locy > this->taily) {
        if (locx > this->tailx) {
            this->tailx++;
            this->taily++;
            this->visits.push_back(concat(taily, tailx));
            return;
        }else{
            this->tailx--;
            this->taily++;
            this->visits.push_back(concat(taily, tailx));
            return;
        }
    }else{
        if (locx > this->tailx) {
            this->tailx++;
            this->taily--;
            this->visits.push_back(concat(taily, tailx));
            return;
        }else{
            this->tailx--;
            this->taily--;
            this->visits.push_back(concat(taily, tailx));
            return;
        }
    }
    cout << "you should not be here";
}

void Rope::UpdateTails()
{
    //using more variables because using the same ones keeps breaking
    int locx = 0;
    int locy = 0;
    //check if heads is in range
    bool inrange = false;
    int scanx = (this->tailx - 1);
    int scany = (this->taily - 1);
    while (scany < (this->taily + 2)) {
        int scanx = (this->tailx - 1);
        while (scanx < (this->tailx + 2)) {
            if (*this->headx == scanx && *this->heady == scany) {
                inrange = true;
                break;
            }
            scanx++;
        }
        if (inrange == true) {
            break;
        }
        scany++;
    }
    if (inrange == true) {
        //doesn't move
        return;
    }
    
    //heads is not in range - tails must move
    //determine location
    bool found = false;
    scanx = (this->tailx - 2);
    scany = (this->taily - 2);
    while (scany != (this->taily + 3)) {
        int scanx = (this->tailx - 2);
        while (scanx != (this->tailx + 3)) {
            if (*this->headx == scanx && *this->heady == scany) {
                locx = scanx;
                locy = scany;
                found = true;
                break;
            }
            scanx++;
        }
        if (found == true) {
            break;
        }
        scany++;
    }
    //heads must be found, or code is wrong elsewhere
    if (locx == this->tailx) {
        //heads is directly up or down
        if (locy > this->taily) {
            this->taily++;
        }else{
            this->taily--;
        }
        this->visits.push_back(concat(taily, tailx));
        return;
    }
    if (locy == this->taily) {
        //heads is directly left or right
        if (locx > this->tailx) {
            this->tailx++;
        }else{
            this->tailx--;
        }
        this->visits.push_back(concat(taily, tailx));
        return;
    }
    //if here, heads is diagonally elsewhere
    if (locy > this->taily) {
        if (locx > this->tailx) {
            this->tailx++;
            this->taily++;
            this->visits.push_back(concat(taily, tailx));
            return;
        }else{
            this->tailx--;
            this->taily++;
            this->visits.push_back(concat(taily, tailx));
            return;
        }
    }else{
        if (locx > this->tailx) {
            this->tailx++;
            this->taily--;
            this->visits.push_back(concat(taily, tailx));
            return;
        }else{
            this->tailx--;
            this->taily--;
            this->visits.push_back(concat(taily, tailx));
            return;
        }
    }
    cout << "you should not be here";
}

class Grid {
    public:
    int** Grid;
    int positionx;
    int positiony;
    void UpdatePosition(char dir);
};

void Grid::UpdatePosition(char dir)
{
    int newy = this->positiony;
    int newx = this->positionx;
    switch (dir) {
        case 'U':
            newy -= 1;
            break;
        case 'L':
            newx -= 1;
            break;
        case 'R':
            newx += 1;
            break;
        case 'D':
            newy += 1;
            break;
    }
    this->Grid[this->positiony][this->positionx] = 0;
    this->positionx = newx;
    this->positiony = newy;
    this->Grid[this->positiony][this->positionx] = 1;
    return;
}

int size(vector<string> command, int direction) {
    // direction: 0 = x axis, 1 = y axis
    char m;
    char n;
    switch (direction) {
        case 0:
            m = 'R';
            n = 'L';
            break;
        case 1:
            m = 'U';
            n = 'D';
            break;
    }

    //now generate max in each direction + wiggle room
    stringstream ss;
    int num;
    int forward = 0;
    int backward = 0;
    for (int i = 0; i < command.size(); i++) {
        ss.clear();
        if (command[i][0] != m && command[i][0] != n) {
            continue;
        }
        if (command[i][0] == m) {
            ss << command[i][2];
            num = 0;
            ss >> num;
            forward += num;
        }else{
            ss << command[i][2];
            num = 0;
            ss >> num;
            backward += num;
        }
    }
    if (((backward + forward) % 2) != 0) {
        forward++;
    }
    //plus 10 = wiggle room to not break the scan loops in UpdateTails()
    return (backward + forward + 20);
}

fstream Advent(".\\Day9.txt", ios::in | ios::out);
vector<string> instructions;
string cur_line;

int main () 
{
    while(getline(Advent,cur_line)) {
        instructions.push_back(cur_line);
    }
    //vector now contains all steps

    //calculate total height and width that the directions need to complete
    //function outputs a little wiggle room
    int height = 0;
    int width = 0;
    height = size(instructions, 0);
    width = size(instructions, 1);
    
    //generate a grid
    Grid puzzle;
    puzzle.Grid = new int*[height];
    for (int i = 0; i < height; i++) {
        puzzle.Grid[i] = new int[width];
    }
    for (int i = 0; i < height; i++) {
        for (int w = 0; w < width; w++) {
            puzzle.Grid[i][w] = 0;
        }
    }

    //starting location - note: forced an even number in the function above
    int startx = (width / 2);
    int starty = (height / 2);
    puzzle.Grid[starty][startx] = 1;
    puzzle.positionx = startx;
    puzzle.positiony = starty;

    vector<Rope*> Ropes;
    Ropes.push_back(new Rope(puzzle.positiony, puzzle.positionx));
    for (int i = 1; i < 9; i++) {
        Ropes.push_back(new Rope(Ropes[i-1]->taily, Ropes[i-1]->tailx));
    }
    
    stringstream spaces;
    int move = 0;
    for (int z = 0; z < instructions.size(); z++) {
        spaces.clear();
        move = 0;
        char d = instructions[z][0];
        if (instructions[z].length() > 3) {
            spaces << instructions[z].substr(2,2);
        }else{
            spaces << instructions[z][2];
        }
        spaces >> move;
        cout << move << endl;
        for (int ct = 0; ct < move; ct++) {
            puzzle.UpdatePosition(d);
            Ropes[0]->LookForHeads(puzzle.Grid, 0);
            for (int i = 1; i < Ropes.size(); i++) {
                Ropes[i]->UpdateTails();
            }
        }
    }
    /*
    //cout << *Ropes[0]->headx << endl;
    //cout << *Ropes[8]->headx << endl;
    cout << Ropes[0]->visits.size() << endl;
    sort(Ropes[0]->visits.begin(),Ropes[0]->visits.end());
    Ropes[0]->visits.erase( unique(Ropes[0]->visits.begin(), Ropes[0]->visits.end()), Ropes[0]->visits.end());
    //auto it = unique(Rope1.visits.begin(),Rope1.visits.end());
    //Rope1.visits.resize(distance(Rope1.visits.begin(), it));
    cout << Ropes[0]->visits.size();
    */
    cout << Ropes[8]->visits.size() << endl;
    sort(Ropes[8]->visits.begin(),Ropes[8]->visits.end());
    Ropes[8]->visits.erase( unique(Ropes[8]->visits.begin(), Ropes[8]->visits.end()), Ropes[8]->visits.end());
    //auto it = unique(Rope1.visits.begin(),Rope1.visits.end());
    //Rope1.visits.resize(distance(Rope1.visits.begin(), it));
    cout << Ropes[8]->visits.size();
    
    return 0;
}
