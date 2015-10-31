#ifndef LIST_INCLUDED
#define LIST_INCLUDED

template <typename T> class CList;

template <typename T> class CConstList {
	private:
		CList<T>* list;
	public:
		CConstList(CList<T>* list);
		T* first();
		T* next();
		T* get(unsigned int id);
};

template <typename T> class CList {
private:
	struct List {
		T* elem;
		List* next;
	} root;
	struct List* last;
	struct List* cur;
	struct List* prev;
	unsigned int lsize;
	

public:
	CList();
	bool add(T* elem);
	unsigned int size();
	T* first();
	T* next();
	T* get(unsigned int id);
	T* remove();
	T* remove(unsigned int id);
	CConstList<T>* get_constant_list();
	bool remove(T* element);
	void clear(bool delete_elements);
	~CList();
};

#endif

