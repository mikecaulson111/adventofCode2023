#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;



int main() {
    ifstream myFile("input.txt");

    string line;

    vector<int> one;
    vector<int> two;

    int n = 0;

    while(getline(myFile, line)) {
        line = line.substr(line.find(':')+1);
        cout << line << endl;
        istringstream ss(move(line));
        for(string var; getline(ss, var, ' ');) {
            if (var.length() != 0) {
                if(n == 0) {
                    one.push_back(stoi(var));
                } else {
                    two.push_back(stoi(var));
                }
            }
        }
        n++;
    }

    for(int i = 0; i < one.size(); i++) {
        cout << one.at(i) << " " << two.at(i) << endl;
    }

    int total = 1;

    for(int i = 0; i < one.size(); i++) {
        int num = 0;
        for(int j = 0; j < one.at(i)+1; j++) {
            int acc = j;
            int diff = one.at(i) - j;
            int tot = acc * diff;

            if ( tot >= two.at(i)) {
                num++;
            }
        }

        if ( num != 0 ) {
            total *= num;
        }
    }

    cout << "TOTAL: " << total << endl;


    myFile.close();
}
