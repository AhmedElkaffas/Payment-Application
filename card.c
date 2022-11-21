#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	uint8_t nameLen = 0;
	gets(cardData->cardHolderName);
	nameLen = strlen(cardData->cardHolderName);
	if (nameLen > 24 || nameLen < 20)
	{
		return WRONG_NAME;
	}
	else
	{
		return CARD_OK;
	}
}

/* Example Test
* [Case 1] Correct Name (AHMED ELSAYED HAMED MO)
* [Case 2] Wrong Name (AHMED ELSAYED HAMED MOHAMED)
* [Case 3] Wrong Name (AHMED ELSAYED HAMED)
*/
void getCardHolderNameTest(void)
{
	uint8_t state=0;
	struct ST_cardData_t Name;
	printf("Tester Name = Ahmed Elsayed Hamed Mohamed\n");
	printf("Function Name = getCardHolderName\n");
	printf("Test Case 1\n");
	printf("Input Data:");
	state = getCardHolderName(&Name);
	printf("Expected Result: CARD_OK\n");
	if (state == CARD_OK)
	{
		printf("Actual Result: CARD_OK\n");
	}
	else
	{
		printf("Actual Result: WRONG_NAME\n");
	}
	state = 0;
	printf("Test Case 2\n");
	printf("Input Data:");
	state = getCardHolderName(&Name);
	printf("Expected Result: WRONG_NAME\n");
	if (state == CARD_OK)
	{
		printf("Actual Result: CARD_OK\n");
	}
	else
	{
		printf("Actual Result: WRONG_NAME\n");
	}
	state = 0;
	printf("Test Case 3\n");
	printf("Input Data:");
	state = getCardHolderName(&Name);
	printf("Expected Result: WRONG_NAME\n");
	if (state == CARD_OK)
	{
		printf("Actual Result: CARD_OK\n");
	}
	else
	{
		printf("Actual Result: WRONG_NAME\n");
	}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	uint8_t expiryDateLen = 0;
	gets(&cardData->cardExpirationDate);
	expiryDateLen = strlen(cardData->cardExpirationDate); /*11/25*/
	if (expiryDateLen < 5 || expiryDateLen>5)
	{
		return WRONG_EXP_DATE;
	}
	if (cardData->cardExpirationDate[2] != '/')
	{
		return WRONG_EXP_DATE;
	}
	if (cardData->cardExpirationDate[0] > '1' || cardData->cardExpirationDate[0] < '0')
	{
		return WRONG_EXP_DATE;
	}
	if (cardData->cardExpirationDate[0] == '1')
	{
		if (cardData->cardExpirationDate[1] > '2' || cardData->cardExpirationDate[1] < '0')
		{
			return WRONG_EXP_DATE;
		}
	}
	if (cardData->cardExpirationDate[1] > '9' || cardData->cardExpirationDate[1] < '0')  /* ex, 1-/25 */
	{
		return WRONG_EXP_DATE;
	}

	return CARD_OK;
}

/* Example Test
* [Case 1] Correct Date (07/25)
* [Case 2] Wrong Date (20/25)
* [Case 3] Wrong Date (-1/25)
* [Case 4] Wrong Date (17/23)
* [Case 5] Wrong Date (1-/24)
* [Case 6] Wrong Date (11*25)
*/
void getCardExpiryDateTest(void)
{
	uint8_t state = 0;
	struct ST_cardData_t Date;
	printf("Tester Name = Ahmed Elsayed Hamed Mohamed\n");
	printf("Function Name = getCardExpiryDate\n");
	printf("Test Case 1\n");
	printf("Input Data:");
	state = getCardExpiryDate(&Date);
	printf("Expected Result: CARD_OK\n");
	if (state == CARD_OK)
	{
		printf("Actual Result: CARD_OK\n");
	}
	else
	{
		printf("Actual Result: WRONG_EXP_DATE\n");
	}
	state = 0;
	printf("Test Case 2\n");
	printf("Input Data:");
	state = getCardExpiryDate(&Date);
	printf("Expected Result: WRONG_EXP_DATE\n");
	if (state == CARD_OK)
	{
		printf("Actual Result: CARD_OK\n");
	}
	else
	{
		printf("Actual Result: WRONG_EXP_DATE\n");
	}
	state = 0;
	printf("Test Case 3\n");
	printf("Input Data:");
	state = getCardExpiryDate(&Date);
	printf("Expected Result: WRONG_EXP_DATE\n");
	if (state == CARD_OK)
	{
		printf("Actual Result: CARD_OK\n");
	}
	else
	{
		printf("Actual Result: WRONG_EXP_DATE\n");
	}
	state = 0;
	printf("Test Case 4\n");
	printf("Input Data:");
	state = getCardExpiryDate(&Date);
	printf("Expected Result: WRONG_EXP_DATE\n");
	if (state == CARD_OK)
	{
		printf("Actual Result: CARD_OK\n");
	}
	else
	{
		printf("Actual Result: WRONG_EXP_DATE\n");
	}
	state = 0;
	printf("Test Case 5\n");
	printf("Input Data:");
	state = getCardExpiryDate(&Date);
	printf("Expected Result: WRONG_EXP_DATE\n");
	if (state == CARD_OK)
	{
		printf("Actual Result: CARD_OK\n");
	}
	else
	{
		printf("Actual Result: WRONG_EXP_DATE\n");
	}
	state = 0;
	printf("Test Case 6\n");
	printf("Input Data:");
	state = getCardExpiryDate(&Date);
	printf("Expected Result: WRONG_EXP_DATE\n");
	if (state == CARD_OK)
	{
		printf("Actual Result: CARD_OK\n");
	}
	else
	{
		printf("Actual Result: WRONG_EXP_DATE\n");
	}
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	uint8_t PANLen = 0;
	gets(cardData->primaryAccountNumber);
	PANLen = strlen(cardData->primaryAccountNumber);
	if (PANLen < 16 || PANLen > 19)
	{
		return WRONG_PAN;
	}
	return CARD_OK;
}

/* Example Test
* [Case 1] Correct PAN 123456789123456789
* [Case 2] Wrong PAN 1234
* [Case 3] Wrong Pan 123456789123456789123
*/
void getCardPANTest(void)
{
	uint8_t state = 0;
	struct ST_cardData_t PAN;
	printf("Tester Name = Ahmed Elsayed Hamed Mohamed\n");
	printf("Function Name = getCardPAN\n");
	printf("Test Case 1\n");
	printf("Input Data:");
	state = getCardPAN(&PAN);
	printf("Expected Result: CARD_OK\n");
	if (state == CARD_OK)
	{
		printf("Actual Result: CARD_OK\n");
	}
	else
	{
		printf("Actual Result: WRONG_PAN\n");
	}
	state = 0;
	printf("Test Case 2\n");
	printf("Input Data:");
	state = getCardPAN(&PAN);
	printf("Expected Result: WRONG_PAN\n");
	if (state == CARD_OK)
	{
		printf("Actual Result: CARD_OK\n");
	}
	else
	{
		printf("Actual Result: WRONG_PAN\n");
	}
	state = 0;
	printf("Test Case 3\n");
	printf("Input Data:");
	state = getCardPAN(&PAN);
	printf("Expected Result: WRONG_PAN\n");
	if (state == CARD_OK)
	{
		printf("Actual Result: CARD_OK\n");
	}
	else
	{
		printf("Actual Result: WRONG_PAN\n");
	}
}
