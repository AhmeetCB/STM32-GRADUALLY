#include "stm32f10x.h"
	
int say=0;
int sayac=0;
void yak()
{
if(sayac<=2000)
		{
			if(sayac%100==0)
			{
					say = say + 180;
					TIM1->CCR2 = say;
			}
			
		}
		else if(sayac<4000){
			if(sayac%100==0)
				{
						say = say - 180;
						TIM1->CCR2 = say;
				}
			
		}
		else
		{sayac=0;
			say=0;
			TIM1->CCR2 =0;}
		sayac++;
}
void TIM1_UP_IRQHandler(){
	if(TIM1->SR&=~1){
		TIM1 -> SR&=~1;
		yak();
	}
}
int main(){
	RCC -> APB2ENR |= (1<<2)|1; 																																							
	GPIOA->CRH&=~(1<<6);
    GPIOA->CRH|=((1<<7)|(1<<5)|(1<<4));

	RCC -> APB2ENR |= (1<<11);																																											
	TIM1->CCMR1|=(6<<12); 																																													
	TIM1->CCER|=1<<4; 																																															
	TIM1->BDTR|=(1<<15); 
	TIM1->ARR = 3600;
	TIM1->PSC = 9;
	TIM1->RCR=0;
	TIM1->CCR2 = say;
	TIM1->DIER|=1;
	NVIC->ISER[0]|=(1<<25);
	TIM1->CR1|=1;																																																		
	while(1){
		}
}