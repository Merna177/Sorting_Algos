#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct node{
  char color;
  string value;
  node *right;
  node *left;
  node *parent;
  node(string a){
     value=a;
     right=left=parent=NULL;
  }
};
node *root=NULL;
void leftRotate(node *x){
   node *y=x->right;
   x->right=y->left;
   if(y->left!=NULL)
      y->left->parent=x;
   y->parent = x->parent;
   if(x->parent==NULL)
      root=y;
   else if(x==x->parent->left)
      x->parent->left = y;
   else
      x->parent->right = y;
  y->left = x;
  x->parent = y;
}
void rightRotate(node *y){
    node *x = y->left;
    y->left = x->right;
    if(x->right != NULL)
        x->right->parent =y;
    x->parent = y->parent;
    if(y->parent == NULL)
        root=x;
    else if(y==y->parent->left)
         y->parent->left =x;
    else
        y->parent->right =x;
    x->right = y;
    y->parent = x;
}
void insertFixUp(node *z){
    while(z!=root&&z->parent!=root&&z->parent->color=='R'){
         if(z->parent==z->parent->parent->left){
             node *y= z->parent->parent->right;
             if(y!=NULL&&y->color == 'R'){
                z->parent->color='B';
                y->color='B';
                z->parent->parent->color='R';
                z=z->parent->parent;
             }
             else{
                 if(z==z->parent->right){
                    z=z->parent;
                    leftRotate(z);
                 }
                  z->parent->color='B';
                  z->parent->parent->color='R';
                  rightRotate(z->parent->parent);
             }
         }
         else{
            node *y = z->parent->parent->left;
             if(y!=NULL&&y->color == 'R'){
                z->parent->color='B';
                y->color='B';
                z->parent->parent->color='R';
                z=z->parent->parent;
             }
             else{
                 if(z==z->parent->left){
                    z=z->parent;
                    rightRotate(z);
                 }
                  z->parent->color='B';
                  z->parent->parent->color='R';
                  leftRotate(z->parent->parent);
             }
         }
    }
    root->color='B';
}
bool search(node *now,string key){
   if(now==NULL)
    return 0;
   if(key>now->value)return search(now->right,key);
   if(key<now->value)return search(now->left,key);
   return true;
}
int getLevel(node *now){
   if(now==NULL)return 0;
   return 1+max(getLevel(now->left),getLevel(now->right));
}
int getSize(node *now){
   if(now==NULL)return 0;
   return 1 + getSize(now->left)+getSize(now->right);
}
void insertRB(string val){
    if(search(root,val)){
        cout<<"ERROR value already is in dictionary \n";
        return;
    }
    node *z=new node(val);
    if(root==NULL){
        root=z;
        cout<<"after this insertion size is "<<getSize(root)<<" and height is "<<getLevel(root)<<endl;
        return;
    }
    node *x=root;
    node *y=NULL;
    while(x !=NULL){
        y=x;
        if(z->value < x->value)
            x=x->left;
        else
            x=x->right;
    }
   z->parent=y;
   if(y==NULL)
    root=z;
   else if(z->value <y->value)
    y->left=z;
   else
    y->right=z;
   z->left=NULL;
   z->right=NULL;
   z->color='R';
   insertFixUp(z);
   cout<<"after this insertion size is "<<getSize(root)<<" and height is "<<getLevel(root)<<endl;
}
void display(node *a){
   if(a==NULL)return;
   display(a->left);
   cout<<a->value<<' ';
   display(a->right);
}
int main()
{
    insertRB("ahmed");
    insertRB("mona");
    insertRB("merna");
    insertRB("merna");
    display(root);
    return 0;
}
