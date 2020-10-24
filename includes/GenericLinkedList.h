#ifndef __GENERIC_LINKED_LIST__
#define __GENERIC_LINKED_LIST__

#include <ostream>

using namespace std;

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
	GenericLinkedList(const GenericLinkedList& other) : head(nullptr)
	{
		*this = other;
	}

	GenericLinkedList(GenericLinkedList&& other)
	{
		*this = other;
	}

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

	const T* operator[](std::size_t index) const
	{
		unsigned count = 0;
		Node<T>* temp = this->head;
		while (temp != nullptr)
		{
			if (count == index)
				return temp->getData();
			temp = temp->getNext();
			count++;
		}
		return nullptr;
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

		if (current->getNext() == nullptr)
			prev->setNext(nullptr);
		else
			prev->setNext(current->getNext());

		return true;
	}

	bool update(const T& s)
	{
		Node<T>* current = this->head;
		while (current != nullptr && !(*(current->getData()) == s))
		{
			current = current->getNext();
		}

		if (current == nullptr)
			return false;

		*(current->getData()) = s;
		return true;
	}

	void printT(std::ostream& os) const
	{
		Node<T>* temp = this->head;
		while (temp != nullptr)
		{
			os << *temp->getData() << endl;
			temp = temp->getNext();
		}
	}

	GenericLinkedList& operator=(const GenericLinkedList& otherL)
	{
		this->~GenericLinkedList();

		if (otherL.head == nullptr)
		{
			this->head = nullptr;
			return *this;
		}

		this->head = new Node<T>(*otherL.head->getData());

		Node<T>* otherTemp = otherL.head;
		Node<T>* thisTemp = this->head;

		while (otherTemp->getNext() != nullptr)
		{
			thisTemp->setNext(*(otherTemp->getNext()->getData()));
			thisTemp = thisTemp->getNext();
			otherTemp = otherTemp->getNext();
		}

		return *this;
	}

	GenericLinkedList& operator=(GenericLinkedList&& otherL)
	{
		this->head = otherL.head;
		otherL.head = nullptr;
		return *this;
	}
};

#endif