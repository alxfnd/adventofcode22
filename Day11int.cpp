#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class Monkey;
class Turn;
class Item;
enum Math {SQUARE, ADD, MULT};

class Item
{
    public:
    int worry;
    Item(int worry);
};

Item::Item(int worry)
{
    this->worry = worry;
}

class Monkey
{
    public:
    vector<Item*> items;
    int inspections = 0;
    Math OpMath;
    int OpValue;
    int TestValue;
    int TrueMonkey;
    int FalseMonkey;
    Monkey(Math OpMath, int OpValue, int TestValue, int TrueMonkey, int FalseMonkey);
    void TakeTurn(vector<Monkey*>& Monkeys);
    int Inspect(int item);
    void Throw(vector<Monkey*>& Monkeys);
};

Monkey::Monkey(Math OpMath, int OpValue, int TestValue, int TrueMonkey, int FalseMonkey) {
    this->OpMath = OpMath;
    this->OpValue = OpValue;
    this->TestValue = TestValue;
    this->TrueMonkey = TrueMonkey;
    this->FalseMonkey = FalseMonkey;
}

void Monkey::TakeTurn(vector<Monkey*>& Monkeys) {
    int count = this->items.size();
    for (int i = 0; i < count; i++) {
        int worry = (int)this->items[0]->worry;
        worry = this->Inspect(worry);
        this->inspections++;
        worry = (int)floor(worry / 3);
        this->items[0]->worry = worry;
        this->Throw(Monkeys);
    }
}

int Monkey::Inspect(int item) {
    int result = 0;
    switch (this->OpMath) {
        case Math::SQUARE:
            result = item * item;
            break;
        case Math::ADD:
            result = item + this->OpValue;
            break;
        case Math::MULT:
            result = item * this->OpValue;
            break;
        default:
            throw new exception();
    }
    return result;
}

void Monkey::Throw(vector<Monkey*>& Monkeys) {
    if ( (this->items[0]->worry % this->TestValue) == 0) {
        Monkeys[this->TrueMonkey]->items.push_back(this->items[0]);
    }else{
        Monkeys[this->FalseMonkey]->items.push_back(this->items[0]);
    }
    this->items.erase(this->items.begin());
}

class Turn
{
    public:
    vector<Monkey*> Monkeys;
    void TakeTurn();
    void Part1();
};

void Turn::TakeTurn() {
    for (int m = 0; m < 8; m++) {
        this->Monkeys[m]->TakeTurn(this->Monkeys);
    }
}

void Turn::Part1() {
    for (int t = 0; t < 20; t++) {
        this->TakeTurn();
    }
    for(int m = 0; m < 8; m++) {
        cout << Monkeys[m]->inspections << endl;
    }
}

