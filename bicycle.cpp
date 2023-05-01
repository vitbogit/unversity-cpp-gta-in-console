// ____________________________________________________
// ____________РЕАЛИЗАЦИЯ МЕТОДОВ КЛАССОВ______________
// ____________________________________________________

#include <windows.h>
#include "bicycle.h"
#include <cmath>
#include <string>

extern HDC hdc;  // Контекст устройства


// ---------------- ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ -----------


// Инверсия цвета
COLORREF invert_colour(COLORREF colour_to_invert) {


	// Возвращаем инвертированный цвет:
	return RGB(255 - GetRValue(colour_to_invert), 255 - GetGValue(colour_to_invert), 255 - GetBValue(colour_to_invert));


}  // Конец блока "Инверсия цвета"


// ------------------------- МАКРОСЫ ------------------

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)  // Макрос для определения нажатия клавиш


// ----------------- ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ -------------

const int gl_drag_sleep_time = 30;  // Время сна после шага буксировки
const int gl_drag_sleep_time_one_step = 15;  // Время сна после шага буксировки в режиме "1 шаг"

const int gl_min_bike_size = 15;  // Минимальный размер велосипеда

const int gl_max_bike_size = 100;  // Максимальный размер велосипеда

// Цвета:

const COLORREF colour_black RGB(0, 0, 0);
const COLORREF colour_red RGB(255, 0, 0);
const COLORREF colour_green RGB(0, 255, 0);
const COLORREF colour_blue RGB(0, 0, 255);
const COLORREF colour_white RGB(255, 255, 255);

// Цвета в соответствии с их ролью:

const COLORREF colour_default_base = colour_blue;  // По умолчанию основной цвет объектов 
const COLORREF colour_default_base2 = colour_black;  // По умолчанию второй основной цвет объектов 
const COLORREF colour_default_backgroung = colour_white;  // По умолчанию цвет фона 
const COLORREF colour_inverted_default_backgroung = invert_colour(colour_default_backgroung);  // Инвертированный цвет фона по умолчанию


// -----------------------------------------------------
// -- 1. Реализация методов базового класса Location ---
// -----------------------------------------------------


// Конструктор базового класса
Location::Location(int InitX, int InitY)
{


	X = InitX;  // Устанавливаем значение абсциссы базового класса

	Y = InitY;  // Устанавливаем значение ординаты базового класса


} // Конец блока "Конструктор базового класса"


// Деструктор базового класса
Location::~Location()
{


	// Пустое тело


} // Конец блока "Деструктор базового класса"


// Получение значения абсциссы базового класса
int Location::GetX()
{


	return X;  // Возвращаем абсциссу базового класса


} // Конец блока "Получение значения абсциссы базового класса"


// Получение значения ординаты базового класса
int Location::GetY()
{


	return Y;  // Возвращаем ординату базового класса


} // Конец блока "Получение значения ординаты базового класса"


// Изменение значения абсциссы базового класса
void Location::SetX(int NewX)
{


	X = NewX;  // Устанавливаем новое значение абсциссы базового класса


} // Конец блока "Изменение значения абсциссы базового класса"


// Изменение значения ординаты базового класса
void Location::SetY(int NewY)
{


	Y = NewY;  // Устанавливаем новое значение ординаты базового класса


} // Конец блока "Изменение значения ординаты базового класса"


// -----------------------------------------------------
// --------- 2. Реализация методов класса Point --------
// -----------------------------------------------------


// Конструктор класса точки
Point::Point(int InitX, int InitY) : Location(InitX, InitY)
{


	Visible = false;  // При создании точка не видна, устанавливаем поле видимости на False


} // Конец блока "Конструктор класса Point"


// Деструктор класса точки
Point::~Point()
{


	// Пустое тело


} // Конец блока "Деструктор класса Point"


// Получение значения видимости точки
bool Point::GetVisible() {


	return Visible;  // Возвращаем значение поля видимости


} // Конец блока "Получение значения видимости точки"


// Изменение значения видимости точки
void Point::SetVisible(bool NewVisible)
{


	if (Visible != NewVisible) {  // Если новое значение поля видимости не равно текущему

		Visible = NewVisible;  // Устанавливаем в поле видимости новое значение

		if (Visible) {  // Если точка должна быть видна

			Show();  // Показываем точку

		} // if

		else {  // Если точка должна быть скрыта

			Hide();  // Скрываем точку

		} // else

	} // Конец блока "Если новое значение поля видимости не равно текущему"


} // Конец блока "Изменение значения видимости точки"


// Показать точку на экране
void Point::Show()
{


	Visible = true;  // Точка становится видна

	Draw();  // Рисуем точку базового цвета


} // Конец блока "Показать точку на экране"


// Показать точку на экране, если она не показана
void Point::GetShowed() {

	if (!Visible) Show();  // Показываем точку на экране, если она еще не видна

}  // Конец блока "Показать точку на экране, если она не показана"


// Убрать точку с экрана
void Point::Hide()
{


	Visible = false;  // Точка становится не видна

	Draw();  // Рисуем точку цвета фона 


} // Конец блока "Убрать точку с экрана"


// Убрать точку с экрана, если она не убрана
void Point::GetHidden() {

	if (Visible) Hide();  // Если точка видна, то убираем ее

}  // Конец блока "Убрать точку с экрана, если она не убрана"


// Рисовать точку
void Point::Draw() {


	// Цвет точки:
	COLORREF colour;

	// Устанавливаем цвет точки:
	if (Visible) colour = colour_default_base;
	else colour = colour_default_backgroung;


	// Рисуем точку:

	SetPixel(hdc, X, Y, colour);
	SetPixel(hdc, X + 1, Y, colour);
	SetPixel(hdc, X, Y + 1, colour);
	SetPixel(hdc, X + 1, Y + 1, colour);


}  // Конец блока "Рисовать точку"


// Переместить точку на экране
void Point::MoveTo(int NewX, int NewY)
{


	if (Visible) {  // Если точка сейчас видна на экране

		Hide();  // Скрыть точку

		// Обновляем координаты точки:

		X = NewX;  // Новая абсцисса

		Y = NewY;  // Новая ордината

		Show();  // Показать точку по новым координатам

	}  // if

	else {  // Если точка сейчас не видна на экране

		// Обновляем координаты точки:

		X = NewX;  // Новая абсцисса

		Y = NewY;  // Новая ордината

	} // else


} // Конец блока "Переместить точку на экране"


// Буксировка точки
void Point::Drag(int Step)
{


	if (!Visible) Show();  // Считаем, что нет смысла буксировать невидимую точку, делаем её видимой

	int FigX, FigY;  // Новые координаты точки, получаемые в ходе буксировки

	// Новые кординаты точки изначально равны начальным координатам:

	FigX = GetX();  // Начальная абсцисса

	FigY = GetY();  // Начальная ордината


	// Бесконечный цикл буксировки:
	while (1) {

		if (KEY_DOWN(VK_ESCAPE)) {  // Если нажата клавиша 27 ("Esc")

			break;  // Выход из бесконечного цикла буксировки

		}  // if

		if (KEY_DOWN(VK_LEFT)) {  // Если нажата клавиша 37 ("Стрелка влево")

			FigX = FigX - Step;  // Новая абсцисса точки меньше текущей абсциссы на шаг буксировки

		}  // if

		if (KEY_DOWN(VK_RIGHT)) {  // Если нажата клавиша 39 ("Стрелка вправо")

			FigX = FigX + Step;  // Новая абсцисса точки больше текущей абсциссы на шаг буксировки

		}  // if

		if (KEY_DOWN(VK_DOWN)) {  // Если нажата клавиша 40 ("Стрелка вниз")

			FigY = FigY + Step;  // Новая ордината точки больше текущей ординаты на шаг буксировки

		}  // if

		if (KEY_DOWN(VK_UP)) {  // Если нажата клавиша 38 ("Стрелка вверх")

			FigY = FigY - Step;   // Новая ордината точки меньше текущей ординаты на шаг буксировки

		}  // if

		MoveTo(FigX, FigY);  // Перемещаем точку по новым координатам

		Sleep(gl_drag_sleep_time);  // После совершенного шага буксировки полагается спать установленное время

	} // Конец блока "Бесконечный цикл буксировки"


} // Конец блока "Буксировка точки"


// ------------------------------------------------------
// --------- 3. Реализация методов класса Bicycle -------
// ------------------------------------------------------


// Конструктор класса велосипеда 
Bicycle::Bicycle(int InitX, int InitY, int InitSize, int InitDirection) : Point(InitX, InitY)
{


	size = InitSize;  // Устанавливаем размер велосипеда

	direction = InitDirection;  // Устанавливаем направление велосипеда (0 - влево, 1 - вправо)


} // Конец блока "Конструктор класса велосипеда"


// Деструктор класса велосипеда
Bicycle::~Bicycle() {


	// Пустое тело


}  // Конец блока "Деструктор класса велосипеда"


// Получение размера велосипеда
int Bicycle::GetSize() {


	return size; // Возвращаем размер велосипеда


} // Конец блока "Получение размера велосипеда"


// Установка значения размера велосипеда
void Bicycle::SetSize(int NewSize) { // Установка значения поля Size


	bool was_visible = Visible;  // Дан видимый или скрытый велосипед

	GetHidden();  // В любом случае велосипед не должен быть виден при изменении его параметра

	size = NewSize;  // Устанавливаем новый размер велосипеда

	if (size < gl_min_bike_size) size = gl_min_bike_size;  // Не должны перейти нижнюю границу размера велосипеда

	if (size > gl_max_bike_size) size = gl_max_bike_size;  // Не должны перейти верхнюю границу размера велосипеда

	if (was_visible) Show();  // Показываем велосипед, если изначально он был виден


} // SetSize()


