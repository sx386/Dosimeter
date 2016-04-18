
struct imageClassConstructor {
  
   unsigned char const * array;  // указатель на первыи элемент массива
   unsigned char x;  // x координата вывода рисунка : 0 ... 111
   unsigned char y;  // y координата вывода рисунка : 0 ... 31
   unsigned char Width;  // ширина рисунка : количество точек
};

struct ClassIntConstructor {
  
   unsigned char x;  // x координата вывода рисунка : 0 ... 111
   unsigned char y;  // y координата вывода рисунка : 0 ... 31
   unsigned char Count;  // количество выводимых символов
   unsigned int Sourse;  // выводимое число
};

struct ClassGradientConstructor {
  
   unsigned char x1;  // x начальная координата вывода : 0 ... 111
   unsigned char y1;  // y начальная координата вывода : 0 ... 31
   unsigned char x2;  // x конечная координата вывода : 0 ... 111
   unsigned char y2;  // y конечная координата вывода : 0 ... 31
};

struct ClassFontBigConstructor {
  
   unsigned char x;  // x начальная координата вывода : 0 ... 111
   unsigned char y;  // y начальная координата вывода : 0 ... 31
   unsigned char Count;  // количество выводимых символов
   unsigned int Sourse;  // выводимое число
};

struct imageClassConstructor imageClass;
struct ClassIntConstructor ClassInt;
struct ClassGradientConstructor ClassGradient;
struct ClassFontBigConstructor ClassFontBig;

void SetPixel (char xPosition, char yPosition);
void SetImage (struct imageClassConstructor data);
void fontSmall (char * text, char xPosition, char yPosition);
void font (char * text, char xPosition, char yPosition);
void fontInteger (char xPosition, char yPosition, int Sourse, char Count);
void fontRadiation (char xPosition, char yPosition, int Sourse, char Count);
void InvertPixel (char xPosition, char yPosition);
void InvertRect (char xPosition1, char yPosition1, char xPosition2, char yPosition2);
void VerticalLine (char xPosition, char yPosition, char Count);
void HorisontalLine (char xPosition, char yPosition, char Count);
void FillRect (char xPosition1, char yPosition1, char xPosition2, char yPosition2);
void Icon (char xPosition, char yPosition, char Count);
void Gradient (char xPosition1, char yPosition1, char xPosition2, char yPosition2);
void SetGround (unsigned char const * array);