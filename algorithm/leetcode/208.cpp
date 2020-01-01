#include <string>
#include <iostream>
using namespace std;

class Trie {
private:
    static const int N = 26;
    struct Node {
        struct Node* children[N] = {};
        int val = 0;
    };

    Node root;
public:
    /** Initialize your data structure here. */
    Trie() {
        
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Node* p = &root;
        for (char ch : word) {
            Node* t = p->children[ch-'a'];
            if (t == nullptr) {
                t = new Node();
                p->children[ch-'a'] = t;
            }
            p = t;
        }  
        p->val = 1;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Node* p = &root;
       for (char ch : word) {
           p = p->children[ch - 'a'];
           if (p == nullptr) {
               return false;
           }
       } 
       return p->val == 1;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
       Node* p = &root;
       for (char ch : prefix) {
           p = p->children[ch - 'a'];
           if (p == nullptr) {
               return false;
           }
       } 
       return true;
    }
};

int main() {
    Trie* trie = new Trie();
    trie->insert("ab");
    bool exists = trie->search("a");
    bool hasprefix = trie->startsWith("a");
    cout<<"exists = " << exists <<", hasprefix = " << hasprefix << endl;

    return 0;
}
