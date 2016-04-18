
/* ------------------------------------------------------------------------- */
/* ---  ������������� ������� �������  ------------------------------------- */
/* ------------------------------------------------------------------------- */

void time_initialization (void) {
  
 // ��������� ������ � ������� ��������� ������
     PWR_RTCAccessCmd (ENABLE); 
     
  // �������� ��������� �� ������� ������ 32 ���. 
     RCC_LSEConfig (RCC_LSE_ON);
 
  // ������� ������������
     while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET) {}
 
  // ������������� ��� �������� ������������ ��� �����
     RCC_RTCCLKConfig (RCC_RTCCLKSource_LSE);
    
  // ��������� ������������
     RCC_RTCCLKCmd (ENABLE);
 
  // ������� �������������
     RTC_WaitForSynchro ();
     
  // ��������� �����
     RTC_InitTypeDef RTC_InitStructure;
     RTC_InitStructure.RTC_AsynchPrediv = 0x7f;
     RTC_InitStructure.RTC_SynchPrediv = 0xff;
     RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
     RTC_Init (&RTC_InitStructure);
     
  // ��������� ����� ����������
     EXTI_InitTypeDef EXTI_InitStructure;
     EXTI_ClearITPendingBit (EXTI_Line20);
     EXTI_InitStructure.EXTI_Line = EXTI_Line20;
     EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
     EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
     EXTI_InitStructure.EXTI_LineCmd = ENABLE;
     EXTI_Init(&EXTI_InitStructure);
 
  // ��������� ���������� �� �����
     NVIC_InitTypeDef NVIC_InitStructure;
     NVIC_InitStructure.NVIC_IRQChannel = RTC_WKUP_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init (&NVIC_InitStructure);
     
  // �onfigures the RTC Wakeup clock source.
     RTC_WakeUpClockConfig (RTC_WakeUpClock_RTCCLK_Div16);
  
  // �onfigures the RTC Wakeup counter
     RTC_SetWakeUpCounter (1024);
 
  // enable the RTC wakeup interrupt 
     RTC_ITConfig (RTC_IT_WUT, ENABLE);

  // Enable Wakeup Counter
     RTC_WakeUpCmd (ENABLE); 
}


/* ------------------------------------------------------------------------- */
/* ---  ��������������� ������� �������  ----------------------------------- */
/* ------------------------------------------------------------------------- */

void time_deinitialization (void) {
  
     RTC_DeInit ();
     
  // ��������� ������ � ������� ��������� ������
     PWR_RTCAccessCmd (ENABLE); 
     
  // Reset RTC and Backup registers
     RCC_RTCResetCmd(ENABLE);
     RCC_RTCResetCmd(DISABLE);

  // Disable the RTC wakeup interrupt 
     RTC_ITConfig (RTC_IT_WUT, DISABLE);
 
  // Disable Wakeup Counter /
     RTC_WakeUpCmd (DISABLE);   
     
  // �������� ������� :: ����
     RTC_ClearITPendingBit (RTC_IT_WUT);
  
  // �������� ������� :: ����������
     EXTI_ClearITPendingBit (EXTI_Line20);

  // ��������� ������������
     RCC_RTCCLKCmd (DISABLE);
          
     
      // ��������� ��������� ����� ������ ����� ������������ ������:
//	RCC->BDCR |= RCC_BDCR_BDRST;
   //	RCC->BDCR &= ~RCC_BDCR_BDRST;

  // ��������� ��������� �� ������� ������ 32 ���. 
     RCC_LSEConfig (RCC_LSE_OFF);
     
     RTC_DeInit ();

}


/* ------------------------------------------------------------------------- */
/* ---  ���������� ������� �������  ---------------------------------------- */
/* ------------------------------------------------------------------------- */

