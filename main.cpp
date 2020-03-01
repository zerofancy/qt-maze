#include "widget.h"
#include <QApplication>
#include"stdio.h"
#include<stdlib.h>//调用rand()及srand()函数
#include <time.h>//调用time() 函数
#include"QProgressDialog"
#include"QMessageBox"
#include"QVector"
#include"menu.h"
#include"QSettings"
#define N 5000


/**
走迷宫 by 走迷宫研发组
走迷宫研发组成员：刘海鑫 李睿 李子豪 解亚续 闫河

介绍：
本程序是我们准备QT大作业写的项目。
其中地图生成部分参考了知乎：
https://zhuanlan.zhihu.com/p/27381213
采用“自然分岔法”生成地图。(随机prim算法)

自动寻路使用了深度优先搜索。
其实关于寻路还有好多思路的，比如

1.使角色一直贴着迷宫左墙走，只要迷宫没有环路，一定能走到终点。
2.以起点为根节点构建树，找到包含终点的分支
……

编译环境QT(minGW、msvc2017)【已验证】
运行环境：Windows All(需安装DX以及vc++的运行库）、Linux(需安装OpenCL有关的库)
编译后请自己将图片资源拷贝到输出目录
*/

/**
代码效率测试：
1001^2以上的地图速度明显减慢
9999*9999地图结果：

Process returned 0 (0x0)   execution time : 21.179 s
Press any key to continue.

*/

///空间开不下了，只得减小N

int vis[N][N];//有关自动寻路算法（深搜）模拟的数组
myPoint dat2[N*N];
int po_count=0;

int dat[N][N];//地图数据存储单元
myPoint blue[N*N];
int blue_count=0;
int n;
myPoint po_ch;

Widget*pw;

void po_add(myPoint x)
{
    dat2[po_count]=x;
    po_count++;
}

void po_pop()
{
    po_count--;
}

void init()
{
    for(int i=0; i<n; i++)
    {
        for(int i2=0; i2<n; i++)
        {
            vis[i][i2]=0;
        }
    }
}

myPoint nex_myPoint(myPoint x)
{
    if(dat[x.x-1][x.y]==1&&vis[x.x-1][x.y]==0)
    {
        x.x--;
        vis[x.x][x.y]=1;
        return x;
    }
    if(dat[x.x+1][x.y]==1&&vis[x.x+1][x.y]==0)
    {
        x.x++;
        vis[x.x][x.y]=1;
        return x;
    }
    if(dat[x.x][x.y-1]==1&&vis[x.x][x.y-1]==0)
    {
        x.y--;
        vis[x.x][x.y]=1;
        return x;
    }
    if(dat[x.x][x.y+1]==1&&vis[x.x][x.y+1]==0)
    {
        x.y++;
        vis[x.x][x.y]=1;
        return x;
    }
    ///无符合条件
    x.x=-1;
    return x;
}

void fun4(myPoint bp,myPoint ep)//用于路线提示的算法
{
    myPoint ptmp;
    po_add(bp);
    vis[bp.x][bp.y]=1;
    while((dat2[po_count-1].x!=ep.x||dat2[po_count-1].y!=ep.y)&&po_count>0)
    {
        ptmp=nex_myPoint(dat2[po_count-1]);
        if(ptmp.x==-1)
        {
            po_pop();
            continue;
        }
        po_add(ptmp);
    }
}

int randxy(int a,int b)//随机数a~b
{
    b++;
    return rand() % (b - a)   +   a;
}

int yj(myPoint p)//碰撞检测（部分）
{
    if(p.x<0)
    {
        return 1;
    }
    if(p.y<0)
    {
        return 1;
    }
    if(p.x>n-1)
    {
        return 1;
    }
    if(p.y>n-1)
    {
        return 1;
    }
    return 0;
}

myPoint gett(myPoint x)//当前点上方的点
{
    x.y--;
    return x;
}

myPoint getb(myPoint x)
{
    x.y++;
    return x;
}

myPoint getl(myPoint x)
{
    x.x--;
    return x;
}

myPoint getr(myPoint x)
{
    x.x++;
    return x;
}

myPoint getmyPoint(int x,int y)
{
    myPoint a;
    a.x=x;
    a.y=y;
    return a;
}

