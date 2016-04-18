

/* @ ���� S
   ------------------------------------ */

void on_draw_MenuS (void) {
  
   // ������� ���� �������
     CacheClear ();
 
     // ����� ��������� �������        
        fontInteger (100, 11, GenImpDraw, 4);
        
 // ����� ��� -��� �������
        HorisontalLine (12+8*(MenuS-1), 9, 6);
        HorisontalLine (12+8*(MenuS-1), 22, 6);       
     // ����� ������������
        fontInteger (49, 11, Geiger, 5);
     // ����� 
        if (Lang) {
            fontSmall ("���������", 3, 1);
            fontSmall ("����", 74, 1);
            fontSmall ("�����", 2, 25); 
            fontSmall ("�����", 72, 25); 
            fontSmall ("��", 50, 25); 
            VerticalLine (46, 25, 6);
            VerticalLine (67, 25, 6);
        } 
        else {
            fontSmall ("system", 3, 1);
            fontSmall ("menu", 55, 1);
            fontSmall ("exit", 9, 25);
            fontSmall ("next", 74, 25);
            fontSmall ("ok", 47, 25);
            VerticalLine (43, 25, 6);
            VerticalLine (64, 25, 6);
        }
        InvertRect (0, 24, 111, 31);
        InvertRect (0, 0, 111, 7);
  
}


/* ����� � ����
   ---------------------------------- */

void IconPoint (char Count, char Set) {

  Set --;
  char index;
  
   for (index = 0; index < Count; index ++) 
    if (index == Set) 
        Icon (112 - Count * 7 + index * 7, 2, 5); else 
        Icon (112 - Count * 7 + index * 7, 2, 4);
} 

  
/* @ ���� 2
   ------------------------------------ */

