#include <iostream>
#include <string>
using namespace std;

class Skill {
    string skillID;
    string skillName;
    string skillDescription;

public:
    Skill() : skillID(""), skillName(""), skillDescription("") {}  // Default constructor
    Skill(string id, string name, string desc) : skillID(id), skillName(name), skillDescription(desc) {}  // Parameterized constructor

    void displaySkillDetails() {
        cout << "Skill ID: " << skillID << " | Name: " << skillName << " | Description: " << skillDescription << endl;
    }

    void updateSkillDescription(string newDesc) {
        skillDescription = newDesc;
    }

    string getSkillName() { return skillName; }
};

class Sport {
    string sportID;
    string sportName;
    string sportDescription;
    Skill **requiredSkills;  // Pointer to an array of Skill pointers
    int skillCount;

public:
    Sport() : sportID(""), sportName(""), sportDescription(""), requiredSkills(nullptr), skillCount(0) {}  // Default constructor
    Sport(string id, string name, string desc, Skill **skills, int count) : sportID(id), sportName(name), sportDescription(desc), skillCount(count) {       // Parameterized constructor
        requiredSkills = new Skill *[skillCount];
        for (int i = 0; i < skillCount; i++) {
            requiredSkills[i] = skills[i];
        }
    }

    void addSkill(Skill *skill) {
        Skill **temp = new Skill *[skillCount + 1];
        for (int i = 0; i < skillCount; i++) {
            temp[i] = requiredSkills[i];
        }
        temp[skillCount] = skill;
        delete[] requiredSkills;
        requiredSkills = temp;
        skillCount++;
        cout << "Skill \"" << skill->getSkillName() << "\" added to sport \"" << sportName << "\"." << endl;
    }

    void removeSkill(Skill *skill) {
        if (skillCount == 0) {
            cout << "No skills to remove." << endl;
            return;
        }

        int index = -1;
        for (int i = 0; i < skillCount; i++) {
            if (requiredSkills[i]->getSkillName() == skill->getSkillName()) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Skill not found." << endl;
            return;
        }

        Skill **temp = new Skill *[skillCount - 1];
        for (int i = 0, j = 0; i < skillCount; i++) {
            if (i != index) {
                temp[j++] = requiredSkills[i];
            }
        }

        delete[] requiredSkills;
        requiredSkills = temp;
        skillCount--;
        cout << "Skill \"" << skill->getSkillName() << "\" removed from sport \"" << sportName << "\"." << endl;
    }

    void displaySportDetails() {
        cout << "Sport ID: " << sportID << " | Name: " << sportName << " | Description: " << sportDescription << endl;
        cout << "Required Skills: " << endl;
        for (int i = 0; i < skillCount; i++) {
            requiredSkills[i]->displaySkillDetails();
        }
    }

    ~Sport() {
        delete[] requiredSkills;
    }
};

class Mentor {
    string mentorID;
    string mentorName;
    Sport **sportsExpertise;  // Pointer to an array of Sport pointers
    int expertiseCount;
    int maxLearners;
    int currentLearners;
    string *assignedLearners;  // Array of learner names

public:
    Mentor(string id, string name, Sport **expertise, int expertiseCount, int max) // Parameterized constructor
        : mentorID(id), mentorName(name), expertiseCount(expertiseCount), maxLearners(max), currentLearners(0) {
        sportsExpertise = new Sport *[expertiseCount];
        for (int i = 0; i < expertiseCount; i++) {
            sportsExpertise[i] = expertise[i];
        }
        assignedLearners = new string[maxLearners];
    }

    bool assignLearner(string learnerName) {
        if (currentLearners >= maxLearners) {
            cout << "Mentor \"" << mentorName << "\" has reached maximum capacity." << endl;
            return false;
        }

        assignedLearners[currentLearners++] = learnerName;
        cout << "Learner \"" << learnerName << "\" assigned to mentor \"" << mentorName << "\"." << endl;
        return true;
    }

