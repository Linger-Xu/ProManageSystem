#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>

double sumplus=0;
int login1 = 0,login2=0;

struct cell{
    int dingdan;       //订单编号：格式为1000001，1000002，。。。
    int month;         //以下四行是订单日期
    int day;
    int hour;
    int minute;
    int timesum;
    int zhanghao;
    char name[40];     //网点代理人姓名
    char phone[20];    //网点代理人电话
    char type[10];     //商品种类（酒&饮料）
    char itemname[40]; //商品名字
    float uprice;      //商品箱单价
    int rong;           //商品容量
    int inum;           //每箱几瓶
    char beizhu[2];     //商品赠品情况
    int num;           //商品数量
    double sum;        //该订单的总金额
    char itemlab[5];       //商品编号
    struct cell* next;
};
typedef struct cell* plink;

struct account
{
	int number;
	int password;
	char address[200];
    int level;
    float money;
};

struct item
{
    char itemname[40];
    char type[10];
    float uprice[5];
    int info[5][3];
    int tnum;
    char itemlab[5][5];
    struct item* next;
};
typedef struct item* tlink;

struct account useraccount;
plink addition(plink head,tlink ihead);
plink correct(plink head,tlink ihead);
plink fromto(plink head);
plink del(plink head,tlink ihead);
plink dateprint(plink head);
plink itemprint(plink head);
void printall(plink head);
void release(plink head);
void itemdateprint(plink head);
void usercheck(plink head);
int searchuser(int n);
struct cell* readorders(struct cell *head);
struct cell* changeorders(struct cell* head);
void renew();
int searchmanager(int n);
tlink addgoods(tlink ihead);
struct item* readitems(struct item* ihead);
struct item* changeitems(struct item* ihead);
void userprint(plink head);
plink moneyprint(plink head);
void readsum(struct cell* head);
void itemprintall(tlink ihead,struct cell* head);
plink giftcheck(plink head);
tlink itemdel(tlink head);
int min(int a,int b,int c);
int editDistance(char* str1,char *str2);
void itemprintalluser(tlink ihead,struct cell* head);

void readsum(struct cell* head)
{
    struct cell* p;
    p=head->next;
    while(p!=NULL)
    {
        if(p->zhanghao==useraccount.number)
        {
            sumplus+=p->sum;
        }
        p=p->next;
    }
}

struct cell* readorders(struct cell *head)
{
    FILE* order;
    order=fopen("allorders.txt","r");
    struct cell* p,*tmp;
    tmp=head;
    while(fgetc(order)!=EOF)
    {
        p=(struct cell*)malloc(sizeof(struct cell));
        tmp->next=p;
        fscanf(order,"%d ",&p->dingdan);
        fscanf(order,"%d ",&p->month);
        fscanf(order,"%d ",&p->day);
        fscanf(order,"%d ",&p->hour);
        fscanf(order,"%d ",&p->minute);
        fscanf(order,"%d ",&p->timesum);
        fscanf(order,"%d ",&p->zhanghao);
        fscanf(order,"%s ",p->name);
        fscanf(order,"%s ",p->phone);
        fscanf(order,"%s ",p->type);
        fscanf(order,"%s ",p->itemname);
        fscanf(order,"%f ",&p->uprice);
        fscanf(order,"%d ",&p->rong);
        fscanf(order,"%d ",&p->inum);
        fscanf(order,"%s ",p->beizhu);
        fscanf(order,"%d ",&p->num);
        fscanf(order,"%lf ",&p->sum);
        fscanf(order,"%s",p->itemlab);
        tmp=p;
        tmp->next=NULL;
    }
    fclose(order);
    return head;
};

tlink readitems(tlink ihead)
{
    FILE* items;
    items=fopen("allitems.txt","r");
    struct item* p,*tmp;
    tmp=ihead;
    while(fgetc(items)!=EOF)
    {
        p=(struct item*)malloc(sizeof(struct item));
        tmp->next=p;
        int n;
        fscanf(items,"%d",&p->tnum);
        n=p->tnum;
        for(int t=0;t<n;t++)
        {
            if(t==0)
            {
                fscanf(items," %s %s %f %d %d %d %s",p->itemname,p->type,&p->uprice[t],&p->info[t][0],&p->info[t][1],&p->info[t][2],p->itemlab[t]);
            }else
            {
                fscanf(items,"\n %d %s %s %f %d %d %d %s",&p->tnum,p->itemname,p->type,&p->uprice[t],&p->info[t][0],&p->info[t][1],&p->info[t][2],p->itemlab[t]);
            }
        }
        tmp=p;
        tmp->next=NULL;
    }
    fclose(items);
    return ihead;
};

plink changeorders(plink head)
{
    FILE *change;
    change=fopen("allorders.txt","w");
    rewind(change);
    struct cell* p;
    p=head->next;
    while(p!=NULL)
    {
        if(p==head->next)
        {
            fprintf(change," %d %d %d %d %d %d %d %s %s %s %s %f %d %d %s %d %lf %s",p->dingdan,p->month,p->day,p->hour,p->minute,p->timesum,p->zhanghao,p->name,p->phone,p->type,p->itemname,p->uprice,p->rong,p->inum,p->beizhu,p->num,p->sum,p->itemlab);
        }
        else
        {
            fprintf(change,"\n %d %d %d %d %d %d %d %s %s %s %s %f %d %d %s %d %lf %s",p->dingdan,p->month,p->day,p->hour,p->minute,p->timesum,p->zhanghao,p->name,p->phone,p->type,p->itemname,p->uprice,p->rong,p->inum,p->beizhu,p->num,p->sum,p->itemlab);
        }
        p=p->next;
    }
    fclose(change);
    return head;
};

tlink changeitems(tlink ihead)
{
    FILE *change;
    change=fopen("allitems.txt","w");
    struct item* p;
    p=ihead->next;
    while(p!=NULL)
    {
        if(p==ihead->next)
        {
            int n=p->tnum;
            for(int t=0;t<n;t++)
            {
                if(t==0)
                {
                    fprintf(change," %d %s %s %f %d %d %d %s",p->tnum,p->itemname,p->type,p->uprice[t],p->info[t][0],p->info[t][1],p->info[t][2],p->itemlab[t]);
                }else
                {
                    fprintf(change,"\n %d %s %s %f %d %d %d %s",p->tnum,p->itemname,p->type,p->uprice[t],p->info[t][0],p->info[t][1],p->info[t][2],p->itemlab[t]);
                }
            }
        }
        else
        {
            int n=p->tnum;
            for(int t=0;t<n;t++)
            {
                fprintf(change,"\n %d %s %s %f %d %d %d %s",p->tnum,p->itemname,p->type,p->uprice[t],p->info[t][0],p->info[t][1],p->info[t][2],p->itemlab[t]);
            }
        }
        p=p->next;
    }
    fclose(change);
    return ihead;
};

void renew()
{
    FILE* fp;
    fp=fopen("yonghushu.txt","w+");
    int lll=0;
    fprintf(fp,"%d",lll);
    fclose(fp);
    fp=fopen("allaccounts.txt","w+");
    fclose(fp);
    fp=fopen("allorders.txt","w+");
    fclose(fp);
    fp=fopen("dingdanshu.txt","w+");
    fprintf(fp,"%d",lll);
    fclose(fp);
    fp=fopen("allitems.txt","w+");
    fclose(fp);
    printf("重置完成！");
}

int searchuser(int n)
{
    FILE* fp;
    fp=fopen("allaccounts.txt","r");
	int flag = 0;
	while (fgetc(fp)!=EOF)
	{
		fscanf(fp,"%d %d %s %d %f",&useraccount.number,&useraccount.password,useraccount.address,&useraccount.level,&useraccount.money);
		if (useraccount.number == n)
		{
			printf("\t\t\t\t\t请输入密码:");
			int q;
			scanf("%d", &q);
			if (useraccount.password == q)
			{
				printf("\t\t\t\t\t载入中.....");
				login1=1;
				login2=1;
				fclose(fp);
				sleep(1);
				system("cls");
				return 1;
			}
			else
			{
				printf("\t\t\t\t\t密码错误,请重试！\n");
				fclose(fp);
					return 0;
			}
		}
	}
	printf("\t\t\t\t\t未找到用户\n");
	fclose(fp);
	return 0;
}

int searchmanager(int n)
{
   FILE* fp;
    fp=fopen("manager.txt","r");
	struct account a;
	int flag = 0;
	while (fgetc(fp)!=EOF)
	{
		fscanf(fp,"%d %d",&a.number,&a.password);
		if (a.number == n)
		{
			printf("\t\t\t\t\t请输入密码:");
			int q;
			scanf("%d", &q);
			if (a.password == q)
			{
				printf("\t\t\t\t\t载入中.....");
				login1 = 1;
				login2=1;
				fclose(fp);
				sleep(1);
				system("cls");
				return 1;
			}
			else
			{
				printf("\t\t\t\t\t密码错误,请重试！\n");
				fclose(fp);
					return 0;
			}
		}
	}
	printf("\t\t\t\t\t未找到用户\n");
	fclose(fp);
	return 0;
}

plink addition(plink head,tlink ihead)
{
    char type1[10]="酒",type2[10]="饮料";
    int tmpplus;
    struct cell *tmp,*p;
    struct item *p00;
    char judge[100],judge1[100];
    int bo=0,t,po,ty,tt,tt1,count;
    p00=ihead;
    p=head;
    tmp=(struct cell *)malloc(sizeof(struct cell));
    while(p->next!=NULL)
        p=p->next;
    p->next=tmp;
    FILE* dopen;
    dopen=fopen("dingdanshu.txt","r");
    fscanf(dopen,"%d",&count);
    fclose(dopen);
    dopen=fopen("dingdanshu.txt","w");
    count++;
    fprintf(dopen,"%d",count);
    fclose(dopen);
    count=count+1000000;
    tmp->dingdan=count;                       //订单编号
    printf("欢迎进入订单添加栏目 o(*≧▽≦)ツ┏━┓\n");
    printf("一、请输入订单日期:\n");               //以下六行是订单日期
    while(1)
    {
        printf("月/日:");
        while(1)
        {
            scanf("%s",judge);
            scanf("%s",judge1);
            tt=strlen(judge);
            tt1=strlen(judge1);
            bo=0;
            for(ty=0;ty<tt;ty++)
            {
                if(judge[ty]>'9'||judge[ty]<'0')
                    bo=1;
            }
            for(ty=0;ty<tt1;ty++)
            {
                if(judge1[ty]>'9'||judge1[ty]<'0')
                    bo=1;
            }
            if(bo==1)
            {
                printf("输入数据有误，请输入纯数字：\n");
            }
            else
                break;
        }
        tmp->month=atoi(judge);
        tmp->day=atoi(judge1);
        if(tmp->month==1||tmp->month==3||tmp->month==5||tmp->month==7||tmp->month==8||tmp->month==10||tmp->month==12)
        {
            if(tmp->day>0&&tmp->day<=31)
                break;
            else
                printf("输入日期有误，请检查后重新输入哦\n");
        }
        else if(tmp->month==4||tmp->month==6||tmp->month==9||tmp->month==11)
        {
            if(tmp->day>0&&tmp->day<=30)
                break;
            else
                printf("输入日期有误，请检查后重新输入哦\n");
        }
        else if(tmp->month==2)
        {
            if(tmp->day>0&&tmp->day<=28)
                break;
            else
                printf("输入日期有误，请检查后重新输入哦\n");
        }
        else
            printf("输入日期有误，请检查后重新输入哦\n");
    }
    while(1)
    {
        printf("时/分:");
        while(1)
        {
            scanf("%s",judge);
            scanf("%s",judge1);
            tt=strlen(judge);
            tt1=strlen(judge1);
            bo=0;
            for(ty=0;ty<tt;ty++)
            {
                if(judge[ty]>'9'||judge[ty]<'0')
                    bo=1;
            }
            for(ty=0;ty<tt1;ty++)
            {
                if(judge1[ty]>'9'||judge1[ty]<'0')
                    bo=1;
            }
            if(bo==1)
            {
                printf("输入数据有误，请输入纯数字：\n");
            }
            else
                break;
        }
        tmp->hour=atoi(judge);
        tmp->minute=atoi(judge1);
        if(tmp->hour>=0&&tmp->hour<=23&&tmp->minute>=0&&tmp->minute<=59)
            break;
        else
            printf("输入时间有误，请检查后重新输入哦\n");
    }
    tmp->timesum=tmp->minute+(tmp->hour)*60+(tmp->day-1)*1440;
    for(int i=1;i<tmp->month;i++)
    {
        if(i==1||i==3||i==5||i==7||i==8||i==10||i==12)
            tmp->timesum+=31*1440;
        else if(i==2)
            tmp->timesum+=28*1440;
        else
            tmp->timesum+=30*1440;
    }
    getchar();
    while(1)
    {
        printf("二、请输入网点代理人姓名:\n");             //网点代理人姓名
        gets(tmp->name);
        if(strlen(tmp->name)<=39)
            break;
        else
            printf("网点代理人姓名的字数超出限制，请重新输入哦\n");
    }
    while(1)
    {
            printf("三、请输入用户账号:\n");              //网点地址
            gets(judge);
            tt=strlen(judge);
            bo=0;
            for(ty=0;ty<tt;ty++)
            {
                if(judge[ty]>'9'||judge[ty]<'0')
                    bo=1;
            }
            if(bo==1)
            {
                printf("输入数据有误，请输入纯数字：\n");
                continue;
            }
            tmp->zhanghao=atoi(judge);
            FILE* fp;
            fp=fopen("allaccounts.txt","r");
            bo=1;
            while (fgetc(fp)!=EOF)
	        {
		       fscanf(fp,"%d %d %s %d %f",&useraccount.number,&useraccount.password,useraccount.address,&useraccount.level,&useraccount.money);
		       if (useraccount.number == tmp->zhanghao)
		       {
                   tmpplus=useraccount.money;
                   bo=0;
                   break;
               }
             }
             if(bo==0)
             {
                 break;
             }
	         printf("未找到对应账号，请重试。\n");
	         fclose(fp);
    }
    printf("四、请输入网点代理人电话:\n");        //网点代理人电话
    while(1)
    {
        gets(tmp->phone);
        tt=strlen(tmp->phone);
        bo=0;
        for(ty=0;ty<tt;ty++)
        {
            if(tmp->phone[ty]>'9'||tmp->phone[ty]<'0')
                bo=1;
        }
        if(bo==1)
        {
            printf("输入数据有误，请输入纯数字：\n");
        }
        else
            break;
    }
    printf("五、请输入商品名称:\n");              //商品名字
    while(1)
    {
        gets(tmp->itemname);
        p00=ihead;
        bo=0;
        while(p00->next!=NULL)
      {
        p00=p00->next;
        if(strcmp(p00->itemname,tmp->itemname)==0)
        {
            bo=1;
            break;
        }
      }
      if(bo==1)
        break;
      else
        printf("商品名称输入有误，未找到该商品，请再次输入：\n");
    }
    strcpy(tmp->type,p00->type);
    printf("六、请选择你要批发商品的单箱种类\n");
    for(t=0;t<p00->tnum;t++)
    {
        printf("%d、%d件/箱 %d毫升/件 (价格：%.2f/箱  库存：%d)\n",t+1,p00->info[t][0],p00->info[t][1],p00->uprice[t],p00->info[t][2]);
    }
    printf("请选择批发的单箱种类（按编号输入）：");
    bo=0;
    while(1)
    {
        while(1)
        {
            gets(judge);
            tt=strlen(judge);
            bo=0;
            for(ty=0;ty<tt;ty++)
            {
                if(judge[ty]>'9'||judge[ty]<'0')
                    bo=1;
            }
            if(bo==1)
            {
                printf("输入数据有误，请输入纯数字：\n");
            }
            else
                break;
        }
        po=atoi(judge);
        for(t=0;t<p00->tnum;t++)
        {
            if(po==t+1)
            {
                tmp->uprice=p00->uprice[t];
                bo=1;
                break;
            }
        }
        if(bo==1)
            break;
        else
            printf("输入种类有误，请按编号重新输入：");
    }
    printf("七、请输入商品数量:\n");              //商品数量
    while(1)
    {
        while(1)
        {
            gets(judge);
            tt=strlen(judge);
            bo=0;
            for(ty=0;ty<tt;ty++)
            {
                if(judge[ty]>'9'||judge[ty]<'0')
                    bo=1;
            }
            if(bo==1)
            {
                printf("输入数据有误，请输入纯数字：\n");
            }
            else
                break;
        }
        tmp->num=atoi(judge);
        if((p00->info[po-1][2])-(tmp->num)>=0)
            break;
        else
            printf("批发数量超过库存，批发失败，请重新选择批发数量：\n");
    }
    p00->info[po-1][2]=(p00->info[po-1][2])-(tmp->num);
    tmp->rong=p00->info[po-1][1];
    tmp->inum=p00->info[po-1][0];
    tmp->sum=tmp->uprice*tmp->num;            //该订单的总金额
    sumplus+=tmp->sum;
    if(tmpplus+tmp->sum>=5000)
    {
        tmp->beizhu[0]='A';
        tmp->beizhu[1]='\0';
    }
    else if(tmpplus+tmp->sum>=2000)
    {
        tmp->beizhu[0]='B';
        tmp->beizhu[1]='\0';
    }
    else
    {
        tmp->beizhu[0]='C';
        tmp->beizhu[1]='\0';
    }
    tmp->next=NULL;
    strcpy(tmp->itemlab,p00->itemlab[po-1]);
    printf("恭喜你，订单添加成功! (o゜▽゜)o☆[BINGO!]");
    return head;
}

