import serial
from datetime import datetime

PORTA = 'COM12'
BAUD = 9600
TECNICA = 'truncation'  # ALTERAR: normal, modular, truncation
ARQUIVO = f'matriz_{TECNICA}_200.csv'

ser = serial.Serial(PORTA, BAUD, timeout=30)
print(f"Aguardando dados... salvando em {ARQUIVO}")

salvando = False
linhas = []

while True:
    linha = ser.readline().decode('utf-8', errors='ignore').strip()
    if not linha:
        continue
    print(linha[:50])

    if linha.startswith('INICIO_'):
        salvando = True
        continue

    if linha == 'FIM':
        break

    if salvando:
        linhas.append(linha)

with open(ARQUIVO, 'w') as f:
    for l in linhas:
        f.write(l + '\n')

print(f"Salvo {len(linhas)} linhas em {ARQUIVO}")
ser.close()