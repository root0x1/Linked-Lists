#ifndef SCRIPT_H
#define SCRIPT_H
#pragma once
struct List{
	int Data;
	List* Next;
};
struct Linked{
	List* Head;
	List* Tail;
};
typedef List* pList;
class Lists{
public:
	Lists(const int hData, const int tData, Linked* link){
		Head->Data = hData;
		Head->Next = Tail;
		Tail->Data = tData;
		Tail->Next = nullptr;
		link->Head = Head;
		link->Tail = Tail;
	}
	size_t GetSize(Linked* link) const{
		size_t i = 0;
		if(!link) return -1;
		for(pList list = link->Head;list;list = list->Next, i++) ;
		return i;
	}
	void PrintList(Linked* link){
		if(!link) return;
		if(GetSize(link) == 0) std::clog << "Empty List!\n";
		for(pList list = link->Head;list;list = list->Next)
			std::cout << "Data: " << list->Data << std::endl;
	}
	pList AddNode(const int Data, Linked* link){
		pList node = new List, prev = link->Head;
		node->Data = Data;
		for(; prev->Next != link->Tail; prev = prev->Next) ;
		prev->Next = node;
		return node->Next = link->Tail;
	}
	pList SearchNode(const int Data, Linked* link){
		pList list = link->Head;
		for(int i = list->Data; list; list = list->Next, i = list->Data){
			if(i == Data)
				return list;
		}
		return nullptr;
	}
	pList RemoveNode(const int Data, Linked* link){
		if(SearchNode(Data, link) == link->Head){
			pList next = link->Head->Next;
			delete Head;
			Head = nullptr;
			return link->Head = next;
		}
		if(SearchNode(Data, link) == link->Tail){
			pList node = link->Head;
			for(; node->Next != link->Tail ; node = node->Next) ;
			delete Tail; 
			Tail = node->Next = nullptr;
			return link->Tail = node;
		}
		if(pList node = SearchNode(Data, link)){	
			for(pList prev = link->Head, next = node->Next; prev; prev = prev->Next){
				if(prev->Next == node){
					node = nullptr;
					return prev->Next = next;
				}
			}
		}
		if(!SearchNode(Data, link))
			return nullptr;
	}
	~Lists(){
		delete Head;
		delete Tail;
	}
private:
	pList Head = new List, Tail = new List;
};
#endif
