/**
 * @file bst.h
 * @author Paolo Pulcini, Matilde Castelli
 * @date 14 Feb 2020
 * @brief * @brief Header file that contains iterator class implementation
 */

#ifndef __iterator__
#define __iterator__
#include <iterator> // for std::forward_iterator_tag;


/**
 * @brief Implementation of an iterator for the bst
 * @tparam node_t Type of the node to which the iterator points to
 * @tparam C Type of the couple key:value of node. It can be const or not.
 */
template <typename node_t, typename C >
class iterator
{

	/** Node to which we are looking  */
	node_t * current;


	 // ************************  Aliases  **************************/
	public:

	/** Alias for the key:value couple (the node content) */
	using value_type= C;

	/** Alias reference for the key:value couple (the node content) */
	using reference=value_type&;

	/** Alias pointer for the key:value couple (the node content) */
	using pointer=value_type*;

	/** Alias  for the  iterator category */
	using iterator_category=std::forward_iterator_tag;

	/** Alias  for the difference type (pointers diff)s*/
	using difference_type = std::ptrdiff_t;
		

	node_t * getCurrent()
	{
		return current;
	}
	
	// ************************  Iterator constructors  **************************/
	
	 /**
	 * @brief Costum constructor for the empty iterator
	 */
	iterator()  noexcept: current{nullptr} {};


	/**
	 * @brief Costum Constructor for bst with root node.
	 * @param n A pointer to a nde of type node_t
	 */
	iterator(node_t * n) noexcept: current{n} {};
	

	// ************************  Arrow   **************************/
	

	 /**
	 * @brief Used to access the content of the node
	 * @return pointer to the couple (so that we can do tree.begin()->first)
	 */
	pointer operator->() const noexcept { return &(*(*this)); }
	

	// ************************  Pointer   **************************/
	

	 /**
	 * @brief Used to dereference the values of the node
	 * @return reference to the content of the pointer node
	 */
	reference operator*() const noexcept {return current->elem;};

	
	
	// ************************  ++it & it++   **************************/


	 /**
	 * @brief Used to increment the iterator (jump to next) (post increment)
	 * @return iterator& to the next node
	 * It is based on the in-order tree visit
	 * Algorithm Inorder(tree)
  	 * 1. Traverse the left subtree, i.e., call Inorder(left-subtree)
   	 * 2. Visit the root.
   	 * 3. Traverse the right subtree, i.e., call Inorder(right-subtree)
	 */ 
	iterator& operator++()
		{
		   if (!current)
		 {  
		 	return *this;
		 }
		else if(current->right)
		{
			current = current->right.get();
			while(current->left)
			{
				current = current->left.get();
			}
		} 
		else
		{
			
			node_t * TemporaryNode{current->parent};	
			while(TemporaryNode && current == TemporaryNode->right.get())
			{
				current = TemporaryNode;
				TemporaryNode = TemporaryNode->parent;
			}
			current = TemporaryNode;	
		}
		return *this;
		}


		 /**
		 * @brief Used to increment the iterator (jump to next)(preincrement)
		 * @return iterator to the next node
		 */ 
   		iterator operator++(int)
   		{
        	iterator it{*this};
        	++(*this);
        	return it;
    	}


		/**
		 * @brief Used to compare Iterators
		 * @return bool true if equals(point to the same node), false otherwise
		 */ 
    	bool operator==(const iterator& other) { return current == other.current; }

    	/**
		 * @brief Used to compare Iterators
		 * @return bool false if equals(point to the same node), true otherwise
		 */ 
    	bool operator!=(const iterator& other) { return current != other.current; }
};

#endif