// Получение значения направления велосипеда
int Bicycle::GetDirection() {


	return direction;  // Возвращаем направление велосипеда


}  // Конец блока "Получение значения направления велосипеда"


// Установка значения направления велосипеда
void Bicycle::SetDirection(int NewDirection) {


	bool was_visible = Visible;  // Дан видимый или скрытый велосипед

	GetHidden();  // В любом случае велосипед не должен быть виден при изменении его параметра

	direction = NewDirection;  // Устанавливаем новое направление велосипеда

	if (was_visible) Show();  // Показываем велосипед, если изначально он был виден


}  // Конец блока "Установка значения направления велосипеда"


// Повернуть велосипед
void Bicycle::Rotate() {


	bool was_visible = Visible;  // Дан видимый или скрытый велосипед

	GetHidden();  // В любом случае велосипед не должен быть виден при изменении его параметра

	direction = 1 - direction;  // Устанавливаем новое направление велосипеда

	if (was_visible) Show();  // Показываем велосипед, если изначально он был виден


} // Конец блока "Повернуть велосипед"


// Увеличить размер велосипеда
void Bicycle::Expand(int DeltaSize) {


	bool was_visible = Visible;  // Дан видимый или скрытый велосипед

	GetHidden();  // В любом случае велосипед не должен быть виден при изменении его параметра

	SetSize(size + DeltaSize);

	if (was_visible) Show();  // Показываем велосипед, если изначально он был виден


}  // Конец блока "Увеличить размер велосипеда"


// Уменьшить размер велосипеда
void Bicycle::Reduce(int DeltaSize) {


	Expand(-DeltaSize);  // Вызываем функцию увеличения с отрицательным параметром


}  // Конец блока "Уменьшить размер велосипеда"


// Рисовать велосипед
void Bicycle::Draw() {


	COLORREF colour;  // Цвет велосипеда


	// Устанавливаем цвет:
	if (Visible) colour = colour_default_base;
	else colour = colour_default_backgroung;


	// Создаем кисть:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, colour);

	SelectObject(hdc, hPen1); // Делаем кисть активной


	// -- ПАРАМЕТРЫ ВЕЛОСИПЕДА --
	// 
	// () Весь велосипед лежит в прямоугольнике от (X,Y) до (X + 3*size, Y + 1.5*size)
	// () Конструкционный центр велосипеда: (X + 1.5*size, Y + size)
	// () Диаметр колес - size
	// () Длина перекладин - size
	// () Ширина велосипеда влево и вправо от конструкционного центра - по 1,5 size
	// () Высота велосипеда над конструкционным центром - 1 size
	// () Глубина велосипеда под конструкционным центром - 0,5 size


	// Зададим координаты:

	int center_x, center_y; // Центр велосипеда (конструкционный центр, не геометрический)

	int left_wheel_center_x, left_wheel_center_y,  // Центры колес велосипеда
		right_wheel_center_x, right_wheel_center_y;


	// Зададим размеры:

	int l = size;  // Размер перекладины корпуса

	int r = l * 0.5;  // Радиус колес

	int wheel_cos = r / sqrt(pow((l * 1.7 / 2), 2) + pow(2, r));  // Косинус между горизонтом и перекладиной от колеса к верхней части корпуса

	// Рассчитаем координаты:

	center_x = X + 1.5 * l;
	center_y = Y + l;

	left_wheel_center_x = center_x - l;
	left_wheel_center_y = center_y;

	right_wheel_center_x = center_x + l;
	right_wheel_center_y = center_y;

	// --------- Рисуем корпус велосипеда ----------

	MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо в конструкционный центр

	// Основной треугольник корпуса:
	LineTo(hdc, center_x + l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x - l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x, center_y);

	// Если велосипед едет влево:
	if (direction == 0) {

		MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо в конструкционный центр

		LineTo(hdc, center_x + l - r, center_y);  // К заднему колесу перекладина из центра

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в задний верх велосипеда

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // К заднему колесу перекладина из заднего верха велосипеда

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в передний верх велосипеда

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // К переднему колесу перекладина из переднего верха велосипеда

	} // if

	else {  // Если велосипед едет право:

		MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо в конструкционный центр

		LineTo(hdc, center_x - l + r, center_y);  // К заднему колесу перекладина из центра

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в задний верх велосипеда

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // К заднему колесу перекладина из заднего верха велосипеда

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в передний верх велосипеда

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // К переднему колесу перекладина из переднего верха велосипеда

	}  // else 


	// --------- Рисуем руль велосипеда ----------


	// Если велосипед едет влево:
	if (direction == 0) {

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо к носу велосипеда

		// Непосредственно рисуем руль:
		LineTo(hdc, center_x - l / 2 - l / 8, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 - l / 3, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 + l / 12, center_y - (l / 2) * 1.7 - l / 8);

	} // if

	else {  // Если велосипед едет право:

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо к носу велосипеда

		// Непосредственно рисуем руль:
		LineTo(hdc, center_x + l / 2 + l / 8, center_y - l);
		LineTo(hdc, center_x + l / 2 + l / 3, center_y - l);
		LineTo(hdc, center_x + l / 2 - l / 12, center_y - l);

	}  // else 


	// ---------- Рисуем колеса велосипеда ---------

	Ellipse(hdc, (left_wheel_center_x - 0.5 * l), left_wheel_center_y - 0.5 * l, left_wheel_center_x + 0.5 * l, left_wheel_center_y + 0.5 * l);
	Ellipse(hdc, (right_wheel_center_x - 0.5 * l), right_wheel_center_y - 0.5 * l, right_wheel_center_x + 0.5 * l, right_wheel_center_y + 0.5 * l);


}  // Конец блока "Рисовать велосипед"


// Что происходит с велосипедом, когда он едет в новую точку:
void Bicycle::WhenRide(int NewX, int NewY) {


	// Если велосипед поедет в сторону, противоположную его текущему направлению, то велосипед должен повернуться:
	if ((NewX > X && direction == 0) || (NewX < X && direction == 1)) {

		Rotate();  // Поворот велосипеда

	}  // if

}  // Конец блока "Что происходит с велосипедом, когда он едет в новую точку"


// Велосипед на экране едет в новую точку
void Bicycle::RideTo(int NewX, int NewY) {


	WhenRide(NewX, NewY);  // Что происходит с велосипедом, когда он едет в новую точку

	MoveTo(NewX, NewY);  // Перемещаем велосипед в новую точку


}  // Конец блока "Велосипед на экране едет в новую точку"


// Управление велосипедом 
void Bicycle::BikeRiding(int Step) // Прокладывание пути для велосипеда, т. е. буксировка с поворотом в нужную сторону
{


	if (!Visible) Show();  // Считаем, что нет смысла ездить на невидимом велосипеде, делаем его видимым

	int FigX, FigY;  // Новые координаты точки, получаемые в ходе езды

	// Новые кординаты точки изначально равны начальным координатам:

	FigX = GetX();  // Начальная абсцисса

	FigY = GetY();  // Начальная ордината


	// Бесконечный цикл езды на велосипеде:
	while (1) {

		if (KEY_DOWN(VK_ESCAPE)) {  // Если нажата клавиша 27 ("Esc")

			break;  // Выход из бесконечного цикла езды

		}  // if

		if (KEY_DOWN(VK_LEFT)) {  // Если нажата клавиша 37 ("Стрелка влево")

			FigX = FigX - Step;  // Новая абсцисса точки меньше текущей абсциссы на шаг езды

		}  // if

		if (KEY_DOWN(VK_RIGHT)) {  // Если нажата клавиша 39 ("Стрелка вправо")

			FigX = FigX + Step;  // Новая абсцисса точки больше текущей абсциссы на шаг езды

		}  // if

		if (KEY_DOWN(VK_DOWN)) {  // Если нажата клавиша 40 ("Стрелка вниз")

			FigY = FigY + Step;  // Новая ордината точки больше текущей ординаты на шаг езды

		}  // if

		if (KEY_DOWN(VK_UP)) {  // Если нажата клавиша 38 ("Стрелка вверх")

			FigY = FigY - Step;   // Новая ордината точки меньше текущей ординаты на шаг езды

		}  // if

		RideTo(FigX, FigY);  // Велосипед едет по новым координатам

		Sleep(gl_drag_sleep_time);  // После совершенного шага езды полагается спать установленное время

	} // Конец блока "Бесконечный цикл езды"


}  // Конец блока "Управление велосипедом"

// Управление велосипедом на 1 шаг
void Bicycle::BikeRideOneStep(int Step) {


	if (!Visible) Show();  // Считаем, что нет смысла ездить на невидимом велосипеде, делаем его видимым

	int FigX, FigY;  // Новые координаты точки, получаемые в ходе езды

	// Новые кординаты точки изначально равны начальным координатам:

	FigX = GetX();  // Начальная абсцисса

	FigY = GetY();  // Начальная ордината

	while (true) {  // Цикл до 1-ого нажатия

		if (KEY_DOWN(VK_LEFT)) {  // Если нажата клавиша 37 ("Стрелка влево")

			FigX = FigX - Step;  // Новая абсцисса точки меньше текущей абсциссы на шаг езды

			break;

		}  // if

		if (KEY_DOWN(VK_RIGHT)) {  // Если нажата клавиша 39 ("Стрелка вправо")

			FigX = FigX + Step;  // Новая абсцисса точки больше текущей абсциссы на шаг езды

			break;

		}  // if

		if (KEY_DOWN(VK_DOWN)) {  // Если нажата клавиша 40 ("Стрелка вниз")

			FigY = FigY + Step;  // Новая ордината точки больше текущей ординаты на шаг езды

			break;

		}  // if

		if (KEY_DOWN(VK_UP)) {  // Если нажата клавиша 38 ("Стрелка вверх")

			FigY = FigY - Step;   // Новая ордината точки меньше текущей ординаты на шаг езды

			break;

		}  // if

	}  // while 


	RideTo(FigX, FigY);  // Велосипед едет по новым координатам

	Sleep(gl_drag_sleep_time_one_step);  // После совершенного шага езды полагается спать установленное время

} // Конец блока "Управление велосипедом на 1 шаг"


