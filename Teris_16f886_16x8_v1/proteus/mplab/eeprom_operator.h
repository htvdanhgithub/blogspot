#if !WINDOW_BASE
void eeprom_write_int(uint8_t at, uint16_t value)
{
    uint8_t temp;
    temp = value >> 8;
    eeprom_write(at, temp);

    temp = value & 0xFF;
    eeprom_write(at + 1, temp);
    dbg_print1(DEBUG_DISABLE, "eeprom_write_int = %d", value);
}
uint16_t eeprom_read_int(uint8_t at)
{
    uint16_t value = 0;
    value = eeprom_read(at) << 8;
    value += eeprom_read(at + 1);
    dbg_print1(DEBUG_DISABLE, "eeprom_read_int = %d", value);
    return value;
}
#endif
