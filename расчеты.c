
/* расчет значения радиации
   --------------------------------- */

void GetRadiation (void) {
  
     char Begin = Rad_array_cnt ? Rad_array_cnt - 1 : 119;
     int n = Begin;
     char TimeBegin;
     if (Rad_time > 60) TimeBegin = 60; else TimeBegin = Rad_time;
     char Time = TimeBegin * 2;
     double Res = 0;
     
  // до 60 сек.
     
     while (Time) {
     
       Res += Rad_array [n];
       Time --;
       if ((n--) == 0) break;
     }

     n = 119;
     while (Time) {
     
       Res += Rad_array [n];
       Time --;
       if ((n --) == 0) break;
     }
     
   // после 60 сек.
     
  if (Rad_time > 60) {
     
     n = Rad_array_Second_cnt - 60/5 - 1;
     n = n < 0 ? 199 + n : n;
     Time = (Rad_time - 60) / 5;
     while (Time) {
     
       Res += Rad_array_Second [n];
       Time --;
       if ((n--) == 0) break;
     }

     n = 199;
     while (Time) {
     
       Res += Rad_array_Second [n];
       Time --;
       if ((n --) == 0) break;
     }
  }
  
  // расчет значения 
  
     Res = Res / Rad_time / 10 * Geiger;
  
  // поправка на время после старта
     
     if (TimeRun < (Rad_time * 2)) {
     
       Res = (Rad_time * 2) * Res / (TimeRun - (TimeRun > 120 ? TimeRun % 10 : 0));
     }
     
  // итоговое значение 
 
     Rad = (int) Res > 99999 ? 99999 : (int) Res;     
}


/* накопленная доза в мкЗв
   --------------------------------- */

int GetDoseRadiation (void) {
  
  return (int) Dose * 2 * 10 / (60*60 * Geiger);
}