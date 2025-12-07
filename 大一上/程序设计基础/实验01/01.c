#include <stdio.h>
#include <math.h>
#define PI 3.1415926

int main(void)
{
  float data1,data2;
  scanf("%f%f",&data1,&data2);
  float ans=sin(data2)/(data1*data2)+fabs(cos(data2*(PI/2)));
  printf("%.3f",ans);
  return 0;
}
