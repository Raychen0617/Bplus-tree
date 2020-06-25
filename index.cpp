#include "index.h"
#include <bits/stdc++.h>
#include <vector>
#define ORDERTWO 50
using namespace std;

FILE *fout2, *fout;
Node::Node(){
    key = new KEY[ORDERTWO];
    ptr = new Node*[ORDERTWO+1];//left right +1
}

Index::Index(){
    root=NULL;
}

void Index::range_query(vector<pair<int,int>> vec){
    fout2= fopen("range_query_out.txt","w");
    for(int i=0;i<vec.size();i++){
        range(vec[i].first, vec[i].second);
    }  
    fclose(fout2);  
}

void Index::range(int start, int end){
    //cout<<start<<" "<<end<<endl;
    Node* current = root;
    //Node* f = root;
    while(current->IS_LEAF==false){
        for(int i=0;i<current->size;i++){
            if(start<current->key[i].k){
                current = current->ptr[i];
                break;
            }
            if(i==current->size-1){
                current = current->ptr[i+1];
                break;
            }
        }  
    }
    int i=0;
    int max=-1;
    while(true){    

        if(i==current->size){
            i=0;
            current = current->ptr[current->size];
        }

        if(current->key[i].k>end){
            //cout<<i<<"----"<<current->key[i].k<<endl;
            break;
        }
        if(current->key[i].k>=start && current->key[i].value>max){
            max = current->key[i].value;
        }
        //cout<<"i= "<<i<<" size= "<<current->size<<" "<<current->key[i].k<<" end="<<end<<endl;       
        i++;
    }
    //cout<<max<<endl;
    fprintf(fout2,"%d\n",max);
    // 27 28 error
}

Index::Index(int row,vector<int>keys, vector<int> values){
    
    root=NULL;

    for(int i=0;i<keys.size();i++){
        insert(keys[i],values[i]);
    }    
    return ;
}

void Index::key_query(vector<int>keys){

    fout=fopen("key_query_out.txt","w");
    for(int i=0;i<keys.size();i++){
        //cout<<keys[i]<<" ";
        query(keys[i]);
    }
    fclose(fout);
}

void Index::query(int x){   
    if(root==NULL){
		cout<<"Tree empty\n";
        return ;
	}
    Node* current = root;
    while(current->IS_LEAF==false){
        
        int start=0, end=current->size;

        for(int i=0;i<current->size;i++){
            if(x<current->key[i].k){
                current = current->ptr[i];
                break;
            }
            if(i==current->size-1){
                current = current->ptr[i+1];
                break;
            }
        } 
    }
    //leaf   
    int start=0, end= current->size-1, mid;
    
    while(start<=end){

        mid = start + (end-start)/2;

        //cout<<"----"<<start<<" "<<mid<<" "<<end;

        if(x==current->key[mid].k){
            //cout<<"found"<<endl;
            fprintf(fout,"%d\n",current->key[mid].value);
            return ;
        }
        if(x<current->key[mid].k){
            end = mid-1;
        }
        else if(x>current->key[mid].k){
            start = mid+1;
        }
    }
    
    /*

    for(int i=0;i<current->size;i++){
        if(current->key[i].k==x){
            fout<<current->key[i].value<<endl;
            return ;
        }
    }
    */    
    fprintf(fout,"-1\n");
    return ;
}

