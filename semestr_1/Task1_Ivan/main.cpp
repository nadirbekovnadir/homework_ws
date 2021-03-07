#include <iostream>
#include <string>
#include "Parser.h"
using namespace std;

int main()
{
	// Ввод исходных байт посылки в виде строки
	cout << "Input data:" << endl;
	string input_string; // Строка, содержащая посылку
	cin >> input_string; // Запись посылки в строку
	cout << endl;

	// Конвертация строки в массив байт
	char *bytes = new char[input_string.length() / 2]; // Количество байт равно половине длины строки
	// Так как один байт записан в виде двух символов
	string t; // Временная строка, для хранения двух знаков байта
	t.resize(2);
	for (int i = 0; i < input_string.length() - 1; i += 2) // Цикл проходит по всей строке посылки с шагом два
	{
		// Конвертация конкретного байта из строчной записи в численную
		t[0] = input_string[i];
		t[1] = input_string[i + 1];
		bytes[i / 2]  = stoi(t, nullptr, 16);
	}

	// Вызов подпрограммы записи байтовой посылки в заданную структуру данных
	Data data = bytes_to_data(bytes, input_string.length());
	// Вызов подпрограммы, печатающей содержимое структуры данных в читаемом виде
	Print(data);

	return 0;
}

//05430D083B183F91BCD8193EDF4DE94F00080015BCA408C0163BFB4DAB173F80F5081BC16EA4371cc12d31271d42513d4f4a000000004b000000004c00000000