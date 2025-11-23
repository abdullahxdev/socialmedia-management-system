#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct User {
    string name;
    int age;
    string dateOfBirth;
    string dateOfJoining;
    int totalPosts;
    int totalImpressions;
    int followers;
    int following;
    double avgDailyTimeSpent;
    double avgDailyPosts;
    string gender;
    string country;
    string accountType;
    string verified;
    User* next; 
};

struct QueueNode {
    string data;
    QueueNode* next;
};

struct Queue {
    QueueNode* front;
    QueueNode* rear;
    
    Queue() {
        front = NULL;
        rear = NULL;
    }

    void enqueue(string data) {
        QueueNode* newNode = new QueueNode;
        newNode->data = data;
        newNode->next = NULL;
        if (rear == NULL) {
            front = newNode;
            rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (front == NULL) {
            return;
        }
        QueueNode* temp = front;
        front = front->next;
        if (front == NULL) {
            rear = NULL;
        }
        delete temp;
    }

    bool isEmpty() {
        return front == NULL;
    }

    string peek() {
        if (rear != NULL) {
            return front->data;
        }
        return "";
    }

    void display() {
        QueueNode* temp = front;
        while (temp != NULL) {
            cout << temp->data << endl;
            temp = temp->next;
        }
    }
};

struct BSTNode {
    int key;
    vector<string> users;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int k, string user) {
        key = k;
        users.push_back(user);
        left = NULL;
        right = NULL;
    }
};

struct BST {
    BSTNode* root;

    BST() {
        root = NULL;
    }

    void insert(int key, string user) {
        root = insertRec(root, key, user);
    }

    BSTNode* insertRec(BSTNode* node, int key, string user) {
        if (node == NULL) {
            return new BSTNode(key, user);
        }

        if (key < node->key) {
            node->left = insertRec(node->left, key, user);
        } else if (key > node->key) {
            node->right = insertRec(node->right, key, user);
        } else {
            node->users.push_back(user);
        }

        return node;
    }

    void display() {
        inOrder(root);
    }

    void inOrder(BSTNode* node) {
        if (node == NULL) {
            return;
        }
        inOrder(node->left);
        cout << node->key << ": ";
        for (string user : node->users) {
            cout << user << " ";
        }
        cout << endl;
        inOrder(node->right);
    }
};

User* head = NULL; 
Queue supportQueue; 
vector<pair<int, string>> userHeap; 
BST followersBST; 
vector<pair<string, vector<string>>> userGraph; 

void addNode(string name, int age, string dateOfBirth, string dateOfJoining,
             int totalPosts, int totalImpressions, int followers, int following,
             double avgDailyTimeSpent, double avgDailyPosts, string gender,
             string country, string accountType, string verified) {
    User* newNode = new User;
    newNode->name = name;
    newNode->age = age;
    newNode->dateOfBirth = dateOfBirth;
    newNode->dateOfJoining = dateOfJoining;
    newNode->totalPosts = totalPosts;
    newNode->totalImpressions = totalImpressions;
    newNode->followers = followers;
    newNode->following = following;
    newNode->avgDailyTimeSpent = avgDailyTimeSpent;
    newNode->avgDailyPosts = avgDailyPosts;
    newNode->gender = gender;
    newNode->country = country;
    newNode->accountType = accountType;
    newNode->verified = verified;
    newNode->next = head;
    head = newNode;

    userHeap.push_back(make_pair(totalImpressions, name));
    sort(userHeap.rbegin(), userHeap.rend());
    followersBST.insert(followers, name);
    bool found = false;
    for (auto& pair : userGraph) {
        if (pair.first == name) {
            found = true;
            break;
        }
    }
    if (!found) {
        userGraph.push_back(make_pair(name, vector<string>()));
    }
}

void addSupportRequest() {
    string request;
    cout << "Enter your support request: ";
    cin.ignore();
    getline(cin, request);
    supportQueue.enqueue(request);
    cout << "Support request added.\n";
}

void viewSupportRequests() {
    if (supportQueue.isEmpty()) {
        cout << "No support requests in the queue.\n";
    } else {
        cout << "Support requests in the queue:\n";
        supportQueue.display();
    }
}

void processSupportRequest() {
    if (supportQueue.isEmpty()) {
        cout << "No support requests in the queue.\n";
    } else {
        cout << "Processing request: " << supportQueue.peek() << "\n";
        supportQueue.dequeue();
    }
}

void displayTopUserByImpressions() {
    if (userHeap.size() > 0) {
        pair<int, string> topUser = userHeap[0];
        cout << "Top user by impressions: " << topUser.second << " with " << topUser.first << " impressions.\n";
    } else {
        cout << "No users to display.\n";
    }
}

void displayUsersByFollowers() {
    cout << "Users ranked by followers:\n";
    followersBST.display();
}

