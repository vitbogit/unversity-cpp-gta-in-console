/*
 * --------- МАИ 2023 ---------
 *
 * Объектно-ориентированное программирование
 *
 * РАБОТА № 2 "НАСЛЕДОВАНИЕ"
 *
 * Гр-па: М3О-211Б-21
 * Ст-т: Богомольский Виталий
 * Вариант: 5 (Велосипед)
 *
 * Формулировка задания:
 * Построить вертикальную иерархию потомков класса Figure, добавив 2 прямых
 * потомка, с использованием виртуальных функций.
 * Построить веерную иерархию потомков класса Figure, добавив 2 прямых потомка,
 * с использованием виртуальных функций.
 * Построить иерархию дополнительных объектов, с которыми будут
 * взаимодействовать/конфликтовать потомки класса Figure (например, для Ракеты
 * это могут быть Метеориты с разной степенью поражения/восстановления
 * Ракеты).
 * Реализовать простейшее взаимодействие объектов.
 *
 * Задание 3
 * Реализовать взаимодействие объектов через динамический полиморфизм с использованием матрицы перехода.
 *
*/



#include <windows.h>
#include <string>
#include <conio.h>
#include <iostream>
#include "bicycle.h"
using namespace std;

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)


// ---- ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ И КОНСТАНТЫ ---


HDC hdc;  // Контекст устройства (по сути это структура,
// содержащая описание видеокарты на компьютере
// и всех необходимых графических элементов.


// Цвета:

const COLORREF colour_dark_red RGB(139, 0, 0);
const COLORREF colour_mocassin RGB(255, 228, 181);
const COLORREF colour_orchid RGB(218, 112, 214);
const COLORREF colour_medium_turquoise RGB(72, 209, 204);
const COLORREF colour_crystal RGB(172, 221, 222);
const COLORREF colour_sandy_tan RGB(247, 216, 186);

// ----------- ПРОТОТИПЫ ФУНКЦИЙ ------------



HWND GetConcolWindow();  // Указатель на консольное окно
bool Collision(Man* M, Bicycle* Bike);  // Коллизия человека и велосипеда
bool Collision(Button* B, Bicycle* Bike);  // Коллизия кнопки и велосипеда

// Пересекаются ли прямоугольники:
bool AreRectanglesColliding(int Rect1X1, int Rect1Y1, int Rect1X2, int Rect1Y2, int Rect2X1, int Rect2Y1, int Rect2X2, int Rect2Y2);



// ----------- ОСНОВНАЯ ПРОГРАММА -----------

