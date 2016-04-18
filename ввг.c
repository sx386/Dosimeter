    
/* ------------------------------------------------------------------------- */
/* --- ������������� ��������������� ����������  --------------------------- */
/* ------------------------------------------------------------------------- */

void generator_initialization (void) {
 
  // ������������� ����� ������������ ���������� ��� : PB11 
     GPIO_InitTypeDef GPIO_InitStructure11;
     GPIO_InitStructure11.GPIO_Pin = GPIO_Pin_11;  // ������������ ����
     GPIO_InitStructure11.GPIO_Mode = GPIO_Mode_IN;  // ���� 
     GPIO_InitStructure11.GPIO_Speed = GPIO_Speed_2MHz;  // �������� �������
     GPIO_InitStructure11.GPIO_PuPd = GPIO_PuPd_UP;  // ������������� �������� � �������
     GPIO_Init (GPIOB, &GPIO_InitStructure11);

  // ������������� ����� ��������� ��� : PA7 
     GPIO_InitTypeDef GPIO_InitStructure;
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;  // ������������ ����
     GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  // ����������� ����� 
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  // �������� �������
     GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;  // ������������� ��������� ���������
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  // �������������� �������
     GPIO_Init (GPIOA, &GPIO_InitStructure);

  // ��-�� ���������� ���������� �������������� ������� �� ���� ����� ������������ 
  // ������ ������ ������������� ������������. ���������� ����� ������ ����� �����-������ 
  // ����� ���� ��������� � ������������ �������������� �������. ��� ���������� 
  // ���������������� �� ������ ���� ������������� ����� ��� �������� (AFRL � AFRH) � �� 
  // ������ ���� �� ������ ����� �����-������.
  
     GPIO_PinAFConfig (GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);
  
  // �������� ������������
     RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM3, ENABLE);
  
  // ������ ������������ ������� ������� ������������� �������� �������.
  // � ������ ������ �������� �� ������������,
  // ������� ������� ������� ����� ��������� �������

     TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
     TIM_TimeBaseStructure.TIM_Prescaler = 0;
     TIM_TimeBaseStructure.TIM_ClockDivision = 0;
     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  // ����������� ����� - ���������
     TIM_TimeBaseStructure.TIM_Period = 16;  // ������������
     TIM_TimeBaseInit (TIM3, &TIM_TimeBaseStructure);
  
  // ����� ��� : ��� �������� - ��� ������ ����� � �������� ���������, ��� 
  // ������ ����� ����������. � ������ ���������� - ��� ��������.
  
     TIM_OCInitTypeDef TIM_OCInitStructure2; 
     TIM_OCInitStructure2.TIM_OCMode = TIM_OCMode_PWM1;  // ����� ���  : 110 - mode 1 : ��������
     TIM_OCInitStructure2.TIM_OutputState = TIM_OutputState_Enable;  // ��������� ����������� � ������ ��
     TIM_OCInitStructure2.TIM_Pulse = 0;  // ������������
     TIM_OCInitStructure2.TIM_OCPolarity = TIM_OCPolarity_High;  // ������������� ����������
     TIM_OC2Init (TIM3, &TIM_OCInitStructure2);
  
  // ��������� ��������������� �������� �������� ���������
     TIM_OC2PreloadConfig (TIM3, TIM_OCPreload_Enable); 
  
  // ��������� ��������������� �������� �������� ����������������
     TIM_ARRPreloadConfig (TIM3, ENABLE); 

  // ���������� �� ������������
     TIM3->DIER |= TIM_DIER_UIE;  
    
  // ��������� ����������  
     NVIC_EnableIRQ (TIM3_IRQn); 
}


/* ------------------------------------------------------------------------- */
/* --- ��������������� ��������������� ����������  ------------------------- */
/* ------------------------------------------------------------------------- */
     
void generator_deinitialization (void) {
  
  // ��������� �������������� ��������� 
     GeneratorStop ();
 }


/* ------------------------------------------------------------------------- */
/* --- �������� �������������� ���������  ---------------------------------- */
/* ------------------------------------------------------------------------- */

void GeneratorStart (void) {

  // ������������ ���������� : H - ���
     if (GPIO_ReadInputDataBit (GPIOB, GPIO_Pin_11)) {
 
     // ��������� ���: �������
        on_Generator = 1; 
   
     // �������� ������ ���
        TIM_Cmd (TIM3, ENABLE);
     }
}


/* ------------------------------------------------------------------------- */
/* --- ��������� �������������� ���������  --------------------------------- */
/* ------------------------------------------------------------------------- */

void GeneratorStop (void) {
   
  // ��������� ������ ���
     TIM_Cmd (TIM3, DISABLE);
     
  // ������������ ��������
     TIM3->CCR2 = 0;  
     
  // ��������� ���: ��������
     on_Generator = 0; 
}


/* ------------------------------------------------------------------------- */
/* --- ���������� �� ������������ TIM3  ------------------------------------ */
/* ------------------------------------------------------------------------- */

void TIM3_IRQHandler (void) {
  
  // ������������ ���������� : H - ���
     if (GPIO_ReadInputDataBit (GPIOB, GPIO_Pin_11)) {
     
        GenImp ++;
     // ������������ ��������
        TIM3->CCR2 = 1; 
     } 
     
  // ������������ ���������� : L - ��
     else GeneratorStop ();  // ��������� ���

  // ������� �������� ����������
     TIM3->SR &= ~TIM_SR_UIF;      
}
