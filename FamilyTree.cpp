#include "FamilyTree.hpp"
#include <iostream>
#include <string.h>
#include <string>
#include <exception>

using namespace std;

namespace family{

	Tree& Tree::addFather(string r, string s){
   		 if (addFatherHelper(this,r,s)) 
			return *this;
   		 else 
			throw runtime_error("there is no root with this name:" + r );
	}

	bool Tree::addFatherHelper(Tree *r , string s, string f){
   		if(r == nullptr) 
			return false;

   		if (r->data == s){
      		if (r->father == nullptr){
           		r->father = new Tree(f);
            	if (r->mother == nullptr) 
					this->dep++; 
            	return true;
        	}
			else 
				throw runtime_error("this root has father");
		   }
    
    return addFatherHelper(r->father , s , f) || addFatherHelper(r->mother , s , f);
}

	Tree& Tree::addMother(string r,string s){
   		 if (addMotherHelper(this,r,s)) 
			return *this;
   		 else 
			throw runtime_error("there is no root with this name:" + r );
	}

	bool Tree::addMotherHelper(Tree *r , string s, string f){
   		 if(r == nullptr) 
			return false;

   		 if (r->data==s){
      		if (r->mother == nullptr){
           		r->mother = new Tree(f);
            	if (r->father == nullptr) 
					this->dep++; 
            	return true;
        		} 
			else 
				throw runtime_error("this root has mother");
			}
    return addMotherHelper(r->father , s , f) || addMotherHelper(r->mother , s , f);
}

	void Tree::remove(string s){
   		if (this->data == s)
        	throw runtime_error("cannot remove the Root of the Tree!!");
    	if(!removeHelper(this,s))
        	throw runtime_error("there is no root to remove with this name: " + s);
	}

	bool Tree::removeHelper(Tree* r, string s){
    	if(r == nullptr) 
			return false;

    	if (r->father != nullptr && r->father->data == s) {
        	delete r->father;
        	r->father = nullptr;
        	return true;
    	}

    	if (r->mother != nullptr && r->mother->data == s) {
        	delete r->mother;
        	r->mother = nullptr;
        	return true;
    	}

    	return removeHelper(r->father,s) || removeHelper(r->mother,s);
}

	string Tree::relation(string s){
    	string ans = relationHelper(this,s,0,0);
		if (ans == "")
			return "unrelated";
   		else
			return ans;
	}


	string Tree::relationHelper(Tree *r,const string s,int d,int g){
    	string ans = "";
    	if (r->data == s)
        	return calculateRelation(d , g);
    	if (r->father != nullptr)
        	ans = relationHelper(r->father,s,++d,0);
    	else 
			d++;

    	if (ans == "" && r->mother != nullptr)
        	ans = relationHelper(r->mother, s,d,1);
    	return ans;
	}

	string Tree::calculateRelation(int d,int g){
	if(d == 0)
		return "me";

    int n= d-2;
	string ans = "";
	
    if (n >= 0){
        for (int i = 0; i < n; ++i) 
			ans += "great-";
		
		if(g == 0)
			ans += "grandfather";
		else
			ans += "grandmother";
		return ans;
    }
    
	if(g == 0)
		ans = "father" ;
	else
		ans = "mother" ;

	return ans;
}

	string Tree::find(string s){
    	string ans = findHelper(this,s,0,0);
		if (ans == "")
			throw runtime_error("there is no relation like this: "+ s);
		return ans;
    	
	}

	string Tree::findHelper(Tree *r,string s,int d,int g){
    	string ans = "";
    	if (s == calculateRelation(d,g))
       		return r->data;
    	if (r->father != nullptr)
        	ans = findHelper(r->father,s,++d,0);
    	else 
			d++;
    	if (ans == "" && r->mother != nullptr)
        	ans = findHelper(r->mother, s,d,1);
    	return ans;
	}

	void Tree::display(){
    	int size = this->dep +1;
    	string ans[size];
    	displayHelper(this,ans,0);
    	for(int i = 0; i < size; ++i){
        	for (int j = 0; j <(size*4)-(i*5) ; ++j) {
				cout<<" ";
				} 
        	cout << ans[i].substr(0, ans[i].size()-3) << "\n";
    	}
	}

	void Tree::displayHelper(Tree *r,string* s,int d) {
    	if (r != nullptr) {
       		s[d] += r->data + " _ ";
        	displayHelper(r->father,s,++d);
        	displayHelper(r->mother,s,d);
    	}
	}

}
