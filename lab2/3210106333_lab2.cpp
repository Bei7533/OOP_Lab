#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<algorithm>
#include<windows.h>

using namespace std;

//build a list to store the message of each student
typedef struct student* studentNode; 
struct student{
    string StudentName; 
    map <string, int> studentScores; //store the score of students by a map
    studentNode next;
    student(string n, map<string, int> s):
        StudentName(n), studentScores(s), next(NULL){}

    double studentAverage(){     //function to calculate the average score of a student
        int sum = 0;
        map <string, int> *scorePrt = &studentScores;
        for(auto p=scorePrt->begin(); p!=scorePrt->end(); p++)
            sum += p->second;
        return 1.0*sum/studentScores.size();
    }
};

//build a list to store the message of each subject
typedef struct subject* subjectNode;
struct subject{
    string subjectName;
    int scoreSum;  //the sum of the scores
    int maxScores;
    int minScores;
    int numofStu; //store the number of students who take this class
    subjectNode Next;
    subject(string n, int s):
        subjectName(n), scoreSum(s), maxScores(s), minScores(s), numofStu(1), Next(NULL){}

    void isMaxMin(int s){ //function to find the max and min score
        if(s>maxScores) maxScores = s;
        else if(s<minScores) minScores = s;
    }
};

studentNode stuHead = NULL;
subjectNode subHead = NULL;

//function to find the certain string in the subject list
subjectNode inSubjectList(string subName){ 
    subjectNode p = subHead;
    while(p){
        if(p->subjectName == subName){
            return p;
        }
        p = p->Next;
    }
    return NULL;
}

//do the input
void input(){
    string name, subjectN;
    int score, num = 0;
    studentNode stuTail;
    subjectNode subTail;
    cout << "Input the name of No. "<< num+1 <<" student, or input 'end' to end the input:\n";
    cin >> name;
    while(name != "end"){ //when the input is 'end', the input end
        cout << "Input the pairs of subject and score of this student and input 'over' if you want:\n";
        cin >> subjectN;     //store the name of subject the student took
        map <string, int> curScores = {};
        subjectNode cur = NULL;
        while(subjectN!="over"){ //when input over than go to another student
            cin >> score; 
            curScores[subjectN] = score; //store the score into the map in student's node
            if(!subHead){  //if the head is null
                subHead = new struct subject(subjectN, score);
                subTail = subHead;
            }else{
                cur = inSubjectList(subjectN);
                if(!cur){  //if the subject is the fisrt time to be inputed, build new
                    subjectNode q = new struct subject(subjectN, score);
                    subTail->Next = q;
                    subTail = subTail->Next;
                }else{  //if the subject has already stored, add to the sum and num
                    cur->numofStu ++;
                    cur->scoreSum += score;
                    cur->isMaxMin(score);
                }
            }
            cin >> subjectN;
        }
        studentNode p = new struct student(name, curScores);
        if(!stuHead){ //if the head is null
            stuHead = p;
            stuTail = stuHead;
        }else{
            stuTail->next = p;
            stuTail = p;
        }
        num ++; //the num of students ++
        cout << "Input the name of No. "<< num+1 <<" student, or input 'end' to end the input:\n";
        cin >> name;
    }
    return;
}

//do the output
void output(){
    cout << "no\tname\t";
    subjectNode q = subHead;
    while(q){ //output the title of the result
        cout << q->subjectName << '\t';
        q = q->Next;
    }
    cout << "average\n"; 
    studentNode cur = stuHead;
    int i=1;
    while(cur){ //output each student's grades
        cout << i++ << '\t' << cur->StudentName<<'\t';
        q = subHead;
        while(q){ //output the student's score of each subject
            auto isFind = cur->studentScores.find(q->subjectName);
            if(isFind != cur->studentScores.end())
                cout << cur->studentScores[q->subjectName] << '\t';
            else 
                cout << "null\t";
            q = q->Next;
        }
        cout << cur->studentAverage(); //output the average of a students'scores
        cout << '\n';
        cur = cur->next;
    }
    cout << "\taverage\t";
    q = subHead;
    while(q){ //output the average score of the subject
        cout << 1.0*q->scoreSum/q->numofStu << '\t';
        q = q->Next;
    } 
    cout << "\n\tmin\t";
    q = subHead;
    while(q){ //output the min score of the subject
        cout << q->minScores << '\t';
        q = q->Next;
    } 
    cout << "\n\tmax\t";
    q = subHead;
    while(q){ //output the max score of the subject
        cout << q->maxScores << '\t';
        q = q->Next;
    } 

    cout << '\n';
}

void freeStu(studentNode p){
    if(!p) return;
    else p = p->next;
    delete p;
}

void freeSub(subjectNode p){
    if(!p) return;
    else p = p->Next;
    delete p;
}

int main(){
    input();
    output();
    studentNode p = stuHead;
    subjectNode q = subHead;
    freeStu(p);
    freeSub(q);
    system("PAUSE");
    return 0;
}