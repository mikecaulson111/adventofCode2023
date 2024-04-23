#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

struct LR {
    string left;
    string right;
};


int main() {
    // ifstream myFile("directions.txt");
    ifstream myFile("temp.txt");

    unordered_map <string, struct LR> hashmap;
    // vector<string> tots;
    string tots[100];
    int tn = 0;

    string line;
    string dirs;
    string first;

    int n = 0;
    while(getline(myFile, line)) {
        if(n==0) {
            dirs = line;
        } else if ( n == 1 ) {
            //
        } else {
            string definer = line.substr(0,3);
            string left = line.substr(7,3);
            string right = line.substr(12,3);
            struct LR temp;
            temp.left = left;
            temp.right = right;
            hashmap.insert({ definer, temp});
            // cout << temp.right << endl;
            if (definer[2] == 'A') {
                tots[tn] = definer;
                tn++;
            }
        }
        n++;
    }

    // cout << hashmap["GXF"].left << endl;

    bool finished = false;
    int t = 0;
    string prev = "AAA";
    while(finished == false) {
        int numzs = 0;
        for(int i = 0; i < tn; i++) {
            string temp;
            if (dirs[t % dirs.length()] == 'L') {
                temp = hashmap[tots[i]].left;
            } else {
                temp = hashmap[tots[i]].right;
            }

            // cout << i << " " << temp << endl;

            if (temp[2] == 'Z') {
                numzs += 1;
                // cout << i << " " << temp << endl;
            }
            tots[i] = temp;
        }
        if ( numzs == tn ) {
            finished = true;
        }
        t++;
    }

    cout << "Total: " << t << endl;



    myFile.close();
}
