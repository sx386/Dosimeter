
/* ------------------------------------------------------------------------- */
/* ---  инициализация  ----------------------------------------------------- */
/* ------------------------------------------------------------------------- */

void initialization (void) {

  // читать данные из EEPROM памяти
     rom_read ();
       
  // тактирование
     rcc_initialization ();
  
  // инициалзация портов ввода-вывода
     GPIO_initialization ();
 
  // включить режим пониженного энергопотребления
     PWR_UltraLowPowerCmd (ENABLE);
     
  // установить питание ядра в Range 3 : VCORE = 1.2V
     PWR_VoltageScalingConfig (PWR_VoltageScaling_Range3); 
     
     
  // инициализация звука
     Sound_initialization ();
 
  // инициализация питания 3.3В   
     Power33_initialization ();
      
  // инициализация дисплея
     lcd_initialization ();

     
  // инициализация кнопок
     ButtonT_initialization ();
     Button1_initialization ();
     Button2_initialization ();
     Button3_initialization ();     
     
  // инициализация высоковольтного генератора 
     generator_initialization ();  
     
  // инициализация световой индикации
     Led_initialization ();
  
  // инициализация таимера времени
     time_initialization ();
     
  // инициализация счетчика
     counter_initialization () ;
     
  // инициализация подсветки дисплея
     Lcd_Led_initialization ();
     
  // зарядка АКБ
     batt_charge_initialization ();
}


/* ------------------------------------------------------------------------- */
/* ---  деинициализация  --------------------------------------------------- */
/* ------------------------------------------------------------------------- */

void de_initialization (void) {

  // отключить программирование по SWD
     SWD (DISABLE);
     
  // деинициализация подсветки дисплея
     Lcd_Led_deinitialization ();
   
  // деинициализация таимера времени
     time_deinitialization ();
    
  // деинициализация высоковольтного генератора 
     generator_deinitialization ();  
    
  // деинициализация счетчика
     counter_deinitialization () ;  
     
  // деинициализация световой индикации
     Led_deinitialization ();
     
  // деинициализация питания 3.3В
     Power33_deinitialization (); 
     
  // деинициализация дисплея
     lcd_deinitialization ();
    
  // деинициализация кнопок
     Button1_deinitialization ();
     Button3_deinitialization ();  
  
  // очистка переменных
     var_reset ();
}