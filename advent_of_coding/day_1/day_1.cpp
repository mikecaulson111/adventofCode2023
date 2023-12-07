#include <iostream>
#include <fstream>

using namespace std;

int main() {
    string line;
    ifstream myFile("keys_file.txt");

    int total = 0;
    int temp_num = 0;
    int count = 0;

    while(getline(myFile, line)) {
        count++;
        // cout << line << endl;
        for (int i = 0; i < line.length(); i++) {
            if (line[i] > 47 && line[i] < 58) {
                temp_num = ((int)line[i] - 48) * 10;
                break;
            }
        }

        for (int i = line.length() - 1; i >= 0; i--) {
            if ( line[i] > 47 && line[i] < 58) {
                temp_num += ((int)line[i] - 48);
                break;
            }
        }
        total += temp_num;
    }

    cout << "Total number is: " << total << endl;
    cout << count << endl;

    myFile.close();
}
