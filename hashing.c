#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ELEMENT 997

typedef enum { FALSE, TRUE }bool;

typedef union Data
{
	bool bool_data;
	int int_data;
	float float_data;
	char string_data[20];
}Data;

typedef struct Linked_List
{
	Data data;
	int choice;
	struct Linked_List* next;
}List;

List* create_node(Data data, int choice)
{
	List* nptr = (List*)malloc(sizeof(List));
	nptr->data = data;
	nptr->choice = choice;
	nptr->next = NULL;
	return nptr;
}

int hash_function(Data data, int choice, int hash)
{
	bool bval;
	int int_val, hash_value, ascii_char, len, i, index;
	float dec_val;
	char string_val[20], conv_string[20];
	hash_value = 0;
	if (choice == 1)
	{
		bval = data.bool_data;
		if (bval == TRUE)
		{
			sprintf(conv_string, "%d", 1);
			ascii_char = conv_string[0];
			hash_value += ascii_char;
		}
		else
		{
			sprintf(conv_string, "%d", 1);
			ascii_char = conv_string[0];
			hash_value += ascii_char;
		}
	}
	else if (choice == 2)
	{
		int_val = data.int_data;
		sprintf(conv_string, "%d", int_val);
		len = strlen(conv_string);
		for (i = 0; i < len; i++)
		{
			ascii_char = conv_string[i];
			hash_value += ascii_char;
		}
	}
	else if (choice == 3)
	{
		dec_val = data.float_data;
		sprintf(conv_string, "%f", dec_val);
		len = strlen(conv_string);
		for (i = 0; i < len; i++)
		{
			ascii_char = conv_string[i];
			hash_value += ascii_char;
		}
	}
	else if (choice == 4)
	{
		strcpy(string_val, data.string_data);
		len = strlen(string_val);
		for (i = 0; i < len; i++)
		{
			ascii_char = string_val[i];
			hash_value += ascii_char;
		}
	}
	index = hash_value % hash;
	return index;
}

void individual_cardinality(List* set[], int* count_int, int* count_float, int* count_str, int* count_char)
{
	int i;
	List* ptr, * lptr;
	*count_int = 0;
	*count_float = 0;
	*count_str = 0;
	*count_char = 0;
	for (i = 0; i < MAX_ELEMENT; i++)
	{
		lptr = set[i];
		if (lptr != NULL)
		{
			ptr = lptr;
			while (ptr != NULL)
			{
				if (ptr->choice == 2)
				{
					(*count_int)++;
				}
				else if (ptr->choice == 3)
				{
					(*count_float)++;
				}
				else if (ptr->choice == 4 && strlen(ptr->data.string_data) == 1)
				{
					(*count_char)++;
				}
				else if (ptr->choice == 4)
				{
					(*count_str)++;
				}
				ptr = ptr->next;
			}
		}
	}
}

bool is_Element(List* set[], List* lptr)
{
	bool bval, flag;
	int int_val, hash_val, hash;
	float dec_val;
	char string_val[20];
	List* ptr;
	flag = FALSE;
	hash = MAX_ELEMENT;
	if (lptr->choice == 1)
	{
		bval = lptr->data.bool_data;
		if (bval != 0 && bval != 1)
		{
			flag = FALSE;
		}
		else
		{
			hash_val = hash_function(lptr->data, lptr->choice, hash);
			ptr = set[hash_val];
			while (ptr != NULL)
			{
				if (bval == ptr->data.bool_data)
				{
					flag = TRUE;
					break;
				}
				ptr = ptr->next;
			}
		}
	}
	else if (lptr->choice == 2)
	{
		int_val = lptr->data.int_data;
		hash_val = hash_function(lptr->data, lptr->choice, hash);
		ptr = set[hash_val];
		while (ptr != NULL)
		{
			if (int_val == ptr->data.int_data)
			{
				flag = TRUE;
				break;
			}
			ptr = ptr->next;
		}
	}
	else if (lptr->choice == 3)
	{
		dec_val = lptr->data.float_data;
		hash_val = hash_function(lptr->data, lptr->choice, hash);
		ptr = set[hash_val];
		while (ptr != NULL)
		{
			if (dec_val == ptr->data.float_data)
			{
				flag = TRUE;
				break;
			}
			ptr = ptr->next;
		}
	}
	else if (lptr->choice == 4)
	{
		strcpy(string_val, lptr->data.string_data);
		hash_val = hash_function(lptr->data, lptr->choice, hash);
		ptr = set[hash_val];
		while (ptr != NULL)
		{
			if (strcmp(string_val, ptr->data.string_data) == 0);
			{
				flag = TRUE;
				break;
			}
			ptr = ptr->next;
		}
	}
	return flag;
}

