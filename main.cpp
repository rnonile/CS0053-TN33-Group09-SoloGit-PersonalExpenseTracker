
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
#include <map>

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
// * Save expenses to file safely (using a delimiter)
void saveExpenses() {
    ofstream out("expenses.txt");

    for (const auto& exp : expenses) {
        // Using a pipe '|' to separate fields so categories with spaces
        out << exp.expenseID << "|"
            << exp.date << "|"
            << exp.category << "|"
            << exp.amount << "|"
            << exp.description << "\n";
    }
    out.close();
}

// * Load all expenses from the text file safely
void loadExpenses() {
    ifstream in("expenses.txt");
    if (!in.is_open()) return; 

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);
        size_t pos4 = line.find('|', pos3 + 1);

        if (pos1 != string::npos && pos2 != string::npos && 
            pos3 != string::npos && pos4 != string::npos) {
            
            Expense exp;
            exp.expenseID = stoi(line.substr(0, pos1));
            exp.date = line.substr(pos1 + 1, pos2 - pos1 - 1);
            exp.category = line.substr(pos2 + 1, pos3 - pos2 - 1);
            exp.amount = stod(line.substr(pos3 + 1, pos4 - pos3 - 1));
            exp.description = line.substr(pos4 + 1);

            expenses.push_back(exp);
        }
    }
    in.close();
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
// * Generate summary report
void summaryReport() {

    if (expenses.empty()) {
        cout << "\nNo expenses available.\n";
        return;
    }

    double total = 0;
    double highest = expenses[0].amount;
    double lowest = expenses[0].amount;

    map<string, double> categoryTotals;

    for (const auto& exp : expenses) {

        total += exp.amount;

        categoryTotals[exp.category] += exp.amount;

        if (exp.amount > highest)
            highest = exp.amount;

        if (exp.amount < lowest)
            lowest = exp.amount;
    }

    double average = total / expenses.size();

    cout << "\n====================================";
    cout << "\n SUMMARY REPORT";
    cout << "\n====================================";

    cout << "\nTotal Expenses Recorded : "
         << expenses.size();

    cout << fixed << setprecision(2);

    cout << "\nTotal Amount Spent : P"
         << total;

    cout << "\nAverage Expense Amount : P"
         << average;

    cout << "\nHighest Expense : P"
         << highest;

    cout << "\nLowest Expense : P"
         << lowest;

    cout << "\n\n--- Expenses by Category ---\n";

    for (const auto& category : categoryTotals) {
        cout << category.first
             << " : P"
             << category.second
             << endl;
    }

    cout << "====================================\n";
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
                summaryReport();
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