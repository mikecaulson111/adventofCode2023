#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <vector>

using namespace std;

int main() {
    char characters[140][140];
    ifstream myFile("gears.txt");
    string line;

    int total = 0;

    int place = 0;
    while(getline(myFile, line)) {
        for (int i = 0; i < line.length(); i++) {
            characters[place][i] = line[i];
        }
        place++;
    }

    vector<vector<int>>asterPos;

    for(int i = 0; i < 140; i++) {
        for( int j = 0; j < 140; j++) {
            if (characters[i][j] == 42) {
                vector<int> temp;
                temp.push_back(i);
                temp.push_back(j);

                asterPos.push_back(temp);
            }
        }
    }

    vector<vector<int>>numPositions;

    for(int i = 0; i < 140; i++) {
        for(int j = 0; j < 140; j++) {
            if ( characters[i][j] < 58 && characters[i][j] > 47) {
                int n = 1;

                while (characters[i][j+n] > 47 && characters[i][j+n] < 58) {
                    n++;
                } 

                vector<int> temp;
                temp.push_back(i); // row number
                temp.push_back(j); // first postion of number
                temp.push_back(j+n-1); // last position of number

                numPositions.push_back(temp);
                j += n;
            }
        }
    }

    for ( int i = 0; i < asterPos.size(); i++) {
        cout << asterPos.at(i).at(0) << " " << asterPos.at(i).at(1) << endl;
    }
 
    int num1 = -1;

    for (int i = 0; i < asterPos.size(); i++) {
        num1 = -1;
        for (int j = 0; j < numPositions.size(); j++) {
            if (abs(asterPos.at(i).at(0) - numPositions.at(j).at(0)) <= 1) {
                if ( asterPos.at(i).at(1) <= numPositions.at(j).at(2) + 1 && asterPos.at(i).at(1) >= numPositions.at(j).at(1) - 1 ) {
                    // need to find the other number now
                    int n = numPositions.at(j).at(2) - numPositions.at(j).at(1);
                    int beg = numPositions.at(j).at(1);
                    int temptot = 0;
                    int pows = n + 1;
                    for(int t = numPositions.at(j).at(1); t <= numPositions.at(j).at(2); t++) {
                        temptot += (characters[numPositions.at(j).at(0)][t] - 48) * pow(10.0, pows -1 );
                        pows--;
                    }

                    if ( num1 == -1 ) {
                        num1 = temptot;
                    } else {
                        int prevtot = total;
                        total += num1 * temptot;
                        // cout << total << endl;
                    }
                }
            }
        }
    }

    cout << "Total: " << total << endl;

































   //  for(int i = 0; i < 140; i++) {
   //      for (int j = 0; j < 140; j++) {
   //          cout << characters[i][j];
   //      }
   //      cout << endl;
   //  }

   //  for (int i = 0; i < 140; i++) {
   //      for (int j = 0; j < 140; j++) {
   //          if ( characters[i][j] > 47 && characters[i][j] < 58) {
   //              int n = 1;
   //              while (characters[i][j+n] > 47 && characters[i][j+n] < 58) {
   //                  n++;
   //              }


   //              int lowerlimx, lowerlimy, upperlimx, upperlimy;
   //              if ( i == 0 ) {
   //                  lowerlimy = 0;
   //                  upperlimy = i+1;
   //              } else if ( i == 139 ) {
   //                  lowerlimy = i-1;
   //                  upperlimy = 139;
   //              } else {
   //                  lowerlimy = i-1;
   //                  upperlimy = i+1;
   //              }

   //              if ( j == 0 ) {
   //                  lowerlimx = 0;
   //              } else {
   //                  lowerlimx = j-1;
   //              }

   //              if (j+n == 140) {
   //                  upperlimx = 140;
   //              } else {
   //                  upperlimx = j+n+1;
   //              }
   //              
   //              bool breaker = false;
   //              int temptot = 0;

   //              for (int t = lowerlimy; t <= upperlimy; t++) {
   //                  for (int r = lowerlimx; r < upperlimx; r++) {
   //                      if (characters[t][r] == 42) {
   //                          // int temptot = 0;
   //                          int pows = n;

   //                          for (int t = 0; t < n; t++) {
   //                              temptot += ((characters[i][j+t] - 48) * pow(10.0, pows - 1));
   //                              pows--;
   //                          }

   //                          j+=n;

   //                          breaker = true;
   //                          break;
   //                      }
   //                  }
   //                  if ( breaker) {
   //                      break;
   //                  }
   //              }




   //              total += temptot;






   //             // int temptot = 0;
   //             // int pows = n;

   //             // for (int t = 0; t < n; t++) {
   //             //     temptot += ((characters[i][j+t] - 48) * pow(10.0, pows - 1));
   //             //     pows--;
   //             // }

   //             // cout << temptot << endl;
   //             // j+=n;
   //          }
   //      }
   //  }

    cout << total << endl;

    return 0;
}
