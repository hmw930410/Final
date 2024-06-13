#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm> // For std::sort

using namespace std;

// 載入索引檔案
void loadIndex(const string& filename, unordered_multimap<string, string>& indexMap) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "無法打開檔案 " << filename << endl;
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

// 根據學號進行搜尋
void searchByStudentID(const string& studentID) {
    unordered_multimap<string, string> indexMap;
    string filename;

    // 根據學號長度選擇對應的檔案
    if (studentID.length() == 8) {
        filename = "student_8_index.txt";
    } else if (studentID.length() == 10) {
        filename = "student_10_index.txt";
    } else {
        cerr << "學號長度不正確！" << endl;
        return;
    }

    loadIndex(filename, indexMap);

    vector<string> results;
    auto range = indexMap.equal_range(studentID);
    if (range.first == range.second) {
        results.push_back("未找到學號 " + studentID + " 的任何課程。");
    } else {
        for (auto it = range.first; it != range.second; ++it) {
            results.push_back(it->second);
        }
        sort(results.begin(), results.end()); // 排序課程代碼
    }

    ofstream outfile("result.txt");
    if (!outfile.is_open()) {
        cerr << "無法打開輸出檔案 result.txt" << endl;
        return;
    }

    outfile << "學號 " << studentID << " 的課程有: " << endl;
    for (const auto& course : results) {
        outfile << course << endl;
    }
    if (results.size() > 1) {
        outfile << "總共有 " << results.size() << " 堂課程。" << endl;
    }

    outfile.close();
}

// 根據課程代碼進行搜尋
void searchByCourseID(const string& courseID) {
    unordered_multimap<string, string> indexMap;
    string filename = "course_index.txt";

    loadIndex(filename, indexMap);

    vector<pair<string, string>> results;
    auto range = indexMap.equal_range(courseID);
    if (range.first == range.second) {
        results.push_back(make_pair("未找到課程代碼 " + courseID + " 的任何學生。", ""));
    } else {
        for (auto it = range.first; it != range.second; ++it) {
            results.push_back(make_pair(it->first, it->second));
        }
        sort(results.begin(), results.end()); // 根據學號排序
    }

    ofstream outfile("result.txt");
    if (!outfile.is_open()) {
        cerr << "無法打開輸出檔案 result.txt" << endl;
        return;
    }

    outfile << "課程代碼 " << courseID << " 的學生有: " << endl;
    for (const auto& entry : results) {
        if (!entry.second.empty()) {
            outfile << entry.second << endl;
        }
    }
    if (results.size() > 1) {
        outfile << "總共有 " << results.size() << " 位學生選擇。" << endl;
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
