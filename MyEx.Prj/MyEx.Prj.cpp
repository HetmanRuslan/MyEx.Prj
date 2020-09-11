#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
using namespace std;
#define PATH "..\\MyEx.Prj\\info.txt"

class Car
{
	size_t number;
	string brand;
	string name;
	size_t year;
public:

	Car(size_t _number, string _brand, string _name, size_t _year) :
		number(_number), brand(_brand), name(_name), year(_year)
	{
		string _n = "\0", _a = "\0";
		if (_brand == _n) brand = "Пусто!";
		if (_name == _a) name = "Пусто!";
	}


	bool set_brand(string _brand)
	{
		brand = _brand;
		return true;
	}

	bool set_name(string _name)
	{
		name = _name;
		return true;
	}

	bool set_year(size_t _year)
	{
		year = _year;
		return true;
	}


	size_t get_number()const
	{
		return number;
	}

	string get_brand()const
	{
		return brand;
	}

	string get_name()const
	{
		return name;
	}

	size_t get_year()const
	{
		return year;
	}


	void show_car()
	{
		cout << "\nНомер:   " << get_number()
			<< "\nМарка:   " << get_brand()
			<< "\nВласник: " << get_name()
			<< "\nРiк:   " << get_year() << "\n\n";
	}


	void change_car
	(string _brand, string _name, size_t _year)
	{
		set_brand(_brand);
		set_name(_name);
		set_year(_year);
	}



};


class Register_Car  {

	vector<Car> arr;

public:
	
	Register_Car()
	{
		fstream f;
		f.open(PATH, fstream::in);
		if (!(f.is_open()))  cout << "Помилка вiдкриття файлу!!!\n";
		string co, na, au, ye, str;
		size_t code_int, year_int;
		while (!f.eof())
		{
			getline(f, str);
			if (str == "\0") break;
			co = str.substr(0, str.find_first_of('|'));
			str.erase(0, str.find_first_of('|') + 1);

			na = str.substr(0, str.find_first_of('|'));
			str.erase(0, str.find_first_of('|') + 1);

			au = str.substr(0, str.find_first_of('|'));
			str.erase(0, str.find_first_of('|') + 1);

			ye = str.substr(0, str.find_first_of('|'));
			str.empty();

			code_int = stoi(co);
			year_int = stoi(ye);

			add_car((Car(code_int, na, au, year_int)));
				
		}
		f.close();
	}


	~Register_Car()
	{
		fstream f;
		f.open(PATH, fstream::out);
		for (size_t i = 0; i < arr.size(); i++)
		{
			f << arr[i].get_number() << "|" << arr[i].get_brand() << "|" << arr[i].get_name() << "|" << arr[i].get_year() << "|\n";
		}
	}


	Car& operator[] (int ind)
	{
		return arr.at(ind);
	}


	size_t code_code()const
	{
		if (arr.size())
			return arr[arr.size() - 1].get_number();
		else return 1110;
	}


	int find_number(int _number)const
	{
		for (size_t i = 0; i < arr.size(); i++)
			if (arr[i].get_number() == _number) return i;

		return -1;
	}

	int find_brand(string _brand)const
	{
		for (size_t i = 0; i < arr.size(); i++)
			if (arr[i].get_brand() == _brand) return i;

		return -1;
	}

	int find_name(string _name)const
	{
		for (size_t i = 0; i < arr.size(); i++)
			if (arr[i].get_name() == _name) return i;

		return -1;
	}

	int find_year(size_t _year)const
	{
		for (size_t i = 0; i < arr.size(); i++)
			if (arr[i].get_year() == _year) return i;

		return -1;
	}


	bool add_car(const Car& obj)
	{
		arr.push_back(obj);
		return true;
	}


	bool del_car(size_t code)
	{
		if (find_number(code) == -1) return false;
		vector<Car>::iterator it = arr.begin();
		int k = 0;
		for (int k = 0; it != arr.end(); it++)
		{
			if (find_number(code) == k) { it = arr.erase(it); return true; }
			k++;
		}
		return false;
	}


	bool change_car(size_t _code, string _name, string _author, size_t _year)
	{

		int ind = find_number(_code);
		if (ind == -1) return false;

		arr[ind].set_brand(_name);
		arr[ind].set_name(_author);
		arr[ind].set_year(_year);
		return true;
	}


