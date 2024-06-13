#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm> // For std::sort

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

    vector<string> results;
    auto range = indexMap.equal_range(studentID);
    if (range.first == range.second) {
        results.push_back("�����Ǹ� " + studentID + " ������ҵ{�C");
    } else {
        for (auto it = range.first; it != range.second; ++it) {
            results.push_back(it->second);
        }
        sort(results.begin(), results.end()); // �Ƨǽҵ{�N�X
    }

    ofstream outfile("result.txt");
    if (!outfile.is_open()) {
        cerr << "�L�k���}��X�ɮ� result.txt" << endl;
        return;
    }

    outfile << "�Ǹ� " << studentID << " ���ҵ{��: " << endl;
    for (const auto& course : results) {
        outfile << course << endl;
    }
    if (results.size() > 1) {
        outfile << "�`�@�� " << results.size() << " ��ҵ{�C" << endl;
    }

    outfile.close();
}

// �ھڽҵ{�N�X�i��j�M
void searchByCourseID(const string& courseID) {
    unordered_multimap<string, string> indexMap;
    string filename = "course_index.txt";

    loadIndex(filename, indexMap);

    vector<pair<string, string>> results;
    auto range = indexMap.equal_range(courseID);
    if (range.first == range.second) {
        results.push_back(make_pair("�����ҵ{�N�X " + courseID + " ������ǥ͡C", ""));
    } else {
        for (auto it = range.first; it != range.second; ++it) {
            results.push_back(make_pair(it->first, it->second));
        }
        sort(results.begin(), results.end()); // �ھھǸ��Ƨ�
    }

    ofstream outfile("result.txt");
    if (!outfile.is_open()) {
        cerr << "�L�k���}��X�ɮ� result.txt" << endl;
        return;
    }

    outfile << "�ҵ{�N�X " << courseID << " ���ǥͦ�: " << endl;
    for (const auto& entry : results) {
        if (!entry.second.empty()) {
            outfile << entry.second << endl;
        }
    }
    if (results.size() > 1) {
        outfile << "�`�@�� " << results.size() << " ��ǥͿ�ܡC" << endl;
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
