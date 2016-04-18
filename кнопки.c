
/* ------------------------------------------------------------------------- */
/* ---  ������ ������  ----------------------------------------------------- */
/* ------------------------------------------------------------------------- */
     
void on_button (void) { 

  // ���� ����� �� ������ "����"
     if (OnSTOP != 0) {
    
     }
      else 
  
  // ���� ������ �� �������
      if (ButtonDisable > 0) {
      
      }
       else
         
  // ���� ������ ������
     if (Button_exec == 2) MenuButton ();
        
     // ���� ������ ������
        else {
          MenuButtonSe ();
          ButtonDisable = 3; // ����� �� 0,5�. ������������ ������
        }
  
    
  // �������� ����� ����� ���������� ������� �� ������  
     TimeButtonAct = 0;
     
  // �������� 50 ��
  // noop (5000);
        
  // ������� ������ ������
     Button = 0;  // ������� ������
     Button_exec = 0;  // ��������� ������� ������
     Button_time = 0;  // ������� ������: ������ 
 
  // ������� ������: �� ����������� 
     on_Button = 0;  
}


/* ------------------------------------------------------------------------- */
/* ---  ������������� ������ 1  -------------------------------------------- */
/* ------------------------------------------------------------------------- */

void Button1_initialization (void) {
  
  // ��������� ����� PA9
     GPIO_InitTypeDef GPIO_InitStructure;
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // ����
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  // �������� �������
     GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // �������� � �������
     GPIO_Init (GPIOA, &GPIO_InitStructure);

  // ��������� ���������� �� ����� 9 ����� A 
     SYSCFG->EXTICR[2]|= SYSCFG_EXTICR3_EXTI9_PA;  
 
  // ���������� �� ��������� ����������
     EXTI->FTSR |= EXTI_RTSR_TR9; 
 
  // ��������� ���������� �� ����� 9
     EXTI->IMR |= EXTI_IMR_MR9;

  // ��������� ����������
     NVIC_SetPriority (EXTI9_5_IRQn, 1);
  
  // ��������� ���������� ����������
     NVIC_EnableIRQ (EXTI9_5_IRQn);
}


/* ------------------------------------------------------------------------- */
/* ---  ������������� ������ 2  -------------------------------------------- */
/* ------------------------------------------------------------------------- */

void Button2_initialization (void) {
  
  // ��������� ����� PC13
     GPIO_InitTypeDef Port;
     Port.GPIO_Pin = GPIO_Pin_13;
     Port.GPIO_Mode = GPIO_Mode_IN;  // ����
     Port.GPIO_Speed = GPIO_Speed_2MHz;  // �������� �������
     Port.GPIO_PuPd = GPIO_PuPd_DOWN;  // �������� � �����
     GPIO_Init (GPIOC, &Port);
  
  // ��������� ���������� �� ����� 13 ����� C 
     SYSCFG->EXTICR [3] |= SYSCFG_EXTICR4_EXTI13_PC;  
 
  // ���������� �� ��������� ����������
     EXTI->RTSR |= EXTI_RTSR_TR13;  // ��������� :: ������ ���������� 
  // EXTI->FTSR |= EXTI_RTSR_TR13;  // ��������� :: ������ ���������� 
 
  // ��������� ���������� �� ����� 13 
     EXTI->IMR |= EXTI_IMR_MR13;

  // ��������� ����������
     NVIC_SetPriority (EXTI15_10_IRQn, 1);
  
  // ��������� ���������� ����������
     NVIC_EnableIRQ (EXTI15_10_IRQn); 
}


/* ------------------------------------------------------------------------- */
/* ---  ������������� ������ 3  -------------------------------------------- */
/* ------------------------------------------------------------------------- */

void Button3_initialization (void) {
  
 // ��������� ����� PA5
     GPIO_InitTypeDef GPIO_InitStructure;
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // ����
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  // �������� �������
     GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // �������� � �������
     GPIO_Init (GPIOA, &GPIO_InitStructure);

  // ��������� ���������� �� ����� 5 ����� A 
     SYSCFG->EXTICR[1]|= SYSCFG_EXTICR2_EXTI5_PA;  
 
  // ���������� �� ��������� ����������
     EXTI->FTSR |= EXTI_RTSR_TR5; 
 
  // ��������� ���������� �� ����� 5 
     EXTI->IMR |= EXTI_IMR_MR5;

  // ��������� ����������
     NVIC_SetPriority (EXTI9_5_IRQn, 1);
  
  // ��������� ���������� ����������
     NVIC_EnableIRQ (EXTI9_5_IRQn); 
  
}


/* ------------------------------------------------------------------------- */
/* ---  ��������������� ������ 1  ------------------------------------------ */
/* ------------------------------------------------------------------------- */

void Button1_deinitialization (void) {
   
  // ��������� ���������� �� ����� 9 ����� A 
     SYSCFG->EXTICR [2] &= ~SYSCFG_EXTICR3_EXTI9_PA;  
 
  // ��������� ���������� �� ����� 9
     EXTI->IMR &= ~EXTI_IMR_MR9;
    
  // ��������� ���������� ����������
     NVIC_DisableIRQ (EXTI9_5_IRQn);   
}


