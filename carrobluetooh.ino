#include <Ultrasonic.h>
#include <SoftwareSerial.h>

#define trigger 8
#define echo 7

//configurações da ponte_h
int IN1 = 6;
int IN2 = 5;
int IN3 = 4;
int IN4 = 2;

//configurações do modulo bluetooth
String comando;
int TxD = 11; //conexao arduino e bluetooh
int RxD = 10; //conexao arduino e bluetooh
SoftwareSerial bluetooth(TxD, RxD);

//sensor ultrassônico
Ultrasonic ultrasonic(trigger, echo);

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void frente() {
  //gira o Motor A no sentido anti-horário
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //gira o Motor B no sentido anti-horário
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void re() {
  //gira o Motor A no sentido horário
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //gira o Motor B no sentido horário
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void parar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void direita_frente() {
  //gira o Motor A no sentido anti-horário
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //Motor B fica parado
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void esquerda_frente() {
  //Motor A fica parado
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  //gira o Motor B no sentido anti-horário
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void direita_re() {
  //gira o Motor A no sentido horário
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //Motor B fica parado
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void esquerda_re() {
  //gira o Motor A no sentido horário
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  //gira o Motor B no sentido horário
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void loop() {
  // Leitura da distância medida pelo sensor ultrassônico
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  Serial.print("Distancia em cm: ");
  Serial.println(cmMsec);

  if (bluetooh.avaliable()) {
    comando = bluetooh.readString();
    Serial.println(comando);

    if (comando == "frente" || comando == "FRENTE") {
      frente();
    }

    if (comando == "trás" || comando == "traz") {
      re();
    }

    if (comando == "parar" || comando == "PARAR") {
      parar();
    }

    if (comando == "direita" || comando == "DIREITA") {
      direita_frente();
    }
    
    if (comando == "esquerda" || comando == "ESQUERDA") {
      esquerda_frente();
    }
    
    if (comando == "direita trás" || comando == direita traz") {
      direita_re();
    }
    
    if (comando == "esquerda trás" || comando == "esquerda traz") {
      esquerda_re();
    }
  }
  
}