// -------------------------------------------------------------
// --------- 4 Реализация методов класса ColouredBicycle -------
// -------------------------------------------------------------


// Конструктор цветного велосипеда
ColouredBicycle::ColouredBicycle(int InitX, int InitY, int InitSize, int InitDirection, COLORREF InitColour) : Bicycle(InitX, InitY, InitSize, InitDirection)
{


	colour = InitColour;  // Устанавливаем цвет велосипеда


}  // Конец блока "Конструктор цветного велосипеда"


// Деструктор цветного велосипеда
ColouredBicycle::~ColouredBicycle() {


	// Пустое тело


}  // Конец блока "Деструктор цветного велосипеда"


// Получить цвет велосипеда
COLORREF ColouredBicycle::GetColour() {


	return colour;  // Возвращаем цвет велосипеда


}  // Конец блока "Получить цвет велосипеда"


// Установить новый цвет велосипеда
void ColouredBicycle::SetColour(COLORREF NewColour) {


	bool was_visible = Visible;  // Дан видимый или скрытый велосипед

	GetHidden();  // В любом случае велосипед не должен быть виден при изменении его параметра

	colour = NewColour;  // Устанавливаем новый цвет велосипеда

	if (was_visible) Show();  // Показываем велосипед, если изначально он был виден


}  // Конец блока "Установить новый цвет велосипеда"


// Рисовать цветной велосипед
void ColouredBicycle::Draw() {


	// Реальный цвет велосипеда:
	COLORREF real_colour;

	// Если велосипед скрытый, реальный его цвет - это цвет фона:
	if (!Visible) real_colour = colour_default_backgroung;
	else real_colour = colour;

	// Создаем кисть:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, real_colour);

	SelectObject(hdc, hPen1); // Делаем кисть активной


	// -- ПАРАМЕТРЫ ВЕЛОСИПЕДА --
	// 
	// () Весь велосипед лежит в прямоугольнике от (X,Y) до (X + 3*size, Y + 1.5*size)
	// () Конструкционный центр велосипеда: (X + 1.5*size, Y + size)
	// () Диаметр колес - size
	// () Длина перекладин - size
	// () Ширина велосипеда влево и вправо от конструкционного центра - по 1,5 size
	// () Высота велосипеда над конструкционным центром - 1 size
	// () Глубина велосипеда под конструкционным центром - 0,5 size


	// Зададим координаты:

	int center_x, center_y; // Центр велосипеда (конструкционный центр, не геометрический)

	int left_wheel_center_x, left_wheel_center_y,  // Центры колес велосипеда
		right_wheel_center_x, right_wheel_center_y;


	// Зададим размеры:

	int l = size;  // Размер перекладины корпуса

	int r = l * 0.5;  // Радиус колес

	int wheel_cos = r / sqrt(pow((l * 1.7 / 2), 2) + pow(2, r));  // Косинус между горизонтом и перекладиной от колеса к верхней части корпуса

	// Рассчитаем координаты:

	center_x = X + 1.5 * l;
	center_y = Y + l;

	left_wheel_center_x = center_x - l;
	left_wheel_center_y = center_y;

	right_wheel_center_x = center_x + l;
	right_wheel_center_y = center_y;

	// --------- Рисуем корпус велосипеда ----------

	MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо в конструкционный центр

	// Основной треугольник корпуса:
	LineTo(hdc, center_x + l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x - l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x, center_y);

	// Если велосипед едет влево:
	if (direction == 0) {

		MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо в конструкционный центр

		LineTo(hdc, center_x + l - r, center_y);  // К заднему колесу перекладина из центра

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в задний верх велосипеда

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // К заднему колесу перекладина из заднего верха велосипеда

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в передний верх велосипеда

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // К переднему колесу перекладина из переднего верха велосипеда

	} // if

	else {  // Если велосипед едет право:

		MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо в конструкционный центр

		LineTo(hdc, center_x - l + r, center_y);  // К заднему колесу перекладина из центра

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в задний верх велосипеда

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // К заднему колесу перекладина из заднего верха велосипеда

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в передний верх велосипеда

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // К переднему колесу перекладина из переднего верха велосипеда

	}  // else 


	// --------- Рисуем руль велосипеда ----------


	// Если велосипед едет влево:
	if (direction == 0) {

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо к носу велосипеда

		// Непосредственно рисуем руль:
		LineTo(hdc, center_x - l / 2 - l / 8, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 - l / 3, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 + l / 12, center_y - (l / 2) * 1.7 - l / 8);

	} // if

	else {  // Если велосипед едет право:

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо к носу велосипеда

		// Непосредственно рисуем руль:
		LineTo(hdc, center_x + l / 2 + l / 8, center_y - l);
		LineTo(hdc, center_x + l / 2 + l / 3, center_y - l);
		LineTo(hdc, center_x + l / 2 - l / 12, center_y - l);

	}  // else 


	// ---------- Рисуем колеса велосипеда ---------

	Ellipse(hdc, (left_wheel_center_x - 0.5 * l), left_wheel_center_y - 0.5 * l, left_wheel_center_x + 0.5 * l, left_wheel_center_y + 0.5 * l);
	Ellipse(hdc, (right_wheel_center_x - 0.5 * l), right_wheel_center_y - 0.5 * l, right_wheel_center_x + 0.5 * l, right_wheel_center_y + 0.5 * l);


}  // Конец блока "Рисовать цветной велосипед"


// -------------------------------------------------------------
// -------- 5 Реализация методов класса TestBicycle ------
// -------------------------------------------------------------


// Конструктор TestBicycle
TestBicycle::TestBicycle(int InitX, int InitY, int InitSize, int InitDirection) : Bicycle(InitX, InitY, InitSize, InitDirection) {


	// Пустое тело


} // Конец блока "Конструктор TestBicycle"


// Деструктор TestBicycle
TestBicycle::~TestBicycle() {


	// Пустое тело


}  // Конец блока "Деструктор TestBicycle"


// Рисовать TestBicycle
void TestBicycle::Draw() {


	// Реальный цвет велосипеда:
	COLORREF real_colour;


	if (!Visible) real_colour = colour_default_backgroung;  // Если велосипед скрытый, реальный его цвет - это цвет фона
	else real_colour = colour_inverted_default_backgroung;  // Иначе - инвертированный цвет фона


	// Создаем кисть:
	HPEN hPen1 = CreatePen(PS_DASH, 1, real_colour);

	SelectObject(hdc, hPen1); // Делаем кисть активной


	// -- ПАРАМЕТРЫ ВЕЛОСИПЕДА --
	// 
	// () Весь велосипед лежит в прямоугольнике от (X,Y) до (X + 3*size, Y + 1.5*size)
	// () Конструкционный центр велосипеда: (X + 1.5*size, Y + size)
	// () Диаметр колес - size
	// () Длина перекладин - size
	// () Ширина велосипеда влево и вправо от конструкционного центра - по 1,5 size
	// () Высота велосипеда над конструкционным центром - 1 size
	// () Глубина велосипеда под конструкционным центром - 0,5 size


	// Зададим координаты:

	int center_x, center_y; // Центр велосипеда (конструкционный центр, не геометрический)

	int left_wheel_center_x, left_wheel_center_y,  // Центры колес велосипеда
		right_wheel_center_x, right_wheel_center_y;


	// Зададим размеры:

	int l = size;  // Размер перекладины корпуса

	int r = l * 0.5;  // Радиус колес

	int wheel_cos = r / sqrt(pow((l * 1.7 / 2), 2) + pow(2, r));  // Косинус между горизонтом и перекладиной от колеса к верхней части корпуса

	// Рассчитаем координаты:

	center_x = X + 1.5 * l;
	center_y = Y + l;

	left_wheel_center_x = center_x - l;
	left_wheel_center_y = center_y;

	right_wheel_center_x = center_x + l;
	right_wheel_center_y = center_y;

	// --------- Рисуем корпус велосипеда ----------

	MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо в конструкционный центр

	// Основной треугольник корпуса:
	LineTo(hdc, center_x + l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x - l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x, center_y);

	// Если велосипед едет влево:
	if (direction == 0) {

		MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо в конструкционный центр

		LineTo(hdc, center_x + l - r, center_y);  // К заднему колесу перекладина из центра

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в задний верх велосипеда

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // К заднему колесу перекладина из заднего верха велосипеда

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в передний верх велосипеда

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // К переднему колесу перекладина из переднего верха велосипеда

	} // if

	else {  // Если велосипед едет право:

		MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо в конструкционный центр

		LineTo(hdc, center_x - l + r, center_y);  // К заднему колесу перекладина из центра

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в задний верх велосипеда

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // К заднему колесу перекладина из заднего верха велосипеда

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в передний верх велосипеда

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // К переднему колесу перекладина из переднего верха велосипеда

	}  // else 


	// --------- Рисуем руль велосипеда ----------


	// Если велосипед едет влево:
	if (direction == 0) {

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо к носу велосипеда

		// Непосредственно рисуем руль:
		LineTo(hdc, center_x - l / 2 - l / 8, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 - l / 3, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 + l / 12, center_y - (l / 2) * 1.7 - l / 8);

	} // if

	else {  // Если велосипед едет право:

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо к носу велосипеда

		// Непосредственно рисуем руль:
		LineTo(hdc, center_x + l / 2 + l / 8, center_y - l);
		LineTo(hdc, center_x + l / 2 + l / 3, center_y - l);
		LineTo(hdc, center_x + l / 2 - l / 12, center_y - l);

	}  // else 


	// ---------- Рисуем колеса велосипеда ---------

	Ellipse(hdc, (left_wheel_center_x - 0.5 * l), left_wheel_center_y - 0.5 * l, left_wheel_center_x + 0.5 * l, left_wheel_center_y + 0.5 * l);
	Ellipse(hdc, (right_wheel_center_x - 0.5 * l), right_wheel_center_y - 0.5 * l, right_wheel_center_x + 0.5 * l, right_wheel_center_y + 0.5 * l);


}  // Конец блока "Рисовать TestBicycle"


