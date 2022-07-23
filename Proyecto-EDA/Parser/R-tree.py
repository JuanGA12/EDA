from rtree import index
import json
import pandas as pd
from time import time

idx = index.Index()


def leer_json(Nombre_Archivo):
    df = pd.read_csv(Nombre_Archivo, sep=';')
    #print(df['coordinates'])
    lista = []
    contador = 0
    
    for key in df['coordinates']:
        lista = key.split("/")
        lista.remove("") 
        #print(lista)
        #print(key)
        LimiteMaximoX = -10000000;
        LimiteMinimoX = 1000000;
        LimiteMaximoY = -10000000;
        LimiteMinimoY = 1000000;
        lista2=[]
        for key2 in lista:
            lista2 = key2.split(",")
            Corx = float(lista2[0]) 
            Cory = float(lista2[1])
            if LimiteMaximoX < Corx:
                LimiteMaximoX = Corx
            if LimiteMinimoX > Corx:
                LimiteMinimoX = Corx
            if LimiteMaximoY < Cory:
                LimiteMaximoY = Cory
            if LimiteMinimoY > Cory:
                LimiteMinimoY = Cory

   

        idx.insert(contador, (LimiteMinimoX, LimiteMinimoY, LimiteMaximoX,LimiteMaximoY ))
        contador= contador + 1

            #print(key2.split(","))
            #print('HOLA')
    
    print(idx) 
    lista = []
    for i in range(0,10000):
        start_time = time()
        id = list(idx.nearest((-73.807693481445300, 40.700393676757800,-73.807693481445300, 40.700393676757800),0))
        elapsed_time = time() - start_time
        lista.append(elapsed_time)
    acc = 0
    for i in lista: 
        acc+=i

    #print(acc/len(lista))
    id = list(idx.nearest((-73.98626270358606, 40.6862135260153,-73.98626270358606, 40.6862135260153),0))
    #print(id)
    print("El punto -73.98626270358606, 40.6862135260153 se encuentra en  " + df['neighborhood'][id[0]])
    #print("Elapsed time: %0.10f seconds." % elapsed_time)

leer_json("Barrios.csv")