plink correct(plink head,tlink ihead)
{
    int key;
    char judge[100],judge1[100];
    int bo=0,t,po,ty,tt,tt1,count;
    if(head->next==NULL)
        printf("系统中还没有数据哦\n");
    else
    {
        printf("请输入您要修改的订单的编号:");
        scanf("%d",&key);
        plink p0,p;
        p0=head;p=head->next;
        while(p!=NULL)
        {
            if(p->dingdan!=key)
            {
                p0=p;p=p->next;
                continue;
            }
            else
            {
                tlink p00;
                p00=ihead->next;
                while(p00!=NULL)
                {
                    if(strcmp(p00->itemname,p->itemname)==0)
                        break;
                    p00=p00->next;
                }
                int po;
                for(po=0;po<p00->tnum;po++)
                    if(strcmp(p00->itemlab[po],p->itemlab)==0)
                        break;
                po=po+1;
                int n;
                printf("1.订单日期\n");
                printf("2.网点代理人姓名\n");
                printf("3.网点代理人电话\n");
                printf("4.商品名称\n");
                printf("5.商品组合\n");
                printf("6.商品数量\n");
                printf("0.修改完成\n");
                printf("请输入要修改的项目对应的编号：");
                scanf("%d",&n);
                while(n!=0)
                {
                    if(n==1)
                    {
                        int a,b,c,d;
                        while(1)
                        {
                            printf("请输入月/日：");
                            while(1)
                            {
                                scanf("%s",judge);
                                scanf("%s",judge1);
                                tt=strlen(judge);
                                tt1=strlen(judge1);
                                bo=0;
                                for(ty=0;ty<tt;ty++)
                                {
                                    if(judge[ty]>'9'||judge[ty]<'0')
                                        bo=1;
                                }
                                for(ty=0;ty<tt1;ty++)
                                {
                                    if(judge1[ty]>'9'||judge1[ty]<'0')
                                        bo=1;
                                }
                                if(bo==1)
                                {
                                    printf("输入数据有误，请输入纯数字：\n");
                                }
                                else
                                    break;
                            }
                            a=atoi(judge);
                            b=atoi(judge1);
                            if(a<1||a>12)
                            {
                                printf("输入日期有误，请检查后重新输入哦\n");
                                continue;
                            }
                            else
                            {
                                if(a==1||a==3||a==5||a==7||a==8||a==10||a==12)
                                {
                                    if(1<=b&&b<=31)
                                    {
                                        p->month=a;
                                        p->day=b;
                                        break;
                                    }
                                    else
                                    {
                                        printf("输入日期有误，请检查后重新输入哦\n");
                                        continue;
                                    }
                                }
                                else if(a==4||a==6||a==9||a==11)
                                {
                                    if(1<=b&&b<=30)
                                    {
                                        p->month=a;
                                        p->day=b;
                                        break;
                                    }
                                    else
                                    {
                                        printf("输入日期有误，请检查后重新输入哦\n");
                                        continue;
                                    }
                                }
                                else if(a==2)
                                {
                                    if(1<=b&&b<=28)
                                    {
                                        p->month=a;
                                        p->day=b;
                                        break;
                                    }
                                    else
                                    {
                                        printf("输入日期有误，请检查后重新输入哦\n");
                                        continue;
                                    }
                                }
                            }
                        }
                        while(1)
                        {
                            printf("请输入时/分:");
                            while(1)
                            {
                                scanf("%s",judge);
                                scanf("%s",judge1);
                                tt=strlen(judge);
                                tt1=strlen(judge1);
                                bo=0;
                                for(ty=0;ty<tt;ty++)
                                {
                                    if(judge[ty]>'9'||judge[ty]<'0')
                                        bo=1;
                                }
                                for(ty=0;ty<tt1;ty++)
                                {
                                    if(judge1[ty]>'9'||judge1[ty]<'0')
                                        bo=1;
                                }
                                if(bo==1)
                                {
                                    printf("输入数据有误，请输入纯数字：\n");
                                }
                                else
                                    break;
                            }
                            c=atoi(judge);
                            d=atoi(judge1);
                            if(0<=c&&c<=23&&0<=d&&d<=59)
                            {
                                p->hour=c;
                                p->minute=d;
                                break;
                            }
                            else
                            {
                                printf("输入日期有误，请检查后重新输入哦\n");
                                continue;
                            }
                        }
                        p->timesum=p->minute+(p->hour)*60+(p->day-1)*1440;
                        for(int i=1;i<p->month;i++)
                        {
                            if(i==1||i==3||i==5||i==7||i==8||i==10||i==12)
                                p->timesum+=31*1440;
                            else if(i==2)
                                p->timesum+=28*1440;
                            else
                                p->timesum+=30*1440;
                        }
                        printf("修改后的订单记录为：\n");
                        char h[13][50]={"订单编号","日期","代理人姓名","地址","电话","商品种类","商品名字","单价(元/箱)","商品备注","数量","总金额","单箱件数","单件容量"};
                        printf("%-8s\t%-18s\t%-25s\t%-14s\t%-10s\t%-14s\t%-10s\t%-10s\t%-13s\t%-10s\t%-6s\t%-10s\t\n",h[0],h[1],h[2],h[4],h[5],h[6],h[11],h[12],h[7],h[8],h[9],h[10]);
                        printf("%-8d\t%02d月%02d日%02d时%02d分\t%-25s\t%-14s\t%-10s\t%-14s\t%-10d\t%-10d\t%-13.2f\t%-10s\t%-6d\t%-10.2f\t\n",p->dingdan,p->month,p->day,p->hour,p->minute,p->name,p->phone,p->type,p->itemname,p->inum,p->rong,p->uprice,p->beizhu,p->num,p->sum);
                    }
                    else if(n==2)
                    {
                        char e[40];
                        while(1)
                        {
                            printf("请输入新的网点代理人姓名：");
                            scanf("%s",e);
                            if(strlen(e)<=40)
                            {
                                strcpy(p->name,e);
                                break;
                            }
                            else
                            {
                                printf("网点代理人姓名字数超出限制，请重新输入哦\n");
                                continue;
                            }
                        }
                        printf("修改后的订单记录为：\n");
                        char h[13][50]={"订单编号","日期","代理人姓名","地址","电话","商品种类","商品名字","单价(元/箱)","商品备注","数量","总金额","单箱件数","单件容量"};
                        printf("%-8s\t%-18s\t%-25s\t%-14s\t%-10s\t%-14s\t%-10s\t%-10s\t%-13s\t%-10s\t%-6s\t%-10s\t\n",h[0],h[1],h[2],h[4],h[5],h[6],h[11],h[12],h[7],h[8],h[9],h[10]);
                        printf("%-8d\t%02d月%02d日%02d时%02d分\t%-25s\t%-14s\t%-10s\t%-14s\t%-10d\t%-10d\t%-13.2f\t%-10s\t%-6d\t%-10.2f\t\n",p->dingdan,p->month,p->day,p->hour,p->minute,p->name,p->phone,p->type,p->itemname,p->inum,p->rong,p->uprice,p->beizhu,p->num,p->sum);
                    }
                    else if(n==3)
                        {
                            char g[20];
                            int i;
                            while(1)
                            {
                                printf("请输入新的网点代理人电话：");
                                scanf("%s",g);
                                if(strlen(g)<=20)
                                {
                                    for(i=0;i<strlen(g);i++)
                                        if(g[i]<'0'||g[i]>'9')
                                            break;
                                    if(i==strlen(g))
                                    {
                                        strcpy(p->phone,g);
                                        break;
                                    }
                                    else
                                    {
                                        printf("网点代理人电话格式错误，请重新输入哦\n");
                                        continue;
                                    }
                                }
                                else
                                {
                                    printf("网点代理人电话长度超出限制，请重新输入哦\n");
                                    continue;
                                }
                            }
                            printf("修改后的订单记录为：\n");
                            char h[13][50]={"订单编号","日期","代理人姓名","地址","电话","商品种类","商品名字","单价(元/箱)","商品备注","数量","总金额","单箱件数","单件容量"};
                            printf("%-8s\t%-18s\t%-25s\t%-14s\t%-10s\t%-14s\t%-10s\t%-10s\t%-13s\t%-10s\t%-6s\t%-10s\t\n",h[0],h[1],h[2],h[4],h[5],h[6],h[11],h[12],h[7],h[8],h[9],h[10]);
                            printf("%-8d\t%02d月%02d日%02d时%02d分\t%-25s\t%-14s\t%-10s\t%-14s\t%-10d\t%-10d\t%-13.2f\t%-10s\t%-6d\t%-10.2f\t\n",p->dingdan,p->month,p->day,p->hour,p->minute,p->name,p->phone,p->type,p->itemname,p->inum,p->rong,p->uprice,p->beizhu,p->num,p->sum);
                        }
                    else if(n==4)
                    {
                        tlink q;
                        char ss[40];
                        sumplus-=p->sum;
                        p00->info[po-1][2]+=p->num;
                        while(1)
                        {
                            printf("请输入新的商品名称：");
                            scanf("%s",ss);
                            q=ihead->next;
                            while(q!=NULL)
                            {
                                if(strcmp(q->itemname,ss)==0)
                                    break;
                                q=q->next;
                            }
                            if(q==NULL)
                            {
                                printf("未找到商品，请重新输入！");
                                continue;
                            }
                            else
                                break;
                        }
                        strcpy(p->itemname,ss);
                        strcpy(p->type,q->type);
                        p00=q;
                        printf("请选择新商品的单箱种类\n");
                        for(t=0;t<p00->tnum;t++)
                        {
                            printf("%d、%d件/箱 %d毫升/件 (价格：%.2f/箱  库存：%d)\n",t+1,p00->info[t][0],p00->info[t][1],p00->uprice[t],p00->info[t][2]);
                        }
                        printf("请选择批发的单箱种类（按编号输入）：");
                        bo=0;
                        while(1)
                        {
                            while(1)
                            {
                                scanf("%s",judge);
                                tt=strlen(judge);
                                bo=0;
                                for(ty=0;ty<tt;ty++)
                                {
                                    if(judge[ty]>'9'||judge[ty]<'0')
                                        bo=1;
                                }
                                if(bo==1)
                                {
                                    printf("输入数据有误，请输入纯数字：\n");
                                }
                                else
                                    break;
                            }
                            po=atoi(judge);
                            for(t=0;t<p00->tnum;t++)
                            {
                                if(po==t+1)
                                {
                                    p->uprice=p00->uprice[t];
                                    bo=1;
                                    break;
                                }
                            }
                            if(bo==1)
                                break;
                            else
                                printf("输入种类有误，请按编号重新输入：");
                        }
                        printf("请输入新商品批发数量:\n");              //商品数量
                        while(1)
                        {
                            while(1)
                            {
                                scanf("%s",judge);
                                tt=strlen(judge);
                                bo=0;
                                for(ty=0;ty<tt;ty++)
                                {
                                    if(judge[ty]>'9'||judge[ty]<'0')
                                        bo=1;
                                }
                                if(bo==1)
                                {
                                    printf("输入数据有误，请输入纯数字：\n");
                                }
                                else
                                    break;
                            }
                            p->num=atoi(judge);
                            if((p00->info[po-1][2])-(p->num)>=0)
                                break;
                            else
                                printf("批发数量超过库存，批发失败，请重新选择批发数量：\n");
                        }
                        p00->info[po-1][2]=(p00->info[po-1][2])-(p->num);
                        p->sum=p->num*p->uprice;
                        sumplus+=p->sum;
                        p->rong=p00->info[po-1][1];
                        p->inum=p00->info[po-1][0];
                        strcpy(p->itemlab,p00->itemlab[po-1]);
                        printf("修改后的订单记录为：\n");
                        char h[13][50]={"订单编号","日期","代理人姓名","地址","电话","商品种类","商品名字","单价(元/箱)","商品备注","数量","总金额","单箱件数","单件容量"};
                        printf("%-8s\t%-18s\t%-25s\t%-14s\t%-10s\t%-14s\t%-10s\t%-10s\t%-13s\t%-10s\t%-6s\t%-10s\t\n",h[0],h[1],h[2],h[4],h[5],h[6],h[11],h[12],h[7],h[8],h[9],h[10]);
                        printf("%-8d\t%02d月%02d日%02d时%02d分\t%-25s\t%-14s\t%-10s\t%-14s\t%-10d\t%-10d\t%-13.2f\t%-10s\t%-6d\t%-10.2f\t\n",p->dingdan,p->month,p->day,p->hour,p->minute,p->name,p->phone,p->type,p->itemname,p->inum,p->rong,p->uprice,p->beizhu,p->num,p->sum);
                    }
                    else if(n==5)
                    {
                        sumplus-=p->num*p->uprice;
                        p00->info[po-1][2]+=p->num;                   //先把商品数量加回去
                        printf("请选择你要批发商品的单箱种类（商品数量已被重置）\n");
                        for(t=0;t<p00->tnum;t++)
                        {
                            printf("%d、%d件/箱 %d毫升/件 (价格：%.2f/箱  库存：%d)\n",t+1,p00->info[t][0],p00->info[t][1],p00->uprice[t],p00->info[t][2]);
                        }
                        printf("请选择新的单箱种类（按编号输入）：");
                        bo=0;
                        while(1)
                        {
                            while(1)
                            {
                                getchar();
                                gets(judge);
                                tt=strlen(judge);
                                bo=0;
                                for(ty=0;ty<tt;ty++)
                                {
                                    if(judge[ty]>'9'||judge[ty]<'0')
                                        bo=1;
                                }
                                if(bo==1)
                                {
                                    printf("输入数据有误，请输入纯数字：\n");
                                }
                                else
                                    break;
                            }
                            po=atoi(judge);
                            for(t=0;t<p00->tnum;t++)
                            {
                                if(po==t+1)
                                {
                                    p->uprice=p00->uprice[t];
                                    bo=1;
                                    break;
                                }
                            }
                            if(bo==1)
                                break;
                            else
                                printf("输入种类有误，请按编号重新输入：");
                        }
                        printf("请输入商品数量:\n");              //商品数量
                        while(1)
                        {
                            while(1)
                            {
                                gets(judge);
                                tt=strlen(judge);
                                bo=0;
                                for(ty=0;ty<tt;ty++)
                                {
                                    if(judge[ty]>'9'||judge[ty]<'0')
                                        bo=1;
                                }
                                if(bo==1)
                                {
                                    printf("输入数据有误，请输入纯数字：\n");
                                }
                                else
                                    break;
                            }
                            p->num=atoi(judge);
                            if((p00->info[po-1][2])-(p->num)>=0)
                                break;
                            else
                                printf("批发数量超过库存，批发失败，请重新选择批发数量：\n");
                        }
                        p->rong=p00->info[po-1][1];
                        p->inum=p00->info[po-1][0];
                        p00->info[po-1][2]-=p->num;
                        p->sum=p->num*p->uprice;
                        sumplus+=p->sum;
                        strcpy(p->itemlab,p00->itemlab[po-1]);
                        printf("修改后的订单记录为：\n");
                        char h[13][50]={"订单编号","日期","代理人姓名","地址","电话","商品种类","商品名字","单价(元/箱)","商品备注","数量","总金额","单箱件数","单件容量"};
                        printf("%-8s\t%-18s\t%-25s\t%-14s\t%-10s\t%-14s\t%-10s\t%-10s\t%-13s\t%-10s\t%-6s\t%-10s\t\n",h[0],h[1],h[2],h[4],h[5],h[6],h[11],h[12],h[7],h[8],h[9],h[10]);
                        printf("%-8d\t%02d月%02d日%02d时%02d分\t%-25s\t%-14s\t%-10s\t%-14s\t%-10d\t%-10d\t%-13.2f\t%-10s\t%-6d\t%-10.2f\t\n",p->dingdan,p->month,p->day,p->hour,p->minute,p->name,p->phone,p->type,p->itemname,p->inum,p->rong,p->uprice,p->beizhu,p->num,p->sum);
                    }
                    else if(n==6)
                    {
                        sumplus-=p->uprice*p->num;
                        p00->info[po-1][2]+=p->num;
                        while(1)
                        {
                            printf("请输入新的商品数量:");
                            while(1)
                            {
                                scanf("%s",judge);
                                tt=strlen(judge);
                                bo=0;
                                for(ty=0;ty<tt;ty++)
                                {
                                    if(judge[ty]>'9'||judge[ty]<'0')
                                        bo=1;
                                }
                                if(bo==1)
                                {
                                    printf("输入数据有误，请输入纯数字：\n");
                                }
                                else
                                    break;
                            }
                            p->num=atoi(judge);
                            if(p->num<=p00->info[po-1][2])
                            {
                                p00->info[po-1][2]-=p->num;
                                break;
                            }
                            else
                            {
                                printf("该商品的库存为：%d\n",p00->info[po-1][2]);
                                printf("批发数量超过库存，批发失败\n");
                                continue;
                            }
                        }
                        sumplus+=p->uprice*p->num;
                        p->sum=p->num*p->uprice;
                        printf("修改后的订单记录为：\n");
                        char h[13][50]={"订单编号","日期","代理人姓名","地址","电话","商品种类","商品名字","单价(元/箱)","商品备注","数量","总金额","单箱件数","单件容量"};
                        printf("%-8s\t%-18s\t%-25s\t%-14s\t%-10s\t%-14s\t%-10s\t%-10s\t%-13s\t%-10s\t%-6s\t%-10s\t\n",h[0],h[1],h[2],h[4],h[5],h[6],h[11],h[12],h[7],h[8],h[9],h[10]);
                        printf("%-8d\t%02d月%02d日%02d时%02d分\t%-25s\t%-14s\t%-10s\t%-14s\t%-10d\t%-10d\t%-13.2f\t%-10s\t%-6d\t%-10.2f\t\n",p->dingdan,p->month,p->day,p->hour,p->minute,p->name,p->phone,p->type,p->itemname,p->inum,p->rong,p->uprice,p->beizhu,p->num,p->sum);
                    }
                    else
                    {
                        printf("请输入正确的数字编号！\n");
                        printf("请重新输入：");
                        scanf("%d",&n);
                        continue;
                    }
                    printf("1.订单日期\n");
                    printf("2.网点代理人姓名\n");
                    printf("3.网点代理人电话\n");
                    printf("4.商品名称\n");
                    printf("5.商品组合\n");
                    printf("6.商品数量\n");
                    printf("0.修改完成\n");
                    printf("请输入要修改的项目对应的编号：");
                    scanf("%d",&n);
                }
                if(n==0)
                    break;
            }
        }
        if(p==NULL)
        printf("没有找到相应的订单编号哦\n");
    }
    return head;
}