/* ------------------------------------------------------------------------- */
/* ---  ��������������� ������ 3  ------------------------------------------ */
/* ------------------------------------------------------------------------- */

void Button3_deinitialization (void) {
   
  // ��������� ���������� �� ����� 5 ����� A 
     SYSCFG->EXTICR [1] &= ~SYSCFG_EXTICR2_EXTI5_PA;   
 
  // ��������� ���������� �� ����� 5
     EXTI->IMR &= ~EXTI_IMR_MR5;
    
  // ��������� ���������� ����������
     NVIC_DisableIRQ (EXTI9_5_IRQn);   
}


/* ------------------------------------------------------------------------- */
/* ---  ���������� ������ 2  ----------------------------------------------- */
/* ------------------------------------------------------------------------- */

void EXTI15_10_IRQHandler (void) { 
  
  // ���������� �� ����� 13 (������ 2)
     if (EXTI->PR & (1<<13)) {
       
     // ������ 2
        ButtonTimerOn (2);
       
     // �������� ������� ����������
        EXTI->PR |= (1<<13);
     }
}


/* ------------------------------------------------------------------------- */
/* ---  ���������� ������ 1 � 3  ------------------------------------------- */
/* ------------------------------------------------------------------------- */

void EXTI9_5_IRQHandler (void) {
 
  // ���������� �� ����� 9 (������ 1)
     if (EXTI->PR & (1<<9)) {
       
     // ������ 1
        ButtonTimerOn (1);
        
     // �������� ������� ����������
        EXTI->PR |= (1<<9);
     }
       else

  // ���������� �� ����� 5 (������ 3)
     if (EXTI->PR & (1<<5)) {

     // ������ 3
        ButtonTimerOn (3);
        
     // �������� ������� ����������
        EXTI->PR |= (1<<5);
     }
}


/* ------------------------------------------------------------------------- */
/* ---  ������������� ������� ��� ������  ---------------------------------- */
/* ------------------------------------------------------------------------- */

void ButtonT_initialization (void) { 
  // ������������ �������
  
     RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM4, ENABLE);
     
  // �������� ��������� �������
     TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
     TIM_TimeBaseStructure.TIM_Prescaler = 1024 - 1;  // ��������
     TIM_TimeBaseStructure.TIM_ClockDivision = 0;  // ������� ��������
     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  // ����������� �����: ���������
     TIM_TimeBaseStructure.TIM_Period = 30;  // ������������
     TIM_TimeBaseInit (TIM4, &TIM_TimeBaseStructure);
     
  // ���������� �� ������������
     TIM4->DIER |= TIM_DIER_UIE;  
    
  // ��������� ����������  
     NVIC_EnableIRQ (TIM4_IRQn); 
}


/* ------------------------------------------------------------------------- */
/* ---  ���������� ������� ��� ������  ------------------------------------- */
/* ------------------------------------------------------------------------- */

void TIM4_IRQHandler (void) {

  // ������ ������� ������ (+1)
     Button_time ++;
     
  // ���� ������ ������ * ������
     if (Button_time == 60) ButtonTimerOff (); else
 
  // �������� ������� (1)
     if (Button_exec == 0) {
     
        if ((Button == 1) && (GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_9 ) == 1)) Button_exec = 1; 
        if ((Button == 2) && (GPIO_ReadInputDataBit (GPIOC, GPIO_Pin_13) == 0)) Button_exec = 1; 
        if ((Button == 3) && (GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_5 ) == 1)) Button_exec = 1; 
     }
        else
        
  // �������� ������� (2)
     if (Button_exec == 1) {
      
        if ((Button == 1) && (GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_9 ) == 1)) Button_exec = 2; 
        if ((Button == 2) && (GPIO_ReadInputDataBit (GPIOC, GPIO_Pin_13) == 0)) Button_exec = 2;
        if ((Button == 3) && (GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_5 ) == 1)) Button_exec = 2;
     
     // ���� ������ ������
        if (Button_exec == 2)  ButtonTimerOff (); else Button_exec = 0;
     }  
  
  // ������� ���� ����������
     TIM4->SR &= ~TIM_SR_UIF;    
}


/* ------------------------------------------------------------------------- */
/* ---  ��������� ������� ������  ------------------------------------------ */
/* ------------------------------------------------------------------------- */

void ButtonTimerOn (char no) {
  
  // ������� ������: ����������� 
     on_Button = 1;  
 
  // ������� ������ ������
     Button = no;  // ������� ������
     Button_exec = 0;  // ��������� ������� ������
     Button_time = 0;  // ������� ������: ������ 
  
  // �������� ������
     TIM_Cmd (TIM4, ENABLE);  
}


/* ------------------------------------------------------------------------- */
/* ---  ���������� ������� ������  ----------------------------------------- */
/* ------------------------------------------------------------------------- */

void ButtonTimerOff (void) {
  
  // ���������� ������
     TIM_Cmd (TIM4, DISABLE);
  
  // ������ ������
     on_button (); 
}





