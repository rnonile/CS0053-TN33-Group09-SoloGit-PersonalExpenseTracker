#include <iostream>
#include <vector>
#include <limits>
#include <String>
#include <fstream>

using namespace std;

struct Expense {
    int expenseID;
    string date;
    string category;
    double amount;
    string description;
};

// Global vector for storing expenses
vector<Expense> expenses;

void saveExpenses(){
    ofstream out("expenses.txt");

    for (const auto& exp : expenses) {
        out << exp.expenseID << " "
            << exp.date << " "
            << exp.category << " "
            << exp.amount << "\n";
        out << exp.description << "\n";
    }
}

// Load all expenses from expenses.txt (if it exists)
void loadExpenses() {
    ifstream in("expenses.txt");
    Expense exp;

    while (in >> exp.expenseID >> exp.date >> exp.category >> exp.amount) {
        in.ignore();                   // skip the newline after amount
        getline(in, exp.description);  // description is the whole next line
        expenses.push_back(exp);
    }
}


void addExpense() {
    Expense exp;

    cout << "\n--- Add Expense ---\n";

    cout << "Enter ID: ";
    cin >> exp.expenseID;

    cout << "Enter Date [YYYY-MM-DD]: ";
    cin >> exp.date;

    cout << "Enter Category: ";
    cin >> exp.category;

    cout << "Enter Amount: ";
    cin >> exp.amount;

    cin.ignore();

    cout << "Enter Description: ";
    getline(cin, exp.description);

    expenses.push_back(exp);
    saveExpenses();   // Save to file

    cout << "\nExpense Successfully Added!\n";
}

void viewExpenses() {
    if (expenses.empty()) {
        cout << "\nExpenses no found.\n";
        return;
    }

    cout << "\n--- All Expenses ---\n";

    for (const auto& exp : expenses) {
        cout << "\nID: " << exp.expenseID
             << "\nDate: " << exp.date
             << "\nCategory: " << exp.category
             << "\nAmount: " << exp.amount
             << "\nDescription: " << exp.description
             << "\n---------------------\n";
    }
}

void choices() {
    cout << "\n=== Personal Expense Tracker ===" << endl;
    cout << "Expense Tracker Menu:" << endl;
    cout << "1. Add Expense" << endl;
    cout << "2. View All Expenses" << endl;
    cout << "3. Search / Filter Expenses" << endl;
    cout << "4. Update an Expense" << endl;
    cout << "5. Delete an Expense" << endl;
    cout << "6. Summary Report" << endl;
    cout << "7. Exit" << endl;
}

int main() {

    int choice = 0;

    while (choice != 7) {

        choices();

        cout << "Enter your choice (1-7): ";
        cin >> choice;

        switch (choice) {

            case 1:
                addExpense();
                break;

            case 2:
                viewExpenses();
                break;

            case 3:
                cout << "\n[Feature coming soon: Search / Filter Expenses]\n";
                break;

            case 4:
                cout << "\n[Feature coming soon: Update an Expense]\n";
                break;

            case 5:
                cout << "\n[Feature coming soon: Delete an Expense]\n";
                break;

            case 6:
                cout << "\n[Feature coming soon: Summary Report]\n";
                break;

            case 7:
                cout << "\nExiting program. Goodbye!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
        }
    }

    return 0;
}