plink fromto(plink head)
{
    int month1,month2,day1,day2,hour1,hour2,minute1,minute2,judge=0;
    int timesummin,timesummax;
    while(1)
    {
        printf("请输入起始时间范围(按照月/日/时/分，用空格分开):\n");
        scanf("%d%d%d%d",&month1,&day1,&hour1,&minute1);
        printf("请输入终止时间范围(按照月/日/时/分，用空格分开):\n");
        scanf("%d%d%d%d",&month2,&day2,&hour2,&minute2);
        timesummin=minute1+(hour1)*60+(day1-1)*1440;
        for(int i=1;i<month1;i++)
        {
            if(i==1||i==3||i==5||i==7||i==8||i==10||i==12)
                timesummin+=31*1440;
            else if(i==2)
                timesummin+=28*1440;
            else
                timesummin+=30*1440;
        }
        timesummax=minute2+(hour2)*60+(day2-1)*1440;
        for(int i=1;i<month2;i++)
        {
            if(i==1||i==3||i==5||i==7||i==8||i==10||i==12)
                timesummax+=31*1440;
            else if(i==2)
                timesummax+=28*1440;
            else
                timesummax+=30*1440;
        }
        if(timesummin>timesummax)
        {
            printf("起始时间不可以超过终止时间！请重新输入\n");
            continue;
        }
        else
            break;
    }
    plink p=head->next;
    plink tmp,head0;
    tmp=(plink)malloc(sizeof(struct cell));
    tmp->timesum=-1;
    tmp->next=NULL;
    head0=tmp;
    while(p!=NULL)
    {
        if(p->timesum>=timesummin&&p->timesum<=timesummax)
        {
            plink q;
            q=(plink)malloc(sizeof(struct cell));
            q->zhanghao=useraccount.number;
            q->dingdan=p->dingdan;
            q->month=p->month;
            q->day=p->day;
            q->hour=p->hour;
            q->minute=p->minute;
            q->uprice=p->uprice;
            q->num=p->num;
            q->timesum=p->timesum;
            q->sum=p->sum;
            q->zhanghao=p->zhanghao;
            q->rong=p->rong;
            q->inum=p->inum;
            strcpy(q->itemlab,p->itemlab);
            strcpy(q->name,p->name);
            strcpy(q->phone,p->phone);
            strcpy(q->type,p->type);
            strcpy(q->itemname,p->itemname);
            strcpy(q->beizhu,p->beizhu);
            q->next=NULL;
            tmp->next=q;
            tmp=q;
            judge=1;
        }
        p=p->next;
    }
    if(judge==0)
        printf("没有符合的订单记录\n");
    else
    {
        head0=dateprint(head0);
                printall(head0);
    }
    return head;
}

void printall(plink head)
{
    if(head->next==NULL)
        printf("系统中还没有数据哟\n");
    else
    {
        char h[10][50]={"编号","日期","姓名","电话","商品种类","商品名称","单价(元/箱)","赠品","数量","总金额"};
        printf("%-7s\t %-15s\t%-8s\t%-10s\t%-9s%-11s\t%-12s%-5s%-6s%-6s\n",h[0],h[1],h[2],h[3],h[4],h[5],h[6],h[7],h[8],h[9]);
        plink p;
        p=head->next;
        while(p!=NULL)
        {
            printf("%-8d %02d月%02d日%02d时%02d分\t%-8s\t%-11s\t%-2s\t %-14s\t%-12.2f%-5s%-6d%-10.2f\t\n",p->dingdan,p->month,p->day,p->hour,p->minute,p->name,p->phone,p->type,p->itemname,p->uprice,p->beizhu,p->num,p->sum);
            //printf("timesum=%d\n",p->timesum);
            p=p->next;
        }
    }
}

void release(plink head)
{
    plink tmp=head;
    while(tmp!=NULL)
    {
        head=head->next;
        free(tmp);
        tmp=head;
    }
}

plink del(plink head,tlink ihead)
{
    int key;
    printf("请输入你要删除的订单编号:");
    scanf("%d",&key);
    if(head->next==NULL)
        printf("系统中还没有数据哦\n");
    else
    {
        plink p0,p;
        p0=head;p=head->next;
        int judge0=0;
        while(p!=NULL)
        {
            if(p->dingdan!=key)
            {
                p0=p;p=p->next;
                continue;
            }
            else
            {
                tlink p00;
                p00=ihead->next;
                while(p00!=NULL)
                {
                    if(strcmp(p00->itemname,p->itemname)==0)
                        break;
                    p00=p00->next;
                }
                int po;
                for(po=0;po<p00->tnum;po++)
                    if(strcmp(p00->itemlab[po],p->itemlab)==0)
                        break;
                po=po+1;
                printf("您要删除的订单信息如下：\n");
                char h[10][50]={"编号","日期","姓名","电话","商品种类","商品名称","单价(元/箱)","赠品","数量","总金额"};
        printf("%-7s\t %-15s\t%-8s\t%-10s\t%-9s%-11s\t%-12s%-5s%-6s%-6s\n",h[0],h[1],h[2],h[3],h[4],h[5],h[6],h[7],h[8],h[9]);
                printf("%-8d %02d月%02d日%02d时%02d分\t%-8s\t%-11s\t%-2s\t %-14s\t%-12.2f%-5s%-6d%-10.2f\t\n",p->dingdan,p->month,p->day,p->hour,p->minute,p->name,p->phone,p->type,p->itemname,p->uprice,p->beizhu,p->num,p->sum);
                printf("请按下数字1以继续删除,按下数字0取消删除操作:");
                //sumplus-=p->sum;
                //p00->info[po-1][2]+=p->num;
                int judge;
                scanf("%d",&judge);
                if(judge)
                {
                    plink tmp;
                    tmp=p;
                    sumplus-=p->sum;
                    p=p->next;
                    p0->next=p;
                    free(tmp);
                    judge0=1;
                    break;
                }
                else
                    break;
            }
        }
        if(p==NULL&&judge0==0)
            printf("没有找到相应的订单编号\n");
    }
        return head;
}