void addFollowerConnection(string follower, string followee) {
    bool found = false;
    for (auto& pair : userGraph) {
        if (pair.first == follower) {
            pair.second.push_back(followee);
            cout << follower << " now follows " << followee << ".\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Follower not found.\n";
    }
}

void displayConnections() {
    cout << "User connections:\n"; 
    for (auto& pair : userGraph) {
        cout << pair.first << " follows: ";
        for (string followee : pair.second) {
            cout << followee << " ";
        }
        cout << "\n";
    }
}

void searchUser(string name) {
    bool found = false;
    User* temp = head;
    while (temp != NULL) {
        if (temp->name.find(name) != string::npos) {
            found = true;
            cout << "User found:\n";
            cout << "Name: " << temp->name << "\n";
            cout << "Age: " << temp->age << "\n";
            cout << "Followers: " << temp->followers << "\n";
            cout << "Following: " << temp->following << "\n";
            cout << "----------------------\n";
        }
        temp = temp->next;
    }
    if (!found) {
        cout << "User not found.\n";
    }
}

void displayUsers() {
    User* temp = head;
    while (temp != NULL) {
        cout << "Name: " << temp->name << "\n";
        cout << "Age: " << temp->age << "\n";
        cout << "Followers: " << temp->followers << "\n";
        cout << "Following: " << temp->following << "\n";
        cout << "----------------------\n";
        temp = temp->next;
    }
}

void addUser() {
    string name, dateOfBirth, dateOfJoining, gender, country, accountType, verified;
    int age, totalPosts, totalImpressions, followers, following;
    double avgDailyTimeSpent, avgDailyPosts;

    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter age: ";
    cin >> age;
    cout << "Enter date of birth (YYYY-MM-DD): ";
    cin >> dateOfBirth;
    cout << "Enter date of joining (YYYY-MM-DD): ";
    cin >> dateOfJoining;
    cout << "Enter total posts: ";
    cin >> totalPosts;
    cout << "Enter total impressions: ";
    cin >> totalImpressions;
    cout << "Enter followers: ";
    cin >> followers;
    cout << "Enter following: ";
    cin >> following;
    cout << "Enter average daily time spent (hours): ";
    cin >> avgDailyTimeSpent;
    cout << "Enter average daily posts: ";
    cin >> avgDailyPosts;
    cout << "Enter gender: ";
    cin >> gender;
    cout << "Enter country: ";
    cin >> country;
    cout << "Enter account type: ";
    cin >> accountType;
    cout << "Enter verified status (yes/no): ";
    cin >> verified;

    addNode(name, age, dateOfBirth, dateOfJoining, totalPosts, totalImpressions, followers, following,
            avgDailyTimeSpent, avgDailyPosts, gender, country, accountType, verified);
    cout << "User added successfully.\n";
}

int main() {
    ifstream fin("socialmediadataset.csv"); 
    string line;
    vector<string> lineData;
    int lines = 0;

    while (getline(fin, line)) {
        stringstream s(line);
        string word;
        while (getline(s, word, ',')) {
            lineData.push_back(word);
        }

        if (lines != 0 && lineData.size() >= 14) {
            int age = stoi(lineData[1]);
            int totalPosts = stoi(lineData[4]);
            int totalImpressions = stoi(lineData[5]);
            int followers = stoi(lineData[6]);
            int following = stoi(lineData[7]);
            double avgDailyTimeSpent = stod(lineData[8]);
            double avgDailyPosts = stod(lineData[9]);

            addNode(lineData[0], age, lineData[2], lineData[3], totalPosts, totalImpressions,
                    followers, following, avgDailyTimeSpent, avgDailyPosts, lineData[10],
                    lineData[11], lineData[12], lineData[13]);
        }
        lineData.clear();
        lines++;
    }
    fin.close();

    int choice;
    do {
        cout << "***************************************\n";
        cout << "Social Media App Management System\n";
        cout << "***************************************\n";
        cout << "Menu:\n";
        cout << "1. Add Support Request\n";
        cout << "2. View Support Requests\n";
        cout << "3. Process Support Request\n";
        cout << "4. Display Top User by Impressions\n";
        cout << "5. Display Users by Followers\n";
        cout << "6. Add Follower Connection\n";
        cout << "7. Display Connections\n";
        cout << "8. Search User\n";
        cout << "9. Display All Users\n";
        cout << "10. Add new User\n";
        cout << "11. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addSupportRequest();
                break;
            case 2:
                viewSupportRequests();
                break;
            case 3:
                processSupportRequest();
                break;
            case 4:
                displayTopUserByImpressions();
                break;
            case 5:
                displayUsersByFollowers();
                break;
            case 6: {
                string follower, followee;
                cout << "Enter follower's name: ";
                cin.ignore();
                getline(cin, follower);
                cout << "Enter followee's name: ";
                getline(cin, followee);
                addFollowerConnection(follower, followee);
                break;
            }
            case 7:
                displayConnections();
                break;
            case 8: {
                string name;
                cout << "Enter user's name to search: ";
                cin >> name;
                searchUser(name);
                break;
            }
            case 9:
                displayUsers();
                break;
            case 10:
                addUser();
                break;
            case 11:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 11);

    return 0;
}
