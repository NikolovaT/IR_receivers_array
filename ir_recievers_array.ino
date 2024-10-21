#define DATA_PIN 2
#define CLOCK_PIN 3
#define LATCH_PIN 4
#define NUM_BITS 8
#define ROW_SIZE 5

float dist_between_rows = 1;
float radius = 0;
float angle_rad = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(DATA_PIN, INPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
}

void  loop() {
  digitalWrite(LATCH_PIN, LOW);
  digitalWrite(LATCH_PIN, HIGH);

  for (int i = 0; i < NUM_BITS; i++) {
    int bit = digitalRead(DATA_PIN);
    if (bit == LOW) {
      Serial.print("Transmiter is over Reciver No.");
      Serial.print(i+1);

      radius = find_radius(i/ROW_SIZE, i%ROW_SIZE);
      angle_rad = find_angle(i/ROW_SIZE, i%ROW_SIZE);

      Serial.print("\t distance to center: ");  
      Serial.print(radius);
      Serial.print("\t angle in rad compared to west: ");  
      Serial.print(angle_rad); 
      Serial.println("\t"); 

      move(radius, angle_rad);
    }
    digitalWrite(CLOCK_PIN, HIGH); 
    digitalWrite(CLOCK_PIN, LOW);
  }

  delay(100);
}

void move(float radius, float angle_rad){
  // move drone radius distance in direction east - angle_rad 
  // then land()
}

void land(){

}

float find_radius(int x, int y){
  float r;
  if(x == 2){
    r = abs(2-y)*dist_between_rows;
    return r;
  }
  else if(y == 2){
    r = abs(2-x)*dist_between_rows;
    return r;
  }
  r = sqrt(pow(abs(2-x), 2) + pow(abs(2-y), 2))*dist_between_rows;
  return r;
}

float find_angle(int x, int y){
  float a;
  if(x == 2){
    a = 1.57; 
    return a;
  }
  else if(y == 2){
    a = 0;
    return a;
  }  
  a = atan(abs(2-y)/abs(2-x));
  return a;
}
