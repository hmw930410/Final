#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// �G���j�M��`�I
struct Node {
    string data;
    Node* left;
    Node* right;
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

int main() {
    // �}�ҿ�X�ɮ�
    ofstream outputFile_8;
    ofstream outputFile_10;
    outputFile_8.open("student_8_index.txt");
    outputFile_10.open("student_10_index.txt");

    // �إߤG���j�M�𪺮ڸ`�I
    Node* root_8 = nullptr;
    Node* root_10 = nullptr;

    // Ū���h���ɮ�
    for (int i = 1; i <= 466; i++) {
        // �c�y�ɮ׸��|
        stringstream ss;
        string directoryPath;
        if (i < 10)
            ss << "data_no_cname/000" << i;
        else if (10 <= i && i < 100)
            ss << "data_no_cname/00" << i;
        else
            ss << "data_no_cname/0" << i;
        directoryPath = ss.str();

        // �}�ҿ�J�ɮ�
        ifstream inputFile;
        inputFile.open(directoryPath);

        // �q�ؿ���Ū���ɮרñN�䴡�J�G���j�M��
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

        // ������J�ɮ�
        inputFile.close();
    }

    // ���椤�ǹM���G���j�M��ñN�Ƨǫ᪺��ƫO�s���X�ɮפ�
    inorderTraversal(root_8, outputFile_8);
    inorderTraversal(root_10, outputFile_10);

    // ������X�ɮ�
    outputFile_8.close();
    outputFile_10.close();

    return 0;
}