
/* константы портов управления
   ----------------------------------------------- */
 
# define lcd_vcc_on GPIOB->BSRRL = GPIO_Pin_8
# define lcd_vcc_off GPIOB->BSRRH = GPIO_Pin_8
 
# define lcd_clk_on GPIOB->BSRRL = GPIO_Pin_9
# define lcd_clk_off GPIOB->BSRRH = GPIO_Pin_9
 
# define lcd_reset_on GPIOA->BSRRL = GPIO_Pin_3
# define lcd_reset_off GPIOA->BSRRH = GPIO_Pin_3
 
# define lcd_data_on GPIOA->BSRRL = GPIO_Pin_2
# define lcd_data_off GPIOA->BSRRH = GPIO_Pin_2
 

/* установить все порты дисплея в низкое состояние
   ----------------------------------------------- */

void lcd_GPIO_off (void) {
  
  // установить порты шины 0..7 в низкое состояние  
     GPIOB->BSRRH = GPIO_Pin_0;
     GPIOB->BSRRH = GPIO_Pin_1;
     GPIOB->BSRRH = GPIO_Pin_2;
     GPIOB->BSRRH = GPIO_Pin_3;
     GPIOB->BSRRH = GPIO_Pin_4;
     GPIOB->BSRRH = GPIO_Pin_5;
     GPIOB->BSRRH = GPIO_Pin_6;
     GPIOB->BSRRH = GPIO_Pin_7;
  
  // установить порты управления в низкое состояние
     lcd_vcc_off; 
     lcd_data_off;  
     lcd_reset_off; 
     lcd_clk_off;  
}

  
/* инициализация портов дисплея
   --------------------------------- */

void lcd_PortInitialization (void) {
  
  // тип данных портов ввода-вывода
     GPIO_InitTypeDef GPIO_InitStructure;

  // настроика портов ввода-вывода
     GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  // двухтактный выход 
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  // тактовая частота
     GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  // подтягивающие резисторы отключены
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  // выход
  
  // настроика портов шины А
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
 
  // использовать на шине PAx
     GPIO_Init (GPIOA, &GPIO_InitStructure);

  // настроика портов шины B
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | 
                                   GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | 
                                   GPIO_Pin_8 | GPIO_Pin_9 ;
 
  // использовать на шине PBx
     GPIO_Init (GPIOB, &GPIO_InitStructure);
 
  // установить все порты дисплея в низкое состояние
     lcd_GPIO_off (); 
}

  
void lcd_deinitialization (void) {
   
  // установить все порты дисплея в низкое состояние
     lcd_GPIO_off (); 
}


/* отослать в дисплеи комманду из 8 бит
   ------------------------------------ */

void lcd_WriteCommand (char data) {

  // ножка "данные" в низкое состояние
     lcd_data_off;

  // очистить и установить биты порта B: 0...7    
     GPIOB->BSRRH = 0xff;  // очистить
     GPIOB->BSRRL = data;  // установить
             
  // ножка тактирования дисплея 
     lcd_clk_on;  // высокое (1) состояние
     lcd_clk_off;  // низкое (0) состояние
}



/* отослать в дисплеи данные из 8 бит
   ---------------------------------- */

void lcd_WriteData (char data) {

  // ножка "данные" в высокое состояние
     lcd_data_on;

  // очистить и установить биты порта B: 0...7    
     GPIOB->BSRRH = 0xff;  // очистить
     GPIOB->BSRRL = data;  // установить
             
  // ножка тактирования дисплея 
     lcd_clk_on;  // высокое (1) состояние
     lcd_clk_off;  // низкое (0) состояние
}


/* из 8 бит в char
   --------------------------------- */

char BitToChar (char e7, 
                char e6,               
                char e5, 
                char e4, 
                char e3, 
                char e2, 
                char e1, 
                char e0) {

  return e0*128+
         e1*64+
         e2*32+
         e3*16+
         e4*8+
         e5*4+
         e6*2+
         e7;
}


/* инициализация дисплея
   --------------------------------- */

void lcd_initialization (void) {
  
  // очистка кэша дисплея
     CacheClear ();
     
  
  // инициализация портов дисплея
     lcd_PortInitialization ();
 
  // включить питание дисплея
     lcd_vcc_on; 

  // установить вывод "RESET" в высокое состояние
     lcd_reset_on;
	
  // -------------------
     
     noop (100);
     lcd_WriteCommand (BitToChar (1,0,1,0,1,1,1,0));  // display off
     lcd_WriteCommand (BitToChar (0,1,0,0,0,0,0,0));  // Specify DDRAM line for COM0 
     lcd_WriteCommand (BitToChar (1,0,1,0,0,0,0,0));  // Select SEG output direction | normal direction | SEG 0 ... SEG 131
     
  // -------------------
 	
     noop (100);
     lcd_WriteCommand (BitToChar (0,0,0,1,0,0,0,0));  // Set column address MSB | = 0
     lcd_WriteCommand (BitToChar (0,0,0,0,0,0,0,0));  // Set column address LSB | = 0
     lcd_WriteCommand (BitToChar (1,0,1,0,0,1,1,0));  // Reverse display OFF 
     lcd_WriteCommand (BitToChar (1,0,1,0,0,0,1,0));  // Select LCD bias | ???
     lcd_WriteCommand (BitToChar (1,1,0,0,1,0,0,0));  // Select COM output direction | reverse direction | COM 63 ... COM 0
      
  // -------------------
 
     noop (100);
     lcd_WriteCommand (BitToChar (0,0,1,0,1,1,0,0));  // Control power circuit operation | ???
     noop (100);
     lcd_WriteCommand (BitToChar (0,0,1,0,1,1,1,0));  // Control power circuit operation | ???
     noop (100);
     lcd_WriteCommand (BitToChar (0,0,1,0,1,1,1,1));  // Control power circuit operation | ???
      
  // -------------------

     noop (100);
     lcd_WriteCommand (BitToChar (0,0,1,0,0,0,1,0));  // Select internal resistance ratio of the regulator resistor
  // lcd_WriteCommand (BitToChar (0,0,1,0,0,1,1,1));  // Select internal resistance ratio of the regulator resistor
     lcd_WriteCommand (BitToChar (1,0,0,0,0,0,0,1));  // Set reference voltage mode
     lcd_WriteCommand (BitToChar (0,0,1,0,1,0,0,0));  // Set reference voltage register
  // lcd_WriteCommand (BitToChar (0,0,1,1,1,1,1,1));  // Set reference voltage register
     lcd_WriteCommand (BitToChar (1,0,1,0,1,1,1,1));  // display on
     noop (100);
     
     
  // запись кэша в дисплей
     lcd_CacheWrite ();
}


