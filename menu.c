

/* �������� ������ � �������: +1
   ---------------------------------- */

int ChangeChar (int Sourse, char Index) {
  
  char a5 = Sourse / 10000; 
  char a4 = Sourse % 10000 / 1000; 
  char a3 = Sourse % 1000 / 100; 
  char a2 = Sourse % 100 / 10; 
  char a1 = Sourse % 10; 
 
  if (Index == 5) a5 ++; 
  if (Index == 4) a4 ++; 
  if (Index == 3) a3 ++;
  if (Index == 2) a2 ++; 
  if (Index == 1) a1 ++; 
 
  if (a5 == 10) a5 = 0;
  if (a4 == 10) a4 = 0;
  if (a3 == 10) a3 = 0;
  if (a2 == 10) a2 = 0;
  if (a1 == 10) a1 = 0;

  return a5*10000+
         a4*1000+
         a3*100+
         a2*10+
         a1;
} 

void MenuButton2_S (void) {
  
  Geiger = ChangeChar (Geiger, 6 - MenuS);
}

void MenuButton2_Set (void) {
  
       /* 1: ��������� 
          ----------------------------- */
       
          if (Menu1 == 1) {
            
             if (Menu2 == 1) { // ���. ����. 
               
             // ���. ����. ��������� ������� 
                if (on_Led_Lcd) Lcd_Led_off (); else Lcd_Led_on ();
                
             } else
             if (Menu2 == 2) { // ������� : x~
               
             // �������� ������� ���������
                Led_Lcd_Percent = ChangeChar (Led_Lcd_Percent, 2);
                Lcd_Led_Set (false);
                
             } else
             if (Menu2 == 3) { // ������� : ~x
               
             // �������� ������� ���������
                Led_Lcd_Percent = ChangeChar (Led_Lcd_Percent, 1);
                Lcd_Led_Set (false);
             }
          } 
          else
         
       // 2: ��������� 
       //  ----------------------------- 
              
          if (Menu1 == 2) {
            
             if (Menu2 == 1) { // ���. ����. - �������� ���������
                on_Sound ? Led_Sound (none, false) : Led_Sound (none, true);
             } else
             if (Menu2 == 2) { // ���. ����. - �������� ���������
                on_Led ? Led_Sound (false, none) : Led_Sound (true, none);
             } 
          } 
           else
              
       // 3: ����������� 
       //   ----------------------------- 
              
          if (Menu1 == 3) {
           
             if (Menu2 == 1) { // ���. ����. 
                on_alarm = on_alarm ? 0 : 1;
             } else
             if (Menu2 == 2) { // x~~~~
                alarm = ChangeChar (alarm, 5);
             } else
             if (Menu2 == 3) { // ~x~~~
                alarm = ChangeChar (alarm, 4);
             } else
             if (Menu2 == 4) { // ~~x~~
                alarm = ChangeChar (alarm, 3);
             } else
             if (Menu2 == 5) { // ~~~x~
                alarm = ChangeChar (alarm, 2);
             } else
             if (Menu2 == 6) { // ~~~~x
                alarm = ChangeChar (alarm, 1);
             } 
          } 
        //    else
              
       // 3: ���� ���� 
       //   ----------------------------- 
              
          if (Menu1 == 4) {
            
             if (Menu2 == 1) { // ���. ����. 
                on_PowerDownTime = on_PowerDownTime ? 0 : 1;
                if (PowerDownTime < 100) PowerDownTime = 100;
             } else
             if (Menu2 == 2) { // x~~~~
                PowerDownTime = ChangeChar (PowerDownTime, 5);
             } else
             if (Menu2 == 3) { // ~x~~~
                PowerDownTime = ChangeChar (PowerDownTime, 4);
             } else
             if (Menu2 == 4) { // ~~x~~
                PowerDownTime = ChangeChar (PowerDownTime, 3);
             } else
             if (Menu2 == 5) { // ~~~x~
                PowerDownTime = ChangeChar (PowerDownTime, 2);
             } else
             if (Menu2 == 6) { // ~~~~x
                PowerDownTime = ChangeChar (PowerDownTime, 1);
             } 
           
             if (PowerDownTime < 100) {
               on_PowerDownTime = 0;
             }
          } 
            else

       // 4: ���� 
       //   ----------------------------- 
              
          if (Menu1 == 5) {
            
             Lang = Lang ? 0 : 1;
          } 
            else
              
       /// 5: ���� 
        //  ----------------------------- 
              
          if (Menu1 == 6) {
            
             if (Menu2 == 2) Dose = 0;
          } 
        


}


