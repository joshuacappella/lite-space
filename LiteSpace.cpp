/*
 * Lite Space: Problem from kattis.com
 * Joshua Cappella
 * 08/31/2023
 */

using namespace std;
#include <iostream>
#include <stack>
#include <string>
#include <cmath>

// get Binary number from front of string converted to base 10
int getBinary(string ints){
    int j = 0;
    ints = ints.substr(1);
    char c;
    string s = "";
    while(c != 'N'){
        c = ints[0];
        //cout << c << endl;
        if(c == 'S'){
            s += "0";
        }
        else if(c == 'T'){
            s += "1";
        }
        //cout << s << endl;
        ints = ints.substr(1);
        //cout << ints << endl;
    }
    ints = ints.substr(1);
    for(int k = 0; s.size() > 0; k++){
        if(s[s.size() - 1] == '1'){
            //cout << k << endl;
            j += pow(2,k);
        }
        //cout << j << endl;
        //cout << s << endl;
        s = s.substr(0, (s.size() - 1));
    }
    //cout << j << endl;
    return j;
}

// removes numerical characters
string trim(string input){
    while(input[0] != 'N'){
        input = input.substr(1);
    }
    input = input.substr(1);
    return input;
}

int main(){
    // declarations
    string i = "";
    stack<int> s;

    cin >> i;

    //if(input == "S"){cout << "Hello World\n";}
    // push number on to stack
    while(i.size() > 0){
        if(i.substr(0,2) == "SS"){
            i = i.substr(2);
            int j = 0;
            if(i.substr(0,1) == "S"){
                j = getBinary(i);
            }
            else{
                j = (-1 * getBinary(i));
            }
            s.push(j);
            i = trim(i);
            //cout << i << endl;
        }
        // push copy of stack top onto top of stack
        else if(i.substr(0,3) == "SNS"){
            i = i.substr(3);
            if(!s.empty()){
                s.push(s.top());
            }
            else{
                cout << "Invalid copy operation\n";
            }
        }
        // swap two top stack elements
        else if(i.substr(0,3) == "SNT"){
            i = i.substr(3);
            if(s.size() > 1){
                int l = s.top();
                s.pop();
                int m = s.top();
                s.pop();
                s.push(l);
                s.push(m);
            }
            else{
                cout << "Invalid swap operation\n";
            }
        }
        // remove and discard top stack element
        else if(i.substr(0,3) == "SNN"){
            i = i.substr(3);
            if(!s.empty()){
                s.pop();
            }
            else{
                cout << "Invalid remove operation\n";
            }
        }
        // remove top two stack elements and push their sum onto stack
        else if(i.substr(0,4) == "TSSS"){
            i = i.substr(4);
            if(s.size() > 1){
                int l = s.top();
                s.pop();
                int m = s.top();
                s.pop();
                s.push(l+m);
            }
            else{
                cout << "Invalid addition operation\n";
            }
        }
        // remove top two stack elements and push their difference onto stack
        else if(i.substr(0,4) == "TSST"){
            i = i.substr(4);
            if(s.size() > 1){
                int l = s.top();
                s.pop();
                int m = s.top();
                s.pop();
                s.push(m-l);
            }
            else{
                cout << "Invalid subtraction operation\n";
            }
        }
        // remove two topmost stack elements and push their product onto stack
        else if(i.substr(0,4) == "TSSN"){
            i = i.substr(4);
            if(s.size() > 1){
                int l = s.top();
                s.pop();
                int m = s.top();
                s.pop();
                s.push(l*m);
            }
            else{
                cout << "Invalid multiplication operation\n";
            }
        }
        // remove two top stack elements and push their quotient onto the stack
        else if(i.substr(0,4) == "TSTS"){
            i = i.substr(4);
            if(s.size() < 2){
                cout << "Invalid division operation\n";
            }
            else if(s.top() == 0){
                cout << "Division by zero\n";
            }
            else{
                int l = s.top();
                s.pop();
                int m = s.top();
                s.pop();
                int n = (m/l);
                s.push(n);
            }
        }
        // remove the integer on top of stack and print
        else if(i.substr(0,4) == "TNST"){
            i = i.substr(4);
            if(s.empty()){
                cout << "Invalid print operation\n";
            }
            else{
                cout << s.top() << endl;
                s.pop();
            }
        }
    }
    return 0;
}