#define in1 6 //L298n Motor
#define in2 7
#define in3 8
#define in4 9
#define sikat 5
#define pompa 4
int command; //untuk menyimpan status perintah aplikasi.
int Speed = 150; // 0 - 255.
int Speedsec;
int buttonState = 0;
int lastButtonState = 0;
int Turnradius = 0; //Atur radius belokan, 0 - 255 Catatan: robot akan mengalami malfungsi jika ini lebih tinggi dari Kecepatan int.
int brakeTime = 10;
int brkonoff = 1; //1 untuk sistem pengereman elektronik, 0 untuk normal.
void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(pompa, OUTPUT);
  pinMode(sikat, OUTPUT); //Setting sikat
  Serial.begin(9600);  //Setel baud rate ke modul Bluetooth Anda.
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
    Stop(); //Inisialisasi dengan motor berhenti.
    switch (command) {
      case 'F':
        forward();
        break;
      case 'B':
        back();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'G':
        forwardleft();
        break;
      case 'I':
        forwardright();
        break;
      case 'H':
        backleft();
        break;
      case 'J':
        backright();
        break;
      case 'w':
        sikaton();
        break;
      case 'W':
        sikatoff();
        break;
      case 'u':
        pompaon();
        break;
      case 'U' :
        pompaoff();
        break;
      case '0':
        Speed = 0;
        break;
      case '1':
        Speed = 100;
        break;
      case '2':
        Speed = 120;
        break;
      case '3':
        Speed = 165;
        break;
      case '4':
        Speed = 178;
        break;
      case '5':
        Speed = 191;
        break;
      case '6':
        Speed = 204;
        break;
      case '7':
        Speed = 216;
        break;
      case '8':
        Speed = 229;
        break;
      case '9':
        Speed = 242;
        break;
      case 'q':
        Speed = 255;
        break;
    }
    Speedsec = Turnradius;
    if (brkonoff == 1) {
      brakeOn();
    } else {
      brakeOff();
    }
  }
}

void forward() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speed);
}

void back() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speed);
}

void left() {
  analogWrite(in3, Speed);
  analogWrite(in2, Speed);
}

void right() {
  analogWrite(in4, Speed);
  analogWrite(in1, Speed);
}
void forwardleft() {
  analogWrite(in1, Speedsec);
  analogWrite(in3, Speed);
}
void forwardright() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speedsec);
}
void backright() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speedsec);
}
void backleft() {
  analogWrite(in2, Speedsec);
  analogWrite(in4, Speed);
}

void Stop() {
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);
}
void sikaton() {
digitalWrite(sikat,HIGH);
}
void sikatoff() {
digitalWrite(sikat,LOW);
}
void pompaon() {
digitalWrite(pompa,HIGH);
}
void pompaoff() {
digitalWrite(pompa,LOW);
}
void brakeOn() {
  //Inilah kegunaan masa depan: sistem pengereman elektronik!
  // baca pin masukan tombol tekan:
  buttonState = command;
  // bandingkan keadaan tombol dengan keadaan sebelumnya
  if (buttonState != lastButtonState) {
    // jika status telah berubah, tambahkan penghitung
    if (buttonState == 'S') {
      if (lastButtonState != buttonState) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, HIGH);
        delay(brakeTime);
        Stop();
      }
    }
   // simpan status saat ini sebagai status terakhir,
    //untuk waktu berikutnya melalui loop
    lastButtonState = buttonState;
  }
}
void brakeOff() {

}
