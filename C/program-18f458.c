#include <program-18f458.h>
#include <stdio.h>


void main()
{
   int nb_personne = 0;
   int nb_max_personne = 3;
   valeur_affi2 = 0;

   #bit PIR_IN= PIN_C0;// entree de la zone
   #bit PIR_OUT= PIN_C1;// sortie de la zone

   setup_adc_ports(AN0); //pas besoin on utilise pas la pin AN0
   setup_adc(ADC_CLOCK_INTERNAL);
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
   	if(input(PIR_IN)) {
   		nb_personne += 1;
   	}
   	if(input(PIR_OUT)) {
   		nb_personne -= 1;
   	}
   
      // Gestion des led selon le nombre de personne
      if (nb_personne > nb_max_personne){
         output_low(10); //Dans la paranthèse faut indiquer la pin de la led verte car on l'éteind
         output_toggle(9); //Ici on doit indiquer la pin de la led rouge car on allume cette led car la valeur dépasse le seuil
      }
      else {
         output_e(0b100);// met E0 à 0, E1 à 0 et E2 à 1
      }

      // Gestion des afficheurs 7 segment
      int unite = nb_personne%10;
      int dizaine = (nb_personne/10) %10;


   }
}
