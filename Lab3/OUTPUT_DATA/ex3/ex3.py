import matplotlib.pyplot as plt
import pandas as pd
import glob
import re
import math

y = [[[0]*100]*2]*5
positions = ["begin", "mid", "end", "rand", "outside"]
stat_type = ['compares', 'time']
colors = ['-b', '-r', '-g', '-k', '-c']
for stat in range(0,2):

    fig, ax = plt.subplots()
    for elem_position in range(0,5):
            
        filename = "./csv/"+positions[elem_position]+".csv"
        df = pd.read_csv(filename, sep=';')
        y[elem_position][stat] = df[stat_type[stat]]
        x = df['n']
        ax.plot(x, y[elem_position][stat], colors[elem_position], label=positions[elem_position])
        
    ax.set_title(stat_type[stat]+"(n)")
    ax.set_xlabel('n')
    ax.set_ylabel(stat_type[stat])
    ax.legend()
    png_name = "./pngs/"+stat_type[stat]+".png"
    fig.savefig(png_name, bbox_inches='tight')
    plt.close()

#constant in rand
constStat = [[0]*100]*2
stats = [[0]*100]*2

df = pd.read_csv('./csv/rand.csv', sep=';')
x = df['n']
for i in range(0,2):

    stats[i] = df[stat_type[i]]
    for j in range(0,100):
        constStat[i][j] = float(stats[i][j])/math.log(x[j],2)

    plt.plot(x, constStat[i], '-b')
    plt.title("Const for "+stat_type[i])
    plt.xlabel('n')
    plt.ylabel('value')
    plt.savefig("./pngs/"+"const_"+stat_type[i]+".png", bbox_inches='tight')
    plt.close()

        





