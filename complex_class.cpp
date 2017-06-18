/* complex class */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

class Complex {
	double re, im;
public:
	Complex(double re = 0.0, double im = 0.0) {
		this->re = re;
		this->im = im;
	}
	operator double() {
		return re;
	}
	Complex& operator+(const Complex& c) {
		return Complex(re + c.re, im + c.im);
	}
	Complex& operator++() {
		re++;
		return *this;
	}
	friend Complex& operator+(const Complex& c1, const Complex& c2) {
		return Complex(c1.re + c2.re, c1.im + c2.im);
	}
	friend Complex& operator-(const Complex& c1, const Complex& c2) {
		return Complex(c1.re - c2.re, c1.im - c2.im);
	}
	friend Complex& operator/(const Complex& c1, const Complex& c2) {
		double common = c2.re * c2.re + c2.im * c2.im;
		return Complex((c1.re * c2.re + c1.im * c2.im) / common,
			(c1.re * c2.im - c1.im * c2.re) / common);
	}
	bool operator==(const Complex& c2) const {
		return (re == c2.re) && (im == c2.im);
	}
	friend ostream& operator<< (ostream& os, const Complex& c) {
		const char* sign = c.im < 0 ? " - " : " + ";
		os << c.re << sign << c.im << "i";
		return os;
	}
};
