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
	unsigned int tapePos = 0;
	FILE* filebf = NULL;
	FILE* file = fopen(argv[1], "r+");
	if (file == NULL)
	{
		printf("Unable to open file \n");
		free(tape);
		return -1;
	}

	fseek(file, 0, SEEK_SET);
	while(1)
	{
		static long int currentFPos = -1;
		static int fopenCount = 0;
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
		else if (c == '%' && fopenCount == 0)
		{
			filebf = fopen(argv[2], "r+");
			if (filebf == NULL)
			{
				printf("Unable to Open Fıle \n");
				if (filebf != NULL) { fclose(filebf); }
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
		else if (c == '%' && fopenCount == 1)
		{
			if (fclose(filebf) == NULL)
			{
				printf("Unable to close file\n");
				if (filebf != NULL) { fclose(filebf); }
				fclose(file);
				free(tape);
				return -1;
			}
			else
			{
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
			tape[tapePos] = fgetc(filebf);
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
						//printf("Unable to find expected ']'\n");
						fclose(filebf);
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
				currentFPos = ftell(file);
			}
		}
		else if (c == ']')
		{
			if (tape[tapePos] == 0)
			{
				//printf("Loop Ends\n");
				currentFPos = -1;
			}
			else
			{
				if (currentFPos != -1)
				{
					//printf("Jumped back to loop beginning\n");
					fseek(file, currentFPos, SEEK_SET);
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
	}
	fclose(file);
	if (filebf != NULL) { fclose(filebf); }
	free(tape);
	return 0;
}
