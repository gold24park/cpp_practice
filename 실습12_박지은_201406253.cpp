#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

class MyString {
	char* str;
public:
	MyString() { str = 0; }

	MyString(const MyString& myString) {
		delete[] str;
		str = new char[myString.getSize() + 1];
		strcpy(str, myString.getStr());
	}

	MyString(char * newStr) {
		str = new char[strlen(newStr) + 1];
		strcpy(str, newStr);
	}

	~MyString() {
		delete[] str;
	}

	char* getStr() const { return str; }

	int getSize() const { return strlen(str); }

	bool operator<(const MyString& myString) const {
		return strcmp(str, myString.getStr()) < 0;
	}

	bool operator==(const MyString& myString) const {
		return strcmp(str, myString.getStr()) == 0;
	}

	MyString& operator=(const MyString& myString) {
		delete[] str;
		str = new char[myString.getSize() + 1];
		strcpy(str, myString.getStr());
		return *this;
	}

	friend ostream& operator<<(ostream& os, const MyString& myString) {
		os << myString.str;
		return os;
	}
};

class Complex {
	float r, i;
public:
	Complex(float r = 0.F, float i = 0.F) {
		this->r = r;
		this->i = i;
	}
	const Complex& min(const Complex& comp1, const Complex& comp2) const {
		return (comp1 < comp2) ? comp1 : comp2;
	}
	bool operator < (const Complex& c) const {
		return size() < c.size();
	}
	float size() const {
		return sqrt(r*r + i*i);
	}

	bool operator== (const Complex& comp) const {
		return (r == comp.r && i == comp.i);
	}

	friend ostream& operator<<(ostream& os, const Complex& complex) {
		os << complex.r << ", " << complex.i;
		return os;
	}
};

template <class T, int SIZE>
class List {
	T* pElem;
	int top;
public:
	List() {
		pElem = new T[SIZE];
		top = 0;
	}

	List(const List& list) {
		delete[] pElem;
		pElem = new T[SIZE];
		top = list.getTop();
		for (int i = 0; i < top; i++) {
			pElem[i] = list.pElem[i];
		}
	}

	~List() {
		delete[] pElem;
	}

	int add(const T& elem) {
		int insertIndex = top;
		if (!isFull()) {
			pElem[insertIndex] = elem;
			top++;
		}
		else {
			insertIndex = -1;
		}
		return insertIndex;
	}

	int find(const T& elem) {
		int foundIndex = -1;
		for (int i = 0; i < top; i++) {
			if (pElem[i] == elem) {
				foundIndex = i;
			}
		}
		return foundIndex;
	}

	void remove(const T& elem) {
		int foundIndex = find(elem);
		// 찾았는데 마지막 애는 아닐 때
		if (foundIndex >= 0) {
			if (foundIndex != top - 1) {
				for (int i = foundIndex; i < top - 1; i++) {
					pElem[i] = pElem[i + 1];
				}
			}
			top--;
		}
	}

	void remove(int index) {
		if (index >= 0) {
			if (index != top - 1) {
				for (int i = index; i < top - 1; i++) {
					pElem[i] = pElem[i + 1];
				}
			}
			top--;
		}
	}

	bool isEmpty() const { return top == 0 }

	bool isFull() const { return top == SIZE; }

	int getTop() const { return top; }

	int getSize() const { return SIZE; }

	List& operator=(const List& list) {
		delete[] pElem;
		pElem = new T[SIZE];
		top = list.getTop();
		for (int i = 0; i < top; i++) {
			pElem[i] = list.pElem[i];
		}
		return *this;
	}

	friend ostream& operator<<(ostream& os, const List& list) {
		for (int i = 0; i < list.top; i++) {
			os << list.pElem[i] << " ";
		}
		os << endl;
		return os;
	}
};

int main() {
	List<Complex, 100> cList;
	List<MyString, 200> sList;
	int i1 = cList.add(Complex(0, 0));
	cList.add(Complex(1, 1));
	int i2 = sList.add("abc");
	sList.add("def");
	cList.find(Complex(1, 0));
	sList.find("def");
	cList.remove(i1);
	sList.remove("abc");
	List<MyString, 200> s2List(sList);
	List<MyString, 200> s3List;
	s3List.add("123");
	s3List = s2List;
	s3List.remove("def");
}