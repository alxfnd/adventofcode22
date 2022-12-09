#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Grid {
    public:
    int** Grid;
    int headx;
    int heady;
    int tailx;
    int taily;
    void UpdateHeads(char dir);
    void UpdateTails();
};

void Grid::UpdateHeads(char dir)
{
    int newy = this->heady;
    int newx = this->headx;
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
    //cout << this->heady << " :hy: " << newy << endl;
    //cout << this->headx << " :hx: " << newx << endl;
    //cout << this->taily << " :t: " << this->tailx << endl;

    // check if new space has already been visited by Tails
    if (this->Grid[newy][newx] == 2) {
        this->Grid[newy][newx] = 4;
    }else{
        //heads is now in an unvisited space
        this->Grid[newy][newx] = 3;
    }

    // replace old space based on heads value (which determines if it has already been visited)
    if (this->Grid[heady][headx] == 4) {
        this->Grid[heady][headx] = 2;
    }
    if (this->Grid[heady][headx] == 3) {
        this->Grid[heady][headx] = 1;
    }
    this->headx = newx;
    this->heady = newy;
}

void Grid::UpdateTails()
{
    //using more variables because using the same ones keeps breaking
    int locx = 0;
    int locy = 0;
    //check if heads is in range
    bool inrange = false;
    int scanx = (this->tailx - 1);
    int scany = (this->taily - 1);
    while (scany < (this->taily + 2)) {
        //cout << scany << "..." << scanx << endl;
        int scanx = (this->tailx - 1);
        while (scanx < (this->tailx + 2)) {
            //cout << scany << "..." << scanx << endl;
            //cout << this->Grid[scany][scanx];
            if (this->Grid[scany][scanx] == 3 || this->Grid[scany][scanx] == 4) {
                //cout << "in range" << endl;
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
            //cout << scany << "..." << scanx << endl;
            if (this->Grid[scany][scanx] == 3 || this->Grid[scany][scanx] == 4) {
                //cout << "found it!" << endl;
                locx = scanx;
                locy = scany;
                //cout << "final: y-x : " << locy << locx << endl;
                found = true;
                break;
            }
            scanx++;
        }
        if (found == true) {
            //cout << "final: y-x : " << locy << locx << endl;
            break;
        }
        scany++;
    }
    //cout << "final: y-x : " << locy << locx << endl;
    //cout << scanx << " " << scany << endl;
    //heads must be found, or code is wrong elsewhere
    //here come lots of ifs/switch statements
    if (locx == this->tailx) {
        //heads is directly up or down
        if (locy > this->taily) {
            this->taily++;
        }else{
            this->taily--;
        }
        this->Grid[taily][tailx] = 2;
        return;
    }
    if (locy == this->taily) {
        //heads is directly left or right
        if (locx > this->tailx) {
            this->tailx++;
        }else{
            this->tailx--;
        }
        this->Grid[taily][tailx] = 2;
        return;
    }
    //if here, heads is diagonally elsewhere
    if (locy > this->taily) {
        if (locx > this->tailx) {
            this->tailx++;
            this->taily++;
            this->Grid[taily][tailx] = 2;
            return;
        }else{
            this->tailx--;
            this->taily++;
            this->Grid[taily][tailx] = 2;
            return;
        }
    }else{
        if (locx > this->tailx) {
            this->tailx++;
            this->taily--;
            this->Grid[taily][tailx] = 2;
            return;
        }else{
            this->tailx--;
            this->taily--;
            this->Grid[taily][tailx] = 2;
            return;
        }
    }
    cout << "you should not be here";
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
    return (backward + forward + 10);
}

//Collect instructions into a vector for re-use

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
    //fill all values with 1 (not visited)
    for (int i = 0; i < height; i++) {
        for (int w = 0; w < width; w++) {
            puzzle.Grid[i][w] = 1;
        }
    }

    //starting location - note: forced an even number in the function above
    int startx = (width / 2);
    int starty = (height / 2);
    puzzle.headx = startx;
    puzzle.heady = starty;
    puzzle.tailx = startx;
    puzzle.taily = starty;
    puzzle.Grid[puzzle.taily][puzzle.tailx] = 0;

    //now what.
    // use 0s and 2s to determine where 
    // HEADS will use a 3 on unvisited spots - not divisible by 2
    // and HEADS will use a 4 on visited spots
    // TAILS will use a 2 - divisible by 2
    //
    stringstream spaces;
    int move = 0;
    for (int z = 0; z < instructions.size(); z++) {
        spaces.clear();
        move = 0;
        char d = instructions[z][0];
        spaces << instructions[z][2];
        spaces >> move;
        for (int ct = 0; ct < move; ct++) {
            puzzle.UpdateHeads(d);
            puzzle.UpdateTails();
        }
    }


    // calculate how many places it visited
    int visited = 0;
    int check = 0;
    for (int i = 0; i < height; i++) {
        for (int w = 0; w < width; w++) {
            check = (puzzle.Grid[i][w] % 2);
            //cout << puzzle.Grid[i][w];
            if (check == 0) {
                visited++;
            }
        }
        //cout << endl;
    }
    cout << visited;
    return 0;
}

//first guess: 3118
