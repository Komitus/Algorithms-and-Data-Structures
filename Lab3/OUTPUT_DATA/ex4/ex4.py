import matplotlib.pyplot as plt
import pandas as pd
import glob
import re
import math

data_types = ['rand', 'worst']
stat_types = ['compares', 'time'] 
algos = ['QS', 'QS_DP', 'QS_MEDIAN', 'QS_DP_MEDIAN']
colors = ['-b', '-r', '-g', '-k']
values = ['', 'const']

for dtype in data_types:

    for stat in stat_types:
  
        for value in values:

            fig, ax = plt.subplots()

            for algo in algos:
                
                filename = './csv/'+dtype+algo+'.csv'
                df = pd.read_csv(filename, sep=';')

                x = df['n']
                y = df[stat]

                if value == 'const':
                    i = 0
                    constStat = []
                    for valY in y:
                        if dtype == 'rand':
                            tmp = x[i]*math.log(x[i],2)
                        else:
                            tmp = x[i]**2
                        constStat.append( valY / tmp )	
                        i+=1
                    ax.plot(x, constStat, colors[algos.index(algo)], label=algo)
                else:   
                    ax.plot(x, y, colors[algos.index(algo)], label=algo)

            stat_name = stat
            if stat == 'time':
                stat_name+='(micro_secs)'
            ax.set_title(dtype+'_'+value+'_'+stat_name+'(n)')
            ax.set_xlabel('n')
            ax.set_ylabel(dtype+'_'+value+'_'+stat_name)
            ax.legend()
            png_name = './pngs/'+dtype+'_'+value+'_'+stat
            fig.savefig(png_name, bbox_inches='tight')
            plt.cla()


        

