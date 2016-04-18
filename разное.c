
/* ------------------------------------------------------------------------- */
/* ---  одидание : тактов * 10  -------------------------------------------- */
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
/* ---  питание 3.3в  ------------------------------------------------------ */
/* ------------------------------------------------------------------------- */
 
# define Power33on GPIOA->BSRRL = GPIO_Pin_8
# define Power33off GPIOA->BSRRH = GPIO_Pin_8

void Power33_initialization (void) {

  // тип данных
     GPIO_InitTypeDef Port;

  // настроика портов ввода-вывода
     Port.GPIO_OType = GPIO_OType_PP;  // двухтактный выход 
     Port.GPIO_Speed = GPIO_Speed_2MHz;  // тактовая частота
     Port.GPIO_PuPd = GPIO_PuPd_NOPULL;  // подтягивающие резисторы отключены
     Port.GPIO_Mode = GPIO_Mode_OUT;  // выход
  
  // использовать для портов
     Port.GPIO_Pin = GPIO_Pin_8;
  
  // использовать на шине PAx
     GPIO_Init (GPIOA, &Port);
  
  // включить питание 3.3В
     Power33on;
}

void Power33_deinitialization (void) {
  
  Power33off;
}


/* ------------------------------------------------------------------------- */
/* ---  звуковая индикация  ------------------------------------------------ */
/* ------------------------------------------------------------------------- */
 
# define SoundOn GPIOA->BSRRL = GPIO_Pin_4
# define SoundOff GPIOA->BSRRH = GPIO_Pin_4

void Sound_initialization (void) {

  // тип данных
     GPIO_InitTypeDef Port;

  // настроика портов ввода-вывода
     Port.GPIO_OType = GPIO_OType_PP;  // двухтактный выход 
     Port.GPIO_Speed = GPIO_Speed_2MHz;  // тактовая частота
     Port.GPIO_PuPd = GPIO_PuPd_NOPULL;  // подтягивающие резисторы отключены
     Port.GPIO_Mode = GPIO_Mode_OUT;  // выход
  
  // использовать для портов
     Port.GPIO_Pin = GPIO_Pin_4;
  
  // использовать на шине PAx
     GPIO_Init (GPIOA, &Port);
} 


/* ------------------------------------------------------------------------- */
/* ---  отключить программирование по SWD  --------------------------------- */
/* ------------------------------------------------------------------------- */

void SWD (char set) {

 // отключить SWD
    if (set == DISABLE) {
      
    // тип данных
       GPIO_InitTypeDef Port;

    // настроика портов ввода-вывода
       Port.GPIO_OType = GPIO_OType_PP;  // двухтактный выход 
       Port.GPIO_Speed = GPIO_Speed_2MHz;  // тактовая частота
       Port.GPIO_PuPd = GPIO_PuPd_NOPULL;  // подтягивающие резисторы отключены
       Port.GPIO_Mode = GPIO_Mode_OUT;  // выход
  
    // использовать для портов
       Port.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
  
    // использовать на шине PAx
       GPIO_Init (GPIOA, &Port);
    }
}


/* ------------------------------------------------------------------------- */
/* ---  инициализация подсветки дисплея  ----------------------------------- */
/* ------------------------------------------------------------------------- */

