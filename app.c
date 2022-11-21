#include "app.h"

void appStart(void)
{
	uint8_t state = 0;
	struct ST_cardData_t cardData;
	struct ST_terminalData_t termData;
	struct ST_transaction_t transData;
	
	/*
		Card Data Module:
		 - card holder name
		 - card expiry date
		 - card PAN
	*/
	printf("Card Holder Name: ");           /*card holder name*/
	state = getCardHolderName(&cardData);
	if (state == WRONG_NAME)
	{
		printf("WRONG NAME\n");
		return 0;
	}
	printf("Card Expiry Date: ");           /*card expiry date*/
	state = 0;
	state = getCardExpiryDate(&cardData);
	if (state == WRONG_EXP_DATE)
	{
		printf("WRONG EXPIRY DATE\n");
		return 0;
	}
	printf("Card PAN: ");                   /*card PAN*/
	state = 0;
	state = getCardPAN(&cardData);
	if (state == WRONG_PAN)
	{
		printf("WRONG PAN\n");
		return 0;
	}

	/*
	Terminal Module:
	*/
	printf("Transaction Date: ");           /*Transaction Date*/
	state = 0;
	state = getTransactionDate(&termData);
	if (state == WRONG_DATE)
	{
		printf("WRONG DATE\n");
		return 0;
	}
	state = 0; 
	state = isCardExpired(&cardData, &termData);  /*Card Exired or No*/
	if (state == EXPIRED_CARD)
	{
		printf("EXPIRED CARD\n");
		return 0;
	}
	printf("Transaction Amount: ");           /*Transaction Amount*/
	state = 0;
	state = getTransactionAmount(&termData);
	if (state == INVALID_AMOUNT)
	{
		printf("INVALID AMOUNT\n");
		return 0;
	}
	state = 0;
	state = isBelowMaxAmount(&termData);  /*Exceeded Max Amount or No*/
	if (state == EXCEED_MAX_AMOUNT)
	{
		printf("EXCEED MAX AMOUNT\n");
		return 0;
	}
	/*
	Server Module
	*/
	state = 0;
	state = isValidAccount(&cardData, &accountsDB);  /*Account is Valid or Not*/
	if (state == ACCOUNT_NOT_FOUND)
	{
		printf("ACCOUNT IS UNVALID\n");
		return 0;
	}
	uint8_t i;                                         /*Get Account Index*/
	uint8_t accountIndex;
	state = -1;
	for (i = 0; i < 255; i++)
	{
		state = strcmp(&accountsDB[i].primaryAccountNumber, cardData.primaryAccountNumber);
		if (state == 0)
		{
			accountIndex = i;
			break;
		}
	}
	state = 0;
	state = isBlockedAccount(&accountsDB[accountIndex]);  /*Account is Running or Blocking*/
	if (state == BLOCKED_ACCOUNT)
	{
		printf("ACCOUNT IS BLOCKING\n");
		return 0;
	}
	state = 0;
	state = isAmountAvailable(&termData, &accountsDB);  /*Amount is Available or Not*/
	if (state == LOW_BALANCE)
	{
		printf("AMOUNT IS UNAVAILABLE\n");
		return 0;
	}
	state = 0;                                          /*Update Balance*/
	accountsDB[accountIndex].balance = accountsDB[accountIndex].balance - termData.transAmount;
	state = saveTransaction(&transData);
	if (state == SERVER_OK)
	{
		printf("Successful Process\n");
	}
}