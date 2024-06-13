#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// 二元搜尋樹節點
struct Node {
    string data;
    Node* left;
    Node* right;
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

int main() {
    // 開啟輸出檔案
    ofstream outputFile_8;
    ofstream outputFile_10;
    outputFile_8.open("student_8_index.txt");
    outputFile_10.open("student_10_index.txt");

    // 建立二元搜尋樹的根節點
    Node* root_8 = nullptr;
    Node* root_10 = nullptr;

    // 讀取多個檔案
    for (int i = 1; i <= 466; i++) {
        // 構造檔案路徑
        stringstream ss;
        string directoryPath;
        if (i < 10)
            ss << "data_no_cname/000" << i;
        else if (10 <= i && i < 100)
            ss << "data_no_cname/00" << i;
        else
            ss << "data_no_cname/0" << i;
        directoryPath = ss.str();

        // 開啟輸入檔案
        ifstream inputFile;
        inputFile.open(directoryPath);

        // 從目錄中讀取檔案並將其插入二元搜尋樹
        string line;
        while (getline(inputFile, line)) {
            stringstream linestream(line);
            string student_id, course_id;
            getline(linestream, student_id, ',');
            getline(linestream, course_id, ',');

            if (student_id.length() == 8 && course_id.length() == 4){
                root_8 = insertNode(root_8, line);
            } else if (student_id.length() == 10 && course_id.length() == 4) {
                root_10 = insertNode(root_10, line);
            }
        }

        // 關閉輸入檔案
        inputFile.close();
    }

    // 執行中序遍歷二元搜尋樹並將排序後的資料保存到輸出檔案中
    inorderTraversal(root_8, outputFile_8);
    inorderTraversal(root_10, outputFile_10);

    // 關閉輸出檔案
    outputFile_8.close();
    outputFile_10.close();

    return 0;
}