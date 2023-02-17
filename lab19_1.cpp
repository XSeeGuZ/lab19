#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names, vector<int> &scores,vector<char> &grades){
    ifstream input(filename);
    string s;
    while (getline(input,s))
    {
      char format[]="%[^:]:%d %d %d";
      char name[100];
      int a,b,c;
      sscanf(s.c_str(),format,name,&a,&b,&c);
      names.push_back(name);
      int sum;
      sum=a+b+c;
      scores.push_back(sum);
      grades.push_back(score2grade(sum));
    }
    input.close();
}

void getCommand(string &command,string &key){
    string input;
    cout << "Please input your command: ";
    getline(cin,input);
    int start=0;
    int end = input.find_last_of(input);
    int space=input.find_first_of(" ");
    command = input.substr(start,space-start);
    key = input.substr(space+1,end-space);
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
cout << "---------------------------------" << "\n";
int count=0;
    for (unsigned int i = 0; i < names.size(); i++)
    {
        if(toUpperStr(names[i])==key){
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            count++;
        }
    }
    if(count==0){
        cout << "Cannot found."<< endl;
    }
cout << "---------------------------------" << "\n";
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grades,string key){
cout << "---------------------------------" << "\n";
int count=0;
    for (unsigned int i = 0; i < grades.size(); i++)
    {
        if(grades[i]==*key.c_str()){
            cout << names[i] << " ("<< scores[i] << ")" << endl;
            count++;
        }
    }
    if(count==0){
        cout << "Cannot found." << endl;
    }
cout << "---------------------------------" << "\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
