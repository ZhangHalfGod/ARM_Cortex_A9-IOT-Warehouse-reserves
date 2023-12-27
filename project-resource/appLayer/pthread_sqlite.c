#include "all.h"
//数据库操作线程
void *pthread_sqlite(void *p)
{
	createTables();  //创建表格

	while(1){
		sem_wait(&SemGoods); //信号量-3 P操作 : 睡眠 
	    if(   sqliteGoods(&Goods)   ) 
			printf("%s : goods --> sqlite3\n\n", __func__);
	}
}
/* 功能：数据库总算法实现函数
 * 参数：pg 货物信息指针
 * 返回值：成功 1  ； 出错 0
 */
int sqliteGoods(goods_t *pg)
{
	int r; //存储 返回值 
	// 1. 打开数据库
	sqlite3 *db;
	r = sqlite3_open("/www/warehouse.db", &db);
	if(r != SQLITE_OK){
		printf("%s %s: sqlite3_open() error %s\n", __FILE__, __func__, sqlite3_errmsg(db));
		sqlite3_close(db);
		return 0;
	}
	// 2. 查找货物原数量
	int num = 0; 
	r = selectGoodsNum(db, pg, &num);
	if(r != 0){  
		// 3. 分析num 
		if(num == 0){
			if(pg->inout == 'I')   r = insertGoods(db, pg); //4. 插入货物
			else{
				printf("%s %s: 此仓库没有货物:%s , 出库操作：无效\n",__FILE__, __func__, pg->name);
				r = 0; 
			}
		}else if(num > 0){
			num = (pg->inout == 'I') ? num+pg->num : num-pg->num;   //计算最新的货物数量 
			if(num > 0)   r = updateGoods(db, pg, num);  //5. 更新货物
			else if(num == 0) r = deleteGoods(db, pg);	 //6. 删除货物 
			else{
				printf("%s %s: 此仓库货物：%s 库存不足, 出库操作：无效\n",__FILE__, __func__, pg->name);
				r = 0;
			}   
		}
	}
	//7. 关闭数据库
	sqlite3_close(db);
	return r; 
}
/* 功能：执行SQL插入货物
 * 参数：db 数据库指针
 *       pg 货物信息指针 
 * 返回值：成功 1 ； 出错 0
 */
int insertGoods(sqlite3 *db, goods_t *pg)
{
	char *errmsg;
	char sql[200] = {0};
	//获得SQL字符串 
	sprintf(sql,
		"insert into goods_%d values(%d,'%s',%d,datetime('now', 'localtime'),'入库%d');",
		pg->devno, pg->devno, pg->name, pg->num, pg->num);
	if( sqlite3_exec(db, sql, NULL,NULL, &errmsg) != SQLITE_OK ){ //执行SQL 
		printf("%s %s : sqlite3_exec() error %s\n",__FILE__,__func__, sqlite3_errmsg(db));
		return 0;
	}
	return 1;
}
/* 功能：执行SQL删除货物
 * 参数：db 数据库指针
 *       pg 货物信息指针 
 * 返回值：成功 1 ； 出错 0
 */
int deleteGoods(sqlite3 *db, goods_t *pg)
{
	char *errmsg;
	char sql[200] = {0};
	//获得SQL字符串 
	sprintf(sql,
		"delete from goods_%d where 货物名='%s';",
		pg->devno,  pg->name);
	if( sqlite3_exec(db, sql, NULL,NULL, &errmsg) != SQLITE_OK ){ //执行SQL 
		printf("%s %s : sqlite3_exec() error %s\n",__FILE__,__func__, sqlite3_errmsg(db));
		return 0;
	}
	return 1;
}
/* 功能：执行SQL更新货物
 * 参数：db 数据库指针
 *       pg 货物信息指针 
 *       num 最新的数量
 * 返回值：成功 1 ； 出错 0
 */
int updateGoods(sqlite3 *db, goods_t *pg, int num)
{
	char *errmsg;
	char sql[200] = {0};
	//获得SQL字符串 
	sprintf(sql,
		"update goods_%d set 数量=%d,更新时间=datetime('now','localtime'),备注='新%s库%d' where 货物名='%s';",
		pg->devno, num, (pg->inout=='I') ? "入":"出",pg->num, pg->name);
	if( sqlite3_exec(db, sql, NULL,NULL, &errmsg) != SQLITE_OK ){ //执行SQL 
		printf("%s %s : sqlite3_exec() error %s\n",__FILE__,__func__, sqlite3_errmsg(db));
		return 0;
	}
	return 1;
}
/* 功能：执行SQL查货物数量 
 * 参数：db 数据库指针
 *       pg 货物信息指针
 *       pnum 出参 查到的货物的数量变量指针
 * 返回值：成功 1 ； 出错 0
 */
int selectGoodsNum(sqlite3 *db, goods_t *pg, int *pnum)
{
	int r;
	char *errmsg;
	char **table;  //查找结果表 
	int row;       //行数
	int column ;   //列数 
	char sql[200] = {0};   
	//获得SQL字符串
	sprintf(sql,
			"select 数量 from goods_%d where 货物名='%s';",
			pg->devno, pg->name);
	r = sqlite3_get_table(db, sql, &table, &row, &column, &errmsg);  //执行SQL 
	if(r != SQLITE_OK){
		printf("%s %s : sqlite3_get_table() error %s\n", __FILE__, __func__, sqlite3_errmsg(db));
		return 0;
	}
	*pnum = 0; 
	if(row > 0){  //有查找结果 
		*pnum = atoi(table[1]);  //将查到的货物数量转为int     table[0] = "数量"  table[1] = "1000"
	}
	sqlite3_free_table(table); //释放表格空间 
	return 1;
}
// 执行SQL创建仓库相关表格
int createTables(void)
{
	int r;
	sqlite3 *db; 
	char *errmsg;
	char sql[200] = {0};
	r = sqlite3_open("/www/warehouse.db", &db); //打开数据库
	if(r != SQLITE_OK){
		printf("%s %s: sqlite3_open() error %s\n", __FILE__, __func__, sqlite3_errmsg(db));
		sqlite3_close(db);
		return 0;
	}
	for(r = 1; r < 3; r++){
		//获得SQL字符串 
		sprintf(sql,
				"create table if not exists goods_%d(仓库号 integer,货物名 varchar(20) primary key,数量 integer,更新时间 varchar(40),备注 varcar(40));",
			    r);
		if( sqlite3_exec(db, sql, NULL,NULL, &errmsg) != SQLITE_OK ){ //执行SQL 
			printf("%s %s : sqlite3_exec() error %s\n",__FILE__,__func__, sqlite3_errmsg(db));
			sqlite3_close(db);
			return 0;
		}
	}
	sqlite3_close(db); //关闭数据库
	return 1;
}
