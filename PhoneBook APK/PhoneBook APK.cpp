#include <iostream>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

// User Functions
    // Main Functions
void getData();
void save();
void menu();
void addContact();
void showContact();
void edit();
void search();
void deleteContact();
// Sub Functions
void enterName(int);
void enterGender(int);
void enterPhone(int);
void enterEmail(int);
// Inputs Validation
bool nameValidation(string, int);
bool genderValidation(string);
bool phoneValidation(string, int);
bool emailValidation(string, int&, int);
// Systematic Functions
string lowerCase(string);
string upperCase(string);
void lines();
void headName(string);
void Beeb();
void msgView(string, string);
void teamView(string, string);
string space(int);
void ending();

// Main Struct
struct contacts {
    string name;
    string gender;
    string phoneNum;
    string anotherMail;
    string mail[2];
};

// Main Data
short int counter = 0;

// Contact's Data
contacts Contact[10000];


int main()
{
    // Getting Data Back
    getData();

    // Start
    menu();

}

//For Data ------------------------------------------------------------
    //Saving Data
void save() {
    // Saving Contact's Data To Storage
    ofstream Storage("storage.txt");

    for (int i = 0; i < counter; i++) {
        // save Name/PhoneNumber To Storage
        Storage << Contact[i].name << endl
            << Contact[i].gender << endl
            << Contact[i].phoneNum << endl
            << Contact[i].anotherMail << endl
            << Contact[i].mail[0] << endl
            << Contact[i].mail[1] << endl;
    }

    Storage.close();
}

//Getting Data Back
void getData() {
    ifstream Storage("storage.txt");
    int i = 0;
    // end of file
    while (!(Storage.eof())) {
        // Restore Contact's Name
        getline(Storage, Contact[i].name);
        // Restore Contact's gender
        getline(Storage, Contact[i].gender);
        // Restore Contact's Phone Number
        getline(Storage, Contact[i].phoneNum);
        // Restore Contact's another Mail Checker
        getline(Storage, Contact[i].anotherMail);
        // Restore Contact's Mail 1
        getline(Storage, Contact[i].mail[0]);
        // Restore Contact's Mail 2
        getline(Storage, Contact[i].mail[1]);
        counter = i;
        i++;
    }
    Storage.close();
}

// For Menu View
void menu() {

    headName("Menu");

    short int i;
    string menuList[6] = { "View Contact","Search For a Contact","Add Contact","Edit Contact","Delete Contact","Exit" };
    for (i = 1; i <= 6; i++) {
        cout << "\n\n" << "\t\t" <<"\033[1m\033[36m"<< i << "- " << menuList[i - 1];
        Sleep(100);
    }

    string menuNum;

    cout << "\n\n\t How Can I Help You (1-" << i - 1 << ")?  "; getline(cin, menuNum);

    // Menu Action
    if (menuNum == "1") {
        system("cls");
        showContact();
    }
    else if (menuNum == "2") {
        system("cls");
        search();
    }
    else if (menuNum == "3") {
        system("cls");
        addContact();
    }
    else if (menuNum == "4") {
        system("cls");
        edit();
    }
    else if (menuNum == "5") {
        system("cls");
        deleteContact();
    }
    else {
        system("cls");
        ending();
    }
}

//Adding Data ---------------------------------------------------------
    //Main Add Contact Function
void addContact() {

    // Add Contact's Condetion
    bool add = true;

    // Add Contact's Input
    string addAnother;

    // Add Contact's Loop
    while (add) {

        headName("Add New Contact");

        // Enter Contact's Name
        enterName(counter);

        // Enter Contact's Gender
        enterGender(counter);
        //cout << "\n\n\tGender: "; getline(cin, Contact[counter].gender);

    // Contact's Phone Number
        enterPhone(counter);


        // Adding Emails
        enterEmail(counter);

        // Counter
        counter++;

        // Success Message

        msgView("\033[1m\033[32m", "Contact Has Added Successfuly");

        // Save New Contact's Data
        save();

        // Add Another Contact
        cout << "\nAdd Another Contact (y/n)? "; getline(cin, addAnother);
        if (lowerCase(addAnother) == "y" || lowerCase(addAnother) == "yes") {
            add = true;
            system("cls");
        }
        else {
            add = false;
            system("cls");
            menu();
        }

    }
}

