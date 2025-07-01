#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

struct Node {
    string data;
    int id;
    Node* next;
};

class Linked_List {
public:
    Node* head;

    Linked_List() {
        head = nullptr;
        load_from_file();
    }

    bool id_exists(int Id) {
        return search_by_id(Id) != nullptr;
    }

    void sorted_insert(string Data, int Id) {
        if (id_exists(Id)) {
            cout << "\nID " << Id << " already exists. Entry not added.\n";
            return;
        }

        Node* newNode = new Node;
        newNode->data = Data;
        newNode->id = Id;
        newNode->next = nullptr;

        if (head == nullptr || head->id >= newNode->id) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr && current->next->id < newNode->id)
                current = current->next;

            newNode->next = current->next;
            current->next = newNode;
        }
        create_user_file(Id, Data);
        save_to_file();
    }

    Node* search_by_id(int Id) {
        Node* current = head;
        while (current != nullptr) {
            if (current->id == Id) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void display() {
        Node* current = head;
        while (current != nullptr) {
            cout << "Name: " << current->data << " | ID: " << current->id << "\n";
            current = current->next;
        }
        cout << endl;
    }

    void save_to_file() {
        ofstream file("users.txt");
        Node* current = head;
        while (current != nullptr) {
            file << current->data << " " << current->id << "\n";
            current = current->next;
        }
        file.close();
    }

    void load_from_file() {
        ifstream file("users.txt");
        if (!file.is_open()) return;
        string data;
        int id;
        while (file >> data >> id) {
            if (!id_exists(id)) {
                Node* newNode = new Node;
                newNode->data = data;
                newNode->id = id;
                newNode->next = head;
                head = newNode;
            }
        }
        file.close();
    }

    void create_user_file(int id, const string& name) {
        ofstream file(to_string(id) + ".txt", ios::app);
        file << "Name: " << name << "\nID: " << id << "\n";
        file.close();
    }

    void edit_user_file(int id) {
        string filename = to_string(id) + ".txt";

        ifstream infile(filename);
        if (!infile.is_open()) {
            cout << "Error: File for ID " << id << " does not exist.\n";
            return;
        }
        infile.close();

        string command = "notepad " + filename;
        system(command.c_str());

        cout << "\nUpdated contents of the file:\n";
        ifstream updatedFile(filename);
        string line;
        while (getline(updatedFile, line)) {
            cout << line << "\n";
        }
        updatedFile.close();
    }

    void display_file_content(int id) {
        ifstream file(to_string(id) + ".txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                cout << line << "\n";
            }
            file.close();
        } else {
            cout << "Error: File for ID " << id << " does not exist.\n";
        }
    }

    void delete_user_by_id(int id) {
        if (head == nullptr) {
            cout << "No users to delete.\n";
            return;
        }

        if (head->id == id) {
            Node* temp = head;
            head = head->next;
            delete temp;
            remove((to_string(id) + ".txt").c_str());
            cout << "User with ID " << id << " deleted.\n";
            update_users_file();
            return;
        }

        Node* current = head;
        while (current->next != nullptr && current->next->id != id) {
            current = current->next;
        }

        if (current->next == nullptr) {
            cout << "User with ID " << id << " not found.\n";
            return;
        }

        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
        remove((to_string(id) + ".txt").c_str());
        cout << "User with ID " << id << " deleted.\n";
        update_users_file();
    }

    void update_users_file() {
        ofstream file("users.txt");
        Node* current = head;
        while (current != nullptr) {
            file << current->data << " " << current->id << "\n";
            current = current->next;
        }
        file.close();
    }
};

void clearScreen() {
    system("cls");
}

void handle_doctor_access(Linked_List& l) {
    int user_choice, id;
    string data;

    while (true) {
        cout << "\n1. Add Name\n2. Search by ID\n3. Display List\n4. Edit File\n5. Delete User\n6. Exit\nEnter your choice: ";
        cin >> user_choice;

        switch (user_choice) {
            case 1:
                cout << "Enter name and ID: ";
                cin >> data >> id;
                l.sorted_insert(data, id);
                break;
            case 2:
                cout << "Enter ID to search: ";
                cin >> id;
                if (Node* res = l.search_by_id(id)) {
                    l.display_file_content(id);
                } else {
                    cout << "ID not found\n";
                }
                break;
            case 3:
                l.display();
                break;
            case 4:
                cout << "Enter ID of file to edit: ";
                cin >> id;
                l.edit_user_file(id);
                break;
            case 5:
                cout << "Enter ID to delete: ";
                cin >> id;
                l.delete_user_by_id(id);
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice, try again.";
        }
    }
}

void handle_patient_access(Linked_List& l) {
    int id;
    cout << "Enter your ID: ";
    cin >> id;
    if (Node* res = l.search_by_id(id)) {
        l.display_file_content(id);
    } else {
        cout << "ID not found\n";
    }
}

int main() {
    Linked_List l;
    int user_choice;

    do {
        cout << setw(50) << "Calcare\n" << endl;
        cout << setw(48) << "1-Doctor Login" << endl;
        cout << setw(50) << "2-Patient Access" << endl;
        cout << setw(40) << "3-Exit" << endl;
        cout << string(37, ' ') << "Your choice: ";
        cin >> user_choice;
        clearScreen();

        if (user_choice == 1) {
            handle_doctor_access(l);
        } else if (user_choice == 2) {
            handle_patient_access(l);
        } else if (user_choice == 3){
            return 0;
        }else {
            cout << "Invalid choice, try again.";
        }
    } while (true);

    return 0;
}
