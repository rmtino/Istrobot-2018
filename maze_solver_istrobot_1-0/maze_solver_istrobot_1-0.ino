#define SPEEDA 3
#define SPEEDB 11
#define IN1 12
#define IN2 9
#define IN3 13
#define IN4 8

const int proxPins[3] = {4, 5, 6};
byte prox[3];
char path[30];
int pathlength = 0;
byte replayStage = 0;

void setup() {
  pinMode(SPEEDA, OUTPUT);
  pinMode(SPEEDB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  for (int i = 0; i < 3; i++) {
    pinMode(proxPins[i], INPUT);
  }
}

void loop() {
  readProx();
}


void readProx() {
  for (int i = 0; i < 3; i++) {
    prox[i] = digitalRead(proxPins[i]);
  }
}

void leftHand() {
  // krizovatka
  if (prox[0] == 0 && prox[2] == 0) {     // lavy sensor - daleko, pravy sensor - daleko
    readProx();
    turnLeft();
  }
  // ked sa vies otocit vlavo, tak sa otoc
  if (prox[0] == 0) {         // lavy sensor - daleko
    readProx();
    turnLeft();
  }
  // ked mozes ist aj doprava
  if (prox[2] == 0) {         // pravy sensor - daleko
    readProx();
    if (prox[0] == 0) {       // lavy sensor - daleko
      turnLeft();
    }
    else if (prox[1] != 0) {  // inak ak stredny sensor - blizko
      turnRight();
      return;
    }

    path[pathlength] = 'S';
    if (path[pathlength  - 2] == 'B') {
      shortPath();
    }
  }

  readProx();
  if (prox[0] == 1 && prox[1] == 1 && prox[2] == 1) {  // lavy sensor - blizko, stredny senor - blizko, pravy sensor - blizko
    turnAround();
  }
}

void turnLeft() {
  analogWrite(SPEEDA, 230);
  analogWrite(SPEEDB, 230);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(100);

  if (replayStage == 0) {
    path[pathlength] = 'L';
    pathlength++;

    if (path[pathLength - 2] == 'B') {
      shortPath();
    }
  }
}

void turnRight() {
  analogWrite(SPEEDA, 230);
  analogWrite(SPEEDB, 230);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(100);

  if (replayStage == 0) {
    path[pathlength] = 'R';
    pathlength++;

    if (path[pathLength - 2] == 'B') {
      shortPath();
    }
  }
}

void straight() {
  analogWrite(SPEEDA, 200);
  analogWrite(SPEEDB, 200);
  if (digitalRead(proxPins[0] == 1)) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(5);
  }

  if (digitalRead(proxPins[0] == 1)) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(5);
  }
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  }
}

void turnAround() {
  while () {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  path[pathLength]='B';
  pathLength++;
  straight();
}
  
void shortPath() {
  int shortDone = 0;

  if (path[pathlength - 3] == 'L' && path[pathlength - 1] == 'R') {
    pathLength -= 3;
    path[pathlength] = 'B';
    shortDone = 1;
  }    

  if (path[pathLength-3]=='L' && path[pathLength-1]=='S' && shortDone==0) {
    pathLength -= 3;
    path[pathlength] = 'R';
    shortDone = 1;
  }

  if (path[pathLength-3]=='R' && path[pathLength-1]=='L' && shortDone==0) {
    pathLength -= 3;
    path[pathlength] = 'B';
    shortDone = 1;
  }

  if (path[pathLength-3]=='S' && path[pathLength-1]=='L' && shortDone==0) {
    pathLength -= 3;
    path[pathlength] = 'R';
    shortDone = 1;
  }

  if (path[pathLength-3]=='S' && path[pathLength-1]=='S' && shortDone==0) {
    pathLength -= 3;
    path[pathlength] = 'B';
    shortDone = 1;
  }

  if (path[pathLength-3]=='L' && path[pathLength-1]=='L' && shortDone==0) {
    pathLength -= 3;
    path[pathlength] = 'S';
    shortDone = 1
  }

  path[pathLength+1]='D';
  path[pathLength+2]='D';
  pathLength++;
}
