/* Error Handling */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

class StackException {
protected:
	const string msg;
public:
	StackException(const string& msg) : msg(msg) {};
	void print() const { cout << msg << endl; }
};

template <class T>
class StackSizeException : public StackException {
	T value;
public:
	StackSizeException(const string& msg, const T& value) : StackException(msg), value(value) {};
	void print() const { cout << msg << " " << value << endl; }
};

class CharStack {
	int size;
	int top;
	char* s;
public:
	CharStack(int sz) {
		if (sz <= 0) throw StackSizeException<int>("Invalid stack size.", sz);
		top = 0;
		size = sz;
		s = new char[size];
	}
	CharStack(const CharStack& charStack) {
		delete[] s;
		top = charStack.top;
		size = charStack.size;
		s = new char[size];
		for (int i = 0; i < top; i++) {
			s[i] = charStack.s[i];
		}
	}
	~CharStack() {
		delete[] s;
	}
	CharStack& operator= (const CharStack& charStack) {
		delete[] s;
		top = charStack.top;
		size = charStack.size;
		s = new char[size];
		for (int i = 0; i < top; i++) {
			s[i] = charStack.s[i];
		}
		return *this;
	}
	void push(char c) { 
		if (top == size) throw StackException("Stack is full.");
		s[top++] = c; 
	}
	char pop() {
		if (top == 0) throw StackException("Stack is empty.");
		char r = s[--top];
		s[top] = '\0';
		return r;
	}
	void print() const {
		for (int i = 0; i < top; i++) {
			cout << s[i];
		}
		cout << endl;
	}
};

int main() {
	int SIZE = 20;
	CharStack cs(SIZE);

	// push error test
	cout << "<push error test>" << endl;
	string testChar = "Hello world, I'm Jieun.";
	try {
		for (int i = 0; i < testChar.size(); i++) {
			cs.push(testChar.at(i));
		}
	}
	catch (const StackException& e) {
		e.print();
	}
	cs.print();

	// copy constructor test
	cout << "<copy constructor test>" << endl;
	CharStack cs2(cs);
	cs2.print();

	// assignment operator test
	cout << "<assignment operator test>" << endl;
	CharStack cs3 = cs;
	cs3.print();

	// pop error test
	cout << "<pop error test>" << endl;
	try {
		for (int i = 0; i < SIZE + 1; i++) {
			cs.pop();
		}
	}
	catch (const StackException& e) {
		e.print();
	}
	cs.print();

	// constructor error test
	cout << "<constructor error test>" << endl;
	try {
		CharStack cs2(-3);
	}
	catch (const StackSizeException<int>& e) {
		e.print();
	}
	
}