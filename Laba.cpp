#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


const char file_input[] = "input.txt";
const char file_output[] = "output.txt";
enum size{MAX_LINE = 10, MAX_ITEMS = 100};

struct item_t
{
		int key;
    char type[MAX_LINE];
    char steel[MAX_LINE];
    double price;
    double angle;
    char full;						//1 - item is full, 0 - item is empty
};

int creating(struct item_t* items, int* num, int* created);
int entering(void);
int printing(struct item_t* items);
int add_line(struct item_t* items, int* num);
int deleting(struct item_t* items, int* num);
int searching(struct item_t*items);
int sorting(struct item_t* items);
int print_item(struct item_t* items);

int comp_type(const void* str1, const void* str2);
int comp_steel(const void* str1, const void* str2);
int comp_price(const void* str1, const void* str2);
int comp_angle(const void* str1, const void* str2);



int main()
{
	struct item_t* items = (struct item_t*) calloc (MAX_ITEMS, sizeof(struct item_t));
	assert(items);
	int answ = 0;
	int num = 0;			//Current number of items in base
	printf("Добро пожаловать в базу данных \"Режущие инструменты\"!\n");
	int created = 0;
	while(1)
	{
		entering();
		scanf("%d", &answ);
		switch(answ)
		{
			case 1:
			{
				creating(items, &num, &created);
				break;
			}
			case 2:
			{
				printing(items);
				break;
			}
			case 3:
			{
				add_line(items, &num);
				break;
			}
			case 4:
			{
				deleting(items, &num);
				break;
			}
			case 5:
			{
				searching(items);
				break;
			}
			case 6:
			{
				sorting(items);
				break;
			}
			
			case 7:
			{
				printf("Спасибо за использование базы данных!\n");
				exit(0);
			}
			default:
			{
				printf("Введен некорректный вариант ответа\n");
				break;
			}
		}

	printf("Количество записей в базе на данный момент = %d, свободных мест = %d\n", num, MAX_ITEMS - num);	
	}
	free(items);
	return 0;
}

int print_item(struct item_t* items)
{
	assert(items);
	printf("%3d|", items->key);
	printf("%10s|", items->type);
	printf("%10s|", items->steel);
	printf("%10lg|", items->price);
	printf("%10lg|", items->angle);
	printf("\n");
	printf("______________________________________________\n");
	printf("\n");
	return 0;
}

int entering(void)
{
	printf("\n");
	printf("\n");
	printf("*****************************************\n");
	printf("Для создания базы данных введите 1 \n");
	printf("Для печати базы данных введите 2 \n");
	printf("Для добавления новых строк введите 3 \n");
	printf("Для удаления строк введите 4\n");
	printf("Для поиска по базе  введите 5\n");
	printf("Для сортировки введите 6\n");
	printf("Для выхода нажмите 7\n");
	printf("*****************************************\n");
	printf("\n");
	printf("\n");
	return 0;
}

