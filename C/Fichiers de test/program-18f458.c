#include <program-18f458.h>
#include <stdio.h>
#define BUFFER_SIZE 3


char buffer[BUFFER_SIZE];

int toRead=0; // Flag pour actualisation du seuil
int compteur=0; // Nombre de caractère écrit
int i, x;
boolean f_plein = false;
boolean change = false;
int nb_personne = 0;

// Interruption quand on reçoit des données 
#INT_RDA
void RDA_isr(void)
{
   buffer[compteur] = getc();
   if(buffer[0]=='!' && toRead==0){
      compteur++;
      if(compteur>=4){
         compteur=0;
         toRead=1;
      }
   } 
}

// Convertir le nombre de personnes en un nombre à envoyer sur les pins des afficheurs 7 segments
int convertisseurSortie(int valeur){
   int sortie = 0;
   if (valeur < 10) {
      sortie = valeur*16;
   } else {
       x = valeur;
       x = x % 10;
       i = valeur;
       i = i/10;

       sortie = i + x*16;
   }
   return sortie;
}

void main()
{
   int nb_personne = 0;
   int nb_max_personne = 3;

   // Initialiser les interruptions
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);

   // setup de base
   setup_low_volt_detect(false);
   setup_timer_0(RTCC_INTERNAL);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_spi(FALSE);
   setup_wdt(WDT_OFF);
   setup_timer_1( T1_INTERNAL | T1_DIV_BY_1  );
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   setup_oscillator(False);
   
   // Allumer les leds
   output_high(LED_VERT);
   output_low(LED_ROUGE);

   // Boucle du programme
   while(true)
   {
      set_adc_channel(0);// pin non utiliser pas neccessaire 

      // Vérification de l'état des entrées / sorties
      if (input(PIN_C0) == 0 && input(PIN_C1) == 1) {
         change = true;
         nb_personne += 1;
         delay_ms(200);
      } else if (input(PIN_C0) == 1 && input(PIN_C1) == 0) {
         if (nb_personne > 0) {
            change = true;
            nb_personne -= 1;
            delay_ms(200);
         }
      }

      if(toRead) {
      	nb_max_personne = buffer[1];
      }

      // Si le nombre de personne dans la salle change
      if (change) {
         int sortie = convertisseurSortie(nb_personne);
         output_b(sortie); // Afficher le nombre de personnes sur les afficheurs

         // Gérer les leds en fonction du nombre de personne
         boolean f_plein = nb_personne >= nb_max_personne;
         if (f_plein) {
            output_toggle(LED_ROUGE);
            output_low(LED_VERT);
         } else {
            output_low(LED_ROUGE);
            output_high(LED_VERT);
         }
         // Imprimer le nombre de personne sur le port COM
         printf("%d", nb_personne);
         change = false;
      }
      delay_ms(200);
   }
}