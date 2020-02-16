#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main(int argc,char *argv[])
{
	char ch,aword[20],gword[20],mess[100],p;
	int b,n,j=0,i,flag=0,sockid,newsockid,clilen,g,h;
	struct sockaddr_in seraddr,cliaddr;
	sockid=socket(AF_INET,SOCK_STREAM,0);

	bzero(&seraddr,sizeof(seraddr));
	seraddr.sin_family=AF_INET;

	seraddr.sin_port=htons(atoi(argv[1]));
	bind(sockid,(struct sockaddr*)&seraddr,sizeof(seraddr));

	listen(sockid,5);
	clilen=sizeof(cliaddr);
	newsockid=accept(sockid,(struct sockaddr*)&cliaddr,&clilen);

	printf("client connected\n");
while(1)
{
    j=0;flag=0;
    read(newsockid,&n,4);
    
	printf("Enter the actual word:");
	scanf("%s",aword);
	printf("Enter the word in the format:(apple->a_p_le):");
    lb:
    scanf("%s",gword);
    flag=0;
    g=0;h=0;
    for(i=0;aword[i]!='\0';i++)
        {
        	g++;
        	if(gword[i]!=aword[i]&&gword[i]!='_')
        	{
        		flag=1;
        		break;
        	}
        	if(gword[i]=='_')
        	{
        		h++;
        	}

        }
    if(strcmp(gword,aword)==0||flag==1||g==h)
    {
      printf("please enter a correct incomplete word:");
      goto lb;
    }
    write(newsockid,gword,sizeof(gword));
    while(1)
    {

    	read(newsockid,&ch,sizeof(ch));
    	
        for(i=0;aword[i]!='\0';i++)
        {
        	flag=0;
        	if(gword[i]=='_'&&ch==aword[i])
        	{
        		gword[i]=ch;
        		flag=1;
        		break;
        	}

        }
        if(flag==0)
        {
            if(n==1)
                j=j+4;
            else if(n==2)
                j=j+2;
            else
                j=j+1;

        }
        b=j;
        write(newsockid,gword,20);
        write(newsockid,&flag,4);
        
        if(strcmp(gword,aword)==0)
        	{
        		b=100;
        		write(newsockid,&b,4);
        		break;
        	}

        write(newsockid,&b,4);
        
        if(j==8)
        	break;

    }
    if(strcmp(gword,aword)==0)
    {
        strcpy(mess,"won the game");   
    }
    else
    {
    	strcpy(mess,"lose the game");
    }
    write(newsockid,mess,sizeof(mess));
    write(newsockid,aword,sizeof(aword));
    printf("player %s",mess);
    printf("\n");
    read(newsockid,&p,1);
    if(p!='y')
        break;
}
    close(newsockid);
    return 0;
}