void on_draw_Menu2 (void) {
   
  // ������� ���� �������
     CacheClear ();
     
     
// ***** ������ ��� ������ *****
       // *******************************************************
     
       /* 0: ��������� 
          ----------------------------- */
       
          if (Menu1 == 1) {
            
          // ����� ���������
             if (Lang)
                fontSmall ("���������", 3, 1); else
                fontSmall ("backlight", 3, 1);
             
          // ��������� � �����
             if (Menu2 == 1) {
                Icon (23, 13, 3);  
                IconPoint (2, 1);  
             } else {
                Icon (62, 13, 3);  
                IconPoint (2, 2); 
             }
             
          // ����� ���/��� �������
             if (Menu2 == 2) {
                HorisontalLine (69, 9, 6);
                HorisontalLine (69, 22, 6);
             } else
             if (Menu2 == 3) {
                HorisontalLine (76, 9, 6);
                HorisontalLine (76, 22, 6);
             } 
            
          // ���. - ����.
             if (on_Led_Lcd) 
                Icon (29, 11, 0); else
                Icon (29, 11, 1); 
          
          // �������
             fontInteger (81, 11, Led_Lcd_Percent, 2);

          // ������ ��������
             Icon (86, 12, 2); 
         } 
            else
         
       /* 1: ��������� 
          ----------------------------- */
              
          if (Menu1 == 2) {
            
          // ����� ���������
             if (Lang)
                fontSmall ("���������", 3, 1); else
                fontSmall ("indication", 3, 1);
             
          // ��������� � �����
             if (Menu2 == 1) {
                IconPoint (2, 1);  
                Icon (0, 13, 3); 
             } else {
                IconPoint (2, 2); 
                if (Lang)
                  Icon (60, 13, 3); else
                  Icon (68, 13, 3);
             }
       
          // ���.����. ����
             if (on_Sound) 
                Icon (6, 11, 0); else 
                Icon (6, 11, 1);   
       
          // ���.����. ����
             if (Lang) {
               if (on_Led) 
                  Icon (66, 11, 0); else  
                  Icon (66, 11, 1);  
             }
               else {
                if (on_Led) 
                  Icon (74, 11, 0); else  
                  Icon (74, 11, 1);  
            }
                  
             if (Lang) {
                font ("����", 20, 12);
                font ("����", 80, 12);
             }
               else {
                font ("sound", 20, 12);
                font ("led", 88, 12);
             }
                 
          } 
            else
              
       /* 2: ������� 
          ----------------------------- */
              
          if (Menu1 == 3) {
            
          // ����� ���������
             if (Lang)
                fontSmall ("�������", 3, 1); else
                fontSmall ("alarm", 3, 1);
             
          // ��������� � �����
             if (Menu2 == 1) {
                IconPoint (2, 1); 
                Icon (14, 13, 3); 
             } else {
                IconPoint (2, 2); 
                Icon (49, 13, 3);
             }
       
          // ���.����.
             if (on_alarm) 
                Icon (20, 11, 0); else  
                Icon (20, 11, 1);   
    
          // ����� �������
             fontInteger (76, 11, alarm / 100, 3);
             fontInteger (96, 11, alarm % 100, 2);
             Icon (79, 19, 6); 
       
          // ����� ���/��� �������
             if (Menu2 == 2) {
                HorisontalLine (55+8*0, 9, 6);
                HorisontalLine (55+8*0, 22, 6);
             } else
             if (Menu2 == 3) {
                HorisontalLine (55+8*1, 9, 6);
                HorisontalLine (55+8*1, 22, 6);
             } else
             if (Menu2 == 4) {
                HorisontalLine (55+8*2, 9, 6);
                HorisontalLine (55+8*2, 22, 6);
             } else
             if (Menu2 == 5) {
                HorisontalLine (83+8*0, 9, 6);
                HorisontalLine (83+8*0, 22, 6);
             } else
             if (Menu2 == 6) {
                HorisontalLine (83+8*1, 9, 6);
                HorisontalLine (83+8*1, 22, 6);
             } 
          } 
            else
              
       /* 3: ���� ���� 
          ----------------------------- */
              
          if (Menu1 == 4) {
            
          // ����� ���������
             if (Lang) {
                fontSmall ("����", 3, 1);
                fontSmall ("����", 35, 1);
             }
               else {
                fontSmall ("power", 3, 1);
                fontSmall ("down", 48, 1);
             }
             
          // ��������� � �����
             if (Menu2 == 1) {
                IconPoint (2, 1); 
                Icon (14, 13, 3); 
             } else {
                IconPoint (2, 2); 
                Icon (49, 13, 3);
             }
       
          // ���.����.
             if (on_PowerDownTime) 
                Icon (20, 11, 0); else 
                Icon (20, 11, 1);  
         
          // ����� ���/��� �������
             if (Menu2 == 2) {
                HorisontalLine (55+8*0, 9, 6);
                HorisontalLine (55+8*0, 22, 6);
             } else
             if (Menu2 == 3) {
                HorisontalLine (55+8*1, 9, 6);
                HorisontalLine (55+8*1, 22, 6);
             } else
             if (Menu2 == 4) {
                HorisontalLine (55+8*2, 9, 6);
                HorisontalLine (55+8*2, 22, 6);
             } else
             if (Menu2 == 5) {
                HorisontalLine (55+8*3, 9, 6);
                HorisontalLine (55+8*3, 22, 6);
             } else
             if (Menu2 == 6) {
                HorisontalLine (55+8*4, 9, 6);
                HorisontalLine (55+8*4, 22, 6);
             }       

          // ����� �� ����������
             fontInteger (92, 11, PowerDownTime, 5);
             
          // ���� "�"
             if (Lang)
                 fontSmall ("�", 96, 15); else
                 fontSmall ("s", 96, 15); 
          } 
            else

       /* 4: ���� 
          ----------------------------- */
              
          if (Menu1 == 5) {
        
          // ����� ���������
             if (Lang)
                 fontSmall ("����", 3, 1); else
                 fontSmall ("language", 3, 1);
          
          // �����
             IconPoint (1, 1);
          
          // ���������
             Icon (14, 13, 3); 
       
          // ����� �����
             if (Lang) 
                font ("�������", 20, 12); else
                font ("english", 20, 12);
          } 
            else
              
       /* 5: ���� 
          ----------------------------- */
              
          if (Menu1 == 6) {
  
          // ����� ���������
             if (Lang) 
                 fontSmall ("����", 3, 1); else
                 fontSmall ("dose", 3, 1);
             
          // ��������� � �����
             if (Menu2 == 1) {
                IconPoint (2, 1); 
                Icon (0, 13, 3);
             } else {
                IconPoint (2, 2);
                Icon (65, 13, 3);
             }
       
          // ����������� ����
             fontInteger (59, 11, GetDoseRadiation (), 7);
             
          // �����
             if (Lang) 
                 font ("�����", 71, 12); else
                 font ("reset", 71, 12);
          } 

          if (Lang) {
              fontSmall ("�����", 2, 25); 
              fontSmall ("�����", 72, 25); 
              fontSmall ("��", 50, 25); 
              VerticalLine (46, 25, 6);
              VerticalLine (67, 25, 6);
          } 
          else {
              fontSmall ("exit", 9, 25);
              fontSmall ("next", 74, 25);
              fontSmall ("ok", 47, 25);
              VerticalLine (43, 25, 6);
              VerticalLine (64, 25, 6);
          }
    
          
          
          InvertRect (0, 24, 111, 31);
          InvertRect (0, 0, 111, 7);
}


