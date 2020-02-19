#include "bst.h"




/************************* Insert *************************
* The function returns a pair of an iterator (pointing to the node) and a bool.
* The bool is true if a new node has been allocated, false otherwise (i.e., the key
* was already present in the tree). pair_type can be for example std::pair<const key_type,value_type> .
*/


template <class TKey,class TValue,class TComparison>
template <typename T>
std::pair<typename bst<TKey,TValue,TComparison>::Iterator, bool> bst<TKey,TValue,TComparison>::_insert(T&& x)
	{
		if(!root)
		{
			root.reset(new node_type{std::forward<T>(x)}); 			// It can infer if rvalue or lvalue and call the move or copy
			return std::make_pair(Iterator{root.get()},true);
		}
		
		node_type * node = root.get(); 							    // I start from the beginning
		
		while(true)
    	{
        	if( op(node->elem.first, x.first))  					// Comparison 
        	{	
        		if(node->right.get()==nullptr) 					    // I reached the right spot (and can't continue)
        		{
        			        			
					node->right.reset(new node_type{std::forward<T>(x),node}); 	// I insert the new node
					return std::make_pair(Iterator{node->right.get()},true);	// I return the pair
						
        		}
				else 
				{
        		  node = node->right.get();							 // I move down one level on the right 
        		}	
        	}
        	else if (op(x.first, node->elem.first))					 // I look left
        	{
        		if(node->left.get()==nullptr) 						 // I reached the right spot (and can't continue)
        		{
        			node->left.reset(new node_type{std::forward<T>(x),node});  // I insert the new node
        			return std::make_pair(Iterator{node->right.get()},true);  // I return the pair
        		}
        		else 
        		{   
        			  node = node->left.get();    					 // I move down one level on the right
        		}	
        	}
            
            else													 // I found the element and I won't do anything
        	  { 
        	  	std::cout<<"["<<x.first<<"] already present!"<<std::endl;	
        		return std::make_pair(Iterator{node},false);		 // I return wrong 
        	 }
    	}
    	
	}


template <class TKey,class TValue,class TComparison>
std::pair<typename bst<TKey,TValue,TComparison>::Iterator, bool> bst<TKey,TValue,TComparison>::insert(const std::pair<const TKey, TValue>& x)
	{
	    return _insert(x);   	
	}
	
template <class TKey,class TValue,class TComparison>
std::pair<typename bst<TKey,TValue,TComparison>::Iterator, bool> bst<TKey,TValue,TComparison>::insert(std::pair<const TKey, TValue>&& x)
	
	{
		return _insert(std::move(x)); 
	}


/************************* Begin  *************************
* Return an iterator to the left-most node (which, likely, is not the root node).
*/

template <class TKey,class TValue,class TComparison>
typename bst<TKey,TValue,TComparison>::node_type*  bst<TKey,TValue,TComparison>::_begin() const noexcept
{
	if(root!=nullptr)
        {
            node_type* n = root.get();
            while(n->left)
                n = n->left.get();
            return n;
        }
        else{
            return nullptr;
        }
}

template <class TKey,class TValue,class TComparison>
typename bst<TKey,TValue,TComparison>::Iterator bst<TKey,TValue,TComparison>::begin() noexcept
{	
        return Iterator{_begin()};
}

template <class TKey,class TValue,class TComparison>
typename bst<TKey,TValue,TComparison>::constIterator bst<TKey,TValue,TComparison>::begin() const noexcept
{
            return constIterator{_begin()};
        
}

template <class TKey,class TValue,class TComparison>
typename bst<TKey,TValue,TComparison>::constIterator bst<TKey,TValue,TComparison>::cbegin() const noexcept
{
	return constIterator{_begin()};
}





/************************* Find  *************************
* Find a given key. If the key is present, returns an iterator to the proper node, end() otherwise
*/
template <class TKey,class TValue,class TComparison>
typename bst<TKey,TValue,TComparison>::node_type* bst<TKey,TValue,TComparison>::_find(const TKey& x)
{
	auto tmp=root.get();
	while(tmp)
	{
		if(!op(tmp->elem.first, x) && !op(x,tmp->elem.first))  // Current node Key == Searched key
			return tmp;

		if(op(tmp->elem.first,x))                              // Current node Key < Searched key
        	tmp=tmp->right.get();
		else
			tmp=tmp->left.get();					           // Current node Key < Searched key
	}
	return nullptr;
}