// ---------------------------------------------------------------------
// -------- 6 Реализация методов класса BicycleWithSpinningWheels ------
// ---------------------------------------------------------------------


// Конструктор велосипеда с анимацией вращения колес при движении
BicycleWithSpinningWheels::BicycleWithSpinningWheels(int InitX, int InitY, int InitSize, int InitDirection, COLORREF InitColour) : ColouredBicycle(InitX, InitY, InitSize, InitDirection, InitColour) {


	SpinPhase = 0;  // Устанавливаем начальную фазу вращения колес


}  // Конец блока "Конструктор велосипеда с анимацией вращения колес при движении"


// Деструктор велосипеда с частичками почвы при движении
BicycleWithSpinningWheels::~BicycleWithSpinningWheels() {


	// Пустое тело


}  // Конец блока "Деструктор велосипеда с частичками почвы при движении"


// Получить фазу вращения колес
int BicycleWithSpinningWheels::GetSpinPhase() {


	return SpinPhase;


}  // Конец блока "Получить фазу вращения колес"


// Установить фазу вращения колес
void BicycleWithSpinningWheels::SetSpinPhase(float NewSpinPhase) {


	bool was_visible = Visible;  // Дан видимый или скрытый велосипед

	GetHidden();  // В любом случае велосипед не должен быть виден при изменении его параметра

	SpinPhase = NewSpinPhase;  // Устанавливаем новую фазу вращения колес

	if (SpinPhase > 6.28) SpinPhase = 0;  // Границы фазы

	if (was_visible) Show();  // Показываем велосипед, если изначально он был виден


} // Конец блока "Установить фазу вращения колес"


// Что происходит с велосипедом, когда он едет в новую точку
void BicycleWithSpinningWheels::WhenRide(int NewX, int NewY) {

	// Если велосипед поедет в сторону, противоположную его текущему направлению, то велосипед должен повернуться:
	if ((NewX > X && direction == 0) || (NewX < X && direction == 1)) {

		Rotate();  // Поворот велосипеда

	}  // if

	// Путь пройденный велосипедом при движении:
	float L = sqrt(
		pow((NewX - X), 2) +
		pow((NewY - Y), 2));

	// Радиус колес велосипеда:
	float R = size / 2;

	// Если велосипед едет вправо:
	if (direction == 1) {

		// Устанавливаем новую фазу вращения колеса (расчет геометрический, будто велосипед правда проехал L):
		SetSpinPhase(SpinPhase - L / R);

	}
	else {  // Велосипед едет влево

		// Устанавливаем новую фазу вращения колеса (расчет геометрический, будто велосипед правда проехал L):
		SetSpinPhase(SpinPhase + L / R);

	}

}  // Конец блока "Что происходит с велосипедом, когда он едет в новую точку"


// Рисовать велосипед с анимацией вращения колес
void BicycleWithSpinningWheels::Draw() {


	// Реальный цвет велосипеда:
	COLORREF real_colour;

	// Если велосипед скрытый, реальный его цвет - это цвет фона:
	if (!Visible) real_colour = colour_default_backgroung;
	else real_colour = colour;


	// Создаем кисть:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, real_colour);

	SelectObject(hdc, hPen1); // Делаем кисть активной


	// -- ПАРАМЕТРЫ ВЕЛОСИПЕДА --
	// 
	// () Весь велосипед лежит в прямоугольнике от (X,Y) до (X + 3*size, Y + 1.5*size)
	// () Конструкционный центр велосипеда: (X + 1.5*size, Y + size)
	// () Диаметр колес - size
	// () Длина перекладин - size
	// () Ширина велосипеда влево и вправо от конструкционного центра - по 1,5 size
	// () Высота велосипеда над конструкционным центром - 1 size
	// () Глубина велосипеда под конструкционным центром - 0,5 size


	// Зададим координаты:

	int center_x, center_y; // Центр велосипеда (конструкционный центр, не геометрический)

	int left_wheel_center_x, left_wheel_center_y,  // Центры колес велосипеда
		right_wheel_center_x, right_wheel_center_y;


	// Зададим размеры:

	int l = size;  // Размер перекладины корпуса

	int r = l * 0.5;  // Радиус колес

	int wheel_cos = r / sqrt(pow((l * 1.7 / 2), 2) + pow(2, r));  // Косинус между горизонтом и перекладиной от колеса к верхней части корпуса

	// Рассчитаем координаты:

	center_x = X + 1.5 * l;
	center_y = Y + l;

	left_wheel_center_x = center_x - l;
	left_wheel_center_y = center_y;

	right_wheel_center_x = center_x + l;
	right_wheel_center_y = center_y;

	// --------- Рисуем корпус велосипеда ----------

	MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо в конструкционный центр

	// Основной треугольник корпуса:
	LineTo(hdc, center_x + l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x - l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x, center_y);

	// Если велосипед едет влево:
	if (direction == 0) {

		MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо в конструкционный центр

		LineTo(hdc, center_x + l - r, center_y);  // К заднему колесу перекладина из центра

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в задний верх велосипеда

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // К заднему колесу перекладина из заднего верха велосипеда

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в передний верх велосипеда

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // К переднему колесу перекладина из переднего верха велосипеда

	} // if

	else {  // Если велосипед едет право:

		MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо в конструкционный центр

		LineTo(hdc, center_x - l + r, center_y);  // К заднему колесу перекладина из центра

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в задний верх велосипеда

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // К заднему колесу перекладина из заднего верха велосипеда

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в передний верх велосипеда

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // К переднему колесу перекладина из переднего верха велосипеда

	}  // else 


	// --------- Рисуем руль велосипеда ----------


	// Если велосипед едет влево:
	if (direction == 0) {

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо к носу велосипеда

		// Непосредственно рисуем руль:
		LineTo(hdc, center_x - l / 2 - l / 8, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 - l / 3, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 + l / 12, center_y - (l / 2) * 1.7 - l / 8);

	} // if

	else {  // Если велосипед едет право:

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо к носу велосипеда

		// Непосредственно рисуем руль:
		LineTo(hdc, center_x + l / 2 + l / 8, center_y - l);
		LineTo(hdc, center_x + l / 2 + l / 3, center_y - l);
		LineTo(hdc, center_x + l / 2 - l / 12, center_y - l);

	}  // else 


	// ---------- Рисуем колеса велосипеда ---------

	Ellipse(hdc, (left_wheel_center_x - 0.5 * l), left_wheel_center_y - 0.5 * l, left_wheel_center_x + 0.5 * l, left_wheel_center_y + 0.5 * l);
	Ellipse(hdc, (right_wheel_center_x - 0.5 * l), right_wheel_center_y - 0.5 * l, right_wheel_center_x + 0.5 * l, right_wheel_center_y + 0.5 * l);

	// -------------- Рисуем спицы колес -----------

	MoveToEx(hdc, left_wheel_center_x, left_wheel_center_y, NULL);  // Перемещаем перо к центру колеса
	LineTo(hdc, left_wheel_center_x + r * cos(SpinPhase), left_wheel_center_y - r * sin(SpinPhase));
	MoveToEx(hdc, left_wheel_center_x, left_wheel_center_y, NULL);  // Перемещаем перо к центру колеса
	LineTo(hdc, left_wheel_center_x + r * cos(SpinPhase + 1.57), left_wheel_center_y - r * sin(SpinPhase + 1.57));
	MoveToEx(hdc, left_wheel_center_x, left_wheel_center_y, NULL);  // Перемещаем перо к центру колеса
	LineTo(hdc, left_wheel_center_x + r * cos(SpinPhase + 3.14), left_wheel_center_y - r * sin(SpinPhase - 3.14));
	MoveToEx(hdc, left_wheel_center_x, left_wheel_center_y, NULL);  // Перемещаем перо к центру колеса
	LineTo(hdc, left_wheel_center_x + r * cos(SpinPhase - 1.57), left_wheel_center_y - r * sin(SpinPhase - 1.57));

	MoveToEx(hdc, right_wheel_center_x, right_wheel_center_y, NULL);  // Перемещаем перо к центру колеса
	LineTo(hdc, right_wheel_center_x + r * cos(SpinPhase), right_wheel_center_y - r * sin(SpinPhase));
	MoveToEx(hdc, right_wheel_center_x, right_wheel_center_y, NULL);  // Перемещаем перо к центру колеса
	LineTo(hdc, right_wheel_center_x + r * cos(SpinPhase + 1.57), right_wheel_center_y - r * sin(SpinPhase + 1.57));
	MoveToEx(hdc, right_wheel_center_x, right_wheel_center_y, NULL);  // Перемещаем перо к центру колеса
	LineTo(hdc, right_wheel_center_x + r * cos(SpinPhase + 3.14), right_wheel_center_y - r * sin(SpinPhase - 3.14));
	MoveToEx(hdc, right_wheel_center_x, right_wheel_center_y, NULL);  // Перемещаем перо к центру колеса
	LineTo(hdc, right_wheel_center_x + r * cos(SpinPhase - 1.57), right_wheel_center_y - r * sin(SpinPhase - 1.57));

}  // Конец блока "Рисовать велосипед с анимацией вращения колес"


// ---------------------------------------------------------------------
// ----------------- 7 Реализация методов класса Man -------------------
// ---------------------------------------------------------------------


