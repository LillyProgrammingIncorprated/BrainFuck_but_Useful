#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Not enough arguments \n");
		return -1;
	}
	int* tape = calloc(30000, sizeof(int));
	unsigned int tapePos = 0;
	FILE* file = fopen(argv[1], "r+");
	if (file == NULL)
	{
		printf("Unable to open file \n");
		free(tape);
		return -1;
	}

	while(1)
	{
		static int fopenCount = 0;
		static unsigned char c = 0;
		if(feof(file))
		{
			break;
		}
		c = fgetc(file);

		if(c == '<')
		{
			if(tapePos <= 0)
			{
				perror("Cannot Access Array Index Smaller Than 0 \n");
				return -1;
			}
			else
			{
				tapePos = tapePos - 1;
			}
			
		}
		else if (c == '>')
		{
			if (tapePos >= 29999)
			{
				perror("Cannot Access Array Index Greater Than 29999 \n");
				return -1;
			}
			else
			{
				tapePos += 1;
			}
		}
		else if (c == '+')
		{
			tape[tapePos]++;
		}
		else if (c == '-')
		{
			tape[tapePos]--;
		}
		else if (c == '.')
		{
			printf("%c", tape[tapePos]);
		}
		else if (c == ',')
		{
			scanf("%c", tape[tapePos]);
		}
		else if (c == ':')
		{
			printf("%i", tape[tapePos]);
		}
		else if (c == ';')
		{
			scanf("%i", tape[tapePos]);
		}
		else if (c == '%' && fopenCount == 0)
		{
		
			if (filebf == NULL)
			{
				printf("Unable to Open Fıle \n");
				fclose(file);
				free(tape);
				return -1;
			}
			else 
			{
				fopenCount++;
			}
		}
		else if (c == "%" && fopenCount == 1)
		{
			if (fclose(filebf) == NULL)
			{
				printf("Unable to close file\n");
				fclose(file);
				free(tape);
				return -1;
			}
		}
		else if (c == '^')
		{
			if (fputc(tape[tapePos], filebf) == NULL)
			{
				printf("Unable to write to file\n");
				fclose(filebf);
				fclose(file);
				free(tape);
				return -1;
			}
		}
		else if (c == 'v')
		{
			tape[tapePos] = fgetc(filebf);
			if (tape[tapePos] == NULL)
			{
				printf("Unable to read from file\n");
				fclose(filebf);
				fclose(file);
				free(tape);
				return -1;
			}//lol
		}

	}
	fclose(file);
	free(tape);
	return 0;
}
