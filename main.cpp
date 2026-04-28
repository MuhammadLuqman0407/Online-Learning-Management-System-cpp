#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
using namespace std;

// Forward declarations
class Course;
class Assignment;
class Quiz;

class User {
protected:
    string name;
    string email;
    string pass;
    
public:
    int role;  // 1: Student, 2: Instructor, 3: Admin
    User() {
        name = "";
        email = "";
        pass = "";
        role = 0;
    }
    
    int getRole(){
        return role;  // Just return the role, don't ask again
    }
    string getemail(){
        return email;
    }
    
    string getName(){
        return name;
    }

    void displayMenu() {
        cout << "| 1 : Register                        |\n";
        cout << "| 2 : Log In                          |\n";
        cout << "| 3 : Exit                            |\n";
    }


    bool checkDuplicate(const string& newEmail, const string& newName) {
        ifstream file1("1.user.txt");
        if (file1.is_open()) {
            string line;
            while (getline(file1, line)) {
                stringstream ss(line);
                string file_name, file_email, file_pass;
                getline(ss, file_name, '|');
                getline(ss, file_email, '|');
                getline(ss, file_pass, '|');

                if (file_email == newEmail) {
                    cout << "The same email is already registered." << endl;
                    return true;
                }
                if (file_name == newName) {
                    cout << "The same username is already taken." << endl;
                    return true;
                }
            }
            file1.close();
        }
        return false;
    }

    bool signIn() {
        ifstream file;
        string inputEmail, inputPass;
        cout << "Enter the Email: ";
        cin.ignore();
        getline(cin, inputEmail);
        cout << "Enter the Password: ";
        getline(cin, inputPass);

        file.open("1.user.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string file_name, file_email, file_pass;
                int file_role;
                getline(ss, file_name, '|');
                getline(ss, file_email, '|');
                getline(ss, file_pass, '|');
                ss >> file_role;

                if (file_email == inputEmail && file_pass == inputPass) {
                    name = file_name;
                    email = file_email;
                    pass = file_pass;
                    role = file_role;
                    cout << "Sign In Successfully!" << endl;
                    return true;
                }
            }
            file.close();
            cout << "Invalid Email or Password." << endl;
            return false;
        } 
        else {
            cout << "Error opening file." << endl;
            return false;
        }
    }

    void viewProfile() {
        if (name.empty() || email.empty()) {
            cout << "Please log in first to view the profile." << endl;
        } 
        else {
            cout << "\n === Profile Information ===" << endl;
            cout << "  Name: " << name << endl;
            cout << "  Email: " << email << endl;
            cout << "  Role: " << (role == 1 ? "Student" : role == 2 ? "Instructor" : "Admin") << endl;
        }
    }

    void editProfile() {
    if (name.empty() || email.empty()) {
        cout << "Please log in first to edit the profile." << endl;
        return;
    }

    string originalEmail = email; // Store old email to find correct record

    cout << "=== Edit Profile ===" << endl;
    cout << "Enter new Full Name (or press Enter to keep current): ";
    cin.ignore();
    string newName;
    getline(cin, newName);
    if (!newName.empty()) {
        name = newName;
    }

    cout << "Enter new Email (or press Enter to keep current): ";
    string newEmail;
    getline(cin, newEmail);
    if (!newEmail.empty() && !checkDuplicate(newEmail, name)) {
        email = newEmail;
    }

    cout << "Enter new Password (or press Enter to keep current): ";
    string newPass;
    getline(cin, newPass);
    if (!newPass.empty()) {
        pass = newPass;
    }

    // Read all users and update the matching one using original email
    vector<string> users;
    ifstream file("1.user.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string file_name, file_email, file_pass;
            int file_role;
            getline(ss, file_name, '|');
            getline(ss, file_email, '|');
            getline(ss, file_pass, '|');
            ss >> file_role;

            if (file_email == originalEmail) {
                // Update with new data
                string updated = name + "|" + email + "|" + pass + "|" + to_string(role);
                users.push_back(updated);
            } else {
                users.push_back(line); // Keep other users as-is
            }
        }
        file.close();
    }

    // Write all user data back to the file
    ofstream outFile("1.user.txt");
    if (outFile.is_open()) {
        for (const auto& user : users) {
            outFile << user << endl;
        }
        outFile.close();
    } else {
        cout << "File could not be updated." << endl;
    }

    cout << "Profile updated successfully." << endl;
}

};

// Admin class 
class Admin {
private:
    string name;
    string cnic;
    string adminID;
    string department;
    vector<string> courseIDs;
    vector<string> instructors;
    vector<string> cert_course_ids;
    vector<string> cert_course_names;
    vector<double> cert_payment;
    vector<string> non_cert_course_ids;
    vector<string> non_cert_course_names;

public:
    Admin() {
        name = "";
        cnic = "";
        adminID = "";
    }

    Admin(string name, string cnic, string id) {
        this->name = name;
        this->cnic = cnic;
        this->adminID = id;
    }

    string getName() {
        return name;
    }

    string getId() {
        return adminID;
    }

    string getCnic() {
        return cnic;
    }

    void viewAllStudents() {
        ifstream file("2.Student.txt");
        if (file.is_open()) {
            string line;
            cout << "\n=== All Students ===" << endl;
            while (getline(file, line)) {
                stringstream ss(line);
                string name, id, email;
                getline(ss, name, '|');
                getline(ss, id, '|');
                getline(ss, email, '|');
                cout << "Name: " << name << " | ID: " << id << " | Email: " << email << endl;
            }
            file.close();
        }
    }

    void viewAllInstructors() {
        ifstream file("3.Instructor.txt");
        if (file.is_open()) {
            string line;
            cout << "\n=== All Instructors ===" << endl;
            while (getline(file, line)) {
                stringstream ss(line);
                string name, id, email, expertise, salary;
                getline(ss, name, '|');
                getline(ss, id, '|');
                getline(ss, email, '|');
                getline(ss, expertise, '|');
                getline(ss, salary, '|');
                cout << "Name: " << name << " | ID: " << id << " | Email: " << email << " | Expertise: " << expertise << endl;
            }
            file.close();
        }
    }

