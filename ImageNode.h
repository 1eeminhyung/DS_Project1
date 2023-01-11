#ifndef IMAGENODE
#define IMAGENODE

#include <string>
#include <iostream>

using namespace std;

//declare ImageNode class used by list class
class ImageNode
{
	friend class TreeNode;
	friend class BinarySearchTree;
private:
	//declare memeber variable
	string dirname;
	int unique_number;	
	string m_name;
	ImageNode* next;
	ImageNode* down;

public:
	ImageNode() { 						//define constructor
		this->dirname = "";
		this->m_name = "";
		this->unique_number = 0;
		this->next = nullptr;
		this->down = nullptr;
	}
	ImageNode(string dir, int number, string name)		//overloading
		:
		m_name(name),
		dirname(dir),
		unique_number(number)
	{ this->next = nullptr; this->down = nullptr; }

	//declare and define member function
	void Setdir(string dir) { this->dirname = dir; }
	void Setname(string name) { this->m_name = name; }
	void Setnum(int num) { this->unique_number = num; }
	void Setnext(ImageNode* node) { this->next = node; }
	void Setdown(ImageNode* node) { this->down = node; }



	string Getdir() { return this->dirname; }
	string Getname() { return this->m_name; }
	int Getnum() { return this->unique_number; }
	ImageNode* Getnext() { return this->next; }
	ImageNode* Getdown() { return this->down; }
};

#endif
