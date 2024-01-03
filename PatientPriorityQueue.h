// Name: Phubeth Mettaprasert
// File: PatientPriorityQueue.h
// Date: May 27, 2022
//The header file and the implementation of the PatientPriorityQueue. Contains
// the framework to create a PriorityQueue using vectors to store Patient
// objects.
//Purpose: A class that will have different methods to add, manipulate and
//         delete Patient objects from a PriorityQueue where the queue will
//         maintain min heap order.

#ifndef P3_PATIENTPRIORITYQUEUE_H
#define P3_PATIENTPRIORITYQUEUE_H

#include <string>
#include <vector>
#include <cassert>
#include "Patient.h"

using namespace std;

class PatientPriorityQueue {
public:
    PatientPriorityQueue();
    // Constructor that initializes the PatientPriorityQueue class.
    // preconditions: none
    // postconditions: Sets the arrivalOrder to zero.

    void add(string, int);
    // A method to add a Patient object to the PriorityQueue. Heap order is
    // maintained once the Patient is added.
    // preconditions: A vector that exists so that Patient can be added to
    //                the queue.
    // postconditions: A Patient object will be added to the vector for the
    //                 priority queue.

    const Patient remove();
    // A method to remove a Patient object to the PriorityQueue. Heap order is
    // maintained once the Patient is removed.
    // preconditions: A vector that exists so that Patient can be removed.
    //                The vector must not be empty as well.
    // postconditions: The Patient object at index 0 (min heap ordered) will be
    //                 removed from the vector for the priority queue.

    const Patient peek() const;
    // Returns the highest priority patient without removing the patient.
    // preconditions: A vector that exists so that Patient can be peeked.
    //                The vector must not be empty as well.
    // postconditions: none


    int size();
    // Returns the number of patients still waiting.
    // preconditions: A vector that exists so the size function can be called.
    // postconditions: none

    string to_string() const;
    // Returns the string represation of the object in heap or level order.
    // preconditions: A vector that exists so the to_string method can be
    //                called. The vector can be empty.
    // postconditions: none


private:

    int arrivalOrderNo; //A private variable to keep track of the arrival order
    vector<Patient> Patients; //The vector for the priority queue

    //Keeps track of the size of the vector if I am understanding it correctly
    int nextPatientNumber;

    void siftUp(int);
    // A method that assists the add method. This method is called in order
    // to preserve the min heap order when adding a new value to the vector.
    // preconditions: A vector that exists so the siftup method can be
    //                called.
    // postconditions: Will restore the vector to min heap order after adding
    //                 the value.

    void siftDown(int);
    // A method that assists the remove method. This method is called in order
    // to preserve the min heap order when removing a value from the vector.
    // preconditions: A vector that exists so the siftdown method can be
    //                called.
    // postconditions: Will restore the vector to min heap order after
    //                 removing the value.

    int getParent(int) const;
    // A method to get the parent index based on the current index.
    // preconditions: A vector that exists so the getParent method can be
    //                called.
    // postconditions: none

    int getLeftChild(int) const;
    // A method to get the left child index of the current node.
    // preconditions: A vector that exists so the getLeftChild method can be
    //                called.
    // postconditions: none

    int getRightChild(int) const;
    // A method to get the right child index of the current node.
    // preconditions: A vector that exists so the getLeftChild method can be
    //                called.
    // postconditions: none

    bool empty() const;
    // A method to check if the vector is empty. Returns true if it is.
    // preconditions: none
    // postconditions: none


};

PatientPriorityQueue::PatientPriorityQueue() {

    //Starts the arrival order number at zero.
    arrivalOrderNo = 0;

    //Starts the nextPatientNumber at zero
    nextPatientNumber = 0;
}

void PatientPriorityQueue::add(string name, int priorityCode) {

    //Create a new Patient object
    Patient newPatient(name, priorityCode, arrivalOrderNo);

    //Pushes the Patient object to the end of the vector
    Patients.push_back(newPatient);

    //Calls siftUp to heapify inserting the index at size -1
    siftUp(Patients.size() - 1);

    //Increment the arrival order for next patient to be added.
    arrivalOrderNo++;

    //Increment the patient number
    nextPatientNumber++;

}

void PatientPriorityQueue::siftUp(int index) {

    int parentIndex;

    //Make it is not root node or index at zero
    if (index != 0) {

        //Find the parent index from the index given
        parentIndex = getParent(index);

        //Does the min heap comparison and swapping
        if (Patients[parentIndex] > Patients[index]) {
            Patient temp = Patients[parentIndex];
            Patients[parentIndex] = Patients[index];
            Patients[index] = temp;

            //Recursively call siftUp until heap order is maintained or
            // the current index gets to zero or the root node.
            siftUp(parentIndex);
        }
    }
}


int PatientPriorityQueue::getParent(int index) const {

    //Formula to find the parent index in the vector
    return (index - 1) / 2;
}


void PatientPriorityQueue::siftDown(int index) {

    //Finds the left and right index
    int leftIndex, rightIndex, minIndex;
    leftIndex = getLeftChild(index);
    rightIndex = getRightChild(index);

    //See if the index are still in bounds of the priority queue
    if (rightIndex >= nextPatientNumber) {
        if (leftIndex >= nextPatientNumber)
            return;
        else
            minIndex = leftIndex;
    } else {

        //Compare to see who has the min the left or the right
        if (Patients[leftIndex] < Patients[rightIndex])
            minIndex = leftIndex;
        else
            minIndex = rightIndex;
    }

    //Swap if the child index is less than the parent
    if (Patients[index] > Patients[minIndex]) {
        Patient temp = Patients[minIndex];
        Patients[minIndex] = Patients[index];
        Patients[index] = temp;
        siftDown(minIndex);
    }
}

int PatientPriorityQueue::getLeftChild(int index) const {
    return 2 * index + 1;
}

int PatientPriorityQueue::getRightChild(int index) const {
    return 2 * index + 2;
}



const Patient PatientPriorityQueue::remove() {
    //Assert if it is empty
    assert(!empty());

    //Set temp to Patient
    Patient temp = Patients[0];

    //Swap the root with the last one
    Patients[0] = Patients[nextPatientNumber - 1];

    //Delete the root that was just swapped
    Patients.pop_back();

    //Sift down
    if (Patients.size() > 1)
        siftDown(0);

    //Decrement
    nextPatientNumber--;

    //Return the old Patient object
    return temp;
}

const Patient PatientPriorityQueue::peek() const {

    //The top of the priority queue
    assert(!empty());
    return Patients[0];
}

bool PatientPriorityQueue::empty() const {

    //Check if there are still Patients in the queue
    return nextPatientNumber == 0;
}

string PatientPriorityQueue::to_string() const {

    //Print out the list in level order
    stringstream ss;
    for (int i = 0; i < nextPatientNumber; i++) {
        ss << Patients[i].to_string();
    }
    return ss.str();
}

int PatientPriorityQueue::size() {

    //returns the size of the vector
    return nextPatientNumber;
}

#endif //P3_PATIENTPRIORITYQUEUE_H
