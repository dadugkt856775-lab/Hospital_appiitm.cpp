#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Patient {
    int id;
    string name;
    int age;
    string disease;
    string appointmentTime;
};

int main() {
    vector<Patient> patients;
    map<int, Patient> patientRecords;
    queue<int> waitingQueue;

    int choice;

    do {
        cout << "\n===== HOSPITAL APPOINTMENT SYSTEM =====\n";
        cout << "1. Register Patient\n";
        cout << "2. Schedule Appointment\n";
        cout << "3. Display All Patients\n";
        cout << "4. Search Patient\n";
        cout << "5. Serve Next Patient\n";
        cout << "6. Display Waiting Queue\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            Patient p;

            cout << "Enter Patient ID: ";
            cin >> p.id;

            if (patientRecords.count(p.id)) {
                cout << "Patient ID already exists!\n";
                continue;
            }

            cin.ignore();

            cout << "Enter Patient Name: ";
            getline(cin, p.name);

            cout << "Enter Age: ";
            cin >> p.age;

            cin.ignore();
            cout << "Enter Disease: ";
            getline(cin, p.disease);

            p.appointmentTime = "Not Scheduled";

            patients.push_back(p);
            patientRecords[p.id] = p;

            cout << "Patient registered successfully!\n";
        }
        else if (choice == 2) {
            int id;

            cout << "Enter Patient ID: ";
            cin >> id;

            auto it = patientRecords.find(id);

            if (it == patientRecords.end()) {
                cout << "Patient not found!\n";
                continue;
            }

            if (it->second.appointmentTime != "Not Scheduled") {
                cout << "Appointment already scheduled!\n";
                continue;
            }

            string time;
            cout << "Enter Appointment Time (e.g. 10:30 AM): ";
            cin.ignore();
            getline(cin, time);

            it->second.appointmentTime = time;

            for (Patient &p : patients) {
                if (p.id == id) {
                    p.appointmentTime = time;
                    break;
                }
            }

            waitingQueue.push(id);

            cout << "Appointment scheduled successfully!\n";
        }
        else if (choice == 3) {
            if (patients.empty()) {
                cout << "No patient records available.\n";
            }

            for (const Patient &p : patients) {
                cout << "\nPatient ID: " << p.id
                     << "\nName: " << p.name
                     << "\nAge: " << p.age
                     << "\nDisease: " << p.disease
                     << "\nAppointment: " << p.appointmentTime
                     << "\n";
            }
        }
        else if (choice == 4) {
            int id;

            cout << "Enter Patient ID to search: ";
            cin >> id;

            auto it = patientRecords.find(id);

            if (it != patientRecords.end()) {
                const Patient &p = it->second;

                cout << "\nPatient Found!\n";
                cout << "Name: " << p.name << "\n";
                cout << "Age: " << p.age << "\n";
                cout << "Disease: " << p.disease << "\n";
                cout << "Appointment: "
                     << p.appointmentTime << "\n";
            }
            else {
                cout << "Patient not found!\n";
            }
        }
        else if (choice == 5) {
            if (waitingQueue.empty()) {
                cout << "No patients waiting.\n";
            }
            else {
                int id = waitingQueue.front();
                waitingQueue.pop();

                cout << "Now serving Patient ID: " << id
                     << "\nPatient Name: "
                     << patientRecords[id].name << "\n";
            }
        }
        else if (choice == 6) {
            if (waitingQueue.empty()) {
                cout << "Waiting queue is empty.\n";
            }
            else {
                queue<int> temp = waitingQueue;

                cout << "\n===== WAITING PATIENTS =====\n";

                while (!temp.empty()) {
                    int id = temp.front();
                    temp.pop();

                    cout << "ID: " << id
                         << " | Name: "
                         << patientRecords[id].name << "\n";
                }
            }
        }
        else if (choice == 7) {
            cout << "Exiting Hospital Appointment System...\n";
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 7);

    return 0;
}
