#include <program-18f458.h>
#include <stdio.h>
#define BUFFER_SIZE 3


char buffer[BUFFER_SIZE];

int toRead=0; // Flag pour actualisation du seuil
int compteur=0; // Nombre de caractère écrit
int i, x;
boolean flag_dat = false;
boolean f_plein = false;
boolean change = false;
int nb_personne = 0;

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

int convertisseurSortie(int valeur){
   int sortie = 0;
   if (valeur < 10) {
      sortie = valeur;
   }else {
       x = valeur;
       x = x % 10;
       i = valeur;
       i = i/10;

       sortie = x + i*16;
   }
   return sortie;
}

void affichage(int value) {
   output_b(value);
}

void main()
{
   int nb_personne = 0;
   int nb_max_personne = 3;

   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);

   setup_low_volt_detect(false);
   setup_timer_0(RTCC_INTERNAL);
   

   output_high(LED_VERT);
   output_low(LED_ROUGE);

   while(true)
   {
      set_adc_channel(0);// pin non utiliser pas neccessaire 
      output_e(read_adc());

      if (input(PIN_C0) == 0 && input(PIN_C1) == 1) {
         change = !change;
         ++nb_personne;
      } else if (input(PIN_C0) == 1 && input(PIN_C1) == 0) {
         if (nb_personne > 0) {
            change = !change;
            --nb_personne;
         }
      }

      if (flag_dat) {
         flag_dat = false;
         output_high(LED_ROUGE);
         change = false;
      }

      if (change) {
         int sortie = convertisseurSortie(nb_personne);
         affichage(sortie);
         boolean f_plein = nb_personne >= nb_max_personne;

         if (f_plein) {
            output_toggle(LED_ROUGE);
            output_low(LED_VERT);
         } else {
            output_low(LED_ROUGE);
            output_high(LED_VERT);
         }
         printf("%d", convertisseurSortie(nb_personnes));
      }

      change = false;

      delay_ms(200);
   }
}