plink itemprint(plink head)
{
    plink temp,head0;
    temp=(plink)malloc(sizeof(struct cell));
    temp->dingdan=1;
    temp->timesum=-1;
    temp->sum=99999999999;
    temp->next=NULL;
    head0=temp;
    int k=0;
    printf("请输入商品名称：");
    char itemname1[40];
    struct cell*tmp;
    scanf("%s",itemname1);
    tmp=(struct cell *)malloc(sizeof(struct cell));
    tmp=head;
    if(tmp->next==NULL){printf("未找到目标订单！");return head;};
    tmp=tmp->next;
    while(tmp!=NULL)
        {
           if(strcmp(tmp->itemname,itemname1)==0)
           {
                plink q;
                q=(plink)malloc(sizeof(struct cell));
                q->zhanghao=useraccount.number;
                q->dingdan=tmp->dingdan;
                q->month=tmp->month;
                q->day=tmp->day;
                q->hour=tmp->hour;
                q->minute=tmp->minute;
                q->uprice=tmp->uprice;
                q->num=tmp->num;
                q->timesum=tmp->timesum;
                q->sum=tmp->sum;
                q->zhanghao=tmp->zhanghao;
                q->rong=tmp->rong;
                q->inum=tmp->inum;
                strcpy(q->itemlab,tmp->itemlab);
                strcpy(q->name,tmp->name);
                strcpy(q->phone,tmp->phone);
                strcpy(q->type,tmp->type);
                strcpy(q->itemname,tmp->itemname);
                strcpy(q->beizhu,tmp->beizhu);
                q->next=NULL;
                temp->next=q;
                temp=q;
                k++;
                if(k==1)
                {
                    char h[10][50]={"编号","日期","姓名","电话","商品种类","商品名称","单价(元/箱)","赠品","数量","总金额"};
        printf("%-7s\t %-15s\t%-8s\t%-10s\t%-9s%-11s\t%-12s%-5s%-6s%-6s\n",h[0],h[1],h[2],h[3],h[4],h[5],h[6],h[7],h[8],h[9]);
                }
                printf("%-8d %02d月%02d日%02d时%02d分\t%-8s\t%-11s\t%-2s\t %-14s\t%-12.2f%-5s%-6d%-10.2f\t\n",tmp->dingdan,tmp->month,tmp->day,tmp->hour,tmp->minute,tmp->name,tmp->phone,tmp->type,tmp->itemname,tmp->uprice,tmp->beizhu,tmp->num,tmp->sum);
           }
           tmp=tmp->next;
        }
    if(k==0)
    {
        struct tt{
            char sta[100];
            struct tt* next;
        };
        typedef struct tt* ttk;
        ttk d1,d2;
        d2=(ttk)malloc(sizeof(struct tt));
        d2->next=NULL;
        d1=d2;
        plink s1=head->next;
        while(s1!=NULL)
        {
            if(editDistance(s1->itemname,itemname1)<=3)
            {
                ttk ddd=d1->next;
                while(ddd!=NULL)
                {
                    if(strcmp(ddd->sta,s1->itemname)==0)
                        break;
                    ddd=ddd->next;
                }
                if(ddd==NULL)
                {
                    ttk q;
                    q=(ttk)malloc(sizeof(struct tt));
                    strcpy(q->sta,s1->itemname);
                    q->next=NULL;
                    d2->next=q;
                    d2=q;
                }
            }
            s1=s1->next;
        }
        if(d1->next==NULL)
            printf("未找到相关商品!\n");
        else
        {
            printf("订单记录相关商品中未找到名为%s的商品,您可能想搜索的商品是：\n",itemname1);
            d1=d1->next;
            while(d1!=NULL)
            {
                printf("%s\n",d1->sta);
                d1=d1->next;
            }
            printf("请尝试重新搜索!\n");
        }
    }
    else
    {
        printf("按下1以按照时间排序,按下2以按照金额排序,按下0以结束操作:");
        int k;
        scanf("%d",&k);
        while(1)
        {
            if(k==1)
            {
                printf("按照日期排序后的订单记录如下：\n");
                head0=dateprint(head0);
                printall(head0);
                break;
            }
            else if(k==2)
            {
                printf("按照订单金额排序后的订单记录如下：\n");
                head0=moneyprint(head0);
                printall(head0);
                break;
            }
            else
            {
                printf("请输入正确的编号:");
                scanf("%d",&k);
                continue;
            }
        }
    }
    return head;
}

void itemdateprint(plink head)
{
    plink tmp,head0;
    tmp=(plink)malloc(sizeof(struct cell));
    tmp->dingdan=1;
    tmp->timesum=-1;
    tmp->next=NULL;
    head0=tmp;
    plink p=head->next;
    int judge0=0;
    char a[20];
    printf("请输入您要查询的客户姓名：");
    scanf("%s",a);
    if(p==NULL)
        printf("系统中还没有数据哦\n");
    else
    {
        while(p!=NULL)
        {
            int judge=strcmp(p->name,a);
            if(judge==0)
            {
                plink q;
                q=(plink)malloc(sizeof(struct cell));
                q->dingdan=p->dingdan;
                q->month=p->month;
                q->day=p->day;
                q->hour=p->hour;
                q->minute=p->minute;
                q->uprice=p->uprice;
                q->num=p->num;
                q->sum=p->sum;
                q->timesum=p->timesum;
                strcpy(q->name,p->name);
                strcpy(q->phone,p->phone);
                strcpy(q->type,p->type);
                strcpy(q->itemname,p->itemname);
                strcpy(q->beizhu,p->beizhu);
                q->next=NULL;
                tmp->next=q;
                tmp=q;
                judge0=1;
                p=p->next;
            }
            else
            {
                p=p->next;
                continue;
            }
        }
    }
    if(judge0)
    {
        printf("该客户的所有订单记录如下：\n");
        printall(head0);
        printf("按下数字1以按照日期来排序,按下数字0结束当前操作:");
        int s;
        scanf("%d",&s);
        if(s)
        {
            printf("按照日期排序后的订单记录如下：\n");
            head0=dateprint(head0);
            printall(head0);
        }
    }
    else
    {
        struct tt{
            char sta[100];
            struct tt* next;
        };
        typedef struct tt* ttk;
        ttk d1,d2;
        d2=(ttk)malloc(sizeof(struct tt));
        d2->next=NULL;
        d1=d2;
        plink s1=head->next;
        while(s1!=NULL)
        {
            if(editDistance(s1->name,a)<=3)
            {
                ttk ddd=d1->next;
                while(ddd!=NULL)
                {
                    if(strcmp(ddd->sta,s1->name)==0)
                        break;
                    ddd=ddd->next;
                }
                if(ddd==NULL)
                {
                    ttk q;
                    q=(ttk)malloc(sizeof(struct tt));
                    strcpy(q->sta,s1->name);
                    q->next=NULL;
                    d2->next=q;
                    d2=q;
                }
            }
            s1=s1->next;
        }
        if(d1->next==NULL)
            printf("未找到该客户!\n");
        else
        {
            printf("订单记录相关客户中未找到名为%s的客户,您可能想搜索的客户名字是：\n",a);
            d1=d1->next;
            while(d1!=NULL)
            {
                printf("%s\n",d1->sta);
                d1=d1->next;
            }
            printf("请尝试重新搜索!\n");
        }
    }
}

plink dateprint(plink head)
{
    struct cell* p,*p0,*r,*r0,*q;
    p=p0=r=r0=q=NULL;
    p=head;
    while(p!=NULL)
    {
        r=head;
        while(r->timesum<p->timesum&&r!=p)
        {
            r0=r;
            r=r->next;
        }
        if(p!=r)
        {
            q=p;
            p0->next=p->next;
            p=p0;
            if(p==head)
            {
                q->next=head;
                head=q;
            }
            else
            {
                q->next=r;
                r0->next=q;
            }
        }
        p0=p;
        p=p->next;
    }
    return head;
}

tlink addgoods(tlink ihead)
{
    tlink p7,p77;
    int n;
    char type3[10]="酒",type4[10]="饮料";
    char judge[100];
    int t,k1=0,tt,bo,ty,conquer=0;
    p7=ihead;
    getchar();
    while(p7->next!=NULL)
    {
        p7=p7->next;
        k1++;
    }
    p77=(tlink)malloc(sizeof(struct item));
    p7->next=p77;
    k1++;
    printf("欢迎进入商品添加栏目 o(*≧▽≦)ツ┏━┓\n");
    printf("请选择要进行的操作：\n1.增加新商品\n2.增加已有商品库存\n请输入数字编号:");
    scanf("%d",&n);
    while(1)
    {
        if(n==1)            //增加新商品
        {
            printf("一、请输入酒水名称：\n");
            while(1)
            {
                getchar();
                gets(p77->itemname);
                if(strlen(p77->itemname)<=39)
                    break;
                else
                    printf("酒水名称输入超出字数限制，请检查修改后重新输入：\n");
            }
            printf("二、请输入酒水类型（酒/饮料）：\n");
            while(1)
            {
                gets(p77->type);
                if(strcmp(p77->type,type3)==0||strcmp(p77->type,type4)==0)
                    break;
                else
                    printf("酒水类型输入有误，请按照规范重新输入：\n");
            }
            printf("三、请输入该酒水单箱的类型总数：\n");
            while(1)
            {
                while(1)
                {
                    gets(judge);
                    tt=strlen(judge);
                    bo=0;
                    for(ty=0;ty<tt;ty++)
                    {
                        if(judge[ty]>'9'||judge[ty]<'0')
                            bo=1;
                    }
                    if(bo==1)
                    {
                        printf("输入数据有误，请输入纯数字：\n");
                    }
                    else
                        break;
                }
                p77->tnum=atoi(judge);
                if(p77->tnum<=5&&p77->tnum>=1)
                    break;
                else
                    printf("输入数据大小有误，请检查修改后重新输入：\n");
            }
            printf("四、接下来请输入该酒水可供购买的单箱的各类型\n");
            for(t=0;t<(p77->tnum);t++)
            {
                printf("%d、请输入第%d种类型的相关数据\n",t+1,t+1);
                printf("（1）请输入单箱中单件的数量：");
                while(1)
                {
                    gets(judge);
                    tt=strlen(judge);
                    bo=0;
                    for(ty=0;ty<tt;ty++)
                    {
                        if(judge[ty]>'9'||judge[ty]<'0')
                            bo=1;
                    }
                    if(bo==1)
                    {
                        printf("输入数据有误，请输入纯数字：\n");
                    }
                    else
                        break;
                }
                p77->info[t][0]=atoi(judge);
                printf("（2）请输入单件的容量(毫升)：");
                while(1)
                {
                    gets(judge);
                    tt=strlen(judge);
                    bo=0;
                    for(ty=0;ty<tt;ty++)
                    {
                        if(judge[ty]>'9'||judge[ty]<'0')
                            bo=1;
                    }
                    if(bo==1)
                    {
                        printf("输入数据有误，请输入纯数字：\n");
                    }
                    else
                        break;
                }
                p77->info[t][1]=atoi(judge);
                printf("（3）请输入初始库存箱数：");
                while(1)
                {
                    gets(judge);
                    tt=strlen(judge);
                    bo=0;
                    for(ty=0;ty<tt;ty++)
                    {
                        if(judge[ty]>'9'||judge[ty]<'0')
                            bo=1;
                    }
                    if(bo==1)
                    {
                        printf("输入数据有误，请输入纯数字：\n");
                    }
                    else
                        break;
                }
                p77->info[t][2]=atoi(judge);
                printf("（4）请输入单箱的价格（人民币）：");
                while(1)
                {
                    conquer=0;
                    gets(judge);
                    tt=strlen(judge);
                    bo=0;
                    if(judge[0]=='.')
                        bo=1;
                    for(ty=0;ty<tt;ty++)
                    {
                        if((judge[ty]>'9'||judge[ty]<'0')&&judge[ty]!='.')
                            bo=1;
                        if(judge[ty]=='.')
                            conquer++;
                    }
                    if(conquer>1)
                        bo=1;
                    if(judge[tt-1]=='.')
                        bo=1;
                    if(bo==1)
                    {
                        printf("输入数据有误，请重新输入：\n");
                    }
                    else
                        break;
                }
                for(ty=0;ty<tt;ty++)
                    if(judge[ty]=='.')
                    break;
                if(ty==tt)
                    p77->uprice[t]=atoi(judge);
                else if(ty==tt-2)
                    p77->uprice[t]=atoi(judge)+(judge[ty+1]-'0')/10.0;
                else
                    p77->uprice[t]=atoi(judge)+(judge[ty+1]-'0')/10.0+(judge[ty+2]-'0')/100.0;
                p77->itemlab[t][2]=(char)('0'+k1%10);
                p77->itemlab[t][1]=(char)('0'+(k1/10)%10);
                p77->itemlab[t][0]=(char)('0'+(k1/100)%10);
                p77->itemlab[t][3]=(char)('1'+t);
                p77->itemlab[t][4]='\0';
            }
            getchar();
            p77->next=NULL;
            printf("恭喜你，商品添加成功! (o゜▽゜)o☆[BINGO!]");
            break;
        }
        else if(n==2)
        {
            char ss[40];
            printf("请输入商品名称：");
            scanf("%s",ss);
            tlink s=ihead->next;
            if(s==NULL)
                printf("还没有商品哦！");
            else
            {
                while(s!=NULL)
                {
                    if(strcmp(s->itemname,ss)==0)
                        break;
                    s=s->next;
                }
                if(s==NULL)
                    printf("没有找到对应的商品！");
                else
                {
                    printf("该商品的组合情况如下：\n");
                    for(int t=0;t<s->tnum;t++)
                        printf("%d、%d件/箱 %d毫升/件 (价格：%.2f/箱  库存：%d)\n",t+1,s->info[t][0],s->info[t][1],s->uprice[t],s->info[t][2]);
                    while(1)
                    {
                        printf("请选择您要增加库存的组合编号:");
                        int k;
                        scanf("%d",&k);
                        if(1<=k&&k<=s->tnum)
                        {
                            int tt;
                            printf("请输入要增加的库存数量:");
                            scanf("%d",&tt);
                            s->info[k-1][2]+=tt;
                            printf("新的库存情况如下:\n");
                            for(int t=0;t<s->tnum;t++)
                                printf("%d、%d件/箱 %d毫升/件 (价格：%.2f/箱  库存：%d)\n",t+1,s->info[t][0],s->info[t][1],s->uprice[t],s->info[t][2]);
                            break;
                        }
                        else
                        {
                            printf("请输入正确的数字编号\n");
                            continue;
                        }
                    }
                }
            }
            break;
        }
        else
        {
            printf("请输入正确的数字编号！\n请重新输入编号:");
            scanf("%d",&n);
            continue;
        }
    }
    return ihead;
}

