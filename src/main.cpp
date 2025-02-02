/*
    2021 - Programme robot

    Si capteur gauche n'est plus sur la ligne alors aller à droite
    Si capteur droite n'est plus sur la ligne alors aller à gauche

    Si plus de ligne alors aller tout droit

    Motor :
     - 11 / 13
     - 10 / 12
    Capteur Ligne noir
     - XX / XX <- DigitalRead
    Capteur Contact:
     - XX <- DigitalRead
    Capteur Distance;
     - Xx <- AnalogRead

*/

/* Port */

#define aread(_) analogRead(_)
#define dread(_) digitalRead(_)
#define sprintln(_) Serial.println(_)

#define board_led  13
#define port_motor_left 10
#define port_motor_left_speed 5
#define port_motor_right 11
#define port_motor_right_speed 6
#define r_sensor_view 5
#define l_sensor_view 9 // digitalRead -> 1 / 0 
#define speed 300

void setup()
{
    pinMode(port_motor_left, OUTPUT);
    pinMode(port_motor_right, OUTPUT);
    pinMode(port_motor_left_speed, OUTPUT);
    pinMode(port_motor_right_speed, OUTPUT);           
    pinMode(board_led, OUTPUT);           
    Serial.begin(9600);
    
    doBlink(10, 100);
}


void loop()
{  
    forward();
}

void forward()
{
    motor(port_motor_left, port_motor_left_speed, HIGH, speed);
    motor(port_motor_right, port_motor_right_speed, HIGH, speed);
}

void go_right()
{
    motor(port_motor_left, port_motor_left_speed, HIGH, 0);
    motor(port_motor_right, port_motor_right_speed, HIGH, speed);
}

void go_left()
{
    motor(port_motor_left, port_motor_left_speed, HIGH, speed);
    motor(port_motor_right, port_motor_right_speed, HIGH, 0);
}

void motor(int port, int port_speed, int digital_write, int analogvalue)
{
    digitalWrite(port, digital_write);
    analogWrite(port_speed, analogvalue);
}

void get_value_of_view_sensor(byte pdata[2]) {
    Serial.println(String(analogRead(l_sensor_view)));
    Serial.println(String(analogRead(r_sensor_view)));

    pdata[0] = analogRead(r_sensor_view);
    pdata[1] = analogRead(l_sensor_view);
}

int get_value_of_line_sensor(int port) {
    return dread(port);
}

bool is_black(int port) {
     if (!dread(port)) {
        return true;
    } else {
        return false;
    }
}


void doBlink(int times, int delayTime){
  for(int i=0; i<times; i++){
    digitalWrite(board_led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(delayTime);              // wait for a second
    digitalWrite(board_led, LOW);    // turn the LED off by making the voltage LOW
    delay(delayTime);              // wait for a second    
  }
}
