// Name: Phubeth Mettaprasert
// File: PatientPriorityQueue.h
// Date: May 27, 2022
// The header file and the implementation of the Patient class. Contains
// the framework to create Patient objects to be inserted into the
// PatientPriorityQueue class.
//Purpose: Creates a Patient object with the functionalities to compare with
//         other Patient objects. Contains getter and to_string methods to be
//         used in the PatientPriorityQueue.

#ifndef P3_PATIENT_H
#define P3_PATIENT_H

#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

class Patient {
public:
    Patient(string, int, int);
    // Constructor that initializes the Patient class.
    // preconditions: none
    // postconditions: Takes in the name, takes in the priorityOrder and
    //                 takes in the arrivalOrder to create a Patient object.

    string to_string() const;
    // A to_string method that returns the string of the information of the
    // Patient including name, priority code and arrival number.
    // preconditions: none
    // postconditions: none

    bool operator<(const Patient &);
    // An overloaded operator for the less than that allows for comparisons
    // between Patient objects.
    // preconditions: Requires another Patient object to be created as used
    //                as the argument for comparison.
    // postconditions: none


    bool operator>(const Patient &);
    // An overloaded operator for the less than that allows for comparisons
    // between Patient objects.
    // preconditions: Requires another Patient object to be created as used
    //                as the argument for comparison.
    // postconditions: none

    Patient &operator=(const Patient &);
    // An overloaded operator for the = that copies the Patient object
    // inputted and returns reference to the current Patient object
    // preconditions: Requires another Patient object to be created as used
    //                as the argument for copying.
    // postconditions: none

    string getPatientName() const;
    // A getter method that returns the name of the patient. This is needed
    // as to not conflict with the format of the to_string for the class.
    // preconditions: none
    // postconditions: none

    string getPriorityInString() const;
    // Returns the string of the priority code from an int that was stored
    // when creating the Patient object.
    // preconditions: none
    // postconditions: none



private:
    string name; //Store the name of the patient
    int priorityCode; //Store the priority code of the patient
    int arrivalOrder; //Store the arrival order of the patient
};

Patient::Patient(string name, int priorityCode, int arrivalOrder) {

    //Constructor that sets the private attributes by the arguments put in.
    this->name = name;
    this->priorityCode = priorityCode;
    this->arrivalOrder = arrivalOrder;
}


string Patient::to_string() const {

    //Create the stringstream object.
    stringstream ss;

    //Store the string in the string stream object. Reason for +1 was to
    // start the arrival order at 1 rather than at zero.
    ss << setw(6) << (arrivalOrder + 1) << "          " << setw(15) << left <<
       getPriorityInString() << left << name << "\n";
    return ss.str();

}

Patient &Patient::operator=(const Patient &otherPatient) {

    //Copies the attributes of the other Patient object to be copied
    name = otherPatient.name;
    priorityCode = otherPatient.priorityCode;
    arrivalOrder = otherPatient.arrivalOrder;
    return *this;
}

bool Patient::operator<(const Patient &right) {

    //Operator overloading function for the less than equal sign
    if (priorityCode < right.priorityCode) {
        return true;
    } else if (priorityCode == right.priorityCode) {

        //Use arrivalOrder in order to tiebreak
        if (arrivalOrder < right.arrivalOrder) {
            return true;
        }
    }

    //Catch all if none of the condition above matches the above condition.
    return false;

}

bool Patient::operator>(const Patient &right) {

    //Operator overloading function for the less than equal sign
    if (priorityCode > right.priorityCode) {
        return true;
    } else if (priorityCode == right.priorityCode) {

        //Use arrivalOrder in order to tiebreak
        if (arrivalOrder > right.arrivalOrder) {
            return true;
        }
    }

    //Catch all if none of the condition above matches the above condition.
    return false;

}


string Patient::getPatientName() const {

    //Just returns the name of the Patient object since to_string displays
    // another string.
    return name;
}

string Patient::getPriorityInString() const {

    //Returns the string of the priorityCode. Used to switch from the number
    // format to display the string format.
    switch (this->priorityCode) {
        case 1:
            return "immediate";
        case 2:
            return "emergency";
        case 3:
            return "urgent";
        case 4:
            return "minimal";
        default:
            return "";

    }
}

#endif //P3_PATIENT_H