plink addition1(plink head,tlink ihead)
{
    char type1[10]="酒",type2[10]="饮料";
    struct cell *tmp,*p;
    struct item *p00;
    char judge[100],judge1[100];
    int bo=0,t,po,ty,tt,tt1,count;
    p00=ihead;
    p=head;
    tmp=(struct cell *)malloc(sizeof(struct cell));
    while(p->next!=NULL)
        p=p->next;
    p->next=tmp;
    FILE* dopen;
    dopen=fopen("dingdanshu.txt","r");
    fscanf(dopen,"%d",&count);
    fclose(dopen);
    dopen=fopen("dingdanshu.txt","w");
    count++;
    fprintf(dopen,"%d",count);
    fclose(dopen);
    count=count+1000000;
    tmp->dingdan=count;                       //订单编号
    printf("欢迎进入订单添加栏目 o(*≧▽≦)ツ┏━┓\n");
    tmp->zhanghao=useraccount.number;
    printf("一、请输入订单日期:\n");               //以下六行是订单日期
    while(1)
    {
        printf("月/日:");
        while(1)
        {
            scanf("%s",judge);
            scanf("%s",judge1);
            tt=strlen(judge);
            tt1=strlen(judge1);
            bo=0;
            for(ty=0;ty<tt;ty++)
            {
                if(judge[ty]>'9'||judge[ty]<'0')
                    bo=1;
            }
            for(ty=0;ty<tt1;ty++)
            {
                if(judge1[ty]>'9'||judge1[ty]<'0')
                    bo=1;
            }
            if(bo==1)
            {
                printf("输入数据有误，请输入纯数字：\n");
            }
            else
                break;
        }
        tmp->month=atoi(judge);
        tmp->day=atoi(judge1);
        if(tmp->month==1||tmp->month==3||tmp->month==5||tmp->month==7||tmp->month==8||tmp->month==10||tmp->month==12)
        {
            if(tmp->day>0&&tmp->day<=31)
                break;
            else
                printf("输入日期有误，请检查后重新输入哦\n");
        }
        else if(tmp->month==4||tmp->month==6||tmp->month==9||tmp->month==11)
        {
            if(tmp->day>0&&tmp->day<=30)
                break;
            else
                printf("输入日期有误，请检查后重新输入哦\n");
        }
        else if(tmp->month==2)
        {
            if(tmp->day>0&&tmp->day<=28)
                break;
            else
                printf("输入日期有误，请检查后重新输入哦\n");
        }
        else
            printf("输入日期有误，请检查后重新输入哦\n");
        }
    while(1)
    {
            printf("时/分:");
            while(1)
        {
            scanf("%s",judge);
            scanf("%s",judge1);
            getchar();
            tt=strlen(judge);
            tt1=strlen(judge1);
            bo=0;
            for(ty=0;ty<tt;ty++)
            {
                if(judge[ty]>'9'||judge[ty]<'0')
                    bo=1;
            }
            for(ty=0;ty<tt1;ty++)
            {
                if(judge1[ty]>'9'||judge1[ty]<'0')
                    bo=1;
            }
            if(bo==1)
            {
                printf("输入数据有误，请输入纯数字：\n");
            }
            else
                break;
        }
        tmp->hour=atoi(judge);
        tmp->minute=atoi(judge1);
            if(tmp->hour>=0&&tmp->hour<=23&&tmp->minute>=0&&tmp->minute<=59)
                break;
            else
                printf("输入时间有误，请检查后重新输入哦\n");
    }
    tmp->timesum=tmp->minute+(tmp->hour)*60+(tmp->day-1)*1440;
    for(int i=1;i<tmp->month;i++)
    {
        if(i==1||i==3||i==5||i==7||i==8||i==10||i==12)
            tmp->timesum+=31*1440;
        else if(i==2)
            tmp->timesum+=28*1440;
        else
            tmp->timesum+=30*1440;
    }
    while(1)
    {
        printf("二、请输入网点代理人姓名:\n");        //网点代理人姓名
        gets(tmp->name);
        if(strlen(tmp->name)<=39)
            break;
        else
            printf("网点代理人姓名的字数超出限制，请重新输入哦\n");
    }
    printf("三、请输入网点代理人电话:\n");        //网点代理人电话
    while(1)
    {
        gets(tmp->phone);
        tt=strlen(tmp->phone);
        bo=0;
        for(ty=0;ty<tt;ty++)
        {
            if(tmp->phone[ty]>'9'||tmp->phone[ty]<'0')
                bo=1;
        }
        if(bo==1)
        {
            printf("输入数据有误，请输入纯数字：\n");
        }
        else
            break;
    }
    printf("四、请输入商品名称:\n");              //商品名字
    while(1)
    {
        gets(tmp->itemname);
        p00=ihead;
        bo=0;
        while(p00->next!=NULL)
      {
        p00=p00->next;
        if(strcmp(p00->itemname,tmp->itemname)==0)
        {
            bo=1;
            break;
        }
      }
      if(bo==1)
        break;
      else
        printf("商品名称输入有误，未找到该商品，请再次输入：\n");
    }
    strcpy(tmp->type,p00->type);
    printf("五、请选择你要批发商品的单箱种类\n");
    for(t=0;t<p00->tnum;t++)
    {
        printf("%d、%d件/箱 %d毫升/件 (价格：%.2f/箱  库存：%d)\n",t+1,p00->info[t][0],p00->info[t][1],p00->uprice[t],p00->info[t][2]);
    }
    printf("请选择批发的单箱种类（按编号输入）：");
    bo=0;
    while(1)
    {
        while(1)
        {
            gets(judge);
            tt=strlen(judge);
            bo=0;
            for(ty=0;ty<tt;ty++)
            {
                if(judge[ty]>'9'||judge[ty]<'0')
                    bo=1;
            }
            if(bo==1)
            {
                printf("输入数据有误，请输入纯数字：\n");
            }
            else
                break;
        }
        po=atoi(judge);
        for(t=0;t<p00->tnum;t++)
        {
            if(po==t+1)
            {
                tmp->uprice=p00->uprice[t];
                bo=1;
                break;
            }
        }
        if(bo==1)
            break;
        else
            printf("输入种类有误，请按编号重新输入：");
    }
    printf("六、请输入商品数量:\n");              //商品数量
    while(1)
    {
        while(1)
        {
            gets(judge);
            tt=strlen(judge);
            bo=0;
            for(ty=0;ty<tt;ty++)
            {
                if(judge[ty]>'9'||judge[ty]<'0')
                    bo=1;
            }
            if(bo==1)
            {
                printf("输入数据有误，请输入纯数字：\n");
            }
            else
                break;
        }
        tmp->num=atoi(judge);
        if((p00->info[po-1][2])-(tmp->num)>=0)
            break;
        else
            printf("批发数量超过库存，批发失败，请重新选择批发数量：\n");
    }
    p00->info[po-1][2]=(p00->info[po-1][2])-(tmp->num);
    // getchar();
    // while(1)
    // {
    //         printf("八、请输入备注:\n");                //商品备注
    //         gets(tmp->beizhu);
    //         if(strlen(tmp->beizhu)<=199)
    //             break;
    //         else
    //             printf("备注字数超出限制，请重新输入哦\n");
    // }
    tmp->rong=p00->info[po-1][1];
    tmp->inum=p00->info[po-1][0];
    tmp->sum=tmp->uprice*tmp->num;            //该订单的总金额
    if(sumplus+tmp->sum>=5000)
    {
        tmp->beizhu[0]='A';
        tmp->beizhu[1]='\0';
    }
    else if(sumplus+tmp->sum>=2000)
    {
        tmp->beizhu[0]='B';
        tmp->beizhu[1]='\0';
    }
    else
    {
        tmp->beizhu[0]='C';
        tmp->beizhu[1]='\0';
    }
    tmp->next=NULL;
    strcpy(tmp->itemlab,p00->itemlab[po-1]);    //记录这条订单记录设计的商品编号
    sumplus+=tmp->sum;
    //上分隔符
    printf("您添加的订单记录为：\n");
    char h[10][50]={"编号","日期","姓名","电话","商品种类","商品名称","单价(元/箱)","赠品","数量","总金额"};
        printf("%-7s\t %-15s\t%-8s\t%-10s\t%-9s%-11s\t%-12s%-5s%-6s%-6s\n",h[0],h[1],h[2],h[3],h[4],h[5],h[6],h[7],h[8],h[9]);
    printf("%-8d %02d月%02d日%02d时%02d分\t%-8s\t%-11s\t%-2s\t %-14s\t%-12.2f%-5s%-6d%-10.2f\t\n",tmp->dingdan,tmp->month,tmp->day,tmp->hour,tmp->minute,tmp->name,tmp->phone,tmp->type,tmp->itemname,tmp->uprice,tmp->beizhu,tmp->num,tmp->sum);
    printf("配送地址为：%s",useraccount.address);
    printf("\n确认该条订单记录完全正确后请按1，否则按0:");
    int s;
    while(1)
    {
        gets(judge);
        tt=strlen(judge);
        bo=0;
        for(ty=0;ty<tt;ty++)
        {
            if(judge[ty]>'9'||judge[ty]<'0')
                bo=1;
        }
        if(bo==1)
        {
            printf("输入数据有误，请输入纯数字：\n");
        }
        else
            break;
    }
    s=atoi(judge);
    if(s==1)
    {
        ;
    }
    else
    {
        while(1)
        {
            printf("1.日期\n2.代理人姓名\n3.电话\n4.商品名字\n5.单箱件数或者单件容量\n6.商品数量\n");
            printf("请输入您需要修改的项目编号：");
            int t;
            scanf("%d",&t);
            if(t==1)                    //对日期的修改
            {
                int a,b,c,d;
                while(1)
                {
                    printf("请输入月/日：");
                    while(1)
                    {
                        scanf("%s",judge);
                        scanf("%s",judge1);
                        tt=strlen(judge);
                        tt1=strlen(judge1);
                        bo=0;
                        for(ty=0;ty<tt;ty++)
                        {
                            if(judge[ty]>'9'||judge[ty]<'0')
                                bo=1;
                        }
                        for(ty=0;ty<tt1;ty++)
                        {
                            if(judge1[ty]>'9'||judge1[ty]<'0')
                                bo=1;
                        }
                        if(bo==1)
                        {
                            printf("输入数据有误，请输入纯数字：\n");
                        }
                        else
                            break;
                    }
                    a=atoi(judge);
                    b=atoi(judge1);
                    if(a<1||a>12)
                    {
                        printf("输入日期有误，请检查后重新输入哦\n");
                        continue;
                    }
                    else
                    {
                        if(a==1||a==3||a==5||a==7||a==8||a==10||a==12)
                        {
                            if(1<=b&&b<=31)
                            {
                                tmp->month=a;
                                tmp->day=b;
                                break;
                            }
                            else
                            {
                                printf("输入日期有误，请检查后重新输入哦\n");
                                continue;
                            }
                        }
                        else if(a==4||a==6||a==9||a==11)
                        {
                            if(1<=b&&b<=30)
                            {
                                tmp->month=a;
                                tmp->day=b;
                                break;
                            }
                            else
                            {
                                printf("输入日期有误，请检查后重新输入哦\n");
                                continue;
                            }
                        }
                        else if(a==2)
                        {
                            if(1<=b&&b<=28)
                            {
                                tmp->month=a;
                                tmp->day=b;
                                break;
                            }
                            else
                            {
                                printf("输入日期有误，请检查后重新输入哦\n");
                                continue;
                            }
                        }
                    }
                }
                while(1)
                {
                    printf("请输入时/分:");
                    while(1)
                    {
                        scanf("%s",judge);
                        scanf("%s",judge1);
                        tt=strlen(judge);
                        tt1=strlen(judge1);
                        bo=0;
                        for(ty=0;ty<tt;ty++)
                        {
                            if(judge[ty]>'9'||judge[ty]<'0')
                                bo=1;
                        }
                        for(ty=0;ty<tt1;ty++)
                        {
                            if(judge1[ty]>'9'||judge1[ty]<'0')
                                bo=1;
                        }
                        if(bo==1)
                        {
                            printf("输入数据有误，请输入纯数字：\n");
                        }
                        else
                            break;
                    }
                    c=atoi(judge);
                    d=atoi(judge1);
                    if(0<=c&&c<=23&&0<=d&&d<=59)
                    {
                        tmp->hour=c;
                        tmp->minute=d;
                        break;
                    }
                    else
                    {
                        printf("输入日期有误，请检查后重新输入哦\n");
                        continue;
                    }
                }
                tmp->timesum=tmp->minute+(tmp->hour)*60+(tmp->day-1)*1440;
                for(int i=1;i<tmp->month;i++)
                {
                    if(i==1||i==3||i==5||i==7||i==8||i==10||i==12)
                        tmp->timesum+=31*1440;
                    else if(i==2)
                        tmp->timesum+=28*1440;
                    else
                        tmp->timesum+=30*1440;
                }
                printf("修改后的订单记录为：\n");
                char h[10][50]={"编号","日期","姓名","电话","商品种类","商品名称","单价(元/箱)","赠品","数量","总金额"};
        printf("%-7s\t %-15s\t%-8s\t%-10s\t%-9s%-11s\t%-12s%-5s%-6s%-6s\n",h[0],h[1],h[2],h[3],h[4],h[5],h[6],h[7],h[8],h[9]);
    printf("%-8d %02d月%02d日%02d时%02d分\t%-8s\t%-11s\t%-2s\t %-14s\t%-12.2f%-5s%-6d%-10.2f\t\n",tmp->dingdan,tmp->month,tmp->day,tmp->hour,tmp->minute,tmp->name,tmp->phone,tmp->type,tmp->itemname,tmp->uprice,tmp->beizhu,tmp->num,tmp->sum);
                printf("确认该条订单记录完全正确后请按1，否则按0:");
                scanf("%d",&s);
                if(s==1) break;
                else if(s==0) continue;
            }
            else if(t==2)               //姓名进行修改
            {
                char e[40];
                while(1)
                {
                    printf("请输入新的网点代理人姓名：");
                    scanf("%s",e);
                    if(strlen(e)<=40)
                    {
                        strcpy(tmp->name,e);
                        break;
                    }
                    else
                    {
                        printf("网点代理人姓名字数超出限制，请重新输入哦\n");
                        continue;
                    }
                }
                printf("修改后的订单记录为：\n");
                char h[10][50]={"编号","日期","姓名","电话","商品种类","商品名称","单价(元/箱)","赠品","数量","总金额"};
        printf("%-7s\t %-15s\t%-8s\t%-10s\t%-9s%-11s\t%-12s%-5s%-6s%-6s\n",h[0],h[1],h[2],h[3],h[4],h[5],h[6],h[7],h[8],h[9]);
    printf("%-8d %02d月%02d日%02d时%02d分\t%-8s\t%-11s\t%-2s\t %-14s\t%-12.2f%-5s%-6d%-10.2f\t\n",tmp->dingdan,tmp->month,tmp->day,tmp->hour,tmp->minute,tmp->name,tmp->phone,tmp->type,tmp->itemname,tmp->uprice,tmp->beizhu,tmp->num,tmp->sum);
                printf("确认该条订单记录完全正确后请按1，否则按0:");
                scanf("%d",&s);
                if(s==1) break;
                else if(s==0) continue;
            }
            else if(t==6)               //对商品数量进行修改
            {
                sumplus-=tmp->uprice*tmp->num;
                p00->info[po-1][2]+=tmp->num;
                while(1)
                {
                    printf("请输入新的商品数量:");
                    while(1)
                    {
                        scanf("%s",judge);
                        tt=strlen(judge);
                        bo=0;
                        for(ty=0;ty<tt;ty++)
                        {
                            if(judge[ty]>'9'||judge[ty]<'0')
                                bo=1;
                        }
                        if(bo==1)
                        {
                            printf("输入数据有误，请输入纯数字：\n");
                        }
                        else
                            break;
                    }
                    tmp->num=atoi(judge);
                    if(tmp->num<=p00->info[po-1][2])
                    {
                        p00->info[po-1][2]-=tmp->num;
                        break;
                    }
                    else
                    {
                        printf("该商品的库存为：%d\n",p00->info[po-1][2]);
                        printf("批发数量超过库存，批发失败\n");
                        continue;
                    }
                }
                sumplus+=tmp->uprice*tmp->num;
                tmp->sum=tmp->num*tmp->uprice;
                printf("修改后的订单记录为：\n");
                char h[10][50]={"编号","日期","姓名","电话","商品种类","商品名称","单价(元/箱)","赠品","数量","总金额"};
        printf("%-7s\t %-15s\t%-8s\t%-10s\t%-9s%-11s\t%-12s%-5s%-6s%-6s\n",h[0],h[1],h[2],h[3],h[4],h[5],h[6],h[7],h[8],h[9]);
   printf("%-8d %02d月%02d日%02d时%02d分\t%-8s\t%-11s\t%-2s\t %-14s\t%-12.2f%-5s%-6d%-10.2f\t\n",tmp->dingdan,tmp->month,tmp->day,tmp->hour,tmp->minute,tmp->name,tmp->phone,tmp->type,tmp->itemname,tmp->uprice,tmp->beizhu,tmp->num,tmp->sum);
                printf("确认该条订单记录完全正确后请按1，否则按0:");
                scanf("%d",&s);
                if(s==1) break;
                else if(s==0) continue;
            }
            else if(t==3)               //对电话进行修改
            {
                while(1)
                {
                    bo=0;
                    gets(tmp->phone);
                    tt=strlen(tmp->phone);
                    if(tt>19)
                        bo=2;
                    for(ty=0;ty<tt;ty++)
                    {
                        if(judge[ty]>'9'||judge[ty]<'0')
                            bo=1;
                    }
                    if(bo==1)
                    {
                        printf("输入数据有误，请输入纯数字：\n");
                    }
                    if(bo==2)
                    {
                        printf("输入电话号码超过长度限制，请正常输入：\n");
                    }
                    if(bo==0)
                        break;
                }
                char h[10][50]={"编号","日期","姓名","电话","商品种类","商品名称","单价(元/箱)","赠品","数量","总金额"};
        printf("%-7s\t %-15s\t%-8s\t%-10s\t%-9s%-11s\t%-12s%-5s%-6s%-6s\n",h[0],h[1],h[2],h[3],h[4],h[5],h[6],h[7],h[8],h[9]);
    printf("%-8d %02d月%02d日%02d时%02d分\t%-8s\t%-11s\t%-2s\t %-14s\t%-12.2f%-5s%-6d%-10.2f\t\n",tmp->dingdan,tmp->month,tmp->day,tmp->hour,tmp->minute,tmp->name,tmp->phone,tmp->type,tmp->itemname,tmp->uprice,tmp->beizhu,tmp->num,tmp->sum);
                printf("确认该条订单记录完全正确后请按1，否则按0:");
                scanf("%d",&s);
                if(s==1) break;
                else if(s==0) continue;
            }
            else if(t==5)               //对种类进行修改
            {
                sumplus-=tmp->num*tmp->uprice;
                p00->info[po-1][2]+=tmp->num;                   //先把商品数量加回去
                printf("请选择你要批发商品的单箱种类（商品数量已被重置）\n");
                for(t=0;t<p00->tnum;t++)
                {
                    printf("%d、%d件/箱 %d毫升/件 (价格：%.2f/箱  库存：%d)\n",t+1,p00->info[t][0],p00->info[t][1],p00->uprice[t],p00->info[t][2]);
                }
                printf("请选择新的单箱种类（按编号输入）：");
                bo=0;
                while(1)
                {
                    while(1)
                    {
                        getchar();
                        gets(judge);
                        tt=strlen(judge);
                        bo=0;
                        for(ty=0;ty<tt;ty++)
                        {
                            if(judge[ty]>'9'||judge[ty]<'0')
                                bo=1;
                        }
                        if(bo==1)
                        {
                            printf("输入数据有误，请输入纯数字：\n");
                        }
                        else
                            break;
                    }
                    po=atoi(judge);
                    for(t=0;t<p00->tnum;t++)
                    {
                        if(po==t+1)
                        {
                            tmp->uprice=p00->uprice[t];
                            bo=1;
                            break;
                        }
                    }
                    if(bo==1)
                        break;
                    else
                        printf("输入种类有误，请按编号重新输入：");
                }
                printf("请输入商品数量:\n");              //商品数量
                while(1)
                {
                    while(1)
                    {
                        gets(judge);
                        tt=strlen(judge);
                        bo=0;
                        for(ty=0;ty<tt;ty++)
                        {
                            if(judge[ty]>'9'||judge[ty]<'0')
                                bo=1;
                        }
                        if(bo==1)
                        {
                            printf("输入数据有误，请输入纯数字：\n");
                        }
                        else
                            break;
                    }
                    tmp->num=atoi(judge);
                    if((p00->info[po-1][2])-(tmp->num)>=0)
                        break;
                    else
                        printf("批发数量超过库存，批发失败，请重新选择批发数量：\n");
                }
                tmp->rong=p00->info[po-1][1];
                tmp->inum=p00->info[po-1][0];
                p00->info[po-1][2]-=tmp->num;
                tmp->sum=tmp->num*tmp->uprice;
                sumplus+=p->sum;
                strcpy(tmp->itemlab,p00->itemlab[po-1]);
                char h[10][50]={"编号","日期","姓名","电话","商品种类","商品名称","单价(元/箱)","赠品","数量","总金额"};
        printf("%-7s\t %-15s\t%-8s\t%-10s\t%-9s%-11s\t%-12s%-5s%-6s%-6s\n",h[0],h[1],h[2],h[3],h[4],h[5],h[6],h[7],h[8],h[9]);
    printf("%-8d %02d月%02d日%02d时%02d分\t%-8s\t%-11s\t%-2s\t %-14s\t%-12.2f%-5s%-6d%-10.2f\t\n",tmp->dingdan,tmp->month,tmp->day,tmp->hour,tmp->minute,tmp->name,tmp->phone,tmp->type,tmp->itemname,tmp->uprice,tmp->beizhu,tmp->num,tmp->sum);
                printf("确认该条订单记录完全正确后请按1，否则按0:");
                scanf("%d",&s);
                if(s==1) break;
                else if(s==0) continue;
            }
            else if(t==4)               //对商品名字进行修改
            {
                tlink q;
                char ss[40];
                sumplus-=tmp->sum;
                p00->info[po-1][2]+=tmp->num;
                while(1)
                {
                    printf("请输入新的商品名称：");
                    scanf("%s",ss);
                    q=ihead->next;
                    while(q!=NULL)
                    {
                        if(strcmp(q->itemname,ss)==0)
                            break;
                        q=q->next;
                    }
                    if(q==NULL)
                    {
                        printf("未找到商品，请重新输入！");
                        continue;
                    }
                    else
                        break;
                }
                strcpy(tmp->itemname,ss);
                strcpy(tmp->type,q->type);
                p00=q;
                printf("请选择新商品的单箱种类\n");
                for(t=0;t<p00->tnum;t++)
                {
                    printf("%d、%d件/箱 %d毫升/件 (价格：%.2f/箱  库存：%d)\n",t+1,p00->info[t][0],p00->info[t][1],p00->uprice[t],p00->info[t][2]);
                }
                printf("请选择批发的单箱种类（按编号输入）：");
                bo=0;
                while(1)
                {
                    while(1)
                    {
                        scanf("%s",judge);
                        tt=strlen(judge);
                        bo=0;
                        for(ty=0;ty<tt;ty++)
                        {
                            if(judge[ty]>'9'||judge[ty]<'0')
                                bo=1;
                        }
                        if(bo==1)
                        {
                            printf("输入数据有误，请输入纯数字：\n");
                        }
                        else
                            break;
                    }
                    po=atoi(judge);
                    for(t=0;t<p00->tnum;t++)
                    {
                        if(po==t+1)
                        {
                            tmp->uprice=p00->uprice[t];
                            bo=1;
                            break;
                        }
                    }
                    if(bo==1)
                        break;
                    else
                        printf("输入种类有误，请按编号重新输入：");
                }
                printf("请输入新商品批发数量:\n");              //商品数量
                while(1)
                {
                    while(1)
                    {
                        scanf("%s",judge);
                        tt=strlen(judge);
                        bo=0;
                        for(ty=0;ty<tt;ty++)
                        {
                            if(judge[ty]>'9'||judge[ty]<'0')
                                bo=1;
                        }
                        if(bo==1)
                        {
                            printf("输入数据有误，请输入纯数字：\n");
                        }
                        else
                            break;
                    }
                    tmp->num=atoi(judge);
                    if((p00->info[po-1][2])-(tmp->num)>=0)
                        break;
                    else
                        printf("批发数量超过库存，批发失败，请重新选择批发数量：\n");
                }
                p00->info[po-1][2]=(p00->info[po-1][2])-(tmp->num);
                tmp->sum=tmp->num*tmp->uprice;
                sumplus+=tmp->sum;
                tmp->rong=p00->info[po-1][1];
                tmp->inum=p00->info[po-1][0];
                strcpy(tmp->itemlab,p00->itemlab[po-1]);
                char h[10][50]={"编号","日期","姓名","电话","商品种类","商品名称","单价(元/箱)","赠品","数量","总金额"};
        printf("%-7s\t %-15s\t%-8s\t%-10s\t%-9s%-11s\t%-12s%-5s%-6s%-6s\n",h[0],h[1],h[2],h[3],h[4],h[5],h[6],h[7],h[8],h[9]);
    printf("%-8d %02d月%02d日%02d时%02d分\t%-8s\t%-11s\t%-2s\t %-14s\t%-12.2f%-5s%-6d%-10.2f\t\n",tmp->dingdan,tmp->month,tmp->day,tmp->hour,tmp->minute,tmp->name,tmp->phone,tmp->type,tmp->itemname,tmp->uprice,tmp->beizhu,tmp->num,tmp->sum);
                printf("确认该条订单记录完全正确后请按1，否则按0:");
                scanf("%d",&s);
                if(s==1) break;
                else if(s==0) continue;
            }
            else
            {
                printf("请输入正确的项目编号！");
                continue;
            }
        }
    }
    //下分隔符
    printf("恭喜你，订单添加成功! (o゜▽゜)o☆[BINGO!]\n");
    return head;
}

