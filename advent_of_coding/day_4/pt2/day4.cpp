#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;


int main() {
    ifstream myFile("cards.txt");
    // ifstream myFile("tempCards.txt");

    int total = 0;

    int numCards[209];
    for(int i = 0; i  < 209; i++) {
        numCards[i] = 1;
    }

    string line;
    int placer = 0;
    while(getline(myFile, line)) {
        int pos1 = line.find(":");
        int pos2 = line.find("|");

        vector<int>winning;
        
        string winningsString = line.substr(pos1+1, pos2-pos1 -2);
        int i  = 0;
        while(winningsString[i] == ' ') {
            i++;
        }
        winningsString = winningsString.substr(i);
        istringstream ss(move(winningsString));
       // cout << "winn:" << winningsString << endl;

        for(string val; getline(ss, val, ' ');) {
            if (val.length() > 0) {
                winning.push_back(stoi(val));
            }
        }

       //  for(int i = 0; i < winning.size(); i++) {
       //      cout << winning.at(i) << " ";
       //  }
       //  cout << endl;


        vector<int>myNums;

        string myString = line.substr(pos2+1);
        // cout << myString << endl;

        istringstream ss2(move(myString));
        for(string val; getline(ss2, val, ' ');) {
            if (val.length() > 0) {
                myNums.push_back(stoi(val));
            }
        }

       // for(int i = 0; i < myNums.size(); i++) {
       //     cout << myNums.at(i) << " ";
       // }
       // cout << endl;

        int temptot = 0;

       //  for(int i = 0; i < myNums.size(); i++) {
       //      for(int j = 0; j < winning.size(); j++) {
       //          // cout << myNums.at(i) << " " << winning.at(j) << endl;
       //          if ( winning.at(j) == myNums.at(i)) {
       //              // cout << "HERE" << endl;
       //              if (temptot == 0) {
       //                  temptot = 1;
       //              } else {
       //                  temptot *= 2;
       //              }
       //          }
       //      }
       //  }
       // total += temptot;

       for (int i = 0; i < myNums.size(); i++) {
           for (int j = 0; j < winning.size(); j++) {
               if ( winning.at(j) == myNums.at(i)) {
                   temptot += 1;
               }
           }
       }
        
        for(int i = placer + 1; i < placer + temptot + 1; i++) {
            numCards[i] += numCards[placer];
        }

        cout << temptot <<" " << numCards[placer] << endl;

        total += numCards[placer];

       placer++;
    }


    // cout << stoi(" 23") << endl;

    cout << "TOTAL: " << total << endl;

    myFile.close();
}
