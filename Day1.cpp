#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    fstream advent("c:\\Users\\alexf\\Documents\\AdventofCode22\\Day1.txt", std::ios::in | std::ios::out);
    vector<int>line;
    string cur_line;
    int run_total = 0;
    while (getline(advent, cur_line))
    {
        if (cur_line.size() == 0) {
            line.push_back(run_total);
            run_total = 0;
        }else{
            run_total += stoi(cur_line);
        };
    }
    line.push_back(run_total);
    sort(line.begin(), line.end());
    cout << "Question 1: " << endl << line[line.size() - 1] << endl;
    cout << "Question 2: " << endl << line[line.size() - 1] + line[line.size() - 2] + line[line.size() - 3];
    return 0;
};
