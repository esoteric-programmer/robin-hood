#include "List.h"

template <typename T> CConstList<T>::CConstList(CList<T>* list) {
	this->list = list;
}

template <typename T> T* CConstList<T>::first() {
	if (this->list == 0) {
		return 0;
	}
	return this->list->first();
}

template <typename T> T* CConstList<T>::next() {
	if (this->list == 0) {
		return 0;
	}
	return this->list->next();
}


template <typename T> T* CConstList<T>::get(unsigned int id) {
	if (this->list == 0) {
		return 0;
	}
	return this->list->get(id);
}


template <typename T> CList<T>::CList() {
	this->root.elem = 0;
	this->root.next = 0;
	this->last=0;
	this->cur=0;
	this->prev=0;
	this->lsize=0;
}

template <typename T> bool CList<T>::add(T* elem) {
	if (this->last == 0) {
		this->last = &(this->root);
		this->root.next = 0;
		this->root.elem = elem;
		this->lsize = 1;
		this->cur=0;
		this->prev=0;
		return true;
	}
	struct List* nl = new struct List;
	if (nl == 0) {
		return false;
	}
	nl->elem = elem;
	nl->next = 0;
	this->last->next = nl;
	this->last = nl;
	this->lsize++;
	return true;
}

template <typename T> unsigned int CList<T>::size() {
	return this->lsize;
}

template <typename T> T* CList<T>::first() {
	if (this->lsize == 0) {
		return 0;
	}
	this->prev=0;
	this->cur = &(this->root);
	return root.elem;
}

template <typename T> T* CList<T>::next() {
	if (this->cur == 0) {
		return 0;
	}
	this->cur = this->cur->next;
	if (this->cur == 0) {
		return 0;
	}
	return this->cur->elem;
}

template <typename T> T* CList<T>::get(unsigned int id) {
	// TODO
	return 0;
}

template <typename T> T* CList<T>::remove() {
	// TODO
	return 0;
}

template <typename T> T* CList<T>::remove(unsigned int id) {
	// TODO
	return 0;
}

template <typename T> bool CList<T>::remove(T* element) {

	if (this->lsize == 0) {
		return false;
	}
	
	if (this->root.elem == element) {
		if (root.next != 0) {
			List* tmp = root.next;
			root.elem = root.next->elem;
			root.next = root.next->next;
			if (this->last == root.next) {
				this->last = &(this->root);
			}
			this->cur = 0;
			this->prev = 0;
			delete tmp;
		} else {
			root.elem = 0;
		}
		this->lsize--;
		return true;
	}


	struct List* it = &(this->root);
	while (it->next != 0) {
		if (it->next->elem == element) {
			struct List* tmp = it->next;
			it->next = it->next->next;
			if (it->next == 0) {
				this->last = it;
			}
			this->cur = 0;
			this->prev = 0;
			delete tmp;
			lsize--;
			return true;
		}
		it = it->next;
	}
	return false;
}

template <typename T> void CList<T>::clear(bool delete_elements) {
	this->cur = this->root.next;
	while (this->cur != 0) {
		struct List* tmp = this->cur;
		this->cur = this->cur->next;
		if (tmp->elem != 0 && delete_elements) {
			delete tmp->elem;
		}
		delete tmp;
	}
	if (this->root.elem != 0 && delete_elements) {
		delete this->root.elem;
	}
	this->root.elem = 0;
	this->root.next = 0;
	this->last=0;
	this->cur=0;
	this->prev=0;
	this->lsize=0;
}

template <typename T> CConstList<T>* CList<T>::get_constant_list() {
	return new CConstList<T>(this);
}

template <typename T> CList<T>::~CList() {
	this->clear(true);
}

#include "Level.h"
template class CConstList<CLevel::Landscape>;
template class CConstList<CLevel::Nature>;
template class CConstList<CLevel::Enemy>;
template class CList<CLevel::Landscape>;
template class CList<CLevel::Nature>;
template class CList<CLevel::Enemy>;

