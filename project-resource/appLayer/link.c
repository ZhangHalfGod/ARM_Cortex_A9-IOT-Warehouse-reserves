#include "all.h"
/* 功能：创建空链表
 * 参数：无
 * 返回值： 成功 链表指针 ； 出错 NULL
 */
linknode_t *createLink(void)
{
	linknode_t *l = (linknode_t *)malloc(sizeof(linknode_t));
	if(NULL == l){
		perror("link.c createLink() : error");
		return NULL;
	}
	l->next = NULL;
	return l;
}
/* 功能：判断链表是否空
 * 参数：l 链表指针 
 * 返回值： 1 空链表 ; 0 非空链表
 */
int isEmpty(linknode_t *l)
{
	return l->next == NULL ;
}
/* 功能：在链表表尾插入
 * 参数：l 链表指针 
 *       a 插入的数据 
 * 返回值：成功 1 ； 出错 0      
 */
int insertLinkEnd(linknode_t *l, data_t a)
{
	linknode_t *pend;  //指向表尾 
	pend = l;          // 从表头一直向后，找到表尾 
	while(pend->next != NULL){
		pend = pend->next; 
	}
	linknode_t *pnew = (linknode_t *)malloc(sizeof(linknode_t));
	if(NULL == pnew){
		perror("link.c insertLinkEnd() error"); 
		return 0;
	}
	pnew->data = a;     // 数据域赋值 
	pnew->next = NULL;  // 指针域赋值 
	pend->next = pnew;  // 将pnew插入到pend的后面 
	return 1;
}
/* 功能：从链表表头删除 ,获得数据值
 * 参数：l 链表指针 
 *       pd 出参 传出删除的节点中的数据值的指针/地址
 * 返回值：成功 1 ； 出错 0      
 */
int deleteLinkHead(linknode_t *l, data_t *pd)
{
	if( isEmpty(l) ) //空链表
		return 0;
	linknode_t *pdel;       // 指向删除的节点
	pdel = l->next; 
	l->next = pdel->next;  // 从链表中将pdel踢出 
	*pd = pdel->data;      // 传出 数据域 
	free(pdel);            // 释放空间 
	return 1;
}
/* 功能：释放链表
 * 参数：l 链表指针
 * 返回值：无
 */
void freeLink(linknode_t *l)
{
	linknode_t *p = l;
	while(l != NULL)
	{
		l = l->next;
		free(p);
		p = l;
	}
}
