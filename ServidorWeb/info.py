from datetime import datetime
from os import system

fecha = datetime.now().date()
hora = datetime.now().time()


system("uptime -p > prub.txt")
f = open('prub.txt', 'r')
aux = f.read(3)
Iniciado = f.read()
f.close()

system("nproc --all > prub.txt")
f = open('prub.txt', 'r')
Procesadores = f.read()
f.close()

system("free > prub.txt")
f = open('prub.txt', 'r')
aux = f.read().split()
Total = aux[7]
Usado = aux[8]
Libre = aux[9]
f.close()

TamañoDisc = []
UsadoDisc = []
LibreDisc = []
A = [10,11,13]
system("df -h --output=source,fstype,size,used,pcent,avail,target -x tmpfs -x devtmpfs > prub.txt")
f = open('prub.txt', 'r')
aux = f.read().split()
Discos = int(len(aux)/7) -1
for i in range(Discos):
    TamañoDisc.append(aux[A[0]+(i*7)])
    UsadoDisc.append(aux[A[1]+(i*7)])
    LibreDisc.append(aux[A[2]+(i*7)])
f.close()

html = """<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Información del sistema</title>
</head>
<body>

    <h1>Información del sistema</h1>
    <div class="row">
        <div>
            <div>
                <div>
                    <div>
                        <div>
                            <div>
                                <table>
                                    <thead style="background-color:#A1A1A1;color:#FFFFFF">
                                        <tr>
                                            <th>Parámetro</th>
                                            <th>Valor</th>
                                        </tr>
                                    </thead>
                                    <tbody>    
                                        <tr>
                                            <td>Fecha</td>
                                            <td>""" + str(fecha) + """</td>
                                        </tr>  
                                        <tr>
                                            <td>Hora</td>
                                            <td>""" + str(hora) + """ </td>
                                        </tr>  
                                        <tr>
                                            <td>Tiempo de iniciado el sistema</td>
                                            <td>""" + str(Iniciado) + """ </td>
                                        </tr> 
                                        <tr>
                                            <td>Numero de procesadores</td>
                                            <td>""" + str(Procesadores) + """ </td>
                                        </tr> 
                                        <tr>
                                            <td>Memoria total</td>
                                            <td>""" + str(Total) + """ </td>
                                        </tr> 
                                        <tr>
                                            <td>Memoria usada</td>
                                            <td>""" + str(Usado) + """ </td>
                                        </tr> 
                                        <tr>
                                            <td>Memoria libre</td>
                                            <td>""" + str(Libre) + """ </td>
                                        </tr> 
                                        <tr>
                                            <td>Numero de discos</td>
                                            <td>""" + str(Discos) + """ </td>
                                        </tr> 
                                        <tr>
                                            <td>Tamaño total de cada disco</td>
                                            <td>""" + str(TamañoDisc[0]) + """ </td>
                                            <td>""" + str(TamañoDisc[1]) + """ </td>
                                        </tr> 
                                        <tr>
                                            <td>Espacio usado de cada disco</td>
                                            <td>""" + str(UsadoDisc[0]) + """ </td>
                                            <td>""" + str(UsadoDisc[1]) + """ </td>
                                        </tr> 
                                        <tr>
                                            <td>Espacio libre de cada disco</td>
                                            <td>""" + LibreDisc[0] + """ </td>
                                            <td>""" + LibreDisc[1] + """ </td>
                                        </tr> 
                                    </tbody>
                                </table>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>

</body>
</html>"""



f = open('info.html', 'w')
f.write(html)
f.close()