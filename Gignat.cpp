// C++ code
//
const int IN1 = 10; // Alguma parte do motor
const int IN2 = 11; // 
const int IN3 = 5; // 
const int IN4 = 6; // Outra parte do motor
const int echo = 12;
const int trigger = 13;
const int pinLed = 2;
const int pinIRa = A0;
const int motor = 9;

// Variável para armazenar a distância medida pelo sensor ultrassônico
float dist;
int detectou = 1;
// 
int IRvalueA = 0;
 int IRvalueD = 0;

void setup() {
  // Inicialização da comunicação serial
  Serial.begin(9600);

  // Configuração dos pinos como entrada ou saída
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(pinIRa, INPUT);
  pinMode(echo, INPUT);
}

// Função para atacar o robô adversário
void attackEnemy() {
  // Aciona os motores para frente
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Função para procurar o robô adversário
void searchEnemy() {
  // Gira os motores para a esquerda por um curto período de tempo
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(100);

  // Gira os motores para a direita por um curto período de tempo
  for (int i = 0; i < 3; i++) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    if (dist > 50){
     detectou = 1;
    }
    delay(50);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    if (dist >50){
      detectou = 1;
    }
    delay(50);
  }
}

void arenaBorder() {
    // Escrever código para rotacionar QUANDO DETECTAR COR CLARA
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(500);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(500);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(200);
}

void loop() {
  // 
  Serial.print("Analog Reading = ");
  Serial.print(IRvalueA);
  Serial.print("\n");
  delay(100);
  IRvalueA = analogRead(pinIRa);

  // Realiza a medição da distância com o sensor ultrassônico
  digitalWrite(trigger, LOW);
  delay(100);
  digitalWrite(trigger, HIGH);
  delay(100);
  digitalWrite(trigger, LOW);
  dist = pulseIn(echo, HIGH) / 58.0; // Converte o tempo em microssegundos para centímetros
  
    // Verifica a distância medida e toma a ação correspondente
    if(IRvalueA  > 300 || detectou == 1){
      if (dist <= 50) {
        // Ataca o robô adversário
        attackEnemy();
        detectou = 0;
      }
      if(dist > 50){
        // Procura o robô adversário
        searchEnemy();
      }
    }  
    if(IRvalueA < 300){
      arenaBorder();
    }
}
