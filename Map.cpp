/* Program Name: Epic Battle Fantasy Console
Purpose: Make an epic game
Author: Evan Sakryd
LAST MODIFIED: 12/12/23 */
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Game {
public:
    // Function to start the game
    void start()
    {
        cout << "Welcome to a Zork Clone by me, Evan Sakryd!" << endl;
        cout << "In order to move a direction type in the name of that direction (e.g. north)" << endl;
        cout << "Never use capital letters when yping commands" << endl;
        cout << "In some rooms, you can look at parts of the environemnt." << endl; 
        cout << "Type \"lookat \" followed by the item you want to inspect (e.g. lookat bookself)" << endl;
        cout << "Some rooms have monsters, which will have a different prompting system." << endl;
        cout << "Good luck, and have fun adventuring!" << endl;

        currentRoom = rooms["start"];
        play();
    }

private:
    // Structure representing a room in the game
    struct Room
    {
        string description;
        map<string, string> exits;  // Map of exits from the room (direction -> connected room)
        map<string, string> items;  // Map of items in the room (name -> description)
    };

    map<string, Room> rooms;  // Map of all rooms in the game
    Room currentRoom;         // The current room the player is in

    // Function to play the game
    void play() {
        while (true) {
            cout << endl << currentRoom.description << endl;

            // Check if the current room has no exits, indicating the end of the game
            if (currentRoom.exits.empty())
            {
                cout << "Congratulations! You've reached the end of the game." << endl;
                break;
            }

            // Display available exits for the player
            cout << "Exits: ";
            for (const auto& exit : currentRoom.exits)
            {
                cout << exit.first << " ";
            }

            // Display available items for the player to interact with
            

            cout << endl << endl << "Enter your choice: ";
            string choice;
            getline(cin, choice);

            // Check if the entered choice is a valid exit or item from the current room
            if (currentRoom.exits.find(choice) != currentRoom.exits.end())
            {
                currentRoom = rooms[currentRoom.exits[choice]];
            } else if (currentRoom.items.find(choice) != currentRoom.items.end())
            {
                cout << currentRoom.items[choice] << endl;
            } else
            {
                cout << "Invalid choice. Try again." << endl;
            }
        }
    }

public:
    // Constructor to initialize the game world (rooms and connections)
    Game() 
    {
        // Define rooms and connections here
        rooms["start"] = { "You are in a dark room. There is a door to the north.", { { "north", "hallway" } }, {} };
        rooms["hallway"] = { "You are in a long hallway. There are doors to the east and west.", { { "east", "library" }, { "west", "bedroom" } }, {} };
        rooms["library"] = { "You are in a dusty library. The exit is to your west. There is a bookshelf to the south.", { { "west", "hallway" } }, 
                           { { "lookat bookshelf", "It is an old bookshelf with various books." } } };
        rooms["bedroom"] = { "You are in a cozy bedroom. There is a bed to the north.", { { "east", "hallway" } }, {} };
    }
};

int main() 
{
    // Create an instance of the game and start playing
    Game game;
    game.start();

    return 0;
}