plink moneyprint(plink head)
{
    struct cell* p,*p0,*r,*r0,*q;
    p=p0=r=r0=q=NULL;
    p=head;
    while(p!=NULL)
    {
        r=head;
        while(r->sum>p->sum&&r!=p)
        {
            r0=r;
            r=r->next;
        }
        if(p!=r)
        {
            q=p;
            p0->next=p->next;
            p=p0;
            if(p==head)
            {
                q->next=head;
                head=q;
            }
            else
            {
                q->next=r;
                r0->next=q;
            }
        }
        p0=p;
        p=p->next;
    }
    return head;
}

void userprint(plink head)
{

    plink tmp,head0;
    tmp=(plink)malloc(sizeof(struct cell));
    tmp->dingdan=1;
    tmp->timesum=-1;
    tmp->sum=99999999999;
    tmp->next=NULL;
    head0=tmp;
    plink p=head->next;
    int judge=0;
    if(p==NULL)
        printf("系统中还没有数据哦\n");
    else
    {
        while(p!=NULL)                      //把符合的订单记录放到一条新的链表里面去（新链表有哨兵节点）
        {
            if(useraccount.number==p->zhanghao)
            {
                plink q;
                q=(plink)malloc(sizeof(struct cell));
                q->zhanghao=useraccount.number;
                q->dingdan=p->dingdan;
                q->month=p->month;
                q->day=p->day;
                q->hour=p->hour;
                q->minute=p->minute;
                q->uprice=p->uprice;
                q->num=p->num;
                q->timesum=p->timesum;
                q->sum=p->sum;
                q->zhanghao=p->zhanghao;
                q->rong=p->rong;
                q->inum=p->inum;
                strcpy(q->itemlab,p->itemlab);
                strcpy(q->name,p->name);
                strcpy(q->phone,p->phone);
                strcpy(q->type,p->type);
                strcpy(q->itemname,p->itemname);
                strcpy(q->beizhu,p->beizhu);
                q->next=NULL;
                tmp->next=q;
                tmp=q;
                judge=1;
            }
                p=p->next;
        }
        if(judge==0)
            printf("没有找到您的订单记录！\n");
        else
        {
            printf("1.以时间顺序打印\n2.以订单金额打印\n");
            printf("请选择打印的顺序：");
            int k;
            scanf("%d",&k);
            while(1)
            {
                if(k==1)
                {
                    printf("按照日期排序后的订单记录如下：\n");
                    head0=dateprint(head0);
                    printall(head0);
                    break;
                }
                else if(k==2)
                {
                    printf("按照订单金额排序后的订单记录如下：\n");
                    head0=moneyprint(head0);
                    printall(head0);
                    break;
                }
                else
                {
                    printf("请输入正确的编号:");
                    scanf("%d",&k);
                    continue;
                }
            }
        }
    }
}