int getpdat(myPoint x)//获取地图数据
{
    return dat[x.x][x.y];
}

void setpdat(myPoint p,int value)
{
    dat[p.x][p.y]=value;
}

void blue_add(myPoint x)
{
    blue[blue_count]=x;
    blue_count++;
}

void blue_del(int n)
{
    blue[n]=blue[blue_count-1];
    blue_count--;
}

int blue_getnum()
{
    return randxy(0,blue_count-1);
}

void fun1()//生成步骤1
{
    for(int i=0; i<n; i++)
    {
        for(int i2=0; i2<n; i2++)
        {
            dat[i][i2]=0;
        }
    }
    for(int i=1; i<n-1; i++)
    {
        for(int i2=1+(i+1)%2; i2<n-1; i2+=2)
        {
            dat[i][i2]=1;
        }
    }
}

void findblue(myPoint t)
{
    myPoint t1,t2,t3,t4;
    /**
        t1
    t2      t3
        t4
    */
    myPoint tt1,tt2,tt3,tt4;
    t1=gett(t);
    t2=getl(t);
    t3=getr(t);
    t4=getb(t);
    tt1=gett(t1);
    tt2=getl(t2);
    tt3=getr(t3);
    tt4=getb(t4);
    if(!yj(tt1))
    {
        if(getpdat(tt1)==1)
        {
            blue_add(t1);
            setpdat(t1,2);
        }
    }
    if(!yj(tt2))
    {
        if(getpdat(tt2)==1)
        {
            blue_add(t2);
            setpdat(t2,2);
        }
    }
    if(!yj(tt3))
    {
        if(getpdat(tt3)==1)
        {
            blue_add(t3);
            setpdat(t3,2);
        }
    }
    if(!yj(tt4))
    {
        if(getpdat(tt4)==1)
        {
            blue_add(t4);
            setpdat(t4,2);
        }
    }
}

void fun2()//生成步骤2
{
    myPoint tmp;
    int tmpblue;
    myPoint t,t1,t2,t3,t4;
    /**
        t1
    t2  t   t3
        t4
    */
    tmp=getmyPoint(1,1);
    blue_add(getr(tmp));
    blue_add(getb(tmp));
    ///1 for yellow, 0 for gray
    dat[1][2]=dat[2][1]=2;///2 for blue
    dat[1][1]=3;///3 for red 4 for red2
    while(blue_count)
    {
        tmpblue=blue_getnum();
        t=blue[tmpblue];
        t1=gett(t);
        t2=getl(t);
        t3=getr(t);
        t4=getb(t);
        blue_del(tmpblue);
        setpdat(t,0);
        if(!yj(t1))
        {
            if(getpdat(t1)==3)
            {
                if(getpdat(t4)==1)
                {
                    setpdat(t4,3);
                    setpdat(t,4);
                    findblue(t4);
                }
            }
        }
        else
        {
            if(getpdat(t4)==1)
            {
                setpdat(t4,3);
                setpdat(t,4);
                findblue(t4);
            }
        }
        if(!yj(t2))
        {
            if(getpdat(t2)==3)
            {
                if(getpdat(t3)==1)
                {
                    setpdat(t3,3);
                    setpdat(t,4);
                    findblue(t3);
                }
            }
        }
        else
        {
            if(getpdat(t3)==1)
            {
                setpdat(t3,1);
                setpdat(t,4);
                findblue(t3);
            }
        }
        if(!yj(t3))
        {
            if(getpdat(t3)==3)
            {
                if(getpdat(t2)==1)
                {
                    setpdat(t2,3);
                    setpdat(t,4);
                    findblue(t2);
                }
            }
        }
        else
        {
            if(getpdat(t2)==1)
            {
                setpdat(t2,3);
                setpdat(t,4);
                findblue(t2);
            }
        }
        if(!yj(t4))
        {
            if(getpdat(t4)==3)
            {
                if(getpdat(t1)==1)
                {
                    setpdat(t1,3);
                    setpdat(t,4);
                    findblue(t1);
                }
            }
        }
        else
        {
            if(getpdat(t1)==1)
            {
                setpdat(t1,3);
                setpdat(t,4);
                findblue(t1);
            }
        }
    }
}