    // Fixed verifyAdminID function to handle 4 fields
    bool verifyAdminID(const string& id) {
        ifstream file("4.Admin.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string file_name, file_id, file_email, file_dept;
                getline(ss, file_name, '|');
                getline(ss, file_id, '|');
                getline(ss, file_email, '|');
                getline(ss, file_dept, '|');
                
                if (file_id == id) {
                    adminID = file_id;
                    name = file_name;
                    department = file_dept;
                    file.close();
                    return true;
                }
            }
            file.close();
        }
        return false;
    }

    void info() {
        cout << "Enter the Admin Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter the Admin Id: ";
        cin >> adminID;
        // cout << "Enter the CNIC No: ";
        // cin >> cnic;
        cout << "Enter the Department: ";
        cin.ignore();
        getline(cin, department);
        saveFile();
    }

    // Fixed saveFile to use consistent format
    void saveFile() {
        ofstream file2;
        file2.open("4.Admin.txt", ios::app);
        if (file2.is_open()) {
            file2 << name << "|" << adminID << "|admin@example.com|" << department << endl;
            file2.close();
        } 
        else {
            cout << "Error: file could not be opened" << endl;
        }
    }

    void course() {
        cout << "1 : Add Certificate Course" << endl;
        cout << "2 : Add Non-Certificate Course" << endl;
        cout << "3 : Exiting " << endl;
        int co;
        cin >> co;
        if (co == 1) {
            addCertificateCourse();
        } 
        else if (co == 2) {
            addNonCertificateCourse();
        }
    }

    void addCertificateCourse() {
        int co;
        cout << "Enter the number of certificate courses to add: ";
        cin >> co;
        cert_course_ids.resize(co);
        cert_course_names.resize(co);
        cert_payment.resize(co);

        for (int i = 0; i < co; ++i) {
            cout << "Enter details for certificate course " << (i + 1) << ":" << endl;
            cout << "Course ID: ";
            cin >> cert_course_ids[i];
            cout << "Course Name: ";
            cin.ignore();
            getline(cin, cert_course_names[i]);
            cout << " Course Price (MRP) :";
            cin >> cert_payment[i];
        }
        saveCertificateCoursesToFile();
    }

    void addNonCertificateCourse() {
        int c;
        cout << "Enter the number of non-certificate courses to add: ";
        cin >> c;
        non_cert_course_ids.resize(c);
        non_cert_course_names.resize(c);

        for (int i = 0; i < c; ++i) {
            cout << "Enter details for non-certificate course " << (i + 1) << ":" << endl;
            cout << "Course ID: ";
            cin >> non_cert_course_ids[i];
            cout << "Course Name: ";
            cin.ignore();
            getline(cin, non_cert_course_names[i]);
        }
        saveNonCertificateCoursesToFile();
    }

    // Fixed file format to use | delimiter
    void saveCertificateCoursesToFile() {
        ofstream file5("5.CertificateCourse.txt", ios::app);
        if (file5.is_open()) {
            for (size_t i = 0; i < cert_course_ids.size(); ++i) {
                file5 << cert_course_ids[i] << "|" << cert_course_names[i] << "|" << cert_payment[i] << endl;
            }
            file5.close();
        } 
        else {
            cout << "Error: Could not open or create CertificateCourse.txt" << endl;
        }
    }

    void saveNonCertificateCoursesToFile() {
        ofstream file6("6.NonCertificateCourse.txt", ios::app);
        if (file6.is_open()) {
            for (size_t i = 0; i < non_cert_course_ids.size(); ++i) {
                file6 << non_cert_course_ids[i] << "|" << non_cert_course_names[i] << endl;
            }
            file6.close();
        } 
        else {
            cout << "Error: Could not open or create NonCertificateCourse.txt" << endl;
        }
    }

    void viewCourses() {
        cout << "1: View Certificate Courses" << endl;
        cout << "2: View Non-Certificate Courses" << endl;
        int ch;
        cin >> ch;

        if (ch == 1) {
            ifstream file3("5.CertificateCourse.txt");
            if (file3.is_open()) {
                string line;
                cout << "Certificate Courses:" << endl;
                while (getline(file3, line)) {
                    cout << line << endl;
                }
                file3.close();
            } 
            else {
                cout << "No certificate courses found." << endl;
            }
        } 
        else if (ch == 2) {
            ifstream file4("6.NonCertificateCourse.txt");
            if (file4.is_open()) {
                string line;
                cout << "Non-Certificate Courses:" << endl;
                while (getline(file4, line)) {
                    cout << line << endl;
                }
                file4.close();
            } 
            else {
                cout << "No non-certificate courses found." << endl;
            }
        } 
        else {
            cout << "Invalid choice!" << endl;
        }
    }

    void viewEnrollmentReports() {
        ifstream file("9.StudentEnrollments.txt");
        if (file.is_open()) {
            string line;
            cout << "\n=== Enrollment Reports ===" << endl;
            while (getline(file, line)) {
                stringstream ss(line);
                string studentID, studentName, courseID, courseName, courseType, payment, status, assignmentStatus, quizStatus;
                getline(ss, studentID, '|');
                getline(ss, studentName, '|');
                getline(ss, courseID, '|');
                getline(ss, courseName, '|');
                getline(ss, courseType, '|');
                getline(ss, payment, '|');
                getline(ss, status, '|');
                getline(ss, assignmentStatus, '|');
                getline(ss, quizStatus, '|');
                
                cout << "Student: " << studentName << " (" << studentID << ") | Course: " << courseName 
                     << " (" << courseID << ") | Type: " << courseType << " | Status: " << status << endl;
            }
            file.close();
        }
    }

    string getAdminID() { return adminID; }
};

class Course {
protected:
    string c_name;
    string c_id;
    string c_instructor;
    string c_time;
    string c_credit;
    Admin *admin;

public:
    void setCourse(string name, string id, string instructor, string time, string credit){
        this-> c_name = name;
        this-> c_id = id;
        this-> c_instructor = instructor;
        this-> c_credit = credit;
    }
};

