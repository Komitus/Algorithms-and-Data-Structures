import matplotlib.pyplot as plt
import pandas as pd
import os
import math

csv_name = "./output.csv"
operations = ["insert", "priority", "pop"]
colors = ['-b', '-r', '-g']

fig, ax = plt.subplots()
df = pd.read_csv(csv_name, sep=';')
n = df['n']

for operation in operations:
    y = df[operation]
    ax.plot(n, y, colors[operations.index(operation)], label=operation)
 
lgN = []
for i in range (0, len(n)):
    lgN.append(math.log(n[i],2))
ax.plot(n, lgN, '-k', label="lg2(n)")
            
ax.set_title("Operations (N)")
ax.set_xlabel('N')
ax.set_ylabel("Operation (N)")
ax.legend()

png_name = "plot.png"
fig.savefig(png_name, bbox_inches="tight", dpi=1000)
plt.close()