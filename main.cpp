
/*
  Name: Utkrista Mardan Basnyat
  Course: COMSC-210 Data Structures
  Lab 24: Goat Manager 3002
  File: main.cpp
*/

#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "Goat.h"

using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(set<Goat> trip);
void delete_goat(set<Goat> &trip);
void add_goat(set<Goat> &trip, string [], string []);
void display_trip(set<Goat> trip);
int main_menu();

int main() {
  srand(time(0));

  string names[SZ_NAMES];
  string colors[SZ_COLORS];

  // read goat names
  ifstream fin("names.txt");
  int nameCount = 0;

  while (nameCount < SZ_NAMES && fin >> names[nameCount])
    nameCount++;

  fin.close();

  // read goat colors
  ifstream fin1("colors.txt");
  int colorCount = 0;

  while (colorCount < SZ_COLORS && fin1 >> colors[colorCount])
    colorCount++;

  fin1.close();

  if (nameCount != SZ_NAMES || colorCount != SZ_COLORS) {
    cout << "Error: Could not load names and colors." << endl;
    return 1;
  }

  // store goats in a set
  set<Goat> trip;
  bool again = true;

  while (again) {
    int choice = main_menu();

    if (choice == 1) {
      add_goat(trip, names, colors);
    }
    else if (choice == 2) {
      delete_goat(trip);
    }
    else if (choice == 3) {
      display_trip(trip);
    }
    else if (choice == 4) {
      cout << endl << "Goodbye!" << endl;
      again = false;
    }
  }

  return 0;
}

// display the required menu and validate input
int main_menu() {
  int choice;

  while (true) {
    cout << endl;
    cout << "*** GOAT MANAGER 3001 ***" << endl;
    cout << "[1] Add a goat" << endl;
    cout << "[2] Delete a goat" << endl;
    cout << "[3] List goats" << endl;
    cout << "[4] Quit" << endl;
    cout << "Choice --> ";

    if (cin >> choice && choice >= 1 && choice <= 4)
      return choice;

    if (cin.eof())
      return 4;

    cout << "Invalid choice. Please enter 1-4." << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}

// add a randomly generated goat to the set
void add_goat(set<Goat> &trip, string names[], string colors[]) {
  string name = names[rand() % SZ_NAMES];
  int age = rand() % (MAX_AGE + 1);
  string color = colors[rand() % SZ_COLORS];

  Goat newGoat(name, age, color);

  pair<set<Goat>::iterator, bool> result = trip.insert(newGoat);

  if (result.second) {
    cout << endl << "Goat added successfully!" << endl;
    cout << "Name: " << newGoat.get_name() << endl;
    cout << "Age: " << newGoat.get_age() << endl;
    cout << "Color: " << newGoat.get_color() << endl;
  }
  else {
    cout << endl << "This goat already exists in the set." << endl;
  }

  cout << "Total goats: " << trip.size() << endl;
}

// display the goats in sorted order
void display_trip(set<Goat> trip) {
  cout << endl << "Current Goat Trip:" << endl;

  if (trip.empty()) {
    cout << "No goats in the trip." << endl;
    return;
  }

  int number = 1;

  for (Goat goat : trip) {
    cout << "[" << number << "] "
         << goat.get_name() << " ("
         << goat.get_age() << ", "
         << goat.get_color() << ")" << endl;
    number++;
  }

  cout << "Total goats: " << trip.size() << endl;
}

// display goats and validate the selected number
int select_goat(set<Goat> trip) {
  display_trip(trip);

  if (trip.empty())
    return 0;

  int selection;

  while (true) {
    cout << "Select a goat to delete (1-"
         << trip.size() << "): ";

    if (cin >> selection &&
        selection >= 1 &&
        selection <= static_cast<int>(trip.size())) {
      return selection;
    }

    if (cin.eof())
      return 0;

    cout << "Invalid selection. Please try again." << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}

// delete the selected goat from the set
void delete_goat(set<Goat> &trip) {
  if (trip.empty()) {
    cout << endl << "No goats available to delete." << endl;
    return;
  }

  int selection = select_goat(trip);

  if (selection == 0)
    return;

  set<Goat>::iterator it = trip.begin();

  for (int i = 1; i < selection; i++)
    it++;

  string deletedName = it->get_name();
  trip.erase(it);

  cout << endl;
  cout << "Goat \"" << deletedName
       << "\" deleted successfully!" << endl;
  cout << "Total goats remaining: " << trip.size() << endl;
}
