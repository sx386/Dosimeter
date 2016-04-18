
/* ------------------------------------------------------------------------- */
/* ---  �������� : ������ * 10  -------------------------------------------- */
/* ------------------------------------------------------------------------- */

void noop (long int count) { 
  
  while (count > 0) {
    
    __ASM ("NOP");
    __ASM ("NOP");
    __ASM ("NOP");
    __ASM ("NOP");
    __ASM ("NOP");
    __ASM ("NOP");
    
    count --;
  }
}


/**
  * @ brief  Decrements the TimingDelay variable.
  * @ param  None
  * @ retval None
  */

void TimingDelay_Decrement (void) {

}


/* ------------------------------------------------------------------------- */
/* ---  ������� 3.3�  ------------------------------------------------------ */
/* ------------------------------------------------------------------------- */
 
# define Power33on GPIOA->BSRRL = GPIO_Pin_8
# define Power33off GPIOA->BSRRH = GPIO_Pin_8

void Power33_initialization (void) {

  // ��� ������
     GPIO_InitTypeDef Port;

  // ��������� ������ �����-������
     Port.GPIO_OType = GPIO_OType_PP;  // ����������� ����� 
     Port.GPIO_Speed = GPIO_Speed_2MHz;  // �������� �������
     Port.GPIO_PuPd = GPIO_PuPd_NOPULL;  // ������������� ��������� ���������
     Port.GPIO_Mode = GPIO_Mode_OUT;  // �����
  
  // ������������ ��� ������
     Port.GPIO_Pin = GPIO_Pin_8;
  
  // ������������ �� ���� PAx
     GPIO_Init (GPIOA, &Port);
  
  // �������� ������� 3.3�
     Power33on;
}

void Power33_deinitialization (void) {
  
  Power33off;
}


/* ------------------------------------------------------------------------- */
/* ---  �������� ���������  ------------------------------------------------ */
/* ------------------------------------------------------------------------- */
 
# define SoundOn GPIOA->BSRRL = GPIO_Pin_4
# define SoundOff GPIOA->BSRRH = GPIO_Pin_4

void Sound_initialization (void) {

  // ��� ������
     GPIO_InitTypeDef Port;

  // ��������� ������ �����-������
     Port.GPIO_OType = GPIO_OType_PP;  // ����������� ����� 
     Port.GPIO_Speed = GPIO_Speed_2MHz;  // �������� �������
     Port.GPIO_PuPd = GPIO_PuPd_NOPULL;  // ������������� ��������� ���������
     Port.GPIO_Mode = GPIO_Mode_OUT;  // �����
  
  // ������������ ��� ������
     Port.GPIO_Pin = GPIO_Pin_4;
  
  // ������������ �� ���� PAx
     GPIO_Init (GPIOA, &Port);
} 


/* ------------------------------------------------------------------------- */
/* ---  ��������� ���������������� �� SWD  --------------------------------- */
/* ------------------------------------------------------------------------- */

void SWD (char set) {

 // ��������� SWD
    if (set == DISABLE) {
      
    // ��� ������
       GPIO_InitTypeDef Port;

    // ��������� ������ �����-������
       Port.GPIO_OType = GPIO_OType_PP;  // ����������� ����� 
       Port.GPIO_Speed = GPIO_Speed_2MHz;  // �������� �������
       Port.GPIO_PuPd = GPIO_PuPd_NOPULL;  // ������������� ��������� ���������
       Port.GPIO_Mode = GPIO_Mode_OUT;  // �����
  
    // ������������ ��� ������
       Port.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
  
    // ������������ �� ���� PAx
       GPIO_Init (GPIOA, &Port);
    }
}


/* ------------------------------------------------------------------------- */
/* ---  ������������� ��������� �������  ----------------------------------- */
/* ------------------------------------------------------------------------- */