class Student {
private:
    string name;
    string studentID;
    string email;
    fstream fileStream;
    vector<string> enrolledCourses;

public:
    Student() { }

    void setinput() {
        cout << "Enter Student Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Student ID: ";
        getline(cin, studentID);
        cout << "Enter Email: ";
        getline(cin, email);

        fileStream.open("2.Student.txt", ios::app);
        if (fileStream.is_open()) {
            fileStream << name << "|" << studentID << "|" << email << endl;
            fileStream.close();
            cout << "Student details saved successfully." << endl;
        } 
        else {
            cout << "Error: file could not be opened" << endl;
        }
    }

    bool verifyStudentID(const string& id) {
        ifstream file("2.Student.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string file_name, file_id, file_email;
                getline(ss, file_name, '|');
                getline(ss, file_id, '|');
                getline(ss, file_email, '|');
                
                if (file_id == id) {
                    studentID = file_id;
                    name = file_name;
                    email = file_email;
                    file.close();
                    return true;
                }
            }
            file.close();
        }
        return false;
    }

    void viewStudent() {
            fileStream.open("2.Student.txt", ios::in);
            if (fileStream.is_open()) {
                string line;
                cout << " ------------------------------------------ " << endl;
                while (getline(fileStream, line)) {
                    cout << line << endl;
                }
                fileStream.close();
            } 
            else {
                cout << "Error: file could not be opened" << endl;
            }
        }

        void enrollInCourse() {
        cout << "\n=== Available Courses ===" << endl;
        cout << "1. Certificate Courses" << endl;
        cout << "2. Non-Certificate Courses" << endl;
        cout << "Choose course type: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            ifstream file("5.CertificateCourse.txt");
            vector<pair<string, pair<string, string>>> certCourses;

            if (file.is_open()) {
                string line;
                cout << "\nAvailable Certificate Courses:" << endl;
                while (getline(file, line)) {
                    stringstream ss(line);
                    string courseID, courseName, fee;
                    getline(ss, courseID, '|');
                    getline(ss, courseName, '|');
                    getline(ss, fee, '|');
                    certCourses.push_back({courseID, {courseName, fee}});
                    cout << "ID: " << courseID << " | Name: " << courseName << " | Fee: $" << fee << endl;
                }
                file.close();
            }

            string courseID;
            cout << "Enter Course ID: ";
            cin >> courseID;

            bool found = false;
            string courseName, fee;

            for (auto &course : certCourses) {
                if (course.first == courseID) {
                    found = true;
                    courseName = course.second.first;
                    fee = course.second.second;
                    break;
                }
            }

            if (!found) {
                cout << "Error: This certificate course ID is not present.\n";
                return;
            }

            double payment;
            cout << "Course Name: " << courseName << endl;
            cout << "Enter Payment Amount: ";
            cin >> payment;
            if(payment < stod(fee)) {
                cout << "Error: Insufficient payment. Course fee is $" << fee << endl;
                return;
            }
            ofstream enrollFile("9.StudentEnrollments.txt", ios::app);
            if (enrollFile.is_open()) {
                enrollFile << studentID << "|" << name << "|" << courseID << "|" << courseName << "|Certificate|" << payment << "|Enrolled|0|0" << endl;
                enrollFile.close();
                cout << "Successfully enrolled in certificate course!" << endl;
            }

        } else if (choice == 2) {
            ifstream file("6.NonCertificateCourse.txt");
            vector<pair<string, string>> nonCertCourses;

            if (file.is_open()) {
                string line;
                cout << "\nAvailable Non-Certificate Courses:" << endl;
                while (getline(file, line)) {
                    stringstream ss(line);
                    string courseID, courseName;
                    getline(ss, courseID, '|');
                    getline(ss, courseName, '|');
                    nonCertCourses.push_back({courseID, courseName});
                    cout << "ID: " << courseID << " | Name: " << courseName << endl;
                }
                file.close();
            }

            string courseID;
            cout << "Enter Course ID: ";
            cin >> courseID;

            bool found = false;
            string courseName;

            for (auto &course : nonCertCourses) {
                if (course.first == courseID) {
                    found = true;
                    courseName = course.second;
                    break;
                }
            }

            if (!found) {
                cout << "Error: This non-certificate course ID is not present.\n";
                return;
            }

            ofstream enrollFile("9.StudentEnrollments.txt", ios::app);
            if (enrollFile.is_open()) {
                enrollFile << studentID << "|" << name << "|" << courseID << "|" << courseName << "|Non-Certificate|0|Enrolled|0|0" << endl;
                enrollFile.close();
                cout << "Successfully enrolled in non-certificate course!" << endl;
            }
        } else {
            cout << "Invalid course type selected.\n";
        }
    }


    // void viewMyCourses() {
    //     cout << "\n=== My Courses ===" << endl;
    //     cout << "------------------------" << endl;
    //     cout << " 1-> Enrolled Courses" << endl;
    //     cout << "------------------------" << endl;
        
    //     ifstream file("9.StudentEnrollments.txt");
    //     if (file.is_open()) {
    //         string line;
    //         bool found = false;
        
    //         while (getline(file, line)) {
    //             stringstream ss(line);
    //             string fileStudentID, fileName, courseID, courseName, courseType, payment, status, assignmentStatus, quizStatus;
                
    //             getline(ss, fileStudentID, '|');
    //             getline(ss, fileName, '|');
    //             getline(ss, courseID, '|');
    //             getline(ss, courseName, '|');
    //             getline(ss, courseType, '|');
    //             getline(ss, payment, '|');
    //             getline(ss, status, '|');
    //             getline(ss, assignmentStatus, '|');
    //             getline(ss, quizStatus, '|');
                
    //             if (fileStudentID == studentID) {
    //                 found = true;
    //                 cout << "Course ID: " << courseID << " | Course: " << courseName << endl;
    //                 cout << "Type: " << courseType << " | Status: " << status << endl;
    //                 cout << "Assignment: " << (assignmentStatus == "1" ? "Completed" : "Pending") << endl;
    //                 cout << "Quiz: " << (quizStatus == "1" ? "Completed" : "Pending") << endl;
                    
    //                 // if (assignmentStatus == "1" && quizStatus == "1") {
    //                 //     cout << "*** COURSE COMPLETED! ***" << endl;
    //                 //     cout << "--------------------------"<<endl;
    //                 //     if (courseType == "Certificate") {
    //                 //         cout << "You can apply for certificate!" << endl;
    //                 //     }
    //                 // }
    //                 // cout << "------------------------" << endl;
    //             }
    //         }
            
    //         if (!found) {
    //             cout << "No courses enrolled yet." << endl;
    //         }
    //         file.close();
    //     }
    // }


        void viewMyCourses() {
            cout << "\n=== My Courses (Current/Enrolled) ===" << endl;
            cout << "------------------------" << endl;
            
            ifstream file("9.StudentEnrollments.txt");
            if (file.is_open()) {
                string line;
                bool found = false;
            
                while (getline(file, line)) {
                    stringstream ss(line);
                    string fileStudentID, fileName, courseID, courseName, courseType, payment, status, assignmentStatus, quizStatus;
                    
                    getline(ss, fileStudentID, '|');
                    getline(ss, fileName, '|');
                    getline(ss, courseID, '|');
                    getline(ss, courseName, '|');
                    getline(ss, courseType, '|');
                    getline(ss, payment, '|');
                    getline(ss, status, '|');
                    getline(ss, assignmentStatus, '|');
                    getline(ss, quizStatus, '|');
                    
                    if (fileStudentID == studentID && status != "Completed") {
                        found = true;
                        cout << "\nCourse ID: " << courseID << " | Course: " << courseName << endl;
                        cout << "Type: " << courseType << " | Status: " << status << endl;
                        cout << "Assignment: " << (assignmentStatus == "1" ? "Completed" : "Pending") << endl;
                        cout << "Quiz: " << (quizStatus == "1" ? "Completed" : "Pending") << endl;
                        cout << "------------------------" << endl;
                    }
                }
                
                if (!found) {
                    cout << "No current/enrolled courses." << endl;
                }
                file.close();
            }
        }

    void viewCompletedCourses() {
            cout << "\n=== My Completed Courses ===" << endl;
            cout << "------------------------" << endl;
            
            ifstream file("9.StudentEnrollments.txt");
            if (file.is_open()) {
                string line;
                bool found = false;
                int certificateCount = 0;
                int nonCertificateCount = 0;
            
                while (getline(file, line)) {
                    stringstream ss(line);
                    string fileStudentID, fileName, courseID, courseName, courseType, payment, status, assignmentStatus, quizStatus;
                    
                    getline(ss, fileStudentID, '|');
                    getline(ss, fileName, '|');
                    getline(ss, courseID, '|');
                    getline(ss, courseName, '|');
                    getline(ss, courseType, '|');
                    getline(ss, payment, '|');
                    getline(ss, status, '|');
                    getline(ss, assignmentStatus, '|');
                    getline(ss, quizStatus, '|');
                    
                    if (fileStudentID == studentID && status == "Completed") {
                        found = true;
                        cout << "\nCourse ID: " << courseID << " | Course: " << courseName << endl;
                        cout << "Type: " << courseType << endl;
                        cout << "Assignment: " << (assignmentStatus == "1" ? "✓ Completed" : "Pending") << endl;
                        cout << "Quiz: " << (quizStatus == "1" ? "✓ Completed" : "Pending") << endl;
                        
                        if (courseType == "Certificate") {
                            certificateCount++;
                            cout << "Status: ✓ COMPLETED - Certificate Available" << endl;
                        } 
                        else {
                            nonCertificateCount++;
                            cout << "Status: ✓ COMPLETED" << endl;
                        }
                        cout << "------------------------" << endl;
                    }
                }
                
                if (found) {
                    cout << "\n=== Summary ===" << endl;
                    cout << "Certificate Courses Completed: " << certificateCount << endl;
                    cout << "Non-Certificate Courses Completed: " << nonCertificateCount << endl;
                    cout << "Total Completed: " << (certificateCount + nonCertificateCount) << endl;
                } else {
                    cout << "No completed courses yet." << endl;
                }
                file.close();
            }
        }


        


    void attemptAssignment() {
        string courseID;
        cout << "Enter Course ID for assignment: ";
        cin >> courseID;
        
        // Check if assignment exists for this course
        ifstream assignFile("10.Assignments.txt");
        string line;
        bool assignmentFound = false;
        
        while (getline(assignFile, line)) {
            stringstream ss(line);
            string fileCourseID, title, description;
            getline(ss, fileCourseID, '|');
            getline(ss, title, '|');
            getline(ss, description, '|');
            
            if (fileCourseID == courseID) {
                assignmentFound = true;
                cout << "\n=== Assignment ===" << endl;
                cout << "Course ID: " << fileCourseID << endl;
                cout << "Title: " << title << endl;
                cout << "Description: " << description << endl;
                
                cout << "\nSubmit your assignment (type your answer): ";
                string answer;
                cin.ignore();
                getline(cin, answer);
                
                // Save submission
                ofstream subFile("12.AssignmentSubmissions.txt", ios::app);
                if (subFile.is_open()) {
                    subFile << studentID << "|" << courseID << "|" << answer << "|Submitted" << endl;
                    subFile.close();
                    
                    // Update enrollment status
                    updateCourseProgress(courseID, "assignment");
                    cout << "Assignment submitted successfully!" << endl;
                }
                break;
            }
        }
        assignFile.close();
        
        if (!assignmentFound) {
            cout << "No assignment found for this course." << endl;
        }
    }

    void attemptQuiz() {
        string courseID;
        cout << "Enter Course ID for quiz: ";
        cin >> courseID;
        
        // Check if quiz exists for this course
        ifstream quizFile("11.Quizzes.txt");
        string line;
        bool quizFound = false;
        
        while (getline(quizFile, line)) {
            stringstream ss(line);
            string fileCourseID, title, question, optionA, optionB, optionC, optionD, correctAnswer;
            getline(ss, fileCourseID, '|');
            getline(ss, title, '|');
            getline(ss, question, '|');
            getline(ss, optionA, '|');
            getline(ss, optionB, '|');
            getline(ss, optionC, '|');
            getline(ss, optionD, '|');
            getline(ss, correctAnswer, '|');
            
            if (fileCourseID == courseID) {
                quizFound = true;
                cout << "\n=== Quiz ===" << endl;
                cout << "Course ID: " << fileCourseID << endl;
                cout << "Title: " << title << endl;
                cout << "Question: " << question << endl;
                cout << "A) " << optionA << endl;
                cout << "B) " << optionB << endl;
                cout << "C) " << optionC << endl;
                cout << "D) " << optionD << endl;
                
                cout << "Your answer (A/B/C/D): ";
                string userAnswer;
                cin >> userAnswer;
                
                bool isCorrect = (userAnswer == correctAnswer);
                
                // Save quiz attempt
                ofstream attemptFile("13.QuizAttempts.txt", ios::app);
                if (attemptFile.is_open()) {
                    attemptFile << studentID << "|" << courseID << "|" << userAnswer << "|" << (isCorrect ? "Correct" : "Incorrect") << endl;
                    attemptFile.close();
                    
                    if (isCorrect) {
                        cout << "Correct! Quiz completed successfully!" << endl;
                        updateCourseProgress(courseID, "quiz");
                    } else {
                        cout << "Incorrect. Try again later." << endl;
                    }
                }
                break;
            }
        }
        quizFile.close();
        
        if (!quizFound) {
            cout << "No quiz found for this course." << endl;
        }
    }

    void updateCourseProgress(const string& courseID, const string& type) {
        vector<string> enrollments;
        ifstream file("9.StudentEnrollments.txt");
        string line;
        
        while (getline(file, line)) {
            stringstream ss(line);
            string fileStudentID, fileName, fileCourseID, courseName, courseType, payment, status, assignmentStatus, quizStatus;
            
            getline(ss, fileStudentID, '|');
            getline(ss, fileName, '|');
            getline(ss, fileCourseID, '|');
            getline(ss, courseName, '|');
            getline(ss, courseType, '|');
            getline(ss, payment, '|');
            getline(ss, status, '|');
            getline(ss, assignmentStatus, '|');
            getline(ss, quizStatus, '|');
            
            if (fileStudentID == studentID && fileCourseID == courseID) {
                if (type == "assignment") {
                    assignmentStatus = "1";
                }
                if (type == "quiz") {
                    quizStatus = "1";
                }
                
                // Check if course is completed
                if (assignmentStatus == "1" && quizStatus == "1") {
                    status = "Completed";
                }
            }
            
            string updatedLine = fileStudentID + "|" + fileName + "|" + fileCourseID + "|" + courseName + "|" + courseType + "|" + payment + "|" + status + "|" + assignmentStatus + "|" + quizStatus;
            enrollments.push_back(updatedLine);
        }
        file.close();
        
        // Rewrite file
        ofstream outFile("9.StudentEnrollments.txt");
        for (const string& enrollment : enrollments) {
            outFile << enrollment << endl;
        }
        outFile.close();
    }


    // In Student class, replace the applyCertificate() function

    void applyCertificate() {
        string courseID;
        cout << "Enter Course ID for certificate: ";
        cin >> courseID;
        
        // Check if course is completed
        ifstream file("9.StudentEnrollments.txt");
        string line;
        bool courseFound = false;
        string courseName = "";
        string courseType = "";
        string enrollmentStatus = "";
        string assignmentStatus = "";
        string quizStatus = "";
        
        while (getline(file, line)) {
            stringstream ss(line);
            string fileStudentID, fileName, fileCourseID, filCourseName, fileCourseType, payment, status, fileAssignStatus, fileQuizStatus;
            
            getline(ss, fileStudentID, '|');
            getline(ss, fileName, '|');
            getline(ss, fileCourseID, '|');
            getline(ss, filCourseName, '|');
            getline(ss, fileCourseType, '|');
            getline(ss, payment, '|');
            getline(ss, status, '|');
            getline(ss, fileAssignStatus, '|');
            getline(ss, fileQuizStatus, '|');
            
            if (fileStudentID == studentID && fileCourseID == courseID) {
                courseFound = true;
                courseName = filCourseName;
                courseType = fileCourseType;
                enrollmentStatus = status;
                assignmentStatus = fileAssignStatus;
                quizStatus = fileQuizStatus;
                break;
            }
        }
        file.close();
        
        if (!courseFound) {
            cout << "Sorry, the course with this ID is not found or not enrolled." << endl;
            return;
        }
        
        // Check if it's a certificate course
        if (courseType != "Certificate") {
            cout << "This is not a certificate course. You cannot apply for a certificate." << endl;
            return;
        }
        
        // Check if course is completed (both assignment and quiz done)
        if (assignmentStatus != "1" || quizStatus != "1") {
            cout << "You cannot apply for certificate. Please complete both assignment and quiz first." << endl;
            return;
        }
        
        // Apply for certificate
        ofstream certFile("14.CertificateApplications.txt", ios::app);
        if (certFile.is_open()) {
            time_t now = time(0);
            certFile << studentID << "|" << name << "|" << courseID << "|" << courseName << "|Pending|" << now << endl;
            certFile.close();
            cout << "Certificate application submitted! Status: Pending" << endl;
            cout << "It will be approved within 24 hours or by admin." << endl;
        } else {
            cout << "Error submitting certificate application." << endl;
        }
    }

    // ...existing code...

    // Add this new function to Student class to check certificate status
    void checkCertificateStatus() {
    ifstream file("14.CertificateApplications.txt");
    if (file.is_open()) {
        string line;
        bool found = false;
        cout << "\n=== My Certificate Applications ===" << endl;
        
        while (getline(file, line)) {
            stringstream ss(line);
            string fileStudentID, fileName, courseID, courseName, status, timestamp;
            
            getline(ss, fileStudentID, '|');
            getline(ss, fileName, '|');
            getline(ss, courseID, '|');
            getline(ss, courseName, '|');
            getline(ss, status, '|');
            getline(ss, timestamp, '|');
            
            if (fileStudentID == studentID) {
                found = true;
                time_t appliedTime = stoll(timestamp);
                time_t currentTime = time(0);
                double hoursPassed = difftime(currentTime, appliedTime) / 3600.0;
                
                cout << "\nCourse: " << courseName << endl;
                cout << "Application Status: " << status << endl;
                cout << "Hours since application: " << hoursPassed << endl;
                
                // if (status == "Pending" && hoursPassed >= 24) {
                //     cout << "**Certificate is now AVAILABLE for download!**" << endl;
                    
                // }
                if (status == "Pending" && hoursPassed >= 24) {
                    cout << "**Certificate is now AVAILABLE for download!**" << endl;
                    
                    cout << "Do you want to download/view the certificate? (y/n): ";
                    char choice;
                    cin >> choice;
                    if (choice == 'y' || choice == 'Y') {
                        // Display certificate details
                        cout << "\n==========================================" << endl;
                        cout << "         CERTIFICATE OF COMPLETION" << endl;
                        cout << "==========================================" << endl;
                        cout << "This is to certify that" << endl;
                        cout << fileName << endl;
                        cout << "has successfully completed the course" << endl;
                        cout << courseName << endl;
                        cout << "Course ID: " << courseID << endl;
                        cout << "Student ID: " << fileStudentID << endl;
                        cout << "Issued on: " << ctime(&currentTime);
                        cout << "==========================================" << endl;
                        
                        // Optionally, update status to "Downloaded" (commented out as per user request, but can be added if needed)
                        // To update, you would need to rewrite the file similar to other update functions in the code.
                    }
                }
            }
        }
        
            if (!found) {
                cout << "No certificate applications found." << endl;
            }
            file.close();
         }
    }
    string getStudentID() { return studentID; }
};