// Констуктор человека
Man::Man(int InitX, int InitY, int InitSize, std::string InitName) : Point(InitX, InitY) {

	name = InitName;  // Установим имя
	IsAlive = true;  // По началу человек жив
	size = InitSize;  // Начальный размер

} // Конец блока "Констуктор человека"


// Деструктор человека 
Man::~Man() {


	// Пустой блок


} // Конец блока "Деструктор человека" 


// Узнать, жив ли человек
bool Man::GetIsAlive() {


	return IsAlive;  // Возвращает статус жизни человека


}  // Конец блока "Узнать, жив ли человек"


// Убить или воскресить человека
void Man::SetIsAlive(bool NewIsAlive) {


	bool was_visible = Visible;  // Дан видимый или скрытый человек

	GetHidden();  // В любом случае человек не должен быть виден при изменении его параметра

	IsAlive = NewIsAlive;  // Устанавливаем статус жизни человека

	if (was_visible) Show();  // Показываем человека, если изначально он был виден


}  // Конец блока "Убить или воскресить человека"


// Получение размера человека
int Man::GetSize() {


	return size; // Возвращаем размер человека


} // Конец блока "Получение размера человека"


// Установка значения размера человека
void Man::SetSize(int NewSize) { // Установка значения поля Size


	bool was_visible = Visible;  // Дан видимый или скрытый велосипед

	GetHidden();  // В любом случае велосипед не должен быть виден при изменении его параметра

	size = NewSize;  // Устанавливаем новый размер человека

	if (size < gl_min_bike_size) size = gl_min_bike_size;  // Не должны перейти нижнюю границу размера человека

	if (size > gl_max_bike_size) size = gl_max_bike_size;  // Не должны перейти верхнюю границу размера человека

	if (was_visible) Show();  // Показываем велосипед, если изначально он был виден


} // SetSize()


// Получить имя
string Man::GetName() {

	return name;

}


// Рисуем человека
void Man::Draw() {


	COLORREF colour;  // Цвет человека


	// Устанавливаем цвет:
	if (Visible) colour = colour_default_base2;
	else colour = colour_default_backgroung;


	// Создаем кисть:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, colour);

	SelectObject(hdc, hPen1); // Делаем кисть активной

	if (IsAlive) {  // Если жив, рисуем человечка

		// -- ПАРАМЕТРЫ Человека --
		// 
		// () Весь человек лежит в прямоугольнике от (X,Y) до (X + size, Y + 2.87*size)
		// () Пах человека - (X + size/2, Y + 2 * size)
		// () Плечи человека - (X + size/2, Y + size)
		// () Диаметр головы - size
		// () Длина рук и ног - size


		// Зададим координаты:

		int groin_x, groin_y;  // Пах

		int shoulders_x, shoulders_y;  // Плечи


		// Зададим размеры:

		int l = size;  // Длина конечностей

		int d = size;  // Диаметр головы

		// Рассчитаем координаты:

		groin_x = X + l / 2;
		groin_y = Y + 2 * l;

		shoulders_x = X + l / 2;
		shoulders_y = Y + l;

		// --------- Рисуем человека ----------

		MoveToEx(hdc, groin_x, groin_y, NULL);  // Перемещаем перо в пах

		LineTo(hdc, groin_x - l / 2, groin_y + (l / 2) * 1.7);  // Левая нога

		MoveToEx(hdc, groin_x, groin_y, NULL);  // Перемещаем перо в пах

		LineTo(hdc, groin_x + l / 2, groin_y + (l / 2) * 1.7);  // Правая нога

		MoveToEx(hdc, groin_x, groin_y, NULL);  // Перемещаем перо в пах

		LineTo(hdc, shoulders_x, shoulders_y);  // Живот

		LineTo(hdc, shoulders_x - l / 2, shoulders_y + (l / 2) * 1.7);  // Левая рука

		MoveToEx(hdc, shoulders_x, shoulders_y, NULL);  // Перемещаем перо к плечам

		LineTo(hdc, shoulders_x + l / 2, shoulders_y + (l / 2) * 1.7);  // Правая рука

		Ellipse(hdc, shoulders_x - l / 2, shoulders_y - l, shoulders_x + l / 2, shoulders_y);

	}
	else {  // Если человек не жив, рисуем могилочку

		// -- ПАРАМЕТРЫ могилы --
		// 
		// () Вся могилка лежит в прямоугольнике от (X,Y) до (X + size, Y + 2.87*size)
		// () Высота основной части - 1.5*size
		// () Полная высота - 2*size
		// () Крест - 0.87*size
		// () Ширина верхней части - 0.5*size

		int h = 1.5 * size;
		int H = 2 * size;
		int HH = 2.87 * size;
		int w = size;

		// Основная часть
		MoveToEx(hdc, X, Y + HH - h, NULL);
		LineTo(hdc, X, Y + HH);
		LineTo(hdc, X + w, Y + HH);
		LineTo(hdc, X + w, Y + HH - h);
		LineTo(hdc, X + 0.75 * w, Y + HH - H);
		LineTo(hdc, X + 0.25 * w, Y + HH - H);
		LineTo(hdc, X, Y + HH - h);

		// Крест
		MoveToEx(hdc, X + 0.5 * w, Y + HH - H, NULL);
		LineTo(hdc, X + 0.5 * w, Y);
		MoveToEx(hdc, X + 0.3 * w, Y + (HH - H) / 3, NULL);
		LineTo(hdc, X + 0.7 * w, Y + (HH - H) / 3);
	}


} // Конец блока "Рисуем человека"


// ---------------------------------------------------------------------
// ----------------- 8 Реализация методов класса Male ------------------
// ---------------------------------------------------------------------


// Констуктор мужчины
Male::Male(int InitX, int InitY, int InitSize, std::string InitName) : Man(InitX, InitY, InitSize, InitName) {


	// Пустое тело


} // Конец блока "Конструктор мужчины"


// Деструктор мужчины 
Male::~Male() {


	// Пустое тело


} // Конец блока "Деструктор мужчины"


// Рисуем мужчину
void Male::Draw() {


	COLORREF colour;  // Цвет человека


	// Устанавливаем цвет:
	if (Visible) colour = colour_default_base2;
	else colour = colour_default_backgroung;


	// Создаем кисть:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, colour);

	SelectObject(hdc, hPen1); // Делаем кисть активной

	if (IsAlive) {  // Если жив, рисуем человечка

		// -- ПАРАМЕТРЫ Человека --
		// 
		// () Весь человек лежит в прямоугольнике от (X,Y) до (X + size, Y + 2.87*size)
		// () Пах человека - (X + size/2, Y + 2 * size)
		// () Плечи человека - (X + size/2, Y + size)
		// () Диаметр головы - size
		// () Длина рук и ног - size


		// Зададим координаты:

		int groin_x, groin_y;  // Пах

		int shoulders_x, shoulders_y;  // Плечи


		// Зададим размеры:

		int l = size;  // Длина конечностей

		int d = size;  // Диаметр головы

		// Рассчитаем координаты:

		groin_x = X + l / 2;
		groin_y = Y + 2 * l;

		shoulders_x = X + l / 2;
		shoulders_y = Y + l;

		// --------- Рисуем человека ----------

		MoveToEx(hdc, groin_x, groin_y, NULL);  // Перемещаем перо в пах

		LineTo(hdc, groin_x - l / 2, groin_y + (l / 2) * 1.7);  // Левая нога

		MoveToEx(hdc, groin_x, groin_y, NULL);  // Перемещаем перо в пах

		LineTo(hdc, groin_x + l / 2, groin_y + (l / 2) * 1.7);  // Правая нога

		MoveToEx(hdc, groin_x, groin_y, NULL);  // Перемещаем перо в пах

		LineTo(hdc, shoulders_x, shoulders_y);  // Живот

		LineTo(hdc, shoulders_x - l / 2, shoulders_y + (l / 2) * 1.7);  // Левая рука

		MoveToEx(hdc, shoulders_x, shoulders_y, NULL);  // Перемещаем перо к плечам

		LineTo(hdc, shoulders_x + l / 2, shoulders_y + (l / 2) * 1.7);  // Правая рука

		Ellipse(hdc, shoulders_x - l / 2, shoulders_y - l, shoulders_x + l / 2, shoulders_y);

		// --------- Рисуем мужские черты ---------

		int beard_size = size / 4;  // Размер бороды

		// Рисуем бороду
		Pie(hdc, shoulders_x - beard_size, shoulders_y - beard_size, shoulders_x + beard_size, shoulders_y + beard_size, shoulders_x - beard_size, shoulders_y - beard_size, shoulders_x + beard_size, shoulders_y - beard_size);

		// Рисуем грустное лицо  // Ее размер пусть зависит от размера бороды
		Arc(hdc, shoulders_x - beard_size, shoulders_y - 2 * beard_size, shoulders_x + beard_size, shoulders_y + 2 * beard_size, shoulders_x + beard_size, shoulders_y - beard_size, shoulders_x - beard_size, shoulders_y - beard_size);

	}
	else {  // Если человек не жив, рисуем могилочку

		// -- ПАРАМЕТРЫ могилы --
		// 
		// () Вся могилка лежит в прямоугольнике от (X,Y) до (X + size, Y + 2.87*size)
		// () Высота основной части - 1.5*size
		// () Полная высота - 2*size
		// () Крест - 0.87*size
		// () Ширина верхней части - 0.5*size

		int h = 1.5 * size;
		int H = 2 * size;
		int HH = 2.87 * size;
		int w = size;

		// Основная часть
		MoveToEx(hdc, X, Y + HH - h, NULL);
		LineTo(hdc, X, Y + HH);
		LineTo(hdc, X + w, Y + HH);
		LineTo(hdc, X + w, Y + HH - h);
		LineTo(hdc, X + 0.75 * w, Y + HH - H);
		LineTo(hdc, X + 0.25 * w, Y + HH - H);
		LineTo(hdc, X, Y + HH - h);

		// Крест
		MoveToEx(hdc, X + 0.5 * w, Y + HH - H, NULL);
		LineTo(hdc, X + 0.5 * w, Y);
		MoveToEx(hdc, X + 0.3 * w, Y + (HH - H) / 3, NULL);
		LineTo(hdc, X + 0.7 * w, Y + (HH - H) / 3);
	}


}  // Конец блока "Рисуем мужчину"


