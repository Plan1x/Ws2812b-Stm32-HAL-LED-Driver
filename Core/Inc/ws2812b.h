/*
 * ws2812b.h
 *
 *  Created on: Jul 26, 2024
 *      Author: irubt
 */

#ifndef INC_WS2812B_H_
#define INC_WS2812B_H_

/* Includes ------------------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "main.h"
#include "stdbool.h"
#include "math.h"
#include "memory.h"

#define STM32F1

#ifdef STM32F1
    #include "stm32f1xx_hal_conf.h"

#elif defined(STM32F2)
    #include "stm32f2xx_hal_conf.h"

#elif defined(STM32F3)
    #include "stm32f3xx_hal_conf.h"

#elif defined(STM32F4)
    #include "stm32f4xx_hal_conf.h"

#elif defined(STM32F7)
    #include "stm32f7xx_hal_conf.h"

#elif defined(STM32H7)
    #include "stm32h7xx_hal_conf.h"

#elif defined(STM32L0)
    #include "stm32l0xx_hal_conf.h"

#elif defined(STM32L1)
    #include "stm32l1xx_hal_conf.h"

#elif defined(STM32L4)
    #include "stm32l4xx_hal_conf.h"

#elif defined(STM32L5)
    #include "stm32l5xx_hal_conf.h"

#elif defined(STM32G0)
    #include "stm32g0xx_hal_conf.h"

#elif defined(STM32G4)
    #include "stm32g4xx_hal_conf.h"

#elif defined(STM32WB)
    #include "stm32wbxx_hal_conf.h"

#elif defined(STM32WL)
    #include "stm32wlxx_hal_conf.h"

#elif defined(STM32MP1)
    #include "stm32mp1xx_hal_conf.h"

#endif

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
/* USER CODE END PTD */



/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */



#define PIXELS_COUNT 120 // Changeable parameter(number of pixels in your led strip)



#define DWT_CONTROL *(volatile unsigned long *)0xE0001000
#define SCB_DEMCR   *(volatile unsigned long *)0xE000EDFC



#define BITS_IN_PIXEL 24
#define BYTE 8

#define TIME_TO_RST 50 // Should be greater than 50 us

#define LEDS_COUNT (PIXELS_COUNT * BITS_IN_PIXEL) + TIME_TO_RST

/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */



/*
 * ENUMS
 */
typedef enum
{
	PERIOD = 90 - 1,
	LOGIC_ZERO = 26 - 1, // in ns
	LOGIC_ONE = 65 - 1 // in ns

} Led_states;

typedef enum
{
	GREEN = 0,
	RED = 1,
	BLUE = 2

}Colors;

typedef enum {
    HUE_RED = 0,       ///< Red (0°)
    HUE_ORANGE = 35,   ///< Orange (45°)
    HUE_YELLOW = 52,   ///< Yellow (90°)
    HUE_GREEN = 93,    ///< Green (135°)
    HUE_AQUA = 128,    ///< Aqua (180°)
    HUE_BLUE = 230,    ///< Blue (225°)
    HUE_PURPLE = 263,  ///< Purple (270°)
    HUE_PINK = 300     ///< Pink (315°)
} HSVHue_RAINBOW_PALETTE;
typedef enum
{
	HUE_DEEP_BLUE = 224,
	HUE_DEEP_YELLOW = 55
}HSVHue_UKRAINIAN_FLAG_PALETTE;

/*
 * ENUMS
 */

/*
 * STRUCTS
 */
typedef struct
{
	U8 Red;
	U8 Green;
	U8 Blue;

}RGB;

typedef struct
{
	U8 buffer[LEDS_COUNT];
	TIM_HandleTypeDef * htim1;
	TIM_TypeDef * TIM;

}WS2812_hw;

typedef struct
{
	U16 Hue; // Hue >= 0 deg є Hue <= 360 deg
	U8 Saturation; // Saturation >= 0% є Saturation <= 100%
	U8 Value; // Value >= 0% є Value <= 100% (Brightness)

}HSV;

typedef struct
{
	const HSV * parr;
	size_t size;
}Palette_HSV;

typedef struct
{
	const RGB * parr;
	size_t size;
}Palette_RGB;

