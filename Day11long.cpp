#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <cxxabi.h>
using namespace std;

class Turn;

enum Math {PLUS, MULTIPLY};

class Item
{
    public:
    long long id;
    long long worry;
    Item(int id, long long worry);
};

Item::Item(int id, long long worry)
{
    this->id = id;
    this->worry = worry;
}

class Monkey
{
    public:
    int id;
    int inspections = 0;
    Math OpMath;
    int OpValue;
    int TestValue;
    int truemonkey;
    int falsemonkey;
    vector<Item*> items;
    long long Operation(long long item);
    long long GetWorry();
    void SetWorry(int position, long long worry);
    bool TestItem(long long item);
    void ThrowItem(Turn& turn, bool test);
    Monkey(int itrue, int ifalse, Math math, int value, int test, int id);
};

Monkey::Monkey(int itrue, int ifalse, Math math, int value, int test, int id)
{
    this->truemonkey = itrue;
    this->falsemonkey = ifalse;
    this->OpMath = math;
    this->OpValue = value;
    this->TestValue = test;
    this->id = id;
}

long long Monkey::GetWorry()
{
    return this->items[0]->worry;
}

void Monkey::SetWorry(int position, long long worry)
{
    this->items[position]->worry = worry;
}

bool Monkey::TestItem(long long item)
{
    if ((item % this->TestValue) == 0) {
        return true;
    }else{
        return false;
    }
}

long long Monkey::Operation(long long item)
{
    switch (this->OpMath)
    {
        case Math::PLUS:
            if (this->OpValue == -1) {
                item += item;
                return item;
            }else{
                item += OpValue;
                return item;
            }
        case Math::MULTIPLY:
            if (this->OpValue == -1) {
                item *= item;
                return item;
            }else{
                item *= OpValue;
                return item;
            }
    }
    throw new exception();
}

class Turn
{
    public:
    int rounds = 1;
    int counter = 0;
    vector<Monkey*> Monkeys;
    void MoveCounter();
};

void Turn::MoveCounter()
{
    this->counter++;
    if (this->counter == 8) {
        this->counter = 0;
        this->rounds++;
    }
}

void Monkey::ThrowItem(Turn& turn, bool test)
{
    if (test == true) {
        turn.Monkeys[this->truemonkey]->items.push_back(this->items[0]);
        this->items.erase(this->items.begin());
    }else{
        turn.Monkeys[this->falsemonkey]->items.push_back(this->items[0]);
        this->items.erase(this->items.begin());
    }
}