// Entering & Validating Name
    // Entering New Name
void enterName(int num) {
    // Adding Condition
    bool Valid = false;

    // Adding Loop
    while (!Valid) {
        // Get Data From User
        cout << "\n\n\tName: "; getline(cin, Contact[num].name);
        Valid = nameValidation(Contact[num].name, num);
    }
}
// Check Mail Validation
bool nameValidation(string name, int num) {

    bool Valid = true;

    // Name's Validating
    if (name.length() <= 2 || name.length() > 20) {
        // Check If The Name Is Between (2 - 20)
        cout << "\033[1m\033[31m" << "\nName Must Be More than Two Characters and Less Than or Equal Twenty!\n" << "\033[1m\033[33m";
        Valid = false;
        Sleep(500);
    }
    else {

        // Check If The Name Is Alreade Exists
        for (int i = 0; i < counter; i++) {
            if (name == Contact[i].name && i != num) {
                Valid = false;
                cout << "\033[1m\033[31m" << "\nThis Name Already Exists!\n" << "\033[1m\033[33m";
                Sleep(500);
                break;
            }
            else {
                Valid = true;
            }
        }
    }

    // Returned Value
    return Valid;
}

// Entering & Validating Gender
    // Entering Gender
void enterGender(int num) {
    // Adding Condition
    bool Valid = false;

    // Adding Loop
    while (!Valid) {

        // Getting Data From User
        cout << "\n\tGender: "; getline(cin, Contact[num].gender);
        Valid = genderValidation(Contact[num].gender);

    }
}
// Validating Gender
bool genderValidation(string gender) {
    gender = lowerCase(gender);
    // Adding Condition
    bool Valid = true;
    // Check Characters
    for (short int i = 0; i < gender.length(); i++) {
        if (!(gender[i] >= 97 && gender[i] <= 122)) {
            cout << "\033[1m\033[31m" << "\nGender Must Be Only Characters!\n" << "\033[1m\033[33m";
            Sleep(500);
            return false;
        }
    }

    // Entering Rules
    if (gender.length() <= 2 || gender.length() > 8) {
        cout << "\033[1m\033[31m" << "\nGender Must Be More than Two Characters and Less Than or Equal Eight!\n" << "\033[1m\033[33m";
        Sleep(500);
        return false;
    }
    else {
        Valid = true;
    }

    // Return Value
    return Valid;
}

// Entering & Validating Phone
    // Entering PhoneNumber
void enterPhone(int num) {
    // Adding Condition
    bool notValid = true;
    // Adding Loop
    while (notValid) {

        // Getting Data From User
        cout << "\n\tPhone Number: "; getline(cin, Contact[num].phoneNum);
        notValid = phoneValidation(Contact[num].phoneNum, num);

    }
}
// Validating Phone
bool phoneValidation(string phone, int num) {
    // Adding Condition
    bool notValid = true;

    // Check The Length Of The Phone Number Less Than 20 for All Acceptable Numbers
    if (phone.length() <= 20 && phone.length() >= 1) {
        notValid = false;
        for (short int i = 0; i < phone.length(); i++) {

            // Chck If The Phone Number Has Characters
            if (!(phone[i] >= 48 && phone[i] <= 57)) {
                cout << "\033[1m\033[31m" << "\nPhone Number Must Be Only Numbers! \n" << "\033[1m\033[33m";
                Sleep(500);
                return true;
            }
        }
        // Check If The Phone Number Is Existed Before
        for (short int i = 0; i < counter; i++) {
            if (phone == Contact[i].phoneNum && i != num) {
                notValid = true;
                cout << "\033[1m\033[31m" << "\nThis Phone Number Already Exists!\n" << "\033[1m\033[33m";
                Sleep(500);
                break;
            }
            else {
                notValid = false;
            }
        }
    }
    else {
        cout << "\033[1m\033[31m" << "\nPhone Number Must Be More than One Number and Less than Twenty Digits! \n" << "\033[1m\033[33m";
        notValid = true;
        Sleep(500);
    }
    // Return Value
    return notValid;
}