int main()
{


	// Объявление и инициализация переменных:

	int x0 = 130;  // Изначальная абсцисса 
	int y0 = 250;  // Изначальная ордината 

	// Получим дескриптор консольного окна:

	HWND hwnd = GetConcolWindow();

	// Если дескриптор консольного окна существует:
	if (hwnd != NULL)
	{

		// Получим контекст устройства для консольного окна:
		hdc = GetWindowDC(hwnd);

		// Если контекст существует, то можем работать:
		if (hdc != 0)
		{


			// Люди:

			const int people_count = 6;  // Число людей

			Male Bob		 (610, 250, 10, "Bob");
			Male Ben		 (590, 400, 35, "Ben");
			Male Carlin		 (820, 350, 25, "Carlin");
			Female Eva		 (860, 300, 24, "Eva");
			Female Elisabeth (750, 250, 30, "Elisabeth");
			Female Rose		 (790, 200, 25, "Rose");

			Man* people[people_count];  // Список людей

			people[0] = &Bob;
			people[1] = &Ben;
			people[2] = &Carlin;
			people[3] = &Eva;
			people[4] = &Elisabeth;
			people[5] = &Rose;

			for (int i = 0; i < people_count; i++)people[i]->Show();  // Выведем людей на экран


			// Велосипеды:

			const int bicycles_count = 4;  // Число велосипедов

			BicycleWithSpinningWheels red_bicycle(600, 170, 40, 1, colour_dark_red);
			BicycleWithSpinningWheels blue_bicycle(600, 100, 40, 1, colour_orchid);
			TricycleWithSpinningWheels green_tricycle(600, 100, 40, 1, colour_mocassin);
			TricycleWithSpinningWheels medium_turquoise_tricycle(600, 100, 40, 1, colour_medium_turquoise);

			Bicycle* bicycles[bicycles_count];  // Список велосипедов

			bicycles[0] = &red_bicycle;
			bicycles[1] = &blue_bicycle;
			bicycles[2] = &green_tricycle;
			bicycles[3] = &medium_turquoise_tricycle;


			// Кнопки:

			const int number_of_buttons = 2;

			Button* revive_button = new Button(600, 120, 40, colour_crystal);  // Кнопка возрождения людей
			Button* change_bicycle_button = new Button(750, 70, 40, colour_sandy_tan);  // Кнопка смены велосипеда


			// Результаты коллизий велосипедов и кнопки смены велосипеда:

			Bicycle* CollisionsBicycleChangeBicycleButton[bicycles_count]; // Матрица переходов!

			CollisionsBicycleChangeBicycleButton[0] = bicycles[1];
			CollisionsBicycleChangeBicycleButton[1] = bicycles[2];
			CollisionsBicycleChangeBicycleButton[2] = bicycles[3];
			CollisionsBicycleChangeBicycleButton[3] = bicycles[0];


			// Результаты коллизий велосипедов и людей:

			string CollisionsBicycleMan[people_count][bicycles_count]; 

			CollisionsBicycleMan[0][0] = "Bob is killed by red bicycle...";
			CollisionsBicycleMan[0][1] = "Bob is killed by blu bicycle...";
			CollisionsBicycleMan[0][2] = "Bob is killed by green tricycle...";
			CollisionsBicycleMan[0][3] = "Bob is killed by medium turquoise tricycle...";

			CollisionsBicycleMan[1][0] = "Ben is killed by red bicycle...";
			CollisionsBicycleMan[1][1] = "Ben is killed by blu bicycle...";
			CollisionsBicycleMan[1][2] = "Ben is killed by green tricycle...";
			CollisionsBicycleMan[1][3] = "Ben is killed by medium turquoise tricycle...";

			CollisionsBicycleMan[2][0] = "Carlin is killed by red bicycle...";
			CollisionsBicycleMan[2][1] = "Carlin is killed by blu bicycle...";
			CollisionsBicycleMan[2][2] = "Carlin is killed by green tricycle...";
			CollisionsBicycleMan[2][3] = "Carlin is killed by medium turquoise tricycle...";

			CollisionsBicycleMan[3][0] = "Eva is killed by red bicycle...";
			CollisionsBicycleMan[3][1] = "Eva is killed by blu bicycle...";
			CollisionsBicycleMan[3][2] = "Eva is killed by green tricycle...";
			CollisionsBicycleMan[3][3] = "Eva is killed by medium turquoise tricycle...";

			CollisionsBicycleMan[4][0] = "Elisabeth is killed by red bicycle...";
			CollisionsBicycleMan[4][1] = "Elisabeth is killed by blu bicycle...";
			CollisionsBicycleMan[4][2] = "Elisabeth is killed by green tricycle...";
			CollisionsBicycleMan[4][3] = "Elisabeth is killed by medium turquoise tricycle...";

			CollisionsBicycleMan[5][0] = "Rose is killed by red bicycle...";
			CollisionsBicycleMan[5][1] = "Rose is killed by blu bicycle...";
			CollisionsBicycleMan[5][2] = "Rose is killed by green tricycle...";
			CollisionsBicycleMan[5][3] = "Rose is killed by medium turquoise tricycle...";


			// Настоящий велосипед, за которым идет управление:

			Bicycle* actual_bicycle = bicycles[0];


			// Переменные основного цикла:

			string message = "";  // Сообщение, выводимое на экран к концу цикла
			int visible_messages_count = 0;  // Число видимых на экране сообщений
			int got_messages_count = 0;  // Число собранных за цикл сообщений
			int kills_count = 0;  // Число убийств общее
			int dead_now_count = 0;  // Число убитых на экране


			// Основной цикл:
			while (true)
			{

				// Выход из цикла при нажатии Escape
				if (KEY_DOWN(VK_ESCAPE))
					break;

				actual_bicycle->BikeRideOneStep(7);  // Проезжаем 1 шаг на велосипеде

				for (int i = 0; i < people_count; i++)people[i]->Show();  // Перепечатываем людей
				revive_button->Show();  // Перепечатываем кнопку

				// Смотрим, была ли коллизия людей и велосипедов:
				for (int i = 0; i < people_count; i++) {
					for (int j = 0; j < 4; j++) {

						// Если была коллизия:
						if (Collision(people[i], bicycles[j])) {

							// Если человек, с которым была коллизия, жив:
							if (people[i]->GetIsAlive()) {

								people[i]->SetIsAlive(false);  // Теперь мертв
								kills_count++;  // Число убийств 
								dead_now_count++;  // Число убитых на экране

								// Сообщение об убийстве:
								message += CollisionsBicycleMan[i][j] + " (total kills: " + to_string(kills_count) + ")\n";
								got_messages_count++;  // Число сообщений на экране

							}

						} // Конец блока "Если была коллизия"

					}
				} // Конец блока "Смотрим, была ли коллизия людей и велосипедов"


				// Смотрим, была ли коллизия кнопки возрождения с велосипедами:
				for (int j = 0; j < bicycles_count; j++) {

					// Если такая коллизия была
					if (Collision(revive_button, bicycles[j])) {

						// Если на экране есть убитые
						if (dead_now_count != 0) {

							// Сообщение о возрождении
							message += "Revive button activated! Reviving people...\n";
							got_messages_count++;

							// Возрождаем людей
							for (int i = 0; i < people_count; i++)people[i]->SetIsAlive(true);

							// Число убитых равно нулю
							dead_now_count = 0;

						} // Конец блока "Если на экране есть убитые"


					} // Конец блока "Если такая коллизия была"			

				}  // Конец блока "Смотрим, была ли коллизия кнопки возрождения с велосипедами"


				bool was_collisions_with_change_bicycle_button = false;  // Флаг коллизии с кнопкой смены велосипеда


				// Смотрим, была ли коллизия кнопки смены велосипеда с велосипедами:
				for (int j = 0; j < bicycles_count; j++) {


					// Если такая коллизия была
					if (Collision(change_bicycle_button, bicycles[j])) {

						was_collisions_with_change_bicycle_button = true;  // Флаг коллизии с кнопкой смены велосипеда

						// Если кнопка ранее не активирована
						if (!change_bicycle_button->GetIsActivated()) {

							actual_bicycle->Hide(); // Текущий велосипед прячем

							CollisionsBicycleChangeBicycleButton[j]->SetX(actual_bicycle->GetX()); // Новый велосипед появится на месте текущего
							CollisionsBicycleChangeBicycleButton[j]->SetY(actual_bicycle->GetY());

							actual_bicycle = CollisionsBicycleChangeBicycleButton[j];  // Меняем велосипеды

							change_bicycle_button->SetIsActivated(true);  // Кнопка нажата

							actual_bicycle->Show();  // Показываем велосипед

							change_bicycle_button->Show();  // Перепечатываем кнопку

							break; // Выходим из цикла


						} // Конец блока "Если кнопка ранее не активирована"

						change_bicycle_button->Show();  // Перепечатываем кнопку

					}  // Конец блока "Если такая коллизия была"		


					// Если такой коллизии не было ни для одного велосипеда, кнопку можно считать отпущенной:
					if (j == bicycles_count - 1 && !was_collisions_with_change_bicycle_button)
						change_bicycle_button->SetIsActivated(false);


				} // Конец блока "Смотрим, была ли коллизия кнопки смены велосипеда с велосипедами"


				// Если выведено слишком много сообщений на экран
				if (visible_messages_count + got_messages_count > 20) {

					system("cls");  // Очистка экрана

					// Перепечатываем всё:
					for (int i = 0; i < people_count; i++)people[i]->Show();
					revive_button->Show();
					change_bicycle_button->Show();
					actual_bicycle->Show();

					cout << message;

					visible_messages_count = got_messages_count;

					message = "";
					got_messages_count = 0;

				}
				else {  // Еще есть место для сообщений

					cout << message;

					visible_messages_count += got_messages_count;

					message = "";
					got_messages_count = 0;

				}

				Sleep(30);

			}
		}
	}
}

