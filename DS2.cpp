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
node* successor(node *p)
{
      node *y=NULL;
     if(p->left!=NULL)
     {
         y=p->left;
         while(y->right!=NULL)
              y=y->right;
     }
     else
     {
         y=p->right;
         while(y->left!=NULL)
              y=y->left;
     }
     return y;
}
void fixMyDelete(node *p)
{
    node *s;
    ///case1 en node de tb2a root f msh ma7tga a3ml 7aga asln f msh 7yd5ol f while
    while(p!=root&&p->color=='b')
    {
          if(p->parent->left==p)
          { ///b7dad sibling
                  s=p->parent->right;
                  ///case2
                  if(s->color=='r')
                  {    ///b3ml leftRotation lal parent w aswap el colors
                         s->color='b';
                         p->parent->color='r';
                         leftRotate(p->parent);
                         s=p->parent->right;
                  }
                  ///case3 75li sibling red w abdl el node bt3ty b parent
                  if(s->right->color=='b'&&s->left->color=='b')
                  {
                         s->color='r';
                         p=p->parent;
                  }
                  else
                  {
                      if(s->right->color=='b')
                      {
                             s->left->color='b';
                             s->color='r';
                             rightRotate(s);
                             s=p->parent->right;
                      }
                      s->color=p->parent->color;
                      p->parent->color='b';
                      s->right->color='b';
                      leftRotate(p->parent);
                      p=root;
                  }
          }
          else
          {
                  s=p->parent->left;
                  if(s->color=='r')
                  {
                        s->color='b';
                        p->parent->color='r';
                        rightRotate(p->parent);
                        s=p->parent->left;
                  }
                  if(s->left->color=='b'&&s->right->color=='b')
                  {
                        s->color='r';
                        p=p->parent;
                  }
                  else
                  {
                        if(s->left->color=='b')
                        {
                              s->right->color='b';
                              s->color='r';
                              leftRotate(s);
                              s=p->parent->left;
                        }
                        s->color=p->parent->color;
                        p->parent->color='b';
                        s->left->color='b';
                        rightRotate(p->parent);
                        p=root;
                  }
          }
       p->color='b';
       root->color='b';
    }
}
void displayForDel(node *DELNODE){
    cout<<"Deleted Element:\n "<<DELNODE->value;
         cout<<"Colour: ";
         if(DELNODE->color=='B')
     cout<<"Black\n";
    else
     cout<<"Red\n";
     if(DELNODE->parent!=NULL)
               cout<<"Parent:\n"<<DELNODE->parent->value;
         else
               cout<<"There is no parent of the node this node is the root.\n";
         if(DELNODE->right!=NULL)
               cout<<"Right Child:\n"<<DELNODE->right->value;
         else
               cout<<"There is no right child of the node.\n";
         if(DELNODE->left!=NULL)
               cout<<"Left Child:\n "<<DELNODE->left->value;
         else
               cout<<"There is no left child of the node.\n ";
         cout<<"DONE\n";
}
void deleteNode(int x){
    if(root==NULL)
        cout<<"Error: Empty Tree \n";
       node *DELNODE;
       DELNODE=root;
        node *y=NULL;
        node *q=NULL;
        int found =0;
        ///momkn nandy 3la function search ashl
        while(DELNODE!=NULL&&found==0)
     {
           if(DELNODE->value==x)
               found=1;
           if(found==0)
           {
                 if(DELNODE->value<x)
                    DELNODE=DELNODE->right;
                 else
                    DELNODE=DELNODE->left;
           }
     }
      if(found==0)
     {
            cout<<"Element Not Found.\n";
            return ;
     }
     else
     {
         displayForDel(DELNODE);
     if(DELNODE->left==NULL||DELNODE->right==NULL)
              y=DELNODE;
     else
        y=successor(DELNODE);
         if(y->left!=NULL)
              q=y->left;
         else
         {
              if(y->right!=NULL)
                   q=y->right;
              else
                   q=NULL;
         }
         if(q!=NULL)
              q->parent=y->parent;
         if(y->parent==NULL)
              root=q;
         else
         {
             if(y==y->parent->left)
                y->parent->left=q;
             else
                y->parent->right=q;
         }
         if(y!=DELNODE)
         {
              DELNODE->color=y->color;
             DELNODE->value=y->value;
         }
         if(y->color=='b')
             fixMyDelete(q);
     }
}
int main()
{

    return 0;
}