bool is_Empty(List* set[])
{
	int i;
	bool flag;
	flag = TRUE;
	for (i = 0; i < MAX_ELEMENT; i++)
	{
		if (set[i] != NULL)
		{
			flag = FALSE;
			break;
		}
	}
	return flag;
}

int cardinality(List* set[])
{
	int count, i;
	List* ptr, * lptr;
	count = 0;
	for (i = 0; i < MAX_ELEMENT; i++)
	{
		lptr = set[i];
		if (lptr != NULL)
		{
			ptr = lptr;
			while (ptr != NULL)
			{
				count++;
				ptr = ptr->next;
			}
		}
	}
	return count;
}

List* enumerate(List* set[], int choice)	//Modify for character.
{
	List* head;
	int i;
	List* lptr, * ptr, * nptr;
	head = NULL;
	
	for (i = 0; i < MAX_ELEMENT; i++)
	{
		lptr = set[i];
		if (lptr != NULL)
		{
			ptr = lptr;
			while (ptr != NULL)
			{
				if (ptr->choice == choice)
				{
					nptr = create_node(ptr->data, choice);
					nptr->next = head;
					head = nptr;
				}
				ptr = ptr->next;
			}
		}
	}
	return head;
}

List* build(List* lptr, List* set[])	//here hash value is 100;
{
	int hash, hash_val;
	List* ptr, * nptr, * new_ptr;
	hash = 100;
	ptr = lptr;
	if (ptr->choice < 5 && ptr->choice > 1)
	{
		while (ptr != NULL)
		{
			hash_val = hash_function(ptr->data, ptr->choice, hash);
			new_ptr = create_node(ptr->data, ptr->choice);
			if (set[hash_val] == NULL)
			{
				set[hash_val] = new_ptr;
			}
			else
			{
				nptr = set[hash_val];
				while (nptr->next != NULL)
				{
					nptr = nptr->next;
				}
				nptr->next = new_ptr;
			}
			ptr = ptr->next;
		}
	}
	return *set;
}

void create()
{
	List* set[MAX_ELEMENT];
	int i;
	for (i = 0; i < MAX_ELEMENT; i++)
	{
		set[i] = malloc(sizeof(List));
		set[i] = NULL;
	}
}

List* add(List* set[], List* lptr)
{
	bool flag;
	int hash_val, hash;
	List* ptr, * prev;
	hash = MAX_ELEMENT;
	hash_val = hash_function(lptr->data, lptr->choice, hash);
	flag = TRUE;
	if (set[hash_val] == NULL)
	{
		set[hash_val] = lptr;
	}
	else
	{
		prev = NULL;
		ptr = set[hash_val];
		while (ptr != NULL)
		{
			if (flag == TRUE)
			{
				if (ptr->choice == lptr->choice)
				{
					if (lptr->choice == 1)
					{
						if (ptr->data.bool_data == lptr->data.bool_data)
						{
							flag = FALSE;
						}
					}
					else if (lptr->choice == 2)
					{
						if (ptr->data.int_data == lptr->data.int_data)
						{
							flag = FALSE;
						}
					}
					else if (lptr->choice == 3)
					{
						if (ptr->data.float_data == lptr->data.float_data)
						{
							flag = FALSE;
						}
					}
					else if (lptr->choice == 4)
					{
						if (strcmp(ptr->data.string_data, lptr->data.string_data) == 0)
						{
							flag = FALSE;
						}
					}
				}
			}
			prev = ptr;
			ptr = ptr->next;
		}
		if (flag == TRUE)
		{
			prev->next = lptr;
			printf("Value Added.\n");
		}
		else
		{
			printf("Value Exists.\n");
		}
	}
	return *set;
}

