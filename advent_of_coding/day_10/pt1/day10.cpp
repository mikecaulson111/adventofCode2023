#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


long recurFindNext(int arr[], int size) {
    int temparr[size - 1];
    for(int i = 0; i < size - 1; i++) {
        temparr[i] = arr[i+1] - arr[i];
    }

    bool cont = false;
    for(int i = 0; i < size - 1; i++) {
        if ( temparr[i] != 0) {
            cont = true;
            break;
        }
    }

    if ( cont == false ) {
        return 0;
    } else {
        return temparr[size-2] + recurFindNext(temparr, size-1);
    }
}

typedef struct node_t {
    char dir;
    int dist;
} node ;

char findStartingChar(int startx, int starty, vector<vector<node>> vect) {
    char u, d, l ,r;
    if (starty > 0) {
        u = vect.at(starty - 1).at(startx).dir;
    }
    if (starty < vect.size() - 1) {
        d = vect.at(starty + 1).at(startx).dir;
    }
    if (startx > 0) {
        l = vect.at(starty).at(startx - 1).dir;
    }
    if (startx < vect.at(starty).size() - 1) {
        r = vect.at(starty).at(startx + 1).dir;
    }

    // cout << u << d << l << r << endl;

    // up case:
    if (u == '|' || u == 'F' || u == '7') {
        if (d == 'L' || d == '|' || d == 'J') {
            return '|';
        } else if (l == 'L' || l == 'F' || l == '-') {
            return 'J';
        } else if (r == '7' || r == 'J' || r == '-') {
            return 'L';
        }
    } else if (l == 'F' || l == 'L' || l == '-') {
        if (r == '-' || r == 'J' || r == '7') {
            return '-';
        } else if (d == '|' || d == 'J' || d == 'L') {
            return '7';
        }
    } else {
        return 'F';
    }
    //else if (r == '-' || r == 'J' || r == '7') {
    //    if (d == '|' || d == 'L' || d == 'J') {
    //        return 'F';
    //    }
    //}
    return 'Q';
}

void get_next_dir(int *x, int *y, char *prev, vector<vector<node>> vect) {
    char temp = vect.at(*y).at(*x).dir;
    // cout << temp << " prev: " << *prev  << *x << " "<< *y<< endl;

    if (temp == '|') {
        if (*prev == 'D') {
            *y = *y - 1;
        } else {
            *y = *y + 1;
        }
    } else if (temp == '-') {
        if (*prev == 'L') {
            *x = *x + 1;
        } else {
            *x = *x -1;
        }
    } else if (temp == 'F') {
        if (*prev == 'R') {
            *y = *y + 1;
            *prev = 'U';
        } else {
            *x = *x + 1;
            *prev = 'L';
        }
    } else if (temp == 'J') {
        if (*prev == 'U') {
            *x = *x -1;
            *prev = 'R';
        } else {
            *y = *y - 1;
            *prev = 'D';
        }
    } else if (temp == 'L') {
        if (*prev == 'R') {
            *y = *y -1;
            *prev = 'D';
        } else {
            *x = *x +1;
            *prev = 'L';
        }
    } else {
        // 7 case
        if (*prev == 'L') {
            *y = *y + 1;
            *prev = 'U';
        } else {
            *x = *x -1;
            *prev = 'R';
        }
    }
}


int main() {
    // ifstream myFile("temp.txt");
    ifstream myFile("newtemp.txt");
    // ifstream myFile("woah.txt");

    string line;
    long total = 0;
    int startx = -1;
    int starty = -1;

    vector<vector<node>> vect;

    long counter = 0;
    while(getline(myFile, line)) {
        // cout << line << endl;
        // vector<char> myVect(line.begin(), line.end());
        vector<node> myVect;
        for( int i = 0; i < line.length(); i++) {
            node temp;
            temp.dir = line[i];
            if (line[i] == 'S') {
                temp.dist = 0;
                startx = i;
                starty = counter;
            } else {
                temp.dist = -1;
            }
            myVect.push_back(temp);
        }

        vect.push_back(myVect);
        counter++;
    }

    // for ( vector<node> v : vect) {
    //     for (node j : v) {
    //         cout << j.dist;
    //     }
    //     cout << endl;
    // }

    int tposx = startx;
    int tposy = starty;

    char fdir = 'Q';
    char sdir = 'Q';
    char prev = 'Q';
    char prev2 = 'Q';

    char starting = findStartingChar(startx, starty, vect);
    // cout << starting << endl;
    if (starting == '|') {
        fdir = 'U';
        sdir = 'D';
        tposy -= 1;
        prev = 'D';
        prev2 = 'U';
    } else if (starting == 'F') {
        fdir = 'R';
        sdir = 'D';
        tposx += 1;
        prev = 'L';
        prev2 = 'U';
    } else if (starting == '-') {
        fdir = 'R';
        sdir = 'L';
        tposx += 1;
        prev = 'L';
        prev2 = 'R';
    } else if (starting == '7') {
        fdir = 'L';
        sdir = 'D';
        tposx -= 1;
        prev = 'R';
        prev2 = 'U';
    } else if (starting == 'J') {
        fdir = 'U';
        sdir = 'L';
        tposy -= 1;
        prev = 'D';
        prev2 = 'R';
    } else {
        fdir = 'U';
        sdir = 'R';
        tposy -= 1;
        prev = 'D';
        prev2 = 'L';
    }
    cout << "Before first while: " << endl;

    counter = 1;
    while (vect.at(tposy).at(tposx).dir != 'S') {
        vect.at(tposy).at(tposx).dist = counter;

        // need to get the next position, and update prev
        get_next_dir(&tposx, &tposy, &prev, vect);
        // cout << vect.at(tposy).at(tposx).dir << " " << prev << endl;
        // cout << counter << endl;

        counter += 1;
    }

    tposx = startx;
    tposy = starty;
    if (sdir == 'U') {
        tposy -= 1;
    } else if (sdir == 'D') {
        tposy += 1;
    } else if (sdir == 'R') {
        tposx += 1;
    } else if (sdir == 'L') {
        tposy -= 1;
    }
    cout << "Before second while loop" << endl;

    counter = 1;
    while (vect.at(tposy).at(tposx).dir != 'S') {
        if (counter < vect.at(tposy).at(tposx).dist) {
            vect.at(tposy).at(tposx).dist = counter;
        }

        // need to get the next position, and update prev
        get_next_dir(&tposx, &tposy, &prev2, vect);
        // cout << vect.at(tposy).at(tposx).dir << " " << prev << endl;
        // cout << counter << endl;

        counter += 1;
    }

    tposx = startx;
    tposx = starty;

    if (starting == '|') {
        tposy -=1;
        prev = 'D';
    } else if (starting == '-') {
        tposx += 1;
        prev = 'L';
    } else if (starting == 'F') {
        tposx += 1;
        prev = 'L';
    } else if (starting == '7') {
        tposy += 1;
        prev = 'U';
    } else if (starting == 'J') {
        tposy -= 1;
        prev = 'D';
    } else {
        tposy -= 1;
        prev = 'D';
    }
    cout << "Before final while loop> " << endl;

    while ( vect.at(tposy).at(tposx).dir != 'S') {
        if (vect.at(tposy).at(tposx).dist > total) {
            total = vect.at(tposy).at(tposx).dist;
        }

        get_next_dir(&tposx, &tposy, &prev, vect);
    }
    cout << "TOTAL: " << total << endl;

    myFile.close();
}
