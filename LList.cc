#include <bits/stdc++.h>
template<typename T> class LinkedList{
	struct Node{
		Node() = default;
		Node(Node* n) : data{n->data}, next{n->next} {}
		decltype(auto) operator=(Node* n){
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
		for(Node* n = LList.Head, *next = n->next; next; n = next, next = next->next) delete n;
	}
	void Swap(Node* lhs, Node* rhs){
		Node* tmp = lhs;
		lhs = rhs;
		rhs = tmp;
	}
	LinkedList<T> Reverse(){
		std::vector<T> Vector;
		for(Node* n = LList.Head; n; n = n->next) Vector.push_back(n->data);
		std::reverse(Vector.begin(), Vector.end());
		LinkedList<T> list(*Vector.begin(), *(Vector.end()-1));
		for(auto p = ++Vector.begin(), e = (Vector.end()-1); p != e; ++p) list += *p;
		return list;
	}
	LinkedList<T> Sort(){
		std::map<T, Node*> Map;
		for(Node* n = LList.Head; n; n = n->next) Map[n->data] = n;
        auto h = Map.begin(), t = (Map.end());
		LinkedList<T> list(h->first, (--t)->first);
		for(auto p = ++Map.begin(); p != t; ++p) list += p->first;
		return list;
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
        for(Node* n = LL.LList.Head; n != LL.LList.Tail; n = n->next) o << n->data << '\n';
        return o << LL.LList.Tail->data << '\n';
    }
};