//Entering & Validating Email
void enterEmail(int num) {
    // Adding Condition
    bool addEmail = true;

    // Adding Loop
    while (addEmail) {
        cout << "\n\tEmails: \n";

        for (int i = 0; i < 2; i++) {

            // Getting Data From User
            cout << "\n\t\t" << i + 1 << "- Email: "; getline(cin, Contact[num].mail[i]);

            // Chcking With Validation Function
            if (emailValidation(Contact[num].mail[i], i, num) == false) {
                continue;
            }
            else {

                // To Check If The Contact Already Got Two Mails Or Not
                if (i != 1) {
                    cout << "\nHave a Second Email (y/n)? "; getline(cin, Contact[counter].anotherMail);
                    if (lowerCase(Contact[counter].anotherMail) == "y" || lowerCase(Contact[counter].anotherMail) == "yes") {
                        continue;
                    }
                    else {
                        Contact[counter].mail[1] = "None";
                        addEmail = false;
                        break;
                    }
                }
                else {
                    addEmail = false;
                }
            }
        }

    }
}
// Validating Mail
bool emailValidation(string email, int& i, int num) {
    // Validating Condition
    bool valid = true;
    // Saving Data in Variable In With Low Characters
    string mail = lowerCase(email);

    // Checking If The Email Has [@ / . / mail kind / Right Mail end]
    if ((mail.find("@") != string::npos) && (mail.find("@") >= 3) && (mail.find(".") != string::npos) && (mail.find(" ") == string::npos) && (mail.find(".") - mail.find("@") >= 3) && (mail.length() - mail.find(".") >= 2)) {

        // Checking If Mail's Length Is More Than 28 Character
        if (mail.length() > 28) {
            cout << "\033[1m\033[31m" << "\nEmail Can't Be More Than 28 Character. \n" << "\033[1m\033[33m";
            Sleep(500);
            valid = false;
        }
        else {

            // Check If The Email Is Already Existed Before
            for (short int j = 0; j < counter; j++) {
                if (j != num) {
                    if (mail == lowerCase(Contact[j].mail[0]) || mail == lowerCase(Contact[j].mail[1])) {
                        valid = false;
                        i--;
                        cout << "\033[1m\033[31m" << "\nThis Email Already Exists\n" << "\033[1m\033[33m";
                        Sleep(500);
                        break;
                    }
                }
            }

            // Check If The Second Mail = The First Mail
            if (i == 1) {
                if (mail == lowerCase(Contact[counter].mail[0])) {
                    string skip;
                    cout << "\033[1m\033[31m" << "\nTwo Mails Can't Be The Same!!\n" << "\033[1m\033[33m";
                    Sleep(500);
                    cout << "\n\t\tSkip The Second Mail (y/n)? "; getline(cin, skip);
                    if (lowerCase(skip) == "y" || lowerCase(skip) == "yes") {
                        Contact[counter].mail[1] = "None";
                        valid = true;
                    }
                    else {
                        i--;
                        valid = false;
                    }
                }
            }
        }
    }
    else {
        i--;
        cout << "\033[1m\033[31m" << "\nWrong Email Type. \n" << "\033[1m\033[33m";
        Sleep(500);
        valid = false;
    }

    // Return value
    return valid;
}

//Showing Data --------------------------------------------------------
void showContact() {

    headName("Show Contacts");

    cout << "|" << setw(20) << "Name";
    cout << "|" << setw(13) << "Phone Number";
    cout << "|" << setw(8) << "Gender";
    cout << "|" << setw(28) << "First Mail";
    cout << "|" << setw(28) << "Second Mail" << "|";

    cout << endl;
    lines();

    for (short int i = 0; i < counter; i++) {
        cout << "|" << setw(20) << Contact[i].name;
        Sleep(5);
        cout << "|" << setw(13) << Contact[i].phoneNum;
        Sleep(5);
        cout << "|" << setw(8) << Contact[i].gender;
        Sleep(5);
        cout << "|" << setw(28) << Contact[i].mail[0];
        Sleep(5);
        cout << "|" << setw(28) << Contact[i].mail[1] << "|";
        Sleep(5);
        cout << endl;
    }

    lines();
    cout << "\n\n\t";
    system("pause");
    system("CLS");
    menu();
}

