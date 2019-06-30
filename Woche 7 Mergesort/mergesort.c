#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#pragma warning(disable : 4996)

void mergesort(long *, int, int);
long long GetUSecClock();

int main(int argc, char *argv[])
{
	FILE *in = stdin;										//File auf Tastatureingabe setzen
	long zahlenArr[100000] = { 0 };							//Array, in dem Zahlen abgespeichert werden
	int arrPos = 0;											//aktuelle Position im Array
	char temp[80];											//Zwischenspeicher

	clock_t start, ende;
	float dauer;
	long long time1, time2;

	if (argc == 2)
	{
		//wenn Datei an Hauptprogramm �bergeben
		in = fopen(argv[1], "r");
		if (!in)
		{
			exit(EXIT_FAILURE);
		}
	}

	//Einlesen der Zahlen in das Array
	while (!feof(in))
	{
		fgets(temp, 80, in);
		long zahl = atol(temp);
		zahlenArr[arrPos++] = zahl;
	}

	fclose(in);

	//Ausgabe des unsortierten Arrays (die ersten 10 Zahlen)
	printf("Die Groesse des Arrays ist: %i\n", arrPos);
	printf("Ausgabe des unsortierten Arrays\n");
	printf("-----------------------------------------------------\n");
	for (int i = 0; i < 10; i++)
	{
		printf("%i\n", zahlenArr[i]);
	}

	//mergesort aufrufen
	start = clock();
	time1 = GetUSecClock();
	mergesort(zahlenArr, 0, arrPos);
	time2 = GetUSecClock();
	ende = clock();
	dauer = (ende - start) / CLOCKS_PER_SEC;

	//Ausgabe des sortieren Arrays (die ersten 10 Zahlen)
	printf("\n\nAusgabe des sortieren Arrays\n");
	printf("-----------------------------------------------------\n");
	for (int i = 0; i < 10; i++)
	{
		printf("%i\n", zahlenArr[i]);
	}

	printf("Die benoetigte Zeit zum Sortieren: %f Sekunden\n", dauer);
	printf("Die benoetigte Zeit zum Sortieren: %llu Mikrosekunden\n", time1-time2);
	system("Pause");
	exit(EXIT_SUCCESS);
}

void mergesort(long *zahlenArr, int start, int anzahl)
{
	static long mergeArr[100000];

	if (anzahl > 1)
	{
		int a1 = 0;
		int a2 = 0;

		mergesort(zahlenArr, start, anzahl/2);
		mergesort(zahlenArr, start + anzahl/2, anzahl - anzahl/2);

		a1 = start;
		a2 = start + anzahl / 2;

		for (int i = start; i < start + anzahl; i++)
		{
			if (a1 >= start + anzahl / 2)
			{
				mergeArr[i] = zahlenArr[a2];
				a2++;
			}
			else if (a2 >= start + anzahl)
			{
				mergeArr[i] = zahlenArr[a1];
				a1++;
			}
			else if (zahlenArr[a1] <= zahlenArr[a2])
			{
				mergeArr[i] = zahlenArr[a1];
				a1++;
			}
			else
			{
				mergeArr[i] = zahlenArr[a2];
				a2++;
			}
		}

		for (int i = start; i < start + anzahl; i++)
		{
			zahlenArr[i] = mergeArr[i];
		}
	}
}

long long GetUSecClock()
{
	clock_t cpu_time = clock();
	return (long long)cpu_time*CLOCKS_PER_SEC;
}