#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum EmployeeLevel { 사원, 대리, 과장, 차장, 부장 };

class Employee {
	string name;
	EmployeeLevel level;
	float rate;
	int workdays;
public:
	Employee(const string& name, const EmployeeLevel level, float rate = 0) : name(name) {
		this->level = level;
		this->rate = rate;
		workdays = 0;
	}

	const string& getName() const {
		return name;
	}

	EmployeeLevel getLevel() const {
		return level;
	}

	float getRate() const { return rate; }
	int getWorkdays() const { return workdays; }

	virtual float getBonus() const {
		return rate * workdays;
	}

	friend ostream& operator<<(ostream& os, const Employee& employee) {
		os << employee.getLevel() << " ";
		os << employee.getName() << endl;
		return os;
	}

};
class Manager : public Employee {
	vector<Employee*> group;
public:
	Manager(const string& name, const EmployeeLevel level, float rate = 0) : Employee(name, level, rate), group() {}

	friend ostream& operator<<(ostream& os, Manager& manager) {
		os << static_cast<Employee>(manager);
		os << "List of employees managed by me" << endl;
		typedef vector<Employee*>::const_iterator iterator;
		for (iterator it = manager.getGroup().begin(); it != manager.getGroup().end(); ++it) {
			const Employee* pEmployee = *it;
			const Employee& employee = *pEmployee;
			os << employee;
		}
		return os;
	}

	float getBonus() const {
		return getRate() * getWorkdays() + getRate() * 0.5 * group.size();
	}

	vector<Employee*>& getGroup() {
		return group;
	}

	void addEmployee(Employee* const employee) {
		// [ref] Employee가 메모리 해제되도 가리키고 싶다면
		// Employee* newEmp = new Employee(*employee); group.pushback(newEmp);
		group.push_back(employee);
	}
};
int main() {
	Employee e1("홍", 사원, 2.0F), e2("김", 대리, 2.5F), e3("차", 사원, 2.0F);
	cout << e1 << e2 << e3;
	Manager m1("Tom", 차장, 4.0F);
	m1.addEmployee(&e1);
	m1.addEmployee(&e2);
	m1.addEmployee(&e3);
	cout << "Information for Manager" << endl;
	cout << m1;

	cout << endl << "getBonus()" << endl;
	cout << e1.getBonus() << endl;
	cout << e2.getBonus() << endl;
	cout << e3.getBonus() << endl;
	cout << m1.getBonus() << endl;
}