void Lcd_Led_initialization (void) {

  // ������������� ����� ���������
     GPIO_InitTypeDef GPIO_InitStructure;
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;  // ������������ ����
     GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  // ����������� ����� 
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  // �������� �������
     GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  // ������������� ��������� ���������
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  // �������������� �������
     GPIO_Init (GPIOA, &GPIO_InitStructure);
  
  // ��-�� ���������� ���������� �������������� ������� �� ���� ����� ������������ 
  // ������ ������ ������������� ������������. ���������� ����� ������ ����� �����-������ 
  // ����� ���� ��������� � ������������ �������������� �������. ��� ���������� 
  // ���������������� �� ������ ���� ������������� ����� ��� �������� (AFRL � AFRH) � �� 
  // ������ ���� �� ������ ����� �����-������.
  
     GPIO_PinAFConfig (GPIOA, GPIO_PinSource15, GPIO_AF_TIM2); 

  // �������� ������������ 
     RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM2, ENABLE);
 
  // ������ ������������ ������� ������� ������������� �������� �������.
  // � ������ ������ �������� �� ������������,
  // ������� ������� ������� ����� ��������� �������

     TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
     TIM_TimeBaseStructure.TIM_Prescaler = 0;
     TIM_TimeBaseStructure.TIM_ClockDivision = 0;
     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  // ����������� ����� - ���������
     TIM_TimeBaseStructure.TIM_Period = 1024;  // ������������
     TIM_TimeBaseInit (TIM2, &TIM_TimeBaseStructure);

  // ����� ��� : ��� �������� - ��� ������ ����� � �������� ���������, ��� 
  // ������ ����� ����������. � ������ ���������� - ��� ��������.

  // PA3 : ��� ��������� �������
     TIM_OCInitTypeDef TIM_OCInitStructure; 
     TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;  // ����� ���  : 111 - mode 2 : ���������
     TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  // ��������� ����������� � ������ ��
     TIM_OCInitStructure.TIM_Pulse = 0;  // ������������
     TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  // ������������� ����������
     TIM_OC1Init (TIM2, &TIM_OCInitStructure);

  // ��������� ��������������� �������� �������� ���������
     TIM_OC1PreloadConfig (TIM2, TIM_OCPreload_Enable); 
  
  // ��������� ��������������� �������� �������� ����������������
     TIM_ARRPreloadConfig (TIM2, ENABLE); 
     
  // �������� ������ ���������
     TIM_Cmd (TIM2, ENABLE);

     
  // ���������� ������� ��������� �������
     Lcd_Led_Set (false);
}


/* ------------------------------------------------------------------------- */
/* ---  ��������������� ��������� �������  --------------------------------- */
/* ------------------------------------------------------------------------- */
  
void Lcd_Led_deinitialization (void) {
  
}


/* ------------------------------------------------------------------------- */
/* ---  ���������� ������� ��������� �������  ------------------------------ */
/* ------------------------------------------------------------------------- */
  
void Lcd_Led_Set (int count) {
  
  // �������� ������� ���������
     if (count != false) Led_Lcd_Percent = count;

  // ���� ��������� �������� - ���������� ������������ ��������
     if (on_Led_Lcd) TIM2->CCR1 = (int) 600 * Led_Lcd_Percent / 100; 
}


/* ------------------------------------------------------------------------- */
/* ---  �������� ��������� �������  ---------------------------------------- */
/* ------------------------------------------------------------------------- */
  
void Lcd_Led_on (void) {
  
  // ��������� �������: ��������
     on_Led_Lcd = 1;

  // ���������� ������� ��������� �������
     Lcd_Led_Set (false);
}


/* ------------------------------------------------------------------------- */
/* ---  ��������� ��������� �������  --------------------------------------- */
/* ------------------------------------------------------------------------- */
  
void Lcd_Led_off (void) {

  // ���������� ������������ ��������
     TIM2->CCR1 = 0; 
  
  // ��������� �������: ���������
     on_Led_Lcd = 0;
}


/* ------------------------------------------------------------------------- */
/* ---  ������������� �������� ���������  ---------------------------------- */
/* ------------------------------------------------------------------------- */

