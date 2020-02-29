#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


LiquidCrystal_I2C lcd(0x3F, 20, 4);
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication

    lcd.begin();
lcd.backlight();
    delay(500);
    
  lcd.setCursor(3, 1);
  lcd.print("Welcome!!");
  lcd.setCursor(0, 0);
  lcd.print("Circuit is Ready");
  delay(3500);
  lcd.clear();  
  
   
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop() 
{
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Put your card to");
  lcd.setCursor(0, 1);
  lcd.print("the reader......");
  delay(2300);
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  

  
  if (content.substring(1) == "2D 81 1A 2B") //change here the UID of the card/cards that you want to give access
  {
  
    lcd.setCursor(0, 0);
    lcd.print("ID : ");
    lcd.print(content.substring(1));
    lcd.setCursor(0, 1);
    lcd.print("Nasser, Authorized");
    Serial.println("Naseer, Authorized");
    delay(3000);
    lcd.clear();       
  }

   else  if (content.substring(1) == "46 5D 6A 13") //change here the UID of the card/cards that you want to give access
  {

    lcd.setCursor(0, 0);
    lcd.print("ID : ");
    lcd.print(content.substring(1));
    lcd.setCursor(0, 1);
    lcd.print("Esra'a ,Authorized");
    Serial.println("Esra'a, Authorized");
    delay(3000);
    lcd.clear();  
      
  }
 
 else   {

    lcd.print("ID : ");
    lcd.print(content.substring(1));
    lcd.setCursor(0, 1);
    lcd.print("Access denied");
    Serial.println(" Access denied");
    delay(3000);
     }

 

} 





  
