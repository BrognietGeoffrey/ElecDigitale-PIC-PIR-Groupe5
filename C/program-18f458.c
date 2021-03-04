#include <program-18f458.h>
#include <stdio.h>


void main()
{
   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_low_volt_detect(FALSE);

   while(TRUE)
   {
   
   
   
   
      // Gestion des led selon le nombre de personne
      if (valeur > seuil){
         output_low(); //Dans la paranthèse faut indiquer la pin de la led verte car on fait diminuer l'intensité
         output_toggle(); //Ici on doit indiquer la pin de la led rouge car on allume cette led car la valeur dépasse le seuil
      }
      else {
         output_high(); //Vu qu'on doit tout le temps laisser la led verte allumé si la valeur ne dépasse pas le seuil, on la met en "haut"
         output_low(); //Et vu qu'on doit laisser la led verte allumé en permanence, on éteint "down" la led rouge
      }

}
