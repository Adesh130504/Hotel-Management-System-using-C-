#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <limits>

using namespace std;

void intro() {
    cout << "\n\n\t";
    cout << "     C++ Project On Hotel Management System";
    
    cout << "\n-------------------------------------------------\n";
}

void head() {
    cout << "\n-------------------------------------------------";
    cout << "\n||\t\t\t   XYZ Group of Hotels\t\t\t      ||";
    cout << "\n-------------------------------------------------\n";
}

void time() {
    int i = 0;
    long long j;
    cout << "\n\n\n\tConnecting to Server\n\tSyncing Data";
    while (i < 10) {
        for (j = 5; j > 4; j++) {
            if (j == 99999) {
                cout << ".";
                break;
            }
        }
        ++i;
    }
    cout << endl;
}

class Hotel {
    private:
        int room_no;
        char name[30];
        char address[50];
        char phone[15];
        int days;
        float fare;
    public:
        void main_menu();      // to display the main menu
        void add();            // to book a room
        void display();        // to display the customer record
        void rooms();          // to display allotted rooms
        void edit();           // to edit the customer record
        int check(int);        // to check room status
        void modify(int);      // to modify the record
        void delete_rec(int);  // to delete the record
};

void Hotel::main_menu() {
    int choice = 0;
    while (choice != 5) {
        head();
        cout << "\n\t\t\t\t*************";
        cout << "\n\t\t\t\t* MAIN MENU *";
        cout << "\n\t\t\t\t*************";
        cout << "\n\n\n\t\t\t1. Book A Room";
        cout << "\n\t\t\t2. Customer Record";
        cout << "\n\t\t\t3. Rooms Allotted";
        cout << "\n\t\t\t4. Edit Record";
        cout << "\n\t\t\t5. Exit";
        cout << "\n\n\t\t\tEnter Your Choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any remaining input

        switch (choice) {
            case 1:
                add();
                break;
            case 2:
                display();
                break;
            case 3:
                rooms();
                break;
            case 4:
                edit();
                break;
            case 5:
                break;
            default:
                cout << "\n\n\t\t\tWrong choice.....!!!";
                cout << "\n\t\t\tPress any key to continue....!!";
                cin.get();  // wait for any key press
        }
    }
}

void Hotel::add() {
    head();
    int r, flag;
    ofstream fout("Record.dat", ios::app);
    cout << "\n Enter Customer Details";
    cout << "\n ----------------------";
    cout << "\n\n Room no: ";
    cin >> r;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any remaining input
    flag = check(r);
    if (flag)
        cout << "\n Sorry..!!! Room is already booked";
    else {
        room_no = r;
        cout << " Name: ";
        cin.getline(name, sizeof(name));
        cout << " Address: ";
        cin.getline(address, sizeof(address));
        cout << " Phone No: ";
        cin.getline(phone, sizeof(phone));
        cout << " No of Days to Checkout: ";
        cin >> days;
        fare = days * 900;  // 900 is currently set as the default price per day
        fout.write(reinterpret_cast<char*>(this), sizeof(Hotel));
        cout << "\n Room is booked...!!!";
    }
    cout << "\n Press any key to continue.....!!";
    cin.get();  // wait for any key press
    fout.close();
}

