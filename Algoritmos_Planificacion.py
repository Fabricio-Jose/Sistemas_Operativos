import matplotlib.pyplot as plt
import numpy as np

def graph(a,b):
    plt.bar([a],[b])

def robin(orden, hllegada, tservicio):
    q=1
    s=0
    j=-1
    while s!= 20:
        if j+1<5:
            if hllegada[j+1]==s:
                j=j+1
            i=j
            while i!=-1:
                if tservicio[i]!=0:
                    tservicio[i]=tservicio[i]-q
                    print ("el tiempo de servicio es: ", tservicio[i], " en: ", orden[i]," en el segundo: " ,s)
                    graph(s,orden[i])
                    s=s+1
                i=i-1
        else:  
            i=j
            while i!=-1:
                if tservicio[i]!=0:
                    tservicio[i]=tservicio[i]-q
                    print ("el tiempo de servicio es: ", tservicio[i], " en: ", orden[i+1]," en el segundo: " ,s)
                    graph(s,orden[i+1])
                    s=s+1
                i=i-1
    plt.bar(0,orden[0])
    plt.show()

def fcfs(orden,hllegada,tservicio):
    x=0
    s=0
    for i in range(3):
        tservicio[i]+=x
        temp=x
        print("en ",orden[i]," el TF es: ",tservicio[i]," y el TR es:",tservicio[i]-hllegada[i])
        print(tservicio[i])
        x=tservicio[i]
        while temp<tservicio[i]:
            graph(s,orden[i+1])
            temp=temp+1
            s=s+1
    plt.show()

def spn(orden, hllegada, tservicio):
    tfa = [0,0,0,0]
    tra = [0,0,0,0]
    temp=0
    x=0
    s=0
    tf=0
    tr=0
    j=0
    posicion=0
    for i in tservicio:
        x=x+i 
    y=x
    tf=tf+tservicio[0]
    tr=tf-hllegada[0]
    tfa[0]=tf
    tra[0]=tr 
    while(temp<tservicio[0]):
        graph(s,orden[0])
        temp=temp+1
        s=s+1
    tservicio[0]=0
    while(j+1<(len(tservicio))):
        for k in range(len(tservicio)):
            if (tservicio[k]!=0):
                if (tservicio[k]<y):
                    y=tservicio[k]
                    posicion=k
        tf=tf+y
        print("esto es",tf,"y y es",y)
        tr=tf-hllegada[posicion]
        tfa[posicion]=tf
        tra[posicion]=tr
        tservicio[posicion]=0
        y=x
        while(temp<tf):
            graph(s,orden[posicion])
            temp=temp+1
            s=s+1
        j=j+1
        tam=0
    while(tam<len(tfa)):
        print("en ",orden[tam]," el TF es: ",tfa[tam]," y el TR es:",tra[tam])
        tam=tam+1   
    plt.show()


def prioridad(orden,hllegada,tservicio,prioridad):
    ts=0
    p=0
    pmax=2
    #x
    for i in range(4):
        ts=ts+tservicio[i]
    s=0
    for j in range(4):
        if hllegada[j]==s:
            s=s+tservicio[j]
            x=tservicio[j]
            tservicio[j]=0
            print("proceso: ",orden[j]," tiempo en segundos: ", x," , su TF es: ", s, "y su TR es:", s-hllegada[j])
            graph(s,orden[j])
            p=prioridad[j];
    if p+1>pmax:
        p=0
    else:
        p=p+1
    while s<ts:
        for k in range(4):
            if tservicio[k]!=0 and prioridad[k]==p:
                s=s+tservicio[k]
                x=tservicio[k]
                tservicio[k]=0
                print("Proceso: ",orden[k]," tiempo en segundos: ",x,", su TF es: ",s,", y TR es:",s-hllegada[k])
                graph(s,orden[k])

        if p+1>pmax:
            p=0
        else:
            p=p+1
    plt.show()

def str(orden,hllegada,tservicio,j,s):
    if(hllegada[j]==s):
        while (tservicio[j]!=0):
            graph(s,orden[j])
            tservicio[j]=tservicio[j]-1
            s=s+1
            if(tservicio[j]==0):
                print("el tf es",s,"del proceso",orden[j],"y el tiempor de retorno tr = ", s-hllegada[j])
            if(j+1<3):
                if(hllegada[j+1]==s):
                    s=str(orden,hllegada,tservicio,j+1,s)
    #plt.show()
    return s

ordenstr=["a","b","c"]
hllegadastr=[1,3,5]
tserviciostr=[6,2,3]

str(ordenstr,hllegadastr,tserviciostr,0,1)
plt.show()

ordenfc=["T1","T2","T3","T4"]
hllegadafc=[0,3,6,8]
tserviciofc=[9,5,1,4]

ordenRobin=["T0","T1","T2","T3","T4","T5"]
hllegadaRobin = [0,2,5,7,10]
tservicioRobin = [3,6,4,5,2]

#ordenPrioridad=["T0","T1","T2","T3","T4","T5"]
ordenPrioridad=["a","b","c","d"]
hllegadaPrioridad = [0,2,4,6]
tservicioPrioridad = [8,6,4,2]
pprioridad=[2,1,2,0]

#spn(ordenfc,hllegadafc,tserviciofc)
#prioridad(ordenPrioridad,hllegadaPrioridad,tservicioPrioridad,pprioridad)

"""----YA ESTA PRESENTADO-----"""

#fcfs(ordenfc,hllegadafc,tserviciofc)
#print ("que proceso desea realizar? ")

#robin(ordenRobin,hllegadaRobin,tservicioRobin) 
