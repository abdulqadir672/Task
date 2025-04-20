#include <iostream>
#include "CGPA.h"
#include <string>
using namespace std;

void CGPA::setCreditHours1() {
    cout << "Enter Credit_Hours Of Subject 1: ";
    cin >> creditHours1;
}

void CGPA::setCreditHours2() {
    cout << "Enter Credit_Hours Of Subject 2: ";
    cin >> creditHours2;
}

void CGPA::setCreditHours3() {
    cout << "Enter Credit_Hours Of Subject 3: ";
    cin >> creditHours3;
    cout << endl;
}

void CGPA::setCreditHours4() {
    cout << "Enter Credit_Hours Of Subject 4: ";
    cin >> creditHours4;
    cout << endl;
}

void CGPA::setCreditHours5() {
    cout << "Enter Credit_Hours Of Subject 5: ";
    cin >> creditHours5;
    cout << endl;
}

void CGPA::TotalCreditHours() {
    TotalCredit = creditHours1 + creditHours2 + creditHours3 + creditHours4 + creditHours5;
}

void CGPA::setQualityPoints1() {
    cout << "Enter Quality_Points Of Subject 1: ";
    cin >> QualityPoints1;
}

void CGPA::setQualityPoints2() {
    cout << "Enter Quality_Points Of Subject 2: ";
    cin >> QualityPoints2;
}

void CGPA::setQualityPoints3() {
    cout << "Enter Quality_Points Of Subject 3: ";
    cin >> QualityPoints3;
    cout << endl;
}

void CGPA::setQualityPoints4() {
    cout << "Enter Quality_Points Of Subject 4: ";
    cin >> QualityPoints4;
    cout << endl;
}

void CGPA::setQualityPoints5() {
    cout << "Enter Quality_Points Of Subject 5: ";
    cin >> QualityPoints5;
    cout << endl;
}

void CGPA::TotalQualityPoints() {
    TotalQP = QualityPoints1 + QualityPoints2 + QualityPoints3 + QualityPoints4 + QualityPoints5;
}

void CGPA::calculateCGPA() {
    if (TotalCredit != 0)
        cgpa = TotalQP / TotalCredit;
    else
        cout << "Error: Total credit hours is zero. CGPA can't be calculated.\n";
}

void CGPA::displayCGPA() {
    cout << endl << "Credit_Hours Of subjects: " << TotalCredit << endl;
    cout << endl << "Quality_Points Of Subjects: " << TotalQP << endl;
    cout << endl << "GPA: " << cgpa << endl;
}
