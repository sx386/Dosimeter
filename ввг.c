    
/* ------------------------------------------------------------------------- */
/* --- инициализация высоковольтного генератора  --------------------------- */
/* ------------------------------------------------------------------------- */

void generator_initialization (void) {
 
  // инициализация порта переполнения напряжения ВВГ : PB11 
     GPIO_InitTypeDef GPIO_InitStructure11;
     GPIO_InitStructure11.GPIO_Pin = GPIO_Pin_11;  // использовать порт
     GPIO_InitStructure11.GPIO_Mode = GPIO_Mode_IN;  // вход 
     GPIO_InitStructure11.GPIO_Speed = GPIO_Speed_2MHz;  // тактовая частота
     GPIO_InitStructure11.GPIO_PuPd = GPIO_PuPd_UP;  // подтягивающий резистор к питанию
     GPIO_Init (GPIOB, &GPIO_InitStructure11);

  // инициализация порта импульсов ВВГ : PA7 
     GPIO_InitTypeDef GPIO_InitStructure;
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;  // использовать порт
     GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  // двухтактный выход 
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  // тактовая частота
     GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;  // подтягивающие резисторы отключены
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  // альтернативная функция
     GPIO_Init (GPIOA, &GPIO_InitStructure);

  // Из-за увеличения количества альтернативных функций на одну линию разработчики 
  // решили ввести мультиплексор переключений. Фактически выход каждой линии ввода-вывода 
  // может быть подключён к определенной альтернативной функции. Для управления 
  // мультиплексорами на каждый порт дополнительно ввели два регистра (AFRL и AFRH) и по 
  // четыре бита на каждую линии ввода-вывода.
  
     GPIO_PinAFConfig (GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);
  
  // включить тактирование
     RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM3, ENABLE);
  
  // задаем коэффициенты деления внешних предделителей тактовой частоты.
  // в данном случае делители не используются,
  // входная частота таймера равна системной частоте

     TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
     TIM_TimeBaseStructure.TIM_Prescaler = 0;
     TIM_TimeBaseStructure.TIM_ClockDivision = 0;
     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  // направление счета - инкремент
     TIM_TimeBaseStructure.TIM_Period = 16;  // переполнение
     TIM_TimeBaseInit (TIM3, &TIM_TimeBaseStructure);
  
  // Режим шим : при основном - чем больше число в регистре сравнения, тем 
  // больше число заполнения. В случае инверсного - все наоборот.
  
     TIM_OCInitTypeDef TIM_OCInitStructure2; 
     TIM_OCInitStructure2.TIM_OCMode = TIM_OCMode_PWM1;  // режим шим  : 110 - mode 1 : основнои
     TIM_OCInitStructure2.TIM_OutputState = TIM_OutputState_Enable;  // разрешить подключение к выводу мк
     TIM_OCInitStructure2.TIM_Pulse = 0;  // длительность
     TIM_OCInitStructure2.TIM_OCPolarity = TIM_OCPolarity_High;  // положительная полярность
     TIM_OC2Init (TIM3, &TIM_OCInitStructure2);
  
  // разрешить предварительную загрузку регистра сравнения
     TIM_OC2PreloadConfig (TIM3, TIM_OCPreload_Enable); 
  
  // разрешаем предварительную загрузку регистра автоперезагрузки
     TIM_ARRPreloadConfig (TIM3, ENABLE); 

  // прерывание по переполнению
     TIM3->DIER |= TIM_DIER_UIE;  
    
  // разрешить прерывание  
     NVIC_EnableIRQ (TIM3_IRQn); 
}


/* ------------------------------------------------------------------------- */
/* --- деинициализация высоковольтного генератора  ------------------------- */
/* ------------------------------------------------------------------------- */
     
void generator_deinitialization (void) {
  
  // выключить высоковольтный генератор 
     GeneratorStop ();
 }


/* ------------------------------------------------------------------------- */
/* --- включить высоковольтный генератор  ---------------------------------- */
/* ------------------------------------------------------------------------- */

void GeneratorStart (void) {

  // переполнение напряжения : H - нет
     if (GPIO_ReadInputDataBit (GPIOB, GPIO_Pin_11)) {
 
     // состояние ВВГ: включен
        on_Generator = 1; 
   
     // включить таимер ВВГ
        TIM_Cmd (TIM3, ENABLE);
     }
}


/* ------------------------------------------------------------------------- */
/* --- выключить высоковольтный генератор  --------------------------------- */
/* ------------------------------------------------------------------------- */

void GeneratorStop (void) {
   
  // выключить таимер ВВГ
     TIM_Cmd (TIM3, DISABLE);
     
  // длительность импульса
     TIM3->CCR2 = 0;  
     
  // состояние ВВГ: выключен
     on_Generator = 0; 
}


/* ------------------------------------------------------------------------- */
/* --- прерывание по переполнению TIM3  ------------------------------------ */
/* ------------------------------------------------------------------------- */

void TIM3_IRQHandler (void) {
  
  // переполнение напряжения : H - нет
     if (GPIO_ReadInputDataBit (GPIOB, GPIO_Pin_11)) {
     
        GenImp ++;
     // длительность импульса
        TIM3->CCR2 = 1; 
     } 
     
  // переполнение напряжения : L - да
     else GeneratorStop ();  // выключить ВВГ

  // очистка регистра прерывания
     TIM3->SR &= ~TIM_SR_UIF;      
}
