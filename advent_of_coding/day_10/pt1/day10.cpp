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

int main() {
    // ifstream myFile("temp.txt");
    ifstream myFile("input.txt");

    string line;
    long total = 0;

    while(getline(myFile, line)) {
        //
    }

    cout << "TOTAL: " << total << endl;

    myFile.close();
}
