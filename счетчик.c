
/* ------------------------------------------------------------------------- */
/* ---  ������������� ��������  -------------------------------------------- */
/* ------------------------------------------------------------------------- */

void counter_initialization (void) {
  
  // ��������� ����� PA0
     GPIO_InitTypeDef GPIO_InitStructure;
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // ����
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;  // �������� �������
     GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // �������� � �������
     GPIO_Init (GPIOA, &GPIO_InitStructure);
  
  // ��������� ���������� �� ����� 0 ����� A 
     SYSCFG->EXTICR [0] |= SYSCFG_EXTICR1_EXTI0_PA; 
 
  // ���������� �� ��������� ����������
     EXTI->RTSR |= EXTI_RTSR_TR0;  // ���������
  // EXTI->FTSR |= EXTI_RTSR_TR0;  // ���������
 
  // ��������� ���������� �� ����� 0 
     EXTI->IMR |= EXTI_IMR_MR0;

  // ��������� ����������
     NVIC_SetPriority (EXTI0_IRQn, 0);
  
  // ��������� ���������� ����������
     NVIC_EnableIRQ (EXTI0_IRQn);   
}


/* ------------------------------------------------------------------------- */
/* ---  ��������������� ��������  ------------------------------------------ */
/* ------------------------------------------------------------------------- */

void counter_deinitialization (void) {
  
  // ������� ���������� � ������ 0 
     EXTI->IMR &= ~ EXTI_IMR_MR0; 
     
  // ��������� ���������� ����������
     NVIC_DisableIRQ (EXTI0_IRQn);   
     
  // �������� ��� ����������
     EXTI->PR |= EXTI_PR_PR0; 
}

  
/* ���������� �������� 
   --------------------------------------------- */

void EXTI0_IRQHandler (void) { 
 
  // ������� ������� �������� 
     Rad_counter ++;
     
     
  // �������� ���������
     if (on_Led) Led_On ();
  
  // �������� ���������
     if (on_Sound) { SoundOn; noop (3); SoundOff; }
    
  // �������� �������������� ��������� (���� 3 ��� ������ ������� �� 0.5 ���.)
     if (Rad_counter > 2) GeneratorStart ();  
     
          
  // �������� ��� ����������
     EXTI->PR |= EXTI_PR_PR0;
}
 
