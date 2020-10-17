#ifndef __GENERIC_LINKED_LIST__
#define __GENERIC_LINKED_LIST__

#include <ostream>



template <class T> class GenericLinkedList
{
private:
	template <class T> class Node
	{
	private:
		T* data;
		Node* nextT;
	public:
		Node(const T& s) :
			nextT(nullptr)
		{
			data = new T(s);
		}

		~Node()
		{
			delete this->data;
		}

		T* getData()
		{
			return this->data;
		}

		void setData(const T& s)
		{
			delete this->data;
			this->data = new T(s);
		}

		Node* getNext()
		{
			return this->nextT;
		}

		void setNext(Node* node)
		{
			delete nextT;
			this->nextT = node;
		}

		void setNext(const T& s)
		{
			delete nextT;
			this->nextT = new Node(s);
		}

	};

	Node<T>* head;
public:
	GenericLinkedList() : head(nullptr) {}

	~GenericLinkedList()
	{
		Node<T>* current = head;
		Node<T>* next;
		
		while (current != nullptr)
		{
			next = current->getNext();
			delete current;
			current = next;
		}
	}

	void addTToEnd(const T& s)
	{
		if (this->head == nullptr)
		{
			this->head = new Node<T>(s);
			return;
		}

		Node<T>* current = this->head;
		while (current->getNext() != nullptr)
			current = current->getNext();

		current->setNext(s);
	}

	bool removeT(const T& s)
	{
		Node<T>* current = this->head;
		Node<T>* prev = nullptr;
		while (current != nullptr && !(*(current->getData()) == s))
		{
			prev = current;
			current = current->getNext();
		}

		if (current == nullptr)
			return false;

		if (prev == nullptr)
		{
			Node<T>* temp = this->head->getNext();
			delete this->head;
			this->head = temp;
			return true;
		}

		prev->setNext(current->getNext());
		delete current;
	}

	void printT()
	{
		Node<T>* temp = this->head;
		while (temp != nullptr)
		{
			std::cout << *temp->getData() << std::endl;
			temp = temp->getNext();
		}
	};
};

#endif