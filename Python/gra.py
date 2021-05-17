from tkinter import *
from tkinter import ttk
import webbrowser
import serial
import time

# -------------- Partie programmation ------------------- #

# Url pour les boutons des codes
url1 = 1
url1name = "https://github.com/BrognietGeoffrey/ElecDigitale-PIC-PIR-Groupe5/tree/main/Python"
url2 = 1
url2name = "https://github.com/BrognietGeoffrey/ElecDigitale-PIC-PIR-Groupe5/tree/main/C"

#Connexion pour le port COM
ser = serial.Serial('COM4', baudrate=9600, timeout=1)


# Boutons des codes et de fermeture
def openButtonPython():
    webbrowser.open(url1name, new=url1)


def openButtonC():
    webbrowser.open(url2name, new=url2)


def closeWindow():
    window.destroy()


# Fonction qui délimite le nombre de personne
def maxPeople():

    read = spinbox.get()
    ser.write(read.encode())
    return read


# Fonction qui lit les données du PIC
def readDataPic():

    # On reçoit du code Ascii donc on le décode
    people = ser.readline().decode('ascii')

    # Si les données sont différentes de rien donc on imprime les valeurs
    if people != "":
        value = int(people)
        print(value)

        # On instancie la variable limit avec notre fonction qui délimite le nombre de personnes
        maximum = maxPeople()

        # Si la valeur est en dessous de la limite fixée dans la fonction limit(), alors on indique le message positif
        if value < int(maximum):
            number = "Voici le nombre de personnes : {}".format(value)
            info = "Le nombre de personne ne dépasse pas la limite"
            labelNumber.config(text=number)
            labelInfo.config(text=info)  # On indique où placer le texte pour Tkinter
            labelInfo.config(bg="green") # couleur verte pour safe
        elif value == int(maximum):
            number = "Voici le nombre de personnes : {}".format(value)
            info = "Attention la limite est atteinte !"
            labelNumber.config(text=number)
            labelInfo.config(text=info)  # On indique où placer le texte pour Tkinter
            labelInfo.config(bg="orange") # couleur verte pour safe
        # Si la valeur dépasse la limite fixée dans la fonction limit(), alors on indique le message négatif
        elif value > int(maximum):
            number = "Voici le nombre de personnes : {}".format(value)
            info = "Le nombre de personne dépasse la limite"
            labelNumber.config(text=number)
            labelInfo.config(text=info)  # On indique où placer le texte pour Tkinter
            labelInfo.config(bg="red") # Changement de couleur en rouge
    window.after(10, readDataPic)


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

labelNumber = Label(window, text="")
labelNumber.grid(column=1, row=1)

labelInfo = Label(window, text=" ")
labelInfo.grid(column=1, row=2)

labelSpinbox = Label(window, text="Selectionnez une limite : ")
labelSpinbox.grid(column=0, row=2, padx=0, pady=10)

spinbox = ttk.Spinbox(window, from_=0, to=10, width=10, state='readonly')
spinbox.grid(column=0, row=3)

buttonConfirm = Button(window, text="Confirmer", command=maxPeople)
buttonConfirm.grid(column=0, row=4)

window.update()


if __name__ == '__main__':
    window.after(1000, readDataPic)
    window.mainloop()