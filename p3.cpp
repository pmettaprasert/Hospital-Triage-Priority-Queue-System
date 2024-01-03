// Phubeth Mettaprasert
// File: p3.cpp
// Date: May 29th, 2022
// Purpose: This program is designed to create a priority queue using Patient
//          objects implemented using heap. The priority queue is able to sort
//          the different Patient objects based on their priority and
//          arrival number.
// Input: Input commands onto the console in order use different methods in
//        order to modify and display the priority queue. A file of commands
//        can also be loaded onto the program.
// Process: Users will input commands to add, remove and display the priority
//          queue of Patients.
// Output: Each time a command is issued, users should see how it has
//         modified the priority queue and can see the priority queue
//         displayed as well.

#include "PatientPriorityQueue.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;


void welcome();
// Prints welcome message.
// IN: none
// MODIFY: none.
// OUT: Displays welcome message

void goodbye();
// Prints goodbye message.
// IN: none
// MODIFY: none.
// OUT: Displays goodbye message

void help();
// Displays the help menu
// IN: none
// MODIFY: none.
// OUT: Displays the help menu

bool processLine(string, PatientPriorityQueue &);
// Process the line entered from the user or read from the file.
// IN: Takes in the user inputted command and the priority queue object.
// MODIFY: Once the command is inputted, will call other functions. Depending
//         on the command, can modify the priority queue object such
//         as adding or removing Patient objects in the queue.
// OUT: Can display error messages if the commands are read incorrectly

void addPatientCmd(string, PatientPriorityQueue &);
// After reading the command add, adds the patient to the waiting room.
// IN: Takes in the string sans command
// MODIFY: Depending on the command, can modify priority queue object such
//         as adding or removing Patient objects in the queue.
// OUT: Can display error messages if the commands are read incorrectly

void peekNextCmd(PatientPriorityQueue &);
// Displays the next patient in the waiting room that will be called.
// IN: Takes in priority queue
// MODIFY: none.
// OUT: Displays who is next in the queue.

void removePatientCmd(PatientPriorityQueue &);
// Removes a patient from the waiting room and displays the name on the screen.
// IN: Takes in priority queue
// MODIFY: Removes the root of the PriorityQueue
// OUT: Displays which patient object was removed

void showPatientListCmd(PatientPriorityQueue &);
// Displays the list of patients in the waiting room.
// IN: Takes in priority queue
// MODIFY: none
// OUT: Displays which Patients are currently in the PriorityQueue.

void execCommandsFromFileCmd(string, PatientPriorityQueue &);
// Reads a text file with each command on a separate line and executes the
// lines as if they were typed into the command prompt.
// IN: Takes in priority queue and the string that is the filename to be loaded.
// MODIFY: Can execute any available commands based on what is in the file.
// OUT: Display what is done with the PriorityQueue.

string delimitBySpace(string &);
// Delimits (by space) the string from user or file input.
// IN: Takes in the string which is the commands given.
// MODIFY: The string itself is modified to be readable in chunks so that
//         commands can be executed.
// OUT: Returns the modified string.

int validatePriority(string);
// Validates the priority code string so that it is acceptable.
// IN: Takes in the priority code string.
// MODIFY: none
// OUT: Returns the Priority code number.

string removeLeadingTrailingSpaces(string);
// A method to remove the leading and the trailing spaces from a string.
// IN: Takes in the command strings.
// MODIFY: The leading/trailign spaces should be removed from the strings.
// OUT: Returns the modified string.


int main() {
    // declare variables
    string line;

    // welcome message
    welcome();

    // process commands
    PatientPriorityQueue priQueue;
    do {
        cout << "\ntriage> ";
        getline(cin, line);
    } while (processLine(line, priQueue));

    // goodbye message
    goodbye();
}

bool processLine(string line, PatientPriorityQueue &priQueue) {
    // get command
    string cmd = delimitBySpace(line);
    if (cmd.length() == 0) {
        cout << "Error: no command given.";
        return false;
    }

    // process user input
    if (cmd == "help")
        help();
    else if (cmd == "add")
        addPatientCmd(line, priQueue);
    else if (cmd == "peek")
        peekNextCmd(priQueue);
    else if (cmd == "next")
        removePatientCmd(priQueue);
    else if (cmd == "list")
        showPatientListCmd(priQueue);
    else if (cmd == "load")
        execCommandsFromFileCmd(line, priQueue);
    else if (cmd == "quit")
        return false;
    else
        cout << "Error: unrecognized command: " << cmd << endl;

    return true;
}

