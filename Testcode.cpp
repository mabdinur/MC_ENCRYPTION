char key0[] = "1234567890";
char key1[] = "qwertyuiop"; 
char key2[] = "asdfghjkl" ; 
char key3 [] = "zxcvbnm" ;

boolean encypt = false ;

//This pin is HIGH is encryption is desired and low if decryption is desired
int pinEncrypt = 3;   
int pinOutput = 4;

char incomingSignal [] = "abcdefg123456";


char outputSignal [sizeof(incomingSignal)];

char moorseCodeKey [] = "0123456789abcdefghijklmnopqrstuvwxyz" ;
String moorseCode [] = { "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", } ;
String moorseCodeOutput [sizeof(incomingSignal)] ;

int const dashDelay = 500 ; 
int const dotDelay = 1500 ; 


void setup() {
	serial.being(9600);		
]

void loop (){
	
	pinMode(pinEncrypt, Input);
	encrypt = digitalRead(pinEncrypt);
	
	encodeArray( incomingSignal ) ;	
	moorseCodeTranslator() ;
	moorseCodeOutputSignal()
	
	delay(1000);

}


boolean arrayContain(char array[], char element) {
	for (int i = 0; i < sizeof(array) ; i++) {
		  if (array[i] == element) {
			  return true;
		  }
		}
	 return false;
}


void encodeArray(array []){
	for (int i = 0; i < sizeof(array) ; i ++ ){
		
		if (arrayContain( key0 , array [i]) ){
			encodeTerm(array, key0);
		}else if (arrayContain( key1 , array [i]) ){
			encodeTerm(array, key1) ;	
		}else if (arrayContain( key2 , array [i]) ) {
			encodeTerm(array, key2);
		}else if (arrayContain( key3 , array [i]) ){
			encodeTerm(array, key3);
		}
					
	}
 
 }
 
 
 int arrayIndex(char array[], char element) {
 for (int i = 0; i < sizeof(array) ; i++) {
      if (array[i] == element) {
          return i;
      }
    }
  return -1;
}
 
 void encodeTerm(array [], key [] ){
	 for ( int i = 0; i < sizeof(array); i++){
		int keyIndex = arrayIndex( ( key , array[i] ) :
		int maxIndex = key[ sizeof(key) - 1 ] ;
		
		if (encypt){
			
			if( keyIndex == 0){
				outputSignal[i] = key[ maxIndex ] ;
			}else{
				outputSignal[i] = key[ keyIndex - 1 ];
			}
			
		else{
			if( keyIndex == maxIndex ){
				outputSignal[i] = key[0];
			}else{
				outputSignal[i] = key[ keyIndex + 1 ] ;
			}
		
		}

 }
 
 void moorseCodeTranslator() {
	for ( int i = 0 ; i < sizeof(outputSignal) ; i++ ) {
		
		int ascii = outputSignal[i] ;
		
		if ( (ascii >= '0') && (ascii <= '9') ){
			int arrayOffset = ascii - '0';
			moorseCodeOutput[i] = moorseCodeKey[ arrayOffset ];
		}else if ( ( ascii >= 'a') && (ascii <= 'z') ){
			int arrayOffset = (ascii - 'a') + 10;
			moorseCodeOutput[i] = moorseCodeKey[ arrayOffset ] ;
		}else if ( (ascii >= 'A') && (ascii <= 'Z') ){
			int arrayOffset = (ascii - 'A') + 10 ;
			moorseCodeOutput[i] = moorseCodeKey[ arrayOffset ] ;
		}else if ( ascii == ' '){
			moorseCodeOutput[i] = " ";
		}
		
	}

}

void ledflash( int DELAY ) {
	digitalWrite( pinOutput, HIGH ); 
	delay(DELAY)
	digitalWrite( pinOutput, LOW )
	delay(500);
}

void moorseCodeOutputSignal(){
	
	for ( int i = 0; i < sizeof(moorseCodeOutput) ; i++){
		for (int j = 0; j < sizeof(moorseCodeOutput[i] ) ; j++ ) {
			
			if ( moorseCodeOutput[i][j] == '-' ){
				ledflash(dashDelay) ;
			}else if( moorseCodeOutput[i][j] == '.' ){
				ledflash(dotDelay) ;
			}else if( moorseCodeOutput[i][j] == ' '){
				delay(2000);
			}
					
		}
	}

}

