#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Point {
	int x;
	int y;
public:
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	int getX() const { return x; }
	int getY() const { return y; }
	friend ostream& operator<<(ostream& os, const Point& point) {
		os << "(" << point.getX() << ", " << point.getY() << ")";
		return os;
	}
};

float getDistance(const Point& p1, const Point& p2) {
	float distance = sqrt(pow(p1.getX() - p2.getX(), 2) +
		pow(p1.getY() - p2.getY(), 2));
	return distance;
};

class Shape {
public:
	virtual float getArea() const { return 0; };
	virtual void print() const {};
};

class Rectangle : public Shape {
	Point p1; Point p2; Point p3; Point p4;
public:
	Rectangle(const Point& p1, const Point& p2, const Point& p3, const Point& p4) :
		p1(p1), p2(p2), p3(p3), p4(p4) {}
	float getArea() const {
		/*
		x1y1	x2y2
		x3y3	x4y4
		area = abs(x4 - x3) * abs(y3 - y1)
		*/
		float area = abs(p4.getX() - p1.getX()) * abs(p3.getY() - p4.getY());
		return area;
	}

	void print() const {
		cout << "Rectangle: " << p1 << p2 << p3 << p4 << endl;
	}
};

class Triangle : public Shape {
	Point p1; Point p2; Point p3;
public:
	Triangle(const Point& p1, const Point& p2, const Point& p3) :
		p1(p1), p2(p2), p3(p3) {}
	float getArea() const {
		/*
		삼각형의 세 변 길이 a, b, c
		let s = (a + b + c) / 2
		area = sqrt(s*(s-a)*(s-b)*(s-c))
		*/
		float a = getDistance(p1, p2);
		float b = getDistance(p2, p3);
		float c = getDistance(p3, p1);
		float s = (a + b + c) / 2;
		float area = sqrt(s * (s - a) * (s - b) * (s - c));
		return area;
	}
	void print() const {
		cout << "Triangle: " << p1 << p2 << p3 << endl;
	}
};

class ShapeList {
	vector<Shape*> list;
public:
	ShapeList() : list() {};
	~ShapeList() {
		if (list.size() > 0) {
			for (vector<Shape*>::iterator it = list.begin(); it != list.end(); ++it) {
				const Shape* pShape = *it;
				delete pShape;
			}
		}
	}
	void addShape(Shape* const shape) {
		list.push_back(shape);
	}

	void print() const {
		for (vector<Shape*>::const_iterator it = list.begin(); it != list.end(); ++it) {
			const Shape* pShape = *it;
			const Shape& shape = *pShape;
			shape.print();
		}
	}

	float getTotalArea() const {
		float totalArea = 0;
		for (vector<Shape*>::const_iterator it = list.begin(); it != list.end(); ++it) {
			const Shape* pShape = *it;
			const Shape& shape = *pShape;
			totalArea += shape.getArea();
		}
		return totalArea;
	}
};

int main() {
	Point p1(0, 0), p2(0, 10), p3(20, 20), p4(20, 30);

	Shape* r = new Rectangle(p1, p2, p3, p4);
	Shape* t = new Triangle(p1, p2, p3);

	ShapeList list;
	list.addShape(r);
	list.addShape(t);

	list.print();
	cout << list.getTotalArea() << endl;
}