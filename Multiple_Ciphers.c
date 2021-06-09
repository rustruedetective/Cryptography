#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 500

//RSA prototypes
void msg(char in[],unsigned long long int msg[]);//takes input message
void printy(unsigned long long int a[], int name);//prints the outputed string
void rsa(unsigned long long int a[] ,unsigned long long int b[],int i,unsigned long long int o, unsigned long long int n);//combined the seperate functions of RSA that do individual functions into one complete RSA algorithm
void newpq(unsigned long long int p, unsigned long long int q);//gives user new keys
void encrypt(unsigned long long int a[] ,unsigned long long int b[], unsigned long long int e, unsigned long long int n);//encrypts the plain strings
void decrypt(unsigned long long int a[] ,unsigned long long int b[], unsigned long long int d, unsigned long long int n);//decrypts the encrypted string
int primechecker(unsigned long long int x);//checks if a number is prime
unsigned long long int ea(unsigned long long int a, unsigned long long int b);//euclidean algorithm, used for checking greatest common dividor, not used here though, made only as a side tool
unsigned long long int eea(unsigned long long int a, unsigned long long int b);//extended euclidean algorithm, gives inverse of mode, useful for finding keys
//RSA prototypes

//Ceaser prototypes
void shifter(unsigned long long int a[],  long long int key);
//Ceaser prototypes

//Baconian prototypes
void tobinary(int txtii[] , char txt1[]);
void frombinary(int txtii[] , char txt1[]);
//Baconian prototypes

//Vcipher prototypes
int length_findersent(char sentence[]);
int length_finderkey(char key[]);
//Vcipher prototypes

void rsacomp(void );//complete RSA not the single combination funciton rsa
int ceasercipher(void );
int baconiancipher(void );
int vcipher(void );

int main()
{
    int choose = 0;

    while(choose != 5)
    {
        printf("%s\n%s\n%s\n%s\n%s\n%s\n",
    "Please choose which cipher you would like to use",
    "Press 1 to use Ceaser cipher",
    "Press 2 to use Baconian cipher",
    "Press 3 to use RSA system",
    "Press 4 to use Vigenere cipher",
    "Press 5 to exit");

    choose = 0;
    fflush(stdin);
    scanf("%d", &choose);
    getchar();

    //we decide which sipher to use from these if statements
    if(choose == 1)
    {
        puts("Welcome to Ceaser cipher");
        ceasercipher();
    }
    else if(choose == 2)
    {
        puts("Welcome to Baconian cipher");
        baconiancipher();
    }
    else if(choose == 3)
    {
        puts("Welcome to RSA");
        rsacomp();
    }
    else if(choose == 4)
    {
        puts("Welcome to Vigenere cipher");
        vcipher();
    }
    else if(choose == 5)
    {
        puts("Good bye!");
    }
    else if(choose != 5 && choose != 4 && choose != 3 && choose != 2 && choose != 1)
    {puts("Wrong Input");}
    }

    
    system("pause");
}


void rsacomp(void ) 
{
    char in[SIZE] = {0};//plain text string
    unsigned long long int txt[SIZE] = {0};//integers of the plain text string
    unsigned long long int cip[SIZE] = {0};//integers of the encrypted string
    int newOrOld = 0;

    while(newOrOld != 1)//we can choose to get new values of keys e,d,n or use old ones, this while keeps it running until we have keys e,d,n
    {
        puts("Please Press 1 if you have keys or Press 2 to generate new keys");
    
        fflush(stdin);
        scanf("%d", &newOrOld);
        getchar();

        if(newOrOld == 1)//runs the rsa algorithm
        {
            msg(in, txt);//takes in message from user
            unsigned long long int e = 0, d= 0, n = 0;//keys

            //encrypting
            puts("Please enter your keys e and n seperated by a space");
            fflush(stdin);
            scanf("%llu %llu" ,&e ,&n);
            getchar();
            rsa(txt , cip, 0,e,n);
            printy(cip, 1);


            //decrypting
            puts("Now if you want to decrypt it then enter your keys d and n seperated by a space");
            fflush(stdin);
            scanf("%llu %llu", &d, &n);
            getchar();
            rsa(txt , cip, 1,d,n);
            printy(txt, 0);

        }
        else if(newOrOld == 2)//calls function to generate new keys
        {
            rsa(txt , cip, 3 ,0 ,0);
        }
        else
        {
            puts("Good bye!");
            newOrOld =1;
        }
    }
    puts("Good Bye From RSA!");
}

