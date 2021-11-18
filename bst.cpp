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
        int node_index;
        node() {
            left = nullptr;
            right = nullptr;
            parent = nullptr;
            node_index = 0;
        }
    };

    Bst() {
        size = 0;
        root = nullptr;
    }

    ~Bst() {
        delete_all(root);
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
        n->node_index = size;
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

    node* find_node(const T& data) { return find_node(data, root); }
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

    void delete_node(node* ptr) {
        if (ptr) {
            if (!ptr->right && !ptr->left) {
                //case bez potomkow
                if (ptr->data < ptr->parent->data) {
                    ptr->parent->left = nullptr;
                    delete ptr;
                }
                else {
                    ptr->parent->right = nullptr;
                    delete ptr;
                }
                size--;
            }
            else if (ptr->left && !ptr->right) {
                //case tylko z lewym potomkiem
                if (ptr->data < ptr->parent->data) {
                    ptr->left->parent = ptr->parent;
                    ptr->parent->left = ptr->left;
                    delete ptr;
                }
                else {
                    ptr->left->parent = ptr->parent;
                    ptr->parent->right = ptr->left;
                    delete ptr;
                }
                size--;

            }
            else if (ptr->right && !ptr->left) {
                //case tylko z prawym potomkiem
                if (ptr->data < ptr->parent->data) {
                    ptr->right->parent = ptr->parent;
                    ptr->parent->left = ptr->right;
                    delete ptr;
                }
                else {
                    ptr->right->parent = ptr->parent;
                    ptr->parent->right = ptr->right;
                    delete ptr;
                }
                size--;
            }
            else {
                //case gdzie sa oba potomki
                node* tmp = find_succesor(ptr->right);
                ptr->data = tmp->data;
                delete_node(tmp);
            }
        }
    }

    node* find_succesor(node* n) {
        node* tmp = n;
        while (tmp && tmp->left) {
            tmp = tmp->left;
        }

        return tmp;
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

    void delete_all() { delete_all(root); }
    void delete_all(node* n) {
        if (n == nullptr) {
            return;
        }
        else {
            delete_all(n->left);
            delete_all(n->right);
            root = nullptr;
            delete n;
            size--;
        }
    }
    int get_height() { return get_height(root); }
    int get_height(node* n) {
        if (!n) {
            return 0;
        }
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

            output << "(" << n->node_index << ": [parent: " << p.str() << ", left child: " << l.str() << ", right child: " << r.str() << "], data: " << n->data << ")," << std::endl;  
            output << tree_traversal_to_string(n->left);
            output << tree_traversal_to_string(n->right);
            
        }
        return output.str();
    }
    std::string display_tree() { 
        std::ostringstream output;
        output << "Ilosc elementow: " << size << std::endl;
        output << "Wysokosc drzewa: " << get_height(root) << std::endl;
        if (size <= 20) {
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
    
    const int MAX_ORDER = 7;
    srand(time(NULL));

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, o);

        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            data.d1 = rand() % 10000;
            data.d2 = 'a' + rand() % 26;
            bst->add_node(data);
        }
        clock_t t2 = clock();
        std::cout << "=====================================================================" << std::endl;
        std::cout << "                          " << o << " Test                           " << std::endl;
        std::cout << "=====================================================================\n\n";

        std::cout << bst->display_tree() << std::endl;
        double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
        float wynik = bst->get_size() / bst->get_height();
        float log_wynik = log2(bst->get_size());
        std::cout << "---------------------------------------------------------------------\n\n";
        std::cout << "Calkowity czas dodawania: " << time << std::endl;
        std::cout << "Sredni czas dodawania: " << time / n << std::endl;
        std::cout << "Stosunek wysokosci drzewa do rozmiaru danych: " << wynik << std::endl;
        std::cout << "Logarytm z rozmiaru danych: " << log_wynik << std::endl;
        std::cout << "Stosunek wysokosci drzewa do logarytmu z rozmiaru danych: " << bst->get_height() / log_wynik << "\n\n";
        std::cout << "---------------------------------------------------------------------\n\n";
        const int m = pow(10, 4);
        int hits = 0;
        t1 = clock();
        for (int i = 0; i < m; i++) {
            data.d1 = rand() % 10000;
            data.d2 = 'a' + rand() % 26;
            if (bst->find_node(data)) {
                hits++;
            }
        }
        t2 = clock();
        time = (t2 - t1) / (double)CLOCKS_PER_SEC;
        std::cout << "Calkowity czas wyszukiwan: " << time << std::endl;
        std::cout << "Sredni czas wyszukiwan: " << time / n << std::endl;
        std::cout << "Liczba trafien: " << hits << "\n\n";


        std::cout << "=====================================================================\n\n\n\n";



        bst->delete_all();
    }
   
    delete bst;
    system("pause");
}

