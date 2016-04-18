/* xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx */
/* xxxxxxxxxx  Д О З И М Е Т Р xxxxxxxxx */
/* xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx */
 
# include "stdio.h" 
# include "stm32l1xx.h"
# include "const.h" 
# include "main.h"
# include "разное.h"
# include "GPIO.h"
# include "кнопки.h"
# include "питание.h"
# include "дисплеи.h"
# include "кэш.h"
# include "вывод.h"
# include "часы.h"
# include "ввг.h"
# include "счетчик.h"
# include "menu.h"
# include "расчеты.h"

# include "данные.c"
# include "rom.c"
# include "разное.c"
# include "GPIO.c"
# include "инициплизация.c"
# include "кнопки.c"
# include "питание.c"
# include "дисплеи.c"
# include "кэш.c"
# include "вывод.c"
# include "часы.c"
# include "ввг.c"
# include "счетчик.c"
# include "menu.c"
# include "расчеты.c"
 
  
/* xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx */
/* xxxxxxxxxx выполнение кода xxxxxxxxxx */
/* xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx */

void main () {
     
     noop (500000);
     noop (500000);
     noop (500000);

     
  // инициализация
     initialization ();

     
  while (1) {
   
  // выключение дозиметра     
     if (OnSTOP == 1) STOP ();
     
  // измерение напряжения питания
     if (BattGet == 1) on_BattGet ();
     
  // вывод данных на дисплей
     if (draw == 1) on_draw ();
          
  // питание 3,3В
     if (on_Led || on_Sound || on_Led_Lcd) Power33on; else Power33off;
       
  // переход в режим стоп
     if (on_Generator == false)
     if (on_Button == false)
     if (on_Led_Lcd == false)
     if (process_Led == false){
       PWR_EnterSTOPMode (PWR_Regulator_LowPower, PWR_STOPEntry_WFI);     
    }
  }
}