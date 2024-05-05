//=============================================================================
// TFG BREVE: Medidor de decibelios
// Diego Horacio Socas Castro
//=============================================================================

//Pin al que esta conectado el sensor de sonido
#define SENSOR_SONIDO A5

//Tamaño de la ventana para tomar muestras (Se toman muestras durante 50ms)
#define MUESTRAS_T 50

//Valores minimos y máximos que toma el sensor
#define MIN_SENSOR 40
#define MAX_SENSOR 450

//Valores minimos y maximos de dB
#define MIN_DB 0
#define MAX_DB 90

//Numero de LEDs usados
#define NUM_LEDS 12
#define UMBRAL 10

//Valor leido del sensor de sonido
unsigned int senal_valor = 0;

//valor max y min del sensor durante la ventana de muestreo
unsigned int senal_max;
unsigned int senal_min; 

//Rango del valor leido del sensor durante al ventana de muestreo (max - min)
float rango;

//Valor de dB
float db;

//Numero de led a encender
int led;

void setup() {

  Serial.begin(9600);

  //Se definen los pines como pines de salida
  for (int i = 2; i <= NUM_LEDS + 1; i++){
    pinMode(i, OUTPUT);
  }

}

void loop() {   

  //Se resetean las variables
  senal_max = MIN_SENSOR;
  senal_min = MAX_SENSOR;
  rango = 0;    

  //Comienza la ventana de muestreo
  unsigned long t_comienzo= millis();

  while (millis() - t_comienzo < MUESTRAS_T) {

    //Se lee el valor del sensor de sonido
    senal_valor = analogRead(SENSOR_SONIDO);

    //Se almacena el maximo del valor leido durante este tiempo
    if (senal_valor > senal_max){
      senal_max = senal_valor;                           
    }

    //Se almacena el minimo valor leido durante este tiempo
    else if (senal_valor < senal_min){
      senal_min = senal_valor;                           
    }

  }

  //Se calcula la diferencia entre el maximo y el minimo
  rango = senal_max - senal_min;

  //Se mapea el valor del rango entre 0 y 90
  db = map(rango, MIN_SENSOR, MAX_SENSOR, MIN_DB, MAX_DB);

  //Se mapea el valor de los dB para encender el led que le corresponde
  led = map(db, MIN_DB + UMBRAL , MAX_DB , 2, NUM_LEDS + 1);

  //Se encienden los LEDs menores e igual al valor de led
  //si led = 5, se encienden los LEDs 5, 4, 3, 2 y 1
  for (int i = led; i >= 2; i--){
    digitalWrite(i, HIGH);
  }

  //Se encienden los LEDs menores e igual al valor de led
  //si led = 5, se apagan los LEDs del 6 hasta el 12
  for(int i = led+1; i <= NUM_LEDS + 1; i++){
    digitalWrite(i, LOW);
  }

  //Imprime dB para visualizar en el plotter
  Serial.print("dB:");
  Serial.println(db);

}
