# Hospital Emergency Room Triage Priority Queue System

## Project Description

This project implements a priority queue system for managing patient treatment urgency in a hospital emergency room. The system assigns priority levels to patients based on the severity of their conditions and manages their order of treatment accordingly.

## Priority Levels

Patients are classified by the following urgency levels:

- `1 (immediate)`: Should be seen immediately (0 minutes)
- `2 (emergency)`: Should be seen within 15 minutes
- `3 (urgent)`: Should be seen within 30 minutes
- `4 (minimal)`: Should be seen within 120 minutes

## System Interface

The program operates via a command-line interface (CLI) that supports several operations:

- `add <priority-code> <patient-name>`: Adds a patient with the given priority code and name to the queue.
- `peek`: Displays the next patient in line without removing them from the queue.
- `next`: Announces and removes the highest priority patient to be seen next.
- `list`: Lists all patients currently waiting, displayed in heap order.
- `load <file>`: Executes commands from a specified file, automating input.
- `help`: Displays help information for available commands.
- `quit`: Exits the program.

## Implementation Details

- `p3.cpp`: Contains the main program logic and user interface.
- `Patient.h`: Defines the `Patient` class with private variables for the patient's name, priority code, and arrival order. It also includes necessary methods and overloaded operators for patient management.
- `PatientPriorityQueue.h`: Implements a priority queue using a vector and maintains heap order. It provides functions for adding, peeking, removing patients, and other utility operations.
