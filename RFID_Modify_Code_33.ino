/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read data from a PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 * 
 * Example sketch/program showing how to read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
 * Reader on the Arduino SPI interface.
 * 
 * When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
 * then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
 * you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
 * will show the ID/UID, type and any data blocks it can read. Note: you may see "Timeout in communication" messages
 * when removing the PICC from reading distance too early.
 * 
 * If your reader supports it, this sketch/program will read all the PICCs presented (that is: multiple tag reading).
 * So if you stack two or more PICCs on top of each other and present them to the reader, it will first output all
 * details of the first and then the next PICC. Note that this may take some time as all data blocks are dumped, so
 * keep the PICCs at reading distance until complete.
 * 
 * @license Released into the public domain.
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
int x=0;
int y=1;
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
    Serial.print("y = ");
    Serial.println(y);
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
    Serial.print("y = ");
    Serial.println(y);
    delay(3000);
    lcd.clear();  
      
  }
 
 else   {

    lcd.print("ID : ");
    lcd.print(content.substring(1));
    lcd.setCursor(0, 1);
    lcd.print("Access denied");
    Serial.println(" Access denied");
    Serial.print("x =  ");
    Serial.println(x);
    delay(3000);
     }

 

} 





  
