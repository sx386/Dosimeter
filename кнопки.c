
/* ------------------------------------------------------------------------- */
/* ---  кнопка нажата  ----------------------------------------------------- */
/* ------------------------------------------------------------------------- */
     
void on_button (void) { 

  // если выход из режима "стоп"
     if (OnSTOP != 0) {
    
     }
      else 
  
  // если кнопка не активна
      if (ButtonDisable > 0) {
      
      }
       else
         
  // если кнопка нажата
     if (Button_exec == 2) MenuButton ();
        
     // если кнопка зажата
        else {
          MenuButtonSe ();
          ButtonDisable = 3; // время по 0,5с. неактивности кнопки
        }
  
    
  // очистить время после последнего нажатия на кнопку  
     TimeButtonAct = 0;
     
  // ожидание 50 мс
  // noop (5000);
        
  // очистка данных кнопки
     Button = 0;  // нажатая кнопка
     Button_exec = 0;  // состояние нажатия кнопки
     Button_time = 0;  // зажатие кнопки: циклов 
 
  // нажатие кнопки: не выполняется 
     on_Button = 0;  
}


/* ------------------------------------------------------------------------- */
/* ---  инициализация кнопки 1  -------------------------------------------- */
/* ------------------------------------------------------------------------- */

void Button1_initialization (void) {
  
  // настроика порта PA9
     GPIO_InitTypeDef GPIO_InitStructure;
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // вход
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  // тактовая частота
     GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // подтяжка к питанию
     GPIO_Init (GPIOA, &GPIO_InitStructure);

  // настроить прерывание на вывод 9 линии A 
     SYSCFG->EXTICR[2]|= SYSCFG_EXTICR3_EXTI9_PA;  
 
  // выполнение по понижению напряжения
     EXTI->FTSR |= EXTI_RTSR_TR9; 
 
  // настроить прерывание на вывод 9
     EXTI->IMR |= EXTI_IMR_MR9;

  // приоритет прерывания
     NVIC_SetPriority (EXTI9_5_IRQn, 1);
  
  // разрешить выполнение прерывания
     NVIC_EnableIRQ (EXTI9_5_IRQn);
}


/* ------------------------------------------------------------------------- */
/* ---  инициализация кнопки 2  -------------------------------------------- */
/* ------------------------------------------------------------------------- */

void Button2_initialization (void) {
  
  // настроика порта PC13
     GPIO_InitTypeDef Port;
     Port.GPIO_Pin = GPIO_Pin_13;
     Port.GPIO_Mode = GPIO_Mode_IN;  // вход
     Port.GPIO_Speed = GPIO_Speed_2MHz;  // тактовая частота
     Port.GPIO_PuPd = GPIO_PuPd_DOWN;  // подтяжка к земле
     GPIO_Init (GPIOC, &Port);
  
  // настроить прерывание на вывод 13 линии C 
     SYSCFG->EXTICR [3] |= SYSCFG_EXTICR4_EXTI13_PC;  
 
  // выполнение по изменению напряжения
     EXTI->RTSR |= EXTI_RTSR_TR13;  // повышение :: кнопка нажимается 
  // EXTI->FTSR |= EXTI_RTSR_TR13;  // понижение :: кнопка отжимается 
 
  // настроить прерывание на вывод 13 
     EXTI->IMR |= EXTI_IMR_MR13;

  // приоритет прерывания
     NVIC_SetPriority (EXTI15_10_IRQn, 1);
  
  // разрешить выполнение прерывания
     NVIC_EnableIRQ (EXTI15_10_IRQn); 
}


/* ------------------------------------------------------------------------- */
/* ---  инициализация кнопки 3  -------------------------------------------- */
/* ------------------------------------------------------------------------- */

void Button3_initialization (void) {
  
 // настроика порта PA5
     GPIO_InitTypeDef GPIO_InitStructure;
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // вход
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  // тактовая частота
     GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // подтяжка к питанию
     GPIO_Init (GPIOA, &GPIO_InitStructure);

  // настроить прерывание на вывод 5 линии A 
     SYSCFG->EXTICR[1]|= SYSCFG_EXTICR2_EXTI5_PA;  
 
  // выполнение по понижению напряжения
     EXTI->FTSR |= EXTI_RTSR_TR5; 
 
  // настроить прерывание на вывод 5 
     EXTI->IMR |= EXTI_IMR_MR5;

  // приоритет прерывания
     NVIC_SetPriority (EXTI9_5_IRQn, 1);
  
  // разрешить выполнение прерывания
     NVIC_EnableIRQ (EXTI9_5_IRQn); 
  
}


/* ------------------------------------------------------------------------- */
/* ---  деинициализация кнопки 1  ------------------------------------------ */
/* ------------------------------------------------------------------------- */

void Button1_deinitialization (void) {
   
  // отключить прерывание на вывод 9 линии A 
     SYSCFG->EXTICR [2] &= ~SYSCFG_EXTICR3_EXTI9_PA;  
 
  // отключить прерывание на вывод 9
     EXTI->IMR &= ~EXTI_IMR_MR9;
    
  // запретить выполнение прерывания
     NVIC_DisableIRQ (EXTI9_5_IRQn);   
}


