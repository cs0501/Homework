
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<iostream>
#include<bits/stdc++.h>
#define MAX_LINE 1024

using namespace std;

string stand[]={"auto","break","case","char","const","continue","default","do",
    "double","else","enum","extern","float","for","goto","if",
    "int","long","register","return","short","signed","sizeof","static",
    "struct","switch","typedef","union","unsigned","void","volatile","while"};

int case_nums[10000];      //用于存储每个switch后case的数量

int pairing(string target); //配对成功则返回该关键字的号码，配对失败，则返回-1；

int main(){
    int total_num = 0;
    int switch_num = -1;
    int case_num = 0;
    int pairs;               //用于存储pairing函数的返回值
    int senten_jd = 0;      //判断是否处于语句中，为奇数时表示在语句中，不需要识别关键字
    int annot_jd = 0;       //用于定义是否处于长注释中
    char buf[MAX_LINE];  /*缓冲区*/
    FILE *fp;            /*文件指针*/
    int len,n,li;             /*所读到的字符下标,li记录单词的长度*/
    string word_ = "abcdefgh";  //代码中读取进的格式为char，设置word_ 用于转存
    string word;        //用于存储所要进行判断的字符串
    if((fp = fopen("D:\\VSCode\\test1.txt","r")) == NULL){
        perror("fail to read");
        exit (1) ;
    }
    while(fgets(buf,MAX_LINE,fp) != NULL){
        li = 0;   //记录每个只包含字母的子串的长度
        len = strlen(buf);
        buf[len-1] = '\0';  /*去掉换行符*/
        cout<<buf<<endl;
        for(int i = 0;i < len-1;i++){
            if((buf[i] >='a'&&buf[i] <= 'z')){
                word_[li] = buf[i];
                li++;
            }
            else if(buf[i] == '/' && buf[i+1] == '/') break;  //当一行中出现注释时，直接跳过这一行
            else if(buf[i] == '"') {senten_jd++; li =0;}             //当出现引号时，改变判断状态
            else if(buf[i] == '/' && buf[i+1] == '*' && annot_jd == 0) {annot_jd = 1; li = 0;}    //当annot_jd为1时进入长注释
            else if(buf[i] == '*' && buf[i+1] == '/' && annot_jd == 1) {annot_jd = 0; li = 0;}    //当annot_jd为0时离开长注释
            else{
                word = word_.substr(0,li);
                pairs = pairing(word);
                if(pairs >= 0 && senten_jd%2 == 0 && annot_jd == 0){    
                    if(pairs == 25){         //对每个switch后的case进行计数和存储
                        if(switch_num == -1) switch_num++;
                        else{
                            case_nums[switch_num++] = case_num;
                            case_num = 0;
                        }    
                    }
                    else if(pairs == 2) case_num++;             //遇到case时计数
                    cout<<word<<endl;
                    total_num++;    
                }
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