//Editing Data --------------------------------------------------------
void edit() {

    headName("Edit a Contact");

    short int editNum = -1;
    string editName;

    cout << "\n\n\t\tEnter Name or Phone Number (Case sensitive): "; getline(cin, editName); cout << "\n";
    if (editName != "") {
        for (short int i = 0; i < counter; i++) {
            if (Contact[i].name.find(editName) != string::npos || Contact[i].phoneNum.find(editName) != string::npos) {
                editNum = i;

                cout << endl;
                lines();

                cout << "|" << setw(20) << "Name";
                cout << "|" << setw(13) << "Phone Number";
                cout << "|" << setw(8) << "Gender";
                cout << "|" << setw(28) << "First Mail";
                cout << "|" << setw(28) << "Second Mail" << "|";

                cout << endl;
                lines();

                cout << "|" << setw(20) << Contact[i].name;
                Sleep(5);
                cout << "|" << setw(13) << Contact[i].phoneNum;
                Sleep(5);
                cout << "|" << setw(8) << Contact[i].gender;
                Sleep(5);
                cout << "|" << setw(28) << Contact[i].mail[0];
                Sleep(5);
                cout << "|" << setw(28) << Contact[i].mail[1] << "|";
                Sleep(5);

                cout << endl;
                lines();

                break;
            }
        }
        if (editNum == -1) {
            msgView("\033[1m\033[31m", "No Contact with That Name/Phone");
            Sleep(650);
        }
        else {

            enterName(editNum);

            enterGender(editNum);

            enterPhone(editNum);

            enterEmail(editNum);

            save();

            system("cls");
            menu();
        }
    }
    else {
        msgView("\033[1m\033[31m", "Please Enter a Value");
        Sleep(1600);
        system("cls");
        edit();
    }
}

//Searching for Data --------------------------------------------------------
void search() {

    headName("Search for a contact");

    string searchKey;

    cout << "\n\tWho Are You Looking For: ";

    getline(cin, searchKey);
    cout << endl;
    lines();

    cout << "|" << setw(20) << "Name";

    cout << "|" << setw(13) << "Phone Number";

    cout << "|" << setw(8) << "Gender";

    cout << "|" << setw(28) << "First Mail";

    cout << "|" << setw(28) << "Second Mail" << "|";

    cout << endl;
    lines();

    searchKey = lowerCase(searchKey);

    for (int i = 0; i < counter; i++) {

        if (lowerCase(Contact[i].name).find(searchKey) != string::npos || lowerCase(Contact[i].gender) == searchKey || Contact[i].phoneNum.find(searchKey) != string::npos || lowerCase(Contact[i].mail[0]).find(searchKey) != string::npos || lowerCase(Contact[i].mail[1]).find(searchKey) != string::npos) {
            cout << "|" << setw(20) << Contact[i].name;
            Sleep(5);
            cout << "|" << setw(13) << Contact[i].phoneNum;
            Sleep(5);
            cout << "|" << setw(8) << Contact[i].gender;
            Sleep(5);
            cout << "|" << setw(28) << Contact[i].mail[0];
            Sleep(5);
            cout << "|" << setw(28) << Contact[i].mail[1] << "|";
            Sleep(5);
            cout << endl;
        }

    }

    lines();
    cout << "\n\n\t";

    system("pause");
    system("cls");
    menu();
}

