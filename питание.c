
/* ------------------------------------------------------------------------- */
/* ---  тактирование : инициализация  -------------------------------------- */
/* ------------------------------------------------------------------------- */

void rcc_initialization (void) {
  
  // отключить HSE генератор
     RCC_HSEConfig (RCC_HSE_OFF);
     
  // частота тактирования 1 MHz
     RCC_MSIRangeConfig (RCC_MSIRange_4);  
       

  // включить тактирование всех портов
     RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOA, ENABLE);  // включить тактирование PAx
     RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOB, ENABLE);  // включить тактирование PBx
     RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOC, ENABLE);  // включить тактирование PCx
     RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOD, ENABLE);  // включить тактирование PDx
     RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOE, ENABLE);  // включить тактирование PEx
     RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOH, ENABLE);  // включить тактирование PHx
    
  // тактирование питания
     RCC_APB1PeriphClockCmd (RCC_APB1Periph_PWR, ENABLE); 
     
  // тактирование системнои шины
     RCC_APB2PeriphClockCmd (RCC_APB2Periph_SYSCFG, ENABLE);  
}


/* ------------------------------------------------------------------------- */
/* ---  режим "СТОП" : выключение дозиметра  ------------------------------- */
/* ------------------------------------------------------------------------- */

void STOP (void) {

     char _batt_low = Batt_Low_Power_Down;   
  
  
  // ожидание отжатия кнопки
     while (Button != 0);
     
  // деинициализация
     de_initialization ();
   
  // --------- батарея разряжена ------------------
     
     if (_batt_low) {
       lcd_initialization (); // инициализация дисплея
       BattLowDraw ();
       // -----
       GPIO_InitTypeDef Port;
       Port.GPIO_OType = GPIO_OType_PP;  // двухтактный выход 
       Port.GPIO_Speed = GPIO_Speed_2MHz;  // тактовая частота
       Port.GPIO_PuPd = GPIO_PuPd_NOPULL;  // подтягивающие резисторы отключены
       Port.GPIO_Mode = GPIO_Mode_OUT;  // выход
       Port.GPIO_Pin = GPIO_Pin_15;
       GPIO_Init (GPIOB, &Port);
       // -----
       Power33on;
       int i = 0;
       for (i=0; i<5; i++) {
         GPIOB->BSRRL = GPIO_Pin_15;
         noop (100);
         GPIOB->BSRRH = GPIO_Pin_15;
         noop (100000);
       }
       de_initialization ();
     }
     
  // ----------------------------------------------
     
  // ожидание
     noop (100000);
        
  // выключение дозиметра - режим "стоп"
     PWR_EnterSTOPMode (PWR_Regulator_LowPower, PWR_STOPEntry_WFI); 
     
  // ожидание
     noop (5000);
  
  // ожидание отжатия кнопки
     while (Button != 0);
 
  // очистить значение выхода из режима "стоп"
     OnSTOP = 0; 
     
  // инициализация
     initialization ();     
}

/* ------------------------------------------------------------------------- */
/* ---  измерение напряжения питания  -------------------------------------- */
/* ------------------------------------------------------------------------- */

# define batt_charge_on GPIOA->BSRRL = GPIO_Pin_6
# define batt_charge_off GPIOA->BSRRH = GPIO_Pin_6

void batt_charge_initialization (void) {
  
  // тип данных
     GPIO_InitTypeDef Port;

  // настроика портов ввода-вывода
     Port.GPIO_OType = GPIO_OType_PP;  // двухтактный выход 
     Port.GPIO_Speed = GPIO_Speed_2MHz;  // тактовая частота
     Port.GPIO_PuPd = GPIO_PuPd_NOPULL;  // подтягивающие резисторы отключены
     Port.GPIO_Mode = GPIO_Mode_OUT;  // выход
  
  // использовать для портов
     Port.GPIO_Pin = GPIO_Pin_6;
  
  // использовать на шине PAx
     GPIO_Init (GPIOA, &Port);
     
     
     batt_charge_on;

}
  

/* ------------------------------------------------------------------------- */
/* ---  измерение напряжения питания  -------------------------------------- */
/* ------------------------------------------------------------------------- */

# define ionPortOn GPIOB->BSRRL = GPIO_Pin_13
# define ionPortOff GPIOB->BSRRH = GPIO_Pin_13

