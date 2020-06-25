#ifndef INDEX_H
#define INDEX_H

#include <bits/stdc++.h>
using namespace std;

struct KEY
{
    int k;
    int value;
};


class Node{
    bool IS_LEAF;
    KEY *key;
    int size; //key is an array
    Node** ptr; //Node*'s pointer
    friend class Index;
public:
    Node();
};

class Index{
public:
    Index();
    Node *root;
    Index(int,vector<int>,vector<int>);
    void insertInternal(int,Node*,Node*);
    Node* findParent(Node*, Node*);
    void key_query(vector<int>);
    void query(int);
    void insert(int, int);
    void display(Node*);
    Node* getRoot();
    void clear_index();
    void cleanUp(Node*);
    void range_query(vector<pair<int,int>>);
    void range(int,int);
    ~Index();
};

#endif