int ceasercipher(void ) 
{
    int f = 0;
    char b = 'a';
    char text[SIZE];
    unsigned long long int text2[SIZE] = {0};
     long long int key = {0};
    int c;
    printf("Enter the text you want to encrypt:");    
        
    f = 0;
    b = 'a';
    fflush(stdin);
    while(b != '\n' && f <(SIZE-1))
    {
        b = getchar();
        text[f] = b;
        f++;
    }
    text[f] = '\0';
    b = 'a';

    printf("Enter the key:");
    fflush(stdin);
    scanf("%d", &key);

    if( key > 350)
    {
        puts("Sorry you may not enter a key longer than 350");
        return 0;
    }

    for(int i =0 ; i <SIZE ; i++)
    {
        text2[i] = text[i];
    }

    shifter(text2, key);

    for(int i =0 ; i <SIZE ; i++)
    {
        text[i] = text2[i];
    }

    printf("Encrypted text: %s", text);
    puts("");

    puts("To decrypt the text enter the key again.");
    printf("Enter the key:");
    fflush(stdin);
    scanf("%d", & key);
    
    key = key-(2*key);

    shifter(text2, (key) );

    for(int i =0 ; i <SIZE ; i++)
    {
        text[i] = text2[i];
    }

    printf("Dycrypted text: %s", text);
    puts("");
    puts("Good Bye From Ceaser!");
}

int baconiancipher(void ) 
{
    int p = 0, i = 0, l = 0, f = 0, f2 = 0;
	char a = 'a';
	int yesorno = 0;
	int binval[8] = { 0 };
	char txt1[SIZE] = { 0 };
	int txtii[SIZE * 8] = { 0 };
	char txt2[SIZE * 8] = { 0 };
	int z = 0;

	
	puts("Please enter any sentence you would like to hide:");
	f = 0;
    a = 'a';
	fflush(stdin);
	while(a != '\n' && f < (SIZE-1))
    {
        a = getchar();
        txt1[f] = a;
        f++;
    }
    txt1[f-1] = '\0';

	tobinary(txtii,txt1);
	
	for (int k = 1; k < (f*8); k++)
	{
		printf("%d", txtii[k - 1]);
		z++;
	}
    z++;
	
	puts("");
	
    while(1)
    {
        puts("");
	puts("Please enter the sentence your would like to hide the original sentece in:");
	printf("Note:(The sentence should be atleast %d characters long and it should only contain alphabets)\n", z);
	printf("(No special symbols or numbers are allowed. Only alphabets and space)\n");
	
	
	f2 = 0;
	a = 'a';
	fflush(stdin);
    while(a != '\n' && f2 < (SIZE-1))
    {
        a = getchar();
        txt2[f2] = a;
        f2++;

        if( !(a >= 65 && a <= 90) && !(a >= 97 && a <= 122) && a != 32 && a != '\n')
        {
            puts("Sorry you enter any value other than alpbhabets and space");
            return 0;
        }
    }
    txt2[f2-1] = '\0';
	puts("");

    if(f2<(f*8))
    {
        puts("You did not enter enough characters. Re enter them");
    }
    else
    {break;}
    }

	i = 0;
	for (l = 0; l<SIZE * 8; l++)
	{
		if (txt2[l] != 0 && txt2[l] != 32)
		{
			if (txt2[l] > 96 && txtii[i] == 0)
			{

			}
			else if (txt2[l] > 96 && txtii[i] == 1)
			{
				txt2[l] -= 32;
			}
			else if (txt2[l] > 64 && txt2[l] < 91 && txtii[i] == 0)
			{
				txt2[l] += 32;
			}
			else if (txt2[l] > 64 && txt2[l] < 91 && txtii[i] == 1)
			{

			}
			i++;
		}
	}

	puts("Coded false message");
	for (int m = 0; m<SIZE; m++)
	{
		if (txt2[m] != 0 && txt2[m] != 32)
		{
			printf("%c", txt2[m]);
		}
	}
	puts("");

	puts("Would you like to see the original message?\nPress 1 to see it\nPress 2 to exit");
	fflush(stdin);
	scanf("%d", &yesorno);
	getchar();

    for (int q = 0; q<SIZE * 8; q++)
		{
            txtii[q] = 0;
        }

	if (yesorno == 1)
	{
		i = 0;
		for (int q = 0; q<SIZE * 8; q++)
		{
			if (txt2[q] != 0 && txt2[q] != 32)
			{
				if (txt2[q] > 96)
				{
					txtii[i] = 0;
				}
				else if (txt2[q] > 64 && txt2[q] < 91)
				{
					txtii[i] = 1;
				}

				i++;
			}
		}

		frombinary(txtii,txt1);

		puts("Decrypted code:-");
		for (int k = 1; k <= SIZE; k++)
		{
			printf("%c", txt1[k - 1]);
		}


	}
	else if (yesorno == 2)
	{
		puts("Good bye!");
	}
	puts("");
    puts("Good Bye From Baconian!");
}

