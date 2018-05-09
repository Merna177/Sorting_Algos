#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct node{
  char color;
  int value;
  node *right;
  node *left;
  node *parent;
  node(int a){
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
void insertRB(int val){
    node *z=new node(val);
    if(root==NULL){
        root=z;
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
}
void display(node *a){
   if(a==NULL)return;
   display(a->left);
   cout<<a->value<<' ';
   display(a->right);
}
void test(){
   for(int i=0;i<10;i++){
        int val=i;
        insertRB(val);
        display(root);
        cout<<endl;
    }
}
bool search(node *now,int key){
   if(now==NULL)
    return 0;
   if(key>now->value)return search(now->right,key);
   if(key<now->value)return search(now->left,key);
   return true;
}
int main()
{

    return 0;
}