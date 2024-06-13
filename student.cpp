#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// ?G???j?M??`?I
struct Node
{
    string data;
    Node *left;
    Node *right;
};

// ???s?`?I???æÌ
Node *createNode(string data)
{
    Node *newNode = new Node();
    if (newNode)
    {
        newNode->data = data;
        newNode->left = newNode->right = nullptr;
    }
    return newNode;
}

// ?N?`?I???J?G???j?M??æÌ
Node *insertNode(Node *root, string data)
{
    // ?p?G??O????A?N?s?`?I????????`?I
    if (root == nullptr)
    {
        root = createNode(data);
        return root;
    }

    // ?_?h?A?i?â³?j???J
    if (data < root->data)
    {
        root->left = insertNode(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = insertNode(root->right, data);
    }

    // ?^??]??????^?`?I????
    return root;
}

// ??????M???G???j?M??æÌ
void inorderTraversal(Node *root, ofstream &outputFile)
{
    if (root == nullptr)
    {
        return;
    }
    inorderTraversal(root->left, outputFile);
    outputFile << root->data << endl;
    inorderTraversal(root->right, outputFile);
}

int main()
{
    // ?}???X???
    ofstream outputFile_8;
    ofstream outputFile_10;
    outputFile_8.open("student_8_index.txt");
    outputFile_10.open("student_10_index.txt");

    // ???G???j?M???`?I
    Node *root_8 = nullptr;
    Node *root_10 = nullptr;

    // ????h?????
    for (int i = 1; i <= 466; i++)
    {
        // ?c?y?????|
        stringstream ss;
        string directoryPath;
        if (i < 10)
            ss << "data_no_cname/000" << i;
        else if (10 <= i && i < 100)
            ss << "data_no_cname/00" << i;
        else
            ss << "data_no_cname/0" << i;
        directoryPath = ss.str();

        // ?}???J???
        ifstream inputFile;
        inputFile.open(directoryPath);

        // ?q????????????N???J?G???j?M??
        string line;
        while (getline(inputFile, line))
        {
            stringstream linestream(line);
            string student_id, course_id;
            getline(linestream, student_id, ',');
            getline(linestream, course_id, ',');

            if (student_id.length() == 8 && course_id.length() == 4)
            {
                root_8 = insertNode(root_8, line);
            }
            else if (student_id.length() == 10 && course_id.length() == 4)
            {
                root_10 = insertNode(root_10, line);
            }
        }

        // ??????J???
        inputFile.close();
    }

    // ??????M???G???j?M???N???????O?s???X????
    inorderTraversal(root_8, outputFile_8);
    inorderTraversal(root_10, outputFile_10);

    // ??????X???
    outputFile_8.close();
    outputFile_10.close();

    return 0;
}