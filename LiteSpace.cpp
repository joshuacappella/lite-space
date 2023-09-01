/*
 * Recursive solution to problem; runtime too long
 * Lite Space: Problem from kattis.com
 * Joshua Cappella
 * 08/29/2023
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

// converts input to operations
int decode(string i, stack<int> s){

    // stack<int> s;

    // push integer onto stack
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
        decode(i,s);
    }
    // push copy of stack top onto top of stack
    else if(i.substr(0,3) == "SNS"){
        i = i.substr(3);
        if(s.empty()){
            cout << "Invalid copy operation\n";
            decode(i,s);
        }
        s.push(s.top());
        decode(i,s);
    }
    // swap two top stack elements
    else if(i.substr(0,3) == "SNT"){
        i = i.substr(3);
        if(s.size() < 2){
            cout << "Invalid swap operation\n";
            decode(i,s);
        }
        int l = s.top();
        s.pop();
        int m = s.top();
        s.pop();
        s.push(l);
        s.push(m);
        decode(i,s);
    }
    // remove and discard top stack element
    else if(i.substr(0,3) == "SNN"){
        i = i.substr(3);
        if(s.empty()){
            cout << "Invalid remove operation\n";
            decode(i,s);
        }
        s.pop();
        decode(i,s);
    }
    // remove top two stack elements and push their sum onto stack
    else if(i.substr(0,4) == "TSSS"){
        i = i.substr(4);
        if(s.size() < 2){
            cout << "Invalid addition operation\n";
            decode(i,s);
        }
        int l = s.top();
        s.pop();
        int m = s.top();
        s.pop();
        s.push(l+m);
        decode(i,s);
    }
    // remove top two stack elements and push their difference onto stack
    else if(i.substr(0,4) == "TSST"){
        i = i.substr(4);
        if(s.size() < 2){
            cout << "Invalid subtraction operation\n";
            decode(i,s);
        }
        int l = s.top();
        s.pop();
        int m = s.top();
        s.pop();
        s.push(m-l);
        decode(i,s);
    }
    // remove two topmost stack elements and push their product onto stack
    else if(i.substr(0,4) == "TSSN"){
        i = i.substr(4);
        if(s.size() < 2){
            cout << "Invalid multiplication operation\n";
            decode(i,s);
        }
        int l = s.top();
        s.pop();
        int m = s.top();
        s.pop();
        s.push(l*m);
        decode(i,s);
    }
    // remove two top stack elements and push their quotient onto the stack
    else if(i.substr(0,4) == "TSTS"){
        i = i.substr(4);
        if(s.size() < 2){
            cout << "Invalid division operation\n";
            decode(i,s);
        }
        else if(s.top() == 0){
            cout << "Division by zero\n";
            decode(i,s);
        }
        int l = s.top();
        s.pop();
        int m = s.top();
        s.pop();
        int n = (m/l);
        s.push(n);
        decode(i,s);
    }
    // remove the integer on top of stack and print
    else if(i.substr(0,4) == "TNST"){
        i = i.substr(4);
        if(s.empty()){
            cout << "Invalid print operation\n";
            decode(i,s);
        }
        cout << s.top() << endl;
        s.pop();
        decode(i,s);
    }
    return 0;
}

int main(){
    // declarations
    string input = "";
    stack<int> s;

    cin >> input;

    //if(input == "S"){cout << "Hello World\n";}

    decode(input, s);

    return 0;
}