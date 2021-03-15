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

int port_motor_left = 10;
int port_motor_left_speed = 5;
int port_motor_right = 11;
int port_motor_right_speed = 6;
int r_sensor_view = 5;
int l_sensor_view = 4;
int value = -1;
int speed = 150;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    forward();

    sprintln(get_value_of_line_sensor(l_sensor_view));
    sprintln(get_value_of_line_sensor(r_sensor_view));
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