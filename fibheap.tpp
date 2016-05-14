

template <class type,class objects> 
Fibonacciheap<type,objects>::Fibonacciheap()
{
    top_node=NULL;
}
template <class type,class objects> 
Fibonacciheap<type,objects>::~Fibonacciheap()
{
    for(typename list< Fnode<type>* >::iterator itr=nodes.begin();itr!=nodes.end();itr++)
    delete *itr;
}

template <class type,class objects> 
void Fibonacciheap<type,objects>::insert(type value)
{   Fnode<type>* temp=new Fnode<type>(value);
    if(temp==NULL)
        throw "Heap Overflow:No memory";
    if(top_node==NULL)
        top_node=temp;
    else top_node=(func_object( temp->getvalue(),top_node->getvalue() ))? temp:top_node;
    
    nodes.push_back(temp);
}
    
template <class type,class objects> 
type Fibonacciheap<type,objects>::top()
{   if(top_node==NULL) 
        throw "Heap Underflow";
    return top_node->getvalue();
}

template <class type,class objects> 
Fnode<type>* Fibonacciheap<type,objects>::LinkingOperation(Fnode<type>* a,Fnode<type>* b)
{
    if(  func_object(a->getvalue() , b->getvalue()) )
    {   a->children.push_back(b);
        return a;
    }
    else 
    {
        b->children.push_back(a);
        return b;
    }
}
template <class type,class objects> 
void Fibonacciheap<type,objects>::delete_min()
{
    if(top_node==NULL)
        throw "Heap Underflow";
        
    nodes.remove(top_node);
    
    for(typename list<Fnode<type>*>::iterator itr=top_node->children.begin();itr!=top_node->children.end();)
       {
          nodes.push_back(*itr);
          itr=top_node->children.erase(itr);
       }
    map< size_t,Fnode<type>* > rank_list;
    
    for(typename list<Fnode<type>*>::iterator itr=nodes.begin();itr!=nodes.end();)
    {      Fnode<type>* n=*itr; 
        
           while(1)
           if(!rank_list.count(n->order()) )
           {
                rank_list[n->order()]=n;
                break;
            }
            else
            {   n=LinkingOperation(n,rank_list[n->order()]);
                rank_list.erase(n->order()-1);
            }
            itr=nodes.erase(itr);
    }
    for(typename map< size_t,Fnode<type>* >::iterator itr=rank_list.begin();
    itr!=rank_list.end();
    itr++)
    {
        nodes.push_back((*itr).second);
    }
     update_top();   
}
template <class type,class objects> 
void Fibonacciheap<type,objects>::update_top()
{   size_t max=(*nodes.begin())->getvalue();
    top_node=*(nodes.begin());
    for(typename list<Fnode<type>*>::iterator itr=nodes.begin();
        itr!=nodes.end();
        itr++)
    {
        if(max < (*itr)->getvalue())
        {
            top_node=(*itr);
            max=(*itr)->getvalue();
        }
    }
    
}

template <class type,class objects> 
void Fibonacciheap<type,objects>::printHeap(ostream& cout)
{
    cout <<"___________________List of Nodes____________________________" << endl;
    for(typename list<Fnode<type>*>::iterator itr=nodes.begin();
        itr!=nodes.end();
        itr++)
        {
            cout <<"___________________________________________________________________________" << endl;
            (*itr)->printheap(string("    "));    
           
            cout <<"____________________________________________________________________________" << endl;
        }
     cout <<"________________________List ends_______________________" << endl;
}

