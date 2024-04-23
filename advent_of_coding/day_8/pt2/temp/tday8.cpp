#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
using namespace std;


class Node {
private:
    string name;
    string leftName;
    string rightName;
public:
    Node *left;
    Node *right;
    Node(string line) {
        char buffer[3];
        line.copy(buffer, 3, 0); // copy name from line
        for (int i=0; i<3; i++) {
            name.push_back(buffer[i]);
        }
        line.copy(buffer, 3, 7); // copy left name from line
        for (int i=0; i<3; i++) {
            leftName.push_back(buffer[i]);
        }
        line.copy(buffer, 3, 12); // copy right name from line
        for (int i=0; i<3; i++) {
            rightName.push_back(buffer[i]);
        }
        left = NULL;
        right = NULL;
    }

    string getName() {
        return name;
    }

    string getLeftName() {
        return leftName;
    }

    string getRightName() {
        return rightName;
    }

    bool operator< (Node &node1) {
        return (name < node1.getName());
    }

    bool operator> (Node &node1) {
        return (name > node1.getName());
    }

    bool operator== (Node &node1) {
        return (name == node1.getName());
    }
};

long min(long a, long b) {
    if (a < b) {
        return a;
    }
    else {
        return b;
    }
}

long GCD(long a, long b) {
    if (b == 0) {
        return a;
    }
    else {
        return GCD(b, a%b);
    }
}

long LCM(long a, long b) {
    return (a / GCD(a, b) * b);
}


int main(int argc, char **argv) {
    ifstream input_file;
    input_file.open("input.txt");
    string directions;
    getline(input_file, directions);

    string nodeLine;
    getline(input_file, nodeLine); // get the first empty nodeLine

    map<string, Node> nodeMap;

    while (getline(input_file, nodeLine)) {
        Node newNode(nodeLine);
        string name = newNode.getName();
        nodeMap.insert(pair<string, Node>(name, newNode));
    }
    input_file.close();

    int numStartPaths=0;


    list<Node*> startPathList;
    list<Node*> zPathList;

    for (map<string, Node>::iterator currNode = nodeMap.begin(); currNode != nodeMap.end(); currNode++) {
        map<string, Node>::iterator leftNode;
        leftNode = nodeMap.find(currNode->second.getLeftName());
        currNode->second.left = &leftNode->second;
        map<string, Node>::iterator rightNode;
        rightNode = nodeMap.find(currNode->second.getRightName());
        currNode->second.right = &rightNode->second;

        if (currNode->second.getName()[2] == 'A') {
            numStartPaths++;
            Node* path = &currNode->second;
            startPathList.push_back(path);
        }
    }

    // Part 1
    Node *current = &nodeMap.find("AAA")->second;

    int steps=0;

    while (current->getName() != "ZZZ") {
        if (directions[steps%directions.length()] == 'L') {
            current = current->left;
        }
        else if (directions[steps%directions.length()] == 'R') {
            current = current->right;
        }
        steps++;
    }

    cout << "Part 1: It took " << steps << " steps to reach ZZZ" << endl;


    // Part 2

    bool allPathsAtEnd=false;
    long bigSteps=0;
    int path=0;
    steps = 0;

    string startingNode[numStartPaths];
    long pathToFirstZ[numStartPaths];
    long pathLoop[numStartPaths];


    for (list<Node*>::iterator currentPath = startPathList.begin(); currentPath != startPathList.end(); currentPath++) {
        startingNode[path] = (*currentPath)->getName();
        pathToFirstZ[path] = 0;
        pathLoop[path] = 0;
        path++;
    }


    while (!allPathsAtEnd) {
        bool atEnd = true;
        path = 0;
        bigSteps++;
        for (list<Node*>::iterator currentPath = startPathList.begin(); currentPath != startPathList.end(); currentPath++) {
            if (pathLoop[path] == 0) {
                if (directions[steps] == 'L') {
                    (*currentPath) = (*currentPath)->left;
                }
                else if (directions[steps] == 'R') {
                    (*currentPath) = (*currentPath)->right;
                }
                string nodeName = (*currentPath)->getName();

                atEnd = (atEnd && nodeName[2] == 'Z');
                if (nodeName[2] == 'Z') {
                    if (pathToFirstZ[path] == 0) {
                        pathToFirstZ[path] = bigSteps;
                    }
                    else {
                        pathLoop[path] = bigSteps - pathToFirstZ[path];
                    }
                }
                else {
                    atEnd = false;
                }
            }
            path++;
        }
        steps = (steps+1)%directions.length();

        allPathsAtEnd = atEnd;
    }

    long maxLoop=pathLoop[0];
    for (int i = 1; i < numStartPaths; i++) {
        if (maxLoop > pathLoop[i])
        {
            maxLoop = pathLoop[i];
        }
    }

    long leastCommonMultiple=pathLoop[0];

    for (int i=1; i<numStartPaths; i++) {
        leastCommonMultiple = LCM(leastCommonMultiple, pathLoop[i]);
    }

    cout << "Part 2: It will take " << leastCommonMultiple << " steps for all paths to reach a Z simultaneously\n";

    return 0;
}
