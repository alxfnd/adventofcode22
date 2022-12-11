#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class Turn;

enum Math {PLUS, MULTIPLY};

class Item
{
    public:
    int id;
    int worry;
    Item(int id, int worry);
};

Item::Item(int id, int worry)
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
    int Operation(int item);
    int GetWorry();
    void SetWorry(int position, int worry);
    bool TestItem(int item);
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
}

int Monkey::GetWorry()
{
    return this->items[0]->worry;
}

void Monkey::SetWorry(int position, int worry)
{
    this->items[position]->worry = worry;
}

bool Monkey::TestItem(int item)
{
    if ((item % this->TestValue) == 0) {
        return true;
    }else{
        return false;
    }
}

int Monkey::Operation(int item)
{
    switch (this->OpMath)
    {
        case Math::PLUS:
            if (this->OpValue == -1) {
                return floor((item + item) / 3);
            }else{
                return floor((item + this->OpValue) / 3);
            }
        case Math::MULTIPLY:
            if (this->OpValue == -1) {
                return floor((item * item) / 3);
            }else{
                return floor((item * this->OpValue) / 3);
            }
    }
    throw new exception();
}

class Turn
{
    public:
    int rounds = 0;
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
    return;
}

void Monkey::ThrowItem(Turn& turn, bool test)
{
    if (test == true) {
        //cout << "Item is divisible by test value, throwing to true monkey" << endl;
        //this->items.erase(1);
        turn.Monkeys[this->truemonkey]->items.push_back(this->items[0]);
        this->items.erase(this->items.begin());
        //this->items.erase(auto i = 0, auto b = 1);
        //cout << "Monkey now has " << this->items.size();
        //cout << " items" << endl;
    }else{
        //cout << "Item is NOT divisible by test value, throwing to false monkey" << endl;
        turn.Monkeys[this->falsemonkey]->items.push_back(this->items[0]);
        this->items.erase(this->items.begin());
        //this->items.erase(auto i = 0, auto b = 1);
        //cout << "Monkey now has " << this->items.size();
        //cout << " items" << endl;
    }
}

int main ()
{
    //TO DO:
    // Auto generate monkeys based on input
    // Auto create items for each monkey based on input



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
    //Begin the real work
    
    int currentitems = 0;

    while (turn.rounds < 20) {
        currentitems = turn.Monkeys[turn.counter]->items.size();
        for (int i = 0; i < currentitems; i++) {
            int cur_worry = 0;
            bool test;
            // Monkey inspects, increases worry level, gets bored, decreases worry level
            turn.Monkeys[turn.counter]->inspections++;
            cur_worry = turn.Monkeys[turn.counter]->GetWorry();
            cur_worry = turn.Monkeys[turn.counter]->Operation(cur_worry);
            // Is worry level divisible by Monkey's test value
            test = turn.Monkeys[turn.counter]->TestItem(cur_worry);
            // Set new worry level on item
            turn.Monkeys[turn.counter]->SetWorry(0, cur_worry);
            //cout << "New worry level = " << turn.Monkeys[turn.counter]->GetWorry() << endl;
            // Throw to Monkey
            turn.Monkeys[turn.counter]->ThrowItem(turn, test);
        }
        //cout << "Next Monkey" << endl;
        //cout << turn.rounds << endl;
        if (turn.rounds == 1) {
            //break;
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
