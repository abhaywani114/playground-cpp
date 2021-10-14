#ifndef LINKED_LIST_H
	#define LINKED_LIST_H

#include<string>

#define OBJ_T template<typename Obj>


// ************************
// Linked List Node
// ************************

OBJ_T
class LList;


OBJ_T
class LListItr;

OBJ_T
class LListNode {
	Obj element;
	LListNode * next;

	LListNode(Obj & theElement = Obj(), LListNode * n = NULL) :
			element(theElement), next(n) {}

	friend class LList<Obj>;
	friend class LListItr<Obj>;
};

// ************************
// Linked List Iterator
// ************************
OBJ_T
class LListItr {
	private:
		LListNode<Obj> *current;
	 	LListItr( LListNode<Obj> *theNode) : current(theNode) {}\

		friend class LList<Obj>;
	public:
		LListItr() : current(NULL) {}

		bool isValid() const {
			return current != NULL;
		}

		void advance() const {
			if (isValid())
				current = current->next;
		}

		const Obj & retrive() const {
			if (!isValid())
				throw BadIterator();

			return current->element;
		} 

		std::string BadIterator() {
			return ("Invalid iterator");
		}
};

// ************************
// Linked List 
// ************************

OBJ_T
class LList {
	private:
		LListNode<Obj> *header;
	public:
		LList();
		LList(const LList & rhs);
		~LList();

		bool isEmpty() const;
		void makeEmpty();

		LListItr<Obj> zeroth() const;
		LListItr<Obj> first() const;

		void insert(const Obj & x, const LListItr<Obj> & p);
		void remove(const Obj & x);

		LListItr<Obj> find(const Obj & x) const;
		LListItr<Obj> findPrevious(const Obj & x) const;

	//	const LList & operator=(const LList & rhs);
};

OBJ_T
LList<Obj>::LList() {
	header = new LListNode<Obj>;
}

OBJ_T
LList<Obj>::LList(const LList & rhs) {
	LList();
	*this = rhs;	
}

OBJ_T
LList<Obj>::~LList() {
	makeEmpty();
	delete header;
}

OBJ_T
bool LList<Obj>::isEmpty() const {
	return header->next == NULL;
}

OBJ_T
void LList<Obj>::makeEmpty() {
	while(!isEmpty())
		remove(first().retrive());
}

OBJ_T
LListItr<Obj> LList<Obj>::zeroth() const {
	return LListItr<Obj>(header);
}

OBJ_T
LListItr<Obj> LList<Obj>::first() const {
	return LListItr<Obj>(header->first);
}

OBJ_T
void LList<Obj>::insert(const Obj & x, const LListItr<Obj> & p) {
	if (p.current != NULL)
		p.current->next = new LListNode<Obj> (x, p.current->next);
}

OBJ_T
void LList<Obj>::remove(const Obj & x) {
	LListNode<Obj> *p = findPrevious(x).current;

	if (p->next != NULL) {
		LListNode<Obj> *oldNode = p->next;
		p->next = p->next->next;
		delete oldNode;
	}
}

OBJ_T
LListItr<Obj> LList<Obj>::find(const Obj & x) const {
	LListNode<Obj> * p = header->next;

	while(p != NULL && p->element != 0)
		p = p->next;

	return LListItr<Obj>(p);
}

OBJ_T
LListItr<Obj> LList<Obj>::findPrevious(const Obj & x) const {
	LListNode<Obj> * p = header->next;

	while(p->next != NULL && p->next->element != 0)
		p = p->next;

	return LListItr<Obj>(p);

}
/*
OBJ_T
const LList & LList<Obj>::operator=(const LList & rhs) {
	if (this != &rhs) {
		makeEmpty();
		LListItr<Obj> ritr = rhs.first();
		LListItr<Obj> itr = zeroth();
		for(;ritr.isValid(); ritr.advance(), itr.advance()) {
			insert(ritr.retrive(), itr);
		}		
	}
}*/
#endif
