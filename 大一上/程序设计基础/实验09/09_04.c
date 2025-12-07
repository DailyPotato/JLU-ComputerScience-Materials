#include <stdio.h>
#include <malloc.h>

struct farlei_item {
    int numerator, denominator;   // 分子、分母
    struct farlei_item* next;     // 连接部分
};

typedef struct farlei_item* farleipointer;

int gcd(int x, int y) {
    int temp=x%y;
    if(temp==0)return y;
    else
    {
        return gcd(y,temp);
    }
}

/*构造法雷序列,并返回序列头指针*/
farleipointer farlei(int n) {
    int i, j;
    farleipointer fn, r, r0, p;
    fn = r = r0 = p = NULL;
    
    if (n < 1) return NULL; //如果n<=0,则没有法雷序列
    
    fn = (farleipointer)malloc(sizeof(struct farlei_item));  //构造0/1
    fn->numerator = 0;
    fn->denominator = 1;
    
    p = (farleipointer)malloc(sizeof(struct farlei_item));   //构造1/1
    p->numerator = 1;
    p->denominator = 1;
    fn->next = p;
    p->next = NULL;
    
    for(i=2;i<=n;i++)
    {
        for(j=1;j<i;j++)
        {
            if(gcd(i,j)==1)
            {
                r=fn;
                while(j*r->denominator>i*r->numerator)
                {
                    r0=r;
                    r=r->next;
                }
                farleipointer p=(farleipointer)malloc(sizeof(struct farlei_item));
                r0->next=p;
                p->denominator=i;
                p->numerator=j;
                p->next=r;
            }
        }
    }
    
    return fn;
}

void print(farleipointer fn) {
    //输出fn引导的法雷序列
    farleipointer p=fn;
    while(p)
    {
        printf("%d/%d ",p->numerator,p->denominator);
        p=p->next;
    }
}

void release(farleipointer fn)
{
    farleipointer p;
    while (fn)
    {
        p = fn;
        fn = fn->next;
        free(p);
    }
}

int main(void) {
    int n;
    farleipointer fn;
    
    scanf("%d", &n);
    fn = farlei(n); //生成n级法雷序列
    
    if (fn != NULL)
        print(fn);
    else
        printf("NULL");
    
    release(fn);
    return 0;
}