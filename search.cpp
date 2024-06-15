#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Function to check if a file exists
bool fileExists(const string& path) {
    ifstream file(path);
    return file.good();
}

// Function to search by student ID
void searchByStudentID(const string& studentID) {
    string folderName = (studentID.length() == 8) ? "student8" : "student10";
    string resultFile = "result.txt";
    int courseCount = 0;

    ofstream outputFile(resultFile);
    if (!outputFile) {
        cout << "Failed to open " << resultFile << " for writing." << endl;
        return;
    }

    outputFile << "Student ID: " << studentID << endl;

    // Iterate through files in the directory
    for (int i = 1; true; ++i) {
        stringstream ss;
        ss << folderName << "/" << i << ".txt";
        string filePath = ss.str();
        
        if (!fileExists(filePath)) {
            break; // No more files to process
        }
        
        ifstream inputFile(filePath);
        if (inputFile) {
            string line;
            while (getline(inputFile, line)) {
                string studentIDPrefix =(studentID.length() == 8) ? line.substr(0, 8) : line.substr(0, 10);
                // if (folderName == "student8")
                //     studentIDPrefix = line.substr(0, 8); // Extract the first 8 characters (student ID)
                // else if (folderName == "student10")
                //     studentIDPrefix = line.substr(0, 10); // Extract the first 10 characters (student ID)
                if (studentIDPrefix == studentID) {
                    outputFile << line << endl;
                    courseCount++;
                }
            }
            inputFile.close();
        }
    }

    outputFile << "Total courses found: " << courseCount << endl;

    outputFile.close();
}

// Function to search by course ID
void searchByCourseID(const string& courseID) {
    string folderName = "course";
    string resultFile = "result.txt";
    int studentCount = 0;

    ofstream outputFile(resultFile);
    if (!outputFile) {
        cout << "Failed to open " << resultFile << " for writing." << endl;
        return;
    }

    outputFile << "Course ID: " << courseID << endl;

    // Iterate through files in the directory
    for (int i = 1; true; ++i) {
        stringstream ss;
        ss << folderName << "/" << i << ".txt";
        string filePath = ss.str();
        
        if (!fileExists(filePath)) {
            break; // No more files to process
        }

        ifstream inputFile(filePath);
        if (inputFile) {
            string line;
            while (getline(inputFile, line)) {
                string courseIDPrefix = line.substr(0, 4); // Extract the first four characters
                if (courseIDPrefix == courseID) { // Compare with the given courseID
                    outputFile << line << endl;
                    studentCount++;
                }
            }
            inputFile.close();
        }
    }

    outputFile << "Total students : " << studentCount << endl;

    outputFile.close();
}

int main() {
    int choice;
    cout << "Enter 1 to search by student ID, or 2 to search by course ID: ";
    cin >> choice;

    if (choice == 1) {
        string studentID;
        cout << "Enter student ID: ";
        cin >> studentID;
        searchByStudentID(studentID);
    }
    else if (choice == 2) {
        string courseID;
        cout << "Enter course ID: ";
        cin >> courseID;
        searchByCourseID(courseID);
    }
    else {
        cout << "Invalid choice." << endl;
    }

    return 0;
}
