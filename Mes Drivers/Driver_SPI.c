#include "MyTimer.h"


void SPI_Base_Init(){
	SPI1->CR1|= SPI_CR1_MSTR;
}

char SPI_ReadWrite (char address){
	SPI1->CR2|=SPI_CR2_TXEIE;
	//mettre le NSS � 1 et le CS � 0 pendant utilisation sinon CS � 0
	//Tant que TXE n'est pas � un on �crit pas dans DR
	while (!(SPI1->CR2&SPI_CR2_TXEIE)){
		
	}
	SPI1->DR=address;
	while (!(SPI1->CR2&SPI_CR2_RXNEIE)){
		
	}
	return SPI1->DR;
	
	
}