// -----------------------------------------------------------------------
// ----------------- 9 Реализация методов класса Female ------------------
// -----------------------------------------------------------------------


// Констуктор женщины
Female::Female(int InitX, int InitY, int InitSize, std::string InitName) : Man(InitX, InitY, InitSize, InitName) {


	// Пустое тело


} // Конец блока "Конструктор женщины"  


// Деструктор женщины
Female::~Female() {


	// Пустое тело


} // Конец блока "Деструктор женщины" 


// Рисуем женщину
void Female::Draw() {



	COLORREF colour;  // Цвет человека


	// Устанавливаем цвет:
	if (Visible) colour = colour_default_base2;
	else colour = colour_default_backgroung;


	// Создаем кисть:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, colour);

	SelectObject(hdc, hPen1); // Делаем кисть активной

	if (IsAlive) {  // Если жив, рисуем человечка

		// -- ПАРАМЕТРЫ Человека --
		// 
		// () Весь человек лежит в прямоугольнике от (X,Y) до (X + size, Y + 2.87*size)
		// () Пах человека - (X + size/2, Y + 2 * size)
		// () Плечи человека - (X + size/2, Y + size)
		// () Диаметр головы - size
		// () Длина рук и ног - size


		// Зададим координаты:

		int groin_x, groin_y;  // Пах

		int shoulders_x, shoulders_y;  // Плечи


		// Зададим размеры:

		int l = size;  // Длина конечностей

		int d = size;  // Диаметр головы

		// Рассчитаем координаты:

		groin_x = X + l / 2;
		groin_y = Y + 2 * l;

		shoulders_x = X + l / 2;
		shoulders_y = Y + l;

		// --------- Рисуем человека ----------

		MoveToEx(hdc, groin_x, groin_y, NULL);  // Перемещаем перо в пах

		LineTo(hdc, groin_x - l / 2, groin_y + (l / 2) * 1.7);  // Левая нога

		MoveToEx(hdc, groin_x, groin_y, NULL);  // Перемещаем перо в пах

		LineTo(hdc, groin_x + l / 2, groin_y + (l / 2) * 1.7);  // Правая нога

		MoveToEx(hdc, groin_x, groin_y, NULL);  // Перемещаем перо в пах

		LineTo(hdc, shoulders_x, shoulders_y);  // Живот

		// --------- Рисуем женские черты ---------

		int breast_size = size / 4;  // Размер топа

		// Рисуем топ

		Ellipse(hdc, shoulders_x - breast_size, shoulders_y + breast_size / 2, shoulders_x + breast_size, shoulders_y + 1.5 * breast_size);

		// ----- Конец Рисуем женские черты -------

		// Левая рука
		Arc(hdc, shoulders_x - l / 2, shoulders_y, shoulders_x + l / 2, shoulders_y + l, shoulders_x, shoulders_y, shoulders_x - l / 2, shoulders_y + (l / 2) * 1.7);

		// Правая рука
		Arc(hdc, shoulders_x - l / 2, shoulders_y, shoulders_x + l / 2, shoulders_y + l, shoulders_x + l / 2, shoulders_y + (l / 2) * 1.7, shoulders_x, shoulders_y);

		// Голова
		Ellipse(hdc, shoulders_x - l / 2, shoulders_y - l, shoulders_x + l / 2, shoulders_y);



	}
	else {  // Если человек не жив, рисуем могилочку

		// -- ПАРАМЕТРЫ могилы --
		// 
		// () Вся могилка лежит в прямоугольнике от (X,Y) до (X + size, Y + 2.87*size)
		// () Высота основной части - 1.5*size
		// () Полная высота - 2*size
		// () Крест - 0.87*size
		// () Ширина верхней части - 0.5*size

		int h = 1.5 * size;
		int H = 2 * size;
		int HH = 2.87 * size;
		int w = size;

		// Основная часть
		MoveToEx(hdc, X, Y + HH - h, NULL);
		LineTo(hdc, X, Y + HH);
		LineTo(hdc, X + w, Y + HH);
		LineTo(hdc, X + w, Y + HH - h);
		LineTo(hdc, X + 0.75 * w, Y + HH - H);
		LineTo(hdc, X + 0.25 * w, Y + HH - H);
		LineTo(hdc, X, Y + HH - h);

		// Крест
		MoveToEx(hdc, X + 0.5 * w, Y + HH - H, NULL);
		LineTo(hdc, X + 0.5 * w, Y);
		MoveToEx(hdc, X + 0.3 * w, Y + (HH - H) / 3, NULL);
		LineTo(hdc, X + 0.7 * w, Y + (HH - H) / 3);
	}



} // Конец блока "Рисуем женщину"


// ------------------------------------------------------------------------
// ----------------- 10 Реализация методов класса Tricycle ----------------
// ------------------------------------------------------------------------


// Конструктор трехколесного велосипеда
Tricycle::Tricycle(int InitX, int InitY, int InitSize, int InitDirection) : Bicycle(InitX, InitY, InitSize, InitDirection)
{


	// Пустое тело


}  // Конец блока "Конструктор трехколесного велосипеда"


 // Деструктор трехколесного велосипеда
Tricycle::~Tricycle() {


	// Пустое тело


} // Конец блока "Деструктор трехколесного велосипеда"


// Рисовать трехколесный велосипед
void Tricycle::Draw() {


	COLORREF colour;  // Цвет велосипеда


	// Устанавливаем цвет:
	if (Visible) colour = colour_default_base;
	else colour = colour_default_backgroung;


	// Создаем кисть:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, colour);

	SelectObject(hdc, hPen1); // Делаем кисть активной


	// -- ПАРАМЕТРЫ ВЕЛОСИПЕДА --
	// 
	// () Весь велосипед лежит в прямоугольнике от (X,Y) до (X + 3*size, Y + 1.5*size)
	// () Конструкционный центр велосипеда: (X + 1.5*size, Y + size)
	// () Диаметр колес - size
	// () Длина перекладин - size
	// () Ширина велосипеда влево и вправо от конструкционного центра - по 1,5 size
	// () Высота велосипеда над конструкционным центром - 1 size
	// () Глубина велосипеда под конструкционным центром - 0,5 size


	// Зададим координаты:

	int center_x, center_y; // Центр велосипеда (конструкционный центр, не геометрический)

	int left_wheel_center_x, left_wheel_center_y,  // Центры колес велосипеда
		right_wheel_center_x, right_wheel_center_y;


	// Зададим размеры:

	int l = size;  // Размер перекладины корпуса

	int r = l * 0.5;  // Радиус колес

	int wheel_cos = r / sqrt(pow((l * 1.7 / 2), 2) + pow(2, r));  // Косинус между горизонтом и перекладиной от колеса к верхней части корпуса

	// Рассчитаем координаты:

	center_x = X + 1.5 * l;
	center_y = Y + l;

	left_wheel_center_x = center_x - l;
	left_wheel_center_y = center_y;

	right_wheel_center_x = center_x + l;
	right_wheel_center_y = center_y;

	// --------- Рисуем корпус велосипеда ----------

	MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо в конструкционный центр

	// Основной треугольник корпуса:
	LineTo(hdc, center_x + l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x - l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x, center_y);

	// Если велосипед едет влево:
	if (direction == 0) {

		MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо в конструкционный центр

		LineTo(hdc, center_x + l - r, center_y);  // К заднему колесу перекладина из центра

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в задний верх велосипеда

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // К заднему колесу перекладина из заднего верха велосипеда

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в передний верх велосипеда

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // К переднему колесу перекладина из переднего верха велосипеда

	} // if

	else {  // Если велосипед едет право:

		MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо в конструкционный центр

		LineTo(hdc, center_x - l + r, center_y);  // К заднему колесу перекладина из центра

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в задний верх велосипеда

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // К заднему колесу перекладина из заднего верха велосипеда

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в передний верх велосипеда

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // К переднему колесу перекладина из переднего верха велосипеда

	}  // else 


	// --------- Рисуем руль велосипеда ----------


	// Если велосипед едет влево:
	if (direction == 0) {

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо к носу велосипеда

		// Непосредственно рисуем руль:
		LineTo(hdc, center_x - l / 2 - l / 8, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 - l / 3, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 + l / 12, center_y - (l / 2) * 1.7 - l / 8);

	} // if

	else {  // Если велосипед едет право:

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо к носу велосипеда

		// Непосредственно рисуем руль:
		LineTo(hdc, center_x + l / 2 + l / 8, center_y - l);
		LineTo(hdc, center_x + l / 2 + l / 3, center_y - l);
		LineTo(hdc, center_x + l / 2 - l / 12, center_y - l);

	}  // else 


	// ---------- Рисуем колеса велосипеда ---------

	Ellipse(hdc, (left_wheel_center_x - 0.5 * l), left_wheel_center_y - 0.5 * l, left_wheel_center_x + 0.5 * l, left_wheel_center_y + 0.5 * l);
	Ellipse(hdc, (right_wheel_center_x - 0.5 * l), right_wheel_center_y - 0.5 * l, right_wheel_center_x + 0.5 * l, right_wheel_center_y + 0.5 * l);
	Ellipse(hdc, (center_x - 0.5 * l), center_y - 0.5 * l, center_x + 0.5 * l, center_y + 0.5 * l);

} // Конец блока "Рисовать трехколесный велосипед"



