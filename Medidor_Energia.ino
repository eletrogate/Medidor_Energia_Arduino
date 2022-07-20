#include "EmonLib.h" 
#include <LiquidCrystal.h>

#define Vrede 129     // define a tensão RMS da rede(valor lido com multimetro)
#define InputSCT 2    // define o canal analógico para o sinal do SCT = pino A2

#define LCD_RS 9                // definição dos pinos do LCD
#define LCD_E 8
#define LCD_D4 3
#define LCD_D5 4
#define LCD_D6 5
#define LCD_D7 6
#define I_calibration 60         // fator de calibração da corrente - leia minhas dicas no tutorial

 
EnergyMonitor EnerMonitor;       //Cria uma instancia da classe EnergyMonitor
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
double Irms = 0 ;
float Tempo = 0;

void setup() 
{
  lcd.begin(16, 2);                         // configura LCD 16 colunas x 2 linhas
  lcd.clear();                              // limpa tela do LCD
  
  EnerMonitor.current(InputSCT, I_calibration);   // configura pino SCT e fator de calibração
  
  lcd.setCursor(0,0);                       // seleciona coluna 0, linha 0
  lcd.print("Irms(A)=");                    // mostra texto
  lcd.setCursor(0,1);                       // seleciona coluna 0, linha 1
  lcd.print("Ener(Wh)=");                   // mostra texto
} 
 
void loop() 
{ 
  Irms = EnerMonitor.calcIrms(1480);         // calculo da corrente RMS
  lcd.setCursor(9,0);                        // seleciona coluna 9, linha 0
  lcd.print(Irms);                           // mostra valor da corrente 
  lcd.setCursor(9,1);                        // seleciona coluna 9, linha 1
  lcd.print(Irms*Vrede*(Tempo/3600));        // calculo de Watt/hora  
  Tempo++;                                   // incrementa Tempo   
  delay(1000);                               // atraso de 1 segundo
}