#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;


int main() {
    ifstream myFile("games.txt");
    // ifstream myFile("tempgame.txt");
    cout << "Hello world!" << endl;

    int red = 12; int green = 13; int blue = 14;

    int marbles[] = {-1,-1,-1};  // red, green, blue

    // string colors[] = {"red","green","blue"};
    map<string,int> colors = {
        {"red", 0},
        {"green", 1},
        {"blue", 2}
    };

    string line;
    int total = 0;
    int place = 1; // this is the game number

    while(getline(myFile, line)) {
        marbles[0] = -1;
        marbles[1] = -1;
        marbles[2] = -1;

        int colonplace = line.find(":");
        line = line.substr(colonplace + 2, line.length() - colonplace + 1);

        cout << line << endl;
        
        istringstream ss(move(line));
        
        bool working = false;
        int counter = 0;

        for (string val; getline(ss, val, ';');) {
           // istringstream ss2(move(val));
           // for(string val2; getline(ss2, val2, ';');) {
           //      cout << val << endl;
           // }
           // cout << val.substr(1) << endl;
            if (val[0] == ' ') {
                val = val.substr(1);
            }
            counter = 0;
            
            string operating = val.substr(0);
            for(int i = 0; i < 3; i++) {
                counter++;
                // cout << operating << endl;
                if (operating[0] == ' ') {
                    operating = operating.substr(1);
                }
                int newcolplace = operating.find(',');
                string tstring;
                if (newcolplace > 0 ) {
                    tstring = operating.substr(0, newcolplace);
                    int temp = stoi(tstring.substr(0,tstring.find(' ')));
                    string col = tstring.substr(tstring.find(' ') + 1);
                    // cout << "temp " << temp << " and color " << col << endl;
                    operating = operating.substr(newcolplace + 1);
                    if (temp > marbles[colors[col]]) {
                        marbles[colors[col]] = temp;
                    }
                } else {
                    //...
                    int temp = stoi(operating.substr(0, operating.find(' ')));
                    string col = operating.substr(operating.find(' ') + 1);
                    // cout << "FINAL temp " << temp << " and color " << col << endl;
                    if (temp > marbles[colors[col]]) {
                        marbles[colors[col]] = temp;
                    }
                    break;
                }
            }

            cout << val << endl;
            cout << marbles[0] << " " << marbles[1] << " " << marbles[2] << endl;
        }

       //  if (marbles[0] <= red && marbles[1] <= green && marbles[2] <= blue) {
       //      // working = true;
       //      total += place;
       //  }
        for( int i = 0; i < 3; i++) {
            if (marbles[i] == -1) {
                marbles[i] = 1;
            }
        }
        total += (marbles[0] * marbles[1] * marbles[2]);

        place++;
    }

    cout << "TOTAL: " << total << endl;

    myFile.close();
    return 0;
}
