/**
 * @file bst.h
 * @author Paolo Pulcini, Matilde Castelli
 * @date 14 Feb 2020
 * @brief * @brief Header file that contains node class implementation
 */

#ifndef __Node__
#define __Node__

#include <iostream>
#include <memory>   // smart pointer
#include <utility>  // std::pair

/**
 * @brief Implementation of an iterator for the bst
 * @tparam T Type of the couple(std::pair<Tkey:Tvalue> of node.
 */
template <typename T>
struct Node
{
	
     /**
	 * @brief The content of the node
	 */
	T elem;


	 /**
	 * @brief Alias for the nodetype with more friendly name
	 */
	using value_type = T;

	 /**
	 * @brief Right and left child smart pointers
	 */
	std::unique_ptr<Node> left,right;

	
	/**
	 * @brief Raw pointer to the parent 
	 */
	Node * parent;



     /**
	 * @brief Default constructor for the node. Default is ok!
	 */
	Node() = default;


	 /**
	 * @brief Costum constructor for the node from a pair  key:value
	 * @param e a couple key:value of type T
	 */
	Node(T e): 
	elem{e},left{nullptr},right{nullptr},parent{nullptr} {};

	/**
	 * @brief Costum constructor for the node from a pair  key:value and parent
	 * @param e a couple key:value of type T
	 * @param p a raw pointer to which the attribute parent of the node 
	 */
	Node(T e, Node * p): 
	elem{e},left{nullptr},right{nullptr},parent{p} {};

	/**
	 * @brief Costum copy constructor for the node from a node
	 * @param Another node
	 */	
	Node(const Node& n) : elem{n.elem}, left{nullptr}, right{nullptr}, parent{n.parent} {}


	/**
	 * @brief Default destructor of the node
	 */	
	~Node() noexcept= default;
};

#endif