class Instructor {
private:
    string name;
    string instructorID;
    string email;
    string subjectExpertise;
    fstream fileStreamInst;

public:
    void setInput() {
        cout << "Enter Instructor Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Instructor ID: ";
        getline(cin, instructorID);
        cout << "Enter Email: ";
        getline(cin, email);
        
        ofstream fileStream("3.Instructor.txt", ios::app);
        if (fileStream.is_open()) {
            fileStream << name << "|" << instructorID << "|" << email << endl;
            fileStream.close();
            cout << "Instructor details saved successfully." << endl;
        } else {
            cout << "Error: File could not be opened." << endl;
        }
    }

    bool verifyInstructorID(const string& id) {
        ifstream file("3.Instructor.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string file_name, file_id, file_email, file_expertise, file_salary;
                getline(ss, file_name, '|');
                getline(ss, file_id, '|');
                getline(ss, file_email, '|');
                getline(ss, file_expertise, '|');
                getline(ss, file_salary, '|');
                
                if (file_id == id) {
                    instructorID = file_id;
                    name = file_name;
                    email = file_email;
                    subjectExpertise = file_expertise;
                    file.close();
                    return true;
                }
            }
            file.close();
        }
        return false;
    }

    void viewInstructor() {
        ifstream fileStream("3.Instructor.txt");
        if (!fileStream.is_open()) {
            cout << "Error: File could not be opened." << endl;
            return;
        }
        
        string line;
        cout << " ------------------------------------------ " << endl;
        while (getline(fileStream, line)) {
            cout << line << endl;
        }
        fileStream.close();
    }

    void uploadAssignment() {
        string courseID, title, description;
        cout << "Enter Course ID: ";
        cin >> courseID;
        cout << "Enter Assignment Title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter Assignment Description: ";
        getline(cin, description);
        
        ofstream file("10.Assignments.txt", ios::app);
        if (file.is_open()) {
            file << courseID << "|" << title << "|" << description << "|" << instructorID << endl;
            file.close();
            cout << "Assignment uploaded successfully!" << endl;
        }
    }

    void uploadQuiz() {
        string courseID, title, question, optionA, optionB, optionC, optionD, correctAnswer;
        cout << "Enter Course ID: ";
        cin >> courseID;
        cout << "Enter Quiz Title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter Question: ";
        getline(cin, question);
        cout << "Enter Option A: ";
        getline(cin, optionA);
        cout << "Enter Option B: ";
        getline(cin, optionB);
        cout << "Enter Option C: ";
        getline(cin, optionC);
        cout << "Enter Option D: ";
        getline(cin, optionD);
        cout << "Enter Correct Answer (A/B/C/D): ";
        getline(cin, correctAnswer);
        
        ofstream file("11.Quizzes.txt", ios::app);
        if (file.is_open()) {
            file << courseID << "|" << title << "|" << question << "|" << optionA << "|" << optionB << "|" << optionC << "|" << optionD << "|" << correctAnswer << "|" << instructorID << endl;
            file.close();
            cout << "Quiz uploaded successfully!" << endl;
        }
    }

    void viewCourseDetails() {
        cout << "Enter Course ID to view details: ";
        string courseID;
        cin >> courseID;
        
        cout << "\n=== Course Details ===" << endl;
        
        // Show enrolled students
        ifstream enrollFile("9.StudentEnrollments.txt");
        string line;
        cout << "\nEnrolled Students:" << endl;
        while (getline(enrollFile, line)) {
            stringstream ss(line);
            string studentID, studentName, fileCourseID, courseName, courseType, payment, status, assignmentStatus, quizStatus;
            
            getline(ss, studentID, '|');
            getline(ss, studentName, '|');
            getline(ss, fileCourseID, '|');
            getline(ss, courseName, '|');
            getline(ss, courseType, '|');
            getline(ss, payment, '|');
            getline(ss, status, '|');
            getline(ss, assignmentStatus, '|');
            getline(ss, quizStatus, '|');
            
            if (fileCourseID == courseID) {
                cout << "Student: " << studentName << " (ID: " << studentID << ") - Status: " << status << endl;
            }
        }
        enrollFile.close();
    }

    string getInstructorID() { return instructorID; }

    void displayInstructor(const string& c_id) {
        ifstream fileStream("3.Instructor.txt");
        if (!fileStream.is_open()) {
            cout << "Error: File could not be opened." << endl;
            return;
        }
        
        string line;
        bool found = false;
        
        while (getline(fileStream, line)) {
            stringstream ss(line);
            string file_name, file_id, file_email;
            getline(ss, file_name, '|');
            getline(ss, file_id, '|');
            getline(ss, file_email, '|');
            
            if (file_id == c_id) {
                cout << " ------------------------------------ " << endl;
                cout << "   Instructor Name : " << file_name << endl;
                cout << "   Instructor ID   : " << file_id << endl;
                cout << "   Email           : " << file_email << endl;
                found = true;
                break;
            }
        }
        
        fileStream.close();
        if (!found) {
            cout << "Instructor with ID " << c_id << " not found." << endl;
        }
    }
};