/* очистка кэша дисплея
   --------------------------------- */

void CacheClear (void) {
  
  unsigned char x;
  
  for (x = 0; x < 112; x++) cache [0][x] = 0;  // линия 0
  for (x = 0; x < 112; x++) cache [1][x] = 0;  // линия 1
  for (x = 0; x < 112; x++) cache [2][x] = 0;  // линия 2
  for (x = 0; x < 112; x++) cache [3][x] = 0;  // линия 3
}


/* запись кэша в дисплей
   --------------------------------- */

void lcd_CacheWrite (void) {
 
  unsigned char i = 0;

  // 0: --------------------	
  
     lcd_WriteCommand (BitToChar (1,0,1,1,0,0,0,0)); // Set page address 
     lcd_WriteCommand (BitToChar (0,0,0,1,0,0,0,0)); // Set column address MSB 
     lcd_WriteCommand (BitToChar (0,0,0,0,0,0,0,0)); // Set column address LSB

  // вывод "данные" в высокое состояние
     lcd_data_on;

  // запись данных в дисплей
     for (i = 0; i < 112; i++) {
       
     // очистить и установить биты порта B: 0...7    
        GPIOB->BSRRH = 0xff;  // очистить
        GPIOB->BSRRL = cache [0][i];  // установить
             
     // вывод тактирования дисплея 
        lcd_clk_on;  // высокое (1) состояние
        lcd_clk_off;  // низкое (0) состояние
     }
     
  // 1: --------------------	
     
     lcd_WriteCommand (BitToChar (1,0,1,1,0,0,0,1)); // Set page address
     lcd_WriteCommand (BitToChar (0,0,0,1,0,0,0,0)); // Set column address MSB 
     lcd_WriteCommand (BitToChar (0,0,0,0,0,0,0,0)); // Set column address LSB 


  // вывод "данные" в высокое состояние
     lcd_data_on;

  // запись данных в дисплей
     for (i = 0; i < 112; i++) {
       
     // очистить и установить биты порта B: 0...7    
        GPIOB->BSRRH = 0xff;  // очистить
        GPIOB->BSRRL = cache [1][i];  // установить
             
     // вывод тактирования дисплея 
        lcd_clk_on;  // высокое (1) состояние
        lcd_clk_off;  // низкое (0) состояние
     }

  // 2: --------------------
     
     lcd_WriteCommand (BitToChar (1,0,1,1,0,0,1,0)); // Set page address 
     lcd_WriteCommand (BitToChar (0,0,0,1,0,0,0,0)); // Set column address MSB
     lcd_WriteCommand (BitToChar (0,0,0,0,0,0,0,0)); // Set column address LSB 

  // вывод "данные" в высокое состояние
     lcd_data_on;

  // запись данных в дисплей
     for (i = 0; i < 112; i++) {
       
     // очистить и установить биты порта B: 0...7    
        GPIOB->BSRRH = 0xff;  // очистить
        GPIOB->BSRRL = cache [2][i];  // установить
             
     // вывод тактирования дисплея 
        lcd_clk_on;  // высокое (1) состояние
        lcd_clk_off;  // низкое (0) состояние
     }

  // 3: --------------------	
     
     lcd_WriteCommand (BitToChar (1,0,1,1,0,0,1,1)); // Set page address
     lcd_WriteCommand (BitToChar (0,0,0,1,0,0,0,0)); // Set column address MSB
     lcd_WriteCommand (BitToChar (0,0,0,0,0,0,0,0)); // Set column address LSB

  // вывод "данные" в высокое состояние
     lcd_data_on;

  // запись данных в дисплей
     for (i = 0; i < 112; i++) {
       
     // очистить и установить биты порта B: 0...7    
        GPIOB->BSRRH = 0xff;  // очистить
        GPIOB->BSRRL = cache [3][i];  // установить
             
     // вывод тактирования дисплея 
        lcd_clk_on;  // высокое (1) состояние
        lcd_clk_off;  // низкое (0) состояние
     }
     
  // установить порты шины 0..7 в низкое состояние  
     GPIOB->BSRRH = GPIO_Pin_0;
     GPIOB->BSRRH = GPIO_Pin_1;
     GPIOB->BSRRH = GPIO_Pin_2;
     GPIOB->BSRRH = GPIO_Pin_3;
     GPIOB->BSRRH = GPIO_Pin_4;
     GPIOB->BSRRH = GPIO_Pin_5;
     GPIOB->BSRRH = GPIO_Pin_6;
     GPIOB->BSRRH = GPIO_Pin_7;
  
  // установить порты управления в низкое состояние
     lcd_data_off;  
     lcd_clk_off;  
}