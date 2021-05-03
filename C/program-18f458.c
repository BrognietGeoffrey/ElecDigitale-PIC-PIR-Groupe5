#include <program-18f458.h>
#include <stdio.h>
#define BUFFER_SIZE 3


char buffer[BUFFER_SIZE];

int toRead=0; // Flag pour actualisation du seuil
int compteur=0; // Nombre de caractère écrit
int i, x;
bool flag_add = false;
bool flag_sub = false;
bool flag_dat = false;
bool f_plein = false;
bool change = false;
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
   

   envoi(false, nb_personne, nb_max_personne);
   output_high(LED_VERT);
   output_low(LED_ROUGE);

   while(true)
   {
      set_adc_channel(0);// pin non utiliser pas neccessaire 
      output_e(read_adc());

      if (flag_add) {
         flag_add = false;
         change = !change;
         ++nb_personne;
      }

      if (flag_sub) {
         flag_sub = false;
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
         bool f_plein = nb_personne >= nb_max_personne;

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
