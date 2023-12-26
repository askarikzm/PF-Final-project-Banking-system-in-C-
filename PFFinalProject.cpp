#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <windows.h>
using namespace std;
#define ANSI_BLUE "\033[34m"
#define ANSI_GREEN "\033[32m"
#define ANSI_RESET "\033[0m"
#define ANSI_pik "\033[38;5;213m"
#define ANSI_purp "\033[38;5;5m"
#define ANSI_RED "\033[1;31m"
#define ANSI_YELLOW "\033[1;33m"
using namespace std;

struct UserData
{
    string Firstname;
    string Lastname;
    string Pincode;
    int id_number;
    int balance = 0;
};
void PincodeUpdate(int U_d, string Pincode)
{
    UserData User;
    fstream files;
    files.open("users.csv", ios::in);

    string st, update, NewPin;
    const char CSV_DELIMITER = ',';
    while (getline(files, st))
    {
        istringstream iss(st);
        getline(iss, st, ',');
        User.id_number = stoi(st);

        getline(iss, User.Firstname, CSV_DELIMITER);
        getline(iss, User.Lastname, CSV_DELIMITER);
        getline(iss, User.Pincode, CSV_DELIMITER);
        getline(iss, st, CSV_DELIMITER);

        User.balance = stoi(st);

        if (U_d == User.id_number && Pincode == User.Pincode)
        {
            cout << "enter your new Pin code:";
            cin >> NewPin;
            cout << endl;
            User.Pincode = NewPin;
            cout << "Pin Code has successfully change to :" << User.Pincode << endl;
        }
        update += to_string(User.id_number) + CSV_DELIMITER + User.Firstname + CSV_DELIMITER + User.Lastname + CSV_DELIMITER + User.Pincode + CSV_DELIMITER + to_string(User.balance) + "\n";
    }

    files.close();

    files.open("users.csv", ios::out);

    files << update;
    files.close();
}

bool signin(int U_d, string Pincode)
{
    fstream files("users.csv", ios::in);
    string U_id, first, last, code, balance_str, st;

    while (getline(files, st))
    {
        istringstream iss(st);
        getline(iss, U_id, ',');
        getline(iss, first, ',');
        getline(iss, last, ',');
        getline(iss, code, ',');
        getline(iss, balance_str, ',');

        if (stoi(U_id) == U_d && Pincode == code)
        {
            return true;
        }
    }

    return false;
}

int deposit(int ide, string Pincode, int bal)
{
    UserData User;
    fstream files;
    files.open("users.csv", ios::in);

    string st, update;
    const char CSV_DELIMITER = ',';
    while (getline(files, st))
    {
        istringstream iss(st);
        getline(iss, st, ',');
        User.id_number = stoi(st);

        getline(iss, User.Firstname, CSV_DELIMITER);
        getline(iss, User.Lastname, CSV_DELIMITER);
        getline(iss, User.Pincode, CSV_DELIMITER);
        getline(iss, st, CSV_DELIMITER);

        User.balance = stoi(st);

        if (ide == User.id_number && Pincode == User.Pincode)
        {
            cout << ANSI_purp;
            cout << "Adding the balance in to your account" << endl;
            User.balance += bal;
            cout << ANSI_pik;
            cout << "Your Updated Balance is:" << User.balance;
        }
        update += to_string(User.id_number) + CSV_DELIMITER + User.Firstname + CSV_DELIMITER + User.Lastname + CSV_DELIMITER + User.Pincode + CSV_DELIMITER + to_string(User.balance) + "\n";
    }

    files.close();

    files.open("users.csv", ios::out);

    files << update;
    files.close();

    return 0;
}

void withdrawal(int ide, string Pincode, int amount)
{
    UserData User;
    fstream files;
    bool flag = true;
    files.open("users.csv", ios::in);
    const char CSV_DELIMITER = ',';

    string st, update;
    while (getline(files, st))
    {
        istringstream iss(st);

        getline(iss, st, CSV_DELIMITER);
        User.id_number = stoi(st);

        getline(iss, User.Firstname, CSV_DELIMITER);
        getline(iss, User.Lastname, CSV_DELIMITER);
        getline(iss, User.Pincode, CSV_DELIMITER);
        getline(iss, st, CSV_DELIMITER);

        User.balance = stoi(st);

        if (ide == User.id_number && Pincode == User.Pincode)
        {
            if (amount > User.balance)
            {
                cout << ANSI_RED;
                cout << "You dont have enough balance:";
                flag = false;
                break;
            }
            else
            {
                User.balance -= amount;
                cout << AnsiPrev;

                cout << "your updated balance is :" << User.balance;
            }
        }
        update += to_string(User.id_number) + CSV_DELIMITER + User.Firstname + CSV_DELIMITER + User.Lastname + CSV_DELIMITER + User.Pincode + CSV_DELIMITER + to_string(User.balance) + "\n";
    }

    files.close();
    if (flag == true)
    {
        files.open("users.csv", ios::out);

        files << update;
        files.close();
    }
}

