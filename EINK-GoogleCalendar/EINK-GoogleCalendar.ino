/* Includes ------------------------------------------------------------------*/
#include "DEV_Config.h"
#include "EPD.h"
#include "GUI_Paint.h"
#include "imagedata.h"
#include <stdlib.h>
#include "main.h"
/* Setup */
#define TWENTYFOUR_HRS 2 * 43200000UL
unsigned long startTime;

void setup()
{
  Calendar();
  startTime = millis();

}

//Main function
void Calendar(){

  DEV_Module_Init();

  printf("e-Paper Init and Clear...\r\n");
  EPD_7IN5_V2_Init();
  EPD_7IN5_V2_Clear();
  DEV_Delay_ms(500);

  //Create a new image cache
  UBYTE *BlackImage;
  /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
  UWORD Imagesize = ((EPD_7IN5_V2_WIDTH % 8 == 0) ? (EPD_7IN5_V2_WIDTH / 8 ) : (EPD_7IN5_V2_WIDTH / 8 + 1)) * EPD_7IN5_V2_HEIGHT;
  if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
    printf("Failed to apply for black memory...\r\n");
    while (1);
  }
  printf("Paint_NewImage\r\n");
  Paint_NewImage(BlackImage, EPD_7IN5_V2_WIDTH, EPD_7IN5_V2_HEIGHT, 0, WHITE);

#if 1 == 0   // show image for array   
  printf("show image for array\r\n");
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);
  Paint_DrawBitMap(gImage_7in5_V2_2);
  EPD_7IN5_V2_Display(BlackImage);
  DEV_Delay_ms(2000);
#endif

#if 1   // Drawing on the image
  //1.Select Image
  printf("SelectImage:BlackImage\r\n");
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);

  // 2.Drawing on the image
  printf("Drawing:BlackImage\r\n");

  Paint_DrawString_EN(350, 10, "Calendar", &Font24, WHITE, BLACK);

  Paint_DrawRectangle(1, 40, 395, 80, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(1, 80, 395, 180, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawRectangle(250, 80, 395, 180, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

  Paint_DrawRectangle(1, 190, 395, 230, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(1, 230, 395, 330, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawRectangle(250, 230, 395, 330, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

  Paint_DrawRectangle(1, 340, 395, 380, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(1, 380, 395, 480, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawRectangle(250, 380, 395, 480, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

  Paint_DrawRectangle(405, 40, 800, 80, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(405, 80, 800, 180, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawRectangle(655, 80, 800, 180, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

  Paint_DrawRectangle(405, 190, 800, 230, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(405, 230, 800, 330, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawRectangle(655, 230, 800, 330, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

  Paint_DrawRectangle(405, 340, 800, 380, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(405, 380, 800, 480, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawRectangle(655, 380, 800, 480, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

  char* str = getCalendarData();
  char* strtmp = strtok(str, "\n");
  char* strTime;
  char* strtmp2;
  int i = 50;
  int y = 10;
  int j = 0;
  char * separator = "|";
  while(strtmp != NULL){
    Serial.print("------");
    if(strcmp(strtmp,separator) == 0){
      j++;
      if(j == 1){
        i = 200;
      }else if(j == 2){
        i = 350;
      }else if(j == 3){
      Serial.print("\ncositasss\n");
      i = 50;
      y = 415;
      j = 0;
    }
      strtmp = strtok(NULL, "\n");
    }
    Serial.print(strtmp);
    if(i==50 or i==200 or i==350){
      Paint_DrawString_EN(y, i, strtmp, &Font24, BLACK, WHITE);
    }else{
      Paint_DrawString_EN(y, i, strtmp, &Font12, WHITE, BLACK);
    }

    strtmp = strtok(NULL, "\n");
    if(i==50 or i==200 or i==350){
      i+= 20;
    }
    i += 20;
    
  }
  //Serial.print(strtmp);

  //const char* strc = strdate;
  //Paint_DrawString_EN(10, 20, strc, &Font12, WHITE, BLACK);
  
  printf("EPD_Display\r\n");
  EPD_7IN5_V2_Display(BlackImage);
  //DEV_Delay_ms(2000);
#endif

  /*printf("Clear...\r\n");
  EPD_7IN5_V2_Clear();
*/
  printf("Goto Sleep...\r\n");
  EPD_7IN5_V2_Sleep();
  free(BlackImage);
  BlackImage = NULL;

}
/* The main loop -------------------------------------------------------------*/
void loop()
{

   if (millis() - startTime > TWENTYFOUR_HRS)
  {
    Calendar();
    startTime = millis();
  }
}