List* delete(List* set[], List* lptr)
{
	bool flag;
	int hash_val, hash;
	List* ptr, * prev;
	hash = MAX_ELEMENT;
	hash_val = hash_function(lptr->data, lptr->choice, hash);
	flag = TRUE;
	prev = NULL;
	ptr = set[hash_val];
	while (ptr != NULL)
	{
		if (flag == TRUE)
		{
			if (ptr->choice == lptr->choice)
			{
				if (lptr->choice == 1)
				{
					if (ptr->data.bool_data == lptr->data.bool_data)
					{
						flag = FALSE;
					}
				}
				else if (lptr->choice == 2)
				{
					if (ptr->data.int_data == lptr->data.int_data)
					{
						flag = FALSE;
					}
				}
				else if (lptr->choice == 3)
				{
					if (ptr->data.float_data == lptr->data.float_data)
					{
						flag = FALSE;
					}
				}
				else if (lptr->choice == 4)
				{
					if (strcmp(ptr->data.string_data, lptr->data.string_data) == 0)
					{
						flag = FALSE;
					}
				}
			}

			if (flag == FALSE)
			{
				if (prev == NULL)
				{
					set[hash_val] = NULL;
				}
				else
				{
					prev->next = ptr->next;
				}
				free(ptr);
				break;
			}
		}
		prev = ptr;
		ptr = ptr->next;
	}
	if (flag == TRUE)
	{
		printf("Value Not Present.\n");
	}
	else
	{
		printf("Value Deleted.\n");
	}
	
	return *set;
}

List* intersection(List* S[], List* T[], List* result[])
{
	int i;
	bool flag;
	List* ptr_s, * ptr_t, * ptr;
	ptr = NULL;
	for (i = 0; i < MAX_ELEMENT; i++)
	{
		ptr_s = S[i];
		while (ptr_s != NULL)
		{
			ptr_t = T[i];
			while (ptr_t != NULL)
			{
				flag = FALSE;
				if (ptr_s->choice == ptr_t->choice)
				{
					if (ptr_t->choice == 1 && (ptr_t->data.bool_data == ptr_s->data.bool_data))
					{
						ptr = create_node(ptr_t->data, ptr_t->choice);
						flag = TRUE;
					}
					else if (ptr_t->choice == 2 && (ptr_t->data.int_data == ptr_s->data.int_data))
					{
						ptr = create_node(ptr_t->data, ptr_t->choice);
						flag = TRUE;
					}
					else if (ptr_t->choice == 3 && (ptr_t->data.float_data == ptr_s->data.float_data))
					{
						ptr = create_node(ptr_t->data, ptr_t->choice);
						flag = TRUE;
					}
					else if (ptr_t->choice == 4 && (strcmp(ptr_t->data.string_data, ptr_s->data.string_data) == 0))
					{
						ptr = create_node(ptr_t->data, ptr_t->choice);
						flag = TRUE;
					}

					if (flag == TRUE)
					{
						if (result[i] == NULL)
						{
							result[i] = ptr;
						}
						else
						{
							List* lptr = result[i];
							while (lptr->next != NULL)
							{
								lptr = lptr->next;
							}
							lptr->next = ptr;
						}
					}
				}
				ptr_t = ptr_t->next;
			}
			ptr_s = ptr_s->next;
		}
	}
	return *result;
}

bool is_subset(List* S[], List* T[])
{
	bool flag;
	int i;
	List* ptr_s, * ptr_t;
	flag = TRUE;
	for (i = 0; (i < MAX_ELEMENT && flag != FALSE); i++)
	{
		if (S[i] != NULL && T[i] != NULL)
		{
			ptr_s = S[i];
			ptr_t = T[i];
			while (ptr_s != NULL && ptr_t != NULL && flag != FALSE)
			{
				if (ptr_s->choice == ptr_t->choice)
				{
					if (ptr_s->choice == 1)
					{
						if (ptr_s->data.bool_data != ptr_t->data.bool_data)
						{
							flag = FALSE;
						}
					}
					else if (ptr_s->choice == 2)
					{
						if (ptr_s->data.int_data != ptr_t->data.int_data)
						{
							flag = FALSE;
						}
					}
					else if (ptr_s->choice == 3)
					{
						if (ptr_s->data.float_data != ptr_t->data.float_data)
						{
							flag = FALSE;
						}
					}
					else if (ptr_s->choice == 4)
					{
						if (strcmp(ptr_s->data.string_data, ptr_t->data.string_data) != 0)
						{
							flag = FALSE;
						}
					}
				}
				else
				{
					flag = FALSE;
				}
				ptr_s = ptr_s->next;
				ptr_t = ptr_t->next;
			}

			if (ptr_s != NULL || ptr_t != NULL)
			{
				flag = FALSE;
			}
		}
		else if (S[i] == NULL && T[i] == NULL)
		{
			continue;
		}
		else
		{
			flag = FALSE;
		}
	}
	return flag;
}

