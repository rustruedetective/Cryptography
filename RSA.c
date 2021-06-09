/*Notes:
RSA in real life has very high values of keys, so value of n less than 256 in here will break the cipher since 256 is the number of characters in ascii.
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 500

void msg(char in[],unsigned long long int msg[]);//takes input message
void printy(unsigned long long int a[], int name);//prints the outputed string
void rsa(unsigned long long int a[] ,unsigned long long int b[],int i,unsigned long long int o, unsigned long long int n);//combined the seperate functions of RSA that do individual functions into one complete RSA algorithm
void newpq(unsigned long long int p, unsigned long long int q);//gives user new keys
void encrypt(unsigned long long int a[] ,unsigned long long int b[], unsigned long long int e, unsigned long long int n);//encrypts the plain strings
void decrypt(unsigned long long int a[] ,unsigned long long int b[], unsigned long long int d, unsigned long long int n);//decrypts the encrypted string
int primechecker(unsigned long long int x);//checks if a number is prime
unsigned long long int ea(unsigned long long int a, unsigned long long int b);//euclidean algorithm, used for checking greatest common dividor, not used here though, made only as a side tool
unsigned long long int eea(unsigned long long int a, unsigned long long int b);//extended euclidean algorithm, gives inverse of mode, useful for finding keys

int main()
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