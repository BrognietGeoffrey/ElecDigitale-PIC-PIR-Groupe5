from tkinter import *
from tkinter import ttk
import webbrowser
import serial
import serial.tools.list_ports as port_list



import time

# -------------- Partie programmation ------------------- #

# Url pour les boutons des codes
url1 = 1
url1name = "https://github.com/BrognietGeoffrey/ElecDigitale-PIC-PIR-Groupe5/tree/main/Python"
url2 = 1
url2name = "https://github.com/BrognietGeoffrey/ElecDigitale-PIC-PIR-Groupe5/tree/main/C"


# Boutons des codes et de fermeture
def openButtonPython():
    webbrowser.open(url1name, new=url1)


def openButtonC():
    webbrowser.open(url2name, new=url2)


def closeWindow():
    window.destroy()

"""
picData = serial.Serial('COM3', baudrate=9600, timeout=1)
if not picData.isOpen():
    picData.open()
print('com4 is open', picData.isOpen())
"""
limit = 3

"""
# Fonction qui délimite le nombre de personne
def limit():
    read = spinbox.get()
    picData.write(read.encode())
    time.sleep(2)
    return read
"""

def updatePeople():
    serialPort = serial.Serial(port="COM4", baudrate=9600,
                               bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)
    com = serialPort.write(serialPort)
    print(com)

    if com != "":
        print("ici")
        com = com
        if com < limit :
            info = "Il y a {}".format(com)
            labelText.config(text=info)  # On indique où placer le texte pour Tkinter
        elif com >= limit :
            info = "Attention, {} = trop !".format(com)
            labelText.config(text=info)  # On indique où placer le texte pour Tkinter

    window.after(100, updatePeople)


"""
# Fonction qui lit les données du PIC
def readDataPic():
    # On reçoit du code Ascii donc on le décode
    data = picData.readline().decode("ascii")

    # Si les données sont différentes de rien donc on imprime les valeurs
    if data != "":
        print("toto")
        value = int(data)
        print(value)

        # On instancie la variable limit avec notre fonction qui délimite le nombre de personnes

        # Si la valeur est en dessous de la limite fixée dans la fonction limit(), alors on indique le message positif
        if value < limit():
            info = "Il y a {}".format(value)
            labelText.config(text=info)  # On indique où placer le texte pour Tkinter

        # Si la valeur dépasse la limite fixée dans la fonction limit(), alors on indique le message négatif
        elif value >= limit():
            info = "Attention, {} = trop !".format(value)
            labelText.config(text=info)  # On indique où placer le texte pour Tkinter

    else :
        print("je suis là")

    window.after(10, readDataPic)
"""

# --------------------- Partie graphique ---------------- #
window = Tk()
window.title("PIC/PIR")
window.geometry('700x300')

labelTitle = Label(window, text="Projet d'électronique - PIC/PIR - Groupe 5", font=("Arial Bold", 18))
labelTitle.grid(column=1, row=0, padx=3, pady=15)

buttonC = Button(window, text="Code Source C", command=openButtonC)
buttonC.grid(column=0, row=0)

buttonP = Button(window, text="Code Source Python", command=openButtonPython)
buttonP.grid(column=0, row=1)

buttonExit = Button(window, text='Fermer', command=closeWindow)
buttonExit.grid(column=3, row=0)

labelText = Label(window, text="")
labelText.grid(column=1, row=1)

labelSpinbox = Label(window, text="Selectionnez une limite : ")
labelSpinbox.grid(column=0, row=2, padx=0, pady=10)

spinbox = ttk.Spinbox(window, from_=0, to=10, width=10, state='readonly')
spinbox.grid(column=0, row=3)

buttonConfirm = Button(window, text="Confirmer", command=limit)
buttonConfirm.grid(column=0, row=4)

if __name__ == '__main__':
    print("tata")
    window.after(10, updatePeople)
    window.mainloop()
