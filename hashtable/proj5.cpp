#include "passserver.h"
#include <iostream>
#include <string>
using namespace std;

void Menu();

int main()
{
  char input;
  size_t size;
  cout << "Enter hash table capacity: ";
  cin >> size;
  PassServer table(size);
  string username, password, newPass, file;

  do
  {
    Menu();
    cin >> input;
    cin.ignore();
        switch(input)
        {
        case 'l':
            cout << "\nEnter password file name to load from: ";
            getline(cin, file);
            if(table.load(file.c_str()))    // convert to cstring
                cout << "\nFile successfully loaded.";
            else
                cout << "\nError: Cannot open file " << file;
            break;

        case 'a':
            cout << "\nEnter username: ";
            getline(cin, username);
            cout << "\nEnter password: ";
            getline(cin, password);

            if(table.addUser({username, password}))
                cout << "\nUser added.";
            else
                cout << "\nError: User not added.";
            break;

        case 'r':
            cout << "\nEnter username: ";
            getline(cin, username);
            if(table.removeUser(username))
                cout << "\nUser deleted.";
            else
                cout << "\nError: User not deleted.";
            break;

        case 'c':
            cout << "\nEnter username: ";
            getline(cin, username);
            cout << "\nEnter current password: ";
            getline(cin, password);
            cout << "\nEnter new password: ";
            getline(cin, newPass);

            if(table.changePassword({username, password}, newPass))
                cout << "\nPassword successfully changed.";
            else
                cout << "\nError: Password not changed.";
            break;

        case 'f':   
            cout << "\nEnter username: ";
            getline(cin, username);
            if(table.find(username))
                cout << "\nUser successfully found.";
            else
                cout << "\nError: User not found.";
            break;

        case 'd':   
            table.dump();
            break;

        case 's':   
            cout << "\nCurrent size: " << table.size();
        case 'w':   
            cout << "\nEnter file name: ";
            getline(cin, file);
            if(table.write_to_file(file.c_str()))   
                cout << "\nFile created.";
            else
                cout << "\nError: File not created.";
            break;
        case 'x':   break;
        }

  } while (input != 'x');
  return 0;
}

void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}
