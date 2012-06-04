#include <stdio.h>
#include "sphere.h"

class NODE{
private:
	SPHERE* data;
	NODE* pre;
	NODE* next;
public:
	//inline--start
	NODE(void);
	NODE(SPHERE* data);
	~NODE();
	SPHERE* getData();
	void setData(SPHERE* data);
	void setNext(NODE* p);
	void setPre(NODE* p);
	NODE* getNext();
	NODE* getPre();
	//inline--end
};

inline NODE :: NODE(void){
	this->next = NULL;
	this->pre = NULL;
}

inline NODE :: NODE(SPHERE* data){
	this->next = NULL;
	this->pre = NULL;
	this->data = data;
}
inline NODE :: ~NODE(){
	delete data;
}

inline SPHERE* NODE :: getData(){
	return this->data;
}

inline void NODE :: setData(SPHERE* data){
	this->data = data;
}

inline void NODE :: setNext(NODE* p){
	this->next = p;
}

inline void NODE :: setPre(NODE* p){
	this->pre = p;
}

inline NODE* NODE :: getNext(){
	return this->next;
}

inline NODE* NODE :: getPre(){
	return this->pre;
}