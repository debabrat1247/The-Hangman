#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main(int argc,char *argv[])
{
    char man[8][15]={{' ',' ',' ',' ','_','_','_','\n'},{' ',' ',' ',' ',' ','|','\n'},{' ',' ',' ',' ',' ','0','\n'},{' ',' ',' ',' ',' ','|','\n'},{' ',' ',' ',' ','/','|','\\','\n'},{' ',' ',' ',' ',' ','|','\n'},{' ',' ',' ','_','/',' ','\\','_','\n'},{'_','_','_','_','_','_','_','_','_','_','_','\n'}};
	int sockid,j,flag=1,r,s,n;
	char ch,gword[20],mess[100],p;
	struct sockaddr_in seraddr;
	sockid=socket(AF_INET,SOCK_STREAM,0);
	bzero(&seraddr,sizeof(seraddr));
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(atoi(argv[2]));
	inet_pton(AF_INET,argv[1],&seraddr.sin_addr);
	connect(sockid,(struct sockaddr*)&seraddr,sizeof(seraddr));
    printf("WELCOME TO HANGMAN GAME\n");;
while(1)
{
    
    printf("1.HARD\n");
    printf("2.MEDIUM\n");
    printf("3.EASY\n");
    printf("choose the level of game:");
    scanf("%d",&n);
    getchar();
    write(sockid,&n,4);
    printf("wait till server give you the word.....\n");
    read(sockid,gword,20);
    printf("start guessing the word:%s\n",gword);
    
    while(1)
    {
    	printf("put a letter:");
    	scanf("%c",&ch);
    	getchar();
    	write(sockid,&ch,1);
        read(sockid,gword,20);
        printf("%s\n",gword);
        read(sockid,&flag,4);
    	read(sockid,&j,4);
        if(flag==0)
        {
            for(r=0;r<j;r++)
            {
                for(s=0;s<15;s++)
                {
                    printf("%c",man[r][s]);
                }
            }
            printf("\a\a\a\a\a\a");
        }
    	if(j==100)
    		break;

    	if(j==8)
    		break;
    
    }
    read(sockid,mess,100);
    printf("You %s\n",mess);
    read(sockid,mess,100);
    printf("actual word:%s",mess);
    printf("\nPlay again(y/n):");
    scanf("%c",&p);
    write(sockid,&p,1);
    if(p!='y')
        break;
}
	close(sockid);
	return 0;
}