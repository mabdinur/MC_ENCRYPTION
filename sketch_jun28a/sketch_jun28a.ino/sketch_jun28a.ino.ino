//PLEASE SET THE INPUTVALUES
String setInComingMessage = "123qweasdzxcmnblkjpoiu0987" ;
                          // 234WERSDFXCVZMNALKQPOI1098
                         //  012PQWLASMZXNBVKJHOIUY9876
                         // ----- .---- ..--- .--. --.- .-- .-.. .- ... -- --.. -..- -. -... ...- -.- .--- .... --- .. ..- -.-- ----. ---.. --... -....

//Set value to true to encrypt and false to decypt                        
boolean isEncrypt = true;



String Encryptkey [] = { "1234567890" , "qwertyuiop" , "asdfghjkl"  , "zxcvbnm"  };

String  morseCode [] = { "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", } ;

int const dashDelay = 200 ; 
int const dotDelay = 1000 ; 
char escape = '+' ;


void setup() {
  Serial.begin(9600);   
}

void loop (){
  
  String incomingMessage = setInComingMessage;
 
  String outputMessage = "" ;

  boolean encypt = isEncrypt ;
  
//  do{
//    
//     Serial.println("Please Enter Your Message, press '+' after you finish entering you number ");
//     delay(3000);
//     while( true ) {
//
//        char a = '' ;
//        
//        if( Serial.available() > 0 ){
//          a = Serial.read();
//        }
//             
//        if(  a != escape   ){
//         incomingMessage += a;
//         Serial.println(a);
//        }else{
//          break;
//          Serial.println("+ was pressed");
//        }
//        delay(500);
//        
//    }
//
//    Serial.println( "++++" + incomingMessage );
//    Serial.println( incomingMessage.length() );  
  //  
  //   
   // Serial.println("Your message is" + incomingMessage ); 
  //
   // Serial.println("Enter '1' to encypt message, all other values will decrypt your message" ); 
    //
   // while(Serial.available() > 0) {
    //  delay(1000);
    //  encypt = Serial.read() ;
   // }
//
   // Serial.println( "Encrypt value" + encypt );
  //  
//  }while( inputCheck( incomingMessage ) ) ;
   
    encodeArray( incomingMessage, outputMessage, encypt ) ; 

   
    
    String morseCodeOutput [outputMessage.length()]  ;

 //  Serial.println( outputMessage  ); 


    morseCodeTranslator(outputMessage, morseCodeOutput) ;
    morseCodeOutputMessage(morseCodeOutput);
  
  delay(4000);

}


boolean inputCheck ( String & incomingMessage) {
  
  for ( int i = 0; i < incomingMessage.length() ; i++ ) {
    for( int j = 0; j < sizeof( Encryptkey ) ; j++ ){

      if ( arrayContain( Encryptkey[j] , incomingMessage[i] ) ) {
        continue;
      }else{
        Serial.println("Input contains invalid characters please ONLY enter letters or numbers");
        return false;
      }
      
    }
   
  }
  
  return true;
}

boolean arrayContain( String & array1 , char & element) {
  for (int i = 0; i < array1.length() ; i++) {
      if (array1[i] == element) {
        return true;
      }
  }
  
   return false;
}


void encodeArray(String & input, String & outputMessage, boolean & encypt ){
  for (int i = 0; i < input.length() ; i ++ ){

    for( int j = 0; j < 4 ; j++){
      
      if (arrayContain( Encryptkey[j] , input [i]) ){
        encodeTerm( input[i] , Encryptkey[j] , outputMessage, encypt);
      }
    
    }
          
  }

  
 }
 
 
 int arrayIndex(String & array1 , char element) {
  for (int i = 0; i < array1.length() ; i++) {
      if (array1 [i] == element) 
        return i;     
  }
  return -1;
}
 
 void encodeTerm( char input, String & key, String & outputMessage, boolean encypt ){
  
      int keyIndex =  key.indexOf( input );                                                   // arrayIndex( ( key , input[i] ) ) :
      int maxIndex =  key.length() - 1  ;

      if (encypt){
        
        if( keyIndex == 0)
          outputMessage += key[ maxIndex ] ;
        else
          outputMessage += key[ keyIndex - 1 ];
      }else{
        
        if( keyIndex == maxIndex ){
          outputMessage += key[0];
        }else{
          outputMessage += key[ keyIndex + 1 ] ;
              
        }  
      }
    
  }

 
 void morseCodeTranslator( String & outputMessage, String morseCodeOutput []  ) {
  for ( int i = 0 ; i < outputMessage.length() ; i++ ) {
    
    int ascii = outputMessage[i] ;
    
    if ( (ascii >= '0') && (ascii <= '9') ){
      int arrayOffset = ascii - '0';
      morseCodeOutput [i] = morseCode[ arrayOffset ];
    }else if ( ( ascii >= 'a') && (ascii <= 'z') ){
      int arrayOffset = (ascii - 'a') + 10;
      morseCodeOutput [i] = morseCode[ arrayOffset ] ;
    }else if ( (ascii >= 'A') && (ascii <= 'Z') ){
      int arrayOffset  = (ascii - 'A') + 10 ;
      morseCodeOutput[i] = morseCode[ arrayOffset ] ;
    }else if ( ascii == ' '){
      morseCodeOutput[i] += " ";
    }

    Serial.println( morseCodeOutput[i]  ); 
    
  }


}

void ledflash( int DELAY ) {
 
  //String pinLED = "LED_BUILTIN" ;
  
  pinMode( LED_BUILTIN , OUTPUT);
  digitalWrite( LED_BUILTIN , HIGH ); 
  delay(DELAY);
  digitalWrite( LED_BUILTIN, LOW );
  delay(500);
}

void morseCodeOutputMessage( String morseCodeOutput [] ){

  //morseCodeOutput.lenth() may not work try .length
  for ( int i = 0; i < sizeof (morseCodeOutput) ; i++){
    for (int j = 0; j < morseCodeOutput[i].length() ; j++ ) {
      
      //Use this to test output
 //     Serial.print(morseCodeOutput[i][j]);
      
      if ( morseCodeOutput[i][j] == '-' ){
        ledflash(dashDelay) ;
      }else if( morseCodeOutput[i][j] == '.' ){
        ledflash(dotDelay) ;
      }else if( morseCodeOutput[i][j] == ' '){
        delay(2000);
      }
          
    }
    delay(500);
  }
  
}

