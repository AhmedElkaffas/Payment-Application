#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	uint8_t transactionDateLen = 0;
	gets(termData->transactionDate);
	transactionDateLen = strlen(termData->transactionDate);
	if (transactionDateLen < 10 || transactionDateLen > 10)
	{
		return WRONG_DATE;
	}
	if (termData->transactionDate[2] != '/' || termData->transactionDate[5] != '/')
	{
		return WRONG_DATE;
	}
	if (termData->transactionDate[0] < '0' || termData->transactionDate[0] > '3' || termData->transactionDate[1] < '0' || termData->transactionDate[1] > '9' || termData->transactionDate[3] < '0' || termData->transactionDate[3] > '1' || termData->transactionDate[4] < '0' || termData->transactionDate[4] > '9' || termData->transactionDate[6] < '0' || termData->transactionDate[6] > '9' || termData->transactionDate[7] < '0' || termData->transactionDate[7] > '9' || termData->transactionDate[8] < '0' || termData->transactionDate[8] > '9' || termData->transactionDate[9] < '0' || termData->transactionDate[9] > '9')
	{
		return WRONG_DATE;
	}
	if (termData->transactionDate[0] == '3')
	{
		if (termData->transactionDate[1] > '1')
		{
			return WRONG_DATE;
		}
	}
	if (termData->transactionDate[3] == '1')
	{
		if (termData->transactionDate[4] > '2')
		{
			return WRONG_DATE;
		}
	}

	return TERMINAL_OK;
}

/* Example Test
* [Case 1] Correct Date (01/10/2022)
* [Case 2] Wrong Date (39/10/2022)
* [Case 3] Wrong Date (10/21/2022)
* [Case 4] Wrong Date (10*05/2022)
* [Case 5] Wrong Date (1-/05/2022)
* [Case 6] Wrong Date (11)
*/
void getTransactionDateTest(void)
{
	uint8_t state = 0;
	struct ST_terminalData_t transactionDate;
	printf("Tester Name = Ahmed Elsayed Hamed Mohamed\n");
	printf("Function Name = getTransactionDate\n");
	printf("Test Case 1\n");
	printf("Input Data:");
	state = getTransactionDate(&transactionDate);
	printf("Expected Result: TERMINAL_OK\n");
	if (state == TERMINAL_OK)
	{
		printf("Actual Result: TERMINAL_OK\n");
	}
	else
	{
		printf("Actual Result: WRONG_DATE\n");
	}
	state = 0;
	printf("Test Case 2\n");
	printf("Input Data:");
	state = getTransactionDate(&transactionDate);
	printf("Expected Result: WRONG_DATE\n");
	if (state == TERMINAL_OK)
	{
		printf("Actual Result: TERMINAL_OK\n");
	}
	else
	{
		printf("Actual Result: WRONG_DATE\n");
	}
	state = 0;
	printf("Test Case 3\n");
	printf("Input Data:");
	state = getTransactionDate(&transactionDate);
	printf("Expected Result: WRONG_DATE\n");
	if (state == TERMINAL_OK)
	{
		printf("Actual Result: TERMINAL_OK\n");
	}
	else
	{
		printf("Actual Result: WRONG_DATE\n");
	}
	state = 0;
	printf("Test Case 4\n");
	printf("Input Data:");
	state = getTransactionDate(&transactionDate);
	printf("Expected Result: WRONG_DATE\n");
	if (state == TERMINAL_OK)
	{
		printf("Actual Result: TERMINAL_OK\n");
	}
	else
	{
		printf("Actual Result: WRONG_DATE\n");
	}
	state = 0;
	printf("Test Case 5\n");
	printf("Input Data:");
	state = getTransactionDate(&transactionDate);
	printf("Expected Result: WRONG_DATE\n");
	if (state == TERMINAL_OK)
	{
		printf("Actual Result: TERMINAL_OK\n");
	}
	else
	{
		printf("Actual Result: WRONG_DATE\n");
	}
	state = 0;
	printf("Test Case 6\n");
	printf("Input Data:");
	state = getTransactionDate(&transactionDate);
	printf("Expected Result: WRONG_DATE\n");
	if (state == TERMINAL_OK)
	{
		printf("Actual Result: TERMINAL_OK\n");
	}
	else
	{
		printf("Actual Result: WRONG_DATE\n");
	}
}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	uint8_t Exstatus=0,Trastatus=0;
	uint8_t i;
	uint8_t Exyear[2];
	uint8_t Trayear[2];
	uint8_t Exmonth[2];
	uint8_t Tramonth[2];
	for (i = 0; i < 2; i++)
	{
		Exmonth[i] = cardData->cardExpirationDate[i];
		Tramonth[i] = termData->transactionDate[i + 3];
		Exyear[i] = cardData->cardExpirationDate[i + 3];
		Trayear[i] = termData->transactionDate[i + 8];
	}
	if (atoi(Exyear) < atoi(Trayear))
	{
		return EXPIRED_CARD;
	}
	if (atoi(Exyear) == atoi(Trayear))
	{
		if (atoi(Exmonth) < atoi(Tramonth))
		{
			return EXPIRED_CARD;
		}
	}
	return TERMINAL_OK;
}

