#include "server.h"

struct ST_accountsDB_t accountsDB[255];
struct ST_transaction_t transactions[255];
uint8_t index = 0;
void initializeAccountsDB(void)
{
	uint8_t i;
	for (i = 0; i < 255; i++)
	{
		accountsDB[i].balance = 0;
		accountsDB[i].state = RUNNING;
		strcpy_s(accountsDB[i].primaryAccountNumber,20, "00000000000000000000");
	}
}
void fillTenDifferentAccounts(void)
{
	accountsDB[0].balance = 1000;
	accountsDB[0].state = RUNNING;
	strcpy_s(accountsDB[0].primaryAccountNumber,20, "123456789123456789");
	accountsDB[1].balance = 2000;
	accountsDB[1].state = RUNNING;
	strcpy_s(accountsDB[1].primaryAccountNumber,20, "123456789123456788");
	accountsDB[2].balance = 3000;
	accountsDB[2].state = RUNNING;
	strcpy_s(accountsDB[2].primaryAccountNumber,20, "123456789123456787");
	accountsDB[3].balance = 4000;
	accountsDB[3].state = RUNNING;
	strcpy_s(accountsDB[3].primaryAccountNumber,20, "123456789123456786");
	accountsDB[4].balance = 5000;
	accountsDB[4].state = RUNNING;
	strcpy_s(accountsDB[4].primaryAccountNumber,20, "123456789123456785");
	accountsDB[5].balance = 6000;
	accountsDB[5].state = BLOCKED;
	strcpy_s(accountsDB[5].primaryAccountNumber,20, "123456789123456784");
	accountsDB[6].balance = 7000;
	accountsDB[6].state = BLOCKED;
	strcpy_s(accountsDB[6].primaryAccountNumber,20, "123456789123456783");
	accountsDB[7].balance = 8000;
	accountsDB[7].state = BLOCKED;
	strcpy_s(accountsDB[7].primaryAccountNumber,20, "123456789123456782");
	accountsDB[8].balance = 9000;
	accountsDB[8].state = BLOCKED;
	strcpy_s(accountsDB[8].primaryAccountNumber,20, "123456789123456781");
	accountsDB[9].balance = 10000;
	accountsDB[9].state = BLOCKED;
	strcpy_s(accountsDB[9].primaryAccountNumber,20, "123456789123456780");
}

void initializeTransactions(void)
{
	uint8_t i;
	for (i = 0; i < 255; i++)
	{
		strcpy_s(transactions[i].cardHolderData.cardHolderName,20,"0000000000000000000000000");
		strcpy_s(transactions[i].cardHolderData.primaryAccountNumber,20, "00000000000000000000");
		strcpy_s(transactions[i].cardHolderData.cardExpirationDate,6, "000000");
		strcpy_s(transactions[i].terminalData.transactionDate,11, "00000000000");
		transactions[i].terminalData.transAmount = 0;
		transactions[i].terminalData.maxTransAmount = 0;
		transactions[i].transactionSequenceNumber = 0;
		transactions[i].transState = APPROVED;
	}
}

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	uint8_t i;
	uint8_t accountIndex = 0;
	uint8_t accountStatus;
	uint8_t amountStatus;
	uint8_t nameState = 0;
	uint8_t PANState;
	uint8_t expState;
	uint8_t transactionState = 0 ;
	struct ST_cardData_t cardData;
	struct ST_terminalData_t terminalData;
	//initializeTransactions();
	printf("PAN: ");
	getCardPAN(&transData->cardHolderData);
	for (i = 0; i < 255; i++)
	{
		accountStatus = strcmp(accountsDB[i].primaryAccountNumber, transData->cardHolderData.primaryAccountNumber);
		if (accountStatus == 0)
		{
			accountIndex = i;
			break;
		}
	}
	if (accountStatus != 0)
	{
		return FRAUD_CARD;
	}
	printf("Transactione Amount: ");
	getTransactionAmount(&terminalData);
	if (terminalData.transAmount > accountsDB[accountIndex].balance)
	{
		return DECLINED_INSUFFECIENT_FUND;
	}
	if (&accountsDB[accountIndex].state == BLOCKED)
	{
		return DECLINED_STOLEN_CARD;
	}
	printf("Transaction Sequence Number: ");
	scanf_s("%d", &transData->transactionSequenceNumber);
	if (transData->transactionSequenceNumber == 0)
	{
		return INTERNAL_SERVER_ERROR;
	}
	return APPROVED;
}

