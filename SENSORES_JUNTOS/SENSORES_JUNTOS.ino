int linea1=2;
int linea2=3;
int valvula1=4;
int valvula2=5;
long Duration=0;
int trigger=6;
int echo=7;

#define S0 8    // S0 a pin 2
#define S1 9    // S1 a pin 3
#define S2 10    // S2 a pin 4
#define S3 11   // S3 a pin 5
#define salidaTCS 12 // salidaTCS a pin 6



void setup() {
  // put your setup code here, to run once:
pinMode(trigger,OUTPUT);//trigger
pinMode(echo,INPUT);//echo
pinMode(linea1,INPUT);
pinMode(linea2,INPUT);
pinMode(valvula1,OUTPUT);
pinMode(valvula2,OUTPUT);

//rgb
  pinMode(S0, OUTPUT);    // pin 4 como salida
  pinMode(S1, OUTPUT);    // pin 5 como salida
  pinMode(S2, OUTPUT);    // pin 6 como salida
  pinMode(S3, OUTPUT);    // pin 7 como salida
  pinMode(salidaTCS, INPUT);  // pin 8 como salida
  
  digitalWrite(S0,HIGH);  // establece frecuencia de salida
  digitalWrite(S1,LOW);   // del modulo al 20 por ciento


Serial.begin(9600); // inicializa monitor serie a 9600 bps
}

void loop() {


  digitalWrite(S2,LOW);     // establece fotodiodos
  digitalWrite(S3,LOW);     // con filtro rojo
  int rojo = pulseIn(salidaTCS, LOW); // obtiene duracion de pulso de salida del sensor
  delay(1000);       // demora de 200 mseg
  
  digitalWrite(S2,HIGH);    // establece fotodiodos
  digitalWrite(S3,HIGH);    // con filtro verde
  int verde = pulseIn(salidaTCS, LOW);  // obtiene duracion de pulso de salida del sensor
  delay(1000);       // demora de 200 mseg
  
  digitalWrite(S2,LOW);     // establece fotodiodos
  digitalWrite(S3,HIGH);    // con filtro azul
  int azul = pulseIn(salidaTCS, LOW); // obtiene duracion de pulso de salida del sensor
  delay(1000);       // demora de 200 mseg
  
  Serial.print("R:");     // muestra texto
  Serial.print(rojo);     // muestra valor de variable rojo

  Serial.print("\t");     // espacio de tabulacion

  Serial.print("V:");     // muestra texto
  Serial.print(verde);      // muestra valor de variable verde

  Serial.print("\t");     // espacio de tabulacion

  Serial.print("A:");     // muestra texto
  Serial.println(azul);     // muestra valor de variable azul

  //////////////////////////////////////////
  /////////////////////////////////////////

  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  
  Duration=pulseIn(echo,HIGH);

  long Distance_cm = Distance(Duration);
  Serial.print("Distance= ");
  Serial.print(Distance_cm);
  Serial.println(" cm");
  delay(1000);


if(Distance_cm<10 && azul<120 && rojo>140 && verde>90  ){
 
  if(digitalRead(linea1)==0){
    
    Serial.println("Detectado en primera linea");
   
    digitalWrite(valvula1,HIGH);
    delay(1000);
    digitalWrite(valvula1,LOW);
       }
  else{
    Serial.println("Objeto no detectado");
    }
}
  


if(Distance_cm>13 && verde<130 && rojo>70 && azul>50){
  if(digitalRead(linea2)==0){
    
    Serial.println("Detectado en segunda linea");
    
    digitalWrite(valvula2,HIGH);
    delay(1000);
    digitalWrite(valvula2,LOW);
       }
  else{
    Serial.println("Objeto no detectado");
    }}

}
  
  long Distance(long time){
  long DistanceCalc;
  DistanceCalc= (time/2)/29;
  return DistanceCalc;
  }
