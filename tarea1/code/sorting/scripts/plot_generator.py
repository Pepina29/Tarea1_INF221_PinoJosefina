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

            N = int(partes_nombre[0])
            distribucion = partes_nombre[1]  

            tiempo = float(tiempo.split()[0])
            memoria_MB = float(memoria.split()[0]) / 1024

            data_list.append({
                "N": N,
                "Algoritmo": algoritmo,
                "Distribucion": distribucion,
                "Tiempo_ms": tiempo,
                "Memoria_MB": memoria_MB
            })

df = pd.DataFrame(data_list)

# === Graficar tiempos ===
plt.figure(figsize=(10,6))
sns.lineplot(data=df, x="N", y="Tiempo_ms", hue="Algoritmo", marker="o")
plt.xscale("log")  
plt.yscale("log")  
plt.title("Comparación de tiempos por algoritmo")
plt.xlabel("Tamaño del array (N)")
plt.ylabel("Tiempo (ms)")
plt.legend(title="Algoritmo")
plt.tight_layout()
os.makedirs("../data/plots", exist_ok=True)
plt.savefig("../data/plots/tiempos_algoritmos.png")
plt.show()



# ===  Graficar memoria  ===
plt.figure(figsize=(10,6))
sns.barplot(data=df, x="N", y="Memoria_MB", hue="Algoritmo", palette="viridis")
plt.title("Comparación de memoria por algoritmo")
plt.xlabel("Tamaño del array (N)")
plt.ylabel("Memoria usada (MB)")
plt.ylim(bottom=0)  

for p in plt.gca().patches:
    height = p.get_height()
    plt.text(p.get_x() + p.get_width()/2., height + 0.02, f'{height:.2f}', 
             ha="center", va="bottom", fontsize=8)

plt.legend(title="Algoritmo")
plt.tight_layout()
os.makedirs("../data/plots", exist_ok=True)
plt.savefig("../data/plots/memoria_algoritmos_barras.png")
plt.show()


# === Graficar tiempos para N = 10^1 ===
df_n10 = df[df["N"] == 10]  

plt.figure(figsize=(8,6))
sns.barplot(data=df_n10, x="Algoritmo", y="Tiempo_ms", palette="viridis")
plt.title("Tiempo de ejecución por algoritmo (N = 10¹)")
plt.xlabel("Algoritmo")
plt.ylabel("Tiempo (ms)")
plt.tight_layout()
plt.savefig("../data/plots/tiempo_algoritmos_N10_barra.png")
plt.show()

# === Graficar tiempos para N = 10^3 ===
df_n1000 = df[df["N"] == 1000]  

plt.figure(figsize=(8,6))
sns.barplot(data=df_n1000, x="Algoritmo", y="Tiempo_ms", palette="viridis")
plt.title("Tiempo de ejecución por algoritmo (N = 10³)")
plt.xlabel("Algoritmo")
plt.ylabel("Tiempo (ms)")
plt.tight_layout()
plt.savefig("../data/plots/tiempo_algoritmos_N100_barra.png")
plt.show()


# === Graficar tiempos para N = 10^5 ===
df_n100000 = df[df["N"] == 100000] 

plt.figure(figsize=(8,6))
sns.barplot(data=df_n100000, x="Algoritmo", y="Tiempo_ms", palette="viridis")
plt.title("Tiempo de ejecución por algoritmo (N = 10⁵)")
plt.xlabel("Algoritmo")
plt.ylabel("Tiempo (ms)")
plt.tight_layout()
plt.savefig("../data/plots/tiempo_algoritmos_N100000_barra.png")
plt.show()

# === Graficar por distribución ===
df_n100k = df[df["N"] == 100000]  

plt.figure(figsize=(10,6))
sns.barplot(
    data=df_n100k,
    x="Distribucion",
    y="Tiempo_ms",
    hue="Algoritmo",
    palette="viridis"
)

plt.title("Comparación de tiempos según distribución (N = 10⁵)")
plt.xlabel("Distribución de los datos")
plt.ylabel("Tiempo (ms)")
plt.tight_layout()

plt.savefig("../data/plots/tiempo_por_distribucion.png")
plt.show()