int creating(struct item_t* items, int* num, int* created)
{
	assert(items && num && created);
	if(*created)
	{
		printf("Таблица уже создана\n");
		return 0;
	}
	int answ = 0;
	int N = 0;
	int i = 0;
	printf("Введите количество записей, которые вы хотите внести\n");
	scanf("%d", &N);
	if (N > MAX_ITEMS - *num)
	{
		printf("Такое количество записей не вместится в базу данных\n");
		return 0;
	}
	printf("Нажмите 1, чтобы ввести из файла, нажимте 2, чтобы ввести с клавиатуры\n");
	scanf("%d", &answ);
	switch(answ)
	{
		case 1:
		{
			FILE *f = fopen(file_input, "r");
			printf("Ввод из файла производится в порядке: тип, марка стали, цена, угол заточки\n");

			for (i = 0; i < N; ++i)
			{
				items[i].key = *num + 1;
				fscanf(f, "%s", items[i].type);
				fscanf(f, "%s", items[i].steel);
				fscanf(f, "%lg", &items[i].price);
				if (items[i].price < 0) 
				{
					printf("Введены некорректные данные в записи %d\n", items[i].key);
					return 0;
				}
				fscanf(f, "%lg", &items[i].angle);
				if ((items[i].angle < 0) || (items[i].angle > 90)) 
				{
					printf("Введены некорректные данные в записи %d\n", items[i].key);
					return 0;
				}
				items[i].full = 1;
				(*num)++;
			}
			fclose(f);
			break;
		}
		case 2:
		{
			printf("Введите данные в порядке: тип, марка стали, цена, угол заточки\n");

			for (i = 0; i < N; ++i)
			{
				printf("Введите очередные данные\n");
				items[i].key = *num + 1;
				scanf("%s", items[i].type);
				scanf("%s", items[i].steel);
				scanf("%lg", &items[i].price);
				if (items[i].price < 0) 
				{
					printf("Введены некорректные данные в записи %d\n", items[i].key);
					return 0;
				}
				scanf("%lg", &items[i].angle);
				if ((items[i].angle < 0) || (items[i].angle > 90)) 
				{
					printf("Введены некорректные данные в записи %d\n", items[i].key);
					return 0;
				}
				items[i].full = 1;
				(*num)++;
			}
			break;
		}
		default:
		{
			printf("Введен некорректный вариант ответа\n");
			return 0;
		}
	
	}
	*created = 1;
	return 0;
}

int printing(struct item_t* items)
{
	assert(items);
	int answ = 0;
	int i = 0;
	printf("Нажмите 1, чтобы вывести в файл, нажимте 2, чтобы ввести на экран\n");
	scanf("%d", &answ);
	switch(answ)
	{
		case 1:
		{
			FILE *f = fopen(file_output, "w");
			fprintf(f, "База данных\n");
			fprintf(f," № |   Type   |   Steel  |   Price  |   Angle  |\n");
			fprintf(f, "______________________________________________\n");

			for (i = 0; i < MAX_ITEMS; ++i)
			{
				if (items[i].full == 1)
				{
					fprintf(f, "%3d|", items[i].key);
					fprintf(f, "%10s|", items[i].type);
					fprintf(f, "%10s|", items[i].steel);
					fprintf(f, "%10lg|", items[i].price);
					fprintf(f, "%10lg|", items[i].angle);
					fprintf(f, "\n");
					fprintf(f, "______________________________________________\n");
					fprintf(f, "\n");
				}
			}
			fclose(f);
			break;
		}
		case 2:
		{
			printf("База данных\n");
			printf(" № |   Type   |   Steel  |   Price  |   Angle  |\n");
			printf("______________________________________________\n");

			for (i = 0; i < MAX_ITEMS; ++i)
			{
				if (items[i].full == 1)
				{
					print_item(items + i);
				}
			}
			break;
		}
		default:
		{
			printf("Введен некорректный вариант ответа\n");
			return 0;
		}
	}
	return 0;
}


int add_line(struct item_t* items, int* num)
{
	assert(items && num);
	int i = 0;
	int j = 0;
	while(items[i].full == 1)
		i++;
	printf("Введите данные в порядке: тип, марка стали, цена, угол заточки\n");
	items[i].key = i + 1;
	scanf("%s", items[i].type);
	scanf("%s", items[i].steel);
	scanf("%lg", &items[i].price);
	if (items[i].price < 0) 
	{
		printf("Введены некорректные данные в записи %d\n", items[i].key);
		return 0;
	}
	scanf("%lg", &items[i].angle);
	if ((items[i].angle < 0) || (items[i].angle > 90)) 
	{
		printf("Введены некорректные данные в записи %d\n", items[i].key);
		return 0;
	}
	items[i].full = 1;
	(*num)++;
	for (j = i + 1; j < MAX_ITEMS; ++j)
		if(items[i].full == 1)
			(items[j].key)++;
	return 0;
}