List* set_union(List* S[], List* T[], List* result[])
{
	bool flag;
	int i;
	List* ptr_t, * ptr_s, * ptr, * lptr;
	for (i = 0; i < MAX_ELEMENT; i++)
	{
		if (S[i] != NULL && T[i] == NULL)
		{
			ptr_s = S[i];
			while (ptr_s != NULL)
			{
				ptr = create_node(ptr_s->data, ptr_s->choice);
				if (result[i] == NULL)
				{
					result[i] = ptr;
				}
				else
				{
					lptr = result[i];
					while (lptr->next != NULL)
					{
						lptr = lptr->next;
					}
					lptr->next = ptr;
				}
				ptr_s = ptr_s->next;
			}
		}
		else if (S[i] == NULL && T[i] != NULL)
		{
			ptr_t = T[i];
			while (ptr_t != NULL)
			{
				ptr = create_node(ptr_t->data, ptr_t->choice);
				if (result[i] == NULL)
				{
					result[i] = ptr;
				}
				else
				{
					lptr = result[i];
					while (lptr->next != NULL)
					{
						lptr = lptr->next;
					}
					lptr->next = ptr;
				}
				ptr_t = ptr_t->next;
			}
		}
		else if (S[i] != NULL && T[i] != NULL)
		{
			ptr = NULL;
			ptr_s = S[i];
			ptr_t = T[i];
			while (ptr_s != NULL && ptr_t != NULL)
			{
				flag = FALSE;
				if (ptr_s->choice == ptr_t->choice)
				{
					if (ptr_t->choice == 1 && (ptr_t->data.bool_data == ptr_s->data.bool_data))
					{
						ptr = create_node(ptr_t->data, ptr_t->choice);
						flag = TRUE;
					}
					else if (ptr_t->choice == 2 && (ptr_t->data.int_data == ptr_s->data.int_data))
					{
						ptr = create_node(ptr_t->data, ptr_t->choice);
						flag = TRUE;
					}
					else if (ptr_t->choice == 3 && (ptr_t->data.float_data == ptr_s->data.float_data))
					{
						ptr = create_node(ptr_t->data, ptr_t->choice);
						flag = TRUE;
					}
					else if (ptr_t->choice == 4 && (strcmp(ptr_t->data.string_data, ptr_s->data.string_data) == 0))
					{
						ptr = create_node(ptr_t->data, ptr_t->choice);
						flag = TRUE;
					}
				}

				if (flag == TRUE)
				{
					if (result[i] == NULL)
					{
						result[i] = ptr;
					}
					else
					{
						lptr = result[i];
						while (lptr->next != NULL)
						{
							lptr = lptr->next;
						}
						lptr->next = ptr;
					}
				}
				else
				{
					if (result[i] == NULL)
					{
						lptr = result[i];
						ptr = create_node(ptr_s->data, ptr_s->choice);
						lptr = ptr;
						result[i] = lptr;
						ptr = create_node(ptr_t->data, ptr_t->choice);
						result[i]->next = ptr;
					}
					else
					{
						lptr = result[i];
						ptr = create_node(ptr_s->data, ptr_s->choice);
						ptr->next = lptr;
						lptr = ptr;
						ptr = create_node(ptr_t->data, ptr_t->choice);
						ptr->next = lptr;
						lptr = ptr;
						result[i] = lptr;
					}
				}
				ptr_s = ptr_s->next;
				ptr_t = ptr_t->next;
			}

			while (ptr_s != NULL)
			{
				ptr = create_node(ptr_s->data, ptr_s->choice);
				lptr = result[i];
				ptr->next = lptr;
				lptr = ptr;
				result[i] = lptr;
				ptr_s = ptr_s->next;
			}

			while (ptr_t != NULL)
			{
				ptr = create_node(ptr_t->data, ptr_t->choice);
				lptr = result[i];
				ptr->next = lptr;
				lptr = ptr;
				result[i] = lptr;
				ptr_t = ptr_t->next;
			}
		}
	}
	return *result;
}

