#include <stdio.h>
#include "node.hpp"

class LIST{
private:
	NODE* head;
	NODE* tail;
	NODE* p;
public:
	LIST();
	~LIST();
	void newNODE(SPHERE* data);
	bool deleteNode();
	//inline--start
	void setHead();
	SPHERE* get();
	bool pre();
	bool next();
	int count();
	//inline--end
};

inline void LIST :: setHead(){
	p = head;
}

inline SPHERE* LIST :: get(){
	return p->getData();
}

inline bool LIST :: pre(){
	if(p->getPre() == head || p == head)
		return false;
	p = p->getPre();
	return true;
}

inline bool	LIST :: next(){
	if(p->getNext() == tail || p == tail)
		return false;
	p = p->getNext();
	return true;
}

inline int LIST :: count(){
	p = head;
	int i=0;
	while(p != tail){
		p = p->getNext();
		i++;
	}
	p = head;
	return i;
}