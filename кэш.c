
/* установить точку
   -------------------------------------------
   xPosition : позици€ по оси х = 0 ... 111
   yPosition : позици€ по оси у = 0 ... 31
   ------------------------------------------- */

void SetPixel (char xPosition, char yPosition) {
  
  cache [yPosition / 8] [xPosition] |= (1 << (7 - yPosition % 8));  
}


/* инвертировать точку
   ------------------------------------------------------ */

void InvertPixel (char xPosition, char yPosition) {
      
  cache [yPosition / 8] [xPosition] ^= (1 << (yPosition % 8));  
}


/* инвертировать пр€моугольную область видеопам€ти
   ------------------------------------------------------ */

void InvertRect (char xPosition1, char yPosition1, char xPosition2, char yPosition2) {

  char x;
  char y;
  
  xPosition2 ++;
  yPosition2 ++;
  
  for (y = yPosition1; y < yPosition2; y ++) 
  for (x = xPosition1; x < xPosition2; x ++) InvertPixel (x, y); 
}


/* вертикальна€ лини€
   ------------------------------------------------------ */

void VerticalLine (char xPosition, char yPosition, char Count) {

  while (Count > 0) {
  
    SetPixel (xPosition, yPosition);
    Count --;
    yPosition ++;
  }
}


/* горизонтальна€ лини€
   ------------------------------------------------------ */

void HorisontalLine (char xPosition, char yPosition, char Count) {

  while (Count > 0) {
  
    SetPixel (xPosition, yPosition);
    Count --;
    xPosition ++;
  }
}


/* вывод пр€моугольника
   ------------------------------------------------------ */

void FillRect (char xPosition1, char yPosition1, char xPosition2, char yPosition2) {

  char x;
  char y;
  
  xPosition2 ++;
  yPosition2 ++;
  
  for (y = yPosition1; y < yPosition2; y ++) 
  for (x = xPosition1; x < xPosition2; x ++) SetPixel (x, y); 
}


/* градиент
   ------------------------------------------------------ */

void Gradient (char xPosition1, char yPosition1, char xPosition2, char yPosition2) {

  char x;
  char y;
  char a;
  char z;
  
  xPosition2 ++;
  yPosition2 ++;

  if (yPosition1 % 2 == xPosition1 % 2) z = 1; else z = 0;
  
  for (y = yPosition1; y < yPosition2; y ++) {
    a = y % 2;
    for (x = xPosition1; x < xPosition2; x ++) {
       if ((x % 2 == a) && (z == 1)) SetPixel (x, y);
       if ((x % 2 != a) && (z == 0)) SetPixel (x, y);
    }
  }
}

/* |||   ќ ѕ » я ||| */

void ClassGradientToCache (void) {
 
  Gradient (ClassGradient.x1,ClassGradient.y1,ClassGradient.x2,ClassGradient.y2);
}


/* запись фоновои картинки в кэш диспле€
   ------------------------------------- */

void SetGround (unsigned char const * array) { 
  
  char x = 0;  
  char y = 0;
    
  for (y = 0; y < 4; y ++) 
  for (x = 0; x < 112; x ++) 
       cache [y] [x] = array [y*112+x];
}




/* запись картинки в кэш диспле€
   --------------------------------- */

void SetImage (struct imageClassConstructor image) { 
  
  // количество бит дл€ сдвига  
     char Bit = image.y % 8;
     
     
  // начальна€ строка, на которую будет выполнен вывод   
     char LineBegin = image.y / 8; 
     
  // если есть биты сдвига, то добавл€ем строку
     char imageLine = 1;
     if (Bit > 0) imageLine ++;
  
     
  // конечна€ строка, на которую будет выполнен вывод    
     char LineEnd = LineBegin + imageLine; 
     // конечна€ координата отрисовки не должна быть больше 4, 
     // т.к. высота диспле€ 4 * 8 бит точек
         if (LineEnd > 4) LineEnd = 4;  
     
  // конечна€ X координата рисавани€ рисунка 
     char WidthEnd = image.x + image.Width;
     // конечна€ координата отрисовки не должна быть больше 112, 
     // т.к. ширина диспле€ 112 точки
         if (WidthEnd > 112) WidthEnd = 112;  
         
 
  char x;  
  char Line;
  
  unsigned char dat = 0;
  unsigned char dat2 = 0;
      
for (Line = LineBegin; Line < LineEnd; Line ++) {
    
  for (x = image.x; x < WidthEnd; x ++) {
      
    /* вывод без сдвига битов */
    
    if (Bit == 0) {
    
      cache [Line] [x] |= image.array [image.Width * (Line - LineBegin) + (x - image.x)];
    
    }
    else {
    
    /* вывод со сдвигом битов */ 
     
      // если строка перва€
      if (Line == LineBegin) {
    
        dat = image.array [x - image.x];
        dat = dat >> (Bit);
        
      } 
        else 
      
      // если строка последн€€
      if (Line == (LineEnd - 1)) {

         dat = image.array [image.Width * (Line - LineBegin - 1) + (x - image.x)];
         dat = dat << (8 - Bit);
        
      } 
        else {
       
      // остальные строки
         dat = image.array [image.Width * (Line - LineBegin - 1) + (x - image.x)];
         dat = dat << (8 - Bit);
        
         dat2 = image.array [image.Width * (Line - LineBegin) + (x - image.x)];
         dat2 = dat2 >> Bit;
        
         dat |= dat2;
      }
         
      cache [Line] [x] |= dat;
    }
  }  
} 
}


