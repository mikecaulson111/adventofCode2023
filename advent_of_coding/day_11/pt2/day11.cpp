#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;



typedef struct gal_t {
    int x;
    int y;
} gal;

int num_empty_row_between(int row1, int row2, vector<int> rows) {
    int num_empty_rows = 0;
    if (row2 < row1) {
        int temp = row1;
        row1 = row2;
        row2 = temp;
    }
    for (int i = 0; i < rows.size(); i++) {
        if (rows.at(i) < row2 && rows.at(i) > row1) {
            num_empty_rows++;
        }
    }

    return num_empty_rows;
}

int num_empty_col_between(int col1, int col2, vector<int> cols) {
    int num_empty_cols = 0;
    // cout << "IN COLS: " << col1 << " " << col2 << endl;
    if (col2 < col1) {
        int temp = col1;
        col1 = col2;
        col2 = temp;
    }
    for (int i = 0; i < cols.size(); i++) {
        // cout << cols.at(i) << endl;
        if (cols.at(i) < col2 && cols.at(i) > col1) {
            num_empty_cols += 1;
        }
    }

    return num_empty_cols;
}

int main() {
    ifstream myFile("input.txt");
    // ifstream myFile("woah.txt");

    string line;
    long total = 0;

    vector<vector<char>> vect;
    vector<gal> gals;
    vector<int> rows_empty;
    vector<int> cols_empty;
    int count1 =  0;
    while(getline(myFile, line)) {
        int count2 = 0;
        // cout << line << endl;
        vector<char> myVect;
        bool test = true;
        for ( char c : line ) {
            myVect.push_back(c);
            if (c != '.') {
                gal temp;
                temp.x = count2;
                temp.y = count1;
                gals.push_back(temp);
                test = false;
            }
            count2++;
        }

        // find all empty rows
        if (test) {
            rows_empty.push_back(count1);
        }


        vect.push_back(myVect);
        count1++;
    }
     // cout << gals.size() << endl;

    // find all empty columns
    for(int i= 0; i < vect.at(0).size(); i++) {
        bool test = true;
        for (int j = 0; j < vect.size(); j++) {
            if (vect.at(j).at(i) != '.') {
                test = false;
            }
        }

        if (test) {
            cols_empty.push_back(i);
        }
    }

    
    for (int i = 0; i < gals.size(); i++) {
        for ( int j = i+1; j < gals.size(); j++) {
            long x_dist = gals.at(j).x - gals.at(i).x;
            long y_dist = gals.at(j).y - gals.at(i).y;
            if (x_dist < 0) {
                x_dist = -x_dist;
            }
            if (y_dist < 0) {
                y_dist = -y_dist;
            }

            long x_space = num_empty_col_between(gals.at(i).x, gals.at(j).x, cols_empty);
            long y_space = num_empty_row_between(gals.at(i).y, gals.at(j).y, rows_empty);



            x_dist += 999999*x_space;
            y_dist += 999999*y_space;
            total += (x_dist + y_dist);
        }
    }

    
    cout << "TOTAL: " << total << endl;

    myFile.close();
}
