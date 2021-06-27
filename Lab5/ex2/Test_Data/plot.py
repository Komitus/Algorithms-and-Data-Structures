import matplotlib.pyplot as plt
import pandas as pd
import math

csv_name = "./output.csv"

fig, ax = plt.subplots()
df = pd.read_csv(csv_name, sep=';')
V = df['|V|']
E = df['|E|']
comps = df['compares']
ElogV = []
for i in range (0, len(V)):
    val = E[i]*math.log(V[i])
    ElogV.append(val)

ax.plot(ElogV, comps, '-b', label="compares")      
ax.plot(ElogV, ElogV, '-k', label="E*log(V)")     
ax.set_title("Compares ( E*log(V) )")
ax.set_xlabel('E*log(V)')
ax.set_ylabel("Compares ( E*log(V) )")
ax.legend()

png_name = "plot.png"
fig.savefig(png_name, bbox_inches="tight", dpi=1000)
plt.close()