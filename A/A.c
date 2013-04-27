/* Przemyslaw Sierocinski
 * i248066
 */
#include <stdio.h>
#include <stdlib.h>

#define QSIZE 1500*2000

char graf[2000*2000]; // 4MB

struct element
	{
		int id;
		int plength;
	};

struct element queue[QSIZE];  
struct element e;

unsigned qbeg, qend, last;

inline void addqueue(int id, int length)
{
	last = 0;
	queue[qend].id = id;
	queue[qend].plength = length;
	//printf("added %d at %u (l=%d)\t", id, qend, length);
	++qend;
	if(qend == QSIZE)
		qend = 0;
	return;
}

inline void delqueue()
{
	if(last)
	{
		printf("NIE");
		exit(0);
		//e.id = 1<<31;
		//return e;
	}

	if(qbeg == qend)
		last = 1;

	e = queue[qbeg];
	//printf("removed %u from %u (l=%d)\t", e.id, qbeg, e.plength);
	qbeg++;
	if(qbeg == QSIZE)
		qbeg = 0;
	return;
}

int main()
{
	int m,n,p,nm;
	register unsigned i,k;

	//memset(graf, 'x', 2000*2000);

	scanf("%u%u", &m, &n);

	fgetc(stdin); // '\n'

	for(i=0,k=0; i<n; ++i)
	{
		fread(graf+k, 1, m, stdin);
		fgetc(stdin); // '\n'
		k+=m;
	}

	for(k=0; k<m*n; ++k)
		if(graf[k] == 'P')
		{
			p=k;
			break;
		}

	//printf("p is: %u\n",p);
	//printgraph(m,n);

	qbeg = 0;
	qend = 0;
	last = 0;

	addqueue(p, 0);
	graf[p] = 'x';

	nm=n*m;

	while(1)
	{
		delqueue();
		if(e.id+m < nm)
			if(graf[e.id+m] != 'x')
			{
				if(graf[e.id+m] == 'S')
				{
					printf("%d", e.plength+1);
					return 0;
				}
				addqueue(e.id+m, e.plength+1);
				graf[e.id+m] = 'x';
			}
		if(e.id%m != m-1 && e.id+1 < nm)
			if(graf[e.id+1] != 'x')
			{
				if(graf[e.id+1] == 'S')
				{
					printf("%d", e.plength+1);
					return 0;
				}
				addqueue(e.id+1, e.plength+1);
				graf[e.id+1] = 'x';
			}
		if(e.id%m > 0 && e.id-1 >= 0)
			if(graf[e.id-1] != 'x')
			{
				if(graf[e.id-1] == 'S')
				{
					printf("%d", e.plength+1);
					return 0;
				}
				addqueue(e.id-1, e.plength+1);
				graf[e.id-1] = 'x';
			}
		if(e.id-m >= 0)
			if(graf[e.id-m] != 'x')
			{
				if(graf[e.id-m] == 'S')
				{
					printf("%d", e.plength+1);
					return 0;
				}
				addqueue(e.id-m, e.plength+1);
				graf[e.id-m] = 'x';
			}
		//printf("\n");
		//printgraph(m,n);
	}

	//printf("NIE");

	return 0;
}