/* @ ���� 1
   ------------------------------------ */

void on_draw_Menu1 (void) {
  
  // ������� ���� �������
     CacheClear ();
     
     
// ***** ������ ��� ������ *****
       
       Gradient (1+0*19,0,15+0*19,2); 
       Gradient (1+1*19,0,15+1*19,2); 
       Gradient (1+2*19,0,15+2*19,2); 
       Gradient (1+3*19,0,15+3*19,2); 
       Gradient (1+4*19,0,15+4*19,2); 
       Gradient (1+5*19,0,15+5*19,2);
       
       FillRect (1+(Menu1-1)*19,0,15+(Menu1-1)*19,2); 
 
       if (Menu1 == 1) {
          if (Lang)
            font ("���������", 18, 10); 
          else 
            font ("backlight", 18, 10);
       } else
       if (Menu1 == 2) {
          if (Lang)
            font ("���������", 13, 10); else
            font ("indication", 16, 10);
       } else
       if (Menu1 == 3) {
          if (Lang)
            font ("�������", 28, 10); else
            font ("alert", 33, 10);
       } else
       if (Menu1 == 4) {
          if (Lang) {
            font ("����", 16, 10);
            font ("����", 59, 10);
          }
          else {
            font ("power", 7, 10);
            font ("down", 63, 10);
          }
       } else
       if (Menu1 == 5) {
          if (Lang)
            font ("����", 37, 10); else
            font ("language", 20, 10);
       } else
       if (Menu1 == 6) {
         if (Lang)
           font ("����", 39, 10); else
           font ("dose", 39, 10);
       } 
       
        if (Lang) {
            fontSmall ("�����", 2, 25);
            fontSmall ("�����", 72, 25);
            VerticalLine (46, 25, 6);
            VerticalLine (67, 25, 6);
            fontSmall ("��", 50, 25);
        } 
        else {
            fontSmall ("exit", 9, 25);
            fontSmall ("next", 74, 25);
            fontSmall ("ok", 47, 25);
            VerticalLine (43, 25, 6);
            VerticalLine (64, 25, 6);
        }
 
       InvertRect (0, 24, 111, 31);

}


/* @ �������
   ------------------------------------ */

