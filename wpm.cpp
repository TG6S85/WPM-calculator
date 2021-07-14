#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <vector>
#include <stack>
#include <string>
using namespace std;

/*
  simple typing test that uses short random quotes to give a wpm calculaton
  parts to this project:

  1) sourcing the prompt
    a) use a .txt file of a list of words
    b) generate a string containing 25 random words from the list
  2) timing the test
    a) use ctime to time the test
    b) get the duration of the test when user hits enter
  3) scoring the test
    a) gross wpm formula: ((chars typed)/5)/(time in mins))
    b) net wpm formula: (gross wpm)-(errors/(time in mins))

*/

int main() {
    time_t start; // start time
    time_t end; // end time
    double mins; // total number of mins
    char c; // temp char for input
    stack<char> sc; // stack for the user input
    vector<string> words; // vector of the words
    string prompt; // the prompt
    string entry; // user entry
    int errors = 0; // number of errors, set to 0 at the start
    int linenumb; // line number
    ifstream inFile; // file containing 300 most common words

    inFile.open("prompt.txt");
    int x = 0;
    // Loop to add all of the words from the file to the vector
    while(!inFile.eof()){
      getline(inFile,prompt);
      x++;
      words.push_back(prompt);
    }
    inFile.close();

    //Generate the prompt string using 25 random words from our vector
    prompt = "";
    srand(time(0));
    for(int i = 0; i<25; i++) {
      linenumb = rand() % x;
      prompt += words[linenumb];
      prompt += " ";
    }
    cout << prompt << endl;
    // after displaying this text, we start our timer
    time(&start);
    // run the operation where while enter is not entered, we take in the chars
    while ( cin.get(c) && c!='\n')
        sc.push(c);
    time(&end); // right when the while loop closes, log the end time
    cout << endl;
    mins = difftime(end,start)/60; // calc mins

    while ( !sc.empty() )  {
        entry+=sc.top();
        sc.pop();
    }

    reverse(entry.begin(),entry.end());

    for( int i = 0; i < prompt.length(); i++ )
    {
        if(entry[i] != prompt[i]){
          ++errors;
        }
    }

    cout << endl;
    int wpm = (entry.length()/5)/mins;
    int raw_wpm = ((entry.length()-errors)/5)/mins;
    cout<<"WPM: " << wpm << endl;
    cout << "Raw WPM: " << raw_wpm << endl;
    cout << errors << " errors." << endl;
}
