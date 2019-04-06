
//HomeWork_19_03_2019_1553008887


//1.	***Описать структуру Man(Фамилия, Имя, Возраст, Дата рождения).Создать массив, предусмотреть:
//-Вывод информации с сортировкой по фамилии или имени;
//-Вывод списка именинников месяца с указанием даты рождения.
//- Изменение размеров массива при добавлении и удалении записей;
//-Поиск по фамилии и имени;
//-Редактирование записи.

#include<iostream>
#include<fstream>

using namespace std;

int buf_size = 0;
int cur_size = 0;

struct Date
{
	int day;
	int month;
	int year;

	void print()
	{
		cout << day << "/" << month << "/" << year << "  ";
	}
	
	void recordFile()
	{
		ofstream fout("DataBaseEdit.txt");
		fout << day << "/" << month << "/" << year << "  ";
	}

};

struct Human
{
	char surname[25];
	char name[25];
	int age;

	Date dateOfBirth;

	void print()
	{
		cout << name << "  " << surname << "  " << age << "  ";
		dateOfBirth.print();
		cout << endl;
	}

	void recordFile()
	{
		ofstream fout("DataBaseEdit.txt");
		fout << name << "  " << surname << "  " << age << "  ";
		dateOfBirth.recordFile();
	}
};

void add(Human *&arr, Human el)
{
	if (buf_size == 0)
	{
		buf_size = 4;
		arr = new Human[buf_size];
	}
	else
	{
		if (cur_size == buf_size)
		{
			buf_size *= 2;
			Human *file = new Human[buf_size];
			for (int i = 0; i < cur_size; i++)
			{
				file[i] = arr[i];
			}
			delete[] arr;
			arr = file;
		}
	}
	arr[cur_size] = el;
	cur_size++;
}


int main()
{
	ifstream fin("DataBase.txt");
	
	Human *arr = nullptr;
	Human file_Human;

	int n;
	char c;

	if (!fin)
	{
		cout << "file does not exist" << endl;
	}

	else 
	{
		while (!fin.eof()) // считываем файл и записывем данные в Human
		{
			fin >> file_Human.name >> file_Human.surname >> file_Human.age >> file_Human.dateOfBirth.day >> c >>
				file_Human.dateOfBirth.month >> c >> file_Human.dateOfBirth.year;
			add(arr, file_Human);
		}
		cout << "Menu:\n (1) - Sort by name\n (2) - Sort by surname\n (3) - Search for birthday month\n" <<
			" (4) - Search by name\n (5) - Search by surname\n (6) - Edit\n";
		
		int choose;
		
		cout << "\n Your choice -> ";
		cin >> choose;
		cout << endl;

		switch (choose)
		{

		case 1: // сортировка по имени
		{
			for (int i = 0; i < cur_size - 1; i++)
				for (int j = cur_size - 2; j >= i; j--)
					if (strcmp(arr[j].name, arr[j + 1].name) == 1)
						swap(arr[j], arr[j + 1]);

			for (int i = 0; i < cur_size; i++)
				arr[i].print();
			break;
		}

		case 2: // сортировка по фамилии
		{
			for (int i = 0; i < cur_size - 1; i++)
				for (int j = cur_size - 2; j >= i; j--)
					if (strcmp(arr[j].surname, arr[j + 1].surname) == 1)
						swap(arr[j], arr[j + 1]);

			for (int i = 0; i < cur_size; i++)
				arr[i].print();
			break;
		}

		case 3: // Вывод списка именинников месяца с указанием даты рождения
		{
			int m;
			cout << "Write the month: ";
			cin >> m;
			cout << endl;
			for (int i = 0; i < cur_size; i++)
				if (arr[i].dateOfBirth.month == m)
				{
					arr[i].print();
					cout << endl;
				}
				else cout << "\n - Not found - \n\n";
			break;
		}

		case 4: // поиск по имени
		{
			char name[30];
			cout << "Enter the name: ";
			cin >> name;
			cout << endl;
			for (int i = 0; i < cur_size; i++)
				if (strcmp(arr[i].name, name) == 0)
					arr[i].print();
				else cout << "\n - Not found - \n\n";
			break;
		}

		case 5: // поиск по фамилии
		{
			char surname[30];
			cout << "Enter the surname: ";
			cin >> surname;
			cout << endl;
			for (int i = 0; i < cur_size; i++)
				if (strcmp(arr[i].surname, surname) == 0)
					arr[i].print();
				else cout << "\n - Not found - \n\n";
			break;
		}

		case 6:
		{
			for (int i = 0; i < cur_size; i++)
			{
				cout << i + 1 << " - ";
				arr[i].print();
			}

			int num;
			char c, yn = 'y';

			do
			{
				cout << "\n Which record do you want to edit? ";
				cin >> num;

				if (num < 1 || num > cur_size)
				{
					cout << "\n - Record not found - \n"; break;
				}
				else
				{
					cout << "\n Enter new information in the format - Name Surname Age DD/MM/YYYY \n\n -> ";
					cin >> arr[num - 1].name >> arr[num - 1].surname >> arr[num - 1].age >>
						arr[num - 1].dateOfBirth.day >> c >> arr[num - 1].dateOfBirth.month >>
						c >> arr[num - 1].dateOfBirth.year;
				}

				cout << "\n Do you want edit one more record y/n ? -> ";
				cin >> yn;

			} while (yn == 'y');

			cout << "\n\n List after Modification: \n\n";
			for (int i = 0; i < cur_size; i++)
			{
				arr[i].print();
				arr[i].recordFile();
			}
		
			cout << endl << endl;
		}
		}
	}

	system("pause");
}	