template <class TKey,class TValue,class TComparison>
typename bst<TKey,TValue,TComparison>::Iterator bst<TKey,TValue,TComparison>::find(const TKey& x) 
	{
		auto tmp=_find(x);
	    if(tmp == nullptr) return end();
	    else return Iterator{tmp};
	}

template <class TKey,class TValue,class TComparison>
typename bst<TKey,TValue,TComparison>::constIterator bst<TKey,TValue,TComparison>::find(const TKey& x) const
{
   	auto tmp=_find(x);
    if(tmp == nullptr) return cend();
    else return constIterator{tmp};
}


/************************* Balance  *************************
Balance the tree. A simple and naive implementation is fine.
*/

template <class TKey,class TValue,class TComparison>
void bst<TKey,TValue,TComparison>::balance()
	{

		Iterator it{this->begin()}; 				// Here I get the boundaries
	    Iterator end{this->end()};
	    
	    if(it == end)								// Nothing to say about this
	    {
	     std::cout<<"Empty tree"<<std::endl;
    	}
        else										// Here I fill a vector with the values and rebuild a
    	{											// tree with a simple approach
	    std::vector<std::pair<TKey, TValue>> v;
	    
	    for(; it != end; ++it)	
	        v.push_back(*it);
	   		
         this->clear();
       	 helper(v, 0, v.size()-1);					// I call a recursive function the does the hard part
		}

	}


/************************* Helper  *************************
As the name says, it is just an helper 
*/

template <class TKey,class TValue,class TComparison>
void bst<TKey,TValue,TComparison>::helper(std::vector<std::pair<TKey, TValue>>& v,int start, int end)
	{
		if(start > end)
		    {
		        return;
		    }

	    int mid = (start + end) / 2;
	    insert(v[mid]);
	    helper(v, start, mid - 1);
	    helper(v, mid + 1, end);
		
	}


/************************* Subscripting  *************************
*Returns a reference to the value that is mapped to a key equivalent to x , 
*performing an insertion if such key does not already exist.
*/
    template <class TKey,class TValue,class TComparison>
	TValue& bst<TKey,TValue,TComparison>::operator[](TKey&& x)
	{
		auto it {insert(std::pair<TKey, TValue> {std::move(x),TValue{}}).first};
	 	return (*(it)).second;
	}	

  template <class TKey,class TValue,class TComparison>
  TValue& bst<TKey,TValue,TComparison>::operator[](const TKey& x)
	{
		auto it {insert(std::pair<TKey, TValue> {x,TValue{}}).first};
	 	return (*(it)).second;
	}


/************************* Printing  *************************
* These actually are just a re-elaboration of some tree-pretty-printing codes I found on github
*/

template <class TKey,class TValue,class TComparison>
void bst<TKey,TValue,TComparison>::printNode(const std::unique_ptr<node_type>& node, std::ostream& os) const
	{
	    os << node->elem.first << ":" << node->elem.second << std::endl;
	}

template <class TKey,class TValue,class TComparison>
void bst<TKey,TValue,TComparison>::printTreeStructure(const std::unique_ptr<node_type>& node, std::ostream& os, bool right, std::string indent) const
	{
	    if (node->right) 
	    {
	        printTreeStructure(node->right, os, true, indent + (right ? "        " : " |      "));
	    }
	    os << indent << (right ? " /" : " \\") << "------- ";
	    printNode(node, os);
	    if (node->left) 
	    {
	        printTreeStructure(node->left, os, false, indent + (right ? " |      " : "        "));
	    }
	}

template <class TKey,class TValue,class TComparison>
std::ostream& bst<TKey,TValue,TComparison>::printTree(std::ostream& os) const
	{
	    if (!root)
	    {
	        return os << "Empty";
	    }
	    if (root->right) 
	    {
	        printTreeStructure(root->right, os, true, "");
	    }
	    printNode(root, os);
	    if (root->left)
	    {
	        printTreeStructure(root->left, os, false, "");
	    }
	    return os;
	}




