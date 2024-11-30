#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Student {
private:
    vector<string> name;
    vector<string> studentNo;
    vector<float> midterm;
    vector<float> secondExam;
    vector<float> assignment;
    vector<float> finalExam;
    vector<int> attendance;
    vector<float> averageScores;

public:
    void readFromCSV(const string& filename);
    void calculateAverage();
    void print(int filter = -1, const string& outputFile = "");
};

void Student::readFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }
    string line;
    getline(file, line); // Skip header line

    while (getline(file, line)) {
        stringstream ss(line);
        string temp;

        string studentName, studentNumber;
        float midtermScore, secondExamScore, assignmentScore, finalScore;
        int attendanceScore;

        getline(ss, studentName, ',');
        getline(ss, studentNumber, ',');
        getline(ss, temp, ',');
        midtermScore = stof(temp);
        getline(ss, temp, ',');
        secondExamScore = stof(temp);
        getline(ss, temp, ',');
        assignmentScore = stof(temp);
        getline(ss, temp, ',');
        finalScore = stof(temp);
        getline(ss, temp, '\n');
        attendanceScore = stoi(temp);

        // Add the student data to vectors
        name.push_back(studentName);
        studentNo.push_back(studentNumber);
        midterm.push_back(midtermScore);
        secondExam.push_back(secondExamScore);
        assignment.push_back(assignmentScore);
        finalExam.push_back(finalScore);
        attendance.push_back(attendanceScore);
    }

    file.close();
}

void Student::calculateAverage() {
    for (size_t i = 0; i < name.size(); ++i) {
        averageScores.push_back(midterm[i] * 0.2f + secondExam[i] * 0.2f + assignment[i] * 0.2f + finalExam[i] * 0.4f);
    }
}

void Student::print(int filter, const string& outputFile) {
    ofstream file;
    if (!outputFile.empty()) {
        file.open(outputFile);
        if (!file.is_open()) {
            cerr << "Error writing output file!" << endl;
            return;
        }
    }

    ostream& output = outputFile.empty() ? cout : file;

    output << left << setw(25) << "Ogrenci Adi" << right << setw(10) << "Numara" << right << setw(10) << "Ortalama" << endl;
    output << string(45, '-') << endl;

    for (size_t i = 0; i < name.size(); ++i) {
        bool print = false;
        if (filter == 0 && averageScores[i] >= 50) print = true;
        if (filter == 1 && averageScores[i] < 50) print = true;
        if (filter == -1) print = true;

        if (print) {
            output << left << setw(25) << name[i] << right << setw(10) << studentNo[i] << right << setw(10) << averageScores[i] << endl;
        }
    }

    if (!outputFile.empty()) {
        file.close();
    }
}

int main() {
    Student student;
    string filename;
    cout << "Enter CSV filename: ";
    cin >> filename;
    student.readFromCSV(filename);
    student.calculateAverage();

    int filter;
    cout << "Enter filter (0: Pass, 1: Fail, -1: All): ";
    cin >> filter;

    string outputFile;
    cout << "Enter output file (leave empty for console): ";
    cin.ignore();
    getline(cin, outputFile);

    student.print(filter, outputFile);

    return 0;
}