void fun3()//生成步骤3
{
    for(int i=0; i<n; i++)
    {
        for(int i2=0; i2<n; i2++)
        {
            if(dat[i][i2]==3||dat[i][i2]==4)
            {
                dat[i][i2]=1;
            }
            else
            {
                dat[i][i2]=0;
            }
        }
    }
}

void printmap(Widget&w)//打印地图
{
    QProgressDialog prog1("Making the map...", "Abort", 0, n, &w);
    prog1.setWindowModality(Qt::WindowModal);
    for(int i=0; i<n; i++)
    {
        for(int i2=0; i2<n; i2++)
        {
            if(i==n-2&&i2==n-2)//结束点
            {
                //printf("%c%c", 0xa1, 0xf5);
                w.showpic(5,i2,i,50);
                continue;
            }
            if(dat[i][i2]==1)//道路
            {
                //printf("  ");
                w.showpic(1,i2,i,50);
            }
            else//墙
            {
                w.showpic(2,i2,i,50);
            }
        }
        prog1.setValue(i);
        if(prog1.wasCanceled()){
            QProcess::startDetached(qApp->applicationFilePath(), QStringList());
            QApplication::closeAllWindows();
            exit(0);
        }
    }
}

int canup()//能否上移
{
    if(getpdat(gett(po_ch))==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int candown()
{
    if(getpdat(getb(po_ch))==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int canleft()
{
    if(getpdat(getl(po_ch))==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int canright()
{
    if(getpdat(getr(po_ch))==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool isWin(){
    if(po_ch.x==n-2&&po_ch.y==n-2){
        return true;
    }
    return false;
}

void isEnd(){
    if(isWin()){
        pw->win();
    }
}

bool goUp(){
    if(canup()){
        po_ch.y--;
        pw->setLeadPos(po_ch.y,po_ch.x);
        isEnd();
        return true;
    }
    return false;
}

bool goDown(){
    if(candown()){
        po_ch.y++;
        pw->setLeadPos(po_ch.y,po_ch.x);
        isEnd();
        return true;
    }
    return false;
}

bool goLeft(){
    if(canleft()){
        po_ch.x--;
        pw->setLeadPos(po_ch.y,po_ch.x);
        isEnd();
        return true;
    }
    return false;
}

bool goRight(){
    if(canright()){
        po_ch.x++;
        pw->setLeadPos(po_ch.y,po_ch.x);
        isEnd();
        return true;
    }
    return false;
}

QVector<myPoint> getTip(){
    myPoint pend;
    myPoint pbeg;
    QVector<myPoint> tmp_vector;
    pend.x=n-2;
    pend.y=n-2;
    pbeg=po_ch;
    fun4(pbeg,pend);
    for(int i=0; i<po_count; i++)
    {
        tmp_vector.append(dat2[i]);
        //showpic(4,dat2[i].y,dat2[i].x,50,2);
        //gotoxy(dat2[i].y*2,dat2[i].x);
        //printf("<>");
    }
    return tmp_vector;
}

void newGame(Widget*w, int mapsize_n,QString mazestyle)
{
    w->mapsize_n=mapsize_n;
    w->mazestye=mazestyle;
    w->start(goUp,goDown,goLeft,goRight);
    w->passGetTip(getTip);
    w->show();
    pw= w;
    n=mapsize_n;
    srand(time(0));
    po_ch.x=1;
    po_ch.y=1;
    fun1();
    fun2();
    fun3();
    printmap(*w);
//    w.setScrollBar(n);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSettings ini1("set.ini", QSettings::IniFormat);

    int val_now=ini1.value("/set/now").toString().toInt();
    val_now++;
    if(val_now>ini1.value("/set/count").toString().toInt()){
        val_now=1;
    }
    ini1.setValue("/set/now",val_now);
    qDebug()<<val_now;
    Menu mnu;
    Widget *w;
    mnu.exec();
    if(mnu.S_result==1){
        if(mnu.size_N%2==0){
            mnu.size_N--;
        }
        w=new Widget;
        newGame(w,mnu.size_N,QString::number(val_now, 10));
    }
    return a.exec();
}
