#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// �G���j�M��`�I
struct Node {
    string data;
    Node* left;
    Node* right;
};

// �s�x�ǥͩM�ҵ{��ƪ����c��
struct StudentCourse {
    string student_id;
    string course_id;
};

// �إ߷s�`�I���禡
Node* createNode(string data) {
    Node* newNode = new Node();
    if (newNode) {
        newNode->data = data;
        newNode->left = newNode->right = nullptr;
    }
    return newNode;
}

// �N�`�I���J�G���j�M�𪺨禡
Node* insertNode(Node* root, string data) {
    // �p�G��O�Ū��A�N�s�`�I�������ڸ`�I
    if (root == nullptr) {
        root = createNode(data);
        return root;
    }

    // �_�h�A�i�滼�j���J
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }

    // �^�ǡ]���ܪ��^�`�I����
    return root;
}

// ���椤�ǹM���G���j�M�𪺨禡
void inorderTraversal(Node* root, ofstream& outputFile) {
    if (root == nullptr) {
        return;
    }
    inorderTraversal(root->left, outputFile);
    outputFile << root->data << endl;
    inorderTraversal(root->right, outputFile);
}

// Ū�����ñN��Ʀs�x�bvector��
void readDataFromFile(vector<StudentCourse>& data, Node*& root_8, Node*& root_10) {
    // Ū���h���ɮ�
    for (int i = 1; i <= 466; i++) {
        // �c�y�ɮ׸��|
        stringstream ss;
        if (i < 10) {
            ss << "data_no_cname/000" << i;
        } else if (i < 100) {
            ss << "data_no_cname/00" << i;
        } else {
            ss << "data_no_cname/0" << i;
        }
        string directoryPath = ss.str();

        // �}�ҿ�J�ɮ�
        ifstream inputFile(directoryPath);

        // �ˬd���O�_���}
        if (!inputFile.is_open()) {
            cerr << "�L�k���}���: " << directoryPath << endl;
            continue;
        }

        // �q�ؿ���Ū���ɮרñN�䴡�Jvector�M�G���j�M��
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

        // ������J�ɮ�
        inputFile.close();
    }
}

void sortDataWithHashing(vector<StudentCourse>& data) {
    unordered_map<string, vector<string>> courseStudentMap;

    // �N��ƴ��J�����
    for (const auto& entry : data) {
        courseStudentMap[entry.course_id].push_back(entry.student_id);
    }

    // �N������ഫ���V�q�ñƧ�
    vector<pair<string, vector<string>>> sortedData(courseStudentMap.begin(), courseStudentMap.end());
    sort(sortedData.begin(), sortedData.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    // �M�ŭ�Ӫ���ƨô��J�Ƨǫ᪺���
    data.clear();
    for (const auto& entry : sortedData) {
        for (const auto& student_id : entry.second) {
            data.push_back({student_id, entry.first});
        }
    }
}

// �N�Ƨǫ᪺��Ƽg�J��X�ɮ�
void writeDataToFile(const vector<StudentCourse>& data) {
    ofstream outputFile("course_index.txt");

    // �ˬd���O�_���}
    if (!outputFile.is_open()) {
        cerr << "open failed." << endl;
        return;
    }

    // �g�J��ƨ��X���
    for (const auto& entry : data) {
        if (entry.course_id.length() == 4)
            outputFile << entry.course_id << "," << entry.student_id << endl;
    }

    // ������X�ɮ�
    outputFile.close();
}

int main() {
    // �}�ҿ�X�ɮ�
    ofstream outputFile_8("student_8_index.txt");
    ofstream outputFile_10("student_10_index.txt");

    // �إߤG���j�M�𪺮ڸ`�I
    Node* root_8 = nullptr;
    Node* root_10 = nullptr;

    // �s�x�ǥͩM�ҵ{��ƪ�vector
    vector<StudentCourse> data;

    // �q���Ū�����
    readDataFromFile(data, root_8, root_10);

    // �ϥ�����ӱƧ�course_id
    sortDataWithHashing(data);

    // �N�Ƨǫ᪺��Ƽg�J��X���
    writeDataToFile(data);

    // ���椤�ǹM���G���j�M��ñN�Ƨǫ᪺��ƫO�s���X�ɮפ�
    inorderTraversal(root_8, outputFile_8);
    inorderTraversal(root_10, outputFile_10);

    // ������X�ɮ�
    outputFile_8.close();
    outputFile_10.close();

    return 0;
}