void Lcd_Led_initialization (void) {

  // инициализация порта подсветки
     GPIO_InitTypeDef GPIO_InitStructure;
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;  // использовать порт
     GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  // двухтактный выход 
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  // тактовая частота
     GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  // подтягивающие резисторы отключены
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  // альтернативная функция
     GPIO_Init (GPIOA, &GPIO_InitStructure);
  
  // Из-за увеличения количества альтернативных функций на одну линию разработчики 
  // решили ввести мультиплексор переключений. Фактически выход каждой линии ввода-вывода 
  // может быть подключён к определенной альтернативной функции. Для управления 
  // мультиплексорами на каждый порт дополнительно ввели два регистра (AFRL и AFRH) и по 
  // четыре бита на каждую линии ввода-вывода.
  
     GPIO_PinAFConfig (GPIOA, GPIO_PinSource15, GPIO_AF_TIM2); 

  // включить тактирование 
     RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM2, ENABLE);
 
  // задаем коэффициенты деления внешних предделителей тактовой частоты.
  // в данном случае делители не используются,
  // входная частота таймера равна системной частоте

     TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
     TIM_TimeBaseStructure.TIM_Prescaler = 0;
     TIM_TimeBaseStructure.TIM_ClockDivision = 0;
     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  // направление счета - инкремент
     TIM_TimeBaseStructure.TIM_Period = 1024;  // переполнение
     TIM_TimeBaseInit (TIM2, &TIM_TimeBaseStructure);

  // Режим шим : при основном - чем больше число в регистре сравнения, тем 
  // больше число заполнения. В случае инверсного - все наоборот.

  // PA3 : шим подсветки дисплея
     TIM_OCInitTypeDef TIM_OCInitStructure; 
     TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;  // режим шим  : 111 - mode 2 : инверсныи
     TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  // разрешить подключение к выводу мк
     TIM_OCInitStructure.TIM_Pulse = 0;  // длительность
     TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  // положительная полярность
     TIM_OC1Init (TIM2, &TIM_OCInitStructure);

  // разрешить предварительную загрузку регистра сравнения
     TIM_OC1PreloadConfig (TIM2, TIM_OCPreload_Enable); 
  
  // разрешаем предварительную загрузку регистра автоперезагрузки
     TIM_ARRPreloadConfig (TIM2, ENABLE); 
     
  // включить таимер подсветки
     TIM_Cmd (TIM2, ENABLE);

     
  // установить яркость подсветки дисплея
     Lcd_Led_Set (false);
}


/* ------------------------------------------------------------------------- */
/* ---  деинициализация подсветки дисплея  --------------------------------- */
/* ------------------------------------------------------------------------- */
  
void Lcd_Led_deinitialization (void) {
  
}


/* ------------------------------------------------------------------------- */
/* ---  установить яркость подсветки дисплея  ------------------------------ */
/* ------------------------------------------------------------------------- */
  
void Lcd_Led_Set (int count) {
  
  // изменить яркость подсветки
     if (count != false) Led_Lcd_Percent = count;

  // если подсветка включена - установить длительность импульса
     if (on_Led_Lcd) TIM2->CCR1 = (int) 600 * Led_Lcd_Percent / 100; 
}


/* ------------------------------------------------------------------------- */
/* ---  включить подсветку дисплея  ---------------------------------------- */
/* ------------------------------------------------------------------------- */
  
void Lcd_Led_on (void) {
  
  // подсветка дисплея: включена
     on_Led_Lcd = 1;

  // установить яркость подсветки дисплея
     Lcd_Led_Set (false);
}


/* ------------------------------------------------------------------------- */
/* ---  выключить подсветку дисплея  --------------------------------------- */
/* ------------------------------------------------------------------------- */
  
void Lcd_Led_off (void) {

  // установить длительность импульса
     TIM2->CCR1 = 0; 
  
  // подсветка дисплея: выключена
     on_Led_Lcd = 0;
}


/* ------------------------------------------------------------------------- */
/* ---  инициализация световой индикации  ---------------------------------- */
/* ------------------------------------------------------------------------- */

