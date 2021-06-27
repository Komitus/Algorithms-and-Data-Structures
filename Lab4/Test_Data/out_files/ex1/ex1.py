import matplotlib.pyplot as plt
import pandas as pd
import os
import math

directoriesCSV = ["./csv/lotr/", "./csv/aspell/"]
directoresPLT = ["./plots/lotr/", "./plots/aspell/"]
colors = ['-b', '-r', '-g']
treesNames = ['BST', 'RBT', 'SPL']
for directory in directoriesCSV:
    for file in os.listdir(directory):
        filename = os.fsdecode(file)
        
        fig, ax = plt.subplots()
        df = pd.read_csv(os.path.join(directory, filename), sep=';')
        n = df['n']
        for tree in treesNames:
            y = df[tree]
            ax.plot(n, y, colors[treesNames.index(tree)], label=tree)

        statName = filename[0:len(filename)-4]
        if not "time" in statName:
            logN = []
            for i in range (0, len(n)):
                logN.append(math.log(n[i],2))
            ax.plot(n, logN, '-k', label="log(n)")
            
        ax.set_title(statName)
        ax.set_xlabel('n')
        ax.set_ylabel(statName)
        ax.legend()

        png_name = directoresPLT[directoriesCSV.index(directory)] + statName + ".png"
        fig.savefig(png_name, bbox_inches="tight", dpi=1000)
        plt.close()