/*
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	uint8_t i;
	uint8_t accountIndex;
	uint8_t accountStatus;
	uint8_t amountStatus;
	uint8_t nameState = 0;
	uint8_t PANState;
	uint8_t expState;
	uint8_t transactionState = 0 ;
	struct ST_cardData_t cardData;
	struct ST_terminalData_t terminalData;
	printf("cardHolderName: ");
	nameState = getCardHolderName(&cardData);
	if (nameState == WRONG_NAME)
	{
		printf("WRONG NAME\n");
		return FRAUD_CARD;
	}
	printf("cardPAN: ");
	PANState = getCardPAN(&cardData);
	if (PANState == WRONG_PAN)
	{
		printf("WRONG PAN\n");
		return FRAUD_CARD;
	}
	printf("cardExpiryDate: ");
	expState = getCardExpiryDate(&cardData);
	if (expState == WRONG_EXP_DATE)
	{
		printf("WRONG EXPIRY DATE\n");
		return FRAUD_CARD;
	}
	for (i = 0; i < 255; i++)
	{
		accountStatus = strcmp(transactions[i].cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName);
		if (accountStatus == 0)
		{
			accountIndex = i;
			break;
		}
	}
	if (accountStatus != 0)
	{
		return FRAUD_CARD;
	}
	
printf("Transactione Date: ");
transactionState = getTransactionDate(&terminalData);
if (transactionState == WRONG_DATE)
{
	printf("WRONG TRANSACTION DATE\n");
	return FRAUD_CARD;
}
printf("Transactione Amount: ");
transactionState = 0;
transactionState = getTransactionAmount(&terminalData);
if (transactionState == INVALID_AMOUNT)
{
	printf("INVALID AMOUNT\n");
	return FRAUD_CARD;
}
transactionState = 0;
transactionState = setMaxAmount(&terminalData, accountsDB[accountIndex].balance);
if (transactionState == INVALID_MAX_AMOUNT)
{
	printf("INVALID MAX AMOUNT\n");
	return FRAUD_CARD;
}
amountStatus = isBelowMaxAmount(&transData->terminalData.transAmount);
if (amountStatus == EXCEED_MAX_AMOUNT)
{
	return DECLINED_INSUFFECIENT_FUND;
}
if (accountsDB[accountIndex].state == BLOCKED)
{
	return DECLINED_STOLEN_CARD;
}
printf("Transaction Sequence Number: ");
scanf_s("%d", &transData->transactionSequenceNumber);
if (transData->transactionSequenceNumber == 0)
{
	return INTERNAL_SERVER_ERROR;
}
return APPROVED;
}
*/

/* Example Test
* [Case 1] Correct PAN 123456789123456789
*/
void recieveTransactionDataTest(void)
{
	struct ST_transaction_t transactionData;
	fillTenDifferentAccounts();
	uint8_t status = 0;
	printf("Tester Name = Ahmed Elsayed Hamed Mohamed\n");
	printf("Function Name = recieveTransactionData\n");
	printf("Test Case 1\n");
	printf("Input Data:");
	status = recieveTransactionData(&transactionData);
	printf("Expected Result: APPROVED\n");
	if (status == APPROVED)
	{
		printf("Actual Result: APPROVED\n");
	}
	else if(status == DECLINED_INSUFFECIENT_FUND)
	{
		printf("Actual Result: DECLINED_INSUFFECIENT_FUND\n");
	}
	else if (status == DECLINED_STOLEN_CARD)
	{
		printf("Actual Result: DECLINED_STOLEN_CARD\n");
	}
	else if (status == FRAUD_CARD)
	{
		printf("Actual Result: FRAUD_CARD\n");
	}
	else if (status == INTERNAL_SERVER_ERROR)
	{
		printf("Actual Result: INTERNAL_SERVER_ERROR\n");
	}
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	uint8_t accountStatus;
	uint8_t accountIndex;
	uint8_t i;
	for (i = 0; i < 255; i++)
	{
		accountStatus = strcmp(accountRefrence[i].primaryAccountNumber, cardData->primaryAccountNumber);
		if (accountStatus == 0)
		{
			accountIndex = i;
			break;
		}
	}
	if (accountStatus == 0)
	{
		return SERVER_OK;
	}
	else
	{
		return ACCOUNT_NOT_FOUND;
	}
}