void Led_initialization (void) {

  // инициализация порта
     GPIO_InitTypeDef GPIO_InitStructure3;
     GPIO_InitStructure3.GPIO_Pin = GPIO_Pin_15;  // использовать порт
     GPIO_InitStructure3.GPIO_OType = GPIO_OType_PP;  // двухтактный выход 
     GPIO_InitStructure3.GPIO_Speed = GPIO_Speed_2MHz;  // тактовая частота
     GPIO_InitStructure3.GPIO_PuPd = GPIO_PuPd_NOPULL;  // подтягивающие резисторы отключены
     GPIO_InitStructure3.GPIO_Mode = GPIO_Mode_AF;  // альтернативная функция
     GPIO_Init (GPIOB, &GPIO_InitStructure3);
  
  // Из-за увеличения количества альтернативных функций на одну линию разработчики 
  // решили ввести мультиплексор переключений. Фактически выход каждой линии ввода-вывода 
  // может быть подключён к определенной альтернативной функции. Для управления 
  // мультиплексорами на каждый порт дополнительно ввели два регистра (AFRL и AFRH) и по 
  // четыре бита на каждую линии ввода-вывода.
  
     GPIO_PinAFConfig (GPIOB, GPIO_PinSource15, GPIO_AF_TIM11); 

  // включить тактирование 
     RCC_APB2PeriphClockCmd (RCC_APB2Periph_TIM11, ENABLE);
 
  // задаем коэффициенты деления внешних предделителей тактовой частоты.
  // в данном случае делители не используются,
  // входная частота таймера равна системной частоте

     TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
     TIM_TimeBaseStructure.TIM_Prescaler = 0;
     TIM_TimeBaseStructure.TIM_ClockDivision = 0;
     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  // направление счета - инкремент
     TIM_TimeBaseStructure.TIM_Period = 1024 * 4;  // переполнение
     TIM_TimeBaseInit (TIM11, &TIM_TimeBaseStructure);

  // Режим шим : при основном - чем больше число в регистре сравнения, тем 
  // больше число заполнения. В случае инверсного - все наоборот.

     TIM_OCInitTypeDef TIM_OCInitStructure4; 
     TIM_OCInitStructure4.TIM_OCMode = TIM_OCMode_PWM1;  // режим шим  : обычный
     TIM_OCInitStructure4.TIM_OutputState = TIM_OutputState_Enable;  // разрешить подключение к выводу мк
     TIM_OCInitStructure4.TIM_Pulse = 0;  // длительность
     TIM_OCInitStructure4.TIM_OCPolarity = TIM_OCPolarity_High;  // положительная полярность
     TIM_OC1Init (TIM11, &TIM_OCInitStructure4);

  // разрешить предварительную загрузку регистра сравнения
  // TIM_OC1PreloadConfig (TIM11, TIM_OCPreload_Enable); 
  
  // разрешаем предварительную загрузку регистра автоперезагрузки
     TIM_ARRPreloadConfig (TIM11, ENABLE); 

  // прерывание по переполнению
     TIM11->DIER |= TIM_DIER_UIE;  
    
  // разрешить прерывание  
     NVIC_EnableIRQ (TIM11_IRQn); 
  
  // разрешить выполнение
     TIM_Cmd (TIM11, ENABLE);
}


/* ------------------------------------------------------------------------- */
/* ---  деинициализация световой индикации  -------------------------------- */
/* ------------------------------------------------------------------------- */

void Led_deinitialization (void) {

}


/* ------------------------------------------------------------------------- */
/* ---  включить световую индикации  --------------------------------------- */
/* ------------------------------------------------------------------------- */

void Led_On () {
  
  // световая индикация: в процессе 
     process_Led = 1; 
     
  // длительность импульса
     TIM11->CCR1 = 1024 * 2;
   
  // разрешить предварительную загрузку регистра сравнения
     TIM_OC1PreloadConfig (TIM11, TIM_OCPreload_Enable); 
}


/* ------------------------------------------------------------------------- */
/* ---  выключить световую индикации  -------------------------------------- */
/* ------------------------------------------------------------------------- */

void Led_Off () { 
  
  // длительность импульса
     TIM11->CCR1 = 0; 
   
  // запретить предварительную загрузку регистра сравнения
     TIM_OC1PreloadConfig (TIM11, TIM_OCPreload_Disable);
  
  // световая индикация: не работает
     process_Led = 0; 
}


/* ------------------------------------------------------------------------- */
/* ---  звуковой сигнал  --------------------------------------------------- */
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
/* ---  включить - выключить звуковую и световую индикацию  ---------------- */
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
/* ---  прерывание световой индикации  ------------------------------------- */
/* ------------------------------------------------------------------------- */

void TIM11_IRQHandler (void) {
  
  // длительность вспышек светодиода больше длительности регистрации квантов,
  // поэтому выключаем таимер когда кол-во вспышек светодиода 
  // сравняестся с количеством квантов
  
     if (Rad_counter > Led_count) Led_count ++; else Led_Off ();    
  
  // очистка регистра прерывания
     TIM11->SR &= ~TIM_SR_UIF;      
}
