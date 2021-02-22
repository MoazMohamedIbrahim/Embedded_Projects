#include "Main.h"
#include "Port.h"
#include "Util.h"
#include "LCD.h"

#define LCD_CONFIG_WORD             (0x30)

#define LCD_CLR                     (0x01)

#define LCD_CURSOR_HOME             (0x02)

#define LCD_SET_ENTRY_MODE          (0x40)
#define LCD_INCREMENT_CURSOR        (0x02)
#define LCD_DECREMENT_CURSOR        (0x00)
#define LCD_DISPLAY_SHIFT_ON        (0x01)
#define LCD_DISPLAY_SHIFT_OFF       (0x00)

#define LCD_DISPLAY_CONTROL         (0x08)
#define LCD_DISPLAY_ON              (0x04)
#define LCD_DISPLAY_OFF             (0x00)
#define LCD_CURSOR_ON               (0x02)
#define LCD_CURSOR_OFF              (0x00)
#define LCD_CURSOR_BLINK_ON         (0x01)
#define LCD_CURSOR_BLINK_OFF        (0x00)

#define LCD_CURSOR_DISPLAY_CONTROL  (0x10)
#define LCD_SHIFT_CURSOR            (0x00)
#define LCD_SHIFT_DISPLAY           (0x08)
#define LCD_SHIFT_LEFT              (0x00)
#define LCD_SHIFT_RIGHT             (0x04)

#define LCD_FUNCTION_SET            (0x20)
#define LCD_DATA_LENGTH_4           (0x00)
#define LCD_DATA_LENGTH_8           (0x10)
#define LCD_ONE_LINE                (0x00)
#define LCD_TWO_LINES               (0x08)
#define LCD_SMALL_FONT              (0x00)
#define LCD_LARGE_FONT              (0x04)

#define LCD_SET_CGRAM_ADDRESS       (0x40)
#define LCD_SET_DDRAM_ADDRESS       (0x80)

#define LCD_LINE_SIZE               (0x28)
#define LCD_LINE_2_ADDRESS          (0x40)

static void LCD_SendCommand(tByte command);
static void LCD_GoTo(tByte line, tByte column);
static void LCD_SendData(tByte character);

void LCD_Init(void)
{
       /* Initialize Pins */
    GPIO_InitPort(LCD_DATA_PORT_CR, GPIO_OUT);
    GPIO_WritePort(LCD_DATA_PORT_DR, 0);
    GPIO_InitPortPin(LCD_RS_CR, LCD_RS_PIN, GPIO_OUT);
    GPIO_InitPortPin(LCD_E_CR, LCD_E_PIN, GPIO_OUT);
    GPIO_WritePortPin(LCD_RS_DR, LCD_RS_PIN, 0);
    GPIO_WritePortPin(LCD_E_DR, LCD_E_PIN, 0);

    /* Initialization sequence */
    Delay_MS(20);
    LCD_SendCommand(LCD_CONFIG_WORD);
    Delay_MS(5);
    LCD_SendCommand(LCD_CONFIG_WORD);
    Delay_MS(1);
    LCD_SendCommand(LCD_CONFIG_WORD);

    /* Initial LCD commands */
    /* Select data length = 8 bits, 2 lines LCD and small font */
    LCD_SendCommand(LCD_FUNCTION_SET|LCD_DATA_LENGTH_8|LCD_TWO_LINES|LCD_SMALL_FONT);
    /* Turn display , cursor and blinking OFF */
    LCD_SendCommand(LCD_DISPLAY_CONTROL|LCD_DISPLAY_OFF|LCD_CURSOR_OFF|LCD_CURSOR_BLINK_OFF);
    /* Clear LCD */
    LCD_SendCommand(LCD_CLR);
    /* Increment cursor and turn off display shift */
    LCD_SendCommand(LCD_SET_ENTRY_MODE|LCD_INCREMENT_CURSOR|LCD_DISPLAY_SHIFT_OFF);
    /* Turn display ON */
    LCD_SendCommand(LCD_DISPLAY_CONTROL|LCD_DISPLAY_ON|LCD_CURSOR_OFF|LCD_CURSOR_BLINK_OFF);

   
}
void LCD_SendChar(tByte character, tByte line, tByte column)
{
   
    /* Change position and send character */
    LCD_GoTo(line, column);
    LCD_SendData(character);
   

}

void LCD_SendString(tByte line,tByte * str)
{
    tByte i = 0;

    
    /* Clear screen and send character by character to the LCD */
    if (line == LCD_LINE_1)
    {
        LCD_SendCommand(LCD_CLR);
    }


    while (str[i] != '\0')
    {
        LCD_SendChar(str[i], line, i);
        i++;
    }

}

static void LCD_SendCommand(tByte command)
{
 
    GPIO_WritePortPin(LCD_E_DR, LCD_E_PIN, 1);
    GPIO_WritePort(LCD_DATA_PORT_DR, command);
    GPIO_WritePortPin(LCD_RS_DR, LCD_RS_PIN, 0);
    GPIO_WritePortPin(LCD_E_DR, LCD_E_PIN, 0);
    GPIO_WritePortPin(LCD_E_DR, LCD_E_PIN, 1);
 
}

static void LCD_SendData(tByte character)
{
 
    GPIO_WritePortPin(LCD_E_DR, LCD_E_PIN, 1);
    GPIO_WritePort(LCD_DATA_PORT_DR, character);
    GPIO_WritePortPin(LCD_RS_DR, LCD_RS_PIN,1);
    GPIO_WritePortPin(LCD_E_DR, LCD_E_PIN, 0);
    GPIO_WritePortPin(LCD_E_DR, LCD_E_PIN, 1);
  
}

static void LCD_GoTo(tByte line, tByte column)
{
    tByte address = 0;
    /* Calculate address in DDRAM */
    address = (line * LCD_LINE_2_ADDRESS) + column;

    /* Send address to LCD */
    LCD_SendCommand(LCD_SET_DDRAM_ADDRESS|address);
  

}


