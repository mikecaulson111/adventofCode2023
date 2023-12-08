#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;


struct mapper {
    long dest;
    long source;
    long size;
};

int main() {
    ifstream myFile("mapps.txt");

    // first parse each section into a specific map:
    vector<mapper> seed_soil; // section 0
    vector<mapper> soil_fert; // section 1
    vector<mapper> fert_water; // section 2
    vector<mapper> water_light; // section 3
    vector<mapper> light_temp; // section 4
    vector<mapper> temp_humid; // section 5
    vector<mapper> humid_loc; // section 6

    vector<long> seeds;

    int section = 0;

    string line;
    while(getline(myFile, line)) {
        if (line.length()) {
            // do everything:
            if (line[0] == 's') {
                if (line[4] == 's') {
                    line = line.substr(7);
                    cout << line << endl;
                    istringstream ss(move(line));
                    for(string val; getline(ss, val, ' ');) {
                        seeds.push_back(stol(val));
                    }
                } else if (line[1] == 'e') {
                    section = 0;
                } else if (line[1] == 'o') {
                    section = 1;
                }
            } else if (line[0] == 'f') {
                section = 2;
            } else if (line[0] == 'w') {
                section = 3;
            } else if (line[0] == 'l') {
                section  = 4;
            } else if (line[0] == 't') {
                section = 5;
            } else if (line[0] == 'h') {
                section = 6;
            } else if (line[0] < 58 && line[0] > 47) {
                // do pretty muhc everything here: mapping and such;
                istringstream ss(move(line));
                int num = 0;
                struct mapper tmap;
                for(string val; getline(ss, val, ' ');) {
                    if (num == 0) {
                        tmap.dest = stol(val);
                    } else if (num == 1) {
                        tmap.source = stol(val);
                    } else if (num == 2) {
                        tmap.size = stol(val);
                    }
                    num++;
                }
                if (section == 0) {
                    seed_soil.push_back(tmap);
                } else if (section == 1) {
                    soil_fert.push_back(tmap);
                } else if (section == 2) {
                    fert_water.push_back(tmap);
                } else if (section == 3) {
                    water_light.push_back(tmap);
                } else if (section == 4) {
                    light_temp.push_back(tmap);
                } else if (section == 5) {
                    temp_humid.push_back(tmap);
                } else if (section == 6) {
                    humid_loc.push_back(tmap);
                }
            }
        }
    }

    cout << seeds.size() << endl;

    cout << seed_soil.size() << endl;
    cout << soil_fert.size() << endl;
    cout << fert_water.size() << endl;
    cout << water_light.size() << endl;
    cout << light_temp.size() << endl;
    cout << temp_humid.size() << endl;
    cout << humid_loc.size() << endl;

    long smallest_loc;

    for (int i = 0; i < seeds.size(); i++) {
        cout << i << endl;
        long place = seeds.at(i); // this will be the mapped number throughout
        cout << "here" << endl;
        for (int j = 0; j < 7; j++) { // j will track place in sections
            if (j == 0) {
                for ( int k = 0; k < seed_soil.size(); k++) {
                    struct mapper t = seed_soil.at(k);
                    if (place >= t.source && place <= t.source + t.size) {
                        long diff = t.dest - t.source;
                        place = place + diff;
                        break;
                    }
                }
            } else if (j == 1) {
                for ( int k = 0; k < soil_fert.size(); k++) {
                    struct mapper t = soil_fert.at(k);
                    if (place >= t.source && place <= t.source + t.size) {
                        long diff = t.dest - t.source;
                        place = place + diff;
                        break;
                    }
                }
            } else if (j == 2) {
                for ( int k = 0; k < fert_water.size(); k++) {
                    struct mapper t = fert_water.at(k);
                    if (place >= t.source && place <= t.source + t.size) {
                        long diff = t.dest - t.source;
                        place = place + diff;
                        break;
                    }
                }
            } else if (j == 3) {
                for ( int k = 0; k < water_light.size(); k++) {
                    struct mapper t = water_light.at(k);
                    if (place >= t.source && place <= t.source + t.size) {
                        long diff = t.dest - t.source;
                        place = place + diff;
                        break;
                    }
                }
            } else if (j == 4) {
                for ( int k = 0; k < light_temp.size(); k++) {
                    struct mapper t = light_temp.at(k);
                    if (place >= t.source && place <= t.source + t.size) {
                        long diff = t.dest - t.source;
                        place = place + diff;
                        break;
                    }
                }
            } else if (j == 5) {
                for ( int k = 0; k < temp_humid.size(); k++) {
                    struct mapper t = temp_humid.at(k);
                    if (place >= t.source && place <= t.source + t.size) {
                        long diff = t.dest - t.source;
                        place = place + diff;
                        break;
                    }
                }
            } else if (j == 6) {
                for ( int k = 0; k < humid_loc.size(); k++) {
                    struct mapper t = humid_loc.at(k);
                    if (place >= t.source && place <= t.source + t.size) {
                        long diff = t.dest - t.source;
                        place = place + diff;
                        break;
                    }
                }
            }
        }
        if ( i == 0 ) {
            smallest_loc = place;
        } else {
            if (place < smallest_loc) {
                smallest_loc = place;
            }
        }
    }

    cout << "SMALLEST: " << smallest_loc << endl;

    myFile.close();
}
