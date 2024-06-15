#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Function to check if a file exists
bool fileExists(const string &path)
{
    ifstream file(path);
    return file.good();
}

// Function to search by student ID
void searchByStudentID(const string &studentID)
{
    string folderName = (studentID.length() == 8) ? "student8" : "student10";
    string resultFile = "result.txt";
    int courseCount = 0;

    ofstream outputFile(resultFile);
    if (!outputFile)
    {
        cout << "Failed to open " << resultFile << " for writing." << endl;
        return;
    }

    outputFile << "Student ID: " << studentID << endl;

    // Iterate through files in the directory
    for (int i = 1; true; ++i)
    {
        stringstream ss;
        ss << folderName << "/" << i << ".txt";
        string filePath = ss.str();

        if (!fileExists(filePath))
        {
            break; // No more files to process
        }

        ifstream inputFile(filePath);
        if (inputFile)
        {
            string line;
            while (getline(inputFile, line))
            {
                string studentIDPrefix = (studentID.length() == 8) ? line.substr(0, 8) : line.substr(0, 10);
                string output = (studentID.length() == 8) ? line.substr(9) : line.substr(11);
                // if (folderName == "student8")
                //     studentIDPrefix = line.substr(0, 8); // Extract the first 8 characters (student ID)
                // else if (folderName == "student10")
                //     studentIDPrefix = line.substr(0, 10); // Extract the first 10 characters (student ID)
                if (studentIDPrefix == studentID)
                {
                    outputFile << output << endl;
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
void searchByCourseID(const string &courseID)
{
    string folderName = "course";
    string resultFile = "result.txt";
    int studentCount = 0;

    ofstream outputFile(resultFile);
    if (!outputFile)
    {
        cout << "Failed to open " << resultFile << " for writing." << endl;
        return;
    }

    outputFile << "Course ID: " << courseID << endl;
    int flag = 1;
    // Iterate through files in the directory
    for (int i = 1; true; ++i)
    {
        stringstream ss;
        ss << folderName << "/" << i << ".txt";
        string filePath = ss.str();

        if (!fileExists(filePath))
        {
            break; // No more files to process
        }
        ifstream inputFile(filePath);
        if (inputFile)
        {
            string line;
            while (getline(inputFile, line))
            {
                stringstream ss(line);
                string token;
                string courseIDPrefix;
                string courseChinese;
                string studentID;
                int i = 0;
                while (getline(ss, token, ','))
                {
                    if (i == 0)
                        courseIDPrefix = token;
                    else if (i == 1)
                        studentID = token;
                    else if (i == 2)
                        courseChinese = token;
                    else
                        cout << "分割錯誤" << endl;
                    i++;
                }
                if (courseIDPrefix == courseID && flag)
                {
                    outputFile << "Course Name: " << courseChinese << endl;
                    flag = 0;
                }
                if (courseIDPrefix == courseID)
                { // Compare with the given courseID
                    outputFile << studentID << endl;
                    studentCount++;
                }
            }
            inputFile.close();
        }
    }

    outputFile << "Total students : " << studentCount << endl;

    outputFile.close();
}

int main()
{
    int choice;
    cout << "Enter 1 to search by student ID, or 2 to search by course ID: ";
    cin >> choice;

    if (choice == 1)
    {
        string studentID;
        cout << "Enter student ID: ";
        cin >> studentID;
        searchByStudentID(studentID);
    }
    else if (choice == 2)
    {
        string courseID;
        cout << "Enter course ID: ";
        cin >> courseID;
        searchByCourseID(courseID);
    }
    else
    {
        cout << "Invalid choice." << endl;
    }

    return 0;
}