void itemprintall(tlink ihead,struct cell* head)//生成库存报表，统计营业总额。
{
    system("cls");
     printf("\t\t\t\t\t\t酒水批发系统(管理员端)-库存报表\n\n");
    tlink tmp;
    tmp=(tlink)malloc(sizeof(struct item));
    tmp=ihead;if(tmp->next==NULL){printf("当前尚无任何商品！");return;}
    printf("-----------------------------------------------------库存报表-----------------------------------------------------------\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t商品名称\t商品类型\t单件容量\t单件数量\t库存\t\t单价\t\t\t\n");
    while(1)
    {    tmp=tmp->next;
         if(tmp==NULL)
        {
            printf("\t当前营业总额为：%.2f\t\t\t\t\t\t\t\t\t\t\t\t\n",sumplus);
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            break;
        }
        for(int i=0;i<tmp->tnum;i++)
        {
            printf("\t\t%s     \t",tmp->itemname);
            printf("%s\t\t",tmp->type);
            printf("%dml\t\t",tmp->info[i][1]);
            printf("%d瓶/箱\t\t",tmp->info[i][0]);
            printf("%d件\t\t",tmp->info[i][2]);
            printf("%.2f元\t\t\t\n",tmp->uprice[i]);
        }
    }
    printf("如您需要检索某种商品的信息请按下1,否则请按下0:");
    int judge;
    scanf("%d",&judge);
    if(judge==1)
    {
        char ss[40];
        printf("请输入您要检索的商品的名称:");
        scanf("%s",ss);
        tlink s=ihead->next;
        if(s==NULL)
            printf("当前尚无任何商品");
        else
        {
            while(s!=NULL)
            {
                if(strcmp(s->itemname,ss)==0)
                    break;
                s=s->next;
            }
            if(s==NULL)
            {
                struct tt{
                    char sta[100];
                    struct tt* next;
                };
                typedef struct tt* ttk;
                ttk d1,d2;
                d2=(ttk)malloc(sizeof(struct tt));
                d2->next=NULL;
                d1=d2;
                tlink s1=ihead->next;
                while(s1!=NULL)
                {
                    if(editDistance(s1->itemname,ss)<=3)
                    {
                        ttk q;
                        q=(ttk)malloc(sizeof(struct tt));
                        strcpy(q->sta,s1->itemname);
                        q->next=NULL;
                        d2->next=q;
                        d2=q;
                    }
                    s1=s1->next;
                }
                if(d1->next==NULL)
                    printf("未找到相关商品!");
                else
                {
                    printf("未找到名为%s的商品,您可能想搜索的商品是：\n",ss);
                    d1=d1->next;
                    while(d1!=NULL)
                    {
                        printf("%s\n",d1->sta);
                        d1=d1->next;
                    }
                    printf("请尝试重新搜索!\n");
                }
            }
            else
            {
                printf("该商品的相关库存信息如下:\n");
                printf("商品名称:%s\n",s->itemname);
                printf("商品类型:%s\n",s->type);
                for(int t=0;t<s->tnum;t++)
                {
                    printf("%d、%d件/箱 %d毫升/件 (价格：%.2f/箱  库存：%d)\n",t+1,s->info[t][0],s->info[t][1],s->uprice[t],s->info[t][2]);
                }
            }
        }
    }
}

void itemprintalluser(tlink ihead,struct cell* head)//生成库存报表，统计营业总额。
{
    system("cls");
     printf("\t\t\t\t\t\t酒水批发系统(用户端)\n\n");
    tlink tmp;
    tmp=(tlink)malloc(sizeof(struct item));
    tmp=ihead;if(tmp->next==NULL){printf("当前尚无任何商品！");return;}
    printf("-----------------------------------------------------库存报表-----------------------------------------------------------\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t商品名称\t商品类型\t单件容量\t单件数量\t库存\t\t单价\t\t\t\n");
    while(1)
    {    tmp=tmp->next;
         if(tmp==NULL)
        {
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            break;
        }
        for(int i=0;i<tmp->tnum;i++)
        {
            printf("\t\t%s     \t",tmp->itemname);
            printf("%s\t\t",tmp->type);
            printf("%dml\t\t",tmp->info[i][1]);
            printf("%d瓶/箱\t\t",tmp->info[i][0]);
            printf("%d件\t\t",tmp->info[i][2]);
            printf("%.2f元\t\t\t\n",tmp->uprice[i]);
        }
    }
    printf("如您需要检索某种商品的信息请按下1,否则请按下0:");
    int judge;
    scanf("%d",&judge);
    if(judge==1)
    {
        char ss[40];
        printf("请输入您要检索的商品的名称:");
        scanf("%s",ss);
        tlink s=ihead->next;
        if(s==NULL)
            printf("当前尚无任何商品");
        else
        {
            while(s!=NULL)
            {
                if(strcmp(s->itemname,ss)==0)
                    break;
                s=s->next;
            }
            if(s==NULL)
            {
                struct tt{
                    char sta[100];
                    struct tt* next;
                };
                typedef struct tt* ttk;
                ttk d1,d2;
                d2=(ttk)malloc(sizeof(struct tt));
                d2->next=NULL;
                d1=d2;
                tlink s1=ihead->next;
                while(s1!=NULL)
                {
                    if(editDistance(s1->itemname,ss)<=3)
                    {
                        ttk q;
                        q=(ttk)malloc(sizeof(struct tt));
                        strcpy(q->sta,s1->itemname);
                        q->next=NULL;
                        d2->next=q;
                        d2=q;
                    }
                    s1=s1->next;
                }
                if(d1->next==NULL)
                    printf("未找到相关商品!");
                else
                {
                    printf("未找到名为%s的商品,您可能想搜索的商品是：\n",ss);
                    d1=d1->next;
                    while(d1!=NULL)
                    {
                        printf("%s\n",d1->sta);
                        d1=d1->next;
                    }
                    printf("请尝试重新搜索!\n");
                }
            }
            else
            {
                printf("该商品的相关库存信息如下:\n");
                printf("商品名称:%s\n",s->itemname);
                printf("商品类型:%s\n",s->type);
                for(int t=0;t<s->tnum;t++)
                {
                    printf("%d、%d件/箱 %d毫升/件 (价格：%.2f/箱  库存：%d)\n",t+1,s->info[t][0],s->info[t][1],s->uprice[t],s->info[t][2]);
                }
            }
        }
    }
}

plink giftcheck(plink head)//检查赠品情况
{
    plink tmp;
    int a1=0,b1=0,c1=0,d1=0;
    tmp=(plink)malloc(sizeof(struct cell));
    tmp=head;
    if(tmp->next==NULL)
    {
        printf("当前尚未送出任何赠品！");
        return head;
    }
    else
    {
        tmp=tmp->next;
        while(1)
        {
            if(tmp==NULL){printf("赠品A送出了:%d\n赠品B送出了:%d\n赠品C送出了:%d\n赠品D送出了:%d\n",a1,b1,c1,d1);break;}
            if(strcmp("A",tmp->beizhu)==0)a1++;
            if(strcmp("B",tmp->beizhu)==0)b1++;
            if(strcmp("C",tmp->beizhu)==0)c1++;
            if(strcmp("D",tmp->beizhu)==0)d1++;
            tmp=tmp->next;
        }
    }
    return head;
}

void usercheck(plink head)
{
    printf("\t\t\t\t\t您的账号为：%d\n",useraccount.number);
    double tmp=0;
    head=head->next;
    while(head!=NULL)
    {
        if(head->zhanghao==useraccount.number)
            tmp+=head->sum;
        head=head->next;
    }
    printf("\t\t\t\t\t您的消费总金额为：%.2lf\n",tmp);
    int level;
    if(tmp<2000)
        level=1;
    else if(tmp>=2000&&tmp<5000)
        level=2;
    else
        level=3;
    printf("\t\t\t\t\t您的用户等级为:%d\n",level);
}

tlink itemdel(tlink head)
{
    printf("1.减少商品库存\n2.删除商品\n");
    printf("请选择要进行的操作：");
    int ss;
    while(1)
    {
        scanf("%d",&ss);
        if(ss==1)
        {
            char ss[40];
            printf("请输入商品名称：");
            scanf("%s",ss);
            tlink s=head->next;
            if(s==NULL)
                printf("还没有商品哦！");
            else
            {
                while(s!=NULL)
                {
                    if(strcmp(s->itemname,ss)==0)
                        break;
                    s=s->next;
                }
                if(s==NULL)
                    printf("没有找到对应的商品！");
                else
                {
                    printf("该商品的组合情况如下：\n");
                    for(int t=0;t<s->tnum;t++)
                        printf("%d、%d件/箱 %d毫升/件 (价格：%.2f/箱  库存：%d)\n",t+1,s->info[t][0],s->info[t][1],s->uprice[t],s->info[t][2]);
                    while(1)
                    {
                        printf("请选择您要减少库存的组合编号:");
                        int k;
                        scanf("%d",&k);
                        if(1<=k&&k<=s->tnum)
                        {
                            while(1)
                            {
                                int tt;
                                printf("请输入要减少的库存数量:");
                                scanf("%d",&tt);
                                //s->info[k-1][2]+=tt;
                                if(tt>s->info[k-1][2])
                                {
                                    printf("减少数量超过库存!请重新输入!\n");
                                    continue;
                                }
                                else
                                {
                                    s->info[k-1][2]-=tt;
                                    printf("新的库存情况如下:\n");
                                    for(int t=0;t<s->tnum;t++)
                                        printf("%d、%d件/箱 %d毫升/件 (价格：%.2f/箱  库存：%d)\n",t+1,s->info[t][0],s->info[t][1],s->uprice[t],s->info[t][2]);
                                    break;
                                }
                            }
                            break;
                        }
                        else
                        {
                            printf("请输入正确的数字编号\n");
                            continue;
                        }
                    }
                }
            }
            break;
        }
        else if(ss==2)
        {
            tlink p,p0;
            p0=head;
            p=head->next;
            if(p==NULL)
                printf("库中还没有商品！");
            else
            {
                while(1)
                {
                    char t[40];
                    printf("请输入要删除的商品名称：");
                    scanf("%s",t);
                    while(p!=NULL)
                    {
                        if(strcmp(p->itemname,t)==0)
                            break;
                        else
                        {
                            p0=p;
                            p=p->next;
                        }
                    }
                    if(p==NULL)
                    {
                        printf("没有找到相对应的商品，请重新输入！");
                        continue;
                    }
                    else
                    {
                        tlink tmp;
                        tmp=p;
                        p=p->next;
                        p0->next=p;
                        free(tmp);
                        break;
                    }
                }
            }
            break;
        }
        else
        {
            printf("请输入正确的编号！");
            continue;
        }
    }
    return head;
}

int min(int a, int b, int c)
{
    int smallest=a;
    if (b<smallest)
        smallest=b;
    if (c<smallest)
        smallest=c;
    return smallest;
}

int editDistance(char *str1, char *str2)           //字符串编辑距离
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int dp[len1+1][len2+1];
    for(int i=0;i<=len1;i++)
        dp[i][0]=i;
    for (int j=0;j<=len2;j++)
        dp[0][j]=j;
    for (int i = 1; i <= len1; i++)
        for (int j=1;j<=len2;j++)
        {
            int cost=str1[i-1]==str2[j-1]?0:1;
            dp[i][j]=min(dp[i-1][j]+1,       // deletion
                         dp[i][j-1]+1,       // insertion
                         dp[i-1][j-1]+cost); // substitution
        }
    return dp[len1][len2];
}

