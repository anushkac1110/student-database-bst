#include <iostream>
using namespace std;

struct Node {
    int roll;
    string name;
    int marks;
    Node* left;
    Node* right;
};

Node* createNode(int roll, string name, int marks) {
    Node* newNode = new Node();
    newNode->roll = roll;
    newNode->name = name;
    newNode->marks = marks;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert
Node* insert(Node* root, int roll, string name, int marks) {
    if (root == NULL)
        return createNode(roll, name, marks);

    if (roll < root->roll)
        root->left = insert(root->left, roll, name, marks);
    else if (roll > root->roll)
        root->right = insert(root->right, roll, name, marks);

    return root;
}

// Search
Node* search(Node* root, int roll) {
    if (root == NULL || root->roll == roll)
        return root;

    if (roll < root->roll)
        return search(root->left, roll);
    return search(root->right, roll);
}

// Find minimum node
Node* findMin(Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Delete
Node* deleteNode(Node* root, int roll) {
    if (root == NULL) return root;

    if (roll < root->roll)
        root->left = deleteNode(root->left, roll);
    else if (roll > root->roll)
        root->right = deleteNode(root->right, roll);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->roll = temp->roll;
        root->name = temp->name;
        root->marks = temp->marks;
        root->right = deleteNode(root->right, temp->roll);
    }
    return root;
}

// Traversals
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << "Roll: " << root->roll << ", Name: " << root->name
             << ", Marks: " << root->marks << endl;
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root != NULL) {
        cout << "Roll: " << root->roll << ", Name: " << root->name
             << ", Marks: " << root->marks << endl;
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        cout << "Roll: " << root->roll << ", Name: " << root->name
             << ", Marks: " << root->marks << endl;
    }
}

// Find highest and lowest marks
void findMinMaxMarks(Node* root, int &minM, int &maxM) {
    if (root == NULL) return;

    if (root->marks < minM) minM = root->marks;
    if (root->marks > maxM) maxM = root->marks;

    findMinMaxMarks(root->left, minM, maxM);
    findMinMaxMarks(root->right, minM, maxM);
}

int countNodes(Node* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int main() {
    Node* root = NULL;
    int choice;

    do {
        cout << "\n--- Student Database using BST ---\n";
        cout << "1. Insert student\n";
        cout << "2. Search student\n";
        cout << "3. Delete student\n";
        cout << "4. Display Inorder\n";
        cout << "5. Display Preorder\n";
        cout << "6. Display Postorder\n";
        cout << "7. Find highest & lowest marks\n";
        cout << "8. Count total students\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        int roll, marks;
        string name;

        switch (choice) {
            case 1:
                cout << "Enter roll number: ";
                cin >> roll;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter marks: ";
                cin >> marks;
                root = insert(root, roll, name, marks);
                cout << "Student inserted.\n";
                break;

            case 2:
                cout << "Enter roll to search: ";
                cin >> roll;
                {
                    Node* result = search(root, roll);
                    if (result)
                        cout << "Found: " << result->name << ", Marks: " << result->marks << endl;
                    else
                        cout << "Student not found.\n";
                }
                break;

            case 3:
                cout << "Enter roll to delete: ";
                cin >> roll;
                root = deleteNode(root, roll);
                cout << "Student deleted (if existed).\n";
                break;

            case 4:
                cout << "\nInorder Traversal:\n";
                inorder(root);
                break;

            case 5:
                cout << "\nPreorder Traversal:\n";
                preorder(root);
                break;

            case 6:
                cout << "\nPostorder Traversal:\n";
                postorder(root);
                break;

            case 7: {
                if (root == NULL) {
                    cout << "No students in database.\n";
                    break;
                }
                int minM = 1000, maxM = -1;
                findMinMaxMarks(root, minM, maxM);
                cout << "Lowest Marks: " << minM << endl;
                cout << "Highest Marks: " << maxM << endl;
                break;
            }

            case 8:
                cout << "Total students: " << countNodes(root) << endl;
                break;

            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
