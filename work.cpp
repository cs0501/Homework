
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#include <iostream>
#include <bits/stdc++.h>
#define MAX_LINE 1024

using namespace std;

string stand[] = {"auto","break","case","char","const","continue","default","do",
    "double","else","enum","extern","float","for","goto","if",
    "int","long","register","return","short","signed","sizeof","static",
    "struct","switch","typedef","union","unsigned","void","volatile","while"};

int case_nums[10000];      //用于存储每个switch后case的数量

int pairing(string target); //配对成功则返回该关键字的号码，配对失败，则返回-1；

int main(){
    int total_num = 0;
    int switch_num = -1;
    int case_num = 0;
    int else_num = 0;       //else_num用于存储if-else结构和if-else if-else结构的总数量
    int if_else = 0;        //用于存储if-else结构的数量
    int pairs;              //用于存储pairing函数的返回值
    stack<string> if_jd;    //判断if-else结构是否计数
    if_jd.push("if");
    int senten_jd = 0;      //判断是否处于语句中，为奇数时表示在语句中，不需要识别关键字
    int annot_jd = 0;       //用于定义是否处于长注释中
    char buf[MAX_LINE];  /*缓冲区*/
    FILE *fp;            /*文件指针*/
    int len,n,li;             /*所读到的字符下标,li记录单词的长度*/
    string word_ = "abcdefgh";  //代码中读取进的格式为char，设置word_ 用于转存
    string word;        //用于存储所要进行判断的字符串
    char link[100];        //用于存储文件地址
    int level;          //存储实现等级
    cin>>link>>level;
    if((fp = fopen(link,"r")) == NULL){
        perror("fail to read");
        exit (1) ;
    }
    while(fgets(buf,MAX_LINE,fp) != NULL){
        li = 0;   //记录每个只包含字母的子串的长度
        len = strlen(buf);
        buf[len-1] = '\0';  /*去掉换行符*/
        for(int i = 0;i < len-1;i++){
            if((buf[i] >='a'&&buf[i] <= 'z')){
                word_[li] = buf[i];
                li++;
            }
            else if(buf[i] == '/' && buf[i+1] == '/') break;  //当一行中出现注释时，直接跳过这一行
            else if(buf[i] == '"') {            //当出现引号时，改变判断状态
                senten_jd++; 
                li =0;
            }                              
            else if(buf[i] == '/' && buf[i+1] == '*' && annot_jd == 0) {    //当annot_jd为 1 时进入长注释
                annot_jd = 1; 
                li = 0;
            }    
            else if(buf[i] == '*' && buf[i+1] == '/' && annot_jd == 1) {    //当annot_jd为 0 时离开长注释
                annot_jd = 0; 
                li = 0;
            } 
            else if(buf[i] == '}'){
                while (if_jd.top() != "{")  if_jd.pop();
                if_jd.pop();    
            } 
            else{
                word = word_.substr(0,li);
                pairs = pairing(word);
                if(pairs >= 0 && senten_jd%2 == 0 && annot_jd == 0){    
                    if(pairs == 25){         //对每个 switch 后的 case 进行计数和存储
                        if(switch_num == -1) switch_num++;
                        else{
                            case_nums[switch_num++] = case_num;
                            case_num = 0;
                        }    
                    }
                    else if(pairs == 2) case_num++;             //遇到 case 时计数
                    else if(pairs == 15) if_jd.push("if");    //遇到 if 时将 if 入栈
                    else if(pairs == 9){
                        if(buf[i] == ' ' && buf[i+1] == 'i' && buf[i+2] == 'f'){
                            total_num++;
                            buf[i] = buf[i+1] = ' ';
                            if(if_jd.top() == "if") {
                                if_jd.pop();
                            }
                        }
                        else{
                            else_num++;
                            if(if_jd.top() == "if"){
                                if_else++;
                                if_jd.pop();  
                            }
                        }
                    }
                    total_num++;    
                }
                if(buf[i] == '{') if_jd.push("{");
                li = 0;
            }
        }
    }
    if(case_num > 0) case_nums[switch_num++] = case_num;
    cout<<"total num: "<<total_num<<endl;
    cout<<"switch num: "<<switch_num<<endl;
    cout<<"case num: ";
    for(int i = 0; i < switch_num; i++) cout<<case_nums[i]<<" ";
    cout<<endl;
    cout<<"if-else num: "<<if_else<<endl;
    cout<<"if-elseif-else num: "<<else_num - if_else<<endl;
    system("pause");
    return 0;
}

int pairing(string target){
    int head = 0,tail = 31,k;
    while(head <= tail){
        k = (head + tail)/2;
        if(target.compare(stand[k]) < 0){
            tail = k-1;
        }
        else if(target.compare(stand[k]) > 0){
            head = k+1;
        }
        else return k;
    }
    return -1;
}
