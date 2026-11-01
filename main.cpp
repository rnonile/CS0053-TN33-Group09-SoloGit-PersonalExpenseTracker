#include <iostream>
#include <vector>
#include <limits>
#include <String>
#include <fstream>
#include <iomanip>

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

void searchExpenses() {
   if (expenses.empty()) {
        cout << "\nNo expenses available to search.\n";
        return;
    }

    string searchCategory;
    cout << "\nEnter Category to filter by: ";
    cin >> searchCategory;

    bool found = false;
    cout << "\n--- Filtered Expenses (" << searchCategory << ") ---\n";
    for (const auto& exp : expenses) {
        if (exp.category == searchCategory) {
            cout << "\nID: " << exp.expenseID
                 << "\nDate: " << exp.date
                 << "\nCategory: " << exp.category
                 << "\nAmount: $" << fixed << setprecision(2) << exp.amount
                 << "\nDescription: " << exp.description
                 << "\n---------------------\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No expenses found matching that category.\n";
    }
}

void updateExpense() {
    if (expenses.empty()) {
        cout << "\nNo expenses available to update.\n";
        return;
    }

    int idToUpdate;
    cout << "\nEnter the ID of the expense to update: ";
    cin >> idToUpdate;

    bool found = false;
    for (auto& exp : expenses) {
        if (exp.expenseID == idToUpdate) {
            found = true;

            cout << "\n--- Update Expense ---\n";
            cout << "Current Date: " << exp.date << "\nEnter new Date [YYYY-MM-DD] (or press Enter to keep current): ";
            string newDate;
            cin.ignore();
            getline(cin, newDate);
            if (!newDate.empty()) {
                exp.date = newDate;
            }

            cout << "Current Category: " << exp.category << "\nEnter new Category (or press Enter to keep current): ";
            string newCategory;
            getline(cin, newCategory);
            if (!newCategory.empty()) {
                exp.category = newCategory;
            }

            cout << "Current Amount: " << exp.amount << "\nEnter new Amount (or press Enter to keep current): ";
            string newAmountStr;
            getline(cin, newAmountStr);
            if (!newAmountStr.empty()) {
                exp.amount = stod(newAmountStr);
            }

            cout << "Current Description: " << exp.description << "\nEnter new Description (or press Enter to keep current): ";
            string newDescription;
            getline(cin, newDescription);
            if (!newDescription.empty()) {
                exp.description = newDescription;
            }

            saveExpenses(); // Save updated expenses to file
            cout << "\nExpense Successfully Updated!\n";
            break;
        }
    }

    if (!found) {
        cout << "\nExpense with ID " << idToUpdate << " not found.\n";
    }
}

int main() {

    loadExpenses();

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
                searchExpenses();
                break;

            case 4:
                updateExpense();
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