// ------------------------------------------------------------------------------
// ----------------- 11 Реализация методов класса ColouredTricycle --------------
// ------------------------------------------------------------------------------


// Конструктор цветного трехколесного велосипеда
ColouredTricycle::ColouredTricycle(int InitX, int InitY, int InitSize, int InitDirection, COLORREF InitColour) : Tricycle(InitX, InitY, InitSize, InitDirection) {


	colour = InitColour;  // Устанавливаем цвет велосипеда


} // Конец блока "Конструктор цветного трехколесного велосипеда"


// Деструктор цветного трехколесного велосипеда
ColouredTricycle::~ColouredTricycle() {


	// Пустое тело


}  // Конец блока "Деструктор цветного трехколесного велосипеда"


// Получить цвет трехколесного велосипеда
COLORREF ColouredTricycle::GetColour() {


	return colour;  // Возвращаем цвет велосипеда


}  // Конец блока "Получить цвет трехколесного велосипеда"


// Установить новый цвет трехколесного велосипеда
void ColouredTricycle::SetColour(COLORREF NewColour) {

	bool was_visible = Visible;  // Дан видимый или скрытый велосипед

	GetHidden();  // В любом случае велосипед не должен быть виден при изменении его параметра

	colour = NewColour;  // Устанавливаем новый цвет велосипеда

	if (was_visible) Show();  // Показываем велосипед, если изначально он был виден

}  // Конец блока "Установить новый цвет трехколесного велосипеда"


// Рисовать цветной трехколесный велосипед
void ColouredTricycle::Draw() {


	// Реальный цвет велосипеда:
	COLORREF real_colour;

	// Если велосипед скрытый, реальный его цвет - это цвет фона:
	if (!Visible) real_colour = colour_default_backgroung;
	else real_colour = colour;

	// Создаем кисть:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, real_colour);

	SelectObject(hdc, hPen1); // Делаем кисть активной


	// -- ПАРАМЕТРЫ ВЕЛОСИПЕДА --
	// 
	// () Весь велосипед лежит в прямоугольнике от (X,Y) до (X + 3*size, Y + 1.5*size)
	// () Конструкционный центр велосипеда: (X + 1.5*size, Y + size)
	// () Диаметр колес - size
	// () Длина перекладин - size
	// () Ширина велосипеда влево и вправо от конструкционного центра - по 1,5 size
	// () Высота велосипеда над конструкционным центром - 1 size
	// () Глубина велосипеда под конструкционным центром - 0,5 size


	// Зададим координаты:

	int center_x, center_y; // Центр велосипеда (конструкционный центр, не геометрический)

	int left_wheel_center_x, left_wheel_center_y,  // Центры колес велосипеда
		right_wheel_center_x, right_wheel_center_y;


	// Зададим размеры:

	int l = size;  // Размер перекладины корпуса

	int r = l * 0.5;  // Радиус колес

	int wheel_cos = r / sqrt(pow((l * 1.7 / 2), 2) + pow(2, r));  // Косинус между горизонтом и перекладиной от колеса к верхней части корпуса

	// Рассчитаем координаты:

	center_x = X + 1.5 * l;
	center_y = Y + l;

	left_wheel_center_x = center_x - l;
	left_wheel_center_y = center_y;

	right_wheel_center_x = center_x + l;
	right_wheel_center_y = center_y;

	// --------- Рисуем корпус велосипеда ----------

	MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо в конструкционный центр

	// Основной треугольник корпуса:
	LineTo(hdc, center_x + l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x - l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x, center_y);

	// Если велосипед едет влево:
	if (direction == 0) {

		MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо в конструкционный центр

		LineTo(hdc, center_x + l - r, center_y);  // К заднему колесу перекладина из центра

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в задний верх велосипеда

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // К заднему колесу перекладина из заднего верха велосипеда

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в передний верх велосипеда

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // К переднему колесу перекладина из переднего верха велосипеда

	} // if

	else {  // Если велосипед едет право:

		MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо в конструкционный центр

		LineTo(hdc, center_x - l + r, center_y);  // К заднему колесу перекладина из центра

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в задний верх велосипеда

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // К заднему колесу перекладина из заднего верха велосипеда

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в передний верх велосипеда

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // К переднему колесу перекладина из переднего верха велосипеда

	}  // else 


	// --------- Рисуем руль велосипеда ----------


	// Если велосипед едет влево:
	if (direction == 0) {

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо к носу велосипеда

		// Непосредственно рисуем руль:
		LineTo(hdc, center_x - l / 2 - l / 8, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 - l / 3, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 + l / 12, center_y - (l / 2) * 1.7 - l / 8);

	} // if

	else {  // Если велосипед едет право:

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо к носу велосипеда

		// Непосредственно рисуем руль:
		LineTo(hdc, center_x + l / 2 + l / 8, center_y - l);
		LineTo(hdc, center_x + l / 2 + l / 3, center_y - l);
		LineTo(hdc, center_x + l / 2 - l / 12, center_y - l);

	}  // else 


	// ---------- Рисуем колеса велосипеда ---------

	Ellipse(hdc, (left_wheel_center_x - 0.5 * l), left_wheel_center_y - 0.5 * l, left_wheel_center_x + 0.5 * l, left_wheel_center_y + 0.5 * l);
	Ellipse(hdc, (right_wheel_center_x - 0.5 * l), right_wheel_center_y - 0.5 * l, right_wheel_center_x + 0.5 * l, right_wheel_center_y + 0.5 * l);
	Ellipse(hdc, (center_x - 0.5 * l), center_y - 0.5 * l, center_x + 0.5 * l, center_y + 0.5 * l);

} // Конец блока "Рисовать цветной трехколесный велосипед"



// -----------------------------------------------------------------------------------
// ----------------- 12 Реализация методов класса TricycleWithSpinningWheels ---------
// -----------------------------------------------------------------------------------


// Конструктор трехколесного велосипеда с анимацией вращения колес при движении
TricycleWithSpinningWheels::TricycleWithSpinningWheels(int InitX, int InitY, int InitSize, int InitDirection, COLORREF InitColour) : ColouredTricycle(InitX, InitY, InitSize, InitDirection, InitColour) {


	SpinPhase = 0;  // Устанавливаем начальную фазу вращения колес


}  // Конец блока "Конструктор трехколесного велосипеда с анимацией вращения колес при движениии"


// Деструктор трехколесного велосипеда с анимацией вращения колес при движении
TricycleWithSpinningWheels::~TricycleWithSpinningWheels() {


	// Пустое тело


}  // Конец блока "Деструктор трехколесного велосипеда с анимацией вращения колес при движении"


// Получить фазу вращения колес
int TricycleWithSpinningWheels::GetSpinPhase() {


	return SpinPhase;


}  // Конец блока "Получить фазу вращения колес"


// Установить фазу вращения колес
void TricycleWithSpinningWheels::SetSpinPhase(float NewSpinPhase) {


	bool was_visible = Visible;  // Дан видимый или скрытый велосипед

	GetHidden();  // В любом случае велосипед не должен быть виден при изменении его параметра

	SpinPhase = NewSpinPhase;  // Устанавливаем новую фазу вращения колес

	if (SpinPhase > 6.28) SpinPhase = 0;  // Границы фазы

	if (was_visible) Show();  // Показываем велосипед, если изначально он был виден


} // Конец блока "Установить фазу вращения колес"


// Что происходит с трехколесным велосипедом, когда он едет в новую точку
void TricycleWithSpinningWheels::WhenRide(int NewX, int NewY) {

	// Если велосипед поедет в сторону, противоположную его текущему направлению, то велосипед должен повернуться:
	if ((NewX > X && direction == 0) || (NewX < X && direction == 1)) {

		Rotate();  // Поворот велосипеда

	}  // if

	// Путь пройденный велосипедом при движении:
	float L = sqrt(
		pow((NewX - X), 2) +
		pow((NewY - Y), 2));

	// Радиус колес велосипеда:
	float R = size / 2;

	// Если велосипед едет вправо:
	if (direction == 1) {

		// Устанавливаем новую фазу вращения колеса (расчет геометрический, будто велосипед правда проехал L):
		SetSpinPhase(SpinPhase - L / R);

	}
	else {  // Велосипед едет влево

		// Устанавливаем новую фазу вращения колеса (расчет геометрический, будто велосипед правда проехал L):
		SetSpinPhase(SpinPhase + L / R);

	}

}  // Конец блока "Что происходит с трехколесным велосипедом, когда он едет в новую точку"


