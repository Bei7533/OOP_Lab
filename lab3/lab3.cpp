#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

class room{
public:
    string roomName;
    int role;  // role=0, nothing in the room; =1, the princess is in the room; =-1, the monster
    map<string, room*> door;  // use map to store the exits
    room(string n): roomName(n), role(0){ } 
};

vector<room> roomList; // vector to record all the room
unsigned int seed;

// function to create princess or monster in the rooms
void createRole(int roomNum){
    srand(seed); 
    int princess = rand() % (roomNum-1) + 1; // princess and monster not in the lobby
    int monster = rand() % (roomNum-1) + 1;
    while(princess==monster) monster = rand() % roomNum; // make the two in different room
    roomList[princess].role = 1;    // add the tag
    roomList[monster].role = -1;
}

// function to calculate the opp
int oppoDirect(int cur){
    int oppo;
    switch (cur){
    case 0:   // direction = {"up", "down", "left", "right"};
        oppo = 1;
        break;
    case 1:
        oppo = 0;
        break;
    case 2:
        oppo = 3;
        break;
    case 3:
        oppo = 2;
        break;
    default:
        break;
    }
    return oppo;
}

// buile the castle with ramdom rooms
void buildCastle(int roomNum){
    for(int i=0; i<roomNum; i++){   // initial the room
        string roomN;
        if(!i){
            roomN = "lobby";
            roomList.push_back(room(roomN));    // except lobby, the room named room1, room2...
            continue;
        }
        roomN = "room" + to_string(i);
        roomList.push_back(room(roomN));
    }
    vector<string> direction = {"up", "down", "left", "right"};
    for(int i=1; i<roomNum; i++){
        srand(seed);  // set the seed
        int parent = rand() % i;
        while(roomList[parent].door.size() == 4) // if the size is 4, remake the parent
            parent = rand() % i;   
        int direct = rand() % 4;
        while(roomList[parent].door.count(direction[oppoDirect(direct)]))
            direct = rand() % 4;
        roomList[i].door[direction[direct]] = &roomList[parent];    // connect the room
        roomList[parent].door[direction[oppoDirect(direct)]] = &roomList[i];
    }
    createRole(roomNum);
}

// find the princess
int isFind = 0;
void findPrincess(room* curRoom){
    cout << "Welcome to the " << curRoom->roomName << ". ";  
    if(isFind && curRoom->roomName == "lobby"){ // if find the princess and return to lobby, then success
        cout << "Congratulation! You take the princess out the castle." << endl;
        return;
    }
    if(curRoom->role==1){   // find the princess
        cout << endl << "******You find the princess. Now you need to take her back to the lobby******" << endl;
        curRoom->role = 0;
        isFind = 1;
    }else if (curRoom->role==-1){   // meet the monster
        cout << endl << "******You get into the room with monster, you dead.******" << endl;
        return;
    }
    // output the exists
    cout << "There are " << curRoom->door.size() << " exits: ";
    int count = 0;
    for (auto const& pair : curRoom->door){
        cout << pair.first; 
        count ++;
        if(count == curRoom->door.size()-1){
            cout << " and ";
        }else if(curRoom->door.size()!=1 && count != curRoom->door.size()){
            cout << ", ";
        }
    }
    cout << "." << endl << "Enter your command: " << endl;
    // get the input
    string nextRoom, go;
    cin >> go >> nextRoom;
    while(!curRoom->door.count(nextRoom)){  // if input wrong, repeated
        cout << "There is no exit to " << nextRoom << ". Please enter your command again: " << endl;
        cin >> go >> nextRoom;
    }
    findPrincess(curRoom->door[nextRoom]);
}

int main(){
    cout << "Please input the num of room: ";
    int roomNum;  // set the room of castle
    cin >> roomNum;
    cout << "Please input the seed(-1 means ramdom): ";
    cin >> seed;
    while(roomNum<=2){
        cout << "The num of room should be bigger than three, please print again: ";
        cin >> roomNum;
    }
    buildCastle(roomNum);
    findPrincess(&roomList[0]);
}