// Forward declarations for menu functions
void studentMenu(User& user, Student& student);
void instructorMenu(User& user, Instructor& instructor);
void adminMenu(User& user, Admin& admin);

int main() {
    User user;
    Admin admin;
    Student student;
    Instructor instructor;
    Course course;
    
    int choice;
    bool running = true;
    cout << "+--------------------------------------+ \n";
    cout << "|   Welcome to Learning Management     |\n";
    cout << "|           System (LMS)               |\n";
    cout << "+--------------------------------------+\n";
    
    while (running) {
        cout << "\n+--------------------------------------+\n";
        cout << "|             Main Menu                |\n";
        cout << "+--------------------------------------+\n";
        user.displayMenu();
        cout << "+--------------------------------------+\n";

        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: { // Register
                cout << "\n=== User Registration ===" << endl;
                
                // First select role
                cout << "Select Role:" << endl;
                cout << "   1 -> Student" << endl;
                cout << "   2 -> Instructor" << endl; 
                cout << "   3 -> Admin" << endl;
                cout << "Enter your choice: ";
                int selectedRole;
                cin >> selectedRole;
                
                // Validate role selection
                if (selectedRole < 1 || selectedRole > 3) {
                    cout << "Invalid role selection!" << endl;
                    break;
                }
                
                // Set role and complete user registration
                user.role = selectedRole;
                
                // Get user details
                string name, email, pass;
                do {
                    cout << "Enter Full Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter Email: ";
                    getline(cin, email);
                    if (user.checkDuplicate(email, name)) {
                        cout << "Please register with a different username or email." << endl;
                    } else {
                        break;
                    }
                } while (true);

                cout << "Enter Password (at least 4 characters): ";
                getline(cin, pass);
                while (pass.size() < 4) {
                    cout << "Password must be at least 4 characters." << endl;
                    cout << "Please enter the password again: ";
                    getline(cin, pass);
                }
                
                // Save to main user file
                ofstream userFile("1.user.txt", ios::app);
                if (userFile.is_open()) {
                    userFile << name << "|" << email << "|" << pass << "|" << selectedRole << endl;
                    userFile.close();
                    cout << "User account created successfully!" << endl;
                } else {
                    cout << "Error: Could not save user account." << endl;
                    break;
                }
                
                // Now set up role-specific profile
                cout << "\nNow setting up your profile..." << endl;
                
                if (selectedRole == 1) { // Student
                    string studentID;
                    cout << "Enter Student ID: ";
                    getline(cin, studentID);
                    
                    ofstream studentFile("2.Student.txt", ios::app);
                    if (studentFile.is_open()) {
                        studentFile << name << "|" << studentID << "|" << email << endl;
                        studentFile.close();
                        cout << "Student profile created successfully!" << endl;
                    }
                } 
                else if (selectedRole == 2) { // Instructor
                    string instructorID, subjectExpertise;
                    int salary;
                    cout << "Enter Instructor ID: ";
                    getline(cin, instructorID);
                    cout << "Enter Subject Expertise: ";
                    getline(cin, subjectExpertise);
                    cout << "Set Salary: ";
                    cin >> salary;
                    
                    ofstream instructorFile("3.Instructor.txt", ios::app);
                    if (instructorFile.is_open()) {
                        instructorFile << name << "|" << instructorID << "|" << email << "|" << subjectExpertise << "|" << salary << endl;
                        instructorFile.close();
                        cout << "Instructor profile created successfully!" << endl;
                    }
                } 
                else if (selectedRole == 3) { // Admin
                    string adminID, department;
                    cout << "Enter Admin ID: ";
                    getline(cin, adminID);
                    cout << "Enter Department: ";
                    getline(cin, department);
                    
                    ofstream adminFile("4.Admin.txt", ios::app);
                    if (adminFile.is_open()) {
                        adminFile << name << "|" << adminID << "|" << email << "|" << department << endl;
                        adminFile.close();
                        cout << "Admin profile created successfully!" << endl;
                    }
                }
                
                cout << "Registration completed! You can now log in." << endl;
                break;
            }
            
            case 2: { // Login
                cout << "\n=== User Login ===" << endl;
                if (user.signIn()) {
                    int userRole = user.role;
                    
                    // Role-based menu system
                    if (userRole == 1) { // Student
                        studentMenu(user, student);
                    }
                    else if (userRole == 2) { // Instructor
                        instructorMenu(user, instructor);
                    }
                    else if (userRole == 3) { // Admin
                        adminMenu(user, admin);
                    }
                    else {
                        cout << "Invalid role detected!" << endl;
                    }
                }
                break;
            }
            
            case 3: { // Exit
                cout << "\nThank you for using Learning Management System!" << endl;
                cout << "Goodbye!" << endl;
                running = false;
                break;
            }
            
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    }
    
    return 0;
}

