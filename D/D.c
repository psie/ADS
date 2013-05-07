// CYK 
//
// allowed nonterminals: A, B, C, D, E, F, G, H - 8
// allowed terminals: lowercase letters - 26
// A is always the start symbol

#include <stdio.h>
#include <string.h>

char word[500];
unsigned char nonterm[8][8]; 
unsigned char term[26];

unsigned char n2[256][256]; // for preprocessing

unsigned char tab[500][500];

int main()
{
	unsigned char c1, c2, c3;
	int d, m1, m2, N;
	
	int i, j, k, l, m;

	scanf("%d", &d);

	for(i=0; i<d; ++i) // for each instance 
	{
		memset(nonterm, 0, 8*8);
		memset(term, 0, 26);
		memset(word, 0, 500);
		memset(tab, 0, 500*500);
		memset(n2, 0, 256*256);

		scanf("%d%d", &m1, &m2); 

		for(j=0; j<m1; ++j) // reading nonterminals
		{
			getchar();
			c1=getchar();
			getchar();
			c2=getchar();
			getchar();
			c3=getchar();
			nonterm[c2-'A'][c3-'A'] |= (1<<(c1-'A')); // c1 -> c2 c3	
			
		}

		for(j=0; j<m2; ++j) // reading terminals
		{
			getchar();
			c1=getchar();
			getchar();
			c2=getchar();
			term[c2-'a'] |= (1<<(c1-'A')); // c1 -> c2

		}
		scanf("%500s", word);
		
		if(m2 == 0) // zero terminals in grammar
		{
			printf("NIE\n"); 
			continue;
		}

		N=strlen(word);

		// preprocessing
		// reverse mapping nonterminal rules
		for(j=0; j<256; ++j)
			for(k=0; k<256; ++k)
				for(l=0; l<8; ++l)
					if(j & 1<<l)
						for(m=0; m<8; ++m)
							if(k & 1<<m)
								n2[j][k] |= nonterm[l][m];  
		// CYK
		for(j=0; j<N; ++j)
			tab[0][j] = term[word[j]-'a'];
		
		for(j=0; j<N; ++j)
			for(k=0; k<N-j; ++k)
				for(l=0; l<j; ++l)
					tab[j][k] |= n2[ tab[j-l-1][k] ][ tab[l][j+k-l] ];

		if(tab[N-1][0]&1)
			printf("TAK\n"); // the word can be derived from grammar
		else
			printf("NIE\n");
	}

	return 0;
}