void Led_initialization (void) {

  // ������������� �����
     GPIO_InitTypeDef GPIO_InitStructure3;
     GPIO_InitStructure3.GPIO_Pin = GPIO_Pin_15;  // ������������ ����
     GPIO_InitStructure3.GPIO_OType = GPIO_OType_PP;  // ����������� ����� 
     GPIO_InitStructure3.GPIO_Speed = GPIO_Speed_2MHz;  // �������� �������
     GPIO_InitStructure3.GPIO_PuPd = GPIO_PuPd_NOPULL;  // ������������� ��������� ���������
     GPIO_InitStructure3.GPIO_Mode = GPIO_Mode_AF;  // �������������� �������
     GPIO_Init (GPIOB, &GPIO_InitStructure3);
  
  // ��-�� ���������� ���������� �������������� ������� �� ���� ����� ������������ 
  // ������ ������ ������������� ������������. ���������� ����� ������ ����� �����-������ 
  // ����� ���� ��������� � ������������ �������������� �������. ��� ���������� 
  // ���������������� �� ������ ���� ������������� ����� ��� �������� (AFRL � AFRH) � �� 
  // ������ ���� �� ������ ����� �����-������.
  
     GPIO_PinAFConfig (GPIOB, GPIO_PinSource15, GPIO_AF_TIM11); 

  // �������� ������������ 
     RCC_APB2PeriphClockCmd (RCC_APB2Periph_TIM11, ENABLE);
 
  // ������ ������������ ������� ������� ������������� �������� �������.
  // � ������ ������ �������� �� ������������,
  // ������� ������� ������� ����� ��������� �������

     TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
     TIM_TimeBaseStructure.TIM_Prescaler = 0;
     TIM_TimeBaseStructure.TIM_ClockDivision = 0;
     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  // ����������� ����� - ���������
     TIM_TimeBaseStructure.TIM_Period = 1024 * 4;  // ������������
     TIM_TimeBaseInit (TIM11, &TIM_TimeBaseStructure);

  // ����� ��� : ��� �������� - ��� ������ ����� � �������� ���������, ��� 
  // ������ ����� ����������. � ������ ���������� - ��� ��������.

     TIM_OCInitTypeDef TIM_OCInitStructure4; 
     TIM_OCInitStructure4.TIM_OCMode = TIM_OCMode_PWM1;  // ����� ���  : �������
     TIM_OCInitStructure4.TIM_OutputState = TIM_OutputState_Enable;  // ��������� ����������� � ������ ��
     TIM_OCInitStructure4.TIM_Pulse = 0;  // ������������
     TIM_OCInitStructure4.TIM_OCPolarity = TIM_OCPolarity_High;  // ������������� ����������
     TIM_OC1Init (TIM11, &TIM_OCInitStructure4);

  // ��������� ��������������� �������� �������� ���������
  // TIM_OC1PreloadConfig (TIM11, TIM_OCPreload_Enable); 
  
  // ��������� ��������������� �������� �������� ����������������
     TIM_ARRPreloadConfig (TIM11, ENABLE); 

  // ���������� �� ������������
     TIM11->DIER |= TIM_DIER_UIE;  
    
  // ��������� ����������  
     NVIC_EnableIRQ (TIM11_IRQn); 
  
  // ��������� ����������
     TIM_Cmd (TIM11, ENABLE);
}


/* ------------------------------------------------------------------------- */
/* ---  ��������������� �������� ���������  -------------------------------- */
/* ------------------------------------------------------------------------- */

void Led_deinitialization (void) {

}


/* ------------------------------------------------------------------------- */
/* ---  �������� �������� ���������  --------------------------------------- */
/* ------------------------------------------------------------------------- */

void Led_On () {
  
  // �������� ���������: � �������� 
     process_Led = 1; 
     
  // ������������ ��������
     TIM11->CCR1 = 1024 * 2;
   
  // ��������� ��������������� �������� �������� ���������
     TIM_OC1PreloadConfig (TIM11, TIM_OCPreload_Enable); 
}


/* ------------------------------------------------------------------------- */
/* ---  ��������� �������� ���������  -------------------------------------- */
/* ------------------------------------------------------------------------- */

void Led_Off () { 
  
  // ������������ ��������
     TIM11->CCR1 = 0; 
   
  // ��������� ��������������� �������� �������� ���������
     TIM_OC1PreloadConfig (TIM11, TIM_OCPreload_Disable);
  
  // �������� ���������: �� ��������
     process_Led = 0; 
}


/* ------------------------------------------------------------------------- */
/* ---  �������� ������  --------------------------------------------------- */
/* ------------------------------------------------------------------------- */

void Beep (unsigned int n, unsigned int d) {

  Power33on;

  while (n --) {
  
     SoundOn; 
     noop (3); 
     SoundOff;
     noop (d);
  }
}


/* ------------------------------------------------------------------------- */
/* ---  �������� - ��������� �������� � �������� ���������  ---------------- */
/* ------------------------------------------------------------------------- */

char Led_Sound (char _Led, char _Sound) {
  
  if (_Led == true) {
    on_Led = 1;
  }
  
  if (_Led == false) {
    Led_Off ();
    on_Led = 0;
  }
  
  if (_Sound == true) {
    on_Sound = 1;
  }
  
  if (_Sound == false) {
    on_Sound = 0;
  }
  
  if (on_Led || on_Sound) Power33on;
  
  return true;
}


/* ------------------------------------------------------------------------- */
/* ---  ���������� �������� ���������  ------------------------------------- */
/* ------------------------------------------------------------------------- */

void TIM11_IRQHandler (void) {
  
  // ������������ ������� ���������� ������ ������������ ����������� �������,
  // ������� ��������� ������ ����� ���-�� ������� ���������� 
  // ����������� � ����������� �������
  
     if (Rad_counter > Led_count) Led_count ++; else Led_Off ();    
  
  // ������� �������� ����������
     TIM11->SR &= ~TIM_SR_UIF;      
}