List* set_difference(List* S[], List* T[], List* result[])
{
	bool flag;
	int i;
	List* ptr_t, * ptr_s, * ptr, * lptr;
	ptr = NULL;
	for (i = 0; i < MAX_ELEMENT; i++)
	{
		if (S[i] != NULL && T[i] == NULL)
		{
			result[i] = S[i];
		}
		else if (S[i] != NULL && T[i] != NULL)
		{
			ptr_t = T[i];
			while (ptr_t != NULL)
			{
				ptr_s = S[i];
				while (ptr_s != NULL)
				{
					flag = FALSE;
					if (ptr_s->choice == ptr_t->choice)
					{
						if (ptr_t->choice == 1 && (ptr_t->data.bool_data == ptr_s->data.bool_data))
						{
							ptr = create_node(ptr_t->data, ptr_t->choice);
							flag = TRUE;
						}
						else if (ptr_t->choice == 2 && (ptr_t->data.int_data == ptr_s->data.int_data))
						{
							ptr = create_node(ptr_t->data, ptr_t->choice);
							flag = TRUE;
						}
						else if (ptr_t->choice == 3 && (ptr_t->data.float_data == ptr_s->data.float_data))
						{
							ptr = create_node(ptr_t->data, ptr_t->choice);
							flag = TRUE;
						}
						else if (ptr_t->choice == 4 && (strcmp(ptr_t->data.string_data, ptr_s->data.string_data) == 0))
						{
							ptr = create_node(ptr_t->data, ptr_t->choice);
							flag = TRUE;
						}

						if (flag == FALSE)
						{
							if (result[i] == NULL)
							{
								ptr = create_node(ptr_s->data, ptr_s->choice);
								result[i] = ptr;
							}
							else
							{
								ptr = create_node(ptr_s->data, ptr_s->choice);
								lptr = result[i];
								ptr->next = lptr;
								lptr = ptr;
								result[i] = lptr;
							}
						}
					}
					else
					{
						if (result[i] == NULL)
						{
							ptr = create_node(ptr_s->data, ptr_s->choice);
							result[i] = ptr;
						}
						else
						{
							ptr = create_node(ptr_s->data, ptr_s->choice);
							lptr = result[i];
							ptr->next = lptr;
							lptr = ptr;
							result[i] = lptr;
						}
					}
					ptr_s = ptr_s->next;
				}
				ptr_t = ptr_t->next;
			}
		}
	}
	return *result;
}

void display_set(List* set[], int length)
{
	int i;
	List* ptr;
	for (i = 0; i < length; i++)
	{
		if (set[i] != NULL)
		{
			ptr = set[i];
			while (ptr != NULL)
			{
				if (ptr->choice == 1)
				{
					printf("The data is %d\n", ptr->data.bool_data);
				}
				else if (ptr->choice == 2)
				{
					printf("The data is %d\n", ptr->data.int_data);
				}
				else if (ptr->choice == 3)
				{
					printf("The data is %f\n", ptr->data.float_data);
				}
				else
				{
					printf("The data is %s\n", ptr->data.string_data);
				}
				ptr = ptr->next;
			}
		}
	}
}

List* input(List* set[])
{
	bool bval;
	int int_val, choice, index, hash;
	float dec_val;
	char string_val[20];
	choice = 1;
	List* ptr;
	hash = MAX_ELEMENT;
	while (choice < 5 && choice > 0)
	{
		Data value;
		List* lptr = NULL;
		printf("\n1. Boolean\n2. Integer\n3. Floating Point\n4. String\n5. Exit\n");
		printf("Enter your choice = ");
		scanf("%d", &choice);
		if (choice == 1)
		{
			printf("\n0. False\n1. True\n");
			printf("Enter set element = ");
			scanf("%d", &bval);
			while (bval != 0 && bval != 1)
			{
				printf("\nINCORRECT BOOLEAN VALUE!!!\nTRY AGAIN!!!\n");
				printf("Enter set element = ");
				scanf("%d", &bval);
			}
			value.bool_data = bval;
		}
		else if (choice == 2)
		{
			printf("Enter set element = ");
			scanf("%d", &int_val);
			value.int_data = int_val;
		}
		else if (choice == 3)
		{
			printf("Enter set element = ");
			scanf("%f", &dec_val);
			value.float_data = dec_val;
		}
		else if (choice == 4)
		{
			printf("Enter set element = ");
			scanf("%s", &string_val);
			strcpy(value.string_data, string_val);
		}
		if (choice < 5 && choice > 0)
		{
			index = hash_function(value, choice, hash);
			lptr = create_node(value, choice);
			if (set[index] == NULL)
			{
				set[index] = lptr;
			}
			else
			{
				ptr = set[index];
				while (ptr->next != NULL)
				{
					ptr = ptr->next;
				}
				ptr->next = lptr;
			}
		}
	}
	return *set;
}