int main ()
{
    // Create monkeys
    Turn turn;
    turn.Monkeys.push_back(new Monkey(3, 4, Math::MULTIPLY, 5, 11, 0));
    turn.Monkeys.push_back(new Monkey(6, 7, Math::MULTIPLY, -1, 2, 1));
    turn.Monkeys.push_back(new Monkey(1, 5, Math::MULTIPLY, 7, 5, 2));
    turn.Monkeys.push_back(new Monkey(2, 5, Math::PLUS, 1, 17, 3));
    turn.Monkeys.push_back(new Monkey(2, 3, Math::PLUS, 3, 19, 4));
    turn.Monkeys.push_back(new Monkey(1, 6, Math::PLUS, 5, 7, 5));
    turn.Monkeys.push_back(new Monkey(0, 7, Math::PLUS, 8, 3, 6));
    turn.Monkeys.push_back(new Monkey(4, 0, Math::PLUS, 2, 13, 7));
    // Create Items
    turn.Monkeys[0]->items.push_back(new Item(0, 92));
    turn.Monkeys[0]->items.push_back(new Item(1, 73));
    turn.Monkeys[0]->items.push_back(new Item(2, 86));
    turn.Monkeys[0]->items.push_back(new Item(3, 83));
    turn.Monkeys[0]->items.push_back(new Item(4, 65));
    turn.Monkeys[0]->items.push_back(new Item(5, 51));
    turn.Monkeys[0]->items.push_back(new Item(6, 55));
    turn.Monkeys[0]->items.push_back(new Item(7, 93));

    turn.Monkeys[1]->items.push_back(new Item(8, 99));
    turn.Monkeys[1]->items.push_back(new Item(9, 67));
    turn.Monkeys[1]->items.push_back(new Item(10, 62));
    turn.Monkeys[1]->items.push_back(new Item(11, 61));
    turn.Monkeys[1]->items.push_back(new Item(12, 59));
    turn.Monkeys[1]->items.push_back(new Item(13, 98));

    turn.Monkeys[2]->items.push_back(new Item(14, 81));
    turn.Monkeys[2]->items.push_back(new Item(15, 89));
    turn.Monkeys[2]->items.push_back(new Item(16, 56));
    turn.Monkeys[2]->items.push_back(new Item(17, 61));
    turn.Monkeys[2]->items.push_back(new Item(18, 99));

    turn.Monkeys[3]->items.push_back(new Item(19, 97));
    turn.Monkeys[3]->items.push_back(new Item(20, 74));
    turn.Monkeys[3]->items.push_back(new Item(21, 68));

    turn.Monkeys[4]->items.push_back(new Item(22, 78));
    turn.Monkeys[4]->items.push_back(new Item(23, 73));

    turn.Monkeys[5]->items.push_back(new Item(24, 50));

    turn.Monkeys[6]->items.push_back(new Item(25, 95));
    turn.Monkeys[6]->items.push_back(new Item(26, 88));
    turn.Monkeys[6]->items.push_back(new Item(27, 53));
    turn.Monkeys[6]->items.push_back(new Item(28, 75));

    turn.Monkeys[7]->items.push_back(new Item(29, 50));
    turn.Monkeys[7]->items.push_back(new Item(30, 77));
    turn.Monkeys[7]->items.push_back(new Item(31, 98));
    turn.Monkeys[7]->items.push_back(new Item(32, 85));
    turn.Monkeys[7]->items.push_back(new Item(33, 94));
    turn.Monkeys[7]->items.push_back(new Item(34, 56));
    turn.Monkeys[7]->items.push_back(new Item(35, 89));
    
    int currentitems = 0;

    while (turn.rounds < 21) {
        currentitems = turn.Monkeys[turn.counter]->items.size();
        for (int i = 0; i < currentitems; i++) {
            long long cur_worry = 0;
            bool test;
            // Monkey inspects, increases worry level, gets bored, decreases worry level
            turn.Monkeys[turn.counter]->inspections++;
            cur_worry = turn.Monkeys[turn.counter]->GetWorry();
            cur_worry = turn.Monkeys[turn.counter]->Operation(cur_worry);
            // have tried long long (gives 347 + 348) and int (gives 347 + 350)
            cur_worry = (long long)floor(cur_worry / 3);
            // Is worry level divisible by Monkey's test value
            test = turn.Monkeys[turn.counter]->TestItem(cur_worry);
            // Set new worry level on item
            turn.Monkeys[turn.counter]->SetWorry(0, cur_worry);
            // Throw to Monkey
            turn.Monkeys[turn.counter]->ThrowItem(turn, test);
            
        }
        turn.MoveCounter();
    }
    cout << turn.Monkeys[0]->inspections << endl;
    cout << turn.Monkeys[1]->inspections << endl;
    cout << turn.Monkeys[2]->inspections << endl;
    cout << turn.Monkeys[3]->inspections << endl;
    cout << turn.Monkeys[4]->inspections << endl;
    cout << turn.Monkeys[5]->inspections << endl;
    cout << turn.Monkeys[6]->inspections << endl;
    cout << turn.Monkeys[7]->inspections << endl;
    

    return 0;
}

//first answer: 121103 - too high (349 * 347)
//second answer: 105950 - too low (326 * 325)
// 120756 - too high (348 * 347)
