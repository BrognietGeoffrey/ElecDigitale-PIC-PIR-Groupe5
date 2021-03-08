#include <program-18f458.h>
#include <stdio.h>

int buffer;
boolean flag = 0;

#int_RDA
void RDA_isr(void)
{
   buffer = int(getc());
   flag = 1;
}

void main()
{
   int nb_personne = 0;
   int nb_max_personne = 3;

   int PIR_IN= 15;// entree de la zone
   int PIR_OUT= 16;// sortie de la zone

   setup_adc_ports(NO_ANALOGS); //pas besoin on utilise pas la pin AN0
   setup_adc(ADC_OFF);
   setup_low_volt_detect(FALSE);
   setup_psp(PSP_DISABLED);
   setup_spi(FALSE);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   setup_oscillator(FALSE);

   while(TRUE)
   {
      delay_ms(250);
      set_adc_channel(0);// pin non utiliser pas neccessaire 
      output_e(read_adc());

      //verifier si il y a un passage entree ou sortie
      if(PIN_C0 == 1) {
         nb_personne += 1;
         printf("Une personne en plus dans la zone : %d personnes dans la zone\n",nb_personne);
      }
      if(PIN_C1 == 1 && nb_personne != 0) {
         nb_personne -= 1;
         printf("Une personne en moins dans la zone : %d personnes dans la zone\n",nb_personne);
      }
   
      // Gestion des led selon le nombre de personne
      if (nb_personne > nb_max_personne){
         output_low(10); //Dans la paranthèse faut indiquer la pin de la led verte car on l'éteind
         output_toggle(9); //Ici on doit indiquer la pin de la led rouge car on allume cette led car la valeur dépasse le seuil
         printf("Trop de personnes sont dans la zone : %d personnes dans la zone\n",nb_personne);
      }
      else {
         output_e(0b100);// met E0 à 0, E1 à 0 et E2 à 1
      }

      // Gestion des afficheurs 7 segment
      int unite = nb_personne%10;
      int dizaine = nb_personne/10;
      output_b(dizaine);
      output_b((unite<<4));

      // Gestion du port com
      if(flag) {
         nb_max_personnes = buffer;
      }

   }
}
