/* Program Name: Epic Battle Fantasy Console
Purpose: Make an epic game
Author: Evan Sakryd
LAST MODIFIED: 12/12/23 */

#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

int main() {
    int choice;
    int mhp, hp, i, init, atk, def, matk, mdef, hurt, mhurt, agi, magi;
    atk = 10;
    def = 15;
    agi = 5;
    matk = 10;
    mdef = 15;
    magi = 5;

    srand((unsigned)time(0));
    init = rand()%2+1;
    mhp = rand()%50 + 60;
    hp = rand()%20 + 80;
    cout <<"===== Combat Section =====";
    cout << endl;
    cout << endl;
    if (init == 1) {
        cout << "Your move." << endl;
        cout << "==========" << endl;
        while (hp > 0 || mhp > 0) {
            cout << "Choose your move?" << endl;
            cout << "1 - Special Attack" << endl;
            cout << "2 - Normal Attack" << endl;
            cout << "3 - Guard" << endl;
            do{
                cin >> choice;
            } while(choice>3 || choice<1);
            switch (choice) {
            case 1:
                atk = rand()%20+10;
                def = rand()%10+10;
                agi = rand()%5;
                break;
            case 2:
                atk = rand()%5+10;
                def = rand()%10+10;
                agi = rand()%15;
                break;
            case 3:
                atk = rand()%10+10;
                def = rand()%20+10;
                agi = rand()%5;
                break;
            }
            choice = rand()%3;
            switch (choice) {
            case 1:
                matk = rand()%20+10;
                mdef = rand()%10+10;
                magi = rand()%5;
                break;
            case 2:
                matk = rand()%5+10;
                mdef = rand()%10+10;
                magi = rand()%15;
                break;
            case 3:
                matk = rand()%10+10;
                mdef = rand()%20+10;
                magi = rand()%5;
                break;
            }


            mhurt = (atk - magi) - (mdef/atk);
            if (mhurt < 0)
                mhurt = 0;
            mhp = mhp - mhurt;
            cout << "You did "<<mhurt<<" damage to the monster!" << endl;
            cin.get();

            if (mhp < 1) 
            {
            cout << "You killed the monster!! You won with "<<hp<<" hp left."<< endl;
            cin.get();
            return 0;
            }
            cout << "The monster now have "<<mhp<<" hp left."<< endl;
            hurt = (matk - agi) - (def/matk);
            if (hurt < 0)
                hurt = 0;
            hp = hp - hurt;
            cout << "The monster hit you for "<<hurt<<" damage."<< endl;

            if (hp < 1) {
            cout << "You died. The monster still has "<<mhp<<" hp left."<< endl;
            cin.get();
            return 0;
            }
            cout << "You now have "<<hp<<" hp left." << endl << endl;
        }
    
    
    
    }  else {
        cout << "Monster start." << endl << "==============" << endl;
        while (hp > 0 || mhp > 0) {
            choice = rand()%3;
            switch (choice) {
            case 1:
                matk = rand()%20+10;
                mdef = rand()%10+10;
                magi = rand()%5;
                break;
            case 2:
                matk = rand()%5+10;
                mdef = rand()%10+10;
                magi = rand()%15;
                break;
            case 3:
                matk = rand()%10+10;
                mdef = rand()%20+10;
                magi = rand()%5;
                break;
            }

            hurt = (matk - agi) - (def/matk);
            if (hurt < 0)
                hurt = 0;
            hp = hp - hurt;
            cout << "The monster hit you for "<<hurt<<" damage."<< endl;

            if (hp < 1) 
            {
                cout << "You died. The monster still has "<<mhp<<" hp left."<< endl;
                cin.get();
                return 0;
            }
            cout << "You now have "<<hp<<" hp left."<< endl<< endl;
            cout << "Choose your move?" << endl;
            cout << "1 - Critical Attack" << endl;
            cout << "2 - Basic Attack" << endl;
            cout << "3 - Guard" << endl;
            do{
                cin>>choice;
            } while(choice>3 || choice<1);
            switch (choice) {
            case 1:
                atk = rand()%20+10;
                def = rand()%10+10;
                agi = rand()%5;
                break;
            case 2:
                atk = rand()%5+10;
                def = rand()%10+10;
                agi = rand()%15;
                break;
            case 3:
                atk = rand()%10+10;
                def = rand()%20+10;
                agi = rand()%5;
                break;
            }



            mhurt = (atk - magi) - (mdef/atk);
            if (mhurt < 0)
                mhurt = 0;
            mhp = mhp - mhurt;
            cout << "You did " << mhurt <<" damage to the monster!" << endl;
            cin.get();

            if (mhp < 1) {
            cout << "You killed the monster!! You won with " << hp << " hp left." << endl;
            cin.get();
            return 0;
            }
            cout << "The monster now have " << mhp << " hp left."<< endl;
        }
    }
    return 0;
}