int vcipher(void ) 
{
    char sentence[SIZE];
    char key[SIZE];
    int f2 = 0;
    int a ='a';

    puts("Please note that the Viginere cipher will have some specifications");
    puts("Firstly the vigenere will be only take in alphabets and spaces");
    puts("The case of input text and key should be the same as is recommended");
    puts("This is because in real life we only have one form of alphabets");
    puts("In ASCII there are two lists of apbhabets not one, so each has its own specifications");
    puts("Now");
    puts("Enter your Sentence Please");
    	//scanf("%s",sentence);

    f2 = 0;
	a = 'a';
	fflush(stdin);
    while(a != '\n' && f2 < (SIZE-1))
    {
        a = getchar();
        sentence[f2] = a;
        f2++;
        
        if( !(a >= 65 && a <= 90) && !(a >= 97 && a <= 122) && a != 32 && a != '\n')
        {
            puts("Sorry you enter any value other than alpbhabets and space");
            return 0;
        }
    }
    sentence[f2-1] = '\0';
	puts("");


    	puts("Enter your key code");
    	//scanf("%s",key);

    f2 = 0;
	a = 'a';
	fflush(stdin);
    while(a != '\n' && f2 < (SIZE-1))
    {
        a = getchar();
        key[f2] = a;
        f2++;
        if( !(a >= 65 && a <= 90) && !(a >= 97 && a <= 122) && a != '\n')
        {
            puts("Sorry you enter any value other than alpbhabets");
            return 0;
        }
    }
    key[f2-1] = '\0';
	puts("");

    	char cap_list[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    	char low_list[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    	int key_size=length_finderkey(key);
    	int sent_size=length_findersent(sentence);
    	int key_selector=0;
    	for(int i=0;i<sent_size;i+=1)
    	{
    		if(sentence[i]>=65 && sentence[i]<=90  && sentence[i] != 32)
    		{
    		    int y=sentence[i];
    			int adding_i=0;
    			for(;(cap_list[adding_i])!=key[key_selector];adding_i+=1){}
    			y+=adding_i;
    			if(y>90)
    			{
    				y=65+(y-90-1);
    				}
    				sentence[i]=y;
    			key_selector+=1;
    			if(key_selector==key_size)
    			{
    				key_selector=0;
    				}
    			}
    		else if(sentence[i]>=97 && sentence[i]<=122  && sentence[i] != 32)
    		{
    			int x=sentence[i];
    			int adding_i=0;
    			for(;(low_list[adding_i])!=key[key_selector];adding_i+=1){}
    			x+=adding_i;
    			//x=sent[i];
    			if(x>122)
    			{
    				x=97+(x-122-1);
    				//x=sent[i];
    				}
    			sentence[i]=x;
    			key_selector+=1;
    			if(key_selector==key_size)
    			{
    				key_selector=0;
    				}
    			}
    		}
    		key_selector=0;
            puts("");
    	printf("The encrypted message is:\n%s",sentence);
        puts("");

        puts("Please enter a key to decrypt.");
        fflush(stdin);
        //scanf("%s", key);

    f2 = 0;
	a = 'a';
	fflush(stdin);
    while(a != '\n' && f2 < (SIZE-1))
    {
        a = getchar();
        key[f2] = a;
        f2++;
    }
    key[f2-1] = '\0';
	puts("");

    	for(int i=0;i<sent_size;i+=1)
    	{
    		if(sentence[i]>=65 && sentence[i]<=90  && sentence[i] != 32)
    		{
    		    int y=sentence[i];
    			int adding_i=0;
    			for(;(cap_list[adding_i])!=key[key_selector];adding_i+=1){}
    			y-=adding_i;
    			if(y<65)
    			{
    				y=90-((65-1)-y);
    				}
    				sentence[i]=y;
    			key_selector+=1;
    			if(key_selector==key_size)
    			{
    				key_selector=0;
    				}
    			}
    		else if(sentence[i]>=97 && sentence[i]<=122  && sentence[i] != 32)
    		{
    			int x=sentence[i];
    			int adding_i=0;
    			for(;(low_list[adding_i])!=key[key_selector];adding_i+=1){}
    			x-=adding_i;
    			//x=sent[i];
    			if(x<97)
    			{
    				x=122-((97-1)-x);
    				//x=sent[i];
    				}
    			sentence[i]=x;
    			key_selector+=1;
    			if(key_selector==key_size)
    			{
    				key_selector=0;
    				}
    			}
    		}
            puts("");
    	printf("The decryped message is:\n%s",sentence);
    	puts("");
        puts("Good Bye From Vigenere.");
}


//RSA functions.............................................................................................
void rsa(unsigned long long int a[] ,unsigned long long int b[], int i,unsigned long long int o, unsigned long long int n)
{
    unsigned long long int p = 0 , q = 0;
    int primeOrNot = 0;//stores value if a number is prime or not

    if(i == 0)
    {
        encrypt(a ,b,o,n);
    }
    else if(i == 1)
    {
        decrypt(a ,b,o,n);
    }
    else if(i == 2)//not used although it was possible in the initial stages so just left out, it cannot be called btw os it is safe
    {
        //encrypt(a ,b,o,n);
        //decrypt(a ,b,o,n);
    }
    else if(i == 3)
    {
        while(primeOrNot == 0)//if the values of p and q are prime only then can the loop end and keys be generated
        {
            puts("Please enter new values of primes p and q seperated by space.");
            fflush(stdin);
            scanf("%llu %llu",&p ,&q);
            getchar();
            if(primechecker(p) && primechecker(q))//checks primes of not by the lengthy primecheker function
            {
                primeOrNot = 1;
            }
            else
            {
                primeOrNot = 0;
            }
            
        }
        newpq(p,q);
        puts("Now use these values.");
    }
    else
    {
        puts("You did not enter the correct value now suffer.");
    }
}

void encrypt(unsigned long long int a[] ,unsigned long long int b[], unsigned long long int e, unsigned long long int n)
{
    unsigned long long int j = 0 , l = 1;
    
    int i = 0;

    for(i = 0 ; i<SIZE ; i++)//takes the integer of string to the power of e and mods with n
    {
        l = 1;
        for (j=0;j<e;j++)
        {
	        l=l*a[i];
            l=l%n;
            //if(i == 0)
              //  printf("%llu  \n\n", l);
        }

        b[i] = l;
    }
    /*for(i = 0 ; i<SIZE ; i++)
    {
        a[i] = 0;
    }*/
}


void decrypt(unsigned long long int a[] ,unsigned long long int b[], unsigned long long int d, unsigned long long int n)
{
    unsigned long long int j = 0 , l = 1;
    
    int i =0;

    for(i = 0 ; i<SIZE ; i++)//takes the integer of string and raises to power of d and mods with n
    {
        l = 1;
        for (j=0;j<d;j++)
        {
	        l=l*b[i];
            l=l%n;
        }
        a[i] = l;
    }
    /*for(i = 0 ; i<SIZE ; i++)
    {
        b[i] = 0;
    }*/
}

void newpq(unsigned long long int p, unsigned long long int q)
{
    unsigned long long int e = 0 , d = 0 , n = 0 , phi = 0, i = 1;
    srand(time(NULL));

    n = p*q;//creates n
    phi = (p-1)*(q-1);//creates phi

    while(i<phi)//almost randomly, takes a value of prime and makes it into e
    {
        if( (primechecker(i) ) && (i != p) && (i != q) && (i > (20+(rand()%50)) ) )
        {
            e = i;
            break;
        }
        i++;
    }
    d = eea(e,phi);//calls the extended euclidean algorithm to find mod inverse of e mod phi which is d

    printf("New values Hurray! e= %llu d= %llu n= %llu phi= %llu\n",e,d,n,phi);
}

int primechecker(unsigned long long int x)
{
    unsigned long long int i = 2;

    for(i = 2; i < x ; i++)//simply divides all values to check prime, lengthy process
    {
        if(x%i == 0)
        {
            return 0;
        }
    }
    return 1;
}

unsigned long long int ea(unsigned long long int a, unsigned long long int b)//magic
{
    unsigned long long int swap=0;
    if(b>a)
    {
        swap = b;
        b = a;
        a = swap;

        if(a%b == 0) //base case
        {
            return b;
        }
        else
        {
            return ea(b, a%b );
        }
    }
    else if(a == b)
    {
        return a;
    }
    else
    {
        
        if(a%b == 0) //base case
        {
            return b;
        }
        else
        {
            return ea(b, a%b );
        }
    }
}

unsigned long long int eea(unsigned long long int a, unsigned long long int b)//uses the equations of extended euclidean algorithm to compute the inverse
{
    //we have two equations to manipulate here, so instead of manipulating the whole equation
    //lets just manipulate their variables

    unsigned long long int r[3] = {0} , q , s[3] = {0,1,0} , t[3] = {1,0,0};
    r[0] = a;
    r[1] = b;

    
    while(r[2] != 1)//changes values of each variable in the actual equation on each iteration
    {
        //ea
        r[2] = r[0]%r[1];
        q = r[0]/r[1];
        //ea

        //eea core equations
        s[2] = s[0] - (q*s[1]);
        t[2] = t[0] - (q*t[1]);
        //eea core equations

        //shifting
        r[0] = r[1];
        r[1] = r[2];
        s[0] = s[1];
        s[1] = s[2];
        t[0] = t[1];
        t[1] = t[2];  
        //shifting
    }
    return ((t[2]+b)%b);
}

void printy(unsigned long long int a[] ,int name)
{
    int i =0;
    
    //checks which to print, the word "text" or "cipher"
    if(name == 0)
    {
        puts("Your text is:-");
    }
    else if(name == 1)
    {
        puts("Your cipher is:-");
    }
    for(i = 0; i <  SIZE; i++)
        printf("%c", a[i]);
        puts("");
}

void msg(char in[],unsigned long long int msg[])
{
    int i = 0;
    char a = 'a';
    puts("Please enter your message");
    //scanf("%[^\n]%*c", in);
    //getchar();
    
            //uses a basic technique to read once character a time thus reading whitespaces also ,except newline character
    i = 0;
    fflush(stdin);
    while(a != '\n' && i < (SIZE-1))
    {
        a = getchar();
        in[i] = a;
        i++;
    }
    in[i-1] = '\0';

    for(int i=0; i<SIZE; i++)
    {
        msg[i] = in[i];
    }
}
//RSA functions.............................................................................................

//Ceaser functions..........................................................................................
void shifter(unsigned long long int a[],  long long int key)
{
    for (int i = 0; a[i] < SIZE; i++)
    {
        a[i] += key; 
    }
}
//Ceaser functions..........................................................................................

//Baconian functions........................................................................................
void tobinary(int txtii[] , char txt1[])
{
	for (int p = 0; p < SIZE; p++)
	{
			txtii[8 * p + 7] = (txt1[p]) % 2;
			txtii[8 * p + 6] = ((txt1[p]) / 2) % 2;
			txtii[8 * p + 5] = (((txt1[p]) / 2) / 2) % 2;
			txtii[8 * p + 4] = ((((txt1[p]) / 2) / 2) / 2) % 2;
			txtii[8 * p + 3] = (((((txt1[p]) / 2) / 2) / 2) / 2) % 2;
			txtii[8 * p + 2] = ((((((txt1[p]) / 2) / 2) / 2) / 2) / 2) % 2;
			txtii[8 * p + 1] = (((((((txt1[p]) / 2) / 2) / 2) / 2) / 2) / 2) % 2;
			txtii[8 * p + 0] = ((((((((txt1[p]) / 2) / 2) / 2) / 2) / 2) / 2) / 2) % 2;
			
	}
}

void frombinary(int txtii[] , char txt1[])
{
	for (int u = 0; u<SIZE; u++)
		{
			txt1[u] = (txtii[u * 8 + 0] * 126) + (txtii[u * 8 + 1] * 64) + (txtii[u * 8 + 2] * 32) + (txtii[u * 8 + 3] * 16) + (txtii[u * 8 + 4] * 8) + (txtii[u * 8 + 5] * 4) + (txtii[u * 8 + 6] * 2) + (txtii[u * 8 + 7] * 1);
		}
}
//Baconian functions........................................................................................


//Vigenere functions........................................................................................
int length_findersent(char sentence[])
{
    int n=0;
    for(int i=0;sentence[i]!='\0';i++)
    {
    	n+=1;
	}
	return n;
}

int length_finderkey(char key[])
{
	int n=0;
	for(int i=0;key[i]!='\0';i++)
	{
    	n+=1;
	}
    return n;
}

//Vigenerefunctions........................................................................................