void Hotel::display() {
    head();
    ifstream fin("Record.dat", ios::in);
    int r, flag = 0;
    cout << "\n Enter room no: ";
    cin >> r;
    while (fin.read(reinterpret_cast<char*>(this), sizeof(Hotel))) {
        if (room_no == r) {
            head();
            cout << "\n Customer Details";
            cout << "\n ----------------";
            cout << "\n\n Room no: " << room_no;
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone no: " << phone;
            cout << "\n Days: " << days;
            cout << "\n Total Fare: " << fare;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        cout << "\n Sorry Room no. not found or vacant....!!";
    cout << "\n\n Press any key to continue....!!";
    cin.get();  // wait for any key press
    fin.close();
}

void Hotel::rooms() {
    head();
    ifstream fin("Record.dat", ios::in);
    cout << "\n\t\t\t    List Of Rooms Allotted";
    cout << "\n\t\t\t    ----------------------";
    while (fin.read(reinterpret_cast<char*>(this), sizeof(Hotel))) {
        cout << "\n Room no: " << room_no << "\n Name: " << name;
        cout << "\n Address: " << address << "\n Phone: " << phone;
        cout << "\n Days: " << days << "\n Total: " << fare;
        cout << "\n**********************************";
    }
    cout << "\n\n\n\t\t\tPress any key to continue.....!!";
    cin.get();  // wait for any key press
    fin.close();
}

void Hotel::edit() {
    head();
    int choice, r;
    cout << "\n EDIT MENU";
    cout << "\n ---------";
    cout << "\n\n 1. Modify Customer Record";
    cout << "\n 2. Delete Customer Record";
    cout << "\n Enter your choice: ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any remaining input

    head();
    cout << "\n Enter room no: ";
    cin >> r;
    switch (choice) {
        case 1:
            modify(r);
            break;
        case 2:
            delete_rec(r);
            break;
        default:
            cout << "\n Wrong Choice.....!!";
    }
    cout << "\n Press any key to continue....!!!";
    cin.get();  // wait for any key press
}

int Hotel::check(int r) {
    int flag = 0;
    ifstream fin("Record.dat", ios::in);
    while (fin.read(reinterpret_cast<char*>(this), sizeof(Hotel))) {
        if (room_no == r) {
            flag = 1;
            break;
        }
    }
    fin.close();
    return flag;
}

void Hotel::modify(int r) {
    head();
    long pos;
    int flag = 0;
    fstream file("Record.dat", ios::in | ios::out | ios::binary);
    while (file.read(reinterpret_cast<char*>(this), sizeof(Hotel))) {
        pos = file.tellg();
        if (room_no == r) {
            cout << "\n Enter New Details";
            cout << "\n -----------------";
            cout << "\n Name: ";
            cin.getline(name, sizeof(name));
            cout << " Address: ";
            cin.getline(address, sizeof(address));
            cout << " Phone no: ";
            cin.getline(phone, sizeof(phone));
            cout << " Days: ";
            cin >> days;
            fare = days * 900;
            file.seekg(pos - sizeof(Hotel));
            file.write(reinterpret_cast<char*>(this), sizeof(Hotel));
            cout << "\n Record is modified....!!";
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        cout << "\n Sorry Room no. not found or vacant...!!";
    file.close();
}

void Hotel::delete_rec(int r) {
    head();
    int flag = 0;
    char ch;
    ifstream fin("Record.dat", ios::in);
    ofstream fout("temp.dat", ios::out);
    while (fin.read(reinterpret_cast<char*>(this), sizeof(Hotel))) {
        if (room_no == r) {
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone No: " << phone;
            cout << "\n Days: " << days;
            cout << "\n Total Fare: " << fare;
            cout << "\n\n Do you want to delete this record(y/n): ";
            cin >> ch;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any remaining input
            if (ch == 'n')
                fout.write(reinterpret_cast<char*>(this), sizeof(Hotel));
            flag = 1;
        } else {
            fout.write(reinterpret_cast<char*>(this), sizeof(Hotel));
        }
    }
    fin.close();
    fout.close();
    if (flag == 0)
        cout << "\n Sorry room no. not found or vacant...!!";
    else {
        remove("Record.dat");
        rename("temp.dat", "Record.dat");
    }
}

int main() {
    Hotel h;
    cout << "\n\n\n";
    intro();
    time();
    cout << "\n\n\n\t\t\tPress any key to continue....!!";
    cin.get();  // wait for any key press

    head();
    string id, pass;
    cout << "\n\n\t\t\t\tusername => ";
    cin >> id;
    cout << "\n\t\t\t\tpassword => ";
    cin >> pass;

    cout << "\n\n\t";
    time();
    cout << "\t";
    if (id == "admin" && pass == "******")
        cout << "\n\n\t\t\t  !!!Login Successful!!!";
    else {
        cout << "\n\n\t\t\t!!!INVALID CREDENTIALS!!!";
        cin.get();  // wait for any key press
        return -1;
    }

    h.main_menu();

    return 0;
}
