#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// �s�x�ǥͩM�ҵ{��ƪ����c��
struct StudentCourse {
    string student_id;
    string course_id;
};

// Ū�����ñN��Ʀs�x�bvector��
void readDataFromFile(vector<StudentCourse>& data) {
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

        // �q�ؿ���Ū���ɮרñN�䴡�Jvector
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

        // ������J�ɮ�
        inputFile.close();
    }
}

// ����禡�A�Ω�Ƨ�
bool compareByCourseIdAndStudentId(const StudentCourse& a, const StudentCourse& b) {
    if (a.course_id == b.course_id) {
        return a.student_id < b.student_id;
    }
    return a.course_id < b.course_id;
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
    // �s�x�ǥͩM�ҵ{��ƪ�vector
    vector<StudentCourse> data;

    // �q���Ū�����
    readDataFromFile(data);

    // �ھ�course_id�ƧǡA�p�Gcourse_id�ۦP�h�ھ�student_id�Ƨ�
    sort(data.begin(), data.end(), compareByCourseIdAndStudentId);

    // �N�Ƨǫ᪺��Ƽg�J��X���
    writeDataToFile(data);

    return 0;
}
