#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int IsVisible(int** Grid, int y, int x, int height, int width)
{
    int currentvalue = Grid[y][x];
    int topx = x;
    int topy = y;
    bool failed = false;
    
    //is an edge tree
    if (x == 0 || x == (width - 1)) {
        return 1;
    }
    if (y == 0 || y == (height - 1)) {
        return 1;
    }

    //left
    failed = false;
    y = topy;
    x = topx;
    x--;
    while (x >= 0) {
        if (currentvalue <= Grid[y][x]) {
            failed = true;
            break;
        }
        x--;
    }
    if (failed == false) {
        return 1;
    }

    //up
    failed = false;
    y = topy;
    x = topx;
    y--;
    while (y >= 0) {
        if (currentvalue <= Grid[y][x]) {
            failed = true;
            break;
        }
        y--;
    }
    if (failed == false) {
        return 1;
    }

    //right
    failed = false;
    y = topy;
    x = topx;
    x++;
    while (x < width) {
        if (currentvalue <= Grid[y][x]) {
            failed = true;
            break;
        }
        x++;
    }
    if (failed == false) {
        return 1;
    }

    //down
    failed = false;
    y = topy;
    x = topx;
    y++;
    while (y < height) {
        if (currentvalue <= Grid[y][x]) {
            failed = true;
            break;
        }
        y++;
    }
    if (failed == false) {
        return 1;
    }

    return 0;
}

int ScenicScore(int** Grid, int y, int x, int height, int width)
{
    int currentvalue = Grid[y][x];
    int topx = x;
    int topy = y;
    bool failed = false;
    int left = 0;
    int up = 0;
    int down = 0;
    int right = 0;
    //left
    failed = false;
    y = topy;
    x = topx;
    x--;
    while (x >= 0) {
        left++;
        if (currentvalue <= Grid[y][x]) {
            failed = true;
            break;
        }
        x--;
    }

    //up
    failed = false;
    y = topy;
    x = topx;
    y--;
    while (y >= 0) {
        up++;
        if (currentvalue <= Grid[y][x]) {
            failed = true;
            break;
        }
        y--;
    }
    
    //right
    failed = false;
    y = topy;
    x = topx;
    x++;
    while (x < width) {
        right++;
        if (currentvalue <= Grid[y][x]) {
            failed = true;
            break;
        }
        x++;
    }

    //down
    failed = false;
    y = topy;
    x = topx;
    y++;
    while (y < height) {
        down++;
        if (currentvalue <= Grid[y][x]) {
            failed = true;
            break;
        }
        y++;
    }
    int scenicscore = (left * up * right * down);
    return scenicscore;
}

int main()
{
    fstream Advent(".\\Day8.txt", ios::in | ios::out);
    int** Grid;
    string cur_line;
    int height = 0;
    int width = 0;

    //Generate grid array
    while (getline(Advent,cur_line)) {
        if (width == 0){
            width = cur_line.length();
        }
        height++;
    }
    Grid = new int*[height];
    for (int i = 0; i < height; i++) {
        Grid[i] = new int[width];
    }
    //array has now been generated

    //now populate array with tree values
    fstream Advent2(".\\Day8.txt", ios::in | ios::out);
    int count2 = 0;
    stringstream ss;
    int num;
    while (getline(Advent2,cur_line)) {
        for (int i = 0; i < cur_line.length(); i++) {
            ss.clear();
            ss << cur_line[i];
            num = 0;
            ss >> num;
            Grid[count2][i] = num;
            //cout << cur_line[i];
        }
        count2++;
    }
    //puzzle problem is converted into Grid arrays
    
    //REF: Grid[y][x]
    int visibletrees = 0;
    int treehouse = 0;
    int assess = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            visibletrees += IsVisible(Grid, y, x, height, width);
            assess = ScenicScore(Grid, y, x, height, width);
            if (assess > treehouse) {
                treehouse = assess;
            }
        }
        
    }
    cout << endl << visibletrees << endl;
    cout << endl << treehouse << endl;
    return 0;
}
//
