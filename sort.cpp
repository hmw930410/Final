#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstdlib> // 用於 system 函數
#include <codecvt> // 編碼之間進行轉換
#include <locale>  // 控制字符和字符串的轉換

using namespace std;

// 二元搜尋樹節點
struct Node {
    string data;
    Node* left;
    Node* right;
};

// 存儲學生和課程資料的結構體
struct StudentCourse {
    string student_id;
    string course_id;
    string course_chinese;
};

// 建立新節點的函式
Node* createNode(string data) {
    Node* newNode = new Node();
    if (newNode) {
        newNode->data = data;
        newNode->left = newNode->right = nullptr;
    }
    return newNode;
}

// 將節點插入二元搜尋樹的函式
Node* insertNode(Node* root, string data) {
    // 如果樹是空的，將新節點指派給根節點
    if (root == nullptr) {
        root = createNode(data);
        return root;
    }

    // 否則，進行遞迴插入
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }

    // 回傳（不變的）節點指標
    return root;
}

// 執行中序遍歷二元搜尋樹的函式
void inorderTraversal(Node* root, ofstream& outputFile) {
    if (root == nullptr) {
        return;
    }
    inorderTraversal(root->left, outputFile);
    outputFile << root->data << endl;
    inorderTraversal(root->right, outputFile);
}

// 讀取文件並將資料存儲在vector中
void readDataFromFile(vector<StudentCourse>& data, Node*& root_8, Node*& root_10) {
    // 讀取多個檔案
    for (int i = 1; i <= 466; i++) {
        // 構造檔案路徑
        stringstream ss;
        if (i < 10) {
            ss << "data_utf8/000" << i;
        } else if (i < 100) {
            ss << "data_utf8/00" << i;
        } else {
            ss << "data_utf8/0" << i;
        }
        string directoryPath = ss.str();

        // 開啟輸入檔案
        ifstream inputFile(directoryPath);

        // 檢查文件是否打開
        if (!inputFile.is_open()) {
            cerr << "無法打開文件: " << directoryPath << endl;
            continue;
        }

        // 從目錄中讀取檔案並將其插入vector和二元搜尋樹
        string line;
        while (getline(inputFile, line)) {
            stringstream linestream(line);
            string student_id, course_id, course_chinese;
            getline(linestream, student_id, ',');
            getline(linestream, course_id, ',');
            getline(linestream, course_chinese, ',');

            if (!student_id.empty() && !course_id.empty()) {
                data.push_back({student_id, course_id, course_chinese});
            }

            if (student_id.length() == 8 && course_id.length() == 4){
                root_8 = insertNode(root_8, line);
            } else if (student_id.length() == 10 && course_id.length() == 4) {
                root_10 = insertNode(root_10, line);
            }
        }

        // 關閉輸入檔案
        inputFile.close();
    }
}

void sortDataWithHashing(vector<StudentCourse>& data) {
    unordered_map<string, vector<pair<string, string>>> courseStudentMap;

    // 將資料插入雜湊表
    for (const auto& entry : data) {
        courseStudentMap[entry.course_id].push_back({entry.student_id, entry.course_chinese});
    }

    // 將雜湊表轉換為向量並排序
    vector<pair<string, vector<pair<string, string>>>> sortedData(courseStudentMap.begin(), courseStudentMap.end());
    sort(sortedData.begin(), sortedData.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    // 清空原來的資料並插入排序後的資料
    data.clear();
    for (const auto& entry : sortedData) {
        vector<pair<string, string>> sortedStudents = entry.second;
        sort(sortedStudents.begin(), sortedStudents.end()); // 對學生ID進行排序
        for (const auto& student_id : sortedStudents) {
            data.push_back({student_id.first, entry.first, student_id.second});
        }
    }
}

// 將排序後的資料寫入輸出檔案
void writeDataToFile(const vector<StudentCourse>& data) {

    ofstream outputFile("course_index.txt", ios::out | ios::binary);

    // 檢查文件是否打開
    if (!outputFile.is_open()) {
        cerr << "open failed." << endl;
        return;
    }

    // 寫入資料到輸出文件
    for (const auto& entry : data) {
        outputFile << entry.course_id << "," << entry.student_id << "," << entry.course_chinese << endl;
    }

    // 關閉輸出檔案
    outputFile.close();
}

// 分割檔案的函式
void splitFile(const string& inputFileName) {
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        cerr << "無法打開檔案 " << inputFileName << endl;
        return;
    }

    int file_part = 1;

    string outputFileName;
    if (inputFileName == "course_index.txt") {
        outputFileName = "course/" + to_string(file_part) + ".txt";
    }
    else if (inputFileName == "student_8_index.txt") {
        outputFileName = "student8/" + to_string(file_part) + ".txt";
    }
    else if (inputFileName == "student_10_index.txt") {
        outputFileName = "student10/" + to_string(file_part) + ".txt";
    }
    
    ofstream outputFile(outputFileName, ios::binary);
    int bytes_written = 0;
    string line;

    while (getline(inputFile, line)) {
        bytes_written += line.size() + 1; // 加上換行符的長度，因為getline不包括換行符
        outputFile << line << '\n';

        if (bytes_written >= 2000) {
            outputFile.close();
            file_part++;

            if (inputFileName == "course_index.txt") {
                outputFileName = "course/" + to_string(file_part) + ".txt";
            }
            else if (inputFileName == "student_8_index.txt") {
                outputFileName = "student8/" + to_string(file_part) + ".txt";
            }
            else if (inputFileName == "student_10_index.txt") {
                outputFileName = "student10/" + to_string(file_part) + ".txt";
            }

            outputFile.open(outputFileName, ios::binary);
            bytes_written = 0;
        }
    }

    inputFile.close();
    outputFile.close();
}

int main() {
    // 開啟輸出檔案
    ofstream outputFile_8("student_8_index.txt");
    ofstream outputFile_10("student_10_index.txt");

    // 建立二元搜尋樹的根節點
    Node* root_8 = nullptr;
    Node* root_10 = nullptr;

    // 存儲學生和課程資料的vector
    vector<StudentCourse> data;

    // 從文件中讀取資料
    readDataFromFile(data, root_8, root_10);

    // 使用雜湊來排序course_id
    sortDataWithHashing(data);

    // 將排序後的資料寫入輸出文件
    writeDataToFile(data);

    // 執行中序遍歷二元搜尋樹並將排序後的資料保存到輸出檔案中
    inorderTraversal(root_8, outputFile_8);
    inorderTraversal(root_10, outputFile_10);

    // 關閉輸出檔案
    outputFile_8.close();
    outputFile_10.close();

    // 創建資料夾
    system("mkdir student8");
    system("mkdir student10");
    system("mkdir course");

    // 分割輸出檔案
    splitFile("student_8_index.txt");
    splitFile("student_10_index.txt");
    splitFile("course_index.txt");

    return 0;
}
