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
        return temparr[0] - recurFindNext(temparr, size-1);
    }
}


int main() {
    // ifstream myFile("temp2.txt");
    // ifstream myFile("temp.txt");
    ifstream myFile("input.txt");

    string line;
    long total = 0;

    while(getline(myFile, line)) {
        // parse 
        // then call a recursive function
        istringstream ss(move(line));
        vector<string> myvec;
        for(string var; getline(ss, var, ' ');) {
            myvec.push_back(var);
        }

        int arr[myvec.size()];
        for(int i = 0; i < myvec.size(); i++) {
            arr[i] = stoi(myvec.at(i));
        }

        long temp = arr[0] - recurFindNext(arr, myvec.size());
        // cout << temp << endl;

        total += temp;

    }

    cout << "TOTAL: " << total << endl;

    myFile.close();
}
