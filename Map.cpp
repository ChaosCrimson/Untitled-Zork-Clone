#include <iostream>
#include <string>
#include <map>      //This is almost exactly Java's Map, which is why I used it
#include <ctime>
#include <cstdlib>

using namespace std;

class Game 
{
public:
    // Function to start the game
    void start() 
    {
        srand(time(NULL));
        cout << "Welcome to a Zork Clone by me, ChaosCrimson!" << endl;
        cout << "In order to move a direction type in the name of that direction (e.g. north)" << endl;
        cout << "Never use capital letters when typing commands" << endl;
        cout << "In some rooms, you can look at parts of the environment." << endl; 
        cout << "Type \"lookat \" followed by the item you want to inspect (e.g. lookat bookshelf)" << endl;
        cout << "Some rooms have monsters, which will have a different prompting system." << endl;
        cout << "In order to fight them, type \"fight,\" followed by the monster name." << endl;
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
        map<string, string> roomObjects;  // Map of items in the room (name -> item info)
        map<string, string> enemies;
    };

    map<string, Room> rooms;  // Map of all rooms in the game
    Room currentRoom;         // The current room the player is in

    // Player stats
    int playerHealth = 100;
    int playerAttack = 10;
    int playerMp = 100;

    // Enemy stats
    int enemyHealth;
    int enemyAttack;

    // Function to play the game
    void play() 
    {
        while (true) 
        {
            cout << endl << currentRoom.description << endl;

            // Check if the current room has no exits, indicating the end of the game
            if (currentRoom.exits.empty()) 
            {
                cout << "Congrats! You beat the game!" << endl;
                cout << "Unfortunately, I didn't get to add all the features I wanted, such as being able to have a functional inventory, but I think what I have here is reminicent of the original game." << endl;
                cout << "I am also aware that monsters persist after defeat. This is due to time constraints" << endl;
                cout << "Shortcomings aside, I hope you had fun playing!" << endl;
                break;
            }

            // Check if there's an enemy in the room
            if (!currentRoom.enemies.empty()) 
            {
                for (const auto& enemy : currentRoom.enemies) 
                {
                    cout << "There is a " << enemy.second << " in the room." << endl;
                }
            }

            // Display available exits for the player (debug)
            /*
            cout << "Exits: ";
            for (const auto& exit : currentRoom.exits) 
            {
                cout << exit.first << " ";
            }
            */

            cout << endl << "Enter your choice: ";
            string choice;
            getline(cin, choice);

            // Check if the entered choice is a valid exit or item from the current room
            if (currentRoom.exits.find(choice) != currentRoom.exits.end()) 
            {
                currentRoom = rooms[currentRoom.exits[choice]];
            } 
            else if (currentRoom.roomObjects.find(choice) != currentRoom.roomObjects.end()) 
            {
                cout << currentRoom.roomObjects[choice] << endl;
            } 
            else if (currentRoom.enemies.find(choice) != currentRoom.enemies.end()) 
            {
                startFight(currentRoom.enemies[choice]);
                continue;
            } 
            else 
            {
                cout << "Command not recognized. Try again." << endl;
            }
        }
    }
    
    bool checkMP(int attackCost) {
        if (playerMp - attackCost < 0) 
        {
            cout << "Not enough MP!" << endl;
            return false;
        }
        else
        {
            return true;
        }
        
    }

