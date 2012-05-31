#include "list.h"

LIST :: LIST(){
	head = new NODE();
	tail = new NODE();
	head->setNext(tail);
	tail->setPre(head);
	//p = head->getNext();
}

void LIST :: newNODE(SPHERE* data){
	NODE* newNode;
	newNode = new NODE(data);
	p = head;
	while(this->next());
	p->setNext(newNode);
	newNode->setNext(tail);
	newNode->setPre(p);
}

bool LIST :: deleteNode(){
	NODE* tmp;
	if(p == head || p == tail)
		return false;
	tmp = p;
	p = p->getNext();
	tmp->getPre()->setNext(p);
	p->setPre(tmp->getPre());
	delete tmp;
	
	if(p == tail)
		return false;
	return true;
}