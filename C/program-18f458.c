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
         output_low(); //Dans la paranth�se faut indiquer la pin de la led verte car on fait diminuer l'intensit�
         output_toggle(); //Ici on doit indiquer la pin de la led rouge car on allume cette led car la valeur d�passe le seuil
      }
      else {
         output_high(); //Vu qu'on doit tout le temps laisser la led verte allum� si la valeur ne d�passe pas le seuil, on la met en "haut"
         output_low(); //Et vu qu'on doit laisser la led verte allum� en permanence, on �teins "down" la led rouge
      }

}
