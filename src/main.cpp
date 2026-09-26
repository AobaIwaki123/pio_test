#include <Arduino.h>
#include <math.h>

// ピン設定
const int PIN_LED0 = D0;       // 1つ目のLED / MOSFET
const int PIN_LED1 = D1;       // 2つ目のLED / MOSFET

// PWM チャンネル設定
const int CH_LED0 = 0;         // チャンネル 0
const int CH_LED1 = 1;         // チャンネル 1

// PWM パラメータ
const int PWM_FREQ = 5000;     // 周波数 5kHz
const int PWM_RES = 8;         // 8bit (0 〜 255)
const int MAX_DUTY = 25;       // 最大輝度を約1/10に制限 (255 / 10 ≈ 25)

void setup() {
  // LED0 (D0) の PWM 初期化
  ledcSetup(CH_LED0, PWM_FREQ, PWM_RES);
  ledcAttachPin(PIN_LED0, CH_LED0);

  // LED1 (D1) の PWM 初期化
  ledcSetup(CH_LED1, PWM_FREQ, PWM_RES);
  ledcAttachPin(PIN_LED1, CH_LED1);
}

void loop() {
  // 0 〜 2π まで角度を進める
  for (float rad = 0; rad < 2 * PI; rad += 0.02) {
    // D0 のデューティ比 (0 〜 MAX_DUTY)
    int duty0 = (sin(rad - PI / 2) + 1.0) / 2.0 * MAX_DUTY;

    // D1 は反対の明るさにする (MAX_DUTY 〜 0)
    int duty1 = MAX_DUTY - duty0;

    ledcWrite(CH_LED0, duty0);
    ledcWrite(CH_LED1, duty1);

    delay(10);
  }
}
