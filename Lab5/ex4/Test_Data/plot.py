import matplotlib.pyplot as plt
import pandas as pd
import math

csv_name = "./steps.csv"

fig, ax = plt.subplots()
df = pd.read_csv(csv_name, sep=';')

Rand = df['Rand']
Weight = df['Weight']
Prim = df['Prim']
Kruskal = df['Kruskal']
ElogV = []
V = ['|V|']
E = df['|E|']
for i in range (0, len(V)):
    val = E[i]*math.log(V[i])
    ElogV.append(val)

ax.plot(ElogV, ElogV, '-k', label="E*log(V)")  
ax.plot(ElogV, Rand, '-m', label="Rand")  
ax.plot(ElogV, Weight, '-y', label="Weight")  
ax.plot(ElogV, Prim, '-b', label="Prim")     
ax.plot(ElogV, Kruskal, '-r', label="Kruskal")     
  
ax.set_title("Steps ( E*log(V) )")
ax.set_xlabel('E*log(V)')
ax.set_ylabel("Steps ( E*log(V) )")
ax.legend()

png_name = "plot.png"
fig.savefig(png_name, bbox_inches="tight", dpi=1000)
plt.close()