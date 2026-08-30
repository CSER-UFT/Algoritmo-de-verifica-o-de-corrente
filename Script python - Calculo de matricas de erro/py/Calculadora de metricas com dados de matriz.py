import numpy as np

def ler_matriz(arquivo):
    matriz = []
    with open(arquivo) as f:
        for linha in f:
            linha = linha.strip()
            if linha:
                matriz.append([int(x) for x in linha.split(';') if x])
    return np.array(matriz, dtype=np.float64)

normal    = ler_matriz('matriz_normal_200.csv')
modular   = ler_matriz('matriz_modular_200.csv')
truncation = ler_matriz('matriz_truncation_200.csv')

def calcular_metricas(ac, ax, nome):
    ed = np.abs(ac - ax)
    n = ac.size
    mae  = np.mean(ed)
    wce  = np.max(ed)
    mred = np.mean(ed[ac != 0] / np.abs(ac[ac != 0]))
    mse  = np.mean(ed ** 2)
    ed_total = np.sum(ed)
    print(f"\n{nome}:")
    print(f"  ED_total : {ed_total:.2f}")
    print(f"  MAE      : {mae:.2f}")
    print(f"  WCE      : {wce:.2f}")
    print(f"  MRED     : {mred:.6f} ({mred*100:.2f}%)")
    print(f"  MSE      : {mse:.2f}")

calcular_metricas(normal, modular,    "MODULAR")
calcular_metricas(normal, truncation, "TRUNCATION")