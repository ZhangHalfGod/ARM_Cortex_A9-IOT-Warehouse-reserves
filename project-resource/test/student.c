
//定义全局变量存储年龄(静态：共享)
static int age;

//设置年龄
void set_age(int n){
 //参数1：年龄
 //返回值：无
 age = n;
}

//获得年龄
int get_age(){
 //参数1：无
 //返回值：年龄内容
 return age;
}