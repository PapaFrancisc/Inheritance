#include<iostream>
#include<ostream>
#include<string>

using namespace std;
class Worker
{
	string name;
	string surname;
	unsigned int age;
public:
	const string& get_name() const
	{
		return this->name;
	}

	const string& get_surname() const
	{
		return this->surname;
	}

	const unsigned int& get_age() const
	{
		return this->age;
	}

	void set_name(const string& name)
	{
		this->name = name;
	}

	void set_surname(const string& surname)
	{
		this->surname = surname;
	}
	void set_age(unsigned int age)
	{
		this->age = age;
	}

	///////////////////////////////////////////////////////constructors//////////////////////////////////////////////////

	Worker(const string& name, const string& surname, unsigned int age)
	{
		set_name(name);
		set_surname(surname);
		set_age(age);
		cout << "WConstructor:\t" << this << endl;
	}
	virtual ~Worker()
	{
		cout << "DConstructor:\t" << this << endl;
	}

	virtual double get_money() const = 0;
};

ostream& operator << (ostream& os, const Worker& obj)
{
	return os << obj.get_surname() << " " << obj.get_name() << "\t" << obj.get_age() << " лет";
}

class FixedPayment :public Worker
{
	double salary;
public:
	const double get_salary() const
	{
		return this->salary;
	}
	void set_salary(double salary)
	{
		this->salary = salary;
	}

	FixedPayment(const string& name, const string& surname, unsigned int age, double salary) :
		Worker(name, surname, age)
	{
		set_salary(salary);
		cout << "FConstructor:\t" << this << endl;
	}
	~FixedPayment()
	{
		cout << "FDestructor:\t" << this << endl;
	}

	double get_money() const
	{
		return salary;
	}
};

ostream& operator<<(ostream& os, const FixedPayment obj)
{
	os << (Worker&)obj << "\t";
	return os << obj.get_money() << "$" << endl;
}

class HourPayment :public Worker
{
	double rate;
	int hours;

public:

	double get_rate() const
	{
		return this->rate;
	}

	int get_hours() const
	{
		return this->hours;
	}

	void set_rate(double rate)
	{
		this->rate = rate;
	}

	void set_hours(int hours)
	{
		this->hours = hours;
	}

	HourPayment(const string& name, const string& surname, unsigned int age, double rate, int hours = 168) : Worker(name, surname, age)
	{
		set_rate(rate);
		set_hours(hours);
		cout << "HConstructor" << endl;
	}
	~HourPayment()
	{
		cout << "HDestructor" << this << endl;
	}

	double get_money() const
	{
		return rate * hours;
	}
};

ostream& operator<<(ostream& os, const HourPayment obj)
{
	os << (Worker&)obj << "\t";
	return os << obj.get_rate() << "$ " << obj.get_hours() << " hours " << obj.get_money() << " total payment " << endl;
}
void main()
{
	setlocale(LC_ALL, "rus");
	/*FixedPayment fp("Antonio", "Montana", 40, 5000);
	cout << fp << endl;
	HourPayment hp("Kennan", "Kel", 25, 5.5, 40);
	cout << hp << endl;*/

	Worker* department[] =
	{
	new FixedPayment("Antonio", "Montana", 40, 5000),
	new HourPayment("Martin", "Scorsese", 60, 100),
	new HourPayment("Anjela", "Marabella", 23, 200)
	};

	for (int i = 0; i < sizeof(department) / sizeof(Worker*); i++)
	{
		if (typeid(*department[i]) == typeid(HourPayment))cout << *(HourPayment*)department[i] << endl;
		if (typeid(*department[i]) == typeid(FixedPayment))cout << *(FixedPayment*)department[i] << endl;
	}
	for (int i = 0; i < sizeof(department) / sizeof(Worker*); i++)
	{
		delete department[i];
	}

	cout << endl;

}