HWND GetConcolWindow()
{
	char str[128];
	LPWSTR title = (LPWSTR)"xxxxxxxxxxxxxxxxx";
	GetConsoleTitle((LPWSTR)str, sizeof((LPWSTR)str));
	SetConsoleTitle(title);

	Sleep(100);

	HWND hwnd = FindWindow(NULL, (LPWSTR)title);
	SetConsoleTitle((LPWSTR)str);

	return hwnd;

}

bool Collision(Man* M, Bicycle* Bike)
{
	if (!M->GetVisible()) return false;
	if (!Bike->GetVisible()) return false;

	// Координаты прямоугольников человека и байка
	int Rect1X1, Rect1Y1, Rect1X2, Rect1Y2, Rect2X1, Rect2Y1, Rect2X2, Rect2Y2;

	// Для человека:

	int man_x = M->GetX();
	int man_y = M->GetY();
	int man_size = M->GetSize();

	Rect1X1 = man_x;
	Rect1Y1 = man_y;
	Rect1X2 = man_x + man_size;
	Rect1Y2 = man_y + 2.87 * man_size;

	// Для байка:

	int bike_x = Bike->GetX();
	int bike_y = Bike->GetY();
	int bike_size = Bike->GetSize();

	Rect2X1 = bike_x;
	Rect2Y1 = bike_y;
	Rect2X2 = bike_x + 3 * bike_size;
	Rect2Y2 = bike_y + 1.5 * bike_size;

	// Пересекаются ли два прямоугольника:
	return AreRectanglesColliding(Rect1X1, Rect1Y1, Rect1X2, Rect1Y2, Rect2X1, Rect2Y1, Rect2X2, Rect2Y2);

};

