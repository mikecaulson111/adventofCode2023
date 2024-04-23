#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;



int main() {
    ifstream myFile("input.txt");

    string line;

    vector<char> one;
    vector<char> two;

    string s1, s2;

    int n = 0;

    while(getline(myFile, line)) {
        line = line.substr(line.find(':')+1);
        int t = 0;
        for (int i = 0; i < line.length(); i++) {
            if ( line[i] > 47 && line[i] < 58) {
                if (n == 0) {
                    one.push_back(line[i]);
                } else {
                    two.push_back(line[i]);
                }
            }
            // if (line[i] > 47 && line[i] < 58) {
            //     cout << line[i] << endl;
            // }
        }
        n++;
    }


    // int i1 = stoi(s1);
    // int i2 = stoi(s2);

    for(int i = 0; i < one.size(); i++) {
        cout << one.at(i) << " " << two.at(i) << endl;
    }

    long i1 = 0;
    int n1 = one.size() -1;
    for ( int i = 0; i < one.size(); i++) {
        i1 += (one.at(i) - 48) * pow(10.0, n1);
        n1--;
    }

    long i2 = 0;
    int n2 = two.size() -1;
    for ( int i = 0; i < two.size(); i++) {
        i2 += (two.at(i) - 48) * pow(10.0, n2);
        n2--;
    }

    cout << i1 << endl;
    cout << i2 << endl;
    
    // int i1 = 0;
    // int i2 = 0;

    long long total = 0;

    for(long i = 0; i < i1 + 1; i++) {
        long long first = i;
        long long diff = i1 - i;
        long long tot = first * diff;

        if ( tot > i2 ) {
            total++;
        }
    }

    cout << "TOTAL: " << total << endl;


    myFile.close();
}