/* Example Test
* [Case 1] Correct PAN 123456789123456789
* [Case 2] Wrong PAN 123321456654789987
*/
void isValidAccountTest(void)
{
	struct ST_cardData_t cardData;
	fillTenDifferentAccounts();
	uint8_t status = 0;
	printf("Tester Name = Ahmed Elsayed Hamed Mohamed\n");
	printf("Function Name = isValidAccount\n");
	printf("Test Case 1\n");
	printf("Input Data:");
	printf("PAN: ");
	getCardPAN(&cardData);
	status = isValidAccount(&cardData,&accountsDB);
	printf("Expected Result: ACCOUNT IS FOUND\n");
	if (status == SERVER_OK)
	{
		printf("Actual Result: ACCOUNT IS FOUND\n");
	}
	else
	{
		printf("Actual Result: ACCOUNT IS NOT FOUND\n");
	}
	status = 0;
	printf("Test Case 2\n");
	printf("Input Data:");
	printf("PAN: ");
	getCardPAN(&cardData);
	status = isValidAccount(&cardData, &accountsDB);
	printf("Expected Result: ACCOUNT IS NOT FOUND\n");
	if (status == SERVER_OK)
	{
		printf("Actual Result: ACCOUNT IS FOUND\n");
	}
	else
	{
		printf("Actual Result: ACCOUNT IS NOT FOUND\n");
	}
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	if (accountRefrence->state == RUNNING)
	{
		return SERVER_OK;
	}
	else
	{
		return BLOCKED_ACCOUNT;
	}
}

/* Example Test
* [Case 1] Running Account 1
* [Case 2] Blocking Account 5
*/
void isBlockedAccountTest(void)
{
	fillTenDifferentAccounts();
	uint8_t status = 0;
	uint32_t account_index;
	printf("Tester Name = Ahmed Elsayed Hamed Mohamed\n");
	printf("Function Name = isBlockedAccount\n");
	printf("Test Case 1\n");
	printf("Input Data:");
	scanf_s("%d", &account_index);
	status = isBlockedAccount(&accountsDB[account_index]);
	printf("Expected Result: Account Is Running\n");
	if (status == SERVER_OK)
	{
		printf("Actual Result: Account Is Running\n");
	}
	else
	{
		printf("Actual Result: ACCOUNT IS BLOCKING\n");
	}
	status = 0;
	printf("Test Case 2\n");
	printf("Input Data:");
	scanf_s("%d", &account_index);
	status = isBlockedAccount(&accountsDB[account_index]);
	printf("Expected Result: ACCOUNT IS BLOCKING\n");
	if (status == SERVER_OK)
	{
		printf("Actual Result: Account Is Running\n");
	}
	else
	{
		printf("Actual Result: ACCOUNT IS BLOCKING\n");
	}
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	if ((accountRefrence->balance) < (termData->transAmount))
	{
		return LOW_BALANCE;
	}
	else
	{
		return SERVER_OK;
	}
}

/* Example Test
* [Case 1]  Amount Available (index=1 , transaction amount=1000)
* [Case 2] Not Amount Available (index=1 , transaction amount=5000)
*/
void isAmountAvailableTest(void)
{
	struct ST_terminalData_t terminData;
	fillTenDifferentAccounts();
	uint8_t status = 0;
	uint32_t account_index;
	printf("Tester Name = Ahmed Elsayed Hamed Mohamed\n");
	printf("Function Name = isAmountAvailable\n");
	printf("Test Case 1\n");
	printf("Input Data:\n");
	printf("account index:");
	scanf_s("%d", &account_index);
	printf("transaction ammount:");
	scanf_s("%f", &terminData.transAmount);
	status = isAmountAvailable(&terminData, &accountsDB[account_index]);
	printf("Expected Result: Amount Is Available\n");
	if (status == SERVER_OK)
	{
		printf("Actual Result: Amount Is Available\n");
	}
	else
	{
		printf("Actual Result:Amount Is Unavailable\n");
	}
	status = 0;
	printf("Test Case 2\n");
	printf("Input Data:\n");
	printf("account index:");
	scanf_s("%d", &account_index);
	printf("transaction ammount:");
	scanf_s("%f", &terminData.transAmount);
	status = isAmountAvailable(&terminData, &accountsDB[account_index]);
	printf("Expected Result: Amount Is Unavailable\n");
	if (status == SERVER_OK)
	{
		printf("Actual Result: Amount Is Available\n");
	}
	else
	{
		printf("Actual Result:Amount Is Unavailable\n");
	}
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	uint8_t i;
	for (i = 0; i < 11; i++)
	{
		transactions[index].terminalData.transactionDate[i] = transData->terminalData.transactionDate[i];
	}
	for (i = 0; i < 6; i++)
	{
		transactions[index].cardHolderData.cardExpirationDate[i] = transData->cardHolderData.cardExpirationDate[i];
	}
	for (i = 0; i < 19; i++)
	{
		transactions[index].cardHolderData.primaryAccountNumber[i] = transData->cardHolderData.primaryAccountNumber[i];
	}
	for (i = 0; i < 24; i++)
	{
		transactions[index].cardHolderData.cardHolderName[i] = transData->cardHolderData.cardHolderName[i];
	}
	transactions[index].terminalData.transAmount = transData->terminalData.transAmount;
	transactions[index].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
	transactions[index].transactionSequenceNumber = transData->transactionSequenceNumber;
	transactions[index].transState = transData->transState;
	/*transactionSequenceNumber range (00000001 - 99999999)*/
	index++;
	if (transactions[index].transactionSequenceNumber == 100000000)
	{
		printf("Transactions DataBase is Full\n");
		return SAVING_FAILED;
	}
	return SERVER_OK;
}