void on_BattGet (void) {
 
  
 // порт измерения опорного напряжения
  GPIO_InitTypeDef GPIO_InitStructure7;
  GPIO_InitStructure7.GPIO_Pin = GPIO_Pin_14;  // использовать порт
  GPIO_InitStructure7.GPIO_Speed = GPIO_Speed_40MHz;  // тактовая частота
  GPIO_InitStructure7.GPIO_PuPd = GPIO_PuPd_NOPULL;  // подтягивающие резисторы отключены
  GPIO_InitStructure7.GPIO_Mode = GPIO_Mode_AIN;  // аналоговыи вход
  GPIO_Init (GPIOB, &GPIO_InitStructure7);
 
  // напряжения АКБ
  GPIO_InitTypeDef GPIO_InitStructure12;
  GPIO_InitStructure12.GPIO_Pin = GPIO_Pin_12;  // использовать порт
  GPIO_InitStructure12.GPIO_Speed = GPIO_Speed_40MHz;  // тактовая частота
  GPIO_InitStructure12.GPIO_PuPd = GPIO_PuPd_NOPULL;  // подтягивающие резисторы отключены
  GPIO_InitStructure12.GPIO_Mode = GPIO_Mode_AIN;  // аналоговыи вход
  GPIO_Init (GPIOB, &GPIO_InitStructure12);
 
  // опорное напряжения
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;  // использовать порт
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  // двухтактный выход 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  // тактовая частота
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  // подтягивающие резисторы отключены
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  // выход
  GPIO_Init (GPIOB, &GPIO_InitStructure);
    
  // включить опорное напряжение
  ionPortOn;

      noop (500);

    // установить питание ядра в Range 1
     PWR_VoltageScalingConfig (PWR_VoltageScaling_Range1); 
 
  unsigned long int Vop = 0;
  unsigned long int Vbat = 0;
  unsigned long int V = 0;
  unsigned int Vt = 0;
  int n = 16;

    
  // ENABLE VREFINT
   //  ADC_TempSensorVrefintCmd (ENABLE);  
  //   ADC_EOCOnEachRegularChannelCmd (ADC1, ENABLE);
  //   ADC_ITConfig (ADC1, ADC_IT_EOC, ENABLE);
  
 // включаем внутренний генератор HSI - 16 МГц
     if ((RCC->CR&RCC_CR_HSIRDY) == 0) RCC->CR |= RCC_CR_HSION;
  
  // ждем его стабилизации
     while (!(RCC->CR&RCC_CR_HSIRDY));
     
  // тактирование АЦП
     RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; 
    
  // включить АЦП
     ADC1->CR2 |= ADC_CR2_ADON; 
     
  // ожидание готовности АЦП     
     while ((ADC1->SR & ADC_SR_ADONS) == 0);   
     
  // установка разрядности на 12 бит
     ADC1->CR1 &= ~ ADC_CR1_RES;
     
  // выравнивание результата вправо
     ADC1->CR2 &= ~ ADC_CR2_ALIGN;
     
  // В выключенном состоянии АЦП имеет практически нулевое потребление. 
  // Для снижения энергопотребления есть возможность принудительного 
  // отключения модуля, когда нет преобразований. 
 
    // ADC1->CR1 |= ADC_PowerDown_Idle_Delay;     

  // ------------------------------------------------------------------
 // CH16 - ТЕРМОДАТЧИК
// CH17 - ИСТОЧНИК ОПОРНОГО НАПРЯЖЕНИЯ
    
     
 
     ADC_RegularChannelConfig (ADC1, ADC_Channel_18, 1, ADC_SampleTime_4Cycles);
     ADC1->CR2 |= ADC_CR2_SWSTART; //Запуск преобразования
     while ((ADC1->SR & ADC_SR_EOC) != ADC_SR_EOC) { }
     Vt = ADC1->DR >> 0; 
     
     int i;     
     for (i=0;i<n;i++) {
     
       ADC_RegularChannelConfig (ADC1, ADC_Channel_18, 1, ADC_SampleTime_4Cycles);
       ADC1->CR2 |= ADC_CR2_SWSTART; //Запуск преобразования
       while ((ADC1->SR & ADC_SR_EOC) != ADC_SR_EOC) { }
       Vbat += ADC1->DR >> 0; 
       
       ADC_RegularChannelConfig (ADC1, ADC_Channel_20, 1, ADC_SampleTime_4Cycles);
       ADC1->CR2 |= ADC_CR2_SWSTART; //Запуск преобразования
       while ((ADC1->SR & ADC_SR_EOC) != ADC_SR_EOC) { }
       Vop += ADC1->DR >> 0; 
     }

     Vbat /= n;
     Vop /= n;
 

  // ------------------------------------------------------------------
    // 3.007 - 1.443
     V = (Vbat*1000)/Vop;
     V = 61348*V/10000 - 3061;
     V /= 10;
     if (V > 500) V = 500;
     
     Batt = V;
     
     Vt = V;
     if (Vt > Batt_max) Vt = Batt_max;
     if (Vt < Batt_min) Vt = Batt_min; 
     BattPercent = 27 - (Vt - Batt_min) * 27 / (Batt_max - Batt_min);
     
    
  // ------------------------------------------------------------------
  
     
  // выключить АЦП
     ADC1->CR2 &= ~ ADC_CR2_ADON; 
     
  // выключть тактирование АЦП
     RCC->APB2ENR &= ~RCC_APB2ENR_ADC1EN; 
    
  // отключить HSI генератор
     RCC -> CR &= ~ RCC_CR_HSION; 
     
  // выключить опорное напряжение
     ionPortOff;

  // ------------------------------
    // запретить измерение напряжения
       BattGet = 0;  
  
  if (Batt_Low_Power_Down == false) {
     
     if (V < Batt_min) {
       BattLow ++; 
       BattGet = 1;
     } 
     
     if (BattLow == 5) {
       Lcd_Led_off (); // выключить подсветку дисплея
       Batt_Low_Power_Down = true;
       OnSTOP = 1;
     } 
       else noop (5000);
  }
}