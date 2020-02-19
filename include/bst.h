/**
 * @file bst.h
 * @author Paolo Pulcini, Matilde Castelli
 * @date 14 Feb 2020
 * @brief * @brief Header file that contains prototypes for a modern C++ binary search tree implementation
 */
#ifndef __bst__
#define __bst__

#include <iostream> 	// << operator
#include <memory> 		// unique pointers
#include <vector> 		// vector class
#include <utility> 		// std::pair
#include <iterator>
#include <iomanip>      // std::setw
#include "Node.h"
#include "iterator.h"


/**
 * @brief Implementation of a binary search tree with templates
 * @tparam TKey Type of node keys.
 * @tparam TValue Type of node values.
 * @tparam TComparison Type of the comparison iterator between nodes. Default std::less<TKey>.
 */
template <class TKey,class TValue,class TComparison = std::less<TKey>>
class bst
{

	public:

	 /**
	 * @brief Alias for node_type
	 */
	using node_type = Node<std::pair<const TKey, TValue>>;
	 /**
	 * @brief Alias for Iterator
	 */
	using Iterator = iterator<node_type, typename node_type::value_type>;
	 /**
	 * @brief Alias for contiterator
	 */
	using constIterator = iterator<node_type,const typename node_type::value_type>;

	private:

	/**
	 * @brief The bst is represented by its root, which is a smart pointer
	 */
	std::unique_ptr<node_type> root;

	/**
	 * @brief Custom comparison operator.
	 */
	TComparison op;

	// ************************* Private Methods *************************/


	/**
	 * @brief Helper function of balance for copy constructor
	 * @param nodo the node we are looking at
	 */
	void copyelement(const std::unique_ptr<node_type>& nodo);

	 /**
	 * @brief Helper function of balance for balance and erase
	 * @param v vectors of sorted values
	 * @param start lower index
	 *  @param end upper index
	 */
	void helper(std::vector<std::pair<TKey, TValue>>& v,int start, int end);


	/**
	 * @brief It prints the value of a  node nicely
	 * @param node Just a node
	 * @param os An ostream
	 */
	void printNode(const std::unique_ptr<node_type>& node, std::ostream& os) const;


	/**
	 * @brief Helper function of print tree which prints a piece of the tree
	 * @param x key that I look for
	 * @param os An ostream
	 * @param right A boolean needed to correctly print the tree
	 * @param indent The indentation
	 */
	void printTreeStructure(const std::unique_ptr<node_type>& node, std::ostream& os, bool right, std::string indent) const;


	/**
	 * @brief Helper function to make the begin function correctly use move or copy
	 */
	node_type* _begin() const noexcept;


	/**
	 * @brief Helper function to make the begin function correctly use move or copy
	 */
	template <typename T>
	std::pair<Iterator,bool> _insert(T&& x);


	/**
	 * @brief Helper function for find
	 */
	node_type* _find(const TKey& x);



	/**
	 * @brief Helper function for erase
	 */
	void move_left(node_type* A, node_type* B);

	/**
	 * @brief Helper function for erase
	 */
	void move_right(node_type* A, node_type* B);

	public:

	// ************************ Iterators **************************/

     /**
	 * @brief Used by the iterator to start
	 * @return Iterator Returns an iterator to the leftmost node.
	 */
	Iterator begin() noexcept;
	 /**
	 * @brief Used by the iterator to know when to stop.
	 * @return Iterator Returns an iterator to nullptr.
	 */
	Iterator end(){ return Iterator{nullptr}; };

  

	// ************************ Const Iterators **************************/



    /**
	 * @brief Used by the constant iterator to start
	 * @return Iterator Returns a const iterator to the leftmost node.
	 */
	constIterator begin() const noexcept;

	 /**
	 * @brief Used by the constant iterator to start
	 * @return constIterator Returns a constant iterator to the leftmost node.
	 */
  	constIterator cbegin() const noexcept;

	  /**
	 * @brief Used by the constant iterator to know when to stop.
	 * @return constIterator Returns a constant iterator to nullptr.
	 */
  	constIterator end()  const noexcept { return constIterator{nullptr}; };

  	 /**
	 * @brief Used by the constant iterator to know when to stop.
	 * @return constIterator Returns a constant iterator to nullptr.
	 */
  	constIterator cend() const noexcept  { return constIterator{nullptr}; };



     // ************************ Tree constructors **************************/

	/**
	 * @brief Default constructor for bst
     */
	bst() noexcept = default;


	 /** 
	 * @brief Constructor for bst with root node.
	 * @param elem A couple <Key:Value> 
	 */
	bst(std::pair<const TKey,TValue> elem):
         root{new node_type{elem}} {};