// Student Menu Function
void studentMenu(User& user, Student& student) {
    int choice;
    bool studentRunning = true;
    
    // Try to load student data based on user email
    string studentID;
    bool studentFound = false;
    
    // Find student ID from email
    ifstream studentFile("2.Student.txt");
    if (studentFile.is_open()) {
        string line;
        while (getline(studentFile, line)) {
            stringstream ss(line);
            string file_name, file_id, file_email;
            getline(ss, file_name, '|');
            getline(ss, file_id, '|');
            getline(ss, file_email, '|');
            
            if (file_email == user.getemail()) {
                studentID = file_id;
                studentFound = true;
                student.verifyStudentID(studentID);
                break;
            }
        }
        studentFile.close();
    }
    
    if (!studentFound) {
        cout << "Student profile not found! Please contact admin." << endl;
        return;
    }
    
    cout << "Welcome, " << user.getName() << "! (Student ID: " << studentID << ")" << endl;
    
    while (studentRunning) {
        cout << "\n+--------------------------------------+ \n";
        cout << "|          Student Dashboard           |\n";
        cout << "+--------------------------------------+\n";
        cout << "| 1 : View Profile                     |\n";
        cout << "| 2 : Edit Profile                     |\n";
        cout << "| 3 : Enroll in Course                 |\n";
        cout << "| 4 : View Enrolled Courses            |\n";
        cout << "| 5 : Attempt Assignment               |\n";
        cout << "| 6 : Attempt Quiz                     |\n";
        cout << "| 7 : Apply for Certificate            |\n";
        cout << "| 8 : Check Certificate Status         |\n";
        cout << "| 9 : View Complete Courses            |\n";
        cout << "| 10 : Logout                          |\n";
        cout << "+--------------------------------------+\n";

        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                user.viewProfile();
                break;
            case 2:
                user.editProfile();
                break;
            case 3:
                student.enrollInCourse();
                break;
            case 4:
                student.viewMyCourses();
                break;
            case 5:
                student.attemptAssignment();
                break;
            case 6:
                student.attemptQuiz();
                break;
            case 7:
                student.applyCertificate();
                break;
            case 8:
                student.checkCertificateStatus();
                break;
            case 9:
                student.viewCompletedCourses();
                break;
            case 10:
                cout << "Logging out from Student Dashboard..." << endl;
                studentRunning = false;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    }
}

