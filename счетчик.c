
/* ------------------------------------------------------------------------- */
/* ---  инициализация счетчика  -------------------------------------------- */
/* ------------------------------------------------------------------------- */

void counter_initialization (void) {
  
  // настроика порта PA0
     GPIO_InitTypeDef GPIO_InitStructure;
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // вход
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;  // тактовая частота
     GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // подтяжка к питанию
     GPIO_Init (GPIOA, &GPIO_InitStructure);
  
  // настроить прерывание на вывод 0 линии A 
     SYSCFG->EXTICR [0] |= SYSCFG_EXTICR1_EXTI0_PA; 
 
  // выполнение по изменению напряжения
     EXTI->RTSR |= EXTI_RTSR_TR0;  // повышению
  // EXTI->FTSR |= EXTI_RTSR_TR0;  // понижению
 
  // настроить прерывание на вывод 0 
     EXTI->IMR |= EXTI_IMR_MR0;

  // приоритет прерывания
     NVIC_SetPriority (EXTI0_IRQn, 0);
  
  // разрешить выполнение прерывания
     NVIC_EnableIRQ (EXTI0_IRQn);   
}


/* ------------------------------------------------------------------------- */
/* ---  деинициализация счетчика  ------------------------------------------ */
/* ------------------------------------------------------------------------- */

void counter_deinitialization (void) {
  
  // удалить прерывание с вывода 0 
     EXTI->IMR &= ~ EXTI_IMR_MR0; 
     
  // запретить выполнение прерывания
     NVIC_DisableIRQ (EXTI0_IRQn);   
     
  // очистить бит прерывания
     EXTI->PR |= EXTI_PR_PR0; 
}

  
/* прерывание счетчика 
   --------------------------------------------- */

void EXTI0_IRQHandler (void) { 
 
  // счетчик квантов радиации 
     Rad_counter ++;
     
     
  // световая индикация
     if (on_Led) Led_On ();
  
  // звуковая индикация
     if (on_Sound) { SoundOn; noop (3); SoundOff; }
    
  // включить высоковольтный генератор (если 3 или больше квантов за 0.5 сек.)
     if (Rad_counter > 2) GeneratorStart ();  
     
          
  // очистить бит прерывания
     EXTI->PR |= EXTI_PR_PR0;
}
 
