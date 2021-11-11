#include "MyTimer.h"


void SPI_Base_Init(){
	SPI1->CR1|= SPI_CR1_MSTR;
}

char SPI_ReadWrite (char address){
	char data;
		
	SPI1->DR=0xF1; //On écrit n'importe quelle donnée
	//Tant que TXE n'est pas à un on écrit pas dans DR
	while (!(SPI1->CR2&SPI_CR2_TXEIE)){
	}
	SPI1->CR2 &= ~SPI_CR2_TXEIE;
	
	SPI1->DR=address;
	
	while (!(SPI1->CR2&SPI_CR2_RXNEIE)){
	}
	SPI1->DR;
	SPI1->CR2 &= ~SPI_CR2_RXNEIE;
	
	while (!(SPI1->CR2&SPI_CR2_TXEIE)){
	}
	SPI1->CR2 &= ~SPI_CR2_TXEIE;
	SPI1->DR=0x0;
	
	while (!(SPI1->CR2&SPI_CR2_RXNEIE)){
	}
	data = SPI1->DR;
	SPI1->CR2 &= ~SPI_CR2_RXNEIE;
	
	return data;
}