int main()
{
    // Create monkeys
    Turn turn;
    //turn.Monkeys.push_back(new Monkey(Math::MULT, 19, 23, 2, 3));
    //turn.Monkeys.push_back(new Monkey(Math::ADD, 6, 19, 2, 0));
    //turn.Monkeys.push_back(new Monkey(Math::SQUARE, 0, 13, 1, 3));
    //turn.Monkeys.push_back(new Monkey(Math::ADD, 3, 17, 0, 1));

    //
    turn.Monkeys.push_back(new Monkey(Math::MULT, 5, 11, 3, 4));
    turn.Monkeys.push_back(new Monkey(Math::SQUARE, 0, 2, 6, 7));
    turn.Monkeys.push_back(new Monkey(Math::MULT, 7, 5, 1, 5));
    turn.Monkeys.push_back(new Monkey(Math::ADD, 1, 17, 2, 5));
    turn.Monkeys.push_back(new Monkey(Math::ADD, 3, 19, 2, 3));
    turn.Monkeys.push_back(new Monkey(Math::ADD, 5, 7, 1, 6));
    turn.Monkeys.push_back(new Monkey(Math::ADD, 8, 3, 0, 7));
    turn.Monkeys.push_back(new Monkey(Math::ADD, 2, 13, 4, 0));

    // Create Items
    /*
    turn.Monkeys[0]->items.push_back(new Item(79));
    turn.Monkeys[0]->items.push_back(new Item(98));
    turn.Monkeys[1]->items.push_back(new Item(54));
    turn.Monkeys[1]->items.push_back(new Item(65));
    turn.Monkeys[1]->items.push_back(new Item(75));
    turn.Monkeys[1]->items.push_back(new Item(74));
    turn.Monkeys[2]->items.push_back(new Item(79));
    turn.Monkeys[2]->items.push_back(new Item(60));
    turn.Monkeys[2]->items.push_back(new Item(97));
    turn.Monkeys[3]->items.push_back(new Item(74));
    */

    // Create Items
    turn.Monkeys[0]->items.push_back(new Item(92));
    turn.Monkeys[0]->items.push_back(new Item(73));
    turn.Monkeys[0]->items.push_back(new Item(86));
    turn.Monkeys[0]->items.push_back(new Item(83));
    turn.Monkeys[0]->items.push_back(new Item(65));
    turn.Monkeys[0]->items.push_back(new Item(51));
    turn.Monkeys[0]->items.push_back(new Item(55));
    turn.Monkeys[0]->items.push_back(new Item(93));

    turn.Monkeys[1]->items.push_back(new Item(99));
    turn.Monkeys[1]->items.push_back(new Item(67));
    turn.Monkeys[1]->items.push_back(new Item(62));
    turn.Monkeys[1]->items.push_back(new Item(61));
    turn.Monkeys[1]->items.push_back(new Item(59));
    turn.Monkeys[1]->items.push_back(new Item(98));

    turn.Monkeys[2]->items.push_back(new Item(81));
    turn.Monkeys[2]->items.push_back(new Item(89));
    turn.Monkeys[2]->items.push_back(new Item(56));
    turn.Monkeys[2]->items.push_back(new Item(61));
    turn.Monkeys[2]->items.push_back(new Item(99));

    turn.Monkeys[3]->items.push_back(new Item(97));
    turn.Monkeys[3]->items.push_back(new Item(74));
    turn.Monkeys[3]->items.push_back(new Item(68));

    turn.Monkeys[4]->items.push_back(new Item(78));
    turn.Monkeys[4]->items.push_back(new Item(73));

    turn.Monkeys[5]->items.push_back(new Item(50));

    turn.Monkeys[6]->items.push_back(new Item(95));
    turn.Monkeys[6]->items.push_back(new Item(88));
    turn.Monkeys[6]->items.push_back(new Item(53));
    turn.Monkeys[6]->items.push_back(new Item(75));

    turn.Monkeys[7]->items.push_back(new Item(50));
    turn.Monkeys[7]->items.push_back(new Item(77));
    turn.Monkeys[7]->items.push_back(new Item(98));
    turn.Monkeys[7]->items.push_back(new Item(85));
    turn.Monkeys[7]->items.push_back(new Item(94));
    turn.Monkeys[7]->items.push_back(new Item(56));
    turn.Monkeys[7]->items.push_back(new Item(89));

    /*
    for(int i = 0; i < 8; i++) {
        cout << "Math: " <<turn.Monkeys[i]->OpMath << endl;
        cout << "Math Value: " << turn.Monkeys[i]->OpValue << endl;
        cout << "Test Value: " << turn.Monkeys[i]->TestValue << endl;
        cout << "True: " << turn.Monkeys[i]->TrueMonkey << endl;
        cout << "False: " << turn.Monkeys[i]->FalseMonkey << endl;
        cout << "Inspects: " << turn.Monkeys[i]->inspections << endl;
        for (int m = 0; m < turn.Monkeys[i]->items.size(); m++) {
            cout << m << " item: " << turn.Monkeys[i]->items[m]->worry << endl;
        }
        cout << endl;
    }
    */

    //turn.Part1();

    return 0;
}
