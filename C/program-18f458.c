#include <program-18f458.h>
#include <stdio.h>
#define BUFFER_SIZE 3


char buffer[BUFFER_SIZE];

int toRead=0; // Flag pour actualisation du seuil
int compteur=0; // Nombre de caractère écrit

#INT_EXT
void EXT_isr(void) {
   flag_add = true;
}

#INT_EXT1
void EXT1_isr(void) {
   flag_sub = true;
}

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

void envoi(bool f_plein, int nb_personne, int nb_max_personne) {
   putc((char) f_plein);
   putc((char) (personne >> 8));
   putc((char) (personne & 0xff));
   putc((char) (nb_max_personne >> 8));
   putc((char) (nb_max_personne & 0xff));
}

void affichage(int value) {
   output_high(PIN_UNITE);
   output_low(PIN_DIZAINE);

   output_b((value / 10) % 10);

   output_low(PIN_UNITE);
   output_high(PIN_DIZAINE);

   output_b(value % 10);

   output_high(PIN_UNITE);
   output_high(PIN_DIZAINE);
}

void main()
{
   int nb_personne = 0;
   int nb_max_personne = 3;

   enable_interrupts(INT_EXT);
   enable_interrupts(INT_EXT1);
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
         affichage(nb_personne);
         bool f_plein = nb_personne >= nb_max_personne;

         if (f_plein) {
            output_toggle(LED_ROUGE);
            output_low(LED_VERT);
         } else {
            output_low(LED_ROUGE);
            output_high(LED_VERT);
         }
         envoi(f_plein, nb_personne, nb_max_personne);
      }

      change = false;

      delay_ms(200);
   }
}