// Instructor Menu Function
void instructorMenu(User& user, Instructor& instructor) {
    int choice;
    bool instructorRunning = true;
    
    // Try to load instructor data based on user email
    string instructorID;
    bool instructorFound = false;
    
    // Find instructor ID from email
    ifstream instructorFile("3.Instructor.txt");
    if (instructorFile.is_open()) {
        string line;
        while (getline(instructorFile, line)) {
            stringstream ss(line);
            string file_name, file_id, file_email, file_expertise, file_salary;
            getline(ss, file_name, '|');
            getline(ss, file_id, '|');
            getline(ss, file_email, '|');
            getline(ss, file_expertise, '|');
            getline(ss, file_salary, '|');
            
            if (file_email == user.getemail()) {
                instructorID = file_id;
                instructorFound = true;
                instructor.verifyInstructorID(instructorID);
                break;
            }
        }
        instructorFile.close();
    }
    
    if (!instructorFound) {
        cout << "Instructor profile not found! Please contact admin." << endl;
        return;
    }
    
    cout << "Welcome, " << user.getName() << "! (Instructor ID: " << instructorID << ")" << endl;
    
    while (instructorRunning) {
        cout << "\n+--------------------------------------+ \n";
        cout << "|         Instructor Dashboard         |\n";
        cout << "+--------------------------------------+\n";
        cout << "| 1 : View Profile                     |\n";
        cout << "| 2 : Edit Profile                     |\n";
        cout << "| 3 : Upload Assignment                |\n";
        cout << "| 4 : Upload Quiz                      |\n";
        cout << "| 5 : View Course Details              |\n";
        cout << "| 6 : View All Instructors             |\n";
        cout << "| 7 : Logout                           |\n";
        cout << "+--------------------------------------+\n";

        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                user.viewProfile();
                break;
            case 2:
                user.editProfile();
                break;
            case 3:
                instructor.uploadAssignment();
                break;
            case 4:
                instructor.uploadQuiz();
                break;
            case 5:
                instructor.viewCourseDetails();
                break;
            case 6:
                instructor.viewInstructor();
                break;
            case 7:
                cout << "Logging out from Instructor Dashboard..." << endl;
                instructorRunning = false;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    }
}

