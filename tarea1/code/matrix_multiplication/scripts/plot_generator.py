import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import glob
import os

sns.set(style="whitegrid")

files = glob.glob("../data/measurements/*.txt")
data_list = []

for file in files:
    with open(file, "r") as f:
        for line in f:
            parts = line.strip().split("|")
            if len(parts) != 4:
                continue

            filename, algoritmo, tiempo, memoria = [p.strip() for p in parts]

            nombre = filename.replace(".txt", "")
            partes_nombre = nombre.split("_")

            try:
                dim = int(partes_nombre[0])
                distribucion = partes_nombre[1] 
            except Exception as e:
                print("Error parseando nombre:", filename, "|", e)
                continue

            try:
                tiempo_val = float(tiempo.split()[0])
                memoria_val = float(memoria.split()[0]) / 1024.0
            except Exception as e:
                print("Error parseando tiempo/memoria en", filename, "|", e)
                continue

            data_list.append({
                "Dimensión": dim,
                "Algoritmo": algoritmo,
                "Distribucion": distribucion,  
                "Tiempo_ms": tiempo_val,
                "Memoria_MB": memoria_val
            })

df = pd.DataFrame(data_list)
df = df.sort_values("Dimensión")

# === Graficar tiempo ===
plt.figure(figsize=(10,6))
sns.lineplot(data=df, x="Dimensión", y="Tiempo_ms", hue="Algoritmo", marker="o")
plt.yscale("log")  
plt.title("Comparación de tiempos por algoritmo de multiplicación de matrices")
plt.xlabel("Dimensión de la matriz (N)")
plt.ylabel("Tiempo (ms)")
plt.xticks(df["Dimensión"].unique())  
plt.legend(title="Algoritmo")
plt.tight_layout()
os.makedirs("../data/plots", exist_ok=True)
plt.savefig("../data/plots/tiempos_matrices.png")
plt.show()

# === Graficar memoria ===
plt.figure(figsize=(10,6))
sns.lineplot(data=df, x="Dimensión", y="Memoria_MB", hue="Algoritmo", marker="o")
plt.title("Comparación de memoria por algoritmo de multiplicación de matrices")
plt.xlabel("Dimensión de la matriz (N)")
plt.ylabel("Memoria usada (MB)")
plt.xticks(df["Dimensión"].unique())
plt.legend(title="Algoritmo")
plt.tight_layout()
plt.savefig("../data/plots/memoria_matrices.png")
plt.show()

# === Graficar por distribución ===
df_dim16 = df[df["Dimensión"] == 16]  

plt.figure(figsize=(8,6))
sns.barplot(
    data=df_dim16,
    x="Distribucion",
    y="Tiempo_ms",
    hue="Algoritmo",
    palette="viridis"
)

plt.title("Comparación de algoritmos según distribución (N = 16)")
plt.xlabel("Distribución de la matriz")
plt.ylabel("Tiempo (ms)")
plt.tight_layout()

plt.savefig("../data/plots/tiempo_matrices_por_distribucion.png")
plt.show()