/* ------------------------------------------------------------------------- */
/* ---  ������ ������  ----------------------------------------------------- */
/* ------------------------------------------------------------------------- */

const unsigned int time_array [10] = {5,10,20,30,45,60,120,240,360,720};

void MenuButton (void) {

        
     // ������ 1 
        if (Button == 1) {
         
         if (MenuS) {
           MenuS = 0;
           Menu1 = 0;
           Menu2 = 0;
           
           // �������� ������ � ����������������� ������
              RomSave ();
         }
           else
         if (Menu1 == 0) { 
          // ��������� ������� ���������
             if (Rad_time == time_array [0]) Rad_time = time_array [1]; else
             if (Rad_time == time_array [1]) Rad_time = time_array [2]; else
             if (Rad_time == time_array [2]) Rad_time = time_array [3]; else
             if (Rad_time == time_array [3]) Rad_time = time_array [4]; else
             if (Rad_time == time_array [4]) Rad_time = time_array [5]; else
             if (Rad_time == time_array [5]) Rad_time = time_array [6]; else
             if (Rad_time == time_array [6]) Rad_time = time_array [7]; else
             if (Rad_time == time_array [7]) Rad_time = time_array [8]; else
             if (Rad_time == time_array [8]) Rad_time = time_array [9]; else
             if (Rad_time == time_array [9]) Rad_time = time_array [0]; else
                                             Rad_time = time_array [5];   
         } 
         else {
           if (Menu2 != 0) Menu2 = 0; else
           if (Menu1 != 0) Menu1 = 0;
         
         }
        }
         
     // ������ 2
        if (Button == 2) {
          
          if (MenuS) MenuButton2_S (); else
          if (Menu1 == 0) Menu1 = 1; else 
          if (Menu2 == 0) Menu2 = 1; else
          {
            MenuButton2_Set ();
          }            
           
        }
       
     // ������ 3
        if (Button == 3) {
          
          if (MenuS != 0) { 
            if (MenuS ++ == 5) MenuS = 1;
          }
            else
          if (Menu1 == 0) {  
            // ��� - ���� ���������  
             if (on_Led_Lcd == 0) Lcd_Led_on (); else Lcd_Led_off ();
          } else {
            if (Menu2 == 0) {
              if (Menu1 ++ == 6) Menu1 = 1;
            } else {                            
                                                Menu2 ++;               
              if ((Menu1 == 1) && (Menu2 == 4)) Menu2 = 1;  // ��������� 
              if ((Menu1 == 2) && (Menu2 == 3)) Menu2 = 1;  // ���������   
              if ((Menu1 == 3) && (Menu2 == 7)) Menu2 = 1;  // ������� 
              if ((Menu1 == 4) && (Menu2 == 7)) Menu2 = 1;  // ���� ���������� 
              if ((Menu1 == 5) && (Menu2 == 2)) Menu2 = 1;  // ����   
              if ((Menu1 == 6) && (Menu2 == 3)) Menu2 = 1;  // ����� ���� 
        
              
            }
          }
        }             

  // ����� ����� � ��������� ���� 
     MenuS_enter = 0;

  // ��������� ����� ������ �� �������
     draw = 1;
}


/* ------------------------------------------------------------------------- */
/* ---  ������ ������  ----------------------------------------------------- */
/* ------------------------------------------------------------------------- */

void MenuButtonSe (void) {

  // �������� ������
     Beep (50, 160);
  
  // ������ 1
     if (Button == 1) {
     
     // ���� � ��������� ����
        if ((Menu1) && (Menu2 == false)) MenuS = 1; 
        
     // ��������� - ����. �������
        else {
          
         if (on_alarm) {
        
        // ��������� �������
           on_alarm = 0;
        } 
          else {
            
        // �������� �������
           on_alarm = 1;
        }
         
        }
     }     
  
  // ������ 2: ��������� ��������
     if ((Button == 2) && (OnSTOP == 0)) OnSTOP = 1;
  
  // ������ 3 : ���-���� �������� � �������� ���������
     if (Button == 3) {
       
     // ���� � ��������� ����
        if ((Menu1) && (Menu2 == false)) {
           if (MenuS_enter ++ == 1) MenuS = 1; 
        }
          else
    
        if (on_Sound || on_Led) {
        
        // ��������� �������� ��������� � �������� ���������  
           Led_Sound (false, false);
        } 
          else {
            
        // �������� �������� ��������� � �������� ���������  
           Led_Sound (true, true);
        }
     }
}