    void startFight(string choice) 
    {
        string enemyName;
        int input, randomMod, damageMod;
        //Set enemy stats
        if(choice.compare("goblin") == 0) 
        {   //I probably could use a separate struct to handle enemies, but I want to demonstrate a variety of methods
            enemyName = "Goblin";
            enemyHealth = 25;
            enemyAttack = 17;
        } 
        else if(choice.compare("elf") == 0)
        {
            enemyName = "Elf";
            enemyHealth = 45;
            enemyAttack = 12;
        }
        else 
        {
            enemyName = "Spider";
            enemyHealth = 40;
            enemyAttack = 22;
        }
        
        while (playerHealth > 0 && enemyHealth > 0) 
        {
            damageMod = 1;
            randomMod = rand() % 9 - 3;  // Generates a random number between -3 and 5
            
            // I could use setw(), right, and left here, but ill actually implement it later if I have time/ feel like it
            cout << endl << "You                                    " << enemyName << endl;
            cout << "HP: " << playerHealth << "                                 HP: " << enemyHealth << endl;
            cout << "MP: " << playerMp << endl;
            cout << "Choose your Action:" << endl;
            cout << "1 - Normal Attack" << endl;
            cout << "2 - Magic/Bushido" << endl;
            cout << "3 - Defend" << endl << endl;
            cin >> input;

            switch (input) 
            {
                case 1:
                    cout << "You slash your sword and deal " << playerAttack + randomMod << " damage!" << endl;
                    enemyHealth =  enemyHealth - (playerAttack + randomMod);
                    break;

                case 2: 
                    cout << "1 - Fireball" << endl;
                    cout << "2 - Unleash" << endl;
                    cout << "3 - Seiken" << endl << endl;
                    cin >> input;

                    switch (input)
                    {
                    case 1:
                        if (checkMP(8))
                        {
                            cout << "Fire bursts from your fingertips dealing " << 18 + randomMod << " damage!" << endl;
                            playerMp -= 8;
                            enemyHealth -= 18 + randomMod;
                        } 
                        else 
                        {
                            continue;
                        }
                        break;
                    case 2:
                        if (checkMP(18))
                        {
                            cout << "You draw on your weapon's true power and deal " << 37 + randomMod << " damage!" << endl;
                            playerMp -= 18;
                            enemyHealth -= 37 + randomMod;
                        } 
                        else 
                        {
                            continue;
                        }
                        break;
                    case 3:
                        if (checkMP(30))
                        {
                            cout << "You summon a blade of holy light that stabs into your opponent dealing " << 65 + randomMod << " damage!" << endl;
                            playerMp -= 30;
                            enemyHealth -= 65 + randomMod;
                        } 
                        else 
                        {
                            continue;
                        }
                        break;
                    default:
                        continue;
                        break;
                    }
                    break;
                case 3: 
                    cout << "You bolster your defence." << endl;
                    damageMod = 2;
                    break;
                default:
                    continue;
                    break;
            }
            if (enemyHealth <= 0)
                continue;           // Lazy last-second fix
            randomMod = rand() % 9 - 5; // Generates a random number between -5 and 3
            cout << "The " << choice << " attacks you for " << (enemyAttack + randomMod)/damageMod << " damage!" << endl;
            playerHealth = playerHealth - (enemyAttack + randomMod)/damageMod;

        }
        if (playerHealth <= 0) 
        {
            cout << "As you stumble to the ground, your HP drops to zero." << endl;
            cout << "Your final moments are filled with thoughts of all the adventures to be had, all the battles to be won, and all the treasure to be collected." << endl;
            cout << "Perhaps in another timeline you had won this battle.";
            exit(0);
        }
        if (enemyHealth <= 0) 
            cout << "You defeated the " << choice << "!" << endl;
    }

public:
    // Constructor to initialize the game world (rooms and connections)
    Game() 
    {
        // Define rooms and connections here
        // rooms["ROOM_NAME"] = { "DESCRIPTION. TELL PLAYER EXITS.", { { "east", "LOCATION_1" }, { "west", "LOCATION_2" } }, {} };
        rooms["start"] = { "You are in a dark room. There is a door to the north.", { { "north", "hallway" } }, {} };
        rooms["hallway"] = { "You are in a hallway. There are doors to the east and west. The door locks behind you.", { { "east", "library" }, { "west", "bedroom" } }, {} };
        rooms["library"] = { "You are in a dusty library. The exit is to your west. There is a bookshelf to the south.", { { "west", "hallway" } }, 
                        { { "lookat bookshelf", "It is an old bookshelf with various books. One of the books seems to discuss the basics of alchemy." } } };
        rooms["bedroom"] = { "You are in a cozy bedroom. There is a bed to the south, and beside it lies a nightstand with a drawer.", { { "east", "hallway" }, { "north", "connectorL"} }, 
                        { { "lookat bed", "It is a queen sized bed with suprisingly awfully coloured sheets."}, {"lookat nightstand", "You look at the nightstand. The drawer is locked, and the universe shows no indication of it ever being acessible."} }, 
                        { { "fight goblin", "goblin" } } };
        rooms["connectorL"] = { "You are in an L-shaped room, with doors to the north and the west. The southern door leads back to the bedroom.", { { "north", "observatory" }, {"south", "bedroom"}, { "west", "spiderNest" } }, {} };
        rooms["spiderNest"] = { "As you enter the room, you are filled with dread. Cobwebs cover the walls, as well as the northern and western doors, and you can hear skittering sounds.", { { "north", "garden" }, { "east", "connectorL" } }, 
                        { { "lookat cobweb", "As you move to examine the cobweb, you trip and fall and get some in your mouth. Yuck." } }, 
                        { { "fight spider", "spider" } } };
        rooms["observatory"] = { "You reach the observatory. The stars twinkle above you, and light illuminates exits in all directions. There is a telescope in the centre.", { { "north", "" }, { "east", "glitch" }, { "south", "connectorL" }, { "west", "garden" } }, 
                        { { "lookat telescope", "Upon examination, the telescope seems to show a man in the stars. However, that could be a smudge."} } };
        rooms["garden"] = { "You enter an enchanted garden. Colorful flowers surround you. There is a suspiciously large bush to the west. There are doors to the south and the east.", { { "east", "observatory" }, { "south", "spiderNest" }, { "west", "hiddenPassage"} },
                        { { "lookat bush", " As you peek inside the bush, you notice a small hatch. You can now exit to the west!"} }, 
                        { { "fight elf", "elf"} } };
        rooms["hiddenPassage"] = { "You eneter a dark corridor which only exits to the south.", { { "south", "library" } }, {} };
        rooms["glitch"] = { "Reality doesn't look stable here. The northern wall is missing into void, and the southern wall seems to be flickering between brich and drywall. You feel as if you should turn back.", { { "west", "observatory" } },
                        { { "lookat wall", "You are suddenly filled with the urge to say \"xyzzy.\""}, { "xyzzy", "A hollow voice says \"fool\""} } };

    }
};

int main() 
{
    // Create an instance of the game and start playing
    Game game;
    game.start();

    return 0;
}