typedef struct
{
	void (*Init)(TIM_HandleTypeDef *  htim, TIM_TypeDef * TIM);
	void (*Set_pixel_RGB)(RGB * Col, U16 Pixelnum);
	void (*Set_pixel_HSV)(HSV * Col, U16 Pixelnum);
	void (*Setstrip)(RGB *_Col);
	void (*Moving_effect_two_colors)(RGB *_Col_1, RGB * _Col_2,  U16 Delay);
//	void (*Moving_effect_three_colors)(RGB *_Col_1, RGB * _Col_2, RGB * _Col_3, U16 Delay);
	void (*Sliding_effect)(RGB *_Col_1, RGB * _Col_2, RGB * _Col_3, U16 Delay);
	void (*Moving_and_vanishing_effect)(RGB *_Col_1, RGB * _Col_2, U16 Delay);
	void (*Custom_Palette_HSV)(Palette_HSV * _palette, U8 palettes_num, U16 Delay);
	void (*Custom_Palette_RGB)(Palette_RGB * _palette, U8 palettes_num, U16 Delay);
	void (*Delay_in_us)(U32 us);
	void (*Show)(U16 Delay);

}WS2812;


/*
 * STRUCTS
 */

/* USER CODE END PV */


/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */


/*
 * Description : Initializes the Strip structure fields
 *
 * Prototype : void Ws2812b_Init(TIM_HandleTypeDef * htim, TIM_TypeDef * TIM);
 *
 * Parameters :
 *
 * TIM_HandleTypeDef * htim - Pointer to a TIM_HandleTypeDef structure object
 *
 * TIM_TypeDef * TIM - Pointer to a TIM_TypeDef structure object
 */

void Ws2812b_Init(TIM_HandleTypeDef *  htim, TIM_TypeDef * TIM);

/*
 * Description : Lights up specified pixel with specified color in RGB format
 *
 * Prototype : void Ws2812b_SetPixel_RGB(Color * Col, U16 Pixelnum);
 *
 * Parameters :
 *
 * Color *_Col - Pointer to a Color structure object which contains three fields :
 *
 * U8 Green - Sets the brightness of Green color led from 0 to 255
 *
 * U8 Red - Sets the brightness of Red color led from 0 to 255
 *
 * U8 Blue - Sets the brightness of Blue color led from 0 to 255
 *
 *
 * U8 Pixelnum - The number of the pixel you want to light
 *
 * !! Pixel numbering starts from zero. This means that if you want to light the first pixel, you must pass zero as the Pixelnum parameter.
 * Therefore, the index of the last pixel: Pixelnum = (number of pixels - 1) !!
 */

void Ws2812b_SetPixel_RGB(RGB * Col, U16 Pixelnum);

/*
 * Description : Lights up specified pixel with specified color in HSV format
 *
 * Prototype : void Ws2812b_SetPixel_HSV(HSV * Col, U16 Pixelnum);
 *
 * Parameters :
 *
 * HSV * Col - Pointer to a HSV structure object which contains three fields :
 *
 * U16 Hue - Sets Hue from 0 to 360 degrees
 *
 * U8 Saturation - Sets Saturation from 0% to 100%
 *
 * U8 Value - Sets brightness from 0% to 100%
 *
 * About HSV : https://en.wikipedia.org/wiki/HSL_and_HSV
 *
 */

void Ws2812b_SetPixel_HSV(HSV * Col, U16 Pixelnum);

 /*
  * Description : Lights up the whole strip with specified color in RGB format
  *
  * Prototype : void Ws2812b_SetStrip(Color *_Col);
  *
  * Parameters :
  *
  *	Color *_Col - Pointer to a Color structure object which contains three fields :
  *
  *	U8 Red - Sets the brightness of Red color in the whole stripe from 0 to 255
  *
  * U8 Green - Sets the brightness of Green color in the whole stripe from 0 to 255
  *
  * U8 Blue - Sets the brightness of Blue color in the whole stripe from 0 to 255
  *
  */

void Ws2812b_SetStrip(RGB *_Col);

/*
 * Description : Sends the specified effect to strip
 *
 * Prototype : void Ws2812b_Show(U16 Delay);
 *
 * Parameters :
 *
 * U16 Delay - Pixel movement speed
 *
 */

void Ws2812b_Show(U16 Delay);

/*
 *
 * EFFECTS FUNCTIONS
 *
 */