void operation_1(List* set[])
{
	bool result;
	int choice, bval, int_val;
	float dec_val;
	char string_val[20];
	Data val;
	List* ptr = (List*)malloc(sizeof(List));
	choice = 1;
	printf("\n---------------------------------------------Operation 1--------------------------------------------\n");
	while (choice != 5)
	{
		printf("\n1. Boolean\n2. Integer\n3. Floating Point\n4. String\n5. Exit\n");
		printf("Enter the type of data = ");
		scanf("%d", &choice);
		if (choice == 1)
		{
			printf("Enter set element you want to check = ");
			scanf("%d", &bval);
			val.bool_data = bval;
		}
		else if (choice == 2)
		{
			printf("Enter set element you want to check = ");
			scanf("%d", &int_val);
			val.int_data = int_val;
		}
		else if (choice == 3)
		{
			printf("Enter set element you want to check = ");
			scanf("%f", &dec_val);
			val.float_data = dec_val;
		}
		else if (choice == 4)
		{
			printf("Enter set element you want to check = ");
			scanf("%s", &string_val);
			strcpy(val.string_data, string_val);
		}

		if (choice > 0 && choice < 5)
		{
			ptr->data = val;
			ptr->choice = choice;
			ptr->next = NULL;
			result = is_Element(set, ptr);
			if (result == TRUE)
			{
				printf("The Element is present in Set.\n");
			}
			else
			{
				printf("The Element is not present in Set.\n");
			}
		}
		else if (choice == 5)
		{
			printf("Exiting!!!\n");
		}
		else
		{
			printf("Incorrect Choice!!!\n");
			printf("Try Again!!!\n");
		}
	}
}

void operation_2(List* set[])
{
	bool flag;
	printf("\n---------------------------------------------Operation 2---------------------------------------------\n");
	flag = is_Empty(set);
	if (flag == TRUE)
	{
		printf("\nThe Set is Empty.\n");
	}
	else
	{
		printf("\nThe Set is not Empty.\n");
	}
}

void operation_3(List* set[])
{
	int size;
	printf("\n---------------------------------------------Operation 3---------------------------------------------\n");
	size = cardinality(set);
	printf("\nThe size of the set is %d.\n", size);
}

void operation_4(List* set[])
{
	int int_c, float_c, string_c, char_c, choice;
	List* lptr, * ptr;
	lptr = NULL;
	printf("\n---------------------------------------------Operation 4---------------------------------------------\n");
	individual_cardinality(set, &int_c, &float_c, &string_c, &char_c);
	printf("\n1. Integer\n2. Floating Point\n3. String\n4. Exit\n");
	printf("Which type of data would you like to enumerate = ");
	scanf("%d", &choice);
	if (choice > 0 && choice < 4)
	{
		lptr = enumerate(set, choice + 1);
	}
	else if (choice == 4)
	{
		printf("Exiting!!!\n");
	}
	else
	{
		printf("Incorrect Choice!!!\n");
	}

	if (lptr != NULL)
	{
		ptr = lptr;
		printf("Displaying the list : \n");
		if (choice == 1)
		{
			while (ptr != NULL)
			{
				printf("%d\n", ptr->data.int_data);
				ptr = ptr->next;
			}
		}
		else if (choice == 2)
		{
			while (ptr != NULL)
			{
				printf("%f\n", ptr->data.float_data);
				ptr = ptr->next;
			}
		}
		else if (choice == 3)
		{
			while (ptr != NULL)
			{
				printf("%s\n", ptr->data.string_data);
				ptr = ptr->next;
			}
		}
	}
}