// Коллизия кнопки и велосипеда
bool Collision(Button* B, Bicycle* Bike) {

	if (!B->GetVisible()) return false;
	if (!Bike->GetVisible()) return false;

	// Координаты прямоугольников человека и байка
	int Rect1X1, Rect1Y1, Rect1X2, Rect1Y2, Rect2X1, Rect2Y1, Rect2X2, Rect2Y2;

	// Для человека:

	int but_x = B->GetX();
	int but_y = B->GetY();
	int but_size = B->GetSize();

	Rect1X1 = but_x;
	Rect1Y1 = but_y;
	Rect1X2 = but_x + but_size;
	Rect1Y2 = but_y + but_size;

	// Для байка:

	int bike_x = Bike->GetX();
	int bike_y = Bike->GetY();
	int bike_size = Bike->GetSize();

	Rect2X1 = bike_x;
	Rect2Y1 = bike_y;
	Rect2X2 = bike_x + 3 * bike_size;
	Rect2Y2 = bike_y + 1.5 * bike_size;

	// Пересекаются ли два прямоугольника:
	return AreRectanglesColliding(Rect1X1, Rect1Y1, Rect1X2, Rect1Y2, Rect2X1, Rect2Y1, Rect2X2, Rect2Y2);
}
// Пересекаются ли прямоугольники:
bool AreRectanglesColliding(int Rect1X1, int Rect1Y1, int Rect1X2, int Rect1Y2, int Rect2X1, int Rect2Y1, int Rect2X2, int Rect2Y2) {

	return (

		(

			((Rect1X1 >= Rect2X1 && Rect1X1 <= Rect2X2) || (Rect1X2 >= Rect2X1 && Rect1X2 <= Rect2X2))
			&&
			((Rect1Y1 >= Rect2Y1 && Rect1Y1 <= Rect2Y2) || (Rect1Y2 >= Rect2Y1 && Rect1Y2 <= Rect2Y2))

			)

		||

		(

			((Rect2X1 >= Rect1X1 && Rect2X1 <= Rect1X2) || (Rect2X2 >= Rect1X1 && Rect2X2 <= Rect1X2))
			&&
			((Rect2Y2 >= Rect1Y1 && Rect2Y2 <= Rect1Y2) || (Rect2Y2 >= Rect1Y1 && Rect2Y2 <= Rect1Y2))
			)
		) || (

			(
				((Rect1X1 >= Rect2X1 && Rect1X1 <= Rect2X2) || (Rect1X2 >= Rect2X1 && Rect1X2 <= Rect2X2))
				&&
				((Rect2Y2 >= Rect1Y1 && Rect2Y2 <= Rect1Y2) || (Rect2Y2 >= Rect1Y1 && Rect2Y2 <= Rect1Y2))
				)

			||

			(

				((Rect2X1 >= Rect1X1 && Rect2X1 <= Rect1X2) || (Rect2X2 >= Rect1X1 && Rect2X2 <= Rect1X2))
				&&
				((Rect1Y1 >= Rect2Y1 && Rect1Y1 <= Rect2Y2) || (Rect1Y2 >= Rect2Y1 && Rect1Y2 <= Rect2Y2))

				)
			);


}