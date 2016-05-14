#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <functional>
#include "Fibonaciheap.h"
/*
	Heap structure :
	Please read the introduction on Binomialheap from 
	wikipedia before reading this code.
	
	Representation of the Binomialheap:
	The arrows shown in the below diagram are pointers used in this code
	and Node denotes the structure Bnode
		next				  next        				next
	Node1(order-0) -----> Node2(order-1) ------>  Node3(order2)  --------->
							|						|
							|child					|child
							V						V	     next
						Node2.1					  Node2.1    ---->  Node2.2
						(order-0)				  (order-0) 		(order-1)

	Test Cases used to test code:
1:	Insert 1 ,2 ,3 ,4 ,5 ,6 ,7 ,8, 9, 10:
	Deletemin 1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10:
	
2:  Insert 10 , 9 ,8 ,7 ,6 ,5 ,4, 3, 2, 1
	Deletemin 1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10:
	
3: Insert 41 18467 6334 26500 19169 15724 11478 29358 26962 24464
	Deletemin 41 6334 11478 15724 18467 19169 24464 26500 26962 29358
*/

using namespace std;

template <class type>
bool func_object(type a,type b) //function used to decide whether top should be 
//min or max heap 
{
  return a > b;
}


template <class type>
struct Bnode
{	type key; /*Element stored in  binomial node */
	Bnode *next; /*points to next tree of  order k+1 if it is a of order k*/
	Bnode *firstchild; /*If tree is of order k, then child points to 1 order sub tree*/
	Bnode *lastchild;/*If tree is of order k, then child points to k-1 order sub tree*/
	int  order;
	Bnode(type k):key(k) // constructor
	{
		next=firstchild=lastchild=NULL;
		order=0;
	}
	~Bnode() // destructor
	{	Bnode<type> *temp;
		while(firstchild!=NULL)
			{
				temp=firstchild->next;
				delete firstchild;
				firstchild=temp;
			}
	}

	bool addsubtree(Bnode<type>* as) //Merging two sub trees
	{
		if(order==as->order) // Only same order trees can be merged
		{
			order++; // increasing order by one
			if(firstchild==NULL)
				firstchild=lastchild=as; // case when tree has no child
			else
			{	lastchild->next=as; // case when tree has children, appending the child
				lastchild=lastchild->next;
			}
			lastchild->next=NULL;
			return true; // merging succesfull 
		}
		return false; // merging failed
	}
};//End of class bnode

template <class type>
class Binomialheap
{
	private:
	/* Private Variables */
	int treecount;
	Bnode<type> *first;//first tree in the list of binomial trees
	Bnode<type> *last;//last tree in the list of binomial trees
	Bnode<type> *top_compare;// the tree with the min or max element

	public:
	/* 	Functions */
	Binomialheap();//constructor
	~Binomialheap();//destructor
	void insert(type key); // Inserts the key in to heap
	type top();//returns the heap top value
	void deletetop();//delete the top heap value

	bool empty() // if first==NULL return true
	{	return (first)?false:true;
	}
	void print(ostream & O) ;//Not implemented yet
	private:
	/* Functions used for interior implementation */

	void merge(Bnode<type> * a,Bnode<type>* b);//Most complex routine

	void findtopcompare();// used to find the function object,tree with max or min element
    
    Bnode<type>* find_next_order_node_and_increment_list(Bnode<type>* &a,Bnode<type>* &b);
};//End of heap class declaration



void Binomialheaptest()
{
    Binomialheap<int> H;
	//clrscr();
    srand(time(NULL));
    clock_t t=clock();
  	cout << "INSERTING ELEMENT :" ;
    for(int k=1000;k>0;k--)
	{   int x=rand();
        cout << x << " "; 
        H.insert(x);
	}
    
    cout << endl;
    cout << "Poping all elements out from heap one by one" << endl;
    while(!H.empty())
		{
			cout << H.top() << endl;
			H.deletetop();
		}

	cout << "Please press any key to continue " << endl;
	clock_t f=clock();
    f=f-t;
    cout << "Time taken :" << (double(f)/CLOCKS_PER_SEC) << endl;
    getch();
}



void Fibonacciheaptest()
{
    Fibonacciheap<int,greater<int> > h;
    int x=(int)rand();
   for(int i=0;i<100;i++)
   {    x=rand()%1000;
       cout << "Inserting " << x <<endl;
       h.insert(x);
    }
    cout << "heap before delete min" << endl;
    h.printHeap(cout);
    h.delete_min();
    cout << "After delete min" << endl;
    h.printHeap(cout);
}

