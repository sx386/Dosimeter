
/* ------------------------------------------------------------------------- */
/* ---  �������������  ----------------------------------------------------- */
/* ------------------------------------------------------------------------- */

void initialization (void) {

  // ������ ������ �� EEPROM ������
     rom_read ();
       
  // ������������
     rcc_initialization ();
  
  // ������������ ������ �����-������
     GPIO_initialization ();
 
  // �������� ����� ����������� �����������������
     PWR_UltraLowPowerCmd (ENABLE);
     
  // ���������� ������� ���� � Range 3 : VCORE = 1.2V
     PWR_VoltageScalingConfig (PWR_VoltageScaling_Range3); 
     
     
  // ������������� �����
     Sound_initialization ();
 
  // ������������� ������� 3.3�   
     Power33_initialization ();
      
  // ������������� �������
     lcd_initialization ();

     
  // ������������� ������
     ButtonT_initialization ();
     Button1_initialization ();
     Button2_initialization ();
     Button3_initialization ();     
     
  // ������������� ��������������� ���������� 
     generator_initialization ();  
     
  // ������������� �������� ���������
     Led_initialization ();
  
  // ������������� ������� �������
     time_initialization ();
     
  // ������������� ��������
     counter_initialization () ;
     
  // ������������� ��������� �������
     Lcd_Led_initialization ();
     
  // ������� ���
     batt_charge_initialization ();
}


/* ------------------------------------------------------------------------- */
/* ---  ���������������  --------------------------------------------------- */
/* ------------------------------------------------------------------------- */

void de_initialization (void) {

  // ��������� ���������������� �� SWD
     SWD (DISABLE);
     
  // ��������������� ��������� �������
     Lcd_Led_deinitialization ();
   
  // ��������������� ������� �������
     time_deinitialization ();
    
  // ��������������� ��������������� ���������� 
     generator_deinitialization ();  
    
  // ��������������� ��������
     counter_deinitialization () ;  
     
  // ��������������� �������� ���������
     Led_deinitialization ();
     
  // ��������������� ������� 3.3�
     Power33_deinitialization (); 
     
  // ��������������� �������
     lcd_deinitialization ();
    
  // ��������������� ������
     Button1_deinitialization ();
     Button3_deinitialization ();  
  
  // ������� ����������
     var_reset ();
}