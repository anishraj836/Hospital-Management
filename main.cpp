#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Base class: Person
class Person {
protected:
    std::string name;
    int age;
public:
    Person(const std::string& n, int a) : name(n), age(a) {}
    virtual void displayInfo() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
    virtual ~Person() = default;
    std::string getName() const { return name; }
};

// Patient class
class Patient : public Person {
    std::string disease;
    int patientId;
public:
    static int patientCount;
    Patient(const std::string& n, int a, const std::string& d, int id)
        : Person(n, a), disease(d), patientId(id) {
        ++patientCount;
    }
    int getId() const { return patientId; }
    void displayInfo() const override {
        std::cout << "Patient[ID: " << patientId << "] - ";
        Person::displayInfo();
        std::cout << "Disease: " << disease << std::endl;
    }
};
int Patient::patientCount = 0;

// Doctor class
class Doctor : public Person {
    std::string specialization;
    int doctorId;
public:
    static int doctorCount;
    Doctor(const std::string& n, int a, const std::string& s, int id)
        : Person(n, a), specialization(s), doctorId(id) {
        ++doctorCount;
    }
    int getId() const { return doctorId; }
    void displayInfo() const override {
        std::cout << "Doctor[ID: " << doctorId << "] - ";
        Person::displayInfo();
        std::cout << "Specialization: " << specialization << std::endl;
    }
};
int Doctor::doctorCount = 0;

// Consultation class
class Consultation {
    const Patient* patient;
    const Doctor* doctor;
    std::string date; // YYYY-MM-DD
    std::string notes;
public:
    Consultation(const Patient* p, const Doctor* d, const std::string& dt, const std::string& n)
        : patient(p), doctor(d), date(dt), notes(n) {}
    void display() const {
        std::cout << "Consultation - Date: " << date << ", Notes: " << notes << std::endl;
        std::cout << "  Patient Info: ";
        if (patient) patient->displayInfo();
        else std::cout << "Unknown patient\n";
        std::cout << "  Doctor Info: ";
        if (doctor) doctor->displayInfo();
        else std::cout << "Unknown doctor\n";
    }
    std::string getDate() const { return date; }
    int getPatientId() const { return patient ? patient->getId() : -1; }
    int getDoctorId() const { return doctor ? doctor->getId() : -1; }
};

