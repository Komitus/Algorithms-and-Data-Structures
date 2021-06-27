import matplotlib.pyplot as plt
import pandas as pd
import glob
import re

'''
csvfiles = []
for file in glob.glob("./csv/*.csv"):
    csvfiles.append(file)

files = [[][]]
m = re.match(r"\w+([0-9]+)\w+([0-9]+)\w+([0-9]+)\w+([0-9]+)", )
print(m.group)
except AttributeError:
'''      

for mode in range(0,2):
    for k in range(0,3):
        for group_size in range(3,26,2):
            for stat in range(0,3):
                filename = "./csv/mode"+str(mode)+"k"+str(k)+"groupSize"+str(group_size)+"stat"+str(stat)+".csv"
                df = pd.read_csv(filename, sep=';')
                if stat == 0:
                    stat_type = "Compares"
                elif stat == 1:
                    stat_type = "Shifts"
                else:
                    stat_type = "Time(us)"
                title = stat_type+"(n)"
                x = df['n']
                y1 = df['avg']
                y2 = df['min']
                y3 = df['max']
                y4 = df['standard_deviation']
                
                fig, ax = plt.subplots()
                ax.plot(x, y1, '-b', label='avg')
                ax.plot(x, y2, '-g', label='min')
                ax.plot(x, y3, '-r', label='max')
                ax.plot(x, y4, '-k', label='standard_deviation')
                ax.set_title(title)
                ax.set_xlabel('N')
                ax.set_ylabel(stat_type)
                ax.legend()
                
                png_name = "./pngs/m"+str(mode)+"k"+str(k)+"gr"+str(group_size)+str(stat_type)+".png"
                fig.savefig(png_name, bbox_inches='tight')
                plt.close()


        





