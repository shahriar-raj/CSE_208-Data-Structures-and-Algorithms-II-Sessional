#include <bits/stdc++.h>
struct node {
    int ver;
    double key;
    int degree;
    node *parent;
    node *child;
    node *left;
    node *right;
};

void fibonacci_link(node *m, node *x, node *y){
    (y->left)->right = y->right;
    (y->right)->left = y->left;
    if(x->right == x)
        m = x;
    y->left = y;
    y->right = y;
    y->parent = x;
    if(x->child == nullptr){
        x->child = y;
    }

    y->right = x->child;
    y->left = (x->child)->left;
    ((x->child)->left)->right = y;
    (x->child)->left = y;

    if (y->key < (x->child)->key)
        x->child = y;
    x->degree++;
    delete y;
}

class fibonacci_heap {
    int n;
    node *m = new node;
public:
    fibonacci_heap();
    void fib_heap_insert(node *x);
    node* fib_heap_extract_min();
    void consolidate();
    node* getmin();
};

node* fibonacci_heap::getmin(){
    return m;
}

fibonacci_heap::fibonacci_heap(){
    n= 0;
    m = nullptr;
}

void fibonacci_heap::fib_heap_insert(node *x){
    x->degree =0;
    x->parent = nullptr;
    x->child = nullptr;
    x->left = x;
    x->right = x;
    if(m == nullptr){
        m = x;
    }

    else{
        (m->left) -> right = x;
        x -> left = m->left;
        x->right = m;
        m->left = x;
       // cout << m->key << " " << x->key << endl;
        if(x->key < m->key){
            m = x;
           // cout << "Execute" <<endl;
        }
    }
    n = n+1;
    //cout << "Number of nodes: "<< n << endl;
}

node* fibonacci_heap::fib_heap_extract_min(){
    node *z = m;
    node *c;
    node *si;
    node *np;
    //cout << "In " << endl;
    if (z==nullptr){
        //cout << z->key << endl;
        return z;
    }
    if(z->child !=nullptr){
        c = z->child;
        //cout << "In 2" << endl;
    }
    if(z->child  != nullptr){
       si = c;
       do{
             np = si->right;
            (m->left)->right = si;
            si->left = m->left;
            si->right = m;
            m->left = si;
            si->parent = nullptr;
            if(np == c)
                break;
            si = np;
        }while(np != c);
    }

    (z->left)->right = z->right;
    (z->right)->left = z->left;
     m = z->right;
    if(z == z->right && c==nullptr)
        m = nullptr;
    else{
        m = z->right;
        //cout << m->key << endl;
        consolidate();
    }
    n = n-1;
    return z;
}

void fibonacci_heap::consolidate(){
    int D = (log(n)/log(2));
    node **A = new node*[D];
    for(int i=0; i<=D; i++){
        A[i] = new node;
        A[i] = nullptr;
    }
    node *x = m;
    node *ptr = x;
    node *y;
    node *npr;
    do{
        ptr = ptr->right;
        int d = x->degree;
        while (A[d] != nullptr){
            y = A[d];
            if(x->key > y->key){
                npr = x;
                x = y;
                y = npr;
            }
            if(y == m)
                m = x;
            fibonacci_link(m, x, y);
            if(x->right == x)
            m = x;
            A[d] = nullptr;
            d = d + 1;
        }
        A[d] = x;
        x = x->right;
    }while (x != m);

    m=nullptr;
    for (int i = 0; i <= D; i++) {
        if (A[i] != nullptr){
            A[i]->left = A[i];
            A[i]->right = A[i];
            if (m != nullptr){
                (m->left)->right = A[i];
                A[i]->right = m;
                A[i]->left = m->left;
                m->left = A[i];
                if (A[i]->key < m->key)
                    m = A[i];
            }
            else {
            m = A[i];
            }
            if (m == nullptr)
                m = A[i];
            else if (A[i]->key < m->key)
                m = A[i];
        }
    }
}
