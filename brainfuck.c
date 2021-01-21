#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Not enough arguments\n");
		return -1;
	}
	else if (argc > 3)
	{
		printf("Too many arguments\n");
		return -1;
	}
	int* tape = calloc(30000, sizeof(int));

	for(int i = 0; i < 30000; ++i)
	{
		tape[i] = 0;
	}

	unsigned int tapePos = 0;
	FILE* file = fopen(argv[1], "r");
	if (file == NULL)
	{
		printf("Unable to open file \n");
		free(tape);
		return -1;
	}
	FILE* filebf = NULL;
	static int fopenCount = 0;

	fseek(file, 0, SEEK_SET);
	while(1)
	{
		static int functionCount = 0;
		static int argPos = -1;
		static long int currentPos = 0;
		static long int functionPos = 0;
		static long int conditionalPos = -1;
		static unsigned char c = 0;
		if (feof(file))
		{
			printf("\n");
			break;
		}
		c = fgetc(file);

		if(c == '<')
		{
			if(tapePos <= 0)
			{
				perror("Cannot Access Array Index Smaller Than 0 \n");
				if (filebf != NULL) { fclose(filebf); }
				fclose(file);
				free(tape);
				return -1;
			}
			else
			{
				//printf("Moving tape pointer to the left\n");
				tapePos = tapePos - 1;
			}

		}
		else if (c == '>')
		{
			if (tapePos >= 29999)
			{
				perror("Cannot Access Array Index Greater Than 29999 \n");
				if (filebf != NULL) { fclose(filebf); }
				fclose(file);
				free(tape);
				return -1;
			}
			else
			{
				//printf("Moving tape pointer to the right\n");
				tapePos += 1;
			}
		}
		else if (c == '+')
		{
			//printf("Incrementing Value of cell\n");
			tape[tapePos]++;
		}
		else if (c == '-')
		{
			//printf("-1 Value of cell\n");
			tape[tapePos]--;
		}
		else if (c == '.')
		{
		//printf("Printing out cell ASCII value\n");
			printf("%c", tape[tapePos]);
		}
		else if (c == ',')
		{
			//printf("Inputing cell an ASCII value\n");
			scanf("%c", tape[tapePos]);
		}
		else if (c == ':')
		{
			//printf("Printing out cell value\n");
			printf("%i", tape[tapePos]);
		}
		else if (c == ';')
		{
			//printf("Inputting cell value\n");
			scanf("%i", tape[tapePos]);
		}
		else if (c == '%' && fopenCount / 2 == 0)
		{
			filebf = fopen(argv[2], "r+");
			if (filebf == NULL)
			{
				printf("Unable to Open File \n");
				fclose(file);
				free(tape);
				return -1;
			}
			else
			{
				//printf("Opened file\n");
				fopenCount++;
			}
		}
		else if (c == '%' && fopenCount / 2 != 0)
		{
			if (fclose(filebf) == EOF)
			{
				printf("Unable to close file\n");
				fclose(file);
				free(tape);
				return -1;
			}
			else
			{
				fopenCount++;
				//printf("Closing file\n");
			}
		}
		else if (c == '^')
		{
			if (fputc(tape[tapePos], filebf) == NULL)
			{
				printf("Unable to write to file\n");
				if (filebf != NULL) { fclose(filebf); }
				fclose(file);
				free(tape);
				return -1;
			}
			else
			{
				//printf("Cell value written to file\n");
			}
		}
		else if (c == 'v')
		{
			if (filebf != NULL) { tape[tapePos] = fgetc(filebf); }
			if (tape[tapePos] == NULL)
			{
				printf("Unable to read from file\n");
				if (filebf != NULL) { fclose(filebf); }
				fclose(file);
				free(tape);
				return -1;
			}
			else
			{
				//printf("Getting value from file\n");
			}
		}
		else if (c == '[')
		{
			if (tape[tapePos] == 0)
			{
				while (c != ']')
				{
					if (feof(file))
					{
						printf("Unable to find expected ']'\n");
						if (filebf != NULL) { fclose(filebf); }
						fclose(file);
						free(tape);
						return -1;
					}
					//printf("Ending loop because cell == 0\n");
					c = fgetc(file);
				}
			}
			else if (tape[tapePos] != 0)
			{
				//printf("Loop begins hopefully\n");
				conditionalPos = ftell(file);
			}
		}
		else if (c == ']')
		{
			if (tape[tapePos] == 0)
			{
				//printf("Loop Ends\n");
				conditionalPos = -1;
			}
			else
			{
				if (conditionalPos != -1)
				{
					//printf("Jumped back to loop beginning\n");
					fseek(file, conditionalPos, SEEK_SET);
				}
			}
		}
		else if (c == '(')
		{
			if (tape[tapePos] == 0)
			{
				while (c != ')')
				{
					if (feof(file))
					{
						printf("Unable to find expected ')'\n");
						if (filebf != NULL) { fclose(filebf); }
						fclose(file);
						free(tape);
						return -1;
					}
					c = fgetc(file);
				}
			}
			else
			{}
		}
		else if (c == ')')
		{
			if (tape[tapePos] == 0)
			{}
			else
			{}
		}
		else if (c == 'f' && functionCount % 2 == 0)
		{
			c = fgetc(file);
			if (c == 'a')
			{
				argPos = tapePos;
				c = fgetc(file);
				if (c == '{')
				{
					functionPos = ftell(file);
					functionCount += 1;
					while (c != '}')
					{
						if (feof(file))
						{
							printf("Unable to find expected '}'\n");
							if (filebf != NULL) { fclose(filebf); }
							fclose(file);
							free(tape);
							return -1;
						}
						//printf("Ending loop because cell == 0\n");
						c = fgetc(file);
					}
				}
			}
			else if (c == '{')
			{
				functionPos = ftell(file);
				functionCount += 1;
				while (c != '}')
				{
					if (feof(file))
					{
						printf("Unable to find expected '}'\n");
						if (filebf != NULL) { fclose(filebf); }
						fclose(file);
						free(tape);
						return -1;
					}
					//printf("Ending loop because cell == 0\n");
					c = fgetc(file);
				}
			}
			else
			{
				printf("Invalid syntax!\n");
				if (filebf != NULL) { fclose(filebf); }
				fclose(file);
				free(tape);
				return -1;
			}
		}
		else if (c == 'f' && functionCount % 2 != 0)
		{
			currentPos = ftell(file);
			fseek(file, functionPos, SEEK_SET);
			functionCount += 1;


		}
		else if (c == '}' && functionCount % 2 == 0)
		{
			if (currentPos != NULL)
			{
				fseek(file, currentPos, SEEK_SET);
				argPos = NULL;
				functionPos = NULL;
				currentPos = NULL;
			}
		}
		else if (c == '<' && functionCount % 2 != 0)
		{
			if(argPos <= 0)
			{
				perror("Cannot Access Array Index Smaller Than 0 \n");
				if (filebf != NULL) { fclose(filebf); }
				fclose(file);
				free(tape);
				return -1;
			}
			else
			{
				//printf("Moving tape pointer to the left\n");
				argPos = argPos - 1;
			}

		}
		else if (c == '>' && functionCount % 2 != 0)
		{
			if (argPos >= 29999)
			{
				perror("Cannot Access Array Index Greater Than 29999 \n");
				if (filebf != NULL) { fclose(filebf); }
				fclose(file);
				free(tape);
				return -1;
			}
			else
			{
				//printf("Moving tape pointer to the right\n");
				argPos += 1;
			}
		}
		else if (c == '+' && functionCount % 2 != 0)
		{
			//printf("Incrementing Value of cell\n");
			tape[argPos]++;
		}
		else if (c == '-' && functionCount % 2 != 0)
		{
			//printf("-1 Value of cell\n");
			tape[argPos]--;
		}
		else if (c == '.' && functionCount % 2 != 0)
		{
		//printf("Printing out cell ASCII value\n");
			printf("%c", tape[argPos]);
		}
		else if (c == ',' && functionCount % 2 != 0)
		{
			//printf("Inputing cell an ASCII value\n");
			scanf("%c", tape[argPos]);
		}
		else if (c == ':' && functionCount % 2 != 0)
		{
			//printf("Printing out cell value\n");
			printf("%i", tape[argPos]);
		}
		else if (c == ';' && functionCount % 2 != 0)
		{
			//printf("Inputting cell value\n");
			scanf("%i", tape[argPos]);
		}
		else if (c == '%' && fopenCount / 2 == 0 && functionCount % 2 != 0)
		{
			filebf = fopen(argv[2], "r+");
			if (filebf == NULL)
			{
				printf("Unable to Open File \n");
				fclose(file);
				free(tape);
				return -1;
			}
			else
			{
				//printf("Opened file\n");
				fopenCount++;
			}
		}
		else if (c == '%' && fopenCount / 2 != 0 && functionCount % 2 != 0)
		{
			if (fclose(filebf) == EOF)
			{
				printf("Unable to close file\n");
				fclose(file);
				free(tape);
				return -1;
			}
			else
			{
				fopenCount++;
				//printf("Closing file\n");
			}
		}
		else if (c == '^' && functionCount % 2 != 0)
		{
			if (fputc(tape[argPos], filebf) == NULL)
			{
				printf("Unable to write to file\n");
				if (filebf != NULL) { fclose(filebf); }
				fclose(file);
				free(tape);
				return -1;
			}
			else
			{
				//printf("Cell value written to file\n");
			}
		}
		else if (c == 'v' && functionCount % 2 != 0)
		{
			if (filebf != NULL) { tape[tapePos] = fgetc(filebf); }
			if (tape[tapePos] == NULL)
			{
				printf("Unable to read from file\n");
				if (filebf != NULL) { fclose(filebf); }
				fclose(file);
				free(tape);
				return -1;
			}
			else
			{
				//printf("Getting value from file\n");
			}
		}
		else if (c == '[' && functionCount % 2 != 0)
		{
			if (tape[argPos] == 0)
			{
				while (c != ']')
				{
					if (feof(file))
					{
						printf("Unable to find expected ']'\n");
						if (filebf != NULL) { fclose(filebf); }
						fclose(file);
						free(tape);
						return -1;
					}
					//printf("Ending loop because cell == 0\n");
					c = fgetc(file);
				}
			}
			else if (tape[argPos] != 0)
			{
				//printf("Loop begins hopefully\n");
				conditionalPos = ftell(file);
			}
		}
		else if (c == ']' && functionCount % 2 != 0)
		{
			if (tape[argPos] == 0)
			{
				//printf("Loop Ends\n");
				conditionalPos = -1;
			}
			else
			{
				if (conditionalPos != -1)
				{
					//printf("Jumped back to loop beginning\n");
					fseek(file, conditionalPos, SEEK_SET);
				}
			}
		}
		else if (c == '(' && functionCount % 2 != 0)
		{
			if (tape[argPos] == 0)
			{
				while (c != ')')
				{
					if (feof(file))
					{
						printf("Unable to find expected ')'\n");
						if (filebf != NULL) { fclose(filebf); }
						fclose(file);
						free(tape);
						return -1;
					}
					c = fgetc(file);
				}
			}
			else
			{}
		}
		else if (c == ')' && functionCount % 2 != 0)
		{
			if (tape[argPos] == 0)
			{}
			else
			{}
		}
	}

	fclose(file);
	if (filebf != NULL && fopenCount != 2) { fclose(filebf); }
	free(tape);
	return 0;
}
