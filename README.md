# Social Media Data Structures Project

This project is a C++ implementation of a miniature social media management system that uses multiple **Data Structures** including:

* **Linked Lists**
* **Stacks**
* **Queues**
* **Binary Search Trees (BST)**
* **Heaps (Max Heap)**
* **Graphs**
* **Hash Maps / Unordered Maps**

The project loads data from a CSV-based dataset and provides various operations through a **menu-driven interface**.

---

## 🚀 Features Implemented

### **1. Load Social Media Dataset**

Automatically loads and parses the CSV file using:

* `<fstream>` for file handling
* `<sstream>` for splitting CSV fields

### **2. Add New User (Linked List)**

Stores new users in a singly linked list. Each node contains:

* Name
* Age
* Country
* Followers
* Impressions

### **3. Search User (Linked List or BST option)**

Search by:

* Exact Name (Linked List search)
* Age (BST search)

### **4. Delete User (Linked List)**

Deletes user by name from the linked list.

### **5. Display All Users**

Prints all user data from the linked list.

### **6. Country-Based User Search (Hash Map)**

Uses `unordered_map<string, vector<User*>>` to show users from a specific country.

### **7. Top Users by Impressions (Max Heap)**

Displays the top N users based on impressions.

### **8. User Network Graph (Graph / Adjacency List)**

Graph stores follower relationships.
Supports:

* Display network
* Mutual connections check

### **9. Recent User Queue (Queue)**

Stores last 10 searched users.

### **10. Undo Last Action (Stack)**

Undo operations like last added or deleted user.

---

## 📁 Project File Structure

```
📦 SocialMedia-DataStructures-Project
 ┣ 📄 main.cpp
 ┣ 📄 socialmediadataset.csv
 ┣ 📄 README.md
 ┗ 📁 build (optional)
```

---

## 🛠️ Technologies Used

### **Language:**

* C++

### **Libraries:**

* `<iostream>`
* `<fstream>`
* `<sstream>`
* `<vector>`
* `<unordered_map>`
* `<queue>`
* `<stack>`
* `<map>`
* `<set>`
* `<string>`

---

## 📌 Data Structures & Their Purpose

| Data Structure | Feature Used For           |
| -------------- | -------------------------- |
| Linked List    | Add/Search/Delete user     |
| Stack          | Undo last action           |
| Queue          | Recent user history        |
| BST            | Search users by age        |
| Max Heap       | Top impressions ranking    |
| Graph          | Follower-following network |
| Hash Map       | Country-wise user search   |

---

## 🔧 How to Run the Project

### **1. Compile the Program**

```
g++ main.cpp -o socialapp
```

### **2. Run**

```
./socialapp
```

Make sure the CSV file (`socialmediadataset.csv`) is in the same folder as `main.cpp`.

---

## 📊 Dataset Used

The dataset contains fields such as:

* Name
* Age
* Country
* Followers
* Following
* Total Posts
* Impressions
* Account Type

(Modified to remove last names and converted float fields to integers.)

---

## 🎯 Future Enhancements

Some ideas to expand your project:

* Dijkstra shortest path for influence reach
* Trie for autocomplete search
* Min-heap for least active users
* Content recommendation system
* AVL tree for balanced performance

---

## 🤝 Contribution

Feel free to fork the repo and submit pull requests.

---

## 📄 License

This project is open-source under the MIT License.

---
