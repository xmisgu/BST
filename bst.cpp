#include <iostream>
#include <time.h>
#include <sstream>
#include <string>


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
    int get_size() {
        return size;
    }
    node* get_root() {
        return root;
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
                //std::cout << ptr->data << std::endl; //do testow
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
            std::cout << n->data << std::endl; //do testow
            preorder_traversal(n->left);
            preorder_traversal(n->right);
            //todo display method
        }
    }

    void inorder_traversal() { inorder_traversal(root); }
    void inorder_traversal(node* n) {
        if (n) {
            inorder_traversal(n->left);
            std::cout << n->data << std::endl; //do testow
            inorder_traversal(n->right);
            //todo display method
        }
    }

    void delete_all(node* n) {
            if (!n) {
                return;
            }
            delete_all(n->left);
            delete_all(n->right);
            //std::cout << "Deleting node: " << n->data << std::endl; //do testow
            delete n;
            size--;     
    }

    int get_height() { return get_height(root); }
    int get_height(node* n) {
        if (!n)
            return 0;
        else if (size == 1) {
            return 1;
        }
        return 1 + std::max(get_height(n->left), get_height(n->right));
    }

    std::string tree_traversal_to_string(node* n) {
        std::ostringstream output;
        if (n) {
            std::ostringstream p;
            std::ostringstream r;
            std::ostringstream l;
            if (n->parent) {
                p << (n->parent->data);
            }
            else {
                p << "NULL";
            }

            if (n->left) {
                l << n->left->data;
            }
            else {
                l << "NULL";
            }

            if (n->right) {
                r << n->right->data;
            }
            else {
                r << "NULL";
            }

            output << "([parent: " << p.str() << ", left child: " << l.str() << ", right child: " << r.str() << "], data: " << n->data << ")," << std::endl;  
            output << tree_traversal_to_string(n->left);
            output << tree_traversal_to_string(n->right);
            
        }
        return output.str();
    }
    std::string display_tree() { 
        std::ostringstream output;
        output << "Ilosc elementow: " << size << std::endl;
        //output << "Wysokosc drzewa: " << get_height() << std::endl;
        if (size > 0 && size <= 20) {
            output << tree_traversal_to_string(root);
        }
        return output.str();
    }

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
    out << "{d1: " << obj.d1 << ", d2: " << obj.d2 << "}";
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
    Bst<BstData>* bst = new Bst<BstData>();
    BstData data;
    const int order = 6;
    const int n = pow(10, order);

    for (int i = 0; i < n; i++) {
        data.d1 = rand() % 100;
        data.d2 = 'a' + rand() % 26;
        bst->add_node(data);
    }
    
    /*data.d1 = 40;
    data.d2 = 'a';
    bst->add_node(data);
    data.d1 = 30;
    data.d2 = 'a';
    bst->add_node(data);
    data.d1 = 31;
    data.d2 = 'a';
    bst->add_node(data);
    data.d1 = 29;
    data.d2 = 'a';
    bst->add_node(data);
    data.d1 = 2;
    data.d2 = 'a';
    bst->add_node(data);*/

    std::cout << bst->display_tree() << std::endl;
    bst->delete_all(bst->get_root());
    std::cout << bst->display_tree() << std::endl;
    delete bst;
    system("pause");
}