void Index::insert(int x, int value){

    if(root==NULL){
        //cout<<"root is null"<<endl;
        root = new Node;
        root->key[0].k=x;
        root->key[0].value=value;
        root->IS_LEAF = true;
        root->size = 1;
        return ;
    }
    Node* current=root;
    Node* parent;
    while(current->IS_LEAF==false){
        parent=current;
        for(int i=0;i<current->size;i++){

            if(x<current->key[i].k){
                current = current->ptr[i];
                break;
            }
            if(i==current->size-1){
                current = current->ptr[i+1];
                break;
            }
        }
    }

    //cout<<current->key[0]<<" "<<current->IS_LEAF<<endl;
    if(current->size<ORDERTWO){
        int i=0;
        while(x>current->key[i].k && i<current->size){
            i++;
        }

        for(int j=current->size;j>i;j--){       // move backward one step
            current->key[j].k = current->key[j-1].k;
            current->key[j].value = current->key[j-1].value;
        }
        current->key[i].k=x;
        current->key[i].value=value;
        current->size+=1;
        // connect ptr to new key array
        current->ptr[current->size] = current->ptr[current->size-1];
        current->ptr[current->size-1]=NULL;
    }
    else{                   //overflow
        //cout<<"Overflow in leaf node!\nSplitting leaf node\n";
        Node* L2 = new Node;
        int newkey[ORDERTWO+1];
        int newvalue[ORDERTWO+1];
        for(int i=0;i<ORDERTWO;i++){
            newkey[i] = current->key[i].k;
            newvalue[i] = current->key[i].value;
        }

////////////////////////    vector ways(slower) //////////////////////////////
/*       
        for(int i=0;i<ORDERTWO;i++){
            newkey.push_back(current->key[i].k);
            newvalue.push_back(current->key[i].value);
        }
        int i= upper_bound(newkey.begin(), newkey.end(),x)-newkey.begin();
        newkey.insert(newkey.begin()+i,x);
        newvalue.insert(newvalue.begin()+i,value);
*/
//////////////////////////////////////////////////////////////////////////////        

        int i=0,j;
        while(x>newkey[i] && i<ORDERTWO){
            i++;
        }        
        for(int j=current->size;j>i;j--){
            newkey[j] = newkey[j-1];
            newvalue[j] = newvalue[j-1];
        }
        newkey[i]=x;
        newvalue[i]=value;


        L2->IS_LEAF=true;
        
        //cout<<L2->size<<"  "<<current->size<<endl;
        current->size = (ORDERTWO+1)/2;
        L2->size = ORDERTWO+1 - current->size;
        
        L2->ptr[L2->size] = current->ptr[ORDERTWO];
        current->ptr[current->size] = L2;
        current->ptr[ORDERTWO]=NULL;

        
        for(i=0;i<current->size;i++){
            current->key[i].k = newkey[i];
            current->key[i].value = newvalue[i];
        }
        for(int j=0;i<ORDERTWO+1;i++,j++){
            L2->key[j].k = newkey[i];
            L2->key[j].value = newvalue[i];
        }

        // change L2's parent

        if(current==root){
        
            Node* newRoot = new Node;
            newRoot->IS_LEAF=false;
            newRoot->key[0].k=L2->key[0].k;
            newRoot->key[0].value=value;
            newRoot->ptr[0]=current;    // left is current
            newRoot->ptr[1]=L2;         // right is new L2
            newRoot->size=1;
            root = newRoot;
            //cout<<"create new root"<<endl;
        }
        else{
            insertInternal(L2->key[0].k,parent,L2);   // lift up median's value
        }
    }
}