/* Description : Dynamic effect #1
 *
 * Prototype : void Ws2812b_Moving_Effect_Two_Colors(Color *_Col_1, Color * _Col_2,  U16 Delay);
 *
 *
 * Parameters :
 *
 * Color *_Col_1 - Pointer to a Color structure object
 *
 * Color *_Col_2 - Pointer to a Color structure object
 *
 * U16 Delay - Pixel movement speed
 *
 */

void Ws2812b_Moving_Effect_Two_Colors(RGB *_Col_1, RGB * _Col_2,  U16 Delay);

/*
 * Description : Dynamic effect #2
 *
 * Prototype : void Ws2812b_Moving_Effect_Three_Colors(Color *_Col_1, Color * _Col_2, Color * _Col_3, U16 Delay);
 *
 * Parameters :
 *
 * Color *_Col_1 - Pointer to a Color structure object
 *
 * Color *_Col_2 - Pointer to a Color structure object
 *
 * U16 Delay - Pixel movement speed
 *
 */

//void Ws2812b_Moving_Effect_Three_Colors(RGB *_Col_1, RGB * _Col_2, RGB * _Col_3, U16 Delay);

/* Description : Dynamic effect #3
 *
 * Prototype : void Ws2812b_Sliding_Effect(Color *_Col_1, Color * _Col_2, Color * _Col_3, U16 Delay);
 *
 * Parameters :
 *
 * Color *_Col_1 - Pointer to a Color structure object
 *
 * Color *_Col_2 - Pointer to a Color structure object
 *
 * Color *_Col_3 - Pointer to a Color structure object
 *
 * U16 Delay - Pixel movement speed
 *
 */

void Ws2812b_Sliding_Effect(RGB *_Col_1, RGB * _Col_2, RGB * _Col_3, U16 Delay);

/* Description : Dynamic effect #4
 *
 * Prototype : void Ws2812b_Moving_And_Vanishing_Effect(Color *_Col_1, Color * _Col_2, U16 Delay);
 *
 * Parameters :
 *
 * Color *_Col_1 - Pointer to a Color structure object
 *
 * Color *_Col_2 - Pointer to a Color structure object
 *
 * U16 Delay - Pixel movement speed
 *
 */

void Ws2812b_Moving_And_Vanishing_Effect(RGB *_Col_1, RGB * _Col_2, U16 Delay);

/*
 * Description : Constructor
 *
 * Prototype : WS2812 New_Strip(WS2812 * _Strip);
 *
 * Parameters :
 *
 * WS2812 * _Strip - Pointer to a WS2812 structure object
 */

WS2812 New_Strip(WS2812 * _Strip);

/*
 * Description : Delay in microseconds
 *
 * Prototype : void ws2812b_Delay_In_Microseconds(U32 us);
 *
 * Parameters :
 *
 * U32 us - Delay time(in microseconds)
 */

void ws2812b_Delay_In_Microseconds(U32 us);

/*
 * Description : Lights up your own palette in HSV format
 *
 * Prototype : void Ws2812_Custom_Palette_HSV(Palette_HSV * _palette, U8 palette_counts, U16 Delay);
 *
 * Parameters :
 *
 * Palette_HSV * _palette - Pointer to a Palette structure object
 *
 * U8 palettes_num - Number of custom palettes on Strip
 *
 * U16 Delay - Pixel movement speed
 *
 * Tips:
 *
 *  Formula to calculate right value for palettes_num: PIXELS_COUNT / (Colors in palette * paletts_num) - the result of this equation should be integer
 *
 */

void Ws2812_Custom_Palette_HSV(Palette_HSV * _palette, U8 palettes_num, U16 Delay);


/*
 * Description : Lights up your own palette in RGB format
 *
 * Prototype : void Ws2812_Custom_Palette_RGB(Palette_RGB * _palette, U8 palettes_num, U16 Delay);
 *
 * Parameters :
 *
 * Palette_RGB * _palette - Pointer to a Palette structure object
 *
 * U8 palettes_num - Number of custom palettes on Strip
 *
 * U16 Delay - Pixel movement speed
 *
 * Tips:
 *
 *  Formula to calculate right value for palettes_num: PIXELS_COUNT / (Colors in palette * paletts_num) - bthe result of this equation should be integer
 *
 */
void Ws2812_Custom_Palette_RGB(Palette_RGB * _palette, U8 palettes_num, U16 Delay);
/* USER CODE END PFP */


#endif /* INC_WS2812B_H_ */
