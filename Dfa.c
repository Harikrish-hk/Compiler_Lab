#include<stdio.h>
#include<string.h>
int main()
{
    int ns,nsy,fs;
    printf("Enter the Number of States:\t");
    scanf("%d",&ns);
    printf("Enter the Number of Symbols:\t");
    scanf("%d",&nsy);
    char sym[nsy];
    printf("Enter the Symbols:\t");
    for(int i=0;i<nsy;i++)
    {
        scanf(" %c",&sym[i]);
    }
    int trans[ns][nsy];
    printf("Enter the transition table:\n");
    for(int i=0;i<ns;i++)
    {
        for(int j=0;j<nsy;j++)
        {
            printf("(Q%d,%c)-->\t",i,sym[j]);
            scanf("%d",&trans[i][j]);
        }
    }
    printf("Enter the Number of Final States:\t");
    scanf("%d",&fs);
    int fst[fs];
    printf("Enter the Final States:\n");
    for(int i=0;i<fs;i++)
    {
        scanf("%d",&fst[i]);
    }
    while(1)
    {
        int cur_st=0,index;
        printf("Enter the String:\t");
        char string[20];
        scanf("%s",string);
        int len=strlen(string);
        for(int i=0;i<len;i++)
        {
            char ch=string[i];
            for(int j=0;j<nsy;j++)
            {
                if(ch==sym[j])
                  index=j;
                break;
            }
            cur_st=trans[cur_st][index];
        }
        int flag=0;
        for(int i=0;i<fs;i++)
        {
            if(cur_st==fst[i])
            {
                flag=1;
                break;
            }
        }
        if(flag==1)
         printf("Accepted.\n");
        else
         printf(" Not Accepted.\n");
    }
}