int main()
{
	//Binomialheaptest();
    Fibonacciheaptest();
	return 0;
}

template <class type>
Binomialheap<type>::Binomialheap() // constructor of Binomial heap
{
  top_compare=last=first=NULL;
  treecount=0;
}

template <class type>
Binomialheap<type>::~Binomialheap() // destructor
{
	Bnode<type> *temp;
		while(first!=NULL)
			{
				temp=first->next;
				delete first; // calls further destructors of a node's children
				first=temp;
			}
}
template <class type>
void Binomialheap<type>::findtopcompare() // used to find the tree with max or min element 
{
	Bnode<type>* temp=first;

	top_compare=first;
		while(temp!=NULL)
		{
			if(func_object(temp->key,top_compare->key))
				top_compare=temp;
			temp=temp->next;
		}
}
template <class type>
void Binomialheap<type>::insert(type key)
{
	if(first==NULL&&last==NULL)
	{
		top_compare=first=last=new Bnode<type>(key);

	}
	else
	{
		merge(first,new Bnode<type>(key));
	}
	treecount++;
	findtopcompare();
}
template <class type>
type Binomialheap<type>::top()
{
	return top_compare->key;
}

template <class type>
Bnode<type>* Binomialheap<type>::find_next_order_node_and_increment_list(Bnode<type>* & first,Bnode<type>* & second)
{
    Bnode<type>* a=first,*b=second,*temps;
    Bnode<type>* returnnode;//The node with lower order is returned first in the new list.
        if( a->order < b->order ) //Case: when node of 'a' has a lower order than node of 'b'.
			{	returnnode=a;
				a=a->next;//taking next node from heap 'a'
			}
			else if(a->order == b->order ) // Case: if nodes have same order , 
            //then they are combined to form a single node according to the requirement(min or max heap).
			{   //Func_object decides whether a is attached to b , or b is attached to a.
 				//If function object returns true , b's first node is added as a subtree to a's first node.
                //Otherwise a's first node is added as a sub tree to b's first node.
				if(func_object(a->key,b->key))
				{   temps=b->next;
					a->addsubtree(b);
					returnnode=a;
					a=a->next;//taking next node from heap 'a'
					b=temps;
				}
				else
				{	temps=a->next;
                    b->addsubtree(a);
					returnnode=b;
					b=b->next;//taking next node from heap 'b'
					a=temps;
				}

			}
			else
			{	
				b=b->next;//taking next node from heap 'b'
			}
    first=a;
    second=b;
    return returnnode;
}
template <class type>
void Binomialheap<type>::print(ostream & O)
{
	Bnode<type>* ffirst=first;
	while(ffirst!=NULL)
	{
		cout << ffirst->key << " ";
		ffirst=ffirst->next;
	}
}
template <class type>
void Binomialheap<type>::merge(Bnode<type>* a,Bnode<type>* b) // a and b are two heaps to be mereged
{	
    // Algorithm is similiar to merge sort :merge routine.
    //Here the nodes in each heap is sorted according to their tree order.
    // The given below temporary varaibles are used to save the new list created in merge routine.
    //First Loop:Merges nodes from both nodes till any one heap becomes empty.
    //Second Loop:If heap 'a' is not empty , the appends its elements into the new list(new heap)
    //Third Loop:If heap 'b' is not empty , the append its elements into the new list(new heap)
	Bnode<type>* ffirst,* llast,*temps;
    ffirst=llast=NULL;
    //Note:Here nodes are just binomial trees.
	while(a!=NULL && b!=NULL) // First loop ,
    //Merges nodes from both nodes till any one heap becomes empty.
	{
		if(ffirst==NULL && llast==NULL) // New list is empty
		{   
			if( a->order < b->order ) //Case: when first node of 'a' has a lower order than first node of 'b'.
			{
				ffirst=llast=a;
				a=a->next;//taking next node from heap 'a'
			}
			else if(a->order == b->order ) // Case: if nodes have same order , 
            //then they are combined to form a single node according to the requirement(min or max heap).
			{   //Func_object decides whether a is attached to b , or b is attached to a.
 				//If function object returns true , b's first node is added as a subtree to a's first node.
                //Otherwise a's first node is added as a sub tree to b's first node.
                if(func_object(a->key,b->key)) 
				{   temps=b->next;
					a->addsubtree(b);
					ffirst=llast=a;
					a=a->next;//taking next node from heap 'a'
					b=temps;
				}
				else
				{   temps=a->next;
					b->addsubtree(a);
					ffirst=llast=b;
					b=b->next;//taking next node from heap 'b'
					a=temps;
				}
			}
			else //Case: when first node of 'b' has a lower order than first node of 'a'.
			{
				ffirst=llast=b;
				b=b->next;//taking next node from heap 'b'
			}
		}
		else
		{
          //  llast->next=find_next_order_node_and_increment_list(a,b);
			if( a->order < b->order ) //Case: when node of 'a' has a lower order than node of 'b'.
			{	llast->next=a;
				a=a->next;//taking next node from heap 'a'
			}
			else if(a->order == b->order )
			{
				if(func_object(a->key,b->key))
				{   temps=b->next;
					a->addsubtree(b);
					llast->next=a;
					a=a->next;//taking next node from heap 'a'
					b=temps;
				}
				else
				{	temps=a->next;
                    b->addsubtree(a);
					llast->next=b;
					b=b->next;//taking next node from heap 'b'
					a=temps;
				}

			}
			else
			{	llast->next=b;
				b=b->next;//taking next node from heap 'b'
			}
		
        llast=llast->next;
		}
	} // End of first loop

	while(a!=NULL)//If heap 'a' is not empty , the appends its elements into the new list(new heap)
	{
		if(ffirst==NULL && llast==NULL) // Case :when the new list is empty
           { ffirst=llast=a;
            a=a->next;//taking next node from heap 'a'
           }
        else{
                if(llast->order == a->order ) // Checking the order of last element in new heap.
                {
                    if(func_object(llast->key,a->key)) // Last node in new heap and node from 'a' have
                    // equal orders then they are combined together
                    {   temps=a->next;
                        llast->addsubtree(a);
                        a=temps;
                    }
                    else
                    {   
                        Bnode<type> *p=NULL,*t=ffirst;
                        while(t!=llast)  //We find the element before last node in new list .
                            {   
                                p=t;
                                t=t->next;
                            }
                        
                        a->addsubtree(llast); // add last node from new list to the a node as a subtree
                        if(ffirst==llast) ffirst=llast=a; // if last was tge first element
                        else p->next=llast=a; // Make 'a' as the last node in new heap.
                        a=a->next;
                    }
                    llast->next=NULL;
                }
                else // if orders are not equal then just append a to new list.
                {
                    llast->next=a;
                    llast=llast->next;
                    a=a->next;
                }
            }
	} //End of Second Loop
	while(b!=NULL)//:If heap 'b' is not empty , the append its elements into the new list(new heap)
	{
		if(ffirst==NULL && llast==NULL)
            {ffirst=llast=b;
             b=b->next;   
            }
        else{
                if(llast->order == b->order )
                {
                    if(func_object(llast->key,b->key))
                    {   temps=b->next;
                        llast->addsubtree(b);
                        b=temps;
                    }
                    else
                    {	
                         Bnode<type> *p=NULL,*t=ffirst;
                        while(t!=llast) 
                            {   
                                p=t;
                                t=t->next;
                            }
                        b->addsubtree(llast);
                        if(ffirst==llast) ffirst=llast=b;
                        else p->next=llast=b;
                        b=b->next;
                    }
                    llast->next=NULL;
                }
                else
                {
                    llast->next=b;
                    llast=llast->next;
                    b=b->next;
                }
            }
	}//End of third loop

	Binomialheap<type>::first=ffirst; //assign the list first tree to first node instance variable
	Binomialheap<type>::last=llast;// assign the last tree to last node instance variable
}
template <class type>
void Binomialheap<type>::deletetop() //delete min or delete max operation
{    
	if(top_compare==NULL) return; //case :when the heap is empty
    
    Bnode<type> *temp=first,*prev=NULL; 
	while(temp!=top_compare)//Find the previous element of top_compare
	{
		prev=temp;
		temp=temp->next;
	}

	if(prev==NULL) // if no previous element is present ,then merge the children of top compare to next element in list
	{
		merge(top_compare->next,top_compare->firstchild);
	}
	else
	{	prev->next=top_compare->next;
		merge(first,top_compare->firstchild);
	}
    
    //Delete only the root of the topcompare tree
	top_compare->firstchild=NULL;
	top_compare->lastchild=NULL;
	delete top_compare;
    
	findtopcompare();//Search of the new topcomare
	treecount--;//Reduce the tree count
}