#include <bits/stdc++.h>

using namespace std;

struct node {
    int key;
    int color;
    node* left;
    node* right;
    node* parent;
};

class RBT{
    node* root;
    node* tnull;

public:
    RBT();
    void RB_insert(node*);
    void RB_insert_fixup(node*);
    void L_Rotate(node*);
    void R_Rotate(node*);
    void RB_transplant(node*, node*);
    void RB_delete(node*);
    void RB_delete_fixup(node*);
    node* tree_min(node*);
};

RBT::RBT(){
    tnull = new node;
    tnull->color = 0;
    tnull->left = nullptr;
    tnull->right = nullptr;
    tnull->parent = nullptr;
    root = tnull;
}

node* RBT::tree_min(node *z){
    while (z->left != tnull) {
      z = z->left;
    }
    return z;
}

void RBT::RB_insert(node* z){
    node* y = tnull;
    node* x = root;
    while(x!=tnull){
        y = x;
        if(z->key<x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if(y==tnull)
        root = z;
    else if(z->key<y->key){
        y->left = z;}
    else{
        y->right = z;
    }
    z->left = tnull;
    z->right = tnull;
    z->color = 1;
    RB_insert_fixup(z);
}

void RBT::RB_insert_fixup(node *z){
    node *y = new node;
    while((z->parent)->color==1){
        if(z->parent == (((z->parent)->parent)->left)){
            y = ((z->parent)->parent)->right;
            if(y->color == 1){
                (z->parent)->color = 0;
                y->color = 0;
                ((z->parent)->parent)-> color = 1;
                z = ((z->parent)->parent);
            }
            else if(z == (z->parent)->right){
                z = z->parent;
                L_Rotate(z);
            }
            (z->parent)->color = 0;
            ((z->parent)->parent)->color =1;
            R_Rotate(z);
        }
        else{
            y = ((z->parent)->parent)->left;
            if(y->color == 1){
                (z->parent)->color = 0;
                y->color = 0;
                ((z->parent)->parent)-> color = 1;
                z = ((z->parent)->parent);
            }
            else if(z == (z->parent)->left){
                z = z->parent;
                R_Rotate(z);
            }
            (z->parent)->color = 0;
            ((z->parent)->parent)->color =1;
            L_Rotate(z);
        }
    }
    root->color = 0;
}

void RBT::L_Rotate(node* x){
    node *y  = x->right;
    x->right = y->left;
    if(y->left!=tnull)
        (y->left)->parent = x;
    y->parent = x->parent;
    if(x->parent == tnull)
        root = y;
    else if(x == (x->parent)->left){
        (x->parent)->left = y;
    }
    else
        (x->parent)->right = y;
    y->left = x;
    x->parent = y;
}

void RBT::R_Rotate(node* x){
    node *y  = x->left;
    x->left = y->right;
    if(y->right!=tnull)
        (y->right)->parent = x;
    y->parent = x->parent;
    if(x->parent == tnull)
        root = y;
    else if(x == (x->parent)->right){
        (x->parent)->right = y;
    }
    else
        (x->parent)->left = y;
    y->right = x;
    x->parent = y;
}

void RBT::RB_transplant(node* u, node* v){
    if(u->parent==tnull)
        root = v;
    else if(u==(u->parent)->left){
        (u->parent)->left = v;
    }
    else
        (u->parent)->right = v;
    v->parent = u->parent;
}

void RBT::RB_delete(node *z){
    node* y =z;
    node *x = new node;
    int y_o_c = y->color;
    if(z->left == tnull){
        x = z->right;
        RB_transplant(z, z->right);
    }
    else if(z->right == tnull){
        x = z->left;
        RB_transplant(z,z->left);
    }
    else{
        y = tree_min(z->right);
        y_o_c = y->color;
        x = y->right;
        if(y->parent==z)
            x->parent = y;
        else{
            RB_transplant(y,y->right);
            y->right = z->right;
            (y->right)->parent = y;
        }
        RB_transplant(z,y);
        y->left = z->left;
        (y->left)->parent  = y;
        y->color = z->color;
    }
    if(y_o_c==0)
        RB_delete_fixup(x);
}

void RBT::RB_delete_fixup(node* x){
    node *w =new node;
    while(x!=root && x->color==0){
        if(x == (x->parent)->left){
            w = (x->parent)->right;
            if(w->color == 1){
                w->color == 0;
                (x->parent)->color = 1;
                L_Rotate(x->parent);
                w = (x->parent)->right;
            }
            if((w->left)->color == 0 && (w->right)->color == 0){
                w->color = 1;
                x = x->parent;
            }
            else if((w->right)->color==0){
                (w->left)->color = 0;
                w->color = 1;
                R_Rotate(w);
                w = (x->parent)->right;
            }
            w->color = (x->parent)->color;
            (x->parent)->color = 0;
            (w->right)->color =0;
            L_Rotate(x->parent);
            x=root;
        }
        else{
            w = (x->parent)->left;
            if(w->color == 1){
                w->color == 0;
                (x->parent)->color = 1;
                R_Rotate(x->parent);
                w = (x->parent)->left;
            }
            if((w->right)->color == 0 && (w->left)->color == 0){
                w->color = 1;
                x = x->parent;
            }
            else if((w->left)->color==0){
                (w->right)->color = 0;
                w->color = 1;
                L_Rotate(w);
                w = (x->parent)->left;
            }
            w->color = (x->parent)->color;
            (x->parent)->color = 0;
            (w->left)->color =0;
            R_Rotate(x->parent);
            x=root;
        }
    }
    x->color = 0;
}

int main(){
    int test,e,x_i;
    freopen("in.txt", "r", stdin);
    cin >> test;
    for(int i=0; i<test; i++){
        cin>>e>>x_i;
    }
    return 0;
}