void RTC_WKUP_IRQHandler  (void) {
  // ��������� ������������
     RCC_RTCCLKCmd (DISABLE);
     
  // ���������� ���
     GeneratorStop ();

  
  // -------------------------------------------
    
  //   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
     
  // �������� �� ����� �����������      
  //   RadiationCounter += RadiationCounter * RadiationPercent / 1000;    
     
  // �������� �������� �� ����� �����������     
  //   RadiationPercent = 0;  
          
     
  // ��������� ���������� ������� � ������ (0.5 ���)
     Rad_array [Rad_array_cnt] = Rad_counter;
     
  // ��������� ���������� ������� � ������ (5 ���)
     Rad_array_Second [Rad_array_Second_cnt] += Rad_counter;
  
  // ��������� ������ ������� (0.5 ���)
     Rad_array_cnt = Rad_array_cnt < 119 ? Rad_array_cnt + 1 : 0;
     
  // ������ 5 ���.
     if (Rad_array_cnt % 10 == 0) {
       
     // ��������� ������ ������� (5 ���) 
        Rad_array_Second_cnt = Rad_array_Second_cnt < 199 ? Rad_array_Second_cnt + 1 : 0;
        
     // �������� ������� ������� 
        Rad_array_Second [Rad_array_Second_cnt] = 0;
     }
     
  // ����������� ����
     Dose += Rad_counter;
     
     
  // -------------------------------------------
      
  // ������� �������� �������� � �������� Led ���������
     Rad_counter = 0; Led_count = 0;
     
  // ------- ��������� ����� ������ �� ������� --------------
     
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
     
  // ---- ��������� ���� � ����. ��������� -----
     
     if (TimeButtonAct > 120*60*3) {     
       if (on_Led || on_Sound) Led_Sound (false, false);         
     } 
    
     
  // -------- POWER DOWN -----------------------
     
     if (on_PowerDownTime) 
       if (TimeButtonAct > (PowerDownTime * 2)) OnSTOP = 1;
     
    
  // ------- ��������� ������� -----------------
     
     if (TimeButtonAct == 1200) Lcd_Led_off ();
     
  // ------- ������ 5 ���. ����� ��������� �������� ���������� ������ 0.5� -----------------
     
     if (TimeRun < 10) BattGet = 1;
     
  // -------------------------------------------
  
  // ���������� ������ 5 ���
     if (TimeCount % 10 == 0) on_time_5_sec ();
     
  // ���������� ������ 10 ���
     if (TimeCount % 20 == 0) on_time_10_sec ();
     
  // ������� ��� �����   
     if (TimeCount ++ == 119) TimeCount = 0;
     
  // ������� �� 0.5 ���. ����� ���������   
     TimeRun ++;

  // ������� ����� ���������� ������� �� ������
     TimeButtonAct ++;
     
// ---------------------
   // 0: ������ �������; (1... - ���������� �� 0,5�. ������������ ������)   
      if (ButtonDisable) ButtonDisable--; 
     
// --------------------------------------
         
     // �������� �������� ��������� �������
        GenImpDraw = GenImp;
        GenImp = 0;

// --------------------------------------     
    
   // ��������� ������������
     RCC_RTCCLKCmd (ENABLE);
     
  // �������� ������� :: ����
     RTC_ClearITPendingBit (RTC_IT_WUT);
  
  // �������� ������� :: ����������
     EXTI_ClearITPendingBit (EXTI_Line20);
}


/* ------------------------------------------------------------------------- */
/* ---  ���������� ������ 5 ���  ------------------------------------------- */
/* ------------------------------------------------------------------------- */

void on_time_5_sec (void) {
  
  // --------- ALARM ---------------------------

   if (TimeRun > 20) 
     if (on_alarm) 
       if (Rad > alarm) {
         
         // ������� 3,3� ���.
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
  
  // �������� �������������� ���������
     GeneratorStart ();
}



/* ------------------------------------------------------------------------- */
/* ---  ���������� ������ 10 ���  ------------------------------------------ */
/* ------------------------------------------------------------------------- */

void on_time_10_sec (void) {
  
  // ��������� ��������� ����������
     BattGet = 1;  
}