void on_draw_main (void) {
  
  // ������� ��������  
     SetGround (&groundArray [0][0]);
     
  // -------------------------------------------
     
     // ???????????????????
     // ������ ��������
        GetRadiation ();
  // -------------------------------------------
  
  // ����������� ����    
     ClassInt.x = 111;
     ClassInt.y = 22;
     ClassInt.Count = 7;
     ClassInt.Sourse = GetDoseRadiation ();    
     //ClassInt.Sourse = GenImp;
     ClassIntToCache ();

  // ����� ���������
     ClassInt.x = 51;
     ClassInt.y = 3;
     ClassInt.Count = 3;
     ClassInt.Sourse = Rad_time;    
     ClassIntToCache ();
  
  // ���������� �������
     ClassGradient.x1 = 0;
     ClassGradient.y1 = 3 + BattPercent; // 0...27
     ClassGradient.x2 = 2;
     ClassGradient.y2 = 29;
     ClassGradientToCache ();
          
  // ����� �������� ��������
     if (Rad < 1000) {
       
        ClassFontBig.x = 82;
        ClassFontBig.y = 0;
        ClassFontBig.Count = 1;
        ClassFontBig.Sourse = Rad / 100;    
        ClassFontBigCache ();
        
        ClassFontBig.x = 111;
        ClassFontBig.y = 0;
        ClassFontBig.Count = 2;
        ClassFontBig.Sourse = Rad % 100;    
        ClassFontBigCache ();
   
        SetPixel (86, 12);
        SetPixel (86, 13);
        SetPixel (87, 12);
        SetPixel (87, 13);
     } 
        else
          
     if (Rad < 10000) {
       
        ClassFontBig.x = 82;
        ClassFontBig.y = 0;
        ClassFontBig.Count = 2;
        ClassFontBig.Sourse = Rad / 100;    
        ClassFontBigCache ();
        
        ClassFontBig.x = 111;
        ClassFontBig.y = 0;
        ClassFontBig.Count = 2;
        ClassFontBig.Sourse = Rad % 100;    
        ClassFontBigCache ();
        
        SetPixel (86, 12);
        SetPixel (86, 13);
        SetPixel (87, 12);
        SetPixel (87, 13);
     }
        else {
          
        ClassFontBig.x = 94;
        ClassFontBig.y = 0;
        ClassFontBig.Count = 3;
        ClassFontBig.Sourse = Rad / 100;    
        ClassFontBigCache ();
        
        ClassFontBig.x = 111;
        ClassFontBig.y = 0;
        ClassFontBig.Count = 1;
        ClassFontBig.Sourse = Rad % 100 / 10;    
        ClassFontBigCache ();
        
        SetPixel (98, 12);
        SetPixel (98, 13);
        SetPixel (99, 12);
        SetPixel (99, 13);
     }

  // �������� �������
    
     if ((TimeRun < (Rad_time * 2)) && (TimeRun > 0)) {   
     
        short int Time = (Rad_time * 2) - TimeRun;
                  Time = 22 - 22 * Time / (Rad_time * 2); 
        
        HorisontalLine (59 + Time*2, 17, 5);
        HorisontalLine (60 + Time*2, 18, 3);
        HorisontalLine (59 + Time*2, 19, 5);
     }

     
   // ------------------------------
      // ���������
     
     char Index;
     char i;
     short int max = 0;
     char n;
     char begin = Rad_array_cnt ? Rad_array_cnt - 1 : 119 ;
     
     Index = 20;
     n = begin;
     while (Index) {
     
       if (Rad_array [n] > max) max = Rad_array [n];
       Index --;
       if ((n--) == 0) break;
     }

     n = 119;
     while (Index) {
     
       if (Rad_array [n] > max) max = Rad_array [n];
       Index --;
       if ((n --) == 0) break;
     }
    
     max = max / 29;
     Index = 20;
     n = begin;
     while (Index) {
     
       if (max == 0)
         for (i = 0; i < (Rad_array [n] * 2); i ++) SetPixel (4 + Index, 29 - i); else
         for (i = 0; i < (Rad_array [n] / max ); i ++) SetPixel (4 + Index, 29 - i);
       Index --;
       if ((n--) == 0) break;
     }

     n = 119;
     while (Index) {
     
      if (max == 0)
         for (i = 0; i < (Rad_array [n] * 2); i ++) SetPixel (4 + Index, 29 - i); else
         for (i = 0; i < (Rad_array [n] / max ); i ++) SetPixel (4 + Index, 29 - i);
       Index --;
       if ((n --) == 0) break;
     }
     
  // ��������� ���������
     ClassInt.x = 51;
     ClassInt.y = 22;
     ClassInt.Count = 2;
     ClassInt.Sourse = max + 1;    
     ClassIntToCache ();     
}


/* ------------------------------------------------------------------------- */
/* ---  ������� ��������� -------------------------------------------------- */
/* ------------------------------------------------------------------------- */

void BattLowDraw (void) {
 
  // ����� ������
     if (Lang) {
       font ("�������", 26, 4);
       font ("���������", 16, 19);
     }
       else {
       font ("battery", 25, 4);
       font ("low", 42, 19);
     }
     
  // ������ ���� � �������
     lcd_CacheWrite ();
}


/* ------------------------------------------------------------------------- */
/* ---  ����� ������ �� �������  ------------------------------------------- */
/* ------------------------------------------------------------------------- */

void on_draw (void) {

  // ��������� ����� ������ �� �������
     draw = 0;
 
  // ---------------------------------
  
  // @ �������
     if (MenuS) on_draw_MenuS (); else
     if (Menu1 == 0) on_draw_main (); else       
     if (Menu2 == 0) on_draw_Menu1 (); else
                     on_draw_Menu2 ();

  // ---------------------------------
          
  // ������ ���� � �������
     lcd_CacheWrite ();
}