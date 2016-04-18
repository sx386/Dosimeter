
/* ------------------------------------------------------------------------- */
/* ---  инициализация таимера времени  ------------------------------------- */
/* ------------------------------------------------------------------------- */

void time_initialization (void) {
  
 // разрешаем доступ к области резервных данных
     PWR_RTCAccessCmd (ENABLE); 
     
  // включаем генератор на внешнем кварце 32 кГц. 
     RCC_LSEConfig (RCC_LSE_ON);
 
  // ожидаем стабилизации
     while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET) {}
 
  // устанавливаем как источник тактирования для часов
     RCC_RTCCLKConfig (RCC_RTCCLKSource_LSE);
    
  // разрешаем тактирование
     RCC_RTCCLKCmd (ENABLE);
 
  // ожидаем синхронизации
     RTC_WaitForSynchro ();
     
  // настроика часов
     RTC_InitTypeDef RTC_InitStructure;
     RTC_InitStructure.RTC_AsynchPrediv = 0x7f;
     RTC_InitStructure.RTC_SynchPrediv = 0xff;
     RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
     RTC_Init (&RTC_InitStructure);
     
  // настроика линии прерывания
     EXTI_InitTypeDef EXTI_InitStructure;
     EXTI_ClearITPendingBit (EXTI_Line20);
     EXTI_InitStructure.EXTI_Line = EXTI_Line20;
     EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
     EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
     EXTI_InitStructure.EXTI_LineCmd = ENABLE;
     EXTI_Init(&EXTI_InitStructure);
 
  // настройка прерывания от часов
     NVIC_InitTypeDef NVIC_InitStructure;
     NVIC_InitStructure.NVIC_IRQChannel = RTC_WKUP_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init (&NVIC_InitStructure);
     
  // сonfigures the RTC Wakeup clock source.
     RTC_WakeUpClockConfig (RTC_WakeUpClock_RTCCLK_Div16);
  
  // сonfigures the RTC Wakeup counter
     RTC_SetWakeUpCounter (1024);
 
  // enable the RTC wakeup interrupt 
     RTC_ITConfig (RTC_IT_WUT, ENABLE);

  // Enable Wakeup Counter
     RTC_WakeUpCmd (ENABLE); 
}


/* ------------------------------------------------------------------------- */
/* ---  деинициализация таимера времени  ----------------------------------- */
/* ------------------------------------------------------------------------- */

void time_deinitialization (void) {
  
     RTC_DeInit ();
     
  // разрешаем доступ к области резервных данных
     PWR_RTCAccessCmd (ENABLE); 
     
  // Reset RTC and Backup registers
     RCC_RTCResetCmd(ENABLE);
     RCC_RTCResetCmd(DISABLE);

  // Disable the RTC wakeup interrupt 
     RTC_ITConfig (RTC_IT_WUT, DISABLE);
 
  // Disable Wakeup Counter /
     RTC_WakeUpCmd (DISABLE);   
     
  // очистить регистр :: часы
     RTC_ClearITPendingBit (RTC_IT_WUT);
  
  // очистить регистр :: прерывание
     EXTI_ClearITPendingBit (EXTI_Line20);

  // запрещаем тактирование
     RCC_RTCCLKCmd (DISABLE);
          
     
      // Выключить генератор можно только путем программного сброса:
//	RCC->BDCR |= RCC_BDCR_BDRST;
   //	RCC->BDCR &= ~RCC_BDCR_BDRST;

  // выключаем генератор на внешнем кварце 32 кГц. 
     RCC_LSEConfig (RCC_LSE_OFF);
     
     RTC_DeInit ();

}


/* ------------------------------------------------------------------------- */
/* ---  прерывание таимера времени  ---------------------------------------- */
/* ------------------------------------------------------------------------- */

