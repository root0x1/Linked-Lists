#include <bits/stdc++.h>
template<typename T> class LinkedList{
	struct Node{
		Node() = default;
		Node(Node* n) : data{n->data}, next{n->next} {}
		Node& operator=(Node* n){
			this->data = n->data;
			this->next = n->next;
			return *this;
		}
        T data;
		Node* next;
	};
	struct List{
		List() : Head{new Node}, Tail{new Node} {}
		Node* Head, *Tail;
	}LList;
	std::size_t Nodes;
public:
	LinkedList() = default;
	LinkedList(T head, T tail) : Nodes{2}{
		LList.Head->data = head;
		LList.Head->next = LList.Tail;
		LList.Tail->data = tail;
		LList.Tail->next = nullptr;
	}
	~LinkedList(){
		for(Node* n = LList.Head, *next = n->next; next; n = next, next = n->next) delete n;
	}
	void Swap(Node* lhs, Node* rhs){
		T tmp = lhs->data;
		lhs->data = rhs->data;
        rhs->data = tmp;
	}
	LinkedList<T> Reverse(){
		std::vector<T> Vector;
		for(Node* n = LList.Head; n; n = n->next) Vector.push_back(n->data);
		auto itr = std::begin(Vector), _itr = std::end(Vector);
		std::reverse(itr, _itr);
		LinkedList<T> list{*(itr++), *(--_itr)};
		for(; itr != _itr; ++itr) list += *itr;
		return list;    
	}
	LinkedList<T> Sort(){
		if(!std::is_pointer<T>::value)
		{	
			std::vector<T> Vector;
			for(Node* n = LList.Head; n; n = n->next) Vector.push_back(n->data);
			auto itr = std::begin(Vector), _itr = std::end(Vector);
			std::sort(itr, _itr);
			LinkedList<T> list{*(itr++), *(--_itr)};
			for(; itr != _itr; ++itr) list += *itr;
			return list;
		}else std::cerr << "Cannot Sort Pointers, T = " << typeid(T).name() << '\n';
	}
	const std::size_t GetNodes(){
		return Nodes;
	}
	Node* Search(T data){
		for(Node* n = LList.Head; n; n = n->next) if(n->data == data) return n;
		return nullptr;
	}	
	friend void operator+=(LinkedList<T>& LL, T data){
		if(LL.LList.Head->next == LL.LList.Tail){
			Node* n = new Node;
			n->data = data;
			n->next = LL.LList.Tail;
			LL.LList.Head->next = n;
			LL.Nodes += 1;
			return;
		}
		Node* prev = LL.LList.Head->next;
		for(;prev->next != LL.LList.Tail; prev = prev->next) ;
		Node* n = new Node;
		n->data = data;
		n->next = LL.LList.Tail;
		prev->next = n;
		LL.Nodes += 1;
	}
	friend void operator-=(LinkedList<T>& LL, T data){
		if(LL.LList.Head->data == data){
			Node* n = LL.LList.Head->next;
			delete LL.LList.Head;
			LL.LList.Head = n;
			LL.Nodes -= 1;
			return;
		}
		if(LL.LList.Tail->data == data){
			Node* prev = LL.LList.Head;
			while(prev->next != LL.LList.Tail) prev = prev->next;
			delete LL.LList.Tail;
			LL.LList.Tail = prev;
			LL.LList.Tail->next = nullptr;
			LL.Nodes -= 1;
			return;
		}
		Node* node = LL.Search(data);
		if (!node) return;
		Node *prev = LL.LList.Head, *next = node->next;
		while(prev->next != node) prev = prev->next;
		delete node;
		prev->next = next;
		LL.Nodes -= 1;
	}
    friend std::ostream& operator<<(std::ostream& o, LinkedList<T>& LL){
        for(Node* n = LL.LList.Head; n; n = n->next) o << n->data << '\n';
        return o;
    }
};

