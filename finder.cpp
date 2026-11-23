
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX = 100;

struct Classroom
{
    string room;
    string building;
    int capacity;
    bool available;
};

Classroom rooms[MAX];
int count = 0;

// Save data
void saveData()
{
    ofstream file("classrooms.txt");

    for (int i = 0; i < count; i++)
    {
        file << rooms[i].room << " "
             << rooms[i].building << " "
             << rooms[i].capacity << " "
             << rooms[i].available << endl;
    }

    file.close();
}

// Load data
void loadData()
{
    ifstream file("classrooms.txt");

    while (count < MAX &&
           file >> rooms[count].room
                >> rooms[count].building
                >> rooms[count].capacity
                >> rooms[count].available)
    {
        count++;
    }

    file.close();
}

// Table header
void header()
{
    cout << left
         << setw(15) << "Room"
         << setw(20) << "Building"
         << setw(15) << "Capacity"
         << setw(15) << "Status" << endl;

    cout << string(65, '-') << endl;
}

// Display classroom
void display(Classroom r)
{
    cout << left
         << setw(15) << r.room
         << setw(20) << r.building
         << setw(15) << r.capacity
         << setw(15) << (r.available ? "Available" : "Not Available")
         << endl;
}

// Add classroom
void addClassroom()
{
    if (count >= MAX)
    {
        cout << "Classroom list is full!\n";
        return;
    }

    cout << "Enter Room Number: ";
    cin >> rooms[count].room;

    for (int i = 0; i < count; i++)
    {
        if (rooms[i].room == rooms[count].room)
        {
            cout << "Room already exists!\n";
            return;
        }
    }

    cout << "Enter Building Name: ";
    cin >> rooms[count].building;

    cout << "Enter Capacity: ";
    cin >> rooms[count].capacity;

    int status;

    cout << "1. Available\n2. Not Available\n";
    cout << "Enter Status: ";
    cin >> status;

    rooms[count].available = (status == 1);

    count++;
    saveData();

    cout << "Classroom added successfully!\n";
}

// View all classrooms
void viewClassrooms()
{
    if (count == 0)
    {
        cout << "No classroom found!\n";
        return;
    }

    cout << "\nAll Classrooms:\n";
    header();

    for (int i = 0; i < count; i++)
    {
        display(rooms[i]);
    }
}

// Search available classrooms
void searchAvailable()
{
    bool found = false;

    cout << "\nAvailable Classrooms:\n";
    header();

    for (int i = 0; i < count; i++)
    {
        if (rooms[i].available)
        {
            display(rooms[i]);
            found = true;
        }
    }

    if (!found)
        cout << "No available classroom!\n";
}

// Search by capacity
void searchCapacity()
{
    int cap;
    bool found = false;

    cout << "Enter required capacity: ";
    cin >> cap;

    cout << "\nClassrooms by Capacity:\n";
    header();

    for (int i = 0; i < count; i++)
    {
        if (rooms[i].capacity >= cap)
        {
            display(rooms[i]);
            found = true;
        }
    }

    if (!found)
        cout << "No classroom found!\n";
}

// Update room status
void updateStatus()
{
    string room;
    int status;
    bool found = false;

    cout << "Enter Room Number: ";
    cin >> room;

    for (int i = 0; i < count; i++)
    {
        if (rooms[i].room == room)
        {
            cout << "1. Available\n2. Not Available\n";
            cout << "Enter New Status: ";
            cin >> status;

            rooms[i].available = (status == 1);

            saveData();

            cout << "Status updated successfully!\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Room not found!\n";
}

// Delete classroom
void deleteClassroom()
{
    string room;
    bool found = false;

    cout << "Enter Room Number: ";
    cin >> room;

    for (int i = 0; i < count; i++)
    {
        if (rooms[i].room == room)
        {
            for (int j = i; j < count - 1; j++)
            {
                rooms[j] = rooms[j + 1];
            }

            count--;
            saveData();

            cout << "Classroom deleted successfully!\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Room not found!\n";
}

// Search by room number
void searchRoom()
{
    string room;
    bool found = false;

    cout << "Enter Room Number: ";
    cin >> room;

    cout << "\nSearch Result:\n";
    header();

    for (int i = 0; i < count; i++)
    {
        if (rooms[i].room == room)
        {
            display(rooms[i]);
            found = true;
        }
    }

    if (!found)
        cout << "Room not found!\n";
}

// Main function
int main()
{
    loadData();

    int choice;

    do
    {
        cout << "\n================================\n";
        cout << "     EMPTY CLASSROOM FINDER\n";
        cout << "================================\n";

        cout << "1. Add Classroom\n";
        cout << "2. View All Classrooms\n";
        cout << "3. Search Available Rooms\n";
        cout << "4. Search by Capacity\n";
        cout << "5. Update Room Status\n";
        cout << "6. Delete Classroom\n";
        cout << "7. Search by Room Number\n";
        cout << "8. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addClassroom();
                break;

            case 2:
                viewClassrooms();
                break;

            case 3:
                searchAvailable();
                break;

            case 4:
                searchCapacity();
                break;

            case 5:
                updateStatus();
                break;

            case 6:
                deleteClassroom();
                break;

            case 7:
                searchRoom();
                break;

            case 8:
                saveData();
                cout << "Application closed!\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 8);

    return 0;
}
