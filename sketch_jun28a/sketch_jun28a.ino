String const key0 = "1234567890";
String const key1  = "qwertyuiop"; 
String const key2 = "asdfghjkl" ; 
String const key3 = "zxcvbnm" ;


String const morseCodeKey  = "0123456789abcdefghijklmnopqrstuvwxyz " ;
String const morseCode [] = { "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", } ;

int const dashDelay = 500 ; 
int const dotDelay = 1500 ; 
int const pinOutput = 4;


void setup() {
  serial.being(9600);   
]

void loop (){
  
  String incomingMessage = "";
  String outputMessage = "" ;
  String morseCodeOutput = "" ;
  boolean encypt = false ;
  
  do{
    Serial.println("Please Enter Your Message"); 
    incomingMessage = Serial.readString();
    Serial.println("Your message is" + incomingMessage ); 
  
    Serial.println("Enter '1' to encypt message, all other values will decrypt your message" ); 
    encypt = Serial.read() ;
    Serial.println( "Encypt value" + encypt );
  }while( inputCheck( incomingMessage ) ) ;
   
  
  encodeArray( incomingMessage, outputMessage, encypt ) ; 
  
  morseCodeTranslator(outputMessage, morseCodeOutput) ;
  
  morseCodeOutputMessage(morseCodeOutput);

  Serial.println("Signal Sent" ); 
  delay(3000);

}


boolean inputCheck ( String & incomingMessage) {
  
  for ( int i = 0; i < incomingMessage.length() ; i++ ) {
    
    if ( arrayContain(incomingMessage[i], morseCodeKey ) )
      continue;
    else 
      Serial.println("Input contains invalid characters please ONLY enter letters or numbers");
      return false;
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
  for (int i = 0; i < array.length() ; i ++ ){
    
    if (arrayContain( key0 , input [i]) ){
      encodeTerm(input, key0, outputMessage, encypt);
    }else if (arrayContain( key1 , input [i]) ){
      encodeTerm(input, key1, outputMessage, encypt) ; 
    }else if (arrayContain( key2 , input [i]) ) {
      encodeTerm(input, key2, outputMessage, encypt);
    }else if (arrayContain( key3 , input [i]), encypt ){
      encodeTerm(input, key3, outputMessage, encypt);
    }
          
  }
 
 }
 
 
 int arrayIndex(String & array1 , char & element) {
  for (int i = 0; i < array1.length() ; i++) {
      if (array1 [i] == element) 
        return i;     
  }
  return -1;
}
 
 void encodeTerm( String & input, String & key, String & outputMessage, boolean encypt ){
   for ( int i = 0; i < input.length() ; i++){
      int keyIndex = arrayIndex( ( key , input[i] ) :
      int maxIndex =  key.length() - 1  ;
      
      if (encypt){
        
        if( keyIndex == 0)
          outputMessage[i] = key[ maxIndex ] ;
        else
          outputMessage[i] = key[ keyIndex - 1 ];
      }else{
        
        if( keyIndex == maxIndex )
          outputMessage[i] = key[0];
        else
          outputMessage[i] = key[ keyIndex + 1 ] ;
      }
    
  }

 }
 
 void morseCodeTranslator( String & outputMessage, String & morseCodeOutput  ) {
  for ( int i = 0 ; i < outputMessage.length() ; i++ ) {
    
    int ascii = outputMessage[i] ;
    
    if ( (ascii >= '0') && (ascii <= '9') ){
      int arrayOffset = ascii - '0';
      morseCodeOutput[i] = morseCodeKey[ arrayOffset ];
    }else if ( ( ascii >= 'a') && (ascii <= 'z') ){
      int arrayOffset = (ascii - 'a') + 10;
      morseCodeOutput[i] = morseCodeKey[ arrayOffset ] ;
    }else if ( (ascii >= 'A') && (ascii <= 'Z') ){
      int arrayOffset = (ascii - 'A') + 10 ;
      morseCodeOutput[i] = morseCodeKey[ arrayOffset ] ;
    }else if ( ascii == ' '){
      morseCodeOutput[i] = " ";
    }
    
  }

}

void ledflash( int DELAY ) {
  digitalWrite( pinOutput, HIGH ); 
  delay(DELAY)
  digitalWrite( pinOutput, LOW )
  delay(500);
}

void morseCodeOutputMessage( String [] morseCodeOutput ){

  //morseCodeOutput.lenth() may not work try .length
  for ( int i = 0; i < morseCodeOutput.length() ; i++){
    for (int j = 0; j < morseCodeOutput[i].length() ; j++ ) {
      
      //Use this to test output
      Serial.println(morseCodeOutput[i][j]);
      
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

