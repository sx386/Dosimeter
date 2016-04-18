
struct imageClassConstructor {
  
   unsigned char const * array;  // ��������� �� ������ ������� �������
   unsigned char x;  // x ���������� ������ ������� : 0 ... 111
   unsigned char y;  // y ���������� ������ ������� : 0 ... 31
   unsigned char Width;  // ������ ������� : ���������� �����
};

struct ClassIntConstructor {
  
   unsigned char x;  // x ���������� ������ ������� : 0 ... 111
   unsigned char y;  // y ���������� ������ ������� : 0 ... 31
   unsigned char Count;  // ���������� ��������� ��������
   unsigned int Sourse;  // ��������� �����
};

struct ClassGradientConstructor {
  
   unsigned char x1;  // x ��������� ���������� ������ : 0 ... 111
   unsigned char y1;  // y ��������� ���������� ������ : 0 ... 31
   unsigned char x2;  // x �������� ���������� ������ : 0 ... 111
   unsigned char y2;  // y �������� ���������� ������ : 0 ... 31
};

struct ClassFontBigConstructor {
  
   unsigned char x;  // x ��������� ���������� ������ : 0 ... 111
   unsigned char y;  // y ��������� ���������� ������ : 0 ... 31
   unsigned char Count;  // ���������� ��������� ��������
   unsigned int Sourse;  // ��������� �����
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