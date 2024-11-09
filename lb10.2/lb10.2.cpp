#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Перелічуваний тип для спеціальностей
enum Specialty {
    COMPUTER_SCIENCE,
    MATHEMATICS,
    PHYSICS,
    ENGINEERING,
    BIOLOGY
};

// Структура для зберігання інформації про студента
struct Student {
    string lastName;
    int course;
    Specialty specialty;
    double physicsGrade;
    double mathGrade;
    double informaticsGrade;

    double averageGrade() const {
        return (physicsGrade + mathGrade + informaticsGrade) / 3.0;
    }
};

// Функція для введення даних студентів
static void inputStudents(Student* students, int n) {
    for (int i = 0; i < n; ++i) {
        cout << "\nStudent #" << i + 1 << ":\n";
        cout << "Enter last name: ";
        cin >> students[i].lastName;

        cout << "Enter course (1-4): ";
        while (!(cin >> students[i].course) || students[i].course < 1 || students[i].course > 4) {
            cout << "Invalid input. Enter course (1-4): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        int specialtyChoice;
        cout << "Choose specialty (0 - COMPUTER_SCIENCE, 1 - MATHEMATICS, 2 - PHYSICS, 3 - ENGINEERING, 4 - BIOLOGY): ";
        while (!(cin >> specialtyChoice) || specialtyChoice < 0 || specialtyChoice > 4) {
            cout << "Invalid input. Choose specialty (0-4): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        students[i].specialty = static_cast<Specialty>(specialtyChoice);

        cout << "Enter grade in Physics: ";
        while (!(cin >> students[i].physicsGrade) || students[i].physicsGrade < 0 || students[i].physicsGrade > 5) {
            cout << "Invalid input. Enter grade in Physics (0-5): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Enter grade in Math: ";
        while (!(cin >> students[i].mathGrade) || students[i].mathGrade < 0 || students[i].mathGrade > 5) {
            cout << "Invalid input. Enter grade in Math (0-5): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Enter grade in Informatics: ";
        while (!(cin >> students[i].informaticsGrade) || students[i].informaticsGrade < 0 || students[i].informaticsGrade > 5) {
            cout << "Invalid input. Enter grade in Informatics (0-5): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Функція для виведення масиву студентів
static void displayStudents(const Student* students, int n) {
    cout << left << setw(5) << "No" << setw(15) << "Last Name" << setw(8) << "Course"
        << setw(15) << "Specialty" << setw(8) << "Physics" << setw(8) << "Math"
        << setw(12) << "Informatics" << setw(12) << "Average" << endl;
    cout << string(90, '-') << endl;

    for (int i = 0; i < n; ++i) {
        cout << left << setw(5) << i + 1 << setw(15) << students[i].lastName << setw(8)
            << students[i].course << setw(15);

        switch (students[i].specialty) {
        case COMPUTER_SCIENCE: cout << "Comp. Science"; break;
        case MATHEMATICS: cout << "Mathematics"; break;
        case PHYSICS: cout << "Physics"; break;
        case ENGINEERING: cout << "Engineering"; break;
        case BIOLOGY: cout << "Biology"; break;
        }

        cout << setw(8) << students[i].physicsGrade << setw(8) << students[i].mathGrade
            << setw(12) << students[i].informaticsGrade << setw(12) << fixed << setprecision(2)
            << students[i].averageGrade() << endl;
    }
}

// Функція для сортування масиву студентів (пузиркове сортування)
static void sortStudents(Student* students, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (students[j].averageGrade() < students[j + 1].averageGrade() ||
                (students[j].averageGrade() == students[j + 1].averageGrade() && students[j].informaticsGrade < students[j + 1].informaticsGrade) ||
                (students[j].averageGrade() == students[j + 1].averageGrade() && students[j].informaticsGrade == students[j + 1].informaticsGrade &&
                    students[j].lastName < students[j + 1].lastName)) {
                swap(students[j], students[j + 1]);
            }
        }
    }
}

// Функція для створення індексного масиву
static void buildIndexArray(const Student* students, int* indexArray, int n) {
    for (int i = 0; i < n; ++i) {
        indexArray[i] = i;
    }
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (students[indexArray[j]].averageGrade() < students[indexArray[j + 1]].averageGrade() ||
                (students[indexArray[j]].averageGrade() == students[indexArray[j + 1]].averageGrade() &&
                    students[indexArray[j]].informaticsGrade < students[indexArray[j + 1]].informaticsGrade) ||
                (students[indexArray[j]].averageGrade() == students[indexArray[j + 1]].averageGrade() &&
                    students[indexArray[j]].informaticsGrade == students[indexArray[j + 1]].informaticsGrade &&
                    students[indexArray[j]].lastName < students[indexArray[j + 1]].lastName)) {
                swap(indexArray[j], indexArray[j + 1]);
            }
        }
    }
}

// Функція для бінарного пошуку студента
static bool binarySearchStudent(const Student* students, int n, const string& lastName, double averageGrade, double informaticsGrade) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (students[mid].lastName == lastName && students[mid].averageGrade() == averageGrade &&
            students[mid].informaticsGrade == informaticsGrade) {
            return true;
        }
        if (students[mid].averageGrade() > averageGrade ||
            (students[mid].averageGrade() == averageGrade && students[mid].informaticsGrade > informaticsGrade) ||
            (students[mid].averageGrade() == averageGrade && students[mid].informaticsGrade == informaticsGrade &&
                students[mid].lastName > lastName)) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return false;
}

int main() {
    int n;
    cout << "Enter the number of students: ";
    cin >> n;

    if (n <= 0) {
        cout << "Error: Number of students must be greater than 0." << endl;
        return 1;
    }

    // Динамічний масив студентів
    Student* students = new Student[n];

    // Введення даних студентів
    inputStudents(students, n);

    // Виведення масиву студентів
    displayStudents(students, n);

    // Сортування студентів
    sortStudents(students, n);
    cout << "\nSorted Student List:\n";
    displayStudents(students, n);

    // Побудова індексного масиву
    int* indexArray = new int[n];
    buildIndexArray(students, indexArray, n);
    cout << "\nIndex Array (sorted order): ";
    for (int i = 0; i < n; ++i) {
        cout << indexArray[i] + 1 << " "; // +1 для зручності читання (1-based index)
    }
    cout << endl;

    // Пошук студента за прізвищем, середнім балом і оцінкою з інформатики
    string searchLastName;
    double searchAverageGrade, searchInformaticsGrade;
    cout << "\nEnter last name to search: ";
    cin >> searchLastName;
    cout << "Enter average grade to search: ";
    cin >> searchAverageGrade;
    cout << "Enter informatics grade to search: ";
    cin >> searchInformaticsGrade;

    bool found = binarySearchStudent(students, n, searchLastName, searchAverageGrade, searchInformaticsGrade);
    if (found) {
        cout << "Student found in the list." << endl;
    }
    else {
        cout << "Student not found in the list." << endl;
    }

    // Видалення динамічного масиву
    delete[] students;
    delete[] indexArray;

    return 0;
}
