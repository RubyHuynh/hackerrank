/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

struct Node {
    Node* left;
    Node* right;
    int   val;

    Node(int value) : left(NULL), right(NULL), val(value) {
        
    }
    
    ~Node() {
        
    }
    
    void insert(int value) {
        printf("%s %d vs %d\n", __func__, value, this->val);
        Node** locate = value < this->val ? &this->left : &this->right;
        if (!*locate) {
            *locate = new Node(value);
            printf("\tinserted\n");
        }
        else {
            (*locate)->insert(value);
        }
    }
    
    Node* find(int value) {
        printf("%s %d vs %d\n", __func__, value, this->val);
        Node** locate = NULL;
        if (value == this->val) {
            printf("\tfound\n");
            return this;
        }
        else {
            locate = value < this->val ? &this->left : &this->right;
            if (!*locate) {
                printf("\tnot found\n");
                return NULL;
            }
        }
        return (*locate)->find(value);
    }
    
    void dump() {
        if (this->left) this->left->dump();
        printf("%d ", this->val);
        if (this->right) this->right->dump();
    }
};

int main()
{
    printf("binary tree\n");
    Node* root = new Node(9);
    root->insert(7);
    root->insert(25);
    root->insert(12);
    root->insert(3);
    printf("\n-------------\n");
    root->dump();
    printf("\n-------------\n");
    root->find(12);
    root->find(8);
    return 0;
}
/*
binary tree
insert 7 vs 9
        inserted
insert 25 vs 9
        inserted
insert 12 vs 9
insert 12 vs 25
        inserted
insert 3 vs 9
insert 3 vs 7
        inserted

-------------
3 7 9 12 25 
-------------
find 12 vs 9
find 12 vs 25
find 12 vs 12
        found
find 8 vs 9
find 8 vs 7
        not found
*/