void Data_Trs(int id, int id2, string pass, int amount)
{
    const char CSV_DELIMITER = ',';
    UserData User, User2;
    int check;
    fstream files;
    files.open("users.csv", ios::in);
    fstream otp;
    otp.open("otp.txt", ios::out | ios::trunc);
    srand(time(nullptr));
    int a = rand();
    otp << a;
    otp.close();
    cout << "enter a otp genrated in file" << endl;
    cin >> check;
    if (check == a)
    {
        bool found = true;
        string st, update;
        while (getline(files, st))
        {
            istringstream iss(st);
            getline(iss, st, CSV_DELIMITER);
            User.id_number = stoi(st);

            getline(iss, User.Firstname, CSV_DELIMITER);
            getline(iss, User.Lastname, CSV_DELIMITER);
            getline(iss, User.Pincode, CSV_DELIMITER);
            getline(iss, st, CSV_DELIMITER);

            User.balance = stoi(st);

            if (id == User.id_number && pass == User.Pincode)
            {

                if (User.balance < amount || id2 == id)
                {
                    cout << ANSI_RED;
                    cout << "You did Some thing wrong:" << endl;
                    found = false;
                    break;
                }
                else
                {

                    User.balance -= amount;
                    cout << ANSI_purp;
                    cout << "Transfering amount to " << id2 << " account this will take few seconds" << endl;
                    Sleep(3000);
                    cout << ANSI_RED;

                    cout << amount << "Rs"
                         << " successfully dedected from your account \n"
                         << endl;
                    cout << ANSI_GREEN;
                    cout << "Your current balance is: " << User.balance << "Rs" << endl;
                }
            }
            update += to_string(User.id_number) + CSV_DELIMITER + User.Firstname + CSV_DELIMITER + User.Lastname + CSV_DELIMITER + User.Pincode + CSV_DELIMITER + to_string(User.balance) + "\n";
        }

        if (found == true)
        {
            files.close();
            files.open("users.csv", ios::out);
            files << update;
            files.close();
            files.open("users.csv", ios::in);

            string update2, data2;

            while (getline(files, data2))
            {
                istringstream iss(data2);
                getline(iss, data2, CSV_DELIMITER);
                User2.id_number = stoi(data2);

                getline(iss, User2.Firstname, CSV_DELIMITER);
                getline(iss, User2.Lastname, CSV_DELIMITER);
                getline(iss, User2.Pincode, CSV_DELIMITER);
                getline(iss, data2, CSV_DELIMITER);

                User2.balance = stoi(data2);

                if (id2 == User2.id_number)
                {
                    User2.balance += amount;
                    cout << "Transaction done!" << endl;
                }
                update2 += to_string(User2.id_number) + CSV_DELIMITER + User2.Firstname + CSV_DELIMITER + User2.Lastname + CSV_DELIMITER + User2.Pincode + CSV_DELIMITER + to_string(User2.balance) + "\n";
            }

            files.close();

            files.open("users.csv", ios::out);
            files << update2;
            files.close();
        }
    }
    else
    {
        cout << " You have entered  wrong otp" << endl;
    }
}

int CheckBal(int ide, string Pincode)
{
    UserData User;
    fstream files;
    files.open("users.csv", ios::in);
    const char CSV_DELIMITER = ',';
    string st;
    while (getline(files, st))
    {
        istringstream iss(st);
        getline(iss, st, CSV_DELIMITER);
        User.id_number = stoi(st);

        getline(iss, User.Firstname, CSV_DELIMITER);
        getline(iss, User.Lastname, CSV_DELIMITER);
        getline(iss, User.Pincode, CSV_DELIMITER);
        getline(iss, st, CSV_DELIMITER);

        User.balance = stoi(st);

        if (ide == User.id_number && Pincode == User.Pincode)
        {
            cout << ANSI_purp;
            cout << "\nYour current balance is: " << User.balance << " Rs" << endl;
            return 0;
        }
    }
    return 0;
}

int signup()
{
    const char CSV_DELIMITER = ',';
    UserData User;
    cout << "Enter your First Name: " << endl;
    cin >> User.Firstname;
    cout << "Enter your Last Name: " << endl;
    cin >> User.Lastname;

    cout << "Enter Pin Code: " << endl;
    cin >> User.Pincode;
    User.balance = 0;
    User.id_number = 0;
    if (signin(User.id_number, User.Pincode))
    {
        cout << "Dear " << User.Firstname << " " << User.Lastname << " Your account is already created. Please sign in." << endl;
    }
    else
    {

        srand(time(nullptr));
        int a = rand();
        User.id_number = a;

        fstream files;
        files.open("users.csv", ios::app);
        files << User.id_number << CSV_DELIMITER << User.Firstname << CSV_DELIMITER << User.Lastname << CSV_DELIMITER << User.Pincode << CSV_DELIMITER << User.balance << endl;
        files.close();
        cout << ANSI_RED;
        cout << "Remember this unique id given from the bank as it is the Bank account number: " << User.id_number << endl;
        cout << ANSI_GREEN;
        cout << "Vanishing your details in 5 sec " << endl;
        Sleep(5000);
        system("cls");
    }

    return 0;
}

