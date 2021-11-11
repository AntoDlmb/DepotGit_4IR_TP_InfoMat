#include "MyTimer.h"


void SPI_Base_Init(){
	SPI1->CR1|= SPI_CR1_MSTR;
}

char SPI_ReadWrite (char address){
	SPI1->CR2|=SPI_CR2_TXEIE;
	//mettre le NSS à 1 et le CS à 0 pendant utilisation sinon CS à 0
	//Tant que TXE n'est pas à un on écrit pas dans DR
	while (!(SPI1->CR2&SPI_CR2_TXEIE)){
		
	}
	SPI1->DR=address;
	while (!(SPI1->CR2&SPI_CR2_RXNEIE)){
		
	}
	return SPI1->DR;
	
	
}