/************************* Copy  **************************
* Performs deep copy with the help of an auxiliary function
*/

	/***** Copy Constructor******/
    template <class TKey,class TValue,class TComparison>
	bst<TKey,TValue,TComparison>::bst(const bst<TKey,TValue,TComparison>& tree) 
	{
		copyelement(tree.root); 
	};

	/****** The helper function ******/
	template <class TKey,class TValue,class TComparison>
	void bst<TKey,TValue,TComparison>::copyelement(const std::unique_ptr<node_type>& nodo)
	{
		if(nodo)
		{
			insert(nodo->elem);
			copyelement(nodo->left);
			copyelement(nodo->right);
		}
	}

	/****** The copy assignment ******/
	template <class TKey,class TValue,class TComparison>
	bst<TKey,TValue,TComparison>& bst<TKey,TValue,TComparison>::operator=(const bst& tree)
	{
		clear();
		copyelement(tree.root);
		return *this;
	};




/************************* Erase  **************************
* Removes the element (if one exists) with the key equivalent to key.
* It uses a function to swap two nodes. Work in progress.
*/

template <class TKey,class TValue,class TComparison>
void bst<TKey,TValue,TComparison>::move_left(node_type* A, node_type* B)
    {
        B->parent = A->parent;
        B->left = std::move(A->left);
        //A->right = std::move(A->right);
        B->parent->left=std::move(A->right);
       //I reset the pointer linked to the erased node   
        std::cout<< B->elem.first << std::endl;

}
template <class TKey,class TValue,class TComparison>
void bst<TKey,TValue,TComparison>::move_right(node_type* A, node_type* B)
    {
        B->parent = A->parent;
        B->left = std::move(A->left);    
        A->parent->right=std::move(A->right);
        std::cout<<B->elem.first<< std::endl;

}


template <class TKey,class TValue,class TComparison>
void bst<TKey,TValue,TComparison>::erase(const TKey& x)
    {
    	{

        /** CASE: Empty tree */
        if(!root) return;
        
        auto it = find(x);

        /** CASE: Node not found */
         if(it==end()) return;

        /** CASE: Leave */
        if(!(it.getCurrent()->left) && !(it.getCurrent()->right))
        {
           /* I reset the pointer linked to the erased node  */
          (it == Iterator{it.getCurrent()->parent->right.get()}) ? \
          it.getCurrent()->parent->right.reset() :  it.getCurrent()->parent->left.reset();
        } 

        /* CASE: Others */
        auto A=it.getCurrent();
               

        /* CASE: Two children */
        if (A->right && A->left) 				// If the node to erase has 2 children
        {										// The left subtree is attached to the leftmost
            ++it;								// node of the  right subtree.
            auto sub =it.getCurrent();
         	sub->left = std::move(A->left);
            sub->left->parent = sub;
          }
            
        /* CASE: Root */
        if(!(A->parent))						// After that the left subtree has been moved we 
        {										// assign nullpointer to the parentof the node 
            A->right->parent = nullptr;			// node that will become the root
            root = std::move(A->right);
        }
        else{
            
            if(A->parent->right.get() == A)  					/* CASE: Erase a right child  */
            {													// To enter I check if I'm the right child 
                if(A->right)									// If the target node has a right child,  
                 {												// the father of the right child becomes 
                    A->right->parent = A->parent;				// the father of the target node. I std::move the
                    A->parent->right=std::move(A->right);		// right child of the target node to the fathe's right  
                }												// child of the target node. If it is the left, I do the
                else if(A->left)								// same (in the opposite direction)
                {	
                    A->left->parent= A->parent;
                    A->parent->right=std::move(A->left); 
                }
            }
                    
   			else												/* CASE: Erase a left child  */
            {															
                if(A->right)									// See above
                {
                    A->right->parent= A->parent;
                    A->parent->left=std::move(A->right);
                }
                else if(A->left)
                {
                    A->left->parent=A->parent;
                    A->parent->left=std::move(A->left);
            
                }
        
            }
        }

    
}
    }