// Hospital class: manages patients, doctors, and consultations
class Hospital {
    std::vector<Patient> patients;
    std::vector<Doctor> doctors;
    std::vector<Consultation> consultations;
    int nextPatientId = 1;
    int nextDoctorId = 1;
public:
    void addPatient(const std::string& name, int age, const std::string& disease) {
        patients.emplace_back(name, age, disease, nextPatientId++);
    }
    void addDoctor(const std::string& name, int age, const std::string& specialization) {
        doctors.emplace_back(name, age, specialization, nextDoctorId++);
    }
    const std::vector<Patient>& getPatients() const { return patients; }
    const std::vector<Doctor>& getDoctors() const { return doctors; }
    void addConsultation(const Consultation& c) {
        consultations.push_back(c);
    }
    void displayAll() const {
        std::cout << "\n--- Patients (Total: " << Patient::patientCount << ") ---\n";
        for (const auto& p : patients) p.displayInfo();
        std::cout << "\n--- Doctors (Total: " << Doctor::doctorCount << ") ---\n";
        for (const auto& d : doctors) d.displayInfo();
    }
    void displayConsultations() const {
        std::cout << "\n--- Consultations ---\n";
        if (consultations.empty()) {
            std::cout << "No consultations recorded.\n";
        } else {
            for (const auto& c : consultations) c.display();
        }
    }
    // Display consultations for a patient by ID
    void displayPatientConsultations(int patientId, const std::string& currentDate) const {
        std::vector<const Consultation*> upcoming, past;
        for (const auto& c : consultations) {
            if (c.getPatientId() == patientId) {
                if (c.getDate() >= currentDate) upcoming.push_back(&c);
                else past.push_back(&c);
            }
        }
        std::cout << "\nUpcoming Consultations:\n";
        if (upcoming.empty()) std::cout << "None\n";
        else for (const auto* c : upcoming) c->display();
        std::cout << "\nPast Consultations:\n";
        if (past.empty()) std::cout << "None\n";
        else for (const auto* c : past) c->display();
    }
    // Display consultations for a doctor by ID
    void displayDoctorConsultations(int doctorId, const std::string& currentDate) const {
        std::vector<const Consultation*> upcoming, past;
        for (const auto& c : consultations) {
            if (c.getDoctorId() == doctorId) {
                if (c.getDate() >= currentDate) upcoming.push_back(&c);
                else past.push_back(&c);
            }
        }
        std::cout << "\nUpcoming Consultations:\n";
        if (upcoming.empty()) std::cout << "None\n";
        else for (const auto* c : upcoming) c->display();
        std::cout << "\nPast Consultations:\n";
        if (past.empty()) std::cout << "None\n";
        else for (const auto* c : past) c->display();
    }
    // Display consultations for a patient on a specific date
    void displayPatientConsultationsOnDate(int patientId, const std::string& date) const {
        bool found = false;
        for (const auto& c : consultations) {
            if (c.getPatientId() == patientId && c.getDate() == date) {
                c.display();
                found = true;
            }
        }
        if (!found) std::cout << "No consultations found on this date.\n";
    }
    // Display consultations for a doctor on a specific date
    void displayDoctorConsultationsOnDate(int doctorId, const std::string& date) const {
        bool found = false;
        for (const auto& c : consultations) {
            if (c.getDoctorId() == doctorId && c.getDate() == date) {
                c.display();
                found = true;
            }
        }
        if (!found) std::cout << "No consultations found on this date.\n";
    }
    const Patient* findPatientById(int id) const {
        for (const auto& p : patients) if (p.getId() == id) return &p;
        return nullptr;
    }
    const Doctor* findDoctorById(int id) const {
        for (const auto& d : doctors) if (d.getId() == id) return &d;
        return nullptr;
    }
    void showConsultationsByDate(const std::string& date) const {
        bool found = false;
        std::cout << "\nConsultations on " << date << ":\n";
        for (const auto& c : consultations) {
            if (c.getDate() == date) {
                c.display();
                found = true;
            }
        }
        if (!found) std::cout << "No consultations found on this date.\n";
    }
    void findPatientsByName(const std::string& name) const {
        bool found = false;
        for (const auto& p : patients) {
            if (p.getName() == name) {
                p.displayInfo();
                found = true;
            }
        }
        if (!found) std::cout << "No patient found with the name '" << name << "'.\n";
    }
    void findDoctorsByName(const std::string& name) const {
        bool found = false;
        for (const auto& d : doctors) {
            if (d.getName() == name) {
                d.displayInfo();
                found = true;
            }
        }
        if (!found) std::cout << "No doctor found with the name '" << name << "'.\n";
    }
};

// Helper function for input validation
int getValidatedChoice(int min, int max) {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail() || choice < min || choice > max) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
        } else {
            std::cin.ignore(10000, '\n');
            return choice;
        }
    }
}

void patientMenu(const Hospital& h, int patientId) {
    std::string today;
    std::cout << "Enter today's date (YYYY-MM-DD): ";
    getline(std::cin, today);
    h.displayPatientConsultations(patientId, today);
    std::cout << "\nWould you like to see consultations on a specific date? (Y/N): ";
    char c; std::cin >> c; std::cin.ignore();
    if (c == 'Y' || c == 'y') {
        std::string date;
        std::cout << "Enter date (YYYY-MM-DD): ";
        getline(std::cin, date);
        h.displayPatientConsultationsOnDate(patientId, date);
    }
}

void doctorMenu(const Hospital& h, int doctorId) {
    std::string today;
    std::cout << "Enter today's date (YYYY-MM-DD): ";
    getline(std::cin, today);
    h.displayDoctorConsultations(doctorId, today);
    std::cout << "\nWould you like to see consultations on a specific date? (Y/N): ";
    char c; std::cin >> c; std::cin.ignore();
    if (c == 'Y' || c == 'y') {
        std::string date;
        std::cout << "Enter date (YYYY-MM-DD): ";
        getline(std::cin, date);
        h.displayDoctorConsultationsOnDate(doctorId, date);
    }
}

