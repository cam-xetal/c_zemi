#include "list.hpp"

LIST :: LIST(){
	head = new NODE();
	tail = new NODE();
	head->setNext(tail);
	tail->setPre(head);
}

LIST :: ~LIST(){
	p=head->getNext();
	while(this->deleteNode());
	delete head;
	delete tail;
}

void LIST :: newNODE(SPHERE* data){
	NODE* newNode;
	newNode = new NODE(data);
	p = tail->getPre();
	p->setNext(newNode);
	newNode->setNext(tail);
	newNode->setPre(p);
	tail->setPre(newNode);
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

	return true;
}