#define TurningChannel 11   // Connects to receiver channel 1
#define MovingChannel 3    // Connects to receiver channel 2
#define ThrortleChannel 5  // Connects to receiver channel 5

// Motor A Pins
#define speedAPin 10
#define in1 9
#define in2 8

// Motor B Pins
#define speedBPin 6
#define in3 5
#define in4 4

enum TurningDirection
{
  none = 0,
  left = 1,
  right = 2
};

enum MovingDirection
{
  stopped = 0,
  forward = 1,
  backward = 2
};

void setup() {
  // put your setup code here, to run once:
  pinMode(TurningChannel, INPUT);
  pinMode(MovingChannel, INPUT);
  pinMode(ThrortleChannel, INPUT);
  Serial.begin(9600);


  //Motor A Begin
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  //Motor A END

  //Motor B Begin
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  //Motor B End
}



void loop() {
  // put your main code here, to run repeatedly:
  int speed = CalcSpeed();
  MovingDirection direction = GetDirection();
  TurningDirection turning = GetTurningDirection();
  Move(speed, direction, turning);
}

void Move(int speed, MovingDirection direction, TurningDirection turning)
{
  MoveMotorA(speed, direction, turning);
  MoveMotorB(speed, direction, turning);
}

void MoveMotorA(int speed, MovingDirection direction, TurningDirection turning)
{
  if (turning == left)
  {
    speed /= 2;
  }

  if (direction == forward)
  {
    Serial.println("moving forward");
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(speedAPin, speed);
  }
  else if (direction == backward)
  {
    Serial.println("moving backward");
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(speedAPin, speed);
  }
  else
  {
    
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(speedAPin, 0);
  }
}

void MoveMotorB(int speed, MovingDirection direction, TurningDirection turning)
{
     if (turning == right)
  {
    speed /= 2;
  }

  if (direction == forward)
  {
    Serial.println("moving forward");
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(speedBPin, speed);
  }
  else if (direction == backward)
  {
    Serial.println("moving backward");
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(speedBPin, speed);
  }
  else
  {
    
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    analogWrite(speedBPin, 0);
  }
}

int CalcSpeed()
{
  //return readChannel(ThrortleChannel, 200, 250, 200);
  return 250; 
}

MovingDirection GetDirection()
{
  int value = readChannel(MovingChannel, -100, 100, 0);

  if (value >= 5)
  {
    return forward;
  }
  else if (value <= -5)
  {
    return backward;
  }
  else
  {
    return stopped;
  }
}

TurningDirection GetTurningDirection()
{
  int value = readChannel(TurningChannel, -100, 100, 0);

  if (value >= 5)
  {
    return right;
  }
  else if (value <= -5)
  {
    return left;
  }
  else
  {
    return none;
  }
}


// Obtained from https://gist.github.com/werneckpaiva/196b08a715cf5099b66321dd0c4adbb5
// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