/* ------------------------------------------------------------------------- */
/* ---  деинициализация кнопки 3  ------------------------------------------ */
/* ------------------------------------------------------------------------- */

void Button3_deinitialization (void) {
   
  // отключить прерывание на вывод 5 линии A 
     SYSCFG->EXTICR [1] &= ~SYSCFG_EXTICR2_EXTI5_PA;   
 
  // отключить прерывание на вывод 5
     EXTI->IMR &= ~EXTI_IMR_MR5;
    
  // запретить выполнение прерывания
     NVIC_DisableIRQ (EXTI9_5_IRQn);   
}


/* ------------------------------------------------------------------------- */
/* ---  прерывание кнопки 2  ----------------------------------------------- */
/* ------------------------------------------------------------------------- */

void EXTI15_10_IRQHandler (void) { 
  
  // прерывание на линии 13 (кнопка 2)
     if (EXTI->PR & (1<<13)) {
       
     // кнопка 2
        ButtonTimerOn (2);
       
     // очистить регистр прерывания
        EXTI->PR |= (1<<13);
     }
}


/* ------------------------------------------------------------------------- */
/* ---  прерывание кнопки 1 и 3  ------------------------------------------- */
/* ------------------------------------------------------------------------- */

void EXTI9_5_IRQHandler (void) {
 
  // прерывание на линии 9 (кнопка 1)
     if (EXTI->PR & (1<<9)) {
       
     // кнопка 1
        ButtonTimerOn (1);
        
     // очистить регистр прерывания
        EXTI->PR |= (1<<9);
     }
       else

  // прерывание на линии 5 (кнопка 3)
     if (EXTI->PR & (1<<5)) {

     // кнопка 3
        ButtonTimerOn (3);
        
     // очистить регистр прерывания
        EXTI->PR |= (1<<5);
     }
}


/* ------------------------------------------------------------------------- */
/* ---  инициализация таимера для кнопок  ---------------------------------- */
/* ------------------------------------------------------------------------- */

void ButtonT_initialization (void) { 
  // тактирование таимера
  
     RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM4, ENABLE);
     
  // основная настроика таимера
     TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
     TIM_TimeBaseStructure.TIM_Prescaler = 1024 - 1;  // делитель
     TIM_TimeBaseStructure.TIM_ClockDivision = 0;  // внешний делитель
     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  // направление счета: инкремент
     TIM_TimeBaseStructure.TIM_Period = 30;  // переполнение
     TIM_TimeBaseInit (TIM4, &TIM_TimeBaseStructure);
     
  // прерывание по переполнению
     TIM4->DIER |= TIM_DIER_UIE;  
    
  // разрешить прерывание  
     NVIC_EnableIRQ (TIM4_IRQn); 
}


/* ------------------------------------------------------------------------- */
/* ---  прерывание таимера для кнопок  ------------------------------------- */
/* ------------------------------------------------------------------------- */

void TIM4_IRQHandler (void) {

  // циклов зажатия кнопки (+1)
     Button_time ++;
     
  // если кнопка зажата * циклов
     if (Button_time == 60) ButtonTimerOff (); else
 
  // проверка отжатия (1)
     if (Button_exec == 0) {
     
        if ((Button == 1) && (GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_9 ) == 1)) Button_exec = 1; 
        if ((Button == 2) && (GPIO_ReadInputDataBit (GPIOC, GPIO_Pin_13) == 0)) Button_exec = 1; 
        if ((Button == 3) && (GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_5 ) == 1)) Button_exec = 1; 
     }
        else
        
  // проверка отжатия (2)
     if (Button_exec == 1) {
      
        if ((Button == 1) && (GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_9 ) == 1)) Button_exec = 2; 
        if ((Button == 2) && (GPIO_ReadInputDataBit (GPIOC, GPIO_Pin_13) == 0)) Button_exec = 2;
        if ((Button == 3) && (GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_5 ) == 1)) Button_exec = 2;
     
     // если кнопка нажата
        if (Button_exec == 2)  ButtonTimerOff (); else Button_exec = 0;
     }  
  
  // очистка бита прерывания
     TIM4->SR &= ~TIM_SR_UIF;    
}


/* ------------------------------------------------------------------------- */
/* ---  включение таимера кнопок  ------------------------------------------ */
/* ------------------------------------------------------------------------- */

void ButtonTimerOn (char no) {
  
  // нажатие кнопки: выполняется 
     on_Button = 1;  
 
  // очистка данных кнопки
     Button = no;  // нажатая кнопка
     Button_exec = 0;  // состояние нажатия кнопки
     Button_time = 0;  // зажатие кнопки: циклов 
  
  // включить таимер
     TIM_Cmd (TIM4, ENABLE);  
}


/* ------------------------------------------------------------------------- */
/* ---  выключение таимера кнопок  ----------------------------------------- */
/* ------------------------------------------------------------------------- */

void ButtonTimerOff (void) {
  
  // остановить таимер
     TIM_Cmd (TIM4, DISABLE);
  
  // кнопка нажата
     on_button (); 
}





