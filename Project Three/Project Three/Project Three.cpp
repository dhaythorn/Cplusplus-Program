#include <iostream>
#include <map>
#include <string>
#include <fstream>
using namespace std;

class GroceryItems
{
public:
    void populate(ifstream& inFS);
    void search();
    void printFrequency();
    void printHistogram();
private:
    map<string, int> items;
};

void printMenu(GroceryItems& groceryItems);

int main()
{
    GroceryItems groceryItems; // groceryItems object that contains a map hidden internally
    ifstream inFS;

    inFS.open("inventory.txt");

    groceryItems.populate(inFS); // builds the map with the file data

    inFS.close();

    printMenu(groceryItems); // handles the rest of the program
}
void GroceryItems::populate(ifstream& inFS)
{
    map<string, int>::iterator it; // using an iterator find function to see if I should either add a new key or update a current key
    string food;

    inFS >> food;
    while (!inFS.eof())
    {
        it = items.find(food);
        if (it != items.end())
        {
            items .at(food)++;
        }
        else
        {
            items.emplace(food, 1);
        }
        inFS >> food;
    }
}
void printMenu(GroceryItems& groceryItems) // prints the menu and calls the appropriate functions
{
    int ui = 0;
    while (ui != 4)
    {
        cout << "1: Enter a specific food to search. " << endl;
        cout << "2: Print list with a count of each item in the inventory. " << endl;
        cout << "3: Print Histogram. " << endl;
        cout << "4: exit" << endl;
        
        cin >> ui;
        switch (ui)
        {
        case 1:
            groceryItems.search();
            break;
        case 2:
            groceryItems.printFrequency();
            break;
        case 3:
            groceryItems.printHistogram();
            break;
        default:
            break;
        }
    }
}
void GroceryItems::printFrequency()
{
    for (auto &i : items)
    {
        cout << i.first << ": " << i.second << endl;
    }
    cout << endl;
}
void GroceryItems::printHistogram()
{
    for (auto &i : items)
    {
        cout << i.first << " ";
        for (int j = 1; j <= i.second; j++)
        {
            cout << "*";
        }
        cout << endl;
    }
    cout << endl;
}
void GroceryItems::search()
{
    string ui;
    map<string, int>::iterator it;

    cout << "Enter the food you want to find: " << endl;
    cin >> ui;
    it = items.find(ui);

    if (it != items.end())
    {
        cout << it->first << ":" << it->second << endl;
        return;
    }
    else
    {
        cout << "Food not found." << endl;
        return;
    }
}