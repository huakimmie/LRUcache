

#ifndef LRU_h
#define LRU_h

#include <vector>
#include <iostream>
namespace lru {
	template<typename T, unsigned int N, typename ord = std::less<T>>
	class memory {				//memory class implemented using a vector
	private:
		std::vector<T> store;	//vector that stores memory
		T highest, lowest;      //high and low values
		ord comp;				//private variable for comparison
	public:
		class iterator {		//nested iterator class
		private:
			typename std::vector<T>::iterator it;  //private member veriable uses built in vector iterator
		public:
			iterator(typename std::vector<T>::iterator iter) : it(iter) {} //constructor that accepts a vector<T> iterator
			iterator& operator--() { //prefix decrement, advances to further back memory using ++ as newest memory stored at beginning of vector
				++it;
				return *this;
			}
			iterator operator--(int dummy) { //postfix decrement, same logic as prefix
				iterator copy = *this;
				++(*this);
				return copy;
			}
			T& operator*() { //dereferencing operator, utilizes dereference of vector iterators
				return *it;
			}
			T* operator->() { //standard arrow operator
				return &(*it);
			}
			bool operator!=(iterator rhs) { //!= operator for iterator class, uses == operator of vector iterators
				return !(it == rhs.it);
			}
		};
		memory(const ord& compare = ord()) : store(std::vector<T>()), comp(compare) {} //default constructor for memory class
		void remember(T new_object) { //function to remember a new object
			if (store.size() == 0) { //if store is currently empty, the new object will be both highest and lowest value
				lowest = new_object;
				highest = new_object;
			}
			while (store.size() >= N && N != 0) { //get rid of oldest memory until there is space for a new object
				store.pop_back();
			} 
			store.insert(store.begin(), new_object); //insert new object and check if it is highest or lowest value
			if (comp(new_object, lowest))
				lowest = new_object;
			else if (comp(highest, new_object))
				highest = new_object;
		}
		void forget() { //forget using try catch, utilizes pop_back of vector
			try {
				store.pop_back();
			}
			catch (std::exception& e) {
				throw e;
			}
		}
		iterator begin() {  //returns an iterator pointing to the beginning of the store member variable
			return iterator(store.begin());
		}
		iterator end() {	//returns an iterator pointing to the end of the store member variable
			return iterator(store.end());
		}
		size_t size() const { //returns size of the internal vector
			return store.size();
		}
		T get_low() const { //returns current lowest value
			return lowest;
		}
		T get_high() const { //returns current highest value
			return highest;
		}

		template<typename ... Tvals>
		void emplace(const Tvals& ... params) { //variadic templated funtion to remember an object
			T obj = T(params...);
			remember(obj);
		}
	};

	template<typename T, unsigned int N, typename ord>
	void print(memory<T, N, ord> object) { //nonmember print function that prints all objects in memory separated by spaces
		for (auto it = object.begin(); it != object.end(); --it) {
			std::cout << *it << " ";
		}
	}
}

bool length_comp(const std::string& left, const std::string& right) {
	return left.size() < right.size();
}


#endif