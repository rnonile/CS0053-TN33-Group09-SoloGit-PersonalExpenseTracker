
// ! Important note (Red)
// ? Question or reminder (Blue)
// TODO: Task to be completed (Orange)
// * Highlighted information (Green)

#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

// * Structure to store expense details
struct Expense {
    int expenseID;
    string date;
    string category;
    double amount;
    string description;
};

// * Global vector for storing all expenses
vector<Expense> expenses;

// TODO: Improve file error handling
void saveExpenses() {
    ofstream out("expenses.txt");

    for (const auto& exp : expenses) {
        out << exp.expenseID << " "
            << exp.date << " "
            << exp.category << " "
            << exp.amount << "\n";
        out << exp.description << "\n";
    }
}

// * Load all expenses from the text file
void loadExpenses() {
    ifstream in("expenses.txt");
    Expense exp;

    while (in >> exp.expenseID >> exp.date >> exp.category >> exp.amount) {
        in.ignore();

        // ? Why use getline() here?
        // * Because descriptions may contain spaces.
        getline(in, exp.description);

        expenses.push_back(exp);
    }
}

// ! Main function for adding a new expense record
void addExpense() {
    Expense exp;

    cout << "\n--- Add Expense ---\n";

    cout << "Enter ID: ";
    cin >> exp.expenseID;

    cout << "Enter Date [YYYY-MM-DD]: ";
    cin >> exp.date;

    cout << "Enter Category: ";
    cin >> ws;
    getline(cin, exp.category);

    cout << "Enter Amount: ";
    cin >> exp.amount;

    // * Clear input buffer before reading description
    cin.ignore();

    cout << "Enter Description: ";
    getline(cin, exp.description);

    expenses.push_back(exp);

    // ! Automatically save after adding
    saveExpenses();

    cout << "\nExpense Successfully Added!\n";
}

// * Display all recorded expenses
void viewExpenses() {
    if (expenses.empty()) {

        // ! No records available
        cout << "\nExpenses not found.\n";
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

// * Display menu options
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

// ! Search expenses by category
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

        // ! Category does not exist in records
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

// ! Delete an expense using its ID
void deleteExpense() {

    if (expenses.empty()) {
        cout << "\nNo expenses available to delete.\n";
        return;
    }

    int idToDelete;
    cout << "\nEnter the ID of the expense to delete: ";
    cin >> idToDelete;

    bool found = false;

    for (auto it = expenses.begin(); it != expenses.end(); ++it) {

        if (it->expenseID == idToDelete) {

            cout << "\nExpense Found:";
            cout << "\nID: " << it->expenseID
                 << "\nDate: " << it->date
                 << "\nCategory: " << it->category
                 << "\nAmount: " << it->amount
                 << "\nDescription: " << it->description
                 << "\n";

            char confirm;
            cout << "\nAre you sure you want to delete this expense? (Y/N): ";
            cin >> confirm;

            if (confirm == 'Y' || confirm == 'y') {

                expenses.erase(it);

                // * Save changes to file after deletion
                saveExpenses();

                cout << "\nExpense Successfully Deleted!\n";
            }
            else {
                cout << "\nDeletion cancelled.\n";
            }

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nExpense with ID " << idToDelete << " not found.\n";
    }
}

int main() {

    // ! Load saved expenses before starting the program
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
                deleteExpense();
                break;

            case 6:
                // TODO: Implement Summary Report feature
                cout << "\n[Feature coming soon: Summary Report]\n";
                break;

            case 7:
                cout << "\nExiting program. Goodbye!\n";
                break;

            default:

                // ! Handle invalid user input
                cout << "\nInvalid choice! Please try again.\n";

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
        }
    }

    return 0;
}