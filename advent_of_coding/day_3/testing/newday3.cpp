#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;

int main() {
    char characters[2][15];
    ifstream myFile("temp.txt");
    string line;

    int total = 0;

    int place = 0;
    while(getline(myFile, line)) {
        for (int i = 0; i < line.length(); i++) {
            characters[place][i] = line[i];
        }
        place++;
    }

    for(int i = 0; i < 2; i++) {
        for (int j = 0; j < 15; j++) {
            cout << characters[i][j];
        }
        cout << endl;
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 15; j++) {
            if ( characters[i][j] > 47 && characters[i][j] < 58) {
                int n = 1;
                while (characters[i][j+n] > 47 && characters[i][j+n] < 58) {
                    n++;
                }

                cout << "n: " << n << endl;

                int lowerlimx, lowerlimy, upperlimx, upperlimy;
                if ( i == 0 ) {
                    lowerlimy = 0;
                    upperlimy = i+1;
                } else if ( i == 1 ) {
                    lowerlimy = i-1;
                    upperlimy = 1;
                } else {
                    lowerlimy = i-1;
                    upperlimy = i+1;
                }

                if ( j == 0 ) {
                    lowerlimx = 0;
                } else {
                    lowerlimx = j-1;
                }

                if (j+n == 15) {
                    upperlimx = 15;
                } else {
                    upperlimx = j+n+1;
                }
                
                bool breaker = false;
                int temptot = 0;

                for (int t = lowerlimy; t <= upperlimy; t++) {
                    for (int r = lowerlimx; r < upperlimx; r++) {
                        if ( characters[t][r] != 46 && (characters[t][r] < 48 || characters[t][r] > 57) && characters[t][r] >= 33) {
                            // int temptot = 0;
                            int pows = n;

                            for (int t = 0; t < n; t++) {
                                temptot += ((characters[i][j+t] - 48) * pow(10.0, pows - 1));
                                pows--;
                            }

                            cout << temptot << endl;
                            j+=n;

                            breaker = true;
                            break;
                        }
                    }
                    if ( breaker) {
                        break;
                    }
                }




                total += temptot;






               // int temptot = 0;
               // int pows = n;

               // for (int t = 0; t < n; t++) {
               //     temptot += ((characters[i][j+t] - 48) * pow(10.0, pows - 1));
               //     pows--;
               // }

               // cout << temptot << endl;
               // j+=n;
            }
        }
    }

    cout << total << endl;

    return 0;
}
