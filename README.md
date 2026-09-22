# Análise de Consumo Energético com Loop Perforation em IoT

Repositório do projeto de PIBIC desenvolvido na UFT, com foco na análise do impacto da técnica de aproximação de código *Loop Perforation* no consumo energético de dispositivos IoT.

## Estrutura do Repositório

matriz_normal/ # Código C++ para o Raspberry Pi Pico 2W

py/ # Scripts Python para coleta e análise

Esp82/ # Código Arduino para o NodeMCU ESP8266

Dados gerados após a execução dos códigos


## Hardware Necessário

- Raspberry Pi Pico 2W
- NodeMCU ESP8266
- Sensor INA226
- STEMTera (usada como protoboard)
- Jumpers

## Configuração e Execução

### 1. Raspberry Pi Pico 2W

**Pré-requisitos:**
- [pico-sdk](https://github.com/raspberrypi/pico-sdk)
- VS Code com extensão [Raspberry Pi Pico](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico)

**Passos:**
1. Abra a pasta `matriz_normal/` no VS Code
2. Ajuste o `MAT_SIZE` no início do arquivo `.cpp` conforme o tamanho desejado (40, 80, 120, 160 ou 200)
3. Descomente a técnica desejada (`mul_mat_norm`, `mul_mat_mod` ou `mul_mat_trunc`) e os prints correspondentes
4. Compile com **Compile Project** na extensão
5. Grave com **Run Project (USB)**

### 2. NodeMCU ESP8266 (Leitor)

**Pré-requisitos:**
- Arduino IDE com suporte ao ESP8266
- Bibliotecas: `INA226` (Rob Tillaart), `SoftwareSerial`

**Passos:**
1. Abra o arquivo na pasta `Esp82/` na Arduino IDE
2. Selecione a placa **NodeMCU 1.0 (ESP-12E Module)**
3. Grave normalmente via USB

### 3. Coleta de Dados de Tempo e Energia

1. Com o Pico 2W e o ESP8266 gravados e conectados, rode o script de coleta:
```bash
cd matriz_normal/py
py bizarro.py
```
2. Reconecte o USB do Pico para iniciar a coleta
3. O CSV será salvo automaticamente na mesma pasta

### 4. Cálculo das Métricas de Erro

1. Rode o código do Pico para cada técnica separadamente e salve as matrizes resultado com o script de coleta
2. Com os três arquivos gerados (`matriz_normal_N.csv`, `matriz_modular_N.csv`, `matriz_truncation_N.csv`), rode:
```bash
py calcular_erros.py
```

## Observações

- O `MAT_SIZE` e a técnica precisam ser ajustados manualmente antes de cada compilação no Pico
- O script Python deve ser iniciado **antes** de reconectar o USB do Pico
- Para tamanhos de matriz acima de 160, o cálculo de métricas de erro é feito via script Python por limitação de RAM do Pico
