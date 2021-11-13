#include <iostream>
#include <string>
#include <time.h>
#include <sstream>

template<typename T>
class Bst {
public:
    struct node {
        T data;
        node *left, *right, *parent;
        node() {
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }
    };

    Bst() {
        size = 0;
        root = nullptr;
    }

    ~Bst() {
        delete_all();
    }

    int tmp_get_size() {
        return size;
    }

    void add_node(const T& data) {
        node* n = new node();
        n->data = data;
        if (size == 0) {
            root = n;
        }
        else {
            node* ptr = root;
            while (ptr) {
                n->parent = ptr;
                if (ptr->data < n->data) {
                    ptr = ptr->right;
                }
                else {
                    ptr = ptr->left;
                }
            }
            if (n->parent->data < data) {
                n->parent->right = n;
            }
            else {
                n->parent->left = n;
            }
            
        }
        size++;
    }

    node* find_node(const T& data) {
       return find_node(data, root);
    }

    node* find_node(const T& data, node* ptr) {

        if (ptr) {
            if (ptr->data == data) {
                //std::cout << ptr->data << std::endl; //testing purposes
                return ptr;
            }

            if (ptr->data < data) {
                find_node(data, ptr->right);
            }
            else {
                find_node(data, ptr->left);
            }
        }
        else {
            return nullptr;
        }
    }

    void delete_node(const T& data) {
        if (root == nullptr) {
            return;
        }
        node* n = find_node(data, root);
        //todo
    
    }

    void preorder_traversal() { preorder_traversal(root); }
    void preorder_traversal(node* n) {
        if (n) {
            std::cout << n->data << std::endl;
            preorder_traversal(n->left);
            preorder_traversal(n->right);
            //todo display method
        }
    }

    void inorder_traversal() { inorder_traversal(root); }
    void inorder_traversal(node* n) {
        if (n) {
            inorder_traversal(n->left);
            std::cout << n->data << std::endl;
            inorder_traversal(n->right);
            //todo display method
        }
    }

    void delete_all() { delete_all(root); }
    void delete_all(node* n) {
        if (size == 0) {
            return;
        }
        else {
            if (n == nullptr) {
                return;
            }
            delete_all(n->left);
            delete_all(n->right);
            //std::cout << "Deleting node: " << n->data << std::endl; //testing purposes

            delete n;
            size--;
        }
        
    }

    int get_height() {
        //todo
    }

    /*
    string display_tree(unsigned int n = 0) { 
        ostringstream output;

        //todo

    }*/

private:
    unsigned int size;
    node* root;
};

struct BstData {
    int d1;
    char d2;
    BstData() {
        d1 = 1;
        d2 = 'a';
    }
};

std::ostream& operator << (std::ostream& out, const BstData& obj) {
    out << "{d1: " << obj.d1 << std::endl << "d2: " << obj.d2 << "}";
    return out;
}

bool operator < (const BstData& a, const BstData& b) {
    return a.d1 < b.d1 || a.d1 == b.d1 && a.d2 < b.d2;
}
bool operator > (const BstData& a, const BstData& b) {
    return a.d1 > b.d1 || a.d1 == b.d1 && a.d2 > b.d2;
}

bool operator ==(const BstData& a, const BstData& b) {
    return (!(a < b) && !(b < a));
}


int main()
{
    Bst<BstData>* bst = new  Bst<BstData>();
    BstData data;
    const int order = 3;
    const int n = pow(10, order);

    for (int i = 0; i < n; i++) {
        data.d1 = rand() % 100;
        data.d2 = 'a' + rand() % 26;
        bst->add_node(data);
    }
    std::cout << bst->tmp_get_size() << std::endl;
    bst->delete_all();
    std::cout << bst->tmp_get_size() << std::endl;


    delete bst;
    system("pause");
}

