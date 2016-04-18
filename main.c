/* xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx */
/* xxxxxxxxxx  � � � � � � � � xxxxxxxxx */
/* xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx */
 
# include "stdio.h" 
# include "stm32l1xx.h"
# include "const.h" 
# include "main.h"
# include "������.h"
# include "GPIO.h"
# include "������.h"
# include "�������.h"
# include "�������.h"
# include "���.h"
# include "�����.h"
# include "����.h"
# include "���.h"
# include "�������.h"
# include "menu.h"
# include "�������.h"

# include "������.c"
# include "rom.c"
# include "������.c"
# include "GPIO.c"
# include "�������������.c"
# include "������.c"
# include "�������.c"
# include "�������.c"
# include "���.c"
# include "�����.c"
# include "����.c"
# include "���.c"
# include "�������.c"
# include "menu.c"
# include "�������.c"
 
  
/* xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx */
/* xxxxxxxxxx ���������� ���� xxxxxxxxxx */
/* xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx */

void main () {
     
     noop (500000);
     noop (500000);
     noop (500000);

     
  // �������������
     initialization ();

     
  while (1) {
   
  // ���������� ���������     
     if (OnSTOP == 1) STOP ();
     
  // ��������� ���������� �������
     if (BattGet == 1) on_BattGet ();
     
  // ����� ������ �� �������
     if (draw == 1) on_draw ();
          
  // ������� 3,3�
     if (on_Led || on_Sound || on_Led_Lcd) Power33on; else Power33off;
       
  // ������� � ����� ����
     if (on_Generator == false)
     if (on_Button == false)
     if (on_Led_Lcd == false)
     if (process_Led == false){
       PWR_EnterSTOPMode (PWR_Regulator_LowPower, PWR_STOPEntry_WFI);     
    }
  }
}