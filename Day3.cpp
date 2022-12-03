#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main() {
    //Generate alphabet
    char alphabet[52];
    for (int i = 0; i < 26; i++) {
        alphabet[i] = i + 97;
        alphabet[i + 26] = i + 65;
    }
    string cur_line;
    vector<char> PreventDuplicates;
    vector<char> SolutionChars;
    fstream Advent(".\\Day3.txt", ios::in | ios::out);
    while (getline(Advent, cur_line)) {
        PreventDuplicates.clear();
        for (int i = 0; i < (cur_line.length() / 2); i++) {
            if (cur_line.find(cur_line[i], ((cur_line.length() / 2) + 1)) < cur_line.length()) {
                if ( find (PreventDuplicates.begin(), PreventDuplicates.end(), cur_line[i]) == PreventDuplicates.end()) {
                    PreventDuplicates.push_back(cur_line[i]);
                    SolutionChars.push_back(cur_line[i]);
                }
            }
        }
    }
    int PartOne = 0;
    for (int i = 0; i < SolutionChars.size(); i++) {
        for (int a = 0; a < 52; a++) {
            if (alphabet[a] == SolutionChars[i]) {
                PartOne += (a + 1);
            }
        }
    }
    cout << "Answer to Part 1 is: " << PartOne << endl;
    
    //Part 2
    //My theory was to add all unique chars from each line in a batch of 3, to a vector
    //Then, scan the vector for any char that appears 3 times. Then put that in the solution vector for later

    // GroupCount = make sure we process batches of 3
    // Current = keeps previous char to compare
    int GroupCount = 0;
    int Current;
    vector<char> ItemCheck;
    SolutionChars.clear();
    fstream Advent2(".\\Day3.txt", ios::in | ios::out);
    while (getline(Advent2, cur_line)) {
        // Run through each line and add only unique characters to the ItemCheck vector from that line
        for (int c = 0; c < cur_line.length(); c++) {
            if ((cur_line.find(cur_line[c],(c+1))) > cur_line.length()) {
                ItemCheck.push_back(cur_line[c]);
            }
        }
        // If we have reached the third line, time detect the character that existed 3 times
        // Sort the line then scan for a recurring char
        if (GroupCount == 2) {
            sort(ItemCheck.begin(), ItemCheck.end());
            Current = 0;
            int Count = 0;
            for (int item = 0; item < ItemCheck.size(); item++) {
                if (ItemCheck[item] == Current) {
                    Count++;
                    if (Count == 2) {
                        SolutionChars.push_back(ItemCheck[item]);
                        break;
                    }
                }else{
                    Count = 0;
                }
                Current = ItemCheck[item];
            }
            GroupCount = 0;
            ItemCheck.clear();
        }else{
            GroupCount++;
        }
    }
    
    int PartTwo = 0;
    for (int i = 0; i < SolutionChars.size(); i++) {
        for (int a = 0; a < 52; a++) {
            if (alphabet[a] == SolutionChars[i]) {
                PartTwo += (a + 1);
            }
        }
    }
    cout << "Answer to Part 2 is: " << PartTwo << endl;
    
    return 0;
}
