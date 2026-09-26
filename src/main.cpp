#include <Arduino.h>
#include <math.h>

const int PWM_PIN = D0;        // MOSFET ゲートにつなぐピン
const int PWM_CHANNEL = 0;     // 使用する PWM チャンネル
const int PWM_FREQ = 5000;     // 周波数 5kHz
const int PWM_RES = 8;         // 8bit (0 〜 255)
const int MAX_DUTY = 25;       // 最大輝度を約1/10に制限 (255 / 10 ≈ 25)


void setup() {
  Serial.begin(115200);

  // PWM の初期化とピン接続
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RES);
  ledcAttachPin(PWM_PIN, PWM_CHANNEL);

  Serial.println("Breathing LED started on D0!");
}

void loop() {
  // 0度 から 360度（0 〜 2π）まで少しずつ角度を進める
  for (float rad = 0; rad < 2 * PI; rad += 0.02) {
    int duty = (sin(rad - PI / 2) + 1.0) / 2.0 * MAX_DUTY;

    ledcWrite(PWM_CHANNEL, duty);

    // 点滅スピードの調整（値を小さくすると速く、大きくするとゆっくり）
    delay(10);
  }
}
