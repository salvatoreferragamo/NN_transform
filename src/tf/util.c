/*
 * Author:HanRuobing
 * Created on :2018-2-11
 * Description : Refer to util.h
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "util.h"
#define MAXN 100
char* name_list[MAXN];
int id_list[MAXN];
struct node* node_list[MAXN];
int tail = 0;
struct node* new_node(char* node_op_name,int num,...)//construct node of NN DAG
{
    struct node* tmp = (struct node*)malloc(sizeof(struct node));
    va_list valist;
    va_start(valist,num);
    tmp->op_name = node_op_name;
    tmp->input_cnt = num;
    tmp->input = malloc(num * sizeof(struct node*));
    int i;
    for(i = 0;i<num;i++)
        tmp->input[i] = va_arg(valist, struct node*);
    va_end(valist);
    return tmp;
}
char* concat_str(int num,...)
{
    va_list valist;
    va_start(valist,num);
    //TODO:remove constant number
    char* res = malloc(1000 * sizeof(char));
    int i = 0;
    for(i = 0;i<num;i++)
    {
        char* t = va_arg(valist,char*);
        strcat(res,t);
    }
    va_end(valist);
    return res;
}
void yyerror(char*s,...) //变长参数错误处理函数
{
        va_list ap;
        va_start(ap,s);
        vfprintf(stderr,s,ap);
        fprintf(stderr,"\n");
        va_end(ap);
}
char* get_name(char* raw_name)
{
    int i;
    for(i = 0;i<tail;i++)
        if(!strcmp(raw_name,name_list[i]))
            break;
    if(i==tail)
    {
        tail++;
        name_list[i] = raw_name;
    }
}

struct node* get_node(char* variable_name)
{
    int i;
    for(i = 0; i<tail;i++)
        if(!strcmp(variable_name,name_list[i]))
            break;
    if(i==tail)
    {
        fprintf(stderr,"Don't have name %s\n",variable_name);
        return NULL;
    }
    return node_list[i]; 
}

void add_node(char* node_name,struct node* p)
{
    int i;
    for(i = 0; i<tail;i++)
        if(!strcmp(node_name,name_list[i]))
            break;
    if(i==tail)
        tail++;
    node_list[i] = p;
    name_list[i] = node_name;
}
int main()
{
    return yyparse();
}
