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
    if (root == nullptr) {
        root = createNode(data);
        return root;
    }

    // 分割資料行以便比較
    stringstream rootDataStream(root->data);
    stringstream newDataStream(data);
    string rootStudentId, rootCourseId, newStudentId, newCourseId;

    getline(rootDataStream, rootStudentId, ',');
    getline(rootDataStream, rootCourseId, ',');
    getline(newDataStream, newStudentId, ',');
    getline(newDataStream, newCourseId, ',');

    // 比較邏輯
    if (newStudentId < rootStudentId) {
        root->left = insertNode(root->left, data);
    } else if (newStudentId > rootStudentId) {
        root->right = insertNode(root->right, data);
    } else { // student_id 相同，根據 course_id 排序
        if (newCourseId < rootCourseId) {
            root->left = insertNode(root->left, data);
        } else if (newCourseId > rootCourseId) {
            root->right = insertNode(root->right, data);
        }
    }

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
    ofstream outputFile_8;
    ofstream outputFile_10;
    outputFile_8.open("student_8_index.txt");
    outputFile_10.open("student_10_index.txt");

    Node* root_8 = nullptr;
    Node* root_10 = nullptr;

    for (int i = 1; i <= 466; i++) {
        stringstream ss;
        string directoryPath;
        if (i < 10)
            ss << "data_no_cname/000" << i;
        else if (i < 100)
            ss << "data_no_cname/00" << i;
        else
            ss << "data_no_cname/0" << i;
        directoryPath = ss.str();

        ifstream inputFile;
        inputFile.open(directoryPath);

        string line;
        while (getline(inputFile, line)) {
            stringstream linestream(line);
            string student_id, course_id;
            getline(linestream, student_id, ',');
            getline(linestream, course_id, ',');

            if (student_id.length() == 8 && course_id.length() == 4) {
                root_8 = insertNode(root_8, line);
            } else if (student_id.length() == 10 && course_id.length() == 4) {
                root_10 = insertNode(root_10, line);
            }
        }
        inputFile.close();
    }

    inorderTraversal(root_8, outputFile_8);
    inorderTraversal(root_10, outputFile_10);

    outputFile_8.close();
    outputFile_10.close();

    return 0;
}
