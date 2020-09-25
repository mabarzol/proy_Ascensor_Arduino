int estado = 0;
int anterior = 0;
int ENABLE = 11; //pin de control L293d
int INP1 = 10; //subida
int INP2 = 9;  //bajada
int BOTON_A = A1;//declara pines de uso para pulsador//
int estadoA = 0;
int BOTON_B = A2;
int estadoB = 0;
int BOTON_C = A3;
int estadoC = 0;
int BOTON_D = A0;
int estadoD = 0;
int FCARRERA1 = 7; //PINES de entrada de final de carrera por piso//
int FCARRERA2 = 6;
int FCARRERA3 = 5;
int flag1 = LOW;
int flag2 = LOW;
int flag3 = LOW;
int cnta = 0;
int cntb = 0;
int cntc = 0;
int cntd = 0;
void setup() {
  // Inicializamos los pines del chip como salida:

  pinMode(ENABLE, OUTPUT);
  pinMode(INP1, OUTPUT);
  pinMode(INP2, OUTPUT);
  pinMode(FCARRERA1, INPUT);//final de carrera primer piso
  pinMode(FCARRERA2, INPUT);//final de carrera segundo piso
  pinMode(FCARRERA3, INPUT);//final de carrera tercer piso

  pinMode(BOTON_A, INPUT);
  pinMode(BOTON_B, INPUT);
  pinMode(BOTON_C, INPUT);
  pinMode(BOTON_D, INPUT);

  digitalWrite(INP1, LOW);
  digitalWrite(INP2, LOW);
  digitalWrite(ENABLE, LOW);
}
void loop() {
  pulso(BOTON_A, 1, estado, anterior, estadoA); //segundo piso subida
  if  (estadoA == 1 && cnta == 0) //SEGUNDO PISO SUBIDA /
  {
    cntb = 0;
    cntc = 0;
    cntd = 0;
    cnta ++;

    digitalWrite(INP1, HIGH);
    digitalWrite(INP2, LOW);
    digitalWrite(ENABLE, HIGH);
    do {
      flag2 = digitalRead(FCARRERA2);
    } while (flag2 == LOW);
    digitalWrite(ENABLE, LOW);
    digitalWrite(INP1, LOW);
    flag2 = 0;
    estadoA = 0;
  }
  pulso(BOTON_B, 2, estado, anterior, estadoB); //tercer piso subida
  if  (estadoB == 2 && cntb == 0 && cnta != 2) //TERCER PISO SUBIDA /
  {
    cnta ++;
    cntc = 0;
    cntd = 0;
    cntb ++;

    digitalWrite(INP1, HIGH);
    digitalWrite(INP2, LOW);
    digitalWrite(ENABLE, HIGH);
    do {
      flag3 = digitalRead(FCARRERA3);
    } while (flag3 == LOW);

    digitalWrite(ENABLE, LOW);
    digitalWrite(INP1, LOW);
    flag3 = 0;
    estadoB = 0;

  }
  pulso(BOTON_C, 3, estado, anterior, estadoC); //segundo piso bajada
  if  (estadoC == 3 && cntc == 0) //TERCER PISO BAJADA /
  {
    cnta = 0;
    cntb = 0;
    cntd = 0;
    cntc ++;

    digitalWrite(INP1, LOW);
    digitalWrite(INP2, HIGH);
    digitalWrite(ENABLE, HIGH);
    do {
      flag2 = digitalRead(FCARRERA2);
    } while (flag2 == LOW);

    digitalWrite(ENABLE, LOW);
    digitalWrite(INP2, LOW);
    flag2 = 0;
    estadoC = 0;

  }
  pulso(BOTON_D, 4, estado, anterior, estadoD); //primer piso bajada
  if  (estadoD == 4 && cntd == 0 && cntc != 2) //SEGUNDO PISO BAJADA /
  {
    cnta = 0;
    cntb = 0;
    cntc ++;
    cntd ++;

    digitalWrite(INP1, LOW);
    digitalWrite(INP2, HIGH);
    digitalWrite(ENABLE, HIGH);
    do {
      flag1 = digitalRead(FCARRERA1);
    } while (flag1 == LOW);

    digitalWrite(ENABLE, LOW);
    digitalWrite(INP2, LOW);
    flag1 = 0;
    estadoD = 0;
  }

  digitalWrite(INP1, LOW);
  digitalWrite(INP2, LOW);
  digitalWrite(ENABLE, LOW);
  estadoA = 0;
  estadoB = 0;
  estadoC = 0;
  estadoD = 0;
}

void pulso(int boton, int orden, int &estado, int &anterior, int &sal) {
  estado = digitalRead(boton);
  if ((estado == LOW) && (anterior == HIGH)) {
    sal = orden;
  }
  anterior = estado;
  delay(20);
}
