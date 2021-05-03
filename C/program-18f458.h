#include <18F458.h>
#device ADC=10

#FUSES NOWDT                 	//No Watch Dog Timer

#use delay(crystal=20000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=PORT1,FORCE_SW)

void display(int value);
int convertisseurSortie(int valeur);

// Pin aliases
#define LED_ROUGE   PIN_E1
#define LED_VERT PIN_E2
#define PIN_DIZAINE  PIN_E1
#define PIN_UNITE PIN_E0