void Index::insertInternal(int x, Node* current, Node* rightchild){

    if(current->size<ORDERTWO){
        int i=0;
        while(x>current->key[i].k && i<current->size) 
            i++;
        
            
        for(int j=current->size;j>i;j--){       // move backward one step
            current->key[j].k= current->key[j-1].k;
            //current->key[j].value=current->key[j-1].value;
        }

        for(int j = current->size+1; j > i+1; j--)
		{
			current->ptr[j] = current->ptr[j-1];
		}
        
        current->key[i].k=x;
        //current->key[i].value=value;
        current->size+=1;
        current->ptr[i+1]=rightchild;
        return ;   
    }
    
    else{                   //overflow
        //cout<<"Overflow in leaf node!\nSplitting leaf node\n";
        Node* L2 = new Node;
        int newkey[ORDERTWO+1];      // new key array with size+1
        int newvalue[ORDERTWO+1];
        Node* newPtr[ORDERTWO+2];    // not leaf need to record their ptr
        
        for(int i=0;i<ORDERTWO;i++){     //current->size = ORDERTWO
            newkey[i] = current->key[i].k;
            //newvalue[i] = current->key[i].value;
        }

        for(int i=0;i<ORDERTWO+1;i++){
            newPtr[i] = current->ptr[i];
        }
        
        int i=0;
        while(x>newkey[i] && i<ORDERTWO) 
            i++;
            
        for(int j=ORDERTWO;j>i;j--){
            newkey[j] = newkey[j-1];
            newvalue[j] = newvalue[j-1];
        }
        newkey[i]=x;
        //newvalue[i]=value;

        for(int j=ORDERTWO+1;j>i;j--){
            newPtr[j] = newPtr[j-1];
        }

        newPtr[i+1]=rightchild;
        L2->IS_LEAF=false;
        //L2->size = (((ORDERTWO+1)%2)==1)?(ORDERTWO+2)/2:(ORDERTWO+1)/2;
        //current->size = ORDERTWO+1-L2->size;
		current->size = (ORDERTWO+1)/2;
		L2->size = ORDERTWO-current->size;

        for(int i=0;i<current->size;i++){
            current->key[i].k = newkey[i];
            //current->key[i].value = newvalue[i];
        }

        for(int i=0;i<current->size+1;i++){
            current->ptr[i] = newPtr[i];
        }

        for(int i=0,j=current->size+1;i<L2->size;i++,j++){  //current->size is the median to push up
            //cout<<"j="<<j<<endl;
            L2->key[i].k = newkey[j];
            //L2->key[i].value = newvalue[j];
        }

        for(int i=0,j=current->size+1;i<L2->size+1;i++,j++){
            L2->ptr[i] = newPtr[j];
        }
		if(current==root){
            Node* newRoot = new Node;
            newRoot->key[0].k=newkey[current->size];
            //newRoot->key[0].value = newvalue[current->size];
            newRoot->ptr[0]=current;    // left is current
            newRoot->ptr[1]=L2;         // right is new L2
            newRoot->IS_LEAF=false;
            newRoot->size=1;
            root = newRoot;
            //cout<<"create new root"<<endl;
        }
		else
		{
			//recursion
			//find depth first query to find parent of current
			insertInternal(newkey[current->size] ,findParent(root,current) ,L2);
		}
	}
}

Node* Index::findParent(Node* current, Node* child)
{
	//finds parent using depth first traversal and ignores leaf nodes as they cannot be parents
	//also ignores second last level because we will never find parent of a leaf node during insertion using this function
	Node* parent;
	if(current->IS_LEAF || (current->ptr[0])->IS_LEAF)
	{
		return NULL;
	}
	for(int i = 0; i < current->size+1; i++)
	{
		if(current->ptr[i] == child)
		{
			parent = current;
			return parent;
		}
		else
		{
			parent = findParent(current->ptr[i],child);
			if(parent!=NULL)return parent;
		}
	}
	return parent;
}

void Index::display(Node* current)
{
	if(current!=NULL)
	{
		for(int i = 0; i < current->size; i++)
		{
			cout<<current->key[i].k<<" ";
		}
		cout<<"\n";
		if(current->IS_LEAF != true)
		{
			for(int i = 0; i < current->size+1; i++)
			{
				display(current->ptr[i]);
			}
		}
	}
}

Node* Index::getRoot()
{
	return root;
}

void Index::cleanUp(Node* current)
{
	//clean up logic
	if(current!=NULL)
	{
		if(current->IS_LEAF != true)
		{
			for(int i = 0; i < current->size+1; i++)
			{
				cleanUp(current->ptr[i]);
			}
		}
		delete[] current->key;
		delete[] current->ptr;
        delete current;
	}
}

Index::~Index()
{
	//cleanUp(root);
}

void Index::clear_index(){
    cleanUp(root);
}