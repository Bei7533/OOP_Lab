#include <iostream>
#include <map>
#include <cstring>
#include <string>

using namespace std;
class CLI{
    public:
    map <string, string> database; // database to store the data
    void pdadd();
    void pdlist(string op);
    void pdshow(string op);
    int pdremove(string op);
    void endOperation();
};

// function to output the dividing line of each operation
void CLI::endOperation(){
    string line;
    line.assign(75, '*');
    cout << line << endl;
}

// operation of "pdadd", that add to the database
void CLI::pdadd(){
    string dateStr, inputStr;
    cin >> dateStr; //the date is in "year/month/day" format
    int firstIN = 1;
    getchar();
    while(getline(cin, inputStr) && inputStr!="."){
        if(firstIN){  // if it's the first line in this diary
            database[dateStr] = inputStr;
            firstIN = 0;
        }else{
            database[dateStr] += "\n";  // store the 'enter'
            database[dateStr] += inputStr; 
        } 
    }
    endOperation();
}

// operation of "pdlist", that list certaion diary in database
void CLI::pdlist(string op){
    if(!database.size()) cout << "No diary" << endl; // database is empty
    int isRange=0;
    string start, end;
    for(int i=6; i<op.size(); i++){
        while(op[i]==' ') i++;
        if(op[i++]=='['){
            isRange=1;
            while(op[i]!=',' && i<op.size())  // get the start key
                start += op[i++];            
            while(op[i]<'0' || op[i]>'9') i++;  // skip the blank
            while(op[i]!=']')   // get the end key
                end += op[i++]; 
        }
    }
    for(auto const& it : database) // list the entity in the range
        if(!isRange ||(isRange && it.first>=start && it.first<=end))
            cout << it.first << endl << it.second << endl;
    endOperation();
}

// operation of "pdshow", that show the dairy in certain date
void CLI::pdshow(string op){
    int i=0;
    string key;
    while(op[i]<'0' || op[i]>'9') i++; // skip the blank
    while((op[i]>='0' && op[i]<='9')|| op[i]=='/')
        key += op[i++];
    if(!database.count(key)) cout << "No found." <<endl;   // if not in the database
    else cout << database[key] << endl;
    endOperation();
}

// operation of "pdmove", that remove diary from database
int CLI::pdremove(string op){
    int i=0;
    string key;
    while(op[i]<'0' || op[i]>'9') i++;  // skip the blank
    while((op[i]>='0' && op[i]<='9')|| op[i]=='/')
        key += op[i++];
    if(!database.count(key)){  // if not in the database
        cout << "No found." << endl;
        endOperation();
        return -1;
    }else{  
        database.erase(key);  // delete the key
        endOperation();
        return 0;
    } 
}

int main(){
    string op;
    CLI myDiary;
    cout << "Please enter your operation: " << endl;
    while(getline(cin, op) && op!="End input"){ // if EOF or input "End input", over
        if(op.substr(0, 5) == "pdadd") myDiary.pdadd();
        else if(op.substr(0, 6) == "pdlist") myDiary.pdlist(op);
        else if(op.substr(0, 6) == "pdshow") myDiary.pdshow(op);
        else if(op.substr(0, 8) == "pdremove") myDiary.pdremove(op);
        cout << "Please enter your operation: " << endl;
    }  
    return 0;
}