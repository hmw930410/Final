#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

// ���J�����ɮ�
void loadIndex(const string& filename, unordered_multimap<string, string>& indexMap) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "�L�k���}�ɮ� " << filename << endl;
        return;
    }

    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        string key, value;
        if (getline(iss, key, ',') && getline(iss, value)) {
            indexMap.emplace(key, value);
        }
    }
    infile.close();
}

// �ھھǸ��i��j�M
void searchByStudentID(const string& studentID) {
    unordered_multimap<string, string> indexMap;
    string filename;

    // �ھھǸ����׿�ܹ������ɮ�
    if (studentID.length() == 8) {
        filename = "student_8_index.txt";
    } else if (studentID.length() == 10) {
        filename = "student_10_index.txt";
    } else {
        cerr << "�Ǹ����פ����T�I" << endl;
        return;
    }

    loadIndex(filename, indexMap);

    ofstream outfile("result.txt");
    if (!outfile.is_open()) {
        cerr << "�L�k���}��X�ɮ� result.txt" << endl;
        return;
    }

    auto range = indexMap.equal_range(studentID);
    if (range.first == range.second) {
        outfile << "�����Ǹ� " << studentID << " ������ҵ{�C" << endl;
    } else {
        int count = 0;
        outfile << "�Ǹ� " << studentID << " ���ҵ{��: " << endl;
        for (auto it = range.first; it != range.second; ++it) {
            outfile << it->second << endl;
            count++;
        }
        outfile << "�`�@�� " << count << " ��ҵ{�C" << endl;
    }

    outfile.close();
}

// �ھڽҵ{�N�X�i��j�M
void searchByCourseID(const string& courseID) {
    unordered_multimap<string, string> indexMap;
    string filename = "course_index.txt";

    loadIndex(filename, indexMap);

    ofstream outfile("result.txt");
    if (!outfile.is_open()) {
        cerr << "�L�k���}��X�ɮ� result.txt" << endl;
        return;
    }

    auto range = indexMap.equal_range(courseID);
    if (range.first == range.second) {
        outfile << "�����ҵ{�N�X " << courseID << " ������ǥ͡C" << endl;
    } else {
        int count = 0;
        outfile << "�ҵ{�N�X " << courseID << " ���ǥͦ�: " << endl;
        for (auto it = range.first; it != range.second; ++it) {
            outfile << it->second << endl;
            count++;
        }
        outfile << "�`�@�� " << count << " ��ǥͿ�ܡC" << endl;
    }

    outfile.close();
}

int main() {
    string option;
    cout << endl << "1: search by student ID" << endl << "2: search by course ID" << endl;
    cout << "Choose an option (1 or 2): ";
    cin >> option;

    if (option == "1") {
        string studentID;
        cout << "Enter student ID: ";
        cin >> studentID;
        searchByStudentID(studentID);
    } else if (option == "2") {
        string courseID;
        cout << "Enter course ID: ";
        cin >> courseID;
        searchByCourseID(courseID);
    } else {
        cout << "Invalid option." << endl;
    }

    return 0;
}
