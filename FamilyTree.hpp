#ifndef FAMILYTREE_H
#define FAMILYTREE_H

#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;


namespace family{

	class Tree{
	public:
		string data;
		Tree *father;
		Tree *mother;
		int dep;


		Tree(string name){
			this->data = name;
			this->father = nullptr;
			this->mother = nullptr;
			int dep = 0 ;
		}

		Tree& addFather(string,string);
  		Tree& addMother(string,string);
		string find(string);
		string relation(string);
		void remove(string);
		void display();
		
		~Tree(){
		if (this->father != nullptr)
            delete this->father;
        if (this->mother != nullptr)
            delete this->mother;
		}

	private:
		bool addFather(Tree *tree, string root, string father);


		bool addFatherHelper(Tree* , string , string);
		bool addMotherHelper(Tree* , string , string);
		bool removeHelper(Tree* , string );
		string relationHelper(Tree* , string , int , int);
		string calculateRelation(int , int);
		string findHelper(Tree* , string , int , int);
		void displayHelper(Tree* , string* , int);

	};
}


#endif
