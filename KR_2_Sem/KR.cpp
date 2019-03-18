#include <iostream>
#include <vector>
#include <ostream>
#include <iterator>
#include <sstream>
#include <map>
#include <fstream>
#include "Fishmen.h"
#include <queue>
#include <codecvt>

using namespace std;

multimap<int, Fishmen> FillMapTogether(multimap<int, Fishmen>& mapFishmen1, multimap<int, Fishmen>& mapFishmen2 )
{
	multimap<int, Fishmen> mapTogether;
	for(auto a : mapFishmen1)
		mapTogether.insert(pair<int, Fishmen>(a.first, a.second));
	for (auto a : mapFishmen2)
		mapTogether.insert(pair<int, Fishmen>(a.first, a.second));
	return mapTogether;
}

void FoutSort(multimap<int, Fishmen>& mapFishers1, wofstream& fout)
{
	for_each(mapFishers1.begin(), mapFishers1.end(), [&](auto& a) {fout << a.second << endl; });
}

void LastTable(multimap<int, Fishmen>& mapFishers1, wofstream& fout)
{
	for (auto it = mapFishers1.begin(); it != mapFishers1.upper_bound(17); ++it)
		it->second.summa *= 1.1;
	for (auto it = mapFishers1.lower_bound(18); it != mapFishers1.upper_bound(30); ++it)
		it->second.summa *= 1.0;
	for (auto it = mapFishers1.lower_bound(18); it != mapFishers1.upper_bound(30); ++it)
		it->second.summa *= 0.9;
	for (auto a : mapFishers1)
		fout << a.second << endl;
}

void FindMaxByYears(multimap<int, Fishmen>& mapFishmen, wofstream& fout)
{
	priority_queue<Fishmen> queueFishers;
	fout << L"Under 18 : ";

	for (auto it = mapFishmen.begin(); it != mapFishmen.upper_bound(17); ++it)
		queueFishers.push(it->second);
	if (!queueFishers.empty())
		fout << queueFishers.top().name << " " << queueFishers.top().surname << endl;
	else
		fout << L" Nobody " << endl;
	for (auto a = 0; a < queueFishers.size(); a++)
		queueFishers.pop();

	fout << L"From 18 to 30 : ";
	for (auto it = mapFishmen.lower_bound(18); it != mapFishmen.upper_bound(30); ++it)
		queueFishers.push(it->second);
	if (!queueFishers.empty())
		fout << queueFishers.top().name << " " << queueFishers.top().surname << endl;
	else
		fout << L" Nobody " << endl;
	for (auto a = 0; a < queueFishers.size(); a++)
		queueFishers.pop();

	fout << L"From 30 : ";
	for (auto it = mapFishmen.lower_bound(30); it != mapFishmen.end(); ++it)
		queueFishers.push(it->second);
	if (!queueFishers.empty())
		fout << queueFishers.top().name << " " << queueFishers.top().surname << endl;
	else
		fout << L" Nobody " << endl;
	fout << endl;
}

multimap<int,Fishmen> FillMapYears(vector<Fishmen>& VectorFishmen)
{
	multimap<int, Fishmen> multiMap;
	for_each(VectorFishmen.begin(),VectorFishmen.end(), [&](const auto& a) {multiMap.insert(pair<int, Fishmen>(a.years, a));});
	return multiMap;
}

void ShowAll(vector<Fishmen>& VectorFishmen1, vector<Fishmen>& VectorFishmen2,wofstream& fout)
{
	fout << L"All : " << endl;
	for_each(VectorFishmen1.begin(), VectorFishmen1.end(), [&](auto& a) {fout << a << endl;  });
	for_each(VectorFishmen2.begin(), VectorFishmen2.end(), [&](auto& a) {fout << a << endl;  });
	fout << endl;
}


vector<Fishmen> FillVector(string way)
{

		vector<Fishmen> FishmenVector;
		wifstream wifile;
		wifile.open(way);
		wifile.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
		Fishmen men;
		while (!wifile.eof())
		{
			wstring wstr;
			wstring name;
			double weight;
			getline(wifile, wstr);
			wstringstream str_stream(wstr);
			str_stream >> men.surname >> men.name >> men.years;
			getline(wifile, wstr);
			wstringstream str_stream1(wstr);
			while (!str_stream1.eof())
			{
				str_stream1 >> name >> weight;
				men.fishes.insert(pair<wstring, double>(name, weight));
			}
			double sum = 0;
			for(auto a : men.fishes)
			{
				sum = sum + a.second;
			}
			men.summa = sum;
		    FishmenVector.push_back(men);
		}

		return FishmenVector;
}

void Menu(string way1,string way2)
{
	auto VectorFishmen2017 = FillVector(way1);
	auto VectorFishmen2018 = FillVector(way2);
	
	wofstream fout("C:\\Users\\Dell\\source\\repos\\KR_2_Sem\\output.txt");
	fout.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
	auto MapFishmen2017 = FillMapYears(VectorFishmen2017);
	auto MapFishmen2018 = FillMapYears(VectorFishmen2018);
	auto Map20172018 = FillMapTogether(MapFishmen2017,MapFishmen2018);
	fout << L"Best in 2017 : " << endl;
	FindMaxByYears(MapFishmen2017, fout);
	fout << L"Best in 2018 : " << endl;
	FindMaxByYears(MapFishmen2018, fout);
	ShowAll(VectorFishmen2017,VectorFishmen2018, fout);

	fout << L"Sorted : " << endl;
	FoutSort(Map20172018,fout);
	fout << endl;
	fout << L"Last Table : " << endl;
	LastTable(Map20172018, fout);
}

int main()
{
	Menu("C:\\Users\\Dell\\source\\repos\\KR_2_Sem\\2017.txt", "C:\\Users\\Dell\\source\\repos\\KR_2_Sem\\2018.txt");
	system("pause");

}