// trap monitor

 int reedswitch = D1; // reedswitch

 int led = D6; // LED

 bool gateShut = false; // are we blinking?
 bool lastGateStatus = false;

 int intGateShut = 0; // variable
 int intSleepSeconds = 300;

 //Timer timer(5000, statusReport);


 void setup() {

     Serial.begin(9600); // start serial

     pinMode(led,OUTPUT); // Our LED pin is output (lighting up the LED)

     pinMode(reedswitch,INPUT_PULLUP); // gate sensor

     // We are going to declare a Particle.variable() here so that we can access the value.
     Particle.variable("intGateShut", &intGateShut, INT);

     Particle.publish("status","setup",60,PRIVATE);

     //timer.start();

 }


 // Next is the loop function...

 void loop() {

     // check the gate state
     if (digitalRead(reedswitch) == LOW) {
         gateShut=true;
         intGateShut = 1;
     }
     else
     {
         gateShut=false;
         intGateShut = 0;
     }

     if (lastGateStatus != gateShut) {

         //status has changed - flipflop
         lastGateStatus = gateShut;

         Particle.publish("statusGate",String(intGateShut),60,PRIVATE);

     }
     else {
         //Particle.publish("sleeping",String(intSleepSeconds),60,PRIVATE);
         //System.sleep(SLEEP_MODE_DEEP, intSleepSeconds);
     }


     if (gateShut) {
         // blink
         digitalWrite(led,HIGH);
     }
     else {
         digitalWrite(led,LOW);
     }
     delay(100);

 }


 void statusReport(){

     Particle.publish("statusReport","start",60,PRIVATE);

     //CellularSignal sig = Cellular.RSSI();

     // sig.qual - 0 - 49 (higher is better) so x 2 for %
     //sig.rssi signal strength with range -113dBm to -51dBm (in 2dBm steps)
     //String sRSSI = String("RSSI:")+String(sig.rssi) + String("db - Quality:") + String((sig.qual*2)) + String("%");
     //Serial.println(sRSSI);

     FuelGauge fuel;

     // fuel.getVCell battery voltage
     // fuel.getSoC 0 - 100%
     String sFuel = String("fuel.getVCell():") + String(fuel.getVCell()) + String(" fuel.getSoC():") + String(fuel.getSoC());
     Serial.println(sFuel);


     Particle.publish("statusReport","end",60,PRIVATE);

 }
