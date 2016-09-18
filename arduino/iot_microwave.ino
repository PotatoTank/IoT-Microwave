// Inputs
#define I_R2 5
#define I_R3 6
#define I_R4 7
#define I_R5 8
#define I_R6 9
#define I_R7 10
#define I_C3 11
#define I_C4 12
#define I_C5 13

// Outputs
#define O_R2 2
#define O_R3 3
#define O_R4 4
#define O_R5 14
#define O_R6 15
#define O_R7 16
#define O_C3 17
#define O_C4 18
#define O_C5 19

// Constants
#define CLOCK -1
#define RESET -2

long debounceDelay = 100;
int lastDebounceTime = 0;
int lastButton = 0;

void setup() {
  Serial.begin(9600);
  pinMode(I_R2, OUTPUT);
  pinMode(I_R3, OUTPUT);
  pinMode(I_R4, OUTPUT);
  pinMode(I_R5, OUTPUT);
  pinMode(I_R6, OUTPUT);
  pinMode(I_R7, OUTPUT);
  pinMode(I_C3, INPUT_PULLUP);
  pinMode(I_C4, INPUT_PULLUP);
  pinMode(I_C5, INPUT_PULLUP);
  digitalWrite(I_R2, HIGH);
  digitalWrite(I_R3, HIGH);
  digitalWrite(I_R4, HIGH);
  digitalWrite(I_R5, HIGH);
  digitalWrite(I_R6, HIGH);
  digitalWrite(I_R7, HIGH);

  pinMode(O_R2, OUTPUT);
  pinMode(O_R3, OUTPUT);
  pinMode(O_R4, OUTPUT);
  pinMode(O_R5, OUTPUT);
  pinMode(O_R6, OUTPUT);
  pinMode(O_R7, OUTPUT);
  pinMode(O_C3, OUTPUT);
  pinMode(O_C4, OUTPUT);
  pinMode(O_C5, OUTPUT);
  resetOutputs();
}

void resetOutputs() {
  digitalWrite(O_R2, LOW);
  digitalWrite(O_R3, LOW);
  digitalWrite(O_R4, LOW);
  digitalWrite(O_R5, LOW);
  digitalWrite(O_R6, LOW);
  digitalWrite(O_R7, LOW);
  digitalWrite(O_C3, LOW);
  digitalWrite(O_C4, LOW);
  digitalWrite(O_C5, LOW);
}

void loop() {
  digitalWrite(I_R2, LOW);
  checkColumn();
  //resetOutputs();
  digitalWrite(I_R2, HIGH);
  digitalWrite(I_R3, LOW);
  checkColumn();
  //resetOutputs();
  digitalWrite(I_R3, HIGH);
  digitalWrite(I_R4, LOW);
  checkColumn();
  //resetOutputs();
  digitalWrite(I_R4, HIGH);
  digitalWrite(I_R5, LOW);
  checkColumn();
  //resetOutputs();
  digitalWrite(I_R5, HIGH);
  digitalWrite(I_R6, LOW);
  checkColumn();
  //resetOutputs();
  digitalWrite(I_R6, HIGH);
  digitalWrite(I_R7, LOW);
  checkColumn();
  //resetOutputs();
  digitalWrite(I_R7, HIGH);
}

void checkColumn() {
  if (digitalRead(I_C3) == 0) {
    if (digitalRead(I_R7) == 0) {
      debounce(1);
      //resetOutputs();
      //digitalWrite(O_C3, HIGH);
      //digitalWrite(O_R7, HIGH);
    }
    else if (digitalRead(I_R6) == 0) {
      debounce(2);
      //resetOutputs();
      //digitalWrite(O_C3, HIGH);
      //digitalWrite(O_R6, HIGH);
    }
  }
  
  else if (digitalRead(I_C4) == 0) {
    if (digitalRead(I_R4) == 0) {
      debounce(3);
      if (digitalRead(O_R4) == 0) {
        digitalWrite(O_C4, HIGH);
      }

    }
    else if (digitalRead(I_R6) == 0) {
      debounce(4);
      if (digitalRead(O_R6) == 0) {
        digitalWrite(O_C4, HIGH);
      }
    }
    else if (digitalRead(I_R5) == 0) {
      debounce(5);
      if (digitalRead(O_R5) == 0) {
        digitalWrite(O_C4, HIGH);
      }
    }
    else if (digitalRead(I_R3) == 0) {
      debounce(6);
      if (digitalRead(O_R6) == 0) {
        digitalWrite(O_C4, HIGH);
      }
    }
    else if (digitalRead(I_R7) == 0) {
      debounce(7);
      if (digitalRead(O_R7) == 0) {
        digitalWrite(O_C4, HIGH);
      }
    }
  }

  else if (digitalRead(I_C5) == 0) {
    if (digitalRead(I_R3) == 0) {
      debounce(8);
      if (digitalRead(O_R3) == 0) {
        digitalWrite(O_C5, HIGH);
      }
    }
    else if (digitalRead(I_R4) == 0) {
      debounce(9);
      if (digitalRead(O_R4) == 0) {
        digitalWrite(O_C5, HIGH);  
      }
    }
    else if (digitalRead(I_R7) == 0) {
      debounce(CLOCK);
      if (digitalRead(O_R7) == 0) {
        digitalWrite(O_C5, HIGH);
      }
    }
    else if (digitalRead(I_R6) == 0) {
      debounce(0);
      if (digitalRead(O_R6) == 0) {
        digitalWrite(O_C5, HIGH);
      }
    }
    else if (digitalRead(I_R5) == 0) {
      debounce(RESET);
      if (digitalRead(O_R5) == 0) {
        digitalWrite(O_C5, HIGH);
      }
    }
  }
}

void copyInputs() {
  if (digitalRead(I_R6) == 1) {
    digitalWrite(O_R6, HIGH);
  }
  else {
    digitalWrite(O_R6, LOW);
  }

  if (digitalRead(I_C3) == 1) {
    digitalWrite(O_C3, HIGH);
  }
  else {
    digitalWrite(O_C3, LOW);
  }
}

void debounce(int num) {
  if (num != lastButton){
    lastDebounceTime = millis();
    lastButton = num;
  }

  if ((millis() - lastDebounceTime) > debounceDelay){
    if (num == lastButton){
      Serial.println(String(num));
    }
  }
}