int display() {
    while (true) {
          cout << "\033[32m"; 
        cout << "      ___________________________\n";
        cout << "     | BANKING SYSTEM IN C++     |\n";
        cout << "     |      FUNCTIONALITY        |\n";
        cout << "     | login/SignUp/CheckBalance |\n";
        cout << "     | CHECK balance/TRANSFER    | \n";
        cout << "     |___________________________|\n" << "\033[0m";             
        cout << "          |  |  |  |  |  | \n";
        cout << "        __|__|__|__|__|__|__\n";
        cout << "       |  |  |  |  |  |  |  |\n";
        cout << "      _|__|__|__|__|__|__|__|__\n" << "\033[32m";           
        cout << "     | PROGRAMMING fUNDAMENTALS|\n";
        cout << "     |    SEMESTER Project     |\n";
        cout << "     |MADE BY Sabir and Askari |\n";
        cout << "     |_________________________|\n";
        cout << "\033[0m"; 

        Sleep(4000);
        cout << endl;
        int choice;
          cout << "1. Sign Up\n2. Sign In\n3. Exit\n";
        cout << "\033[0m"; 
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Error: Please enter a valid integer.\n";
            continue;
        }

        if (choice < 1 || choice > 3) {
            cout << "Error: Invalid choice. Please enter a number between 1 and 3.\n";
            continue;
        }

        return choice;
    }
}


void Full(){
       UserData Data;
    while (true)
    {

      int choice=display();
        if (choice == 1)
        {
            cout << ANSI_BLUE;
            signup();
        }
        else if (choice == 2)
        {
            cout << ANSI_GREEN;

            cout << "Enter your Bank account number:  ";
            cin >> Data.id_number;
            cout << "Enter your Pincode: ";
            cin >> Data.Pincode;
            cout << endl;
            cout << "Checking your data in in to our file. This will take few seconds: ";
            Sleep(3000);
            cout << endl;
            bool flag = true;

            if (signin(Data.id_number, Data.Pincode))
            {
                bool flag = true;
                cout << "Your account has been login successfully:" << endl;

                while (flag)
                {
                    int opt;
                    cout << ANSI_YELLOW;
                    cout << "\nTo Preform operations Press  \n1. Deposit Cash\n2. Withdraw Money\n3. Check Balance\n4. Transfer amount\n5. Change Pin \n6. logout from account" << endl;
                    cout << "Your Choices: ";
                    cin >> opt;
                 if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Error: Please enter a valid integer.\n";
            continue;
        }

       else if (opt <1 || opt >6 ) {
            cout << "Error: Invalid choice. Please enter a number between 1 and 6.\n";
            continue;
        }

                   else if (opt == 1)
                    {
                        cout << ANSI_BLUE;
                        int amount;
                        cout << "Enter the amount you want to deposit: ";
                        cin >> amount;
                        deposit(Data.id_number, Data.Pincode, amount);
                        cout << ANSI_RESET;
                        Sleep(500);
                    }
                    else if (opt == 2)
                    {
                        cout << ANSI_RED;
                        int amount1;
                        cout << "Enter the amount you want to withdraw: ";
                        cin >> amount1;
                        withdrawal(Data.id_number, Data.Pincode, amount1);
                        Sleep(500);
                        cout << ANSI_RESET;
                    }
                    else if (opt == 4)
                    {
                        int acc;
                        cout << "Enter the account number you want to transfer to: ";
                        cin >> acc;
                        int amount;
                        cout << "Enter the amount you want to transfer: ";
                        cin >> amount;
                        Data_Trs(Data.id_number, acc, Data.Pincode, amount);
                        Sleep(500);
                    }
                    else if (opt == 3)
                    {
                        cout << ANSI_YELLOW;
                        CheckBal(Data.id_number, Data.Pincode);
                        Sleep(500);
                        cout << ANSI_RESET;
                    }
                    else if (opt == 6)
                    {
                        cout << ANSI_YELLOW;
                        cout << "Clearing terminal to avoid data breach";
                        system("cls");
                        Sleep(500);
                        cout << "Successfully logout from account" << endl;
                        Sleep(500);
                        cout << ANSI_RESET;

                        flag = false;
                    }
                    else if (opt == 5)
                    {
                        cout << ANSI_GREEN;
                        PincodeUpdate(Data.id_number, Data.Pincode);
                        cout << ANSI_RESET;
                    }
                }
            }
            else
            {
                cout << ANSI_RED;
                cout << "Invalid username or password. Please sign up first." << endl;
                cout << ANSI_RESET;
                flag = false;
            }
        }
        else if (choice == 3)
        {
            cout << ANSI_YELLOW;
            cout << "Thanks for using ATM ";
            cout << ANSI_RESET;
            exit(0);
        }
    }
}
int main()
{

 Full();
}