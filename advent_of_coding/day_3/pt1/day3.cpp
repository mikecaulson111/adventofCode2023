#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

int main() {
    int total = 0;

    ifstream myFile("temp.txt");

    char characters[140][140];
    int place = 0;
    string line;

    while(getline(myFile, line)) {
        for (int i = 0; i < line.length(); i++) {
            characters[place][i] = line[i];
        }
        place++;
    }

    // first need to find each number, then take that number with start and end index
    // then need to check all squares around said number for a symbol, if symbol, add number to total, move on
    for (int i = 0; i < 1; i++) {
        for(int j = 0; j < 140; j++) {
            if (characters[i][j] > 47 && characters[i][j] < 58) {
                int n = 1;
                while (characters[i][j+n] > 47 && characters[i][j+n] < 58) {
                    n++;
                }
                int end = n+j - 1; // maybe -1?

                int temptot = 0;
                bool continues = true;

                for (int t = (j > 0) ? j-1 : j; t < (end < 139) ? end + 1 : end; t++) {
                    for (int k = (i > 0) ? i-1: i; k < (i < 139) ? i + 1 : i; k++) {
                        // actually check the places:
                        if ( characters[k][t] != 46 && (characters[k][t] >= 58 || characters[k][t] <= 47)) {
                           int counter = n;
                           for(int p = j; p < end; p++) {
                                temptot += ((characters[i][p] - 48) * (int)(pow(10, counter)));
                                counter--;
                           }
                           total += temptot;
                           continues = false;
                           break;
                        }
                    }
                    if (!continues) {
                        break;
                    }
                }
                j += n + 1;
            }
        }
    }

    cout << total << endl;
    
    myFile.close();
    return 0;
}
