#ifndef FIB_HEAP11
#define FIB_HEAP11
#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <queue>
#include <string>
using namespace std;

template <class type>
class Fnode
{
    int No_of_marks;//No of marks in the heap (children)
    bool marked;//true if Root is marked
    type value;
public:
    list< Fnode<type>* > children;
    Fnode(type v,bool mark=false):value(v)
    {
        marked=mark;
    }
    ~Fnode()
    {
        for(typename list<Fnode<type>* >::iterator itr=children.begin();itr!=children.end();itr++)
            delete *itr;
    }
    type getvalue() {return value;}
    void Mark(){ marked=true;}
    void Unmark() { marked=false;}
    bool ismarked() {return ismarked;}
    size_t rank() {return children.size();}
    size_t order() {return children.size();}
    
    bool operator<(const Fnode<type> & x)
    {   return children.size() < x.children.size();
    }
    bool operator>(const Fnode<type> & x)
    {   return children.size() > x.children.size();
    }
    bool operator<=(const Fnode<type> & x)
    {   return children.size() <= x.children.size();
    }
    bool operator>=(const Fnode<type> & x)
    {   return children.size() >= x.children.size();
    }
    
    void printheap(string space)
    {
       cout << space <<  "Order: " << order() << " Value: " << getvalue() << endl;
       for(typename list<Fnode<type>*>::iterator itr=children.begin();
        itr!=children.end();
        itr++)
        {   cout << space << "-----------Children------------"<<endl;
            (*itr)->printheap(string(space+"    ")); 
            cout << space << "_______________________________"<<endl;
        } 
    }
};



template <class type,class objects>
class Fibonacciheap
{
    Fnode<type>* top_node;
    list< Fnode<type>* > nodes;
public:
    objects func_object;
    Fibonacciheap();
    ~Fibonacciheap();
    void insert(type value);
    type top();
    void delete_min();
    void printHeap(ostream& cout=cout);
private:
    void update_top();
   
    Fnode<type>* LinkingOperation(Fnode<type>* a,Fnode<type>* b);
};

#include "fibheap.tpp"
#endif