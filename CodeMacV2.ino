
#include <LiquidCrystal.h>
#include <Servo.h>
#include <string.h>
//esc
Servo esc;

//Potenciometro
int Potpin = 0;

//Sensor hall funcao getRPM
const int maxRPM = 10200; 
const unsigned long sampleTime=1000;
//

 
//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
void setup()
{
  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);
  //Define input do sensor hall 
  pinMode(8,INPUT);
  //Esc
  esc.attach(9);
  Serial.begin(9600);
  //inicializacao de esc sempre no valor minimo;
  esc.write(60);
  // Mensagem de bem vindo do lcd
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(1, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print(  "---bem vindo---");
  lcd.setCursor(3, 1);
  lcd.print("Projeto MacGyver");
  delay(200);
  
}
 
void loop()
{

  //esc
  Fesc(Potpin);

  //lcd
  int rpm=getRPM();
  //Limpa a tela
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(1, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("Projeto MacGyver ");
  lcd.setCursor(3, 1);
  lcd.print("RPM -->");
  lcd.setCursor(11, 1);
  lcd.print(rpm);
  delay(200);
   

}
 // hall
 int getRPM()
  {
  // sample for sampleTime in millisecs
  int kount=0;
  boolean kflag=LOW;
  unsigned long currentTime=0;
  unsigned long startTime=millis();
  while (currentTime<=sampleTime)
  {
    if (digitalRead(8)==HIGH)
    {
      kflag=HIGH;
    }
    if (digitalRead(8)==LOW && kflag==HIGH)
    {
      kount++;
      kflag=LOW;
    }
    currentTime=millis()-startTime;
  }
  int kount2rpm = int(60000./float(sampleTime))*kount;
  return kount2rpm;
  }
  
 void Fesc (int a)
 {
  int Pot = analogRead(a);
  Pot = map(Pot, 0, 1023, 60, 180);
  Serial.println(Pot);
  esc.write(Pot);
 }

  
