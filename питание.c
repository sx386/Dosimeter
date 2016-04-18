
/* ------------------------------------------------------------------------- */
/* ---  ������������ : �������������  -------------------------------------- */
/* ------------------------------------------------------------------------- */

void rcc_initialization (void) {
  
  // ��������� HSE ���������
     RCC_HSEConfig (RCC_HSE_OFF);
     
  // ������� ������������ 1 MHz
     RCC_MSIRangeConfig (RCC_MSIRange_4);  
       

  // �������� ������������ ���� ������
     RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOA, ENABLE);  // �������� ������������ PAx
     RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOB, ENABLE);  // �������� ������������ PBx
     RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOC, ENABLE);  // �������� ������������ PCx
     RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOD, ENABLE);  // �������� ������������ PDx
     RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOE, ENABLE);  // �������� ������������ PEx
     RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOH, ENABLE);  // �������� ������������ PHx
    
  // ������������ �������
     RCC_APB1PeriphClockCmd (RCC_APB1Periph_PWR, ENABLE); 
     
  // ������������ ��������� ����
     RCC_APB2PeriphClockCmd (RCC_APB2Periph_SYSCFG, ENABLE);  
}


/* ------------------------------------------------------------------------- */
/* ---  ����� "����" : ���������� ���������  ------------------------------- */
/* ------------------------------------------------------------------------- */

