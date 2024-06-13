#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// 存儲學生和課程資料的結構體
struct StudentCourse {
    string student_id;
    string course_id;
};

// 讀取文件並將資料存儲在vector中
void readDataFromFile(vector<StudentCourse>& data) {
    // 讀取多個檔案
    for (int i = 1; i <= 466; i++) {
        // 構造檔案路徑
        stringstream ss;
        if (i < 10) {
            ss << "data_no_cname/000" << i;
        } else if (i < 100) {
            ss << "data_no_cname/00" << i;
        } else {
            ss << "data_no_cname/0" << i;
        }
        string directoryPath = ss.str();

        // 開啟輸入檔案
        ifstream inputFile(directoryPath);

        // 檢查文件是否打開
        if (!inputFile.is_open()) {
            cerr << "無法打開文件: " << directoryPath << endl;
            continue;
        }

        // 從目錄中讀取檔案並將其插入vector
        string line;
        while (getline(inputFile, line)) {
            stringstream linestream(line);
            string student_id, course_id;
            getline(linestream, student_id, ',');
            getline(linestream, course_id, ',');

            if (!student_id.empty() && !course_id.empty()) {
                data.push_back({student_id, course_id});
            }
        }

        // 關閉輸入檔案
        inputFile.close();
    }
}

// 比較函式，用於排序
bool compareByCourseIdAndStudentId(const StudentCourse& a, const StudentCourse& b) {
    if (a.course_id == b.course_id) {
        return a.student_id < b.student_id;
    }
    return a.course_id < b.course_id;
}

// 將排序後的資料寫入輸出檔案
void writeDataToFile(const vector<StudentCourse>& data) {
    ofstream outputFile("course_index.txt");

    // 檢查文件是否打開
    if (!outputFile.is_open()) {
        cerr << "open failed." << endl;
        return;
    }

    // 寫入資料到輸出文件
    for (const auto& entry : data) {
        if (entry.course_id.length() == 4)
            outputFile << entry.course_id << "," << entry.student_id << endl;
    }

    // 關閉輸出檔案
    outputFile.close();
}

int main() {
    // 存儲學生和課程資料的vector
    vector<StudentCourse> data;

    // 從文件中讀取資料
    readDataFromFile(data);

    // 根據course_id排序，如果course_id相同則根據student_id排序
    sort(data.begin(), data.end(), compareByCourseIdAndStudentId);

    // 將排序後的資料寫入輸出文件
    writeDataToFile(data);

    return 0;
}
