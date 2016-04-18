

/* �������� ������ � ����������������� ������
   ---------------------------------------- */
     
void RomSave (void) {
  
  DATA_EEPROM_Unlock ();
  FLASH_ErasePage (0x08080000);
  DATA_EEPROM_FastProgramWord (0x08080000, (uint32_t) Geiger);
  DATA_EEPROM_Lock ();
}

/* ������ �������� �� EEPROM
   ---------------------------------------- */

uint32_t RomAddress (uint32_t address) {

  return (*(__IO uint32_t*) address);
}


/* ������ ������ �� EEPROM ������
   ---------------------------------------- */

void rom_read (void) {

  if (RomAddress (0x08080000) != 0) Geiger = RomAddress (0x08080000);
}