void addPatientCmd(string line, PatientPriorityQueue &priQueue) {
    string priority, name;
    int priorityNo;

    //The logic to remove spaces must be before the call to delimitByspace
    line = removeLeadingTrailingSpaces(line);
    priority = delimitBySpace(line);
    if (priority.length() == 0) {
        cout << "Error: no priority code given.\n";
        return;
    }

    //The logic to remove spaces must be before the call to delimitBySpace
    line = removeLeadingTrailingSpaces(line);
    name = line;

    //Need to add more conditionals since the original if you typed out "add
    // urgent" it still added patient "urgent" to the priority system with
    // urgent priority.
    if (name.length() == 0 || name == "urgent" || name == "emergency" || name
    == "immediate" || name == "minimal") {
        cout << "Error: no patient name given.\n";
        return;
    }

    // TODO: add logic to remove leading/trailing spaces
    //Done before the call to delimitBySpace method

    // TODO: validate priority is between 1 and 4
    //Will return -1 and won't add the patient if it is not a valid command
    priorityNo = validatePriority(priority);

    // TODO: add patient
    //Only adds to the queue if it is a valid command
    if (priorityNo != -1) {
        priQueue.add(name, priorityNo);
        cout << "\nAdded patient \"" << name << "\" to the priority system.\n";
   }



}

void peekNextCmd(PatientPriorityQueue &priQueue) {
    // TODO: shows next patient to be seen

    //Prints out the peeked (next Patient) in the PriorityQueue
    cout << "Highest priority patient to be called next: " << priQueue.peek()
    .getPatientName() << endl;
}

void removePatientCmd(PatientPriorityQueue &priQueue) {
    // TODO: removes and shows next patient to be seen

    //If there is no Patient in the priority queue then display message
    if(priQueue.size() == 0) {
        cout << "There are no patients in the waiting area.\n";
    } else {

        //If there are Patient in the queue it is removed and printed out who
        // is removed
        cout << "This patient will now be seen: "
             << priQueue.remove().getPatientName() << endl;
    }

}

void showPatientListCmd(PatientPriorityQueue &priQueue) {
    cout << "# patients waiting: " << priQueue.size() << endl;
    cout << "  Arrival #   Priority Code   Patient Name\n"
         << "+-----------+---------------+--------------+\n";
    // TODO: shows patient detail in heap order

    //Simply prints out the priority queue
    cout << priQueue.to_string();
}

void execCommandsFromFileCmd(string filename, PatientPriorityQueue &priQueue) {
    ifstream infile;
    string line;

    // open and read from file
    infile.open(filename);
    if (infile) {
        while (getline(infile, line)) {
            cout << "\ntriage>" << line;
            // process file input
            processLine(line, priQueue);
        }
    } else {
        cout << "Error: could not open file.\n";
    }
    // close file
    infile.close();
}

string delimitBySpace(string &s) {
    unsigned pos = 0;
    char delimiter = ' ';
    string result = "";

    pos = s.find(delimiter);
    if (pos != string::npos) {
        result = s.substr(0, pos);
        s.erase(0, pos + 1);
    }
    return result;
}

void welcome() {
    // TODO
    cout << "This is a program which will simulate a Priority Queue system"
            "\nin a hospital. The program will allow you to:\n"
            "- add patients according to their priority order and arrival\n- "
            "see who the next patient is\n- remove the patient from the queue "
            "after they are seen\n- allows the user to see how many patients "
            "is on the priority queue.\n- type help and press enter in order "
            "to see how to use the commands for the program.\n- type quit to "
            "quit the program\n\n";

}

void goodbye() {
    // TODO
    cout << "\nThank you for using the program. Have a wonderful day.";
}

void help() {
    cout << "add <priority-code> <patient-name>\n"
         << "            Adds the patient to the triage system.\n"
         << "            <priority-code> must be one of the 4 accepted priority codes:\n"
         << "                1. immediate 2. emergency 3. urgent 4. minimal\n"
         << "            <patient-name>: patient's full legal name (may contain spaces)\n"
         << "next        Announces the patient to be seen next. Takes into account the\n"
         << "            type of emergency and the patient's arrival order.\n"
         << "peek        Displays the patient that is next in line, but keeps in queue\n"
         << "list        Displays the list of all patients that are still waiting\n"
         << "            in the order that they have arrived.\n"
         << "load <file> Reads the file and executes the command on each line\n"
         << "help        Displays this menu\n"
         << "quit        Exits the program\n";
}

int validatePriority(string priorityCode) {

    //Checks to see if the command is written correctly. If not return
    // negative one.
    int priorityNo;
    if(priorityCode == "immediate") {
        priorityNo = 1;

    } else if(priorityCode == "emergency") {
        priorityNo = 2;

    } else if(priorityCode == "urgent") {
        priorityNo = 3;

    } else if(priorityCode == "minimal") {
        priorityNo = 4;

    } else {
        cout << "Invalid priority code.\n";
        return -1;
    }
    //Return the priority number.
    return priorityNo;

}

string removeLeadingTrailingSpaces(string originalString) {


    //I followed the example the example in the C++ reference and it works
    string newString = "";
    size_t found = originalString.find_first_not_of(" ");

    //Remove the leading spaces
    int lengthOfOriginalString = originalString.length();
    if (found != string::npos) {
        for (int i = found; i < lengthOfOriginalString; i++) {
            newString += originalString[i];
        }
    }

    //Remove the trailing spaces
    size_t foundTrailing = newString.find_last_not_of(" ");
    if (found != string::npos) {
        newString.erase(foundTrailing+1);
    }

    return newString;

}