void RTC_WKUP_IRQHandler  (void) {
  // запрещаем тактирование
     RCC_RTCCLKCmd (DISABLE);
     
  // остановить ВВГ
     GeneratorStop ();

  
  // -------------------------------------------
    
  //   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
     
  // поправка на время бездействия      
  //   RadiationCounter += RadiationCounter * RadiationPercent / 1000;    
     
  // очистить поправку на время бездействия     
  //   RadiationPercent = 0;  
          
     
  // поместить количество квантов в массив (0.5 сек)
     Rad_array [Rad_array_cnt] = Rad_counter;
     
  // поместить количество квантов в массив (5 сек)
     Rad_array_Second [Rad_array_Second_cnt] += Rad_counter;
  
  // увеличить индекс массива (0.5 сек)
     Rad_array_cnt = Rad_array_cnt < 119 ? Rad_array_cnt + 1 : 0;
     
  // каждые 5 сек.
     if (Rad_array_cnt % 10 == 0) {
       
     // увеличить индекс массива (5 сек) 
        Rad_array_Second_cnt = Rad_array_Second_cnt < 199 ? Rad_array_Second_cnt + 1 : 0;
        
     // очистить элемент массива 
        Rad_array_Second [Rad_array_Second_cnt] = 0;
     }
     
  // накопленная доза
     Dose += Rad_counter;
     
     
  // -------------------------------------------
      
  // очистка значений радиации и счетчика Led индикации
     Rad_counter = 0; Led_count = 0;
     
  // ------- разрешить вывод данных на дисплей --------------
     
     if (TimeButtonAct < 120*30) {     
       draw = 1;
     } 
     
     else        
     if (TimeButtonAct < 120*60*2) { 
        if (TimeCount % 2 == 0) draw = 1;       
     } 
     
     else { 
        if (TimeCount % 20 == 0) draw = 1;    
     }
     
  // ---- отключить звук и свет. индикацию -----
     
     if (TimeButtonAct > 120*60*3) {     
       if (on_Led || on_Sound) Led_Sound (false, false);         
     } 
    
     
  // -------- POWER DOWN -----------------------
     
     if (on_PowerDownTime) 
       if (TimeButtonAct > (PowerDownTime * 2)) OnSTOP = 1;
     
    
  // ------- подсветка дисплея -----------------
     
     if (TimeButtonAct == 1200) Lcd_Led_off ();
     
  // ------- первые 5 сек. после включения измерять напряжение каждые 0.5с -----------------
     
     if (TimeRun < 10) BattGet = 1;
     
  // -------------------------------------------
  
  // выполнение каждые 5 сек
     if (TimeCount % 10 == 0) on_time_5_sec ();
     
  // выполнение каждые 10 сек
     if (TimeCount % 20 == 0) on_time_10_sec ();
     
  // счетчик для часов   
     if (TimeCount ++ == 119) TimeCount = 0;
     
  // счетчик по 0.5 сек. после включения   
     TimeRun ++;

  // счетчик после последнего нажатия на кнопку
     TimeButtonAct ++;
     
// ---------------------
   // 0: кнопка активна; (1... - количество по 0,5с. неактивности кнопки)   
      if (ButtonDisable) ButtonDisable--; 
     
// --------------------------------------
         
     // очистить значение импульсов накачки
        GenImpDraw = GenImp;
        GenImp = 0;

// --------------------------------------     
    
   // разрешаем тактирование
     RCC_RTCCLKCmd (ENABLE);
     
  // очистить регистр :: часы
     RTC_ClearITPendingBit (RTC_IT_WUT);
  
  // очистить регистр :: прерывание
     EXTI_ClearITPendingBit (EXTI_Line20);
}


/* ------------------------------------------------------------------------- */
/* ---  выполнение каждые 5 сек  ------------------------------------------- */
/* ------------------------------------------------------------------------- */

void on_time_5_sec (void) {
  
  // --------- ALARM ---------------------------

   if (TimeRun > 20) 
     if (on_alarm) 
       if (Rad > alarm) {
         
         // питание 3,3В вкл.
            Power33on;
         
         if (Rad < 1000) {
           noop (6000);
           Beep (30, 200); noop (6000);
           Beep (30, 200); noop (6000);
         } else 
         if (Rad < 10000) {
           noop (6000);
           Beep (30, 200); noop (6000);
           Beep (30, 200); noop (6000);
           Beep (30, 200); noop (6000);
         } else {
           noop (6000);
           Beep (30, 200); noop (6000);
           Beep (30, 200); noop (6000);
           Beep (30, 200); noop (6000);
           Beep (30, 200); noop (6000);
         }
     }
  
  // включить высоковольтный генератор
     GeneratorStart ();
}



/* ------------------------------------------------------------------------- */
/* ---  выполнение каждые 10 сек  ------------------------------------------ */
/* ------------------------------------------------------------------------- */

void on_time_10_sec (void) {
  
  // разрешить измерение напряжения
     BattGet = 1;  
}