/* Example Test
* [Case 1]
* cardHolderName: AHMED ELSAYED HAMED MO
* PAN: 123456789123456789
* cardExpirationDate: 02/25
* transactionDate:05/10/2022
* transAmount: 500
* maxTransAmount: 700
* transactionSequenceNumber: 00000001
* transState: APPROVED (0)
*/
void saveTransactionTest(void)
{
	struct ST_transaction_t transacData;
	uint8_t status = 0;
	printf("Tester Name = Ahmed Elsayed Hamed Mohamed\n");
	printf("Function Name = saveTransaction\n");
	printf("Test Case 1\n");
	printf("Input Data:\n");
	printf("cardHollderName: ");
	gets(transacData.cardHolderData.cardHolderName);
	printf("primaryAccountNumber: ");
	gets(transacData.cardHolderData.primaryAccountNumber);
	printf("cardExpirationDate: ");
	gets(transacData.cardHolderData.cardExpirationDate);
	printf("transactionDate: ");
	gets(transacData.terminalData.transactionDate);
	printf("transAmount: ");
	scanf_s("%f",&transacData.terminalData.transAmount);
	printf("maxTransAmount: ");
	scanf_s("%f", &transacData.terminalData.maxTransAmount);
	printf("transactionSequenceNumber: ");
	scanf_s("%d", &transacData.transactionSequenceNumber);
	printf("transState: ");
	scanf_s("%d", &transacData.transState);
	status = saveTransaction(&transacData);
	printf("Expected Result: Saving Success\n");
	if (status == SERVER_OK)
	{
		printf("Actual Result: Saving Success\n");
	}
	else
	{
		printf("Actual Result:Saving Failed\n");
	}
}

void listSavedTransactions(void)
{
	uint8_t i;
	for ( i = 0; i < index; i++)
	{
		printf("\n");
		printf("#########################\n");
		printf("Transaction Sequence Number: %d \n", transactions[i].transactionSequenceNumber);
		printf("Transaction Date: ");
		puts(&transactions[i].terminalData.transactionDate);
		printf("Transaction Amount :%f \n", transactions[i].terminalData.transAmount);
		printf("Transaction State: %d \n", transactions[i].transState);
		printf("Terminal Max Amount: %f \n", transactions[i].terminalData.maxTransAmount);
		printf("Cardholder Name: ");
		puts(&transactions[i].cardHolderData.cardHolderName);
		printf("PAN: ");
		puts(&transactions[i].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: ");
		puts(&transactions[i].cardHolderData.cardExpirationDate);
		printf("#########################\n");
	}
}

/* Example Test
* [Case 1]
* cardHolderName: AHMED ELSAYED HAMED MO
* PAN: 123456789123456789
* cardExpirationDate: 02/25
* transactionDate:05/10/2022
* transAmount: 500
* maxTransAmount: 700
* transactionSequenceNumber: 1
* transState: APPROVED (0)
*/
void listSavedTransactionsTest(void)
{
	uint8_t i;
	struct ST_transaction_t transacData;
	printf("Tester Name = Ahmed Elsayed Hamed Mohamed\n");
	printf("Function Name = listSavedTransactions\n");
	printf("Test Case 1\n");
	printf("Input Data:\n");
	printf("cardHolderName: ");
	gets(&transacData.cardHolderData.cardHolderName);
	printf("PAN: ");
	gets(&transacData.cardHolderData.primaryAccountNumber);
	printf("cardExpirationDate: ");
	gets(&transacData.cardHolderData.cardExpirationDate);
	printf("transactionDate: ");
	gets(&transacData.terminalData.transactionDate);
	printf("transAmount: ");
	scanf_s("%f", &transacData.terminalData.transAmount);
	printf("maxTransAmount: ");
	scanf_s("%f", &transacData.terminalData.maxTransAmount);
	printf("transactionSequenceNumber: ");
	scanf_s("%d", &transacData.transactionSequenceNumber);
	printf("transState: ");
	scanf_s("%d", &transacData.transState);
	saveTransaction(&transacData);
	listSavedTransactions();
}