/* font : маленький (ru + en)
   --------------------------------- */

void fontSmall (char * text, char xPosition, char yPosition) { 
  
  unsigned char index = 0;
  unsigned char chr;
  
  unsigned char z;
  unsigned char zx;
  unsigned int zIndex = 0;

  
  while (text [index] != '\0') {
  
  if (text [index] > 191) 
      chr = text [index] - 224; else // русский
      chr = text [index] - 97 + 32; // английский
      
      z = 0;
       zx = 0;
       while ((z < 13) && (zx == 0)) {
         
         if (fontSmallArray [0][chr*13 + z] == 0) zx = z;
         z++;
       }
       if (z == 13) zx = 13;
  
     imageClass.x = xPosition + zIndex;
     imageClass.y = yPosition;
     imageClass.Width = 13;
     imageClass.array = &fontSmallArray [0][chr*13];
     SetImage (imageClass);
     
    zIndex = zIndex + zx;
       zIndex++;  
     index ++;
  }
}


/* font : ru + en
   --------------------------------- */

void font (char * text, char xPosition, char yPosition) { 
  
  unsigned char index = 0;
  unsigned char chr;
  
  unsigned char z;
  unsigned char zx;
  unsigned int zIndex = 0;

  
  while (text [index] != '\0') {
  
  if (text [index] > 191) 
      chr = text [index] - 224; else // русский
      chr = text [index] - 97 + 32; // английский
      
      z = 0;
       zx = 0;
       while ((z < 14) && (zx == 0)) {
         
         if (fontArray [0][chr*14 + z] == 0) zx = z;
         z++;
       }
       if (z == 14) zx = 14;
  
     imageClass.x = xPosition + zIndex;
     imageClass.y = yPosition;
     imageClass.Width = 14;
     imageClass.array = &fontArray [0][chr*14];
     SetImage (imageClass);
     
    zIndex = zIndex + zx;
       zIndex++;  
     index ++;
  }
}


/* font : 0...9
   ------------------------------------------------------ */

void fontInteger (char xPosition, char yPosition, int sourse, char count) {
  
  xPosition = xPosition - 5;
  int chr = 0;
  int i = 0;
       
  while ((chr > -1) || (count > 0)) {
    
          chr = sourse % 10;
       sourse = sourse / 10;
        
       imageClass.x = xPosition - i*8;
       imageClass.y = yPosition;
       imageClass.Width = 7;
       imageClass.array = &fontIntegerArray [0][chr*7];
       SetImage (imageClass);
 
       imageClass.x = xPosition - i*8;
       imageClass.y = yPosition + 8;
       imageClass.Width = 7;
       imageClass.array = &fontIntegerArray [1][chr*7];
       SetImage (imageClass);
       
       if (sourse == 0) chr = -1;
       i++;
       count--;
  }
}

/* |||   ќ ѕ » я ||| */

void ClassIntToCache (void) {
 
  fontInteger (ClassInt.x,ClassInt.y,ClassInt.Sourse,ClassInt.Count);
}


/* font : 0...9
   ------------------------------------------------------ */

void fontRadiation (char xPosition, char yPosition, int sourse, char count) {
  
  xPosition = xPosition - 8;
  int chr = 0;
  int i = 0;
       
  while ((chr > -1) || (count > 0)) {
    
          chr = sourse % 10;
       sourse = sourse / 10;
        
       imageClass.x = xPosition - i*12;
       imageClass.y = yPosition;
       imageClass.Width = 9;
       imageClass.array = &fontRadiationArray [0][chr*9];
       SetImage (imageClass);
 
       imageClass.x = xPosition - i*12;
       imageClass.y = yPosition + 8;
       imageClass.Width = 9;
       imageClass.array = &fontRadiationArray [1][chr*9];
       SetImage (imageClass);
       
       if (sourse == 0) chr = -1;
       i++;
       count--;
  }
}

void ClassFontBigCache (void) {

  fontRadiation (ClassFontBig.x, ClassFontBig.y, ClassFontBig.Sourse, ClassFontBig.Count);
}


/* вывод иконки
   ---------------------------------- */

void Icon (char xPosition, char yPosition, char Count) {

       imageClass.x = xPosition;
       imageClass.y = yPosition;
       imageClass.Width = 11;
       imageClass.array = &iconArray [0][Count*11];
       SetImage (imageClass);

       imageClass.x = xPosition;
       imageClass.y = yPosition+8;
       imageClass.Width = 11;
       imageClass.array = &iconArray [1][Count*11];
       SetImage (imageClass);
}