	void all_car()const
	{
		if (arr.size())
		{

			for (size_t i = 0; i < arr.size(); i++)
				cout << "\n	Номер:   " << arr[i].get_number()
				<< "\nМарка:   " << arr[i].get_brand()
				<< "\nВласник: " << arr[i].get_name()
				<< "\nРiк:   " << arr[i].get_year() << "\n\n";
		}
		else cout << "\nПустий реєстр.";
	}


};

int main()
{
	setlocale(LC_CTYPE, "UKR");
	Register_Car c;
	char q = 'q';
	size_t main_code, cin_year, cin_code;
	string cin_name, cin_author;

	cout << "Ласкаво просимо до реєстру машин!\n";
	while (q != '0')
	{
		cout << "\n\n\
1 - Подивитися всi машини\n\
2 - Додати нову машину\n\
3 - Змiнити вибрану машину\n\
4 - Видалити вибрану машину\n\
5 - Шукайте якусь машину\n\
       0 - Вихiд!\n\n";


		cin >> q;
		switch (q)
		{
		case'1':
			c.all_car(); break;


		case'2':
			cout << "Введiть марку машини--> ";

			getchar();
			getline(cin, cin_name);

			cout << "Введiть власника машини-->";
			getline(cin, cin_author);

			cout << "Введiть рiк машини--> ";
			cin >> cin_year;
			while (cin_year < 1 || cin_year > 2050) { cout << "Погано!!!\nПовторiть знову\n"; cin >> cin_year; }

			cout << "Введiть номер машини--> ";
			cin >>main_code ;
			while (main_code < 1000 || main_code > 9999) { cout << "Погано!!!\nПовторiть знову\n"; cin >> main_code; }
			cout << "Машина додана\n";

			c.add_car(Car(main_code, cin_name, cin_author, cin_year));
			break;


		case'3':
			cout << "Введiть номер машини--> ";
			cin >> cin_code;

			cout << "Введiть назву машини-->";
			getchar();
			getline(cin, cin_name);

			cout << "Введiть власника машини-->";
			getline(cin, cin_author);

			cout << "Введiть рiк машини-->";
			cin >> cin_year;
			while (cin_year < 1 || cin_year > 2050) { cout << "Погано!!!\nПовторiть знову\n"; cin >> cin_year; }

			cout << "Машину змiнено.\n";
			c[c.find_number(cin_code)].change_car(cin_name, cin_author, cin_year); break;


		case'4':
			cout << "Введiть номер машини--> ";
			cin >> cin_code;
			if (c.find_number(cin_code) == -1) { cout << "\nНевірний код!\n"; break; }

			c.del_car(cin_code);
			cout << "Машина видалена.\n";
			break;


		case'5':
			cout << "\
1 - Дивитися по номеру.\n\
2 - Пошук по марцi.\n\
3 - Пошук по власнику.\n\
4 - Пошук року.\n\
        0 - Вихiд\n\n";


			cin >> q;
			switch (q)
			{


			case'1':
				cout << "Введiть номер-->\n";
				cin >> cin_code;
				if (c.find_number(cin_code) == -1) { cout << "\nНевiрний номер!\n"; break; }

				cout << "\n\
Ось твоя машина\n\
      ↓\n";
				c[c.find_number(cin_code)].show_car(); break;


			case'2':
				cout << "Введiть марку машини-->\n";
				cin >> cin_name;
				if (c.find_brand(cin_name) == -1) { cout << "\nНевiрна марка!\n"; break; }

				cout << "\n\
Ось твоя машина\n\
      ↓\n";
				c[c.find_brand(cin_name)].show_car(); break;


			case'3':
				cout << "Введiть власника машини-->\n";
				cin >> cin_author;
				if (c.find_name(cin_author) == -1) { cout << "\nНевiрний власник!\n"; break; }

				cout << "\n\
Ось твоя машина\n\
      ↓\n";
				c[c.find_name(cin_author)].show_car(); break;


			case'4':
				cout << "Введіть рiк машини-->\n";
				cin >> cin_year;
				if (c.find_year(cin_year) == -1) { cout << "Невiрний рiк\n!\n"; break; }

				cout << "\n\
Ось твоя машина\n\
      ↓\n";
				c[c.find_year(cin_year)].show_car(); break;


			case'0': break;
			default: cout << "Незрозумiла команда!\n\n"; break;


			}

		case'0': break;
		default: cout << "Незрозумiла команда!\n\n"; break;


		}
	}
} 