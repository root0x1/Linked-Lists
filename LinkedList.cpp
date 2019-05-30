//File Reading using Single-Linked-Lists
// KaliMoro
#include <iostream>
#include <fstream>
#include <map>
template<typename T> class LinkedList{
private:
	struct Node{
		std::size_t line;
		T Data;
		Node* pNext;
	};
	struct List{
		Node* Head, *Tail;
	};
	List* pList;
public:
	LinkedList() : pList(new List) {}
	LinkedList(const std::size_t& fline, const T& hData, const std::size_t& lline, const T& tData) : pList(new List){
        pList->Head = new Node, pList->Tail = new Node;
		pList->Head->line = fline;
		pList->Head->Data = hData;
		pList->Head->pNext = pList->Tail;
		pList->Tail->line = lline;
		pList->Tail->Data = tData;
		pList->Tail->pNext = nullptr;
	}
	std::ostream& operator<<(std::ostream& o){
		for(Node* n = pList->Head; n; n = n->pNext) o << n->line << ") " <<n->Data << '\n';
		return o;
	}
	Node* operator[](const T& Data){
		for(Node* node = pList->Head; node->Data != Data; node = node->pNext) if(node->Data == Data) return node;
	}
	Node* operator[](const std::size_t& line){
		for(Node* node = pList->Head; node->line != line; node = node->pNext) if(node->line == line) return node;
	}
	void Add(const std::size_t& l, const T& Data){
		Node* n = new Node;
		n->line = l;
		n->Data = Data;
		n->pNext = nullptr;
		pList->Tail->pNext = n;
		pList->Tail = n;
	}
	~LinkedList(){
		for(Node* n = pList->Head, *tmp = nullptr; n; n = tmp){
			tmp = n->pNext;
			delete n;
		}
		delete pList;
	}
};
class FileReader{
private:
	LinkedList<std::string> Line;
public:
	FileReader(const std::string& File) : Line(1, File, 2, "\nFile Reader is running: \n"){
		if(auto ifs = std::ifstream(File)){
			std::map<std::size_t, std::string> Map;
			for(std::size_t idx{3}; ifs >> Map[idx]; idx++){
				Line.Add(idx, Map[idx]);
			}
		}
	}
	std::ostream& operator<<(std::ostream& o){
		Line << o;
        return o;
	}
	~FileReader() = default;
};
