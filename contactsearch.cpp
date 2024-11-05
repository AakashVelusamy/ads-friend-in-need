#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <math.h>
using namespace std;

#define SKY_BLUE "\033[38;5;32m"
#define WHITE "\033[1;37m"

struct SuffixTreeNode {
    unordered_map<char, SuffixTreeNode*> children;
    unordered_map<string, string> contacts;
};

class ContactManager {
private:
    SuffixTreeNode* root;

    void insertContact(SuffixTreeNode* node, string name, string number, int index) {
        for (int i = index; i < name.size(); i++) {
            char c = tolower(name[i]);
            if (!node->children[c])
                node->children[c] = new SuffixTreeNode();

            node = node->children[c];
            node->contacts[name] = number;
        }
    }

    vector<pair<string, string>> searchSuffix(SuffixTreeNode* node, string query) {
        for (char c : query) {
            c = tolower(c);
            if (!node->children.count(c))
                return {};

            node = node->children[c];
        }

        vector<pair<string, string>> results;
        for (auto& entry : node->contacts)
            results.emplace_back(entry.first, entry.second);

        return results;
    }

    bool deleteContact(SuffixTreeNode* node, string name, int index) {
        if (index == name.size())
            return node->contacts.erase(name) > 0;

        char c = tolower(name[index]);
        if (node->children.find(c) != node->children.end()) {
            bool deleted = deleteContact(node->children[c], name, index + 1);

            if (deleted) {
                SuffixTreeNode* childNode = node->children[c];
                if (childNode->contacts.empty() && childNode->children.empty()) {
                    delete childNode;
                    node->children.erase(c);
                }
            }
            return deleted;
        }

        return false;
    }

public:
    ContactManager() {
        root = new SuffixTreeNode();
    }

    void addContact(string name, string number) {
        if (number.length() != 10) {
            cout << WHITE << "Invalid number. Please enter a 10-digit number." << SKY_BLUE << endl;
            return;
        }
        for (int i = 0; i < name.size(); i++)
            insertContact(root, name, number, i);

        cout << WHITE << "Contact \"" << name << "\" with number \"" << number << "\" added successfully." << SKY_BLUE << endl;
    }

    vector<pair<string, string>> searchContacts(string query) {
        return searchSuffix(root, query);
    }