int deleting(struct item_t* items, int* num)
{
	assert(items && num);
	int answ = 0;
	char ref_line[MAX_LINE];
	int ref_answ;
	int ref = 0;
	double ref_doub = 0.0;
	int i =0;
	int j = 0;
	printf("Нажмите 1, чтобы удалить по номеру, нажимте 2, чтобы удалить по определенному полю\n");
	scanf("%d", &answ);
	switch(answ)
	{
		case 1:
		{
			printf("Введите ключ, по которому вы хотите удалить\n");
			scanf("%d", &ref);
			if (ref < 0) 
			{
				printf("Введен некорректный ключ\n");
				return 0;
			}
			for (i = 0; i < MAX_ITEMS; ++i)
			{
				if ((items[i].key == ref) && (items[i].full == 1))
				{
					(*num)--;
					items[i].full = 0;
					for (j = i; j < MAX_ITEMS; ++j)
						(items[j].key)--;
					break;
				}
			}
			break;
		}
		case 2:
		{
			printf("Нажмите 1, чтобы удалить по типу, нажимте 2, чтобы удалить по марке стали\n");
			printf("Нажмите 3, чтобы удалить по цене, нажимте 4, чтобы удалить по углу заточки\n");
			scanf("%d", &ref_answ);
			switch(ref_answ)
			{
				case 1:
				{
					printf("Введите значение, по которому вы хотите удалить\n");
					scanf("%s", ref_line);
					for (i = 0; i < MAX_ITEMS; ++i)
					{
						if ((!strcmp(items[i].type, ref_line)) && (items[i].full == 1))
						{
							(*num)--;
							items[i].full = 0;
							for (j = i; j < MAX_ITEMS; ++j)
								(items[j].key)--;
						}
					}
					break;
				}

				case 2:
				{
					printf("Введите значение, по которому вы хотите удалить\n");
					scanf("%s", ref_line);
					for (i = 0; i < MAX_ITEMS; ++i)
					{
						if ((!strcmp(items[i].steel, ref_line)) && (items[i].full == 1))
						{
							(*num)--;
							items[i].full = 0;
							for (j = i; j < MAX_ITEMS; ++j)
								(items[j].key)--;
						}
					}
					break;
				}

				case 3:
				{
					printf("Введите значение, по которому вы хотите удалить\n");
					scanf("%lg", &ref_doub);
					for (i = 0; i < MAX_ITEMS; ++i)
					{
						if ((items[i].price	== ref_doub) && (items[i].full == 1))
						{
							items[i].full = 0;
							(*num)--;
							for (j = i; j < MAX_ITEMS; ++j)
								(items[j].key)--;
						}
					}
					break;
				}
				case 4:
				{
					printf("Введите значение, по которому вы хотите удалить\n");
					scanf("%lg", &ref_doub);
					for (i = 0; i < MAX_ITEMS; ++i)
					{
						if ((items[i].angle	== ref_doub) && (items[i].full == 1))
						{
							items[i].full = 0;
							(*num)--;
							for (j = i; j < MAX_ITEMS; ++j)
								(items[j].key)--;
						}
					}
					break;
				}
				default:
				{
					printf("Введен некорректный вариант ответа\n");
					return 0;
				}
			}
		break;
		}
		default:
		{
			printf("Введен некорректный вариант ответа\n");
			return 0;
		}
	}
	return 0;
}


