//PROJECT 2
//ADVISING PROGRAM
//Lawton Miller
//SNHU CS300

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

struct Course {
    string courseID;
    string courseName;
    vector<string> preReq;
};

const unsigned int DEFAULT_SIZE = 179;

class HashTable {

private:
    // Define structures to hold course info
    struct Node {
        Course course;
        unsigned int key;
        Node* next;

        // default constructor
        Node() {
            key = UINT_MAX;
            next = nullptr;
        }

        // initialize with a course
        Node(Course aCourse) : Node() {
            course = aCourse;
        }

        // initialize with a course and a key
        Node(Course aCourse, unsigned int aKey) : Node(aCourse) {
            key = aKey;
        }
    };

    vector<Node> nodes;

    unsigned int tableSize = DEFAULT_SIZE;

    unsigned int hash(int key);

public:
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    void Insert(Course course);
    void PrintAll();
    void Remove(string CourseId);
    Course Search(string CourseId);
};

HashTable::HashTable() {

    // Initalize node structure by resizing tableSize
    nodes.resize(tableSize);
}

HashTable::HashTable(unsigned int size) {
    // invoke local tableSize to size with this->
    // resize nodes size
    this->tableSize = size;
    nodes.resize(tableSize);
}

HashTable::~HashTable() {

    // erase nodes beginning
    nodes.erase(nodes.begin());
}


unsigned int HashTable::hash(int key) {
 
    // return key tableSize
    return key % tableSize;
}
void HashTable::Insert(Course course) {
    // create the key for the given course
    unsigned int key = hash(atoi(course.courseID.c_str()));

    // retrieve the first node for the given key
    Node* node = &(nodes.at(key));

    // if no entry found for the key, create a new node for the course
    if (node->key == UINT_MAX) {
        node->key = key;
        node->course = course;
        node->next = nullptr;
    }
    // otherwise, append the new node to the end of the linked list for the key
    else {
        while (node->next != nullptr) {
            node = node->next;
        }
        Node* newNode = new Node(course, key);
        node->next = newNode;
    }
}


//printAll function

void HashTable::PrintAll() {
    for (int i = 0; i < nodes.size(); i++) {
        Node* node = &(nodes.at(i));
        while (node != nullptr && node->key != UINT_MAX) {
            Course course = node->course;
            cout << course.courseID << " | " << course.courseName << " | ";
            for (int j = 0; j < course.preReq.size(); j++) {
                cout << course.preReq[j] << " ";
            }
            cout << endl;
            node = node->next;
        }
    }
}

void HashTable::Remove(string courseID) {
    // set key equal to hash atoi courseID cstring
    // erase node begin and key
    unsigned key = hash(atoi(courseID.c_str()));
    nodes.erase(nodes.begin() + key);
}

Course HashTable::Search(string courseID) {
    Course course;

   
    unsigned key = hash(atoi(courseID.c_str()));
    Node* node = &(nodes.at(key));
    // create the key for the given bid
    // if entry found for the key
         //return node course
    if (node == nullptr || node->key == UINT_MAX) {
        return course;
    }
    if (node != nullptr && node->key != UINT_MAX && node->course.courseID.compare(courseID) == 0) {
        return node->course;
    }

    while (node != nullptr) {
        if (node->key != UINT_MAX && node->course.courseID.compare(courseID) == 0) {
            return node->course;
        }
        node = node->next;
    }
    return course;
}


void displayCourse(Course course) {
    cout << course.courseID << ": " << course.courseName << " | ";

    for (int j = 0; j < course.preReq.size(); j++) {
        cout << course.preReq[j] << " ";
    }
    cout << endl;
}

void loadCourses(HashTable& table, const string& filename) {
    ifstream file(filename);

    if (file.is_open()) {
        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            string courseID, courseName;
            vector<string> preReqIDs;

            // Extract courseID and courseName
            getline(ss, courseID, ',');
            getline(ss, courseName, ',');

            // Extract pre-requisite courseIDs
            string preReqID;
            while (getline(ss, preReqID, ',')) {
                preReqIDs.push_back(preReqID);
            }

            // Create Course object and insert into hashtable
            Course course;
            course.courseID = courseID;
            course.courseName = courseName;
            course.preReq = preReqIDs;
            table.Insert(course);
        }

        file.close();
    }
    else {
        cout << "Unable to open file " << filename << endl;
    }
}



int main() {

    HashTable courseTable;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load data" << endl;
        cout << "  2. Print all courses" << endl;
        cout << "  3. Display a course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;


        if (choice == 1) {
            loadCourses(courseTable, "CourseInformation.txt");

        }
        else if (choice == 2) {
            courseTable.PrintAll();
        }
        else if (choice == 3) {
            string userCourseID;
            Course userCourse;
            cout << "Enter course ID to display" << endl;
            cin >> userCourseID;
            displayCourse(courseTable.Search(userCourseID));

        }
        else if (choice == 9) {

        }

    }
}