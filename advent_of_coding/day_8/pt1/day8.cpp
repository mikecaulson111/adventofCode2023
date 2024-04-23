#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>

using namespace std;

struct LR {
    string left;
    string right;
};


int main() {
    ifstream myFile("directions.txt");
    // ifstream myFile("temp.txt");

    unordered_map <string, struct LR> hashmap;

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
        }
        n++;
    }

    // cout << hashmap["GXF"].left << endl;

    bool finished = false;
    int t = 0;
    string prev = "AAA";
    while(finished == false) {
        string temp;
        if (dirs[t % dirs.length()] == 'L') {
            temp = hashmap[prev].left;
        } else {
            temp = hashmap[prev].right;
        }

        if (temp == "ZZZ") {
            finished = true;
        } else {
            prev = temp;
        }
        t++;
    }

    cout << "Total: " << t << endl;



    myFile.close();
}