int searching(struct item_t* items)
{
	assert(items);
	int ref_answ = 0;
	char ref_line[MAX_LINE];
	double ref_doub = 0.0;
	int i = 0;
	printf("Нажмите 1, чтобы искать по типу, нажимте 2, чтобы искать по марке стали\n");
	printf("Нажмите 3, чтобы искать по цене, нажимте 4, чтобы искать по углу заточки\n");
	scanf("%d", &ref_answ);
	printf("\n");
	switch(ref_answ)
			{
				case 1:
				{
					printf("Введите значение, по которому вы хотите искать\n");
					scanf("%s", ref_line);
					printf("Результаты поиска:\n");
					printf(" № |   Type   |   Steel  |   Price  |   Angle  |\n");
					printf("______________________________________________\n");
					for (i = 0; i < MAX_ITEMS; ++i)
					{
						if ((!strcmp(items[i].type, ref_line)) && (items[i].full == 1))
						{
							print_item(items + i);
						}
					}
					break;
				}

				case 2:
				{
					printf("Введите значение, по которому вы хотите искать\n");
					printf("Результаты поиска:\n");
					printf(" № |   Type   |   Steel  |   Price  |   Angle  |\n");
					printf("______________________________________________\n");
					scanf("%s", ref_line);
					for (i = 0; i < MAX_ITEMS; ++i)
					{
						if ((!strcmp(items[i].steel, ref_line)) && (items[i].full == 1))
						{
 							print_item(items + i);
						}
					}
					break;
				}

				case 3:
				{
					printf("Введите значение, по которому вы хотите искать\n");
					printf("Результаты поиска:\n");
					printf(" № |   Type   |   Steel  |   Price  |   Angle  |\n");
					printf("______________________________________________\n");
					scanf("%lg", &ref_doub);
					for (i = 0; i < MAX_ITEMS; ++i)
					{
						if ((items[i].price	== ref_doub) && (items[i].full == 1))
						{
							print_item(items + i);
						}
					}
					break;
				}
				case 4:
				{
					printf("Введите значение, по которому вы хотите искать\n");
					printf("Результаты поиска:\n");
					printf(" № |   Type   |   Steel  |   Price  |   Angle  |\n");
					printf("______________________________________________\n");
					scanf("%lg", &ref_doub);
					for (i = 0; i < MAX_ITEMS; ++i)
					{
						if ((items[i].angle	== ref_doub) && (items[i].full == 1))
						{
							print_item(items + i);
						}
					}
					break;
				}
				default:
				{
					printf("Введен некорректный вариант ответа\n");
					return 0;
				}
			}

	return 0;
}

int sorting(struct item_t* items)
{
	assert(items);
	int ref_answ = 0;
	printf("Нажмите 1, чтобы сортировать по типу, нажимте 2, чтобы сортировать по марке стали\n");
	printf("Нажмите 3, чтобы сортировать по цене, нажимте 4, чтобы сортировать по углу заточки\n");
	scanf("%d", &ref_answ);
	printf("\n");
	int i = 0;
	int k = 1;
	switch(ref_answ)
			{
				case 1:
				{
					qsort(items, MAX_ITEMS, sizeof(struct item_t), comp_type);
					for (i = 0; i < MAX_ITEMS; ++i)
					{
						if (items[i].full == 1)
						{
							items[i].key = k;
							k++;
						}

					}
					break;
				}

				case 2:
				{
					qsort(items, MAX_ITEMS, sizeof(struct item_t), comp_steel);
					for (i = 0; i < MAX_ITEMS; ++i)
					{
						if (items[i].full == 1)
						{
							items[i].key = k;
							k++;
						}
					}

					break;
				}

				case 3:
				{
					qsort(items, MAX_ITEMS, sizeof(struct item_t), comp_price);
					for (i = 0; i < MAX_ITEMS; ++i)
					{
						if (items[i].full == 1)
						{
							items[i].key = k;
							k++;
						}
					}
					break;
				}
				case 4:
				{
					qsort(items, MAX_ITEMS, sizeof(struct item_t), comp_angle);
					for (i = 0; i < MAX_ITEMS; ++i)
					{
						if (items[i].full == 1)
						{
							items[i].key = k;
							k++;
						}
					}
					break;
				}
				default:
				{
					printf("Введен некорректный вариант ответа\n");
					return 0;
				}
			}
	return 0;
}

int comp_type(const void* str1, const void* str2)
{
	struct item_t* item1 =  (struct item_t*) str1;
	struct item_t* item2 =  (struct item_t*) str2;
	return (strcmp(item1 -> type, item2 -> type));
}

int comp_steel(const void* str1, const void* str2)
{
	struct item_t* item1 =  (struct item_t*) str1;
	struct item_t* item2 =  (struct item_t*) str2;
	return (strcmp(item1 -> steel, item2 -> steel));
}

int comp_price(const void* str1, const void* str2)
{
	struct item_t* item1 =  (struct item_t*) str1;
	struct item_t* item2 =  (struct item_t*) str2;
	return (item1 -> price > item2 -> price);
}

int comp_angle(const void* str1, const void* str2)
{
	struct item_t* item1 =  (struct item_t*) str1;
	struct item_t* item2 =  (struct item_t*) str2;
	return (item1 -> angle > item2 -> angle);
}