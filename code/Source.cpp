#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <clocale> 
using namespace std;


class Passenger
{
public:
	//сравнение по полям – номер каюты, порт  назначения, ФИО
	string name;
	int cabin;
	int type; //0,1,2,3
	string port;
	Passenger(){}
	Passenger(string name, int cabin, int type, string port)
	{
		this->name = name;
		this->cabin = cabin;
		this->type = type;
		this->port = port;
	}
	bool operator < (Passenger &b)
	{
		if (this->cabin == b.cabin)
		{
			if (this->port == b.port)
			{
				if (this->name == b.name)
				{
					return true;
				}
				else
				{
					int res = this->name.compare(b.name);
					return res < 0;
				}
			}
			else
			{
				int res = this->port.compare(b.port);
				return res < 0;
			}
		}
		else
		{
			return this->cabin < b.cabin;
		}
	}
	bool operator <= (Passenger& b)
	{
		if (this->cabin == b.cabin)
		{
			if (this->port == b.port)
			{
				if (this->name == b.name)
				{
					return true;
				}
				else
				{
					int res = this->name.compare(b.name);
					return res <= 0;
				}
			}
			else
			{
				int res = this->port.compare(b.port);
				return res <= 0;
			}
		}
		else
		{
			return this->cabin <= b.cabin;
		}
	}

	bool operator > (Passenger& b)
	{
		if (this->cabin == b.cabin)
		{
			if (this->port == b.port)
			{
				if (this->name == b.name)
				{
					return true;
				}
				else
				{
					int res = this->name.compare(b.name);
					return res > 0;
				}
			}
			else
			{
				int res = this->port.compare(b.port);
				return res > 0;
			}
		}
		else
		{
			return this->cabin > b.cabin;
		}
	}

	bool operator >= (Passenger& b)
	{
		if (this->cabin == b.cabin)
		{
			if (this->port == b.port)
			{
				if (this->name == b.name)
				{
					return true;
				}
				else
				{
					int res = this->name.compare(b.name);
					return res >= 0;
				}
			}
			else
			{
				int res = this->port.compare(b.port);
				return res >= 0;
			}
		}
		else
		{
			return this->cabin >= b.cabin;
		}
	}
};



ostream& operator<<(ostream& out, const Passenger& passagir) {
	return out << passagir.name << ":" << passagir.cabin << "," << passagir.type << "-" << passagir.port;
}

// сортировки а, в, е Сортировка выбором Сортировка простыми вставками Быстрая сортировка

template<class T> void selectSort(vector<T>& a, long size)
{
	long i, j, k;
	T x;
	for (i = 0; i < size - 1; i++)
	{   							
		k = i;
		x = a[i];
		for (j = i + 1; j < size; j++)	
		{
			if (a[j] < x)
			{
				k = j; x = a[j];	      
			}
		}
		a[k] = a[i]; a[i] = x;   	
	}
}



 
template<class T> void insertSort(vector<T>& a, long size)
{
	T x;
	long i, j;
	for (i = 0; i < size; i++)
	{
		x = a[i];
		for (j = i - 1; j >= 0 && a[j] > x; j--)
		{
			a[j + 1] = a[j];
		}
		a[j + 1] = x;
	}
}

template<class T>
int partition(vector<T>& nums, int low, int high)
{
	int i = low - 1;
	//choosing pivot as last element 
	T pivot = nums[high];
	for (int j = low; j < high; j++)
	{
		if (nums[j] <= pivot)
		{
			i++;
			swap(nums[i], nums[j]);
		}
	}
	swap(nums[i + 1], nums[high]);
	return i + 1;
}

template<class T>
void quicksort(vector<T>& nums, int low, int high)
{
	if (low < high)
	{
		int pivot = partition(nums, low, high);
		quicksort(nums, low, pivot - 1);
		quicksort(nums, pivot + 1, high);

	}
}



//Passanger

ofstream out_d("D:/учёба/Методы програмирования/Metods_1/graph/ris_grahp.txt");


void handleFile(string fileName, int sortAlgo) {
	string openPath = "D:/учёба/Методы програмирования/Metods_1/test/" + fileName;
	ifstream file(openPath);
	vector <Passenger> data;
	string line, field;
	while (getline(file, line))
	{
		stringstream ss(line);
		int i = 0;
		string name;
		int cabin;
		int type;
		string port;
		while (getline(ss, field, ','))
		{
			switch (i) {
			case 0:
				name = field;
				break;
			case 1:
				cabin = stoi(field);
				break;
			case 2:
				type = stoi(field);
				break;
			case 3:
				port = field;
				break;
			default:
				break;
			}
			++i;
		}
		Passenger pasn(name, cabin, type, port);
		data.push_back(pasn);
	}
	auto begin = std::chrono::steady_clock::now();
	switch (sortAlgo)
	{
	case 1:
		selectSort(data, data.size());
		break;
	case 2:
		insertSort(data, data.size());
		break;
	case 3:
		quicksort(data,0,data.size()-1);
		break;
	default:
		break;
	}
	auto end = chrono::steady_clock::now();
	auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - begin);
	cout << data.size() << "\t" << elapsed_ms.count() << endl;
	out_d << data.size() << "\t" << elapsed_ms.count() << endl;
}



// сортировки а, в, е Сортировка выбором Сортировка простыми вставками Быстрая сортировка
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Size" << "\t" << "Сортировка выбором" << "\n";
	out_d << "Size" << "\t" << "Сортировка выбором" << "\n";
	handleFile("test400.txt", 1);
	handleFile("test800.txt", 1);
	handleFile("test4000.txt", 1);
	handleFile("test8000.txt", 1);
	handleFile("test40000.txt", 1);
	handleFile("test80000.txt", 1);
	handleFile("test120000.txt", 1);
	cout << "Size" << "\t" << "Сортировка простыми вставками" << "\n";
	out_d << "Size" << "\t" << "Сортировка простыми вставками" << "\n";
	handleFile("test400.txt", 2);
	handleFile("test800.txt", 2);
	handleFile("test4000.txt", 2);
	handleFile("test8000.txt", 2);
	handleFile("test40000.txt", 2);
	handleFile("test80000.txt", 2);
	handleFile("test120000.txt", 2);
	cout << "Size" << "\t" << "Быстрая сортировка" << "\n";
	out_d  << "Size" << "\t" << "Быстрая сортировка" << "\n";
	handleFile("test400.txt", 3);
	handleFile("test800.txt", 3);
	handleFile("test4000.txt", 3);
	handleFile("test8000.txt", 3);
	handleFile("test40000.txt", 3);
	handleFile("test80000.txt", 3);
	handleFile("test120000.txt", 3);
}