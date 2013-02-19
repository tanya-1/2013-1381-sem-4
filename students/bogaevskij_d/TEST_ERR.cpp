/*       Пример программы на С++
      Содержит описание двух классов
  ( Location: позиция на экране
    Point: отображение точки в графическом режиме )
   и примеры использования функций-членов классов.*/


#include <conio.h>
#include <iostream.h>
using namespace std;

// описание  класса Location: позиция на экране 
class Location {
     private:		// доступ для функций-членов, дружественных
	int X; int Y;   // функций
     public:            // открытый доступ
	Location (int InitX, int InitY); // конструктор
	int GetX();
	int GetY();
 };
// описание  класса Point: отображение точки в графическом режиме 
class Point: public Location { /* класс Point - производный от базового
 класса Location спецификатор public обеспечивает наследование
функций как public и X,Y как protected */
     protected:          // доступ для функций-членов, дружественных
	bool Visible; // функций и в производных классах
     public:
	Point (int InitX, int InitY);  // конструктор
	void Show();			 // сделать точку видимой 
	void Hide();             // сделать точку невидимой
	void Point::PrintPoint();  // вывод координат
	bool IsVisible();     // проверка видимости
	void MoveTo (int NewX, int NewY); // изменить координаты 
};
// определение функций-членов класса Location
Location::Location (int InitX, int InitY)
       { X = InitX; Y = InitY; };
int Location::GetX(void)
       { return X; };
int Location::GetY(void)
       { return Y; };

// определение функций-членов класса Point
Point::Point(int InitX, int InitY):Location ( InitX, InitY)
       { Visible = false; }; /* конструктор Point
      вызывает конструктор Location и помечает точку как невидимую */
void Point::PrintPoint(void)
       { if (Visible)			
		   cout << "\n Координаты точки: X = " << X << ", Y = " << Y << endl;/* вывести точку*/ 
	     else
			 cout << "\n Координаты точки невидимы " << endl;
		   };
void Point::Show(void)
       { Visible = true; /* разрешить вывод координат */ }
void Point::Hide(void)
       { Visible = false; /* запретить вывод координат */ }
bool Point::IsVisible(void)
       { return Visible; };
void Point::MoveTo (int NewX, int NewY) //изменить координаты 


//                  тестовая программа
int main()
{
 
//   пример диалога в текстовом режими

    int a;
    cout << " Привет! \n "
	 << " Введите любое целое число ";
    cin >> a;
    cout << "\n Спасибо за " << a << endl;
    getch();
//

//  работа с точками
    Point APoint;          // создать точки APoint и BPoint
    Point BPoint(100,50);  // с помощью конструктора класса Point
    APoint.PrintPoint();	// вывод APoint
	BPoint.PrintPoint();	// вывод BPoint
	 _getch();               // ждать нажатия клавиши
	BPoint.Show();         // разрешение вывода точки BPoint
	BPoint.PrintPoint();	// вывод BPoint
    _getch();               // ждать нажатия клавиши
    BPoint.MoveTo(300,150); // переместить точку ВPoint
	BPoint.Show();         // разрешение вывода точки APoint
	BPoint.PrintPoint();	// вывод BPoint
    _getch();
    APoint.Hide();         // сделать невидимыми точки
    BPoint.Hide();         // APoint и  BPoint
    _getch();
// конец
   
    return 0;
}