    void deleteContact(string name) {
        if (deleteContact(root, name, 0))
            cout << WHITE << "Contact \"" << name << "\" deleted successfully." << SKY_BLUE << endl;
        else
            cout << WHITE << "Contact \"" << name << "\" not found." << SKY_BLUE << endl;

    }
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void displayMenu(int choice) {
    clearScreen();
    cout << SKY_BLUE << "=== Contact Management Program ===" << endl << endl;
    char* options[] = {
        "ADD Contact",
        "SEARCH Contact",
        "DELETE Contact",
        "EXIT"
    };

    for (int i = 0; i < 4; i++) {
        if (i == choice)
            cout << WHITE << "- " << options[i] << SKY_BLUE << endl;
        else
            cout << "  " << options[i] << endl;
    }
}

int main() {
    ContactManager cm;

    cm.addContact("AakashVelusamy", "9876543210");
    cm.addContact("AkashK", "8765432109");
    cm.addContact("BDayanitha", "7654321098");
    cm.addContact("CAniruthaSai", "6543210987");
    cm.addContact("DeishaunColinsMartin", "9432187650");
    cm.addContact("DevanandK", "8321098765");
    cm.addContact("DhivyadharshiniR", "7210987654");
    cm.addContact("HarrishR", "6309876542");
    cm.addContact("HarshavardhanG", "9908765431");
    cm.addContact("HarshilBhavikMomaya", "7809876123");
    cm.addContact("JiteshS", "7908765432");
    cm.addContact("KJovishaCurlie", "6901234785");
    cm.addContact("SKabilan", "9109876543");
    cm.addContact("KaniskaC", "8390123456");
    cm.addContact("SKKavinraj", "7245098763");
    cm.addContact("KaviyaSG", "6478901234");
    cm.addContact("KavyaT", "8590123476");
    cm.addContact("KoushikVS", "6832451098");
    cm.addContact("MDeshnaShree", "9475321680");
    cm.addContact("MHaritha", "8312065479");
    cm.addContact("MoneshKumarR", "6987654321");
    cm.addContact("PrathishSM", "9856123047");
    cm.addContact("RakshaPA", "7632098745");
    cm.addContact("RheyaLaurenRajesh", "8234569071");
    cm.addContact("BKRohit", "9801234567");
    cm.addContact("RoshiniR", "8701234567");
    cm.addContact("SangamithraSG", "9567382041");
    cm.addContact("TheesthanS", "6892345170");
    cm.addContact("SaiRakshithaaS", "8712345098");
    cm.addContact("SanchithaM", "6732901485");
    cm.addContact("SantoshRaj", "7532109684");
    cm.addContact("ShivasreeRM", "9345678210");
    cm.addContact("SrivinayK", "6789012345");
    cm.addContact("VaishnaviV", "8321096784");
    cm.addContact("VishnuAravindRG", "9012345678");
    cm.addContact("VishvaVaisnaviN", "6789012345");
    cm.addContact("VithahaselviHaribalajhee", "9801234567");

    int choice = 0;

    while (true) {
        displayMenu(choice);
        int key = getch();

        if (key == 72)
            choice = (choice - 1 + 4) % 4;
        else if (key == 80)
            choice = (choice + 1) % 4;
        else if (key == 13) {
            switch (choice) {
                case 0: {
                    clearScreen();
                    string name, number;
                    cout << WHITE << "Enter the name to add: " << SKY_BLUE;
                    cin.ignore();
                    getline(cin, name);
                    cout << WHITE << "Enter the 10-digit number: " << SKY_BLUE;
                    cin >> number;
                    cm.addContact(name, number);
                    break;
                }
                case 1: {
                    clearScreen();
                    cout << WHITE << "Enter search query: " << SKY_BLUE;
                    string query;
                    query.clear();
                    int count = -1;
                    char ch;
                    while (true) {
                        ch = getch();
                        if (ch == 27) {
                            cout << WHITE << "\nExiting program." << SKY_BLUE << endl;
                            return 0;
                        }
                        else if (ch == '\r') {
                            if (count >= 0) {
                                vector<pair<string, string>> results = cm.searchContacts(query);
                                if (count < results.size()) {
                                    clearScreen();
                                    cout << WHITE << "Name: " << results[count].first << "\nNumber: " << results[count].second << SKY_BLUE << endl;
                                }
                                getch();
                                clearScreen();
                                break;
                            }
                        }
                        else if (ch == 72)
                            count--;
                        else if (ch == 80)
                            count++;
                        else if (ch == 8) {
                            if (!query.empty())
                                query.pop_back();
                            else
                                break;
                        }
                        else {
                            if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) {
                                query += ch;
                                count = 0;
                            }
                        }
                        vector<pair<string, string>> results = cm.searchContacts(query);
                        clearScreen();
                        cout << WHITE << "Enter search query: " << query << SKY_BLUE << endl;

                        if (results.empty())
                            cout << WHITE << "No contacts found." << SKY_BLUE << endl;
                        else {
                            for (int i = 0; i < results.size(); i++) {
                                if (i == count)
                                    cout << WHITE << "- " << results[i].first << SKY_BLUE << endl;
                                else
                                    cout << "  " << results[i].first << endl;
                            }
                        }
                    }
                    break;
                }
                case 2: {
                    clearScreen();
                    string name;
                    cout << WHITE << "Enter the name to delete: " << SKY_BLUE;
                    cin.ignore();
                    getline(cin, name);
                    cm.deleteContact(name);
                    break;
                }
                case 3:
                    cout << WHITE << "Exiting program." << SKY_BLUE << endl;
                    return 0;
            }
        }
    }
}
