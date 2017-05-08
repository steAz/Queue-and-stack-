// projektFifoFilo.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stdio.h>

using namespace std;



struct Lifo
{
	char** tab;
	int top;
};


void push(Lifo* lifo, char* tekst)
{
	lifo->top += 1;

	lifo->tab[lifo->top] = new char[strlen(tekst)];
	lifo->tab[lifo->top] = tekst;
}


bool czyStosPusty(Lifo* lifo)
{
	if (lifo->top <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void pop(Lifo* lifo)
{
	if (czyStosPusty(lifo) == true)
	{

	}
	else
	{
		lifo->tab[lifo->top] = NULL;
		delete[] lifo->tab[lifo->top];

		lifo->top -= 1;
	}
}



struct Fifo 
{
	char** tab;
	int head;
	int tail;
};


void enQueue(Fifo* fifo, char* tekst) 
{
	fifo->tab[fifo->tail] = new char[strlen(tekst)];
	fifo->tab[fifo->tail] = tekst;

	fifo->tail += 1;
}


void deQueue(Fifo* fifo) {
	if (fifo->head == fifo->tail) // jesli glowa rowna sie ogonowi, to znaczy, ze kolejka pusta. Razem wynosza po 1 na starcie
	{

	}
	else
	{
		fifo->head += 1;

		fifo->tab[fifo->head - 1] = NULL;
		delete[] fifo->tab[fifo->head - 1];
	}
}

// NIZEJ DODAWANIE/POWIELANIE/PRZENOSZENIE  ->> ZAWSZE W PARAMETRACH PO LEWEJ ZRODLO, PO PRAWEJ DOCELOWA

void powielaj(Lifo* lifo, Fifo* fifo) 
{
	if (czyStosPusty(lifo)) // jesli stos pusty, to nic nie rob
	{

	}
	else
	{
		fifo->tab[fifo->tail] = NULL;
		fifo->tab[fifo->tail] = lifo->tab[lifo->top];

		fifo->tail += 1;
	}
}


void powielaj(Fifo* fifo, Lifo* lifo) 
{
	if (fifo->head == fifo->tail) // jesli kolejka pustka, to nic nie rob
	{

	}
	else
	{
		lifo->top += 1;

		lifo->tab[lifo->top] = NULL;
		lifo->tab[lifo->top] = fifo->tab[fifo->head];
	}
}


void powielaj(Fifo* fifo)
{
	if (fifo->head == fifo->tail) // jesli kolejka pustka, to nic nie rob
	{

	}
	else
	{
		fifo->tab[fifo->tail] = NULL;
		fifo->tab[fifo->tail] = fifo->tab[fifo->head];

		fifo->tail += 1;
	}
}


void powielaj(Lifo* lifo)
{
	if (czyStosPusty(lifo)) // jesli kolejka pustka, to nic nie rob
	{

	}
	else
	{
		lifo->top += 1;

		lifo->tab[lifo->top] = NULL; // powielam stringa na indeksie fifo->top, ktory byl przed chwila pierwszy, dlatego '-1'
		lifo->tab[lifo->top] = lifo->tab[lifo->top - 1];
	}
}


void przeniesIusun(Lifo* lifo, Fifo* fifo)
{
	if (czyStosPusty(lifo))
	{

	}
	else
	{
		enQueue(fifo, lifo->tab[lifo->top]);

		lifo->tab[lifo->top] = NULL;
		delete[] lifo->tab[lifo->top];

		lifo->top -= 1;
	}
}


void przeniesIusun(Fifo* fifo, Lifo* lifo)
{
	if (fifo->head == fifo->tail)
	{

	}
	else
	{
		push(lifo, fifo->tab[fifo->head]);

		fifo->tab[fifo->head] = NULL;
		delete[] fifo->tab[fifo->head];

		fifo->head += 1;
	}
}


void przeniesIusun(Fifo* fifo)
{
	if (fifo->head == fifo->tail)
	{

	}
	else
	{
		enQueue(fifo, fifo->tab[fifo->head]);

		fifo->tab[fifo->head] = NULL;
		delete[] fifo->tab[fifo->head];

		fifo->head += 1;
	}
}


void przeniesIusun(Lifo* lifo)
{
	if (czyStosPusty(lifo))
	{

	}
	else
	{
		push(lifo, lifo->tab[lifo->top]);

		lifo->tab[lifo->top] = NULL;
		delete[] lifo->tab[lifo->top];

		lifo->top -= 1;
	}
}


void polacz(Lifo* lifo, Fifo* fifo)
{
	if ((czyStosPusty(lifo)) || (fifo->head == fifo->tail))
	{

	}
	else
	{
		fifo->tab[fifo->tail] = new char[strlen(lifo->tab[lifo->top]) + strlen(fifo->tab[fifo->head])];

		int licznik = 0;
		while (lifo->tab[lifo->top][licznik] != NULL)
		{
			fifo->tab[fifo->tail][licznik] = lifo->tab[lifo->top][licznik];
			licznik++; // licznik na koncu ostatniej petli bedzie wiekszy o 1, bo dodawanie sie wykona, dlatego w drugiej nie trzeba dawac 'licznik+1'
		}
		fifo->tab[fifo->tail][licznik] = NULL;

		int j = 0;
		int i = licznik;
		for (i = licznik; fifo->tab[fifo->head][j] != NULL; i++) // zaczynamy od 'licznik' zeby zaczac wpisywac drugi ciag od NULLA z pierwszego ciagu
		{
			fifo->tab[fifo->tail][i] = fifo->tab[fifo->head][j];
			j++;
		}
		fifo->tab[fifo->tail][i] = NULL; // ostatnie elementy ('i' sie dodalo w petli i ma wartosc o jeden wieksza niz w petli an koncu) NULLuje

		fifo->tail += 1;
	}
}


void polacz(Fifo* fifo, Lifo* lifo)
{
	if ((czyStosPusty(lifo)) || (fifo->head == fifo->tail))
	{

	}
	else
	{
		lifo->top += 1;

		lifo->tab[lifo->top] = new char[strlen(fifo->tab[fifo->head]) + strlen(lifo->tab[lifo->top - 1])];

		int licznik = 0;
		while (fifo->tab[fifo->head][licznik] != NULL)
		{
			lifo->tab[lifo->top][licznik] = fifo->tab[fifo->head][licznik];
			licznik++;
		}
		lifo->tab[lifo->top][licznik] = NULL;

		int j = 0;
		int i = licznik;
		for (i = licznik; lifo->tab[lifo->top - 1][j] != NULL; i++) // zaczynamy od 'licznik+1' zeby zaczac wpisywac drugi ciag od NULLA z pierwszego ciagu
		{
			lifo->tab[lifo->top][i] = lifo->tab[lifo->top - 1][j];
			j++;
		}
		lifo->tab[lifo->top][i] = NULL;		
	}
}


void polaczSS(Lifo* lifo, Fifo* fifo)
{
	if ((fifo->head == fifo->tail) || czyStosPusty(lifo))
	{

	}
	else
	{
		lifo->top += 1;

		lifo->tab[lifo->top] = new char[strlen(lifo->tab[lifo->top - 1]) + strlen(fifo->tab[fifo->head])];

		int licznik = 0;
		while (lifo->tab[lifo->top - 1][licznik] != NULL)
		{
			lifo->tab[lifo->top][licznik] = lifo->tab[lifo->top - 1][licznik];
			licznik++;
		}
		lifo->tab[lifo->top][licznik] = NULL;

		int j = 0;
		int i = licznik;
		for (i = licznik; fifo->tab[fifo->head][j] != NULL; i++) // zaczynamy od 'licznik+1' zeby zaczac wpisywac drugi ciag od NULLA z pierwszego ciagu
		{
			lifo->tab[lifo->top][i] = fifo->tab[fifo->head][j];
			j++;
		}
		lifo->tab[lifo->top][i] = NULL;
	}
}


void polaczKK(Fifo* fifo, Lifo* lifo)
{
	if ((fifo->head == fifo->tail) || czyStosPusty(lifo))
	{

	}
	else
	{
		fifo->tab[fifo->tail] = new char[strlen(fifo->tab[fifo->head]) + strlen(lifo->tab[lifo->top])];

		int licznik = 0;
		while (fifo->tab[fifo->head][licznik] != NULL)
		{
			fifo->tab[fifo->tail][licznik] = fifo->tab[fifo->head][licznik];
			licznik++; // licznik na koncu ostatniej petli bedzie wiekszy o 1, bo dodawanie sie wykona, dlatego w drugiej nie trzeba dawac 'licznik+1'
		}
		fifo->tab[fifo->tail][licznik] = NULL;

		int j = 0;
		int i = licznik;
		for (i = licznik; lifo->tab[lifo->top][j] != NULL; i++) // zaczynamy od 'licznik' zeby zaczac wpisywac drugi ciag od NULLA z pierwszego ciagu
		{
			fifo->tab[fifo->tail][i] = lifo->tab[lifo->top][j];
			j++;
		}
		fifo->tab[fifo->tail][i] = NULL; // ostatnie elementy ('i' sie dodalo w petli i ma wartosc o jeden wieksza niz w petli an koncu) NULLuje

		fifo->tail += 1;
	}
}


void wyswietlaj(Fifo* fifo)
{
	printf("%s", fifo->tab[fifo->head]);
	cout << endl;
}


void wyswietlaj(Lifo* lifo)
{
	printf("%s", lifo->tab[lifo->top]);
	cout << endl;
}


void ustawParametry(Lifo* lifo, Fifo* fifo)
{
	fifo->head = 1;
	fifo->tail = 1;
	lifo->top = 0;
	lifo->tab = new char*[5020];
	fifo->tab = new char*[5020];
}



int main()
{
	Lifo lifo;
	Fifo fifo;
	ustawParametry(&lifo, &fifo);

	char* tekst;
	char* operacja;
	operacja = new char[5];

	int iloscOperacji;
	cin >> iloscOperacji;

	for (int i = 0; i < iloscOperacji; i++)
	{
		cin >> operacja;

		if (operacja[0] == 'a')
		{
			tekst = new char[3000];
			cin >> tekst;
			if (operacja[1] == 'k')
			{
				enQueue(&fifo, tekst);
			}
			else if (operacja[1] == 's')
			{
				push(&lifo, tekst);
			}
		}

		if (operacja[0] == 'd')
		{
			if (operacja[1] == 'k')
			{
				deQueue(&fifo);
			}
			else if (operacja[1] == 's')
			{
				pop(&lifo);
			}
		}

		if (operacja[0] == 'c')
		{
			if (operacja[1] == 'k')
			{
				if (operacja[2] == 'k')
				{
					powielaj(&fifo);
				}
				else if (operacja[2] == 's')
				{
					powielaj(&fifo, &lifo);
				}
			}
			else if (operacja[1] == 's')
			{
				if (operacja[2] == 'k')
				{
					powielaj(&lifo, &fifo);
				}
				else if (operacja[2] == 's')
				{
					powielaj(&lifo);
				}
			}
		}

		if (operacja[0] == 'm')
		{
			if (operacja[1] == 'k')
			{
				if (operacja[2] == 'k')
				{
					przeniesIusun(&fifo);
				}
				else if (operacja[2] == 's')
				{
					przeniesIusun(&fifo, &lifo);
				}
			}
			else if (operacja[1] == 's')
			{
				if (operacja[2] == 'k')
				{
					przeniesIusun(&lifo, &fifo);
				}
				else if (operacja[2] == 's')
				{
					przeniesIusun(&lifo);
				}
			}
		}

		if (operacja[0] == 'j')
		{
			if (operacja[1] == 'k')
			{
				if (operacja[2] == 'k')
				{
					polaczKK(&fifo, &lifo);
				}
				else if (operacja[2] == 's')
				{
					polacz(&fifo, &lifo);
				}
			}
			else if (operacja[1] == 's')
			{
				if (operacja[2] == 'k')
				{
					polacz(&lifo, &fifo);
				}
				else if (operacja[2] == 's')
				{
					polaczSS(&lifo, &fifo);
				}
			}
		}

		if (operacja[0] == 's')
		{
			if (operacja[1] == 'k')
			{
				if (fifo.head == fifo.tail)
				{
					printf("%s", "#");
					cout << endl;
				}
				else
				{
					wyswietlaj(&fifo);
				}
			}
			else if (operacja[1] == 's')
			{
				if (czyStosPusty(&lifo))
				{
					printf("%s", "#");
					cout << endl;
				}
				else
				{
					wyswietlaj(&lifo);
				}
			}
		}
	}

	return 0;
}