void operation_5(List* set[])
{
	int i, len, choice, int_data;
	float float_data;
	char string_data[20];
	List* new_set[100];
	printf("\n---------------------------------------------Operation 5---------------------------------------------\n");
	for (i = 0; i < 100; i++)
	{
		new_set[i] = malloc(sizeof(List));
		new_set[i] = NULL;
	}
	printf("\nEnter the number of elements you want in the set = ");
	scanf("%d", &len);
	printf("\n1. Integer\n2. Floating Point\n3. String\n4. Exit\n");
	printf("Enter the type of data = ");
	scanf("%d", &choice);
	List* lptr, * ptr;
	lptr = NULL;
	if (choice == 1)
	{
		for (i = 0; i < len; i++)
		{
			printf("Enter data = ");
			scanf("%d", &int_data);
			ptr = (List*)malloc(sizeof(List));
			ptr->data.int_data = int_data;
			ptr->choice = choice + 1;
			ptr->next = lptr;
			lptr = ptr;
		}
	}
	else if (choice == 2)
	{
		for (i = 0; i < len; i++)
		{
			printf("Enter data = ");
			scanf("%f", &float_data);
			ptr = (List*)malloc(sizeof(List));
			ptr->data.float_data = float_data;
			ptr->choice = choice + 1;
			ptr->next = lptr;
			lptr = ptr;
		}
	}
	else if (choice == 3)
	{
		for (i = 0; i < len; i++)
		{
			printf("Enter data = ");
			scanf("%s", &string_data);
			ptr = (List*)malloc(sizeof(List));
			strcpy(ptr->data.string_data, string_data);
			ptr->choice = choice + 1;
			ptr->next = lptr;
			lptr = ptr;
		}
	}

	if (choice > 0 && choice < 4)
	{
		*new_set = build(lptr, new_set);
		printf("\n");
		display_set(new_set, 100);	//length of the array is 100.
	}
	else if (choice == 4)
	{
		printf("Exiting!!!\n");
	}
	else
	{
		printf("Incorrect Choice!!!\n");
	}
}

void operation_6()
{
	create();
}

void operation_7(List* set[])
{
	bool bval;
	int int_data, choice;
	float dec_val;
	char string_val[20];
	Data x_val;
	List* ptr;
	printf("\n---------------------------------------------Operation 7---------------------------------------------\n");
	printf("\n1. Boolean\n2. Integer\n3. Floating Point\n4. String\n5. Exit\n");
	printf("Enter the type of data you would like to add = ");
	scanf("%d", &choice);
	if (choice == 1)
	{
		printf("\n0. False\n1. True\n");
		printf("Enter set element = ");
		scanf("%d", &bval);
		while (bval != 0 && bval != 1)
		{
			printf("\nINCORRECT BOOLEAN VALUE!!!\nTRY AGAIN!!!\n");
			printf("Enter set element = ");
			scanf("%d", &bval);
		}
		x_val.bool_data = bval;
	}
	else if (choice == 2)
	{
		printf("Enter set element = ");
		scanf("%d", &int_data);
		x_val.int_data = int_data;
	}
	else if (choice == 3)
	{
		printf("Enter set element = ");
		scanf("%f", &dec_val);
		x_val.float_data = dec_val;
	}
	else if (choice == 4)
	{
		printf("Enter set element = ");
		scanf("%s", &string_val);
		strcpy(x_val.string_data, string_val);
	}
	if (choice > 0 && choice < 5)
	{
		ptr = create_node(x_val, choice);
		*set = add(set, ptr);
		display_set(set, MAX_ELEMENT);
	}
	else if (choice >= 5)
	{
		printf("Exiting!!!\n");
	}
}

void operation_8(List* set[])
{
	int choice;
	Data x_val;
	List* ptr;
	printf("\n---------------------------------------------Operation 8---------------------------------------------\n");
	printf("\n1. Boolean\n2. Integer\n3. Floating Point\n4. String\n5. Exit\n");
	printf("Enter the type of data you would like to delete = ");
	scanf("%d", &choice);
	if (choice == 1)
	{
		printf("\n0. False\n1. True\n");
		printf("Enter set element = ");
		scanf("%d", &x_val.bool_data);
		while (x_val.bool_data != 0 && x_val.bool_data != 1)
		{
			printf("\nINCORRECT BOOLEAN VALUE!!!\nTRY AGAIN!!!\n");
			printf("Enter set element = ");
			scanf("%d", &x_val.bool_data);
		}
	}
	else if (choice == 2)
	{
		printf("Enter set element = ");
		scanf("%d", &x_val.int_data);
	}
	else if (choice == 3)
	{
		printf("Enter set element = ");
		scanf("%f", &x_val.float_data);
	}
	else if (choice == 4)
	{
		printf("Enter set element = ");
		scanf("%s", &x_val.string_data);
	}
	if (choice > 0 && choice < 5)
	{
		ptr = create_node(x_val, choice);
		*set = delete(set, ptr);
		display_set(set, MAX_ELEMENT);
	}
	else if (choice >= 5)
	{
		printf("Exiting!!!\n");
	}
}

