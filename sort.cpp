#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

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

        // 從目錄中讀取檔案並將其插入vector和二元搜尋樹
        string line;
        while (getline(inputFile, line)) {
            stringstream linestream(line);
            string student_id, course_id;
            getline(linestream, student_id, ',');
            getline(linestream, course_id, ',');

            if (!student_id.empty() && !course_id.empty()) {
                data.push_back({student_id, course_id});
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

    // 根據course_id排序，如果course_id相同則根據student_id排序
    sort(data.begin(), data.end(), compareByCourseIdAndStudentId);

    // 將排序後的資料寫入輸出文件
    writeDataToFile(data);

    // 執行中序遍歷二元搜尋樹並將排序後的資料保存到輸出檔案中
    inorderTraversal(root_8, outputFile_8);
    inorderTraversal(root_10, outputFile_10);

    // 關閉輸出檔案
    outputFile_8.close();
    outputFile_10.close();

    return 0;
}
