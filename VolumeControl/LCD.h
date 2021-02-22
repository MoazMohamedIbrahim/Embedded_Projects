#ifndef __LCD_H__
#define __LCD_H__

#define LCD_LINE_1          (0)
#define LCD_LINE_2          (1)
#define LCD_LINE_WIDTH      (16)

void LCD_Init(void);
void LCD_SendChar(tByte character, tByte line, tByte column);
void LCD_SendString(tByte line, tByte * str);


#endif // __LCD_H__
