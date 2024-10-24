#include <iostream>
#include <vector>
using namespace std;

// Structure to store course information
struct Course {
    string courseName;
    float grade;   // Grade points for the course (e.g., A=10, B=8, etc.)
    int credits;   // Credits for the course
};

// Function to calculate GPA for a semester
float calculateGPA(const vector<Course>& courses) {
    float totalGradePoints = 0;
    int totalCredits = 0;

    // Loop through each course to compute the total grade points and total credits
    for (const auto& course : courses) {
        totalGradePoints += course.grade * course.credits;
        totalCredits += course.credits;
    }

    if (totalCredits == 0) return 0.0; // Avoid division by zero

    return totalGradePoints / totalCredits; // GPA calculation
}

// Function to calculate CGPA across multiple semesters
float calculateCGPA(const vector<vector<Course>>& semesters) {
    float cumulativeGradePoints = 0;
    int cumulativeCredits = 0;

    // Loop through each semester
    for (const auto& semester : semesters) {
        float semesterGPA = calculateGPA(semester);
        for (const auto& course : semester) {
            cumulativeGradePoints += course.grade * course.credits;
            cumulativeCredits += course.credits;
        }
    }

    if (cumulativeCredits == 0) return 0.0;

    return cumulativeGradePoints / cumulativeCredits; // CGPA calculation
}

int main() {
    int numSemesters;

    cout << "Enter the number of semesters: ";
    cin >> numSemesters;

    vector<vector<Course>> semesters(numSemesters);

    // Loop to input data for each semester
    for (int i = 0; i < numSemesters; ++i) {
        int numCourses;
        cout << "\nEnter the number of courses in semester " << i + 1 << ": ";
        cin >> numCourses;

        semesters[i] = vector<Course>(numCourses);

        // Input course details for each semester
        for (int j = 0; j < numCourses; ++j) {
            cout << "Enter details for course " << j + 1 << ":\n";
            cout << "Course name: ";
            cin >> semesters[i][j].courseName;
            cout << "Grade (on a scale of 10): ";
            cin >> semesters[i][j].grade;
            cout << "Credits: ";
            cin >> semesters[i][j].credits;
        }
    }

    // Calculate CGPA
    float CGPA = calculateCGPA(semesters);

    // Output the result
    cout << "\nYour CGPA is: " << CGPA << endl;

    return 0;
}