    void removeLearner(string learnerName) {
        int index = -1;
        for (int i = 0; i < currentLearners; i++) {
            if (assignedLearners[i] == learnerName) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Learner \"" << learnerName << "\" not found." << endl;
            return;
        }

        for (int i = index; i < currentLearners - 1; i++) {
            assignedLearners[i] = assignedLearners[i + 1];
        }

        currentLearners--;
        cout << "Learner \"" << learnerName << "\" removed from mentor \"" << mentorName << "\"." << endl;
    }

    void viewLearners() {
        cout << "Learners assigned to mentor \"" << mentorName << "\":" << endl;
        for (int i = 0; i < currentLearners; i++) {
            cout << "- " << assignedLearners[i] << endl;
        }
    }

    void provideGuidance() {
        cout << "Mentor \"" << mentorName << "\" says: Practice hard and stay focused!" << endl;
    }

    ~Mentor() {
        delete[] sportsExpertise;
        delete[] assignedLearners;
    }
};

class Student {
    string studentID;
    string studentName;
    int studentAge;
    Sport **sportsInterests;  // Pointer to an array of Sport pointers
    int interestCount;
    Mentor *assignedMentor;

public:
    Student(string id, string name, int age, Sport **interests, int count) 
        : studentID(id), studentName(name), studentAge(age), interestCount(count), assignedMentor(nullptr) {
        sportsInterests = new Sport *[interestCount];
        for (int i = 0; i < interestCount; i++) {
            sportsInterests[i] = interests[i];
        }
    }

    void registerForMentorship(Mentor *mentor) {
        if (mentor->assignLearner(studentName)) {
            assignedMentor = mentor;
        }
    }

    void viewMentorDetails() {
        if (assignedMentor) {
            cout << "Mentor assigned to student \"" << studentName << "\": " << endl;
            assignedMentor->provideGuidance(); 
        } else {
            cout << "No mentor assigned." << endl;
        }
    }

    void updateSportsInterest(Sport *sport) {
        Sport **temp = new Sport *[interestCount + 1];
        for (int i = 0; i < interestCount; i++) {
            temp[i] = sportsInterests[i];
        }
        temp[interestCount] = sport;
        delete[] sportsInterests;
        sportsInterests = temp;
        interestCount++;
        cout << "Sport added to student \"" << studentName << "\"'s interests: " << endl;
        sport->displaySportDetails();
    }

    ~Student() {
        delete[] sportsInterests;
    }
};

int main() {
    Skill skill1("S001", "Running", "Improve speed ");
    Skill skill2("S002", "Serving", "Master the tennis serve");

    Skill *sport1Skills[] = {&skill1};
    Sport sport1("SP001", "Track and Field", "Running events", sport1Skills, 1);

    Skill *sport2Skills[] = {&skill2};
    Sport sport2("SP002", "Tennis", "Racket sport", sport2Skills, 1);

    Sport *mentorExpertise[] = {&sport1, &sport2};
    Mentor mentor("M001", "Ali", mentorExpertise, 2, 3);

    Sport *studentInterests[] = {&sport1};
    Student student("ST001", "Saad", 20, studentInterests, 1);

    int choice;
    do {
        cout << "\n===== MENU =====" << endl;
        cout << "1. Register Student for Mentorship" << endl;
        cout << "2. View Mentor Details" << endl;
        cout << "3. Update Student's Sports Interest" << endl;
        cout << "4. View Assigned Learners for Mentor" << endl;
        cout << "5. Provide Guidance from Mentor" << endl;
        cout << "6. Remove Student from Mentorship" << endl;
        cout << "7. Display Sport Details" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                student.registerForMentorship(&mentor);
                break;
            }
            case 2: {
                student.viewMentorDetails();
                break;
            }
            case 3: {
                cout << "Adding Tennis to student's interests..." << endl;
                student.updateSportsInterest(&sport2);
                break;
            }
            case 4: {
                mentor.viewLearners();
                break;
            }
            case 5: {
                mentor.provideGuidance();
                break;
            }
            case 6: {
                mentor.removeLearner("Saad");
                break;
            }
            case 7: {
                cout << "Displaying details for Track and Field:" << endl;
                sport1.displaySportDetails();
                cout << "\nDisplaying details for Tennis:" << endl;
                sport2.displaySportDetails();
                break;
            }
            case 8: {
                cout << "Exiting program" << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    } while (choice != 8);

    return 0;
}