// Admin Menu Function
void adminMenu(User& user, Admin& admin) {
    int choice;
    bool adminRunning = true;
    
    // Try to load admin data based on user email
    string adminID;
    bool adminFound = false;
    
    // Find admin ID from email
    ifstream adminFile("4.Admin.txt");
    if (adminFile.is_open()) {
        string line;
        while (getline(adminFile, line)) {
            stringstream ss(line);
            string file_name, file_id, file_email, file_dept;
            getline(ss, file_name, '|');
            getline(ss, file_id, '|');
            getline(ss, file_email, '|');
            getline(ss, file_dept, '|');
            
            if (file_email == user.getemail()) {
                adminID = file_id;
                adminFound = true;
                admin.verifyAdminID(adminID);
                break;
            }
        }
        adminFile.close();
    }
    
    if (!adminFound) {
        cout << "Admin profile not found! Please contact system administrator." << endl;
        return;
    }
    
    cout << "Welcome, " << user.getName() << "! (Admin ID: " << adminID << ")" << endl;
    
    while (adminRunning) {
        cout << "\n+--------------------------------------+ \n";
        cout << "|           Admin Dashboard            |\n";
        cout << "+--------------------------------------+\n";
        cout << "| 1 : View Profile                     |\n";
        cout << "| 2 : Edit Profile                     |\n";
        cout << "| 3 : Add/Manage Courses               |\n";
        cout << "| 4 : View All Courses                 |\n";
        cout << "| 5 : View All Students                |\n";
        cout << "| 6 : View All Instructors             |\n";
        cout << "| 7 : View Enrollment Reports          |\n";
        cout << "| 8 : Add New Admin                    |\n";
        cout << "| 9 : Logout                           |\n";
        cout << "+--------------------------------------+\n";

        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                user.viewProfile();
                break;
            case 2:
                user.editProfile();
                break;
            case 3:
                admin.course();
                break;
            case 4:
                admin.viewCourses();
                break;
            case 5:
                admin.viewAllStudents();
                break;
            case 6:
                admin.viewAllInstructors();
                break;
            case 7:
                admin.viewEnrollmentReports();
                break;
            case 8:
                admin.info();
                break;
            case 9:
                cout << "Logging out from Admin Dashboard..." << endl;
                adminRunning = false;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    }
}
                