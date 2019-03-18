#pragma once
#pragma once
#include <iostream>
#include <vector>
#include <ostream>
#include <iterator>
#include <sstream>
#include <map>
#include <iomanip>

using namespace std;

class Fishmen
{
public:
	wstring name;
	wstring surname;
	multimap<wstring, double> fishes;
	int years;
	double summa;

	Fishmen() {}

	Fishmen(const Fishmen& other)
		: name(other.name),
		surname(other.surname),
		fishes(other.fishes),
		years(other.years),
		summa(other.summa)
	{
	}

	Fishmen(Fishmen&& other)
		: name(std::move(other.name)),
		surname(std::move(other.surname)),
		fishes(std::move(other.fishes)),
		years(std::move(other.years)),
		summa(std::move(other.summa))
	{
	}

	void SetYears(int a)
	{
		this->years = a;
	}

	int GetYears()
	{
		return this->years;
	}

	void SetSumma(int a)
	{
		this->summa = a;
	}

	int GetSumma()
	{
		return this->summa;
	}

	wstring GetName() const
	{
		return name;
	}

	void SetName(wstring name)
	{
		this->name = name;
	}


	wstring GetSurname() const
	{
		return surname;
	}

	void SetSurname(wstring surname)
	{
		this->surname = surname;
	}



	multimap<wstring, double> GetFishes() const
	{
		return fishes;
	}

	void SetFishes(multimap<wstring, double> subject)
	{
		this->fishes = subject;
	}



	friend bool operator==(const Fishmen& lhs, const Fishmen& rhs)
	{
		return lhs.name == rhs.name
			&& lhs.surname == rhs.surname
			&& lhs.fishes == rhs.fishes
			&& lhs.years == rhs.years
			&& lhs.summa == rhs.summa;
	}

	friend bool operator!=(const Fishmen& lhs, const Fishmen& rhs)
	{
		return !(lhs == rhs);
	}

	Fishmen& operator=(const Fishmen& other)
	{
		if (this == &other)
			return *this;
		name = other.name;
		surname = other.surname;
		fishes = other.fishes;
		years = other.years;
		summa = other.summa;
		return *this;
	}

	Fishmen& operator=(Fishmen&& other)
	{
		if (this == &other)
			return *this;
		name = std::move(other.name);
		surname = std::move(other.surname);
		fishes = std::move(other.fishes);
		years = std::move(other.years);
		summa = std::move(other.summa);
		return *this;
	}


	friend bool operator<(const Fishmen& lhs, const Fishmen& rhs)
	{
		return lhs.summa < rhs.summa;
	}



	friend bool operator>(const Fishmen& lhs, const Fishmen& rhs)
	{
		return rhs < lhs;
	}


	friend std::wostream& operator<<(std::wostream& os, const Fishmen& obj)
	{

		return os << left << setw(20)  <<  obj.surname << left << setw(12)<<  obj.name << left << setw(3) << obj.years << left << setw(6) << obj.summa;
	}

};