int main()
{
    printf("\n\n\t\t\t\t\t正在检查资源完整性。。。");
    int lll=0;
    FILE* fp;
    fp=fopen("yonghushu.txt","r");
    if(fp==NULL)
    {
        fp=fopen("yonghushu.txt","w+");
        int lll=0;
        fprintf(fp,"%d",lll);
        fclose(fp);
    }else{fclose(fp);}
    fp=fopen("allaccounts.txt","r");
    if(fp==NULL)
    {
        fp=fopen("allaccounts.txt","w+");
        fclose(fp);
    }else{fclose(fp);}
    fp=fopen("allorders.txt","r");
    if(fp==NULL)
    {
        fp=fopen("allorders.txt","w+");
        fclose(fp);
    }else{fclose(fp);}
    fp=fopen("dingdanshu.txt","r");
    if(fp==NULL)
    {
        fp=fopen("dingdanshu.txt","w+");
        fprintf(fp,"%d",lll);
        fclose(fp);
    }else{fclose(fp);}
    fp=fopen("manager.txt","r");
    if(fp==NULL)
    {
        fp=fopen("manager.txt","w+");
        int g=999999999;
        fprintf(fp," %d %d",g,g);
        fclose(fp);
    }else{fclose(fp);}
    fp=fopen("allitems.txt","r");
    if(fp==NULL)
    {
        fp=fopen("allitems.txt","w+");
        fclose(fp);
    }else{fclose(fp);}
    sleep(1);
    system("cls");
    printf("\n\n\t\t\t\t\t玩命加载中。。。");
    sleep(1);
    system("cls");
    printf("\t\t\t\t\t\t酒水批发系统-v6.2.3.0\n");
	    printf("\n\n\t\t\t\t\t您是...?\n");
	printf("\t\t\t\t\t1.管理员    2.用户\n\t\t\t\t\t");
	int choose;
	scanf("%d", &choose);
	if (choose == 2)
	{
		while (login1 == 0)
		{
			printf("\t\t\t\t\t1.登录   2.注册\n");
			int b;
			scanf("\t\t\t\t\t %d", &b);
			if (b == 1)
			{
				int num, p = 0;
				while (p == 0)
				{
					fp = fopen("allaccounts.txt", "r");
					printf("\t\t\t\t\t请输入您的账号:");
					scanf("%d", &num);
					p = searchuser(num);
				}
			}
			else
			{
				struct account add;
				int yonghu;
				FILE* shu;
				shu = fopen("yonghushu.txt", "r");
				fscanf(shu,"%d",&yonghu);
				fclose(shu);
				shu = fopen("yonghushu.txt", "w");
				yonghu++;
				fprintf(shu,"%d",yonghu);
				fclose(shu);
				fp = fopen("allaccounts.txt", "a");
				add.number = (10000000 + yonghu);
				printf("\t\t\t\t\t您的帐号是:%d\n", (10000000 + yonghu));
				printf("\t\t\t\t\t请设置密码:");
				int set;
				scanf("%d", &set);
				add.password = set;
				printf("\t\t\t\t\t请设置网点地址:");
				char d[200];
				scanf("%s",add.address);
				add.level=1;
				add.money=0;
                fprintf(fp," %d %d %s %d %f\n",add.number,add.password,add.address,add.level,add.money);
				printf("\t\t\t\t\t账号注册成功\n");
				fclose(fp);
			}
		}
    struct cell* top;
    top=(struct cell*)malloc(sizeof(struct cell));
    top->next=NULL;
    top->dingdan=1;
    top=readorders(top);
    struct item* itop;
    itop=(struct item*)malloc(sizeof(struct item));
    itop->next=NULL;
    itop=readitems(itop);
    readsum(top);
    int k;
    int n;
    printf("\t\t\t\t\t\t酒水批发系统(用户端)\n\n");
    printf("-------------------------------------------------------主菜单-----------------------------------------------------------\n");
    printf("|\t\t\t\t\t\t1.购买商品\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t2.查看购买记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t3.查看商品库存\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t4.查看用户信息\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t5.退出系统\t\t\t\t\t\t\t\t|\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t请输入功能编号:");
    scanf("%d",&n);
    while(1)
    {
        if(n==1)
        {
            top=addition1(top,itop);
            top=changeorders(top);
            itop=changeitems(itop);
            system("pause");
            system("cls");
            printf("\t\t\t\t\t\t酒水批发系统(用户端)\n\n");
            printf("-------------------------------------------------------主菜单-----------------------------------------------------------\n");
            printf("|\t\t\t\t\t\t1.购买商品\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t2.查看购买记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t3.查看商品库存\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t4.查看用户信息\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t5.退出系统\t\t\t\t\t\t\t\t|\n");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t\t\t请输入功能编号:");
            scanf("%d",&n);
            continue;
        }
	     else if(n==2)
        {
            userprint(top);
            system("pause");
            system("cls");
            printf("\t\t\t\t\t\t酒水批发系统(用户端)\n\n");
            printf("-------------------------------------------------------主菜单-----------------------------------------------------------\n");
             printf("|\t\t\t\t\t\t1.购买商品\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t2.查看购买记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t3.查看商品库存\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t4.查看用户信息\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t5.退出系统\t\t\t\t\t\t\t\t|\n");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t\t\t请输入功能编号:");
            scanf("%d",&n);
            continue;
	     }
	    else if(n==5)
        {
            break;
	    }
	    else if(n==3)
        {
            itemprintalluser(itop,top);
            system("pause");
            system("cls");
            printf("\t\t\t\t\t\t酒水批发系统(用户端)\n\n");
            printf("-------------------------------------------------------主菜单-----------------------------------------------------------\n");
             printf("|\t\t\t\t\t\t1.购买商品\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t2.查看购买记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t3.查看商品库存\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t4.查看用户信息\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t5.退出系统\t\t\t\t\t\t\t\t|\n");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t\t\t请输入功能编号:");
            scanf("%d",&n);
            continue;
        }
        else if(n==4)
        {
            usercheck(top);
            system("pause");
            system("cls");
            printf("\t\t\t\t\t\t酒水批发系统(用户端)\n\n");
            printf("-------------------------------------------------------主菜单-----------------------------------------------------------\n");
            printf("|\t\t\t\t\t\t1.购买商品\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t2.查看购买记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t3.查看商品库存\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t4.查看用户信息\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t5.退出系统\t\t\t\t\t\t\t\t|\n");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t\t\t请输入功能编号:");
            scanf("%d",&n);
            continue;
        }
        else
        {
            printf("请输入正确的数字编号！\n");
            continue;
        }
    }
	}
	else                      //管理员系统
    {
    while (login2 == 0)
		{
					printf("\t\t\t\t\t请输入您的账号：");
					int num,p;
					scanf("%d", &num);
					p = searchmanager(num);
				}
    struct cell* top;
    top=(struct cell*)malloc(sizeof(struct cell));
    top->next=NULL;
    top->dingdan=1;
    top=readorders(top);
    struct cell* p;
    p=top->next;
    while(p!=NULL)
    {
        sumplus+=p->sum;
        p=p->next;
    }
    struct item* itop;
    itop=(struct item*)malloc(sizeof(struct item));
    itop->next=NULL;
    itop=readitems(itop);
    int k;
    int n;
    printf("\t\t\t\t\t\t酒水批发系统(管理员端)\n\n");
    printf("-------------------------------------------------------主菜单-----------------------------------------------------------\n");
    printf("|\t\t\t\t\t\t1.增加订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t2.修改订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t3.删除订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t4.打印全部订单记录\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t5.输出给定时间范围内的订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t6.按照客户姓名寻找订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t7.按照商品名称打印订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t8.商品入库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t9.商品出库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t10.打印库存\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t11.检查赠品情况\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t12.重置系统\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t13.退出系统\t\t\t\t\t\t\t\t|\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t请输入功能编号:");
    scanf("%d",&n);
    while(1)
    {
        if(n==1)                    //增加订单记录
        {
            top=addition(top,itop);
            top=changeorders(top);
            itop=changeitems(itop);
            system("pause");
            system("cls");
            printf("\t\t\t\t\t\t酒水批发系统(管理员端)\n\n");
            printf("-------------------------------------------------------主菜单-----------------------------------------------------------\n");
            printf("|\t\t\t\t\t\t1.增加订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t2.修改订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t3.删除订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t4.打印全部订单记录\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t5.输出给定时间范围内的订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t6.按照客户姓名寻找订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t7.按照商品名称打印订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t8.商品入库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t9.商品出库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t10.打印库存\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t11.检查赠品情况\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t12.重置系统\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t13.退出系统\t\t\t\t\t\t\t\t|\n");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t\t\t请输入功能编号:");
            scanf("%d",&n);
            continue;
        }
        else if(n==2)       //修改订单记录
        {
            top=correct(top,itop);
            top=changeorders(top);
            itop=changeitems(itop);
            system("pause");
            system("cls");
            printf("\t\t\t\t\t\t酒水批发系统(管理员端)\n\n");
            printf("-------------------------------------------------------主菜单-----------------------------------------------------------\n");
            printf("|\t\t\t\t\t\t1.增加订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t2.修改订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t3.删除订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t4.打印全部订单记录\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t5.输出给定时间范围内的订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t6.按照客户姓名寻找订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t7.按照商品名称打印订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t8.商品入库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t9.商品出库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t10.打印库存\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t11.检查赠品情况\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t12.重置系统\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t13.退出系统\t\t\t\t\t\t\t\t|\n");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t\t\t请输入功能编号:");
            scanf("%d",&n);
            continue;
        }
        else if(n==4)               //打印全部订单记录
        {
            printall(top);
            printf("总营收为:%.2lf\n",sumplus);
            system("pause");
            system("cls");
            printf("\t\t\t\t\t\t酒水批发系统(管理员端)\n\n");
            printf("-------------------------------------------------------主菜单-----------------------------------------------------------\n");
            printf("|\t\t\t\t\t\t1.增加订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t2.修改订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t3.删除订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t4.打印全部订单记录\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t5.输出给定时间范围内的订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t6.按照客户姓名寻找订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t7.按照商品名称打印订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t8.商品入库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t9.商品出库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t10.打印库存\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t11.检查赠品情况\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t12.重置系统\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t13.退出系统\t\t\t\t\t\t\t\t|\n");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t\t\t请输入功能编号:");
            scanf("%d",&n);
            continue;
        }
        else if(n==5)     //输出给定时间范围内的订单记录
        {
            top=fromto(top);
            system("pause");
            system("cls");
            printf("\t\t\t\t\t\t酒水批发系统(管理员端)\n\n");
            printf("-------------------------------------------------------主菜单-----------------------------------------------------------\n");
            printf("|\t\t\t\t\t\t1.增加订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t2.修改订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t3.删除订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t4.打印全部订单记录\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t5.输出给定时间范围内的订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t6.按照客户姓名寻找订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t7.按照商品名称打印订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t8.商品入库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t9.商品出库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t10.打印库存\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t11.检查赠品情况\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t12.重置系统\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t13.退出系统\t\t\t\t\t\t\t\t|\n");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t\t\t请输入功能编号:");
            scanf("%d",&n);
            continue;
        }
        else if(n==3)               //删除订单
        {
            top=del(top,itop);
            top=changeorders(top);
            itop=changeitems(itop);
            system("pause");
            system("cls");
            printf("\t\t\t\t\t\t酒水批发系统(管理员端)\n\n");
            printf("-------------------------------------------------------主菜单-----------------------------------------------------------\n");
            printf("|\t\t\t\t\t\t1.增加订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t2.修改订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t3.删除订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t4.打印全部订单记录\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t5.输出给定时间范围内的订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t6.按照客户姓名寻找订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t7.按照商品名称打印订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t8.商品入库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t9.商品出库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t10.打印库存\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t11.检查赠品情况\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t12.重置系统\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t13.退出系统\t\t\t\t\t\t\t\t|\n");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t\t\t请输入功能编号:");
            scanf("%d",&n);
            continue;
        }
        else if(n==6)     //按照客户姓名寻找订单记录
        {
            itemdateprint(top);
            system("pause");
            system("cls");
            printf("\t\t\t\t\t\t酒水批发系统(管理员端)\n\n");
            printf("-------------------------------------------------------主菜单-----------------------------------------------------------\n");
            printf("|\t\t\t\t\t\t1.增加订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t2.修改订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t3.删除订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t4.打印全部订单记录\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t5.输出给定时间范围内的订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t6.按照客户姓名寻找订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t7.按照商品名称打印订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t8.商品入库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t9.商品出库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t10.打印库存\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t11.检查赠品情况\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t12.重置系统\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t13.退出系统\t\t\t\t\t\t\t\t|\n");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t\t\t请输入功能编号:");
            scanf("%d",&n);
            continue;
        }
        else if(n==7)           //按照商品名称打印订单记录
        {
            itemprint(top);
            system("pause");
            system("cls");
            printf("\t\t\t\t\t\t酒水批发系统(管理员端)\n\n");
            printf("-------------------------------------------------------主菜单-----------------------------------------------------------\n");
            printf("|\t\t\t\t\t\t1.增加订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t2.修改订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t3.删除订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t4.打印全部订单记录\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t5.输出给定时间范围内的订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t6.按照客户姓名寻找订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t7.按照商品名称打印订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t8.商品入库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t9.商品出库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t10.打印库存\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t11.检查赠品情况\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t12.重置系统\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t13.退出系统\t\t\t\t\t\t\t\t|\n");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t\t\t请输入功能编号:");
            scanf("%d",&n);
            continue;
        }
        else if(n==13)           //退出系统
            break;
        else if(n==12)           //重置系统
        {
            renew();
            system("pause");
            system("cls");
            printf("\t\t\t\t\t\t酒水批发系统(管理员端)\n\n");
            printf("-------------------------------------------------------主菜单-----------------------------------------------------------\n");
            printf("|\t\t\t\t\t\t1.增加订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t2.修改订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t3.删除订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t4.打印全部订单记录\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t5.输出给定时间范围内的订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t6.按照客户姓名寻找订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t7.按照商品名称打印订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t8.商品入库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t9.商品出库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t10.打印库存\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t11.检查赠品情况\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t12.重置系统\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t13.退出系统\t\t\t\t\t\t\t\t|\n");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t\t\t请输入功能编号:");
            scanf("%d",&n);
            continue;
        }
        else if(n==8)          //商品入库
        {
            itop=addgoods(itop);
            itop=changeitems(itop);
            system("pause");
            system("cls");
            printf("\t\t\t\t\t\t酒水批发系统(管理员端)\n\n");
            printf("-------------------------------------------------------主菜单-----------------------------------------------------------\n");
            printf("|\t\t\t\t\t\t1.增加订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t2.修改订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t3.删除订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t4.打印全部订单记录\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t5.输出给定时间范围内的订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t6.按照客户姓名寻找订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t7.按照商品名称打印订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t8.商品入库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t9.商品出库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t10.打印库存\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t11.检查赠品情况\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t12.重置系统\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t13.退出系统\t\t\t\t\t\t\t\t|\n");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t\t\t请输入功能编号:");
            scanf("%d",&n);
            continue;
        }
        else if(n==10)          //打印库存
        {
            itemprintall(itop,top);
            system("pause");
            system("cls");
            printf("\t\t\t\t\t\t酒水批发系统(管理员端)\n\n");
            printf("-------------------------------------------------------主菜单-----------------------------------------------------------\n");
            printf("|\t\t\t\t\t\t1.增加订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t2.修改订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t3.删除订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t4.打印全部订单记录\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t5.输出给定时间范围内的订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t6.按照客户姓名寻找订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t7.按照商品名称打印订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t8.商品入库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t9.商品出库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t10.打印库存\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t11.检查赠品情况\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t12.重置系统\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t13.退出系统\t\t\t\t\t\t\t\t|\n");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t\t\t请输入功能编号:");
            scanf("%d",&n);
            continue;
        }
        else if(n==11)         //检查赠品情况
        {
            giftcheck(top);
            system("pause");
            system("cls");
            printf("\t\t\t\t\t\t酒水批发系统(管理员端)\n\n");
            printf("-------------------------------------------------------主菜单-----------------------------------------------------------\n");
            printf("|\t\t\t\t\t\t1.增加订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t2.修改订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t3.删除订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t4.打印全部订单记录\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t5.输出给定时间范围内的订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t6.按照客户姓名寻找订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t7.按照商品名称打印订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t8.商品入库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t9.商品出库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t10.打印库存\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t11.检查赠品情况\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t12.重置系统\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t13.退出系统\t\t\t\t\t\t\t\t|\n");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t\t\t请输入功能编号:");
            scanf("%d",&n);
            continue;
        }
        else if(n==9)                   //商品出库
        {
            itop=itemdel(itop);
            itop=changeitems(itop);
            system("pause");
            system("cls");
            printf("\t\t\t\t\t\t酒水批发系统(管理员端)\n\n");
            printf("-------------------------------------------------------主菜单-----------------------------------------------------------\n");
            printf("|\t\t\t\t\t\t1.增加订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t2.修改订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t3.删除订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t4.打印全部订单记录\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t5.输出给定时间范围内的订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t6.按照客户姓名寻找订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t7.按照商品名称打印订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t8.商品入库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t9.商品出库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t10.打印库存\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t11.检查赠品情况\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t12.重置系统\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t13.退出系统\t\t\t\t\t\t\t\t|\n");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t\t\t请输入功能编号:");
            scanf("%d",&n);
            continue;
        }
        else
        {
            printf("\t\t\t\t\t请输入正确的数字编号!\n");
            system("pause");
            system("cls");
            printf("\t\t\t\t\t\t酒水批发系统(管理员端)\n\n");
            printf("-------------------------------------------------------主菜单-----------------------------------------------------------\n");
            printf("|\t\t\t\t\t\t1.增加订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t2.修改订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t3.删除订单记录\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t4.打印全部订单记录\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t5.输出给定时间范围内的订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t6.按照客户姓名寻找订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t7.按照商品名称打印订单记录\t\t\t\t\t\t|\n|\t\t\t\t\t\t8.商品入库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t9.商品出库\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t10.打印库存\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t11.检查赠品情况\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t12.重置系统\t\t\t\t\t\t\t\t|\n|\t\t\t\t\t\t13.退出系统\t\t\t\t\t\t\t\t|\n");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t\t\t请输入功能编号:");
            scanf("%d",&n);
            continue;
        }
    }
    return 0;}
}

