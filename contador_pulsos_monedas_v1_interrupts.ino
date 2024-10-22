const int limite_pulsos = 150; /* EDITAR ESTE VALOR PARA CAMBIAR EL DELAY ENTRE DETECCION DE PULSOS-nesecito poner un DELAY es como una pausa entre la deteccion de pulsos para que el arduino me lea los pulsos sin arrojar basura, eh calado multiples valores y 500 es el mas estable*/
const int coin_pin = 12; /*Asigno el valor de 2 para la variable donde conectare el pin que va a recibir los pulsos del monedero*/
volatile byte cont_pulsos_moneda = 0;/*Variable para guardar el valor de los pulsos contados*/
volatile unsigned long tiempo_pulso; /*Variable para guardar el tiempo en el que se leyo e pulso*/
byte pulsos_total; /* lugar para guardar el total de pulsos detectados*/
byte nueva_moneda=0;/* lugar para guardar el valor de la moneda basandme en el total de pulsos detectados*/
   
void setup()
{
    Serial.begin(9600);/* Establece la velocidad de datos en bits por segundo (baudios) para la transmisión de datos en serie. Para comunicarse con la pc*/   pinMode(coin_pin, INPUT_PULLUP);/*establecemos el pin 2 (coin_pin) como tipo INPUT y le adjuntamos una resistencia interna para evitar rebotes*/
    attachInterrupt(digitalPinToInterrupt(coin_pin), sumar_contador_moneda, RISING);
    Serial.println("Morralla Setup Cargado correctamente.");/*Imprimo en consola para notificarme que la funcion setup() llego a su fin*/
}
  
void sumar_contador_moneda() /*funcion invocada para incrementar el contador cont_pulsos_moneda*/
{
    cont_pulsos_moneda++;
    tiempo_pulso = millis();/*guardo el tiempo ACTUAL y se lo asigno a la variable como el tiempo cuando leyo el pulso*/
}/*fin sumar_cont_moneda()*/

  void loop() {
  /*dejar de contar pulsos si hubo una interrupcion y el contador se incremento entonces hubo una moneda detectada (cont_pulsos_moneda>0) && si el tiempo actual menos el tiempo del ultimo pulso es mayor a los 500 milisegundos entonces hacer lo siguiente*/
    if (cont_pulsos_moneda >0 && millis()-tiempo_pulso > limite_pulsos){
    cli();/*disable interrupts*/
    nueva_moneda = cont_pulsos_moneda; /*Guardo el valor del total de pulsos en esta variable para liberar espacio en la variable cont_pulsos_moneda*/
    sei();/*enable interrupts*/
    Serial.print("Nueva moneda detectada ");/*me alerta en consola que hubo una moneda detectada*/
    Serial.println(nueva_moneda); /* imprime en consola el valor de esa moneda*/
    cli();/*disable interrupts*/
    cont_pulsos_moneda = 0; /*reseteo a 0 el contador de pulsos del interruptor*/
    sei();/*enable interrupts*/  
  }   
}
