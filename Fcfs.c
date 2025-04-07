#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num;
    printf("Enter number of process\n");
    scanf("%d\n",&num);
    int total[num][5];
    for (int i=0;i<num;i++)
    {
        printf("Enter Arrival time of process %d\n",i);
        scanf("%d\n",&total[i][0]);
        printf("Enter Burst time of the process %d\n",i);
        scanf("%d\n",&total[i][1]);
    }
    int asce[num];

    for (int i=0;i<num;i++)
    {
        int temp=total[i][0];
        for(int j=i+1;j<num;j++)
        {
            if (total[j][0]<temp)
            {
                temp=total[j][0];
                continue;
            }

        }
        asce[i]=temp;

    }
    int ct=0;

    for (int i=0;i<num;i++)
    {
        for(int j=0;j<num;j++)
        {
           
            if(total[j][0]==asce[i])
            {
                if (ct<total[j][0])
                {
                    ct=total[j][0];
                }
                ct=ct+total[j][1];
                total[j][2]=ct;
                total[j][3]=ct-total[j][0];
                total[j][4]=total[j][3]-total[j][1];

            }
        }
    }


for(int i=0;i<num,i++)
{
    printf("For Process")


}
}