void STOP (void) {

     char _batt_low = Batt_Low_Power_Down;   
  
  
  // �������� ������� ������
     while (Button != 0);
     
  // ���������������
     de_initialization ();
   
  // --------- ������� ��������� ------------------
     
     if (_batt_low) {
       lcd_initialization (); // ������������� �������
       BattLowDraw ();
       // -----
       GPIO_InitTypeDef Port;
       Port.GPIO_OType = GPIO_OType_PP;  // ����������� ����� 
       Port.GPIO_Speed = GPIO_Speed_2MHz;  // �������� �������
       Port.GPIO_PuPd = GPIO_PuPd_NOPULL;  // ������������� ��������� ���������
       Port.GPIO_Mode = GPIO_Mode_OUT;  // �����
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
     
  // ��������
     noop (100000);
        
  // ���������� ��������� - ����� "����"
     PWR_EnterSTOPMode (PWR_Regulator_LowPower, PWR_STOPEntry_WFI); 
     
  // ��������
     noop (5000);
  
  // �������� ������� ������
     while (Button != 0);
 
  // �������� �������� ������ �� ������ "����"
     OnSTOP = 0; 
     
  // �������������
     initialization ();     
}

/* ------------------------------------------------------------------------- */
/* ---  ��������� ���������� �������  -------------------------------------- */
/* ------------------------------------------------------------------------- */

# define batt_charge_on GPIOA->BSRRL = GPIO_Pin_6
# define batt_charge_off GPIOA->BSRRH = GPIO_Pin_6

void batt_charge_initialization (void) {
  
  // ��� ������
     GPIO_InitTypeDef Port;

  // ��������� ������ �����-������
     Port.GPIO_OType = GPIO_OType_PP;  // ����������� ����� 
     Port.GPIO_Speed = GPIO_Speed_2MHz;  // �������� �������
     Port.GPIO_PuPd = GPIO_PuPd_NOPULL;  // ������������� ��������� ���������
     Port.GPIO_Mode = GPIO_Mode_OUT;  // �����
  
  // ������������ ��� ������
     Port.GPIO_Pin = GPIO_Pin_6;
  
  // ������������ �� ���� PAx
     GPIO_Init (GPIOA, &Port);
     
     
     batt_charge_on;

}
  

/* ------------------------------------------------------------------------- */
/* ---  ��������� ���������� �������  -------------------------------------- */
/* ------------------------------------------------------------------------- */

# define ionPortOn GPIOB->BSRRL = GPIO_Pin_13
# define ionPortOff GPIOB->BSRRH = GPIO_Pin_13

void on_BattGet (void) {
 
  
 // ���� ��������� �������� ����������
  GPIO_InitTypeDef GPIO_InitStructure7;
  GPIO_InitStructure7.GPIO_Pin = GPIO_Pin_14;  // ������������ ����
  GPIO_InitStructure7.GPIO_Speed = GPIO_Speed_40MHz;  // �������� �������
  GPIO_InitStructure7.GPIO_PuPd = GPIO_PuPd_NOPULL;  // ������������� ��������� ���������
  GPIO_InitStructure7.GPIO_Mode = GPIO_Mode_AIN;  // ���������� ����
  GPIO_Init (GPIOB, &GPIO_InitStructure7);
 
  // ���������� ���
  GPIO_InitTypeDef GPIO_InitStructure12;
  GPIO_InitStructure12.GPIO_Pin = GPIO_Pin_12;  // ������������ ����
  GPIO_InitStructure12.GPIO_Speed = GPIO_Speed_40MHz;  // �������� �������
  GPIO_InitStructure12.GPIO_PuPd = GPIO_PuPd_NOPULL;  // ������������� ��������� ���������
  GPIO_InitStructure12.GPIO_Mode = GPIO_Mode_AIN;  // ���������� ����
  GPIO_Init (GPIOB, &GPIO_InitStructure12);
 
  // ������� ����������
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;  // ������������ ����
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  // ����������� ����� 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  // �������� �������
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  // ������������� ��������� ���������
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  // �����
  GPIO_Init (GPIOB, &GPIO_InitStructure);
    
  // �������� ������� ����������
  ionPortOn;

      noop (500);

    // ���������� ������� ���� � Range 1
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
  
 // �������� ���������� ��������� HSI - 16 ���
     if ((RCC->CR&RCC_CR_HSIRDY) == 0) RCC->CR |= RCC_CR_HSION;
  
  // ���� ��� ������������
     while (!(RCC->CR&RCC_CR_HSIRDY));
     
  // ������������ ���
     RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; 
    
  // �������� ���
     ADC1->CR2 |= ADC_CR2_ADON; 
     
  // �������� ���������� ���     
     while ((ADC1->SR & ADC_SR_ADONS) == 0);   
     
  // ��������� ����������� �� 12 ���
     ADC1->CR1 &= ~ ADC_CR1_RES;
     
  // ������������ ���������� ������
     ADC1->CR2 &= ~ ADC_CR2_ALIGN;
     
  // � ����������� ��������� ��� ����� ����������� ������� �����������. 
  // ��� �������� ����������������� ���� ����������� ��������������� 
  // ���������� ������, ����� ��� ��������������. 
 
    // ADC1->CR1 |= ADC_PowerDown_Idle_Delay;     

  // ------------------------------------------------------------------
 // CH16 - �����������
// CH17 - �������� �������� ����������
    
     
 
     ADC_RegularChannelConfig (ADC1, ADC_Channel_18, 1, ADC_SampleTime_4Cycles);
     ADC1->CR2 |= ADC_CR2_SWSTART; //������ ��������������
     while ((ADC1->SR & ADC_SR_EOC) != ADC_SR_EOC) { }
     Vt = ADC1->DR >> 0; 
     
     int i;     
     for (i=0;i<n;i++) {
     
       ADC_RegularChannelConfig (ADC1, ADC_Channel_18, 1, ADC_SampleTime_4Cycles);
       ADC1->CR2 |= ADC_CR2_SWSTART; //������ ��������������
       while ((ADC1->SR & ADC_SR_EOC) != ADC_SR_EOC) { }
       Vbat += ADC1->DR >> 0; 
       
       ADC_RegularChannelConfig (ADC1, ADC_Channel_20, 1, ADC_SampleTime_4Cycles);
       ADC1->CR2 |= ADC_CR2_SWSTART; //������ ��������������
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
  
     
  // ��������� ���
     ADC1->CR2 &= ~ ADC_CR2_ADON; 
     
  // �������� ������������ ���
     RCC->APB2ENR &= ~RCC_APB2ENR_ADC1EN; 
    
  // ��������� HSI ���������
     RCC -> CR &= ~ RCC_CR_HSION; 
     
  // ��������� ������� ����������
     ionPortOff;

  // ------------------------------
    // ��������� ��������� ����������
       BattGet = 0;  
  
  if (Batt_Low_Power_Down == false) {
     
     if (V < Batt_min) {
       BattLow ++; 
       BattGet = 1;
     } 
     
     if (BattLow == 5) {
       Lcd_Led_off (); // ��������� ��������� �������
       Batt_Low_Power_Down = true;
       OnSTOP = 1;
     } 
       else noop (5000);
  }
}