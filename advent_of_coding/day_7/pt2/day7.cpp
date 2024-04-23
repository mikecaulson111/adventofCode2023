#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct hand {
    int rank; // 0 = high_card, ..., 6 = five of a kind
    char cards[5]; // holds the actual cards in order
    int bid; // the  bid for the hand
};

map<char,int> ranks;


int getRank(struct hand sand) {
    int arr[13]; // index 0 -> card 2, ..., index 12 -> card A
    for(int i = 0; i < 13; i++) {
        arr[i] = 0;
    }
    for(int i = 0; i < 5; i++) {
        if (sand.cards[i] < 58) {
            arr[sand.cards[i]-50] += 1;
        } else if (sand.cards[i] == 'A') {
            arr[12] += 1;
        } else if (sand.cards[i] == 'K') {
            arr[11] += 1;
        } else if (sand.cards[i] == 'Q') {
            arr[10] += 1;
        } else if (sand.cards[i] == 'J') {
            arr[9] += 1;
        } else if (sand.cards[i] == 'T') {
            arr[8] += 1;
        }
    }

    int rank = -1;
    bool con = true;
    int num3 = 0;
    int num2 = 0;

    for (int j = 0; j < 13; j++) {
        if ( arr[j] == 5) {
            rank = 6; // five of a kind
            break;
        } else if (arr[j] == 4) {
            if (j == 9 || arr[9] == 1) {
                rank = 6; // five of a kind with J
            } else {
                rank = 5; // four of a kind
            }
            break;
        } else if (arr[j] == 3) {
            num3++;
        } else if (arr[j] == 2) {
            num2++;
        }
    }

    // cout << "num2: " << num2 << " num3 " << num3 << endl;

    if (rank == -1) {
        if ( num3 != 0 && num2 != 0) {
            if ( arr[9] 
            rank = 4; // full house
        } else if (num3 != 0) {
            rank = 3; // three of a kind
        } else if (num2 == 2) {
            rank = 2; // two pair
        } else if (num2 == 1) {
            rank = 1; // one pair
        } else {
            rank = 0; // high card
        }
    }

    return rank;
}

void bubblesort(struct hand arr[], int n) {
    int i, j;
    bool swapped;
    for(i = 0; i < n -1; i++) {
        swapped = false;
        for(j=0; j < n-i - 1; j++) {
            if (arr[j].rank > arr[j+1].rank) {
                struct hand temp;
                temp.rank = arr[j].rank;
                temp.bid = arr[j].bid;
                for(int k = 0; k < 5; k++) {
                    temp.cards[k] = arr[j].cards[k];
                }
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapped = true;
            }
        }
        if (swapped = false) {
            break;
        }
    }

    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n-i-1; j++) {
            if ( arr[j].rank == arr[j+1].rank) {
                for(int k = 0; k < 5; k++) {
                    if (ranks[arr[j].cards[k]] > ranks[arr[j+1].cards[k]]) {
                        struct hand temp;
                        temp.rank = arr[j].rank;
                        temp.bid = arr[j].bid;
                        for(int c = 0; c < 5; c++) {
                            temp.cards[c] = arr[j].cards[c];
                        }
                        arr[j] = arr[j+1];
                        arr[j+1] = temp;
                        break;
                    } else if (ranks[arr[j].cards[k]] < ranks[arr[j+1].cards[k]]) {
                        break;
                    }
                }
            }
        }
    }

    /*
    for(i = 0; i < n; i++) {
        cout << arr[i].rank;
        cout << " " << arr[i].bid;
        for(j = 0; j < 5; j++) {
            cout << " " << arr[i].cards[j];
        }
        cout << endl;
    }
    */
}

int main() {
    ifstream myFile("input.txt");
    // ifstream myFile("temp.txt");
    string line;

    vector<struct hand> hands;

    ranks.insert(pair<char,int>('2',0));
    ranks.insert(pair<char,int>('3',1));
    ranks.insert(pair<char,int>('4',2));
    ranks.insert(pair<char,int>('5',3));
    ranks.insert(pair<char,int>('6',4));
    ranks.insert(pair<char,int>('7',5));
    ranks.insert(pair<char,int>('8',6));
    ranks.insert(pair<char,int>('9',7));
    ranks.insert(pair<char,int>('T',8));
    ranks.insert(pair<char,int>('J',9));
    ranks.insert(pair<char,int>('Q',10));
    ranks.insert(pair<char,int>('K',11));
    ranks.insert(pair<char,int>('A',12));

    // cout << "MAPP T: " << ranks['T'] << endl;

    while(getline(myFile, line)) {
        istringstream ss(move(line));
        int place = 0; // if 0, then its the hand, if 1 then its the bid
        struct hand temp;
        for(string var; getline(ss, var, ' ');) {
            if (place == 0) {
                for(int i = 0; i < var.length(); i++) {
                    temp.cards[i] = var[i];
                }
            } else {
                temp.bid = stoi(var);
            }
            place++;
        }
        hands.push_back(temp);
    }

    // for( int i = 0; i < hands.size(); i++) {
    //     cout << "bid: " << hands.at(i).bid << endl;
    // }

    for( int i = 0; i < hands.size(); i++) {
        int temp = getRank(hands.at(i));
        hands.at(i).rank = temp;
        // cout << hands.at(i).rank << endl;
    }

    struct hand handArr[hands.size()];
    for(int i = 0; i < hands.size(); i++) {
        handArr[i].rank = hands.at(i).rank;
        for(int j = 0; j < 5; j++) {
            handArr[i].cards[j] = hands.at(i).cards[j];
        }
        handArr[i].bid = hands.at(i).bid;
    }

    bubblesort(handArr, hands.size());

    // cout << "----------------" << endl;

    /*
    for(int i = 0; i < hands.size(); i++) {
        cout << handArr[i].rank;
        for(int c = 0; c < 5; c++) {
            cout << " " << handArr[i].cards[c];
        }
        cout << endl;
    }
    */
    
    long total = 0;
    for(int i = 0; i < hands.size(); i++) {
        total += (handArr[i].bid * (i+1));
    }

    cout << "TOTAL: " << total << endl;

    myFile.close();
}
