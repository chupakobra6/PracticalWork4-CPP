// PracticalWork4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

class IFileCustom
{
public:
	virtual void toWrite(string filename, string data) = 0;
	virtual string toRead(string filename) = 0;
};

class FileManager : public IFileCustom
{
public:
	void toWrite(string filename, string data) override
	{
		ofstream file(filename);
		file << data;
		file.close();
	}

	string toRead(string filename) override
	{
		ifstream input_file(filename);
		string data((istreambuf_iterator<char>(input_file)), istreambuf_iterator<char>());
		input_file.close();
		return data;
	}
};

class Person
{
public:
	string name;
	int age;
	string address;

	json toJson() const
	{
		json j;
		j["name"] = name;
		j["age"] = age;
		j["adress"] = address;
		return j;
	}

	void fromJson(const json& j)
	{
		name = j["name"];
		age = j["age"];
		address = j["adress"];
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << " Создаём список Person\n";
	vector<Person> persons =
	{
		{"Jhon", 30, "123 Main St"},
		{"Jane", 25, "456 Oak Ave"},
		{"Bob", 40, "789 Maple St"},
	};

	cout << "Записываем список в файл в формате JSON\n";
	json j;
	for (const auto& p : persons)
	{
		j.push_back(p.toJson());
	}

	ofstream file("persons.json");
	file << j.dump(4);
	file.close();

	cout << "Читаем список из файла и выводим в консоль\n";
	ifstream input_file("persons.json");
	json data;
	input_file >> data;

	for (const auto& j : data)
	{
		Person p;
		p.fromJson(j);
		cout << "Name: " << p.name << endl;
		cout << "Age: " << p.age << endl;
		cout << "Address: " << p.address << endl;
		cout << endl;
	}

	FileManager fm;

	cout << "Записываем данные в файл\n";
	string data1 = "Hello, World!";
	fm.toWrite("file.txt", data1);

	cout << "Читаем данные из файла и выводим в консоль\n";
	string file_data = fm.toRead("file.txt");
	cout << file_data << endl;

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