int main() {
    Hospital h;
    while (true) {
        std::cout << "\n--- Welcome to Hospital Management System ---\n";
        std::cout << "1. Patient\n2. Doctor\n3. Admin/Other\n4. Exit\nEnter your role: ";
        int role = getValidatedChoice(1, 4);
        if (role == 4) {
            std::cout << "Exiting...\n";
            break;
        }
        if (role == 1) {
            std::cout << "Are you registered? (Y/N): ";
            char reg; std::cin >> reg; std::cin.ignore();
            if (reg == 'N' || reg == 'n') {
                std::cout << "Please contact admin to register.\n";
                continue;
            }
            std::cout << "Enter your ID: ";
            int id = getValidatedChoice(1, 1000000);
            if (!h.findPatientById(id)) {
                std::cout << "No patient found with this ID.\n";
                continue;
            }
            patientMenu(h, id);
        } else if (role == 2) {
            std::string password;
            std::cout << "Enter doctor password: ";
            getline(std::cin, password);
            if (password != "doctor") {
                std::cout << "Incorrect password. Access denied.\n";
                continue;
            }
            std::cout << "Are you registered? (Y/N): ";
            char reg; std::cin >> reg; std::cin.ignore();
            if (reg == 'N' || reg == 'n') {
                std::cout << "Please contact admin to register.\n";
                continue;
            }
            std::cout << "Enter your ID: ";
            int id = getValidatedChoice(1, 1000000);
            if (!h.findDoctorById(id)) {
                std::cout << "No doctor found with this ID.\n";
                continue;
            }
            doctorMenu(h, id);
        } else if (role == 3) {
            std::string password;
            std::cout << "Enter admin password: ";
            getline(std::cin, password);
            if (password != "admin") {
                std::cout << "Incorrect password. Access denied.\n";
                continue;
            }
            int choice;
            do {
                std::cout << "\n--- Admin Menu ---\n";
                std::cout << "1. Add Patient\n";
                std::cout << "2. Add Doctor\n";
                std::cout << "3. Display All\n";
                std::cout << "4. Add Consultation\n";
                std::cout << "5. Show Consultations\n";
                std::cout << "6. Show Consultations by Date\n";
                std::cout << "7. Find Patient by Name\n";
                std::cout << "8. Find Doctor by Name\n";
                std::cout << "9. Back\n";
                std::cout << "Enter your choice: ";
                choice = getValidatedChoice(1, 9);
                if (choice == 1) {
                    std::string name, disease;
                    int age;
                    std::cout << "Enter patient name: ";
                    getline(std::cin, name);
                    std::cout << "Enter patient age: ";
                    age = getValidatedChoice(0, 150);
                    std::cout << "Enter disease: ";
                    getline(std::cin, disease);
                    h.addPatient(name, age, disease);
                    std::cout << "Patient added!\n";
                } else if (choice == 2) {
                    std::string name, specialization;
                    int age;
                    std::cout << "Enter doctor name: ";
                    getline(std::cin, name);
                    std::cout << "Enter doctor age: ";
                    age = getValidatedChoice(0, 150);
                    std::cout << "Enter specialization: ";
                    getline(std::cin, specialization);
                    h.addDoctor(name, age, specialization);
                    std::cout << "Doctor added!\n";
                } else if (choice == 3) {
                    h.displayAll();
                } else if (choice == 4) {
                    const auto& patients = h.getPatients();
                    const auto& doctors = h.getDoctors();
                    if (patients.empty() || doctors.empty()) {
                        std::cout << "Add at least one patient and one doctor first!\n";
                        continue;
                    }
                    std::cout << "Select patient:\n";
                    for (size_t i = 0; i < patients.size(); ++i) {
                        std::cout << i+1 << ". ";
                        patients[i].displayInfo();
                    }
                    std::cout << "Enter patient number: ";
                    int pidx = getValidatedChoice(1, patients.size()) - 1;
                    std::cout << "Select doctor:\n";
                    for (size_t i = 0; i < doctors.size(); ++i) {
                        std::cout << i+1 << ". ";
                        doctors[i].displayInfo();
                    }
                    std::cout << "Enter doctor number: ";
                    int didx = getValidatedChoice(1, doctors.size()) - 1;
                    std::string date, notes;
                    std::cout << "Enter date (YYYY-MM-DD): ";
                    getline(std::cin, date);
                    std::cout << "Enter notes: ";
                    getline(std::cin, notes);
                    h.addConsultation(Consultation(&patients[pidx], &doctors[didx], date, notes));
                    std::cout << "Consultation added!\n";
                } else if (choice == 5) {
                    h.displayConsultations();
                } else if (choice == 6) {
                    std::string date;
                    std::cout << "Enter date (YYYY-MM-DD): ";
                    getline(std::cin, date);
                    h.showConsultationsByDate(date);
                } else if (choice == 7) {
                    std::string name;
                    std::cout << "Enter patient name to search: ";
                    getline(std::cin, name);
                    h.findPatientsByName(name);
                } else if (choice == 8) {
                    std::string name;
                    std::cout << "Enter doctor name to search: ";
                    getline(std::cin, name);
                    h.findDoctorsByName(name);
                }
            } while (choice != 9);
        }
    }
    return 0;
}