void operation_9(List* S[], List* T[])
{
	bool flag_s, flag_t;
	int i;
	List* result_set[MAX_ELEMENT];
	for (i = 0; i < MAX_ELEMENT; i++)
	{
		result_set[i] = malloc(sizeof(List));
		result_set[i] = NULL;
	}
	flag_s = is_Empty(S);
	flag_t = is_Empty(T);
	if (flag_s == TRUE && flag_t == TRUE)
	{
		printf("\nSET - 1 is a NULL SET\n");
		printf("SET - 2 is a NULL SET\n");
	}
	printf("\n------------------------------------------------UNION------------------------------------------------\n");
	if (flag_s == TRUE && flag_t == TRUE)
	{
		printf("\nNULL SET\n");
	}
	else
	{
		printf("\n");
		*result_set = set_union(S, T, result_set);
		display_set(result_set, MAX_ELEMENT);
	}
}

void operation_10(List* S[], List* T[])
{
	bool flag, flag_s, flag_t;
	int i;
	List* result_set[MAX_ELEMENT];
	for (i = 0; i < MAX_ELEMENT; i++)
	{
		result_set[i] = malloc(sizeof(List));
		result_set[i] = NULL;
	}
	printf("\n---------------------------------------------INTERSECTION--------------------------------------------\n");
	flag_s = is_Empty(S);
	flag_t = is_Empty(T);
	if (flag_s == TRUE && flag_t == TRUE)
	{
		printf("\nNULL SET\n");
	}
	else
	{
		*result_set = intersection(S, T, result_set);
		flag = is_Empty(result_set);
		if (flag == TRUE)
		{
			printf("\nNULL SET\n");
		}
		else
		{
			printf("\n");
			display_set(result_set, MAX_ELEMENT);
		}
	}
}

void operation_11(List* S[], List* T[])
{
	bool flag_s, flag_t;
	int i;
	List* result_set[MAX_ELEMENT], * result[MAX_ELEMENT];
	for (i = 0; i < MAX_ELEMENT; i++)
	{
		result_set[i] = malloc(sizeof(List));
		result_set[i] = NULL;
		result[i] = malloc(sizeof(List));
		result[i] = NULL;
	}
	printf("\n----------------------------------------------DIFFERENCE---------------------------------------------\n");
	flag_s = is_Empty(S);
	flag_t = is_Empty(T);
	if (flag_s == TRUE && flag_t == TRUE)
	{
		printf("\nNULL SET\n");
	}
	else
	{
		printf("\n");
		*result_set = intersection(S, T, result_set);
		*result = set_difference(S, result_set, result);
		display_set(result, MAX_ELEMENT);
	}
}

void operation_12(List* S[], List* T[])
{
	bool flag, flag_t, flag_s;
	int i;
	List* result_set[MAX_ELEMENT];
	for (i = 0; i < MAX_ELEMENT; i++)
	{
		result_set[i] = malloc(sizeof(List));
		result_set[i] = NULL;
	}
	printf("\n------------------------------------------------SUBSET-----------------------------------------------\n");
	flag_s = is_Empty(S);
	flag_t = is_Empty(T);
	if (flag_s == TRUE && flag_t == TRUE)
	{
		printf("\nSet 1 is a subset of Set 2\n");
	}
	else
	{
		*result_set = intersection(S, T, result_set);
		display_set(result_set, MAX_ELEMENT);
		flag = is_subset(S, result_set);	//When we do intersection first and then do subset opertion we get what we require.
		if (flag == TRUE)
		{
			printf("\nSet 1 is a subset of Set 2\n");
		}
		else
		{
			printf("\nSet 1 is not a subset of Set 2\n");
		}
	}
	printf("\n-----------------------------------------------THE END-----------------------------------------------\n");
}

int main()
{
	int i;
	List* set[MAX_ELEMENT];
	printf("Enter Set 1 :\n");
	for (i = 0; i < MAX_ELEMENT; i++)
	{
		set[i] = malloc(sizeof(List));
		set[i] = NULL;
	}
	*set = input(set);
	display_set(set, MAX_ELEMENT);

	operation_1(set);
	operation_2(set);
	operation_3(set);
	operation_4(set);
	operation_5(set);
	operation_6();
	operation_7(set);
	operation_8(set);

	printf("\nEnter Set 2 :\n");
	List* t_set[MAX_ELEMENT];
	for (i = 0; i < MAX_ELEMENT; i++)
	{
		t_set[i] = malloc(sizeof(List));
		t_set[i] = NULL;
	}
	*t_set = input(t_set);
	display_set(t_set, MAX_ELEMENT);
	
	operation_9(set, t_set);
	operation_10(set, t_set);
	operation_11(set, t_set);
	operation_12(set, t_set);
	return 0;
}