// Рисовать трехколесный велосипед с анимацией вращения колес
void TricycleWithSpinningWheels::Draw() {


	// Реальный цвет велосипеда:
	COLORREF real_colour;

	// Если велосипед скрытый, реальный его цвет - это цвет фона:
	if (!Visible) real_colour = colour_default_backgroung;
	else real_colour = colour;

	// Создаем кисть:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, real_colour);

	SelectObject(hdc, hPen1); // Делаем кисть активной


	// -- ПАРАМЕТРЫ ВЕЛОСИПЕДА --
	// 
	// () Весь велосипед лежит в прямоугольнике от (X,Y) до (X + 3*size, Y + 1.5*size)
	// () Конструкционный центр велосипеда: (X + 1.5*size, Y + size)
	// () Диаметр колес - size
	// () Длина перекладин - size
	// () Ширина велосипеда влево и вправо от конструкционного центра - по 1,5 size
	// () Высота велосипеда над конструкционным центром - 1 size
	// () Глубина велосипеда под конструкционным центром - 0,5 size


	// Зададим координаты:

	int center_x, center_y; // Центр велосипеда (конструкционный центр, не геометрический)

	int left_wheel_center_x, left_wheel_center_y,  // Центры колес велосипеда
		right_wheel_center_x, right_wheel_center_y;


	// Зададим размеры:

	int l = size;  // Размер перекладины корпуса

	int r = l * 0.5;  // Радиус колес

	int wheel_cos = r / sqrt(pow((l * 1.7 / 2), 2) + pow(2, r));  // Косинус между горизонтом и перекладиной от колеса к верхней части корпуса

	// Рассчитаем координаты:

	center_x = X + 1.5 * l;
	center_y = Y + l;

	left_wheel_center_x = center_x - l;
	left_wheel_center_y = center_y;

	right_wheel_center_x = center_x + l;
	right_wheel_center_y = center_y;

	// --------- Рисуем корпус велосипеда ----------

	MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо в конструкционный центр

	// Основной треугольник корпуса:
	LineTo(hdc, center_x + l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x - l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x, center_y);

	// Если велосипед едет влево:
	if (direction == 0) {

		MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо в конструкционный центр

		LineTo(hdc, center_x + l - r, center_y);  // К заднему колесу перекладина из центра

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в задний верх велосипеда

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // К заднему колесу перекладина из заднего верха велосипеда

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в передний верх велосипеда

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // К переднему колесу перекладина из переднего верха велосипеда

	} // if

	else {  // Если велосипед едет право:

		MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо в конструкционный центр

		LineTo(hdc, center_x - l + r, center_y);  // К заднему колесу перекладина из центра

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в задний верх велосипеда

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // К заднему колесу перекладина из заднего верха велосипеда

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо в передний верх велосипеда

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // К переднему колесу перекладина из переднего верха велосипеда

	}  // else 


	// --------- Рисуем руль велосипеда ----------


	// Если велосипед едет влево:
	if (direction == 0) {

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо к носу велосипеда

		// Непосредственно рисуем руль:
		LineTo(hdc, center_x - l / 2 - l / 8, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 - l / 3, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 + l / 12, center_y - (l / 2) * 1.7 - l / 8);

	} // if

	else {  // Если велосипед едет право:

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // Перемещаем перо к носу велосипеда

		// Непосредственно рисуем руль:
		LineTo(hdc, center_x + l / 2 + l / 8, center_y - l);
		LineTo(hdc, center_x + l / 2 + l / 3, center_y - l);
		LineTo(hdc, center_x + l / 2 - l / 12, center_y - l);

	}  // else 


	// ---------- Рисуем колеса велосипеда ---------

	Ellipse(hdc, (left_wheel_center_x - 0.5 * l), left_wheel_center_y - 0.5 * l, left_wheel_center_x + 0.5 * l, left_wheel_center_y + 0.5 * l);
	Ellipse(hdc, (right_wheel_center_x - 0.5 * l), right_wheel_center_y - 0.5 * l, right_wheel_center_x + 0.5 * l, right_wheel_center_y + 0.5 * l);
	Ellipse(hdc, (center_x - 0.5 * l), center_y - 0.5 * l, center_x + 0.5 * l, center_y + 0.5 * l);

	// -------------- Рисуем спицы колес -----------

	// 1-ое колесо
	MoveToEx(hdc, left_wheel_center_x, left_wheel_center_y, NULL);  // Перемещаем перо к центру колеса
	LineTo(hdc, left_wheel_center_x + r * cos(SpinPhase), left_wheel_center_y - r * sin(SpinPhase));
	MoveToEx(hdc, left_wheel_center_x, left_wheel_center_y, NULL);  // Перемещаем перо к центру колеса
	LineTo(hdc, left_wheel_center_x + r * cos(SpinPhase + 1.57), left_wheel_center_y - r * sin(SpinPhase + 1.57));
	MoveToEx(hdc, left_wheel_center_x, left_wheel_center_y, NULL);  // Перемещаем перо к центру колеса
	LineTo(hdc, left_wheel_center_x + r * cos(SpinPhase + 3.14), left_wheel_center_y - r * sin(SpinPhase - 3.14));
	MoveToEx(hdc, left_wheel_center_x, left_wheel_center_y, NULL);  // Перемещаем перо к центру колеса
	LineTo(hdc, left_wheel_center_x + r * cos(SpinPhase - 1.57), left_wheel_center_y - r * sin(SpinPhase - 1.57));

	// 2-е колесо
	MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо к центру колеса
	LineTo(hdc, center_x + r * cos(SpinPhase), left_wheel_center_y - r * sin(SpinPhase));
	MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо к центру колеса
	LineTo(hdc, center_x + r * cos(SpinPhase + 1.57), left_wheel_center_y - r * sin(SpinPhase + 1.57));
	MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо к центру колеса
	LineTo(hdc, center_x + r * cos(SpinPhase + 3.14), left_wheel_center_y - r * sin(SpinPhase - 3.14));
	MoveToEx(hdc, center_x, center_y, NULL);  // Перемещаем перо к центру колеса
	LineTo(hdc, center_x + r * cos(SpinPhase - 1.57), left_wheel_center_y - r * sin(SpinPhase - 1.57));

	// 3-е колесо
	MoveToEx(hdc, right_wheel_center_x, right_wheel_center_y, NULL);  // Перемещаем перо к центру колеса
	LineTo(hdc, right_wheel_center_x + r * cos(SpinPhase), right_wheel_center_y - r * sin(SpinPhase));
	MoveToEx(hdc, right_wheel_center_x, right_wheel_center_y, NULL);  // Перемещаем перо к центру колеса
	LineTo(hdc, right_wheel_center_x + r * cos(SpinPhase + 1.57), right_wheel_center_y - r * sin(SpinPhase + 1.57));
	MoveToEx(hdc, right_wheel_center_x, right_wheel_center_y, NULL);  // Перемещаем перо к центру колеса
	LineTo(hdc, right_wheel_center_x + r * cos(SpinPhase + 3.14), right_wheel_center_y - r * sin(SpinPhase - 3.14));
	MoveToEx(hdc, right_wheel_center_x, right_wheel_center_y, NULL);  // Перемещаем перо к центру колеса
	LineTo(hdc, right_wheel_center_x + r * cos(SpinPhase - 1.57), right_wheel_center_y - r * sin(SpinPhase - 1.57));

} // Конец блока "Рисовать трехколесный велосипед с анимацией вращения колес"



// -----------------------------------------------------------------------------------
// --------------------------- 13 Реализация методов класса Button -------------------
// ------------------------------------------------------------------------------------


// Конструктор кнопки
Button::Button(int InitX, int InitY, int InitRadius, COLORREF InitColour) : Point(InitX, InitY) {

	colour = InitColour;
	Visible = true;
	IsActivated = false;
	radius = InitRadius;  // Устанавливаем радиус
	Draw();


} // end of Конструктор кнопки

Button::~Button() {}  // Деструктор кнопки

// Рисовать кнопку
void Button::Draw() {

	// Цвет кнопки:
	COLORREF real_colour;

	// Устанавливаем цвет кнопки:
	if (Visible) real_colour = colour;
	else colour = colour_default_backgroung;

	// Создаем кисть:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, real_colour);

	SelectObject(hdc, hPen1); // Делаем кисть активной

	// Рисуем кнопку:

	Ellipse(hdc, X, Y, X + radius, Y + radius);

}

// Получить размеры
int Button::GetSize() {

	return radius;

}


// Узнать активирована ли кнопка
bool Button::GetIsActivated() {

	return IsActivated;

}


// Установить активированность кнопки
void Button::SetIsActivated(bool NewIsActivated) {

	IsActivated = NewIsActivated;

}



// -----------------------------------------------------------------------------------
// ------------------------ 13 Реализация методов класса Tombstone -------------------
// -----------------------------------------------------------------------------------



// Констуктор могилы
Tombstone::Tombstone(int InitX, int InitY, int InitSize, std::string InitName) : Point(InitX, InitY) {

	size = InitSize;
	name = InitName;

}

// Констуктор могилы
Tombstone::Tombstone(Man man) : Point(man.GetX(), man.GetY()) {

	size = man.GetSize();
	name = man.GetName();
	Visible = man.GetVisible();

}

// Деструктор могилы 
Tombstone::~Tombstone() {}

// Получение размера могилы
int Tombstone::GetSize() {

	return size;

}


// Установка значения размера могилы
void Tombstone::SetSize(int NewSize) {

	size = NewSize;

}


// Рисуем могилу
void Tombstone::Draw() {


	COLORREF colour;  // Цвет человека


	// Устанавливаем цвет:
	if (Visible) colour = colour_default_base2;
	else colour = colour_default_backgroung;


	// Создаем кисть:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, colour);

	SelectObject(hdc, hPen1); // Делаем кисть активной

	// -- ПАРАМЕТРЫ могилы --
	// 
	// () Вся могилка лежит в прямоугольнике от (X,Y) до (X + size, Y + 2.87*size)
	// () Высота основной части - 1.5*size
	// () Полная высота - 2*size
	// () Крест - 0.87*size
	// () Ширина верхней части - 0.5*size

	int h = 1.5 * size;
	int H = 2 * size;
	int HH = 2.87 * size;
	int w = size;

	// Основная часть
	MoveToEx(hdc, X, Y + HH - h, NULL);
	LineTo(hdc, X, Y + HH);
	LineTo(hdc, X + w, Y + HH);
	LineTo(hdc, X + w, Y + HH - h);
	LineTo(hdc, X + 0.75 * w, Y + HH - H);
	LineTo(hdc, X + 0.25 * w, Y + HH - H);
	LineTo(hdc, X, Y + HH - h);

	// Крест
	MoveToEx(hdc, X + 0.5 * w, Y + HH - H, NULL);
	LineTo(hdc, X + 0.5 * w, Y);
	MoveToEx(hdc, X + 0.3 * w, Y + (HH - H) / 3, NULL);
	LineTo(hdc, X + 0.7 * w, Y + (HH - H) / 3);

}