/* Example Test
* [Case 1] Correct Date EX: (10/25)  Tr: (10/02/2022) 
* [Case 2] Wrong Date Ex: (10/19)   Tr: (10/02/2022)
* [Case 3] Wrong Date Ex: (01/22)   Tr: (10/02/2022)
*/
void isCardExpriedTest(void)
{
	uint8_t status = 0;
	struct ST_cardData_t ExpiredDate;
	struct ST_terminalData_t transactionDate;
	printf("Tester Name = Ahmed Elsayed Hamed Mohamed\n");
	printf("Function Name = isCardExpired\n");
	printf("Test Case 1\n");
	printf("Input Data:\n");
	printf("ExpiredDate: ");
	getCardExpiryDate(&ExpiredDate);
	printf("TransactionDate: ");
	getTransactionDate(&transactionDate);
	status = isCardExpired(&ExpiredDate, &transactionDate);
	printf("Expected Result: TERMINAL_OK\n");
	if (status == TERMINAL_OK)
	{
		printf("Actual Result: TERMINAL_OK\n");
	}
	else
	{
		printf("Actual Result: EXPIRED_CARD\n");
	}
	status = 0;
	printf("Test Case 2\n");
	printf("Input Data:\n");
	printf("ExpiredDate: ");
	getCardExpiryDate(&ExpiredDate);
	printf("TransactionDate: ");
	getTransactionDate(&transactionDate);
	status = isCardExpired(&ExpiredDate, &transactionDate);
	printf("Expected Result: EXPIRED_CARD\n");
	if (status == TERMINAL_OK)
	{
		printf("Actual Result: TERMINAL_OK\n");
	}
	else
	{
		printf("Actual Result: EXPIRED_CARD\n");
	}
	status = 0;
	printf("Test Case 3\n");
	printf("Input Data:\n");
	printf("ExpiredDate: ");
	getCardExpiryDate(&ExpiredDate);
	printf("TransactionDate: ");
	getTransactionDate(&transactionDate);
	status = isCardExpired(&ExpiredDate, &transactionDate);
	printf("Expected Result: EXPIRED_CARD\n");
	if (status == TERMINAL_OK)
	{
		printf("Actual Result: TERMINAL_OK\n");
	}
	else
	{
		printf("Actual Result: EXPIRED_CARD\n");
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	scanf_s("%f", &termData->transAmount);
	if (termData->transAmount <= 0)
	{
		return INVALID_AMOUNT;
	}
	return TERMINAL_OK;
}

/* Example Test
* [Case 1] Correct Amount (1200)
* [Case 2] Wrong Amount (0)
* [Case 3] Wrong Amount (-1000)
*/
void getTransactionAmountTest(void)
{
	uint8_t status = 0;
	struct ST_terminalData_t transactionAmount;
	printf("Tester Name = Ahmed Elsayed Hamed Mohamed\n");
	printf("Function Name = getTransactionAmount\n");
	printf("Test Case 1\n");
	printf("Input Data:");
	status = getTransactionAmount(&transactionAmount);
	printf("Expected Result: TERMINAL_OK\n");
	if (status == TERMINAL_OK)
	{
		printf("Actual Result: TERMINAL_OK\n");
	}
	else
	{
		printf("Actual Result: INVALID_AMOUNT\n");
	}
	status = 0;
	printf("Test Case 2\n");
	printf("Input Data:");
	status = getTransactionAmount(&transactionAmount);
	printf("Expected Result: INVALID_AMOUNT\n");
	if (status == TERMINAL_OK)
	{
		printf("Actual Result: TERMINAL_OK\n");
	}
	else
	{
		printf("Actual Result: INVALID_AMOUNT\n");
	}
	printf("Test Case 3\n");
	printf("Input Data:");
	status = getTransactionAmount(&transactionAmount);
	printf("Expected Result: INVALID_AMOUNT\n");
	if (status == TERMINAL_OK)
	{
		printf("Actual Result: TERMINAL_OK\n");
	}
	else
	{
		printf("Actual Result: INVALID_AMOUNT\n");
	}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	uint8_t TraStatus = 0;
	/*let maxTransAmount = 10000*/
	termData->maxTransAmount = 10000;
	if (termData->maxTransAmount < termData->transAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	return TERMINAL_OK;
}

/* Example Test
* let MaxAmount = 10000
* [Case 1] Correct Amount (1200)
* [Case 2] Wrong Amount (15000)
*/
void isBelowMaxAmountTest(void)
{
	uint8_t status = 0;
	struct ST_terminalData_t transactionAmount;
	printf("Tester Name = Ahmed Elsayed Hamed Mohamed\n");
	printf("Function Name = isBelowMaxAmount\n");
	printf("Test Case 1\n");
	printf("Input Data:\n");
	printf("TransAmount: ");
	getTransactionAmount(&transactionAmount);
	status = isBelowMaxAmount(&transactionAmount);
	printf("Expected Result: TERMINAL_OK\n");
	if (status == TERMINAL_OK)
	{
		printf("Actual Result: TERMINAL_OK\n");
	}
	else
	{
		printf("Actual Result: EXCEED_MAX_AMOUNT\n");
	}
	status = 0;
	printf("Test Case 2\n");
	printf("Input Data:\n");
	printf("TransAmount: ");
	getTransactionAmount(&transactionAmount);
	status = isBelowMaxAmount(&transactionAmount);
	printf("Expected Result: EXCEED_MAX_AMOUNT\n");
	if (status == TERMINAL_OK)
	{
		printf("Actual Result: TERMINAL_OK\n");
	}
	else
	{
		printf("Actual Result: EXCEED_MAX_AMOUNT\n");
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
	termData->maxTransAmount = maxAmount;
	if (termData->maxTransAmount <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}
	return TERMINAL_OK;
}

/* Example Test
* [Case 1] Correct MaxAmount (1200)
* [Case 2] Wrong MaxAmount (0)
* [Case 3] Wrong MaxAmount (-1000)
*/
void setMaxAmountTest(void)
{
	uint8_t status = 0;
	struct ST_terminalData_t mAmount_s;
	float MaxAmount;
	printf("Tester Name = Ahmed Elsayed Hamed Mohamed\n");
	printf("Function Name = setMaxAmount\n");
	printf("Test Case 1\n");
	printf("Input Data:");
	scanf_s("%f", &MaxAmount);
	status = setMaxAmount(&mAmount_s, MaxAmount);
	printf("Expected Result: TERMINAL_OK\n");
	if (status == TERMINAL_OK)
	{
		printf("Actual Result: TERMINAL_OK\n");
	}
	else
	{
		printf("Actual Result: INVALID_MAX_AMOUNT\n");
	}
	status = 0;
	printf("Test Case 2\n");
	printf("Input Data:");
	scanf_s("%f", &MaxAmount);
	status = setMaxAmount(&mAmount_s, MaxAmount);
	printf("Expected Result: INVALID_MAX_AMOUNT\n");
	if (status == TERMINAL_OK)
	{
		printf("Actual Result: TERMINAL_OK\n");
	}
	else
	{
		printf("Actual Result: INVALID_MAX_AMOUNT\n");
	}
	status = 0;
	printf("Test Case 3\n");
	printf("Input Data:");
	scanf_s("%f", &MaxAmount);
	status = setMaxAmount(&mAmount_s, MaxAmount);
	printf("Expected Result: INVALID_MAX_AMOUNT\n");
	if (status == TERMINAL_OK)
	{
		printf("Actual Result: TERMINAL_OK\n");
	}
	else
	{
		printf("Actual Result: INVALID_MAX_AMOUNT\n");
	}
}