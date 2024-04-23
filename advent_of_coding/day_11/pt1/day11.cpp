#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;



typedef struct gal_t {
    int x;
    int y;
} gal;

int main() {
    ifstream myFile("input.txt");
    // ifstream myFile("woah.txt");

    string line;
    long total = 0;

    vector<vector<char>> vect;
    vector<gal> gals;
    while(getline(myFile, line)) {
        // cout << line << endl;
        vector<char> myVect;
        bool test = true;
        for ( char c : line ) {
            myVect.push_back(c);
            if (c != '.') {
                test = false;
            }
        }

        if (test) {
            vect.push_back(myVect);
        }
        vect.push_back(myVect);
    }

    cout << vect.at(0).size() << endl;
    int si = vect.at(0).size();
    for (int i = 0; i < vect.at(0).size(); i++) {
        // cout << i << endl;
        bool test = true;
        for (int j = 0; j < vect.size(); j++) {
            if (vect.at(j).at(i) != '.') {
                test = false;
                break;
            }
        }
        
        if (test) {
            for (int j = 0; j < vect.size(); j++) {
                vect.at(j).insert(vect.at(j).begin() + i, '.');
            }
            i++;
        }
    }

    for (int i = 0; i < vect.size(); i++) {
        for (int j = 0; j < vect.at(0).size(); j++) {
            if (vect.at(i).at(j) == '#') {
                gal temp;
                temp.x = j;
                temp.y = i;
                gals.push_back(temp);
            }
        }
    }

    for ( vector<char> v : vect ) {
        for (char c : v ) {
            cout << c;
        }
        cout << endl;
    }

    for (int i = 0; i < gals.size(); i++) {
        for (int j = i+1; j < gals.size(); j++) {
            int posx = gals.at(j).x-gals.at(i).x;
            if (posx < 0) {
                posx = -posx;
            }
            int posy = gals.at(j).y-gals.at(i).y;
            if (posy < 0) {
                posy = -posy;
            }
            total += (posx+posy);
        }
    }

    
    cout << "TOTAL: " << total << endl;

    myFile.close();
}
