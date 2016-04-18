
/* ��������� ������ ����������
   ----------------------------------------------- */
 
# define lcd_vcc_on GPIOB->BSRRL = GPIO_Pin_8
# define lcd_vcc_off GPIOB->BSRRH = GPIO_Pin_8
 
# define lcd_clk_on GPIOB->BSRRL = GPIO_Pin_9
# define lcd_clk_off GPIOB->BSRRH = GPIO_Pin_9
 
# define lcd_reset_on GPIOA->BSRRL = GPIO_Pin_3
# define lcd_reset_off GPIOA->BSRRH = GPIO_Pin_3
 
# define lcd_data_on GPIOA->BSRRL = GPIO_Pin_2
# define lcd_data_off GPIOA->BSRRH = GPIO_Pin_2
 

/* ���������� ��� ����� ������� � ������ ���������
   ----------------------------------------------- */

void lcd_GPIO_off (void) {
  
  // ���������� ����� ���� 0..7 � ������ ���������  
     GPIOB->BSRRH = GPIO_Pin_0;
     GPIOB->BSRRH = GPIO_Pin_1;
     GPIOB->BSRRH = GPIO_Pin_2;
     GPIOB->BSRRH = GPIO_Pin_3;
     GPIOB->BSRRH = GPIO_Pin_4;
     GPIOB->BSRRH = GPIO_Pin_5;
     GPIOB->BSRRH = GPIO_Pin_6;
     GPIOB->BSRRH = GPIO_Pin_7;
  
  // ���������� ����� ���������� � ������ ���������
     lcd_vcc_off; 
     lcd_data_off;  
     lcd_reset_off; 
     lcd_clk_off;  
}

  
/* ������������� ������ �������
   --------------------------------- */

void lcd_PortInitialization (void) {
  
  // ��� ������ ������ �����-������
     GPIO_InitTypeDef GPIO_InitStructure;

  // ��������� ������ �����-������
     GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  // ����������� ����� 
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  // �������� �������
     GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  // ������������� ��������� ���������
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  // �����
  
  // ��������� ������ ���� �
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
 
  // ������������ �� ���� PAx
     GPIO_Init (GPIOA, &GPIO_InitStructure);

  // ��������� ������ ���� B
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | 
                                   GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | 
                                   GPIO_Pin_8 | GPIO_Pin_9 ;
 
  // ������������ �� ���� PBx
     GPIO_Init (GPIOB, &GPIO_InitStructure);
 
  // ���������� ��� ����� ������� � ������ ���������
     lcd_GPIO_off (); 
}

  
void lcd_deinitialization (void) {
   
  // ���������� ��� ����� ������� � ������ ���������
     lcd_GPIO_off (); 
}


/* �������� � ������� �������� �� 8 ���
   ------------------------------------ */

void lcd_WriteCommand (char data) {

  // ����� "������" � ������ ���������
     lcd_data_off;

  // �������� � ���������� ���� ����� B: 0...7    
     GPIOB->BSRRH = 0xff;  // ��������
     GPIOB->BSRRL = data;  // ����������
             
  // ����� ������������ ������� 
     lcd_clk_on;  // ������� (1) ���������
     lcd_clk_off;  // ������ (0) ���������
}



/* �������� � ������� ������ �� 8 ���
   ---------------------------------- */

void lcd_WriteData (char data) {

  // ����� "������" � ������� ���������
     lcd_data_on;

  // �������� � ���������� ���� ����� B: 0...7    
     GPIOB->BSRRH = 0xff;  // ��������
     GPIOB->BSRRL = data;  // ����������
             
  // ����� ������������ ������� 
     lcd_clk_on;  // ������� (1) ���������
     lcd_clk_off;  // ������ (0) ���������
}


/* �� 8 ��� � char
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


/* ������������� �������
   --------------------------------- */

void lcd_initialization (void) {
  
  // ������� ���� �������
     CacheClear ();
     
  
  // ������������� ������ �������
     lcd_PortInitialization ();
 
  // �������� ������� �������
     lcd_vcc_on; 

  // ���������� ����� "RESET" � ������� ���������
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
     
     
  // ������ ���� � �������
     lcd_CacheWrite ();
}


/* ������� ���� �������
   --------------------------------- */

void CacheClear (void) {
  
  unsigned char x;
  
  for (x = 0; x < 112; x++) cache [0][x] = 0;  // ����� 0
  for (x = 0; x < 112; x++) cache [1][x] = 0;  // ����� 1
  for (x = 0; x < 112; x++) cache [2][x] = 0;  // ����� 2
  for (x = 0; x < 112; x++) cache [3][x] = 0;  // ����� 3
}


