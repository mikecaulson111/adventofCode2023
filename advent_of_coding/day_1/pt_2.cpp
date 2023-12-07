#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string line;
    ifstream myFile("keys_file.txt");
    // ifstream myFile("newtemp.txt");

    string nums[] = {"one","two","three","four","five","six","seven","eight","nine"};

    int total = 0;
    int temp_num = 0;
    int count = 0;

    while(getline(myFile, line)) {
        string new_str = "";
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == 'o') {
                // one case
                if (line.substr(i, 3) == nums[0]) {
                    new_str += "1";
                    i += 2;
                }
            } else if (line[i] == 't') {
                // two and three case
                if (line.substr(i, 3) == nums[1]) {
                    new_str += "2";
                    i += 2;
                } else if (line.substr(i, 5) == nums[2]) {
                    new_str += "3";
                    i += 4;
                }
            } else if (line[i] == 'f') {
                // four and five case
                if (line.substr(i, 4) == nums[3]) {
                    new_str += "4";
                    i += 3;
                } else if (line.substr(i, 4) == nums[4]) {
                    new_str += "5";
                    i += 3;
                }
            } else if (line[i] == 's') {
                // six and seven case
                if (line.substr(i,3) == nums[5]) {
                    new_str += "6";
                    i += 2;
                } else if (line.substr(i, 5) == nums[6]) {
                    new_str += "7";
                    i += 4;
                }
            } else if (line[i] == 'e') {
                // eight case
                if (line.substr(i, 5) == nums[7]) {
                    new_str += "8";
                    i += 4;
                }
            } else if (line[i] == 'n') {
                // nine case
                if (line.substr(i, 4) == nums[8]) {
                    new_str += "9";
                    i += 3;
                }
            } else {
                new_str += line[i];
            }
        }

        cout << line << ", "  << new_str << ", ";


        count++;
        // cout << line << endl;
        for (int i = 0; i < new_str.length(); i++) {
            if (new_str[i] > 47 && new_str[i] < 58) {
                temp_num = ((int)new_str[i] - 48) * 10;
                break;
            }
        }

        for (int i = new_str.length() - 1; i >= 0; i--) {
            if ( new_str[i] > 47 && new_str[i] < 58) {
                temp_num += ((int)new_str[i] - 48);
                break;
            }
        }
        total += temp_num;
        cout << temp_num << endl;
    }

    cout << "Total number is: " << total << endl;
    cout << count << endl;

    myFile.close();
}