	/**
	 * @brief Constructor for bst with comparison type.
	 * @param x A comparison method s.a.  std::less<TKey>
	 */
	explicit bst(TComparison x): op{x}{};


	// ************************* Copy Semantic **************************/

	 /**
	 * @brief Copy constructor for bst
	 * @param tree The template bst to be copied.
	 * 
	 */
    bst(const bst& tree);

     /**
	 * @brief Copy assignment for bst
	 * @param tree The template bst to be copy-assigned
	 * @return bst& The modified tree.
	 */
    bst& operator=(const bst& tree);


    
    // ************************ Move Semantic **************************/

    /**
	 * @brief Default move assignment
	 * @param tree The template bst to be moved into a new one.
	 * @return bst& The modified tree.
	 */
    bst& operator=(bst&&  tree) noexcept =default; 
    
      /**
	 * @brief Default move assignment
	 * @param tree The template bst to be move-assigned into a new one.
	 */
    bst(bst&& tree) noexcept=default;

  

    // ************************* Subscripting operator**************************/

      /**
	 * @brief Operator [] access a node value or insert a new one.
	 * @param x The key for which we want to know the value
	 * @return TValue& The value of the key or 0 if the key was inserted
	 */
    TValue& operator[](TKey&& x);

      /**
	 * @brief Operator [] access a node value or insert a new one.
	 * @param x The key for which we want to know the value
	 * @return TValue& The value of the key or 0 if the key was inserted
	 */
    TValue& operator[](const TKey& x);
		

	// ************************ Insertion *************************/

	 /**
	 * @brief Insert a couple key, value in the right position of the tree
	 * @param x Couple key, value (Left value) to be inserted
	 * @return std::pair<Iterator, bool> with bool True if the value was correctly inserted and an iterator to the node of the inserted value
	 */
	std::pair<Iterator, bool> insert(const std::pair<const TKey,TValue>& x);

	/**
	 * @brief Insert a couple key, value in the right position of the tree
	 * @param x Couple key, value(Right value) to be inserted
	 * @return std::pair<Iterator, bool> with bool True if the value was correctly inserted and an iterator to the node of the inserted value
	 */
	std::pair<Iterator, bool> insert(std::pair<const TKey,TValue>&& x);


	/**
	 * @brief Insert couple of variables without pair them in advance
	 * @param args key, value to be inserted
	 * @return std::pair<Iterator, bool> with bool True if the value was correctly inserted and an iterator to the node of the inserted value
	 */
	template< class... Types >
	std::pair<Iterator,bool> emplace(Types&&... args)
	{
		return insert(std::make_pair(std::forward<Types>(args)...)); 
	}

	// ************************* Controls functions *************************/

	/**
	 * @brief Empty the tree
	 */  
	void clear() noexcept { root.reset(); }; // We are releasing, not aquiring resources

	/**
	 * @brief Look for a key in the bst
	 * @param x The key  which we look for
	 * @return Iterator which points to the key if found, to nullpointer otherwise (end())
	 */
	Iterator find(const TKey& x);


	/**
	 * @brief Look for a key in the bst
	 * @param x The key  which we look for
	 * @return constIterator which points to the key if found, to nullpointer otherwise (end())
	 */
	constIterator find(const TKey& x) const;

	/**
	 * @brief Rebalance the tree
	 * It basically collects all the values and rebuild the tree using the following fashion
	 * 1) Get the Middle of the array and make it root.
	 * 2) Recursively do same for left half and right half.
     *  a) Get the middle of left half and make it left child of the root created in step 1.
     *  b) Get the middle of right half and make it right child of the root created in step 1. 
     * from https://www.geeksforgeeks.org/sorted-array-to-balanced-bst/
	*/
	void balance();




	 /**
	 * @brief Helper function of balance for balance and erase
	 * @param x key that I look for
	 * Practically, it builds a new tree without the node with key x, if found. Otherwise it does nothing.
	 */
	void erase(const TKey& x);

	

    
    // ************************* Printing  *************************
     
	
	 /**
	 * @brief Pretty printing of the tree
	 * @param node Just a node
	 * @param os An ostream
	 */
	std::ostream& printTree(std::ostream& os) const;
	



	 // ************************ Put though operator override  *************************

	 /**
	 * @brief It call the function print tree to draw the tree
	 * @param os An ostream
	 * @param x The tree we want to print
	 */
	
	friend std::ostream& operator<<(std::ostream& os,  const bst& x) 
		{

			for (const auto& pair : x )
				os << "["<<pair.first<<":"<<pair.second<<"]";
			os<<std::endl;

			
			return x.printTree(os);	
		};





};

#include "methods.h"


#endif