/* ������ ���� � �������
   --------------------------------- */

void lcd_CacheWrite (void) {
 
  unsigned char i = 0;

  // 0: --------------------	
  
     lcd_WriteCommand (BitToChar (1,0,1,1,0,0,0,0)); // Set page address 
     lcd_WriteCommand (BitToChar (0,0,0,1,0,0,0,0)); // Set column address MSB 
     lcd_WriteCommand (BitToChar (0,0,0,0,0,0,0,0)); // Set column address LSB

  // ����� "������" � ������� ���������
     lcd_data_on;

  // ������ ������ � �������
     for (i = 0; i < 112; i++) {
       
     // �������� � ���������� ���� ����� B: 0...7    
        GPIOB->BSRRH = 0xff;  // ��������
        GPIOB->BSRRL = cache [0][i];  // ����������
             
     // ����� ������������ ������� 
        lcd_clk_on;  // ������� (1) ���������
        lcd_clk_off;  // ������ (0) ���������
     }
     
  // 1: --------------------	
     
     lcd_WriteCommand (BitToChar (1,0,1,1,0,0,0,1)); // Set page address
     lcd_WriteCommand (BitToChar (0,0,0,1,0,0,0,0)); // Set column address MSB 
     lcd_WriteCommand (BitToChar (0,0,0,0,0,0,0,0)); // Set column address LSB 


  // ����� "������" � ������� ���������
     lcd_data_on;

  // ������ ������ � �������
     for (i = 0; i < 112; i++) {
       
     // �������� � ���������� ���� ����� B: 0...7    
        GPIOB->BSRRH = 0xff;  // ��������
        GPIOB->BSRRL = cache [1][i];  // ����������
             
     // ����� ������������ ������� 
        lcd_clk_on;  // ������� (1) ���������
        lcd_clk_off;  // ������ (0) ���������
     }

  // 2: --------------------
     
     lcd_WriteCommand (BitToChar (1,0,1,1,0,0,1,0)); // Set page address 
     lcd_WriteCommand (BitToChar (0,0,0,1,0,0,0,0)); // Set column address MSB
     lcd_WriteCommand (BitToChar (0,0,0,0,0,0,0,0)); // Set column address LSB 

  // ����� "������" � ������� ���������
     lcd_data_on;

  // ������ ������ � �������
     for (i = 0; i < 112; i++) {
       
     // �������� � ���������� ���� ����� B: 0...7    
        GPIOB->BSRRH = 0xff;  // ��������
        GPIOB->BSRRL = cache [2][i];  // ����������
             
     // ����� ������������ ������� 
        lcd_clk_on;  // ������� (1) ���������
        lcd_clk_off;  // ������ (0) ���������
     }

  // 3: --------------------	
     
     lcd_WriteCommand (BitToChar (1,0,1,1,0,0,1,1)); // Set page address
     lcd_WriteCommand (BitToChar (0,0,0,1,0,0,0,0)); // Set column address MSB
     lcd_WriteCommand (BitToChar (0,0,0,0,0,0,0,0)); // Set column address LSB

  // ����� "������" � ������� ���������
     lcd_data_on;

  // ������ ������ � �������
     for (i = 0; i < 112; i++) {
       
     // �������� � ���������� ���� ����� B: 0...7    
        GPIOB->BSRRH = 0xff;  // ��������
        GPIOB->BSRRL = cache [3][i];  // ����������
             
     // ����� ������������ ������� 
        lcd_clk_on;  // ������� (1) ���������
        lcd_clk_off;  // ������ (0) ���������
     }
     
  // ���������� ����� ���� 0..7 � ������ ���������  
     GPIOB->BSRRH = GPIO_Pin_0;
     GPIOB->BSRRH = GPIO_Pin_1;
     GPIOB->BSRRH = GPIO_Pin_2;
     GPIOB->BSRRH = GPIO_Pin_3;
     GPIOB->BSRRH = GPIO_Pin_4;
     GPIOB->BSRRH = GPIO_Pin_5;
     GPIOB->BSRRH = GPIO_Pin_6;
     GPIOB->BSRRH = GPIO_Pin_7;
  
  // ���������� ����� ���������� � ������ ���������
     lcd_data_off;  
     lcd_clk_off;  
}