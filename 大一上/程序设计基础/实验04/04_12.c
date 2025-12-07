#include <stdio.h>

int main()
{
    int n, ge = 0, shi = 0, bai = 0;
    scanf("%d", &n);
    
    if (n < 0 || n >= 1000)
    {
        printf("ERR");
        return 0;
    }
    
    if (n == 0)
    {
        printf("zero");
        return 0;
    }
    
    ge = n % 10;
    shi = (n / 10) % 10;
    bai = n / 100;
    
    int has_output = 0;
    

    if (bai != 0)
    {
        switch (bai)
        {
            case 1: printf("one hundred"); break;
            case 2: printf("two hundred"); break;
            case 3: printf("three hundred"); break;
            case 4: printf("four hundred"); break;
            case 5: printf("five hundred"); break;
            case 6: printf("six hundred"); break;
            case 7: printf("seven hundred"); break;
            case 8: printf("eight hundred"); break;
            case 9: printf("nine hundred"); break;
        }
        has_output = 1;
    }
    
    if (shi == 1)  
    {
        if (has_output) printf(" and ");
        switch (ge)
        {
            case 0: printf("ten"); break;
            case 1: printf("eleven"); break;
            case 2: printf("twelve"); break;
            case 3: printf("thirteen"); break;
            case 4: printf("fourteen"); break;
            case 5: printf("fifteen"); break;
            case 6: printf("sixteen"); break;
            case 7: printf("seventeen"); break;
            case 8: printf("eighteen"); break;
            case 9: printf("nineteen"); break;
        }
    }
    else
    {
        if (shi >= 2)
        {
            if (has_output) printf(" and ");
            switch (shi)
            {
                case 2: printf("twenty"); break;
                case 3: printf("thirty"); break;
                case 4: printf("forty"); break;
                case 5: printf("fifty"); break;
                case 6: printf("sixty"); break;
                case 7: printf("seventy"); break;
                case 8: printf("eighty"); break;
                case 9: printf("ninety"); break;
            }
            has_output = 1;
        }
        
        if (ge != 0)
        {
            if (has_output && shi >= 2) 
                printf("-");  
            else if (has_output)
                printf(" and ");  
            
            switch (ge)
            {
                case 1: printf("one"); break;
                case 2: printf("two"); break;
                case 3: printf("three"); break;
                case 4: printf("four"); break;
                case 5: printf("five"); break;
                case 6: printf("six"); break;
                case 7: printf("seven"); break;
                case 8: printf("eight"); break;
                case 9: printf("nine"); break;
            }
        }
    }
    
    return 0;
}