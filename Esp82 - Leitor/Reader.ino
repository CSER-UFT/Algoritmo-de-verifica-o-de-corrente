#include <Wire.h>
#include <INA226.h>
#include <SoftwareSerial.h>

INA226 ina(0x40);
SoftwareSerial picoSerial(13, -1); // RX=D7

bool coletando = true;
String tecnicaAtual = "";
String execAtual = "";
String tamanhoAtual = "";

void setup() {
  Serial.begin(9600);
  picoSerial.begin(4800);
  Wire.begin(4, 5);
  ina.begin();
  ina.setMaxCurrentShunt(0.3, 0.1);
  Serial.println("timestamp_ms,exec,tamanho,tecnica,corrente_mA,tensao_V,potencia_mW,tempo_ms");
}

void loop() {
  if (!coletando) return;

  // Lê mensagens do Pico
  if (picoSerial.available()) {
    String msg = picoSerial.readStringUntil('\n');
    msg.trim();

    if (msg == "FIM_COLETA") {
      Serial.println("FIM_COLETA_RECEBIDO");
      coletando = false;
      return;
    }

    if (msg.startsWith("INICIO_")) {
      // Formato: INICIO_TECNICA|exec|tamanho
      int p1 = msg.indexOf('|');
      int p2 = msg.lastIndexOf('|');
      tecnicaAtual = msg.substring(6, p1); // NORMAL, MODULAR ou TRUNCATION
      execAtual = msg.substring(p1 + 1, p2);
      tamanhoAtual = msg.substring(p2 + 1);
    }

    if (msg.startsWith("FIM_")) {
      // Formato: FIM_TECNICA|exec|tamanho|tempo
      int p3 = msg.lastIndexOf('|');
      String tempo = msg.substring(p3 + 1);

      float corrente = ina.getCurrent() * 1000;
      float tensao   = ina.getBusVoltage();
      float potencia = ina.getPower() * 1000;

      Serial.print(millis()); Serial.print(",");
      Serial.print(execAtual); Serial.print(",");
      Serial.print(tamanhoAtual); Serial.print(",");
      Serial.print(tecnicaAtual); Serial.print(",");
      Serial.print(corrente, 2); Serial.print(",");
      Serial.print(tensao, 3); Serial.print(",");
      Serial.print(potencia, 2); Serial.print(",");
      Serial.println(tempo);
    }
  }

  // Lê INA226 continuamente
  float corrente = ina.getCurrent() * 1000;
  float tensao   = ina.getBusVoltage();
  float potencia = ina.getPower() * 1000;

  Serial.print(millis()); Serial.print(",");
  Serial.print(execAtual); Serial.print(",");
  Serial.print(tamanhoAtual); Serial.print(",");
  Serial.print(tecnicaAtual); Serial.print(",");
  Serial.print(corrente, 2); Serial.print(",");
  Serial.print(tensao, 3); Serial.print(",");
  Serial.print(potencia, 2); Serial.print(",");
  Serial.println("");

  delay(100);
}