//Searching for Data --------------------------------------------------------
void deleteContact() {

    headName("Delete contact");

    string keyWord;
    string Delete;

    cout << "\n\tName or Phone Number (Case Sensitive): ";
    getline(cin, keyWord);

    short int searchNum = -1;
    if (keyWord != "") {
        for (short int j = 0; j <= counter; j++) {
            if (keyWord == Contact[j].name || keyWord == Contact[j].phoneNum) {
                searchNum = j;
                break;
            }
        }
        if (searchNum != -1) {

            lines();

            cout << "|" << setw(20) << "Name";
            cout << "|" << setw(13) << "Phone Number";
            cout << "|" << setw(8) << "Gender";
            cout << "|" << setw(28) << "First Mail";
            cout << "|" << setw(28) << "Second Mail" << "|";
            cout << endl;

            lines();
            cout << "|" << setw(20) << Contact[searchNum].name;
            Sleep(5);
            cout << "|" << setw(13) << Contact[searchNum].phoneNum;
            Sleep(5);
            cout << "|" << setw(8) << Contact[searchNum].gender;
            Sleep(5);
            cout << "|" << setw(28) << Contact[searchNum].mail[0];
            Sleep(5);
            cout << "|" << setw(28) << Contact[searchNum].mail[1] << "|";
            Sleep(5);
            cout << endl;
            lines();

            cout << "\n\tDo You Need To Delete This Contact (y/n)? "; getline(cin, Delete);

            if (lowerCase(Delete) == "y" || lowerCase(Delete) == "yes") {
                for (searchNum; searchNum < counter; searchNum++) {
                    Contact[searchNum].name = Contact[searchNum + 1].name;
                    Contact[searchNum].phoneNum = Contact[searchNum + 1].phoneNum;
                    Contact[searchNum].gender = Contact[searchNum + 1].gender;
                    Contact[searchNum].mail[0] = Contact[searchNum + 1].mail[0];
                    Contact[searchNum].mail[1] = Contact[searchNum + 1].mail[1];
                }

                msgView("\033[1m\033[32m", "Deleted Successfully");
                Sleep(900);
                counter--;
                save();
                system("cls");
                menu();
            }
            else {
                system("cls");
                menu();
            }
        }
        else {
            msgView("\033[1m\033[31m", "Sorry, Can't find this contact");
            Sleep(1600);
        }
    }
    else {
        msgView("\033[1m\033[31m", "Wrong Input Value");
        Sleep(1600);
    }

    system("cls");
    menu();
}

//Systematic Functions ------------------------------------------------
string lowerCase(string data) {
    /* data => The Data Got From User
    ---------------------------------
     Lowring "data" 's Characters  */
    for (int i = 0; i < data.length(); i++) {
        if (data[i] >= 65 && data[i] <= 90) {
            data[i] += 32;
        }
    }
    return data;
}

string upperCase(string data) {
    /* data => The Data Got From User
    ---------------------------------
     Uppering "data" 's Characters  */
    for (int i = 0; i < data.length(); i++) {
        if (data[i] >= 97 && data[i] <= 122) {
            data[i] -= 32;
        }
    }
    return data;
}

void lines() {
    for (short int i = 0; i <= 102; i++) {
        cout <<"\033[1m\033[33m"<< "-";
        Sleep(1);
    }
    cout << endl;
}

void lines2() {
    for (short int i = 0; i <= 50; i++) {
        cout <<"\033[1m\033[33m"<< "-";
        Sleep(1);
    }
}                                              

void headName(string name) {
    short int spaces = 102 - name.length() - 2;
    short int left, right;
    if (spaces % 2 == 0) {
        left = spaces / 2;
        right = spaces / 2 + 1;
    }
    else {
        left = spaces / 2 + 1;
        right = spaces / 2 + 1;
    }

    lines();

    cout << "|" << space(left) << "\033[1m\033[36m" << upperCase(name) << "\033[1m\033[33m" << space(right) << "|";

    cout << endl;
    lines();
}

void Beeb() {
    cout << '\a';
}

void msgView(string color, string name) {
    short int spaces = 50 - name.length() - 2;
    short int left, right;
    if (spaces % 2 == 0) {
        left = spaces / 2;
        right = spaces / 2 + 1;
    }
    else {
        left = spaces / 2 + 1;
        right = spaces / 2 + 1;
    }

    lines2();
    Beeb();
    cout << "\n|" << space(left) << color << upperCase(name) << "\033[1m\033[33m" << space(right) << "|\n";

    lines2();
}

void teamView(string color, string name) {
    short int spaces = 50 - name.length() - 2;
    short int left, right;
    if (spaces % 2 == 0) {
        left = spaces / 2;
        right = spaces / 2 + 1;
    }
    else {
        left = spaces / 2 + 1;
        right = spaces / 2 + 1;
    }

    lines2();

    cout << "\n|" << space(left) << color << upperCase(name) << "\033[1m\033[33m" << space(right) << "|\n";

    lines2();
}

string space(int sp) {
    string spaces = "";
    for (int i = 1; i <= sp; i++) {
        spaces += " ";
    }
    return spaces;
} 

void ending() {
    cout << "\n\n\n";
    Beeb();
    headName("Thanks For using our program");
    Sleep(2000);
    exit(1);
}