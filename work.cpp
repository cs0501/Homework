
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

int main(){
    char buf[MAX_LINE];  /*缓冲区*/
    FILE *fp;            /*文件指针*/
    int len;             /*行字符个数*/
    int len,n,li;             /*所读到的字符下标,li记录单词的长度*/
    string word_ = "abcdefgh";  //代码中读取进的格式为char，设置word_ 用于转存
    string word;        //用于存储所要进行判断的字符串
    if((fp = fopen("D:\\VSCode\\test.txt","r")) == NULL){
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
            else{
                word = word_.substr(0,li);
                if(pairing(word) >= 0){    
                    cout<<word<<endl;
                    total_num++;    
                }
                li = 0;
            }
        }
        word = word_.substr(0,li);
        if(pairing(word)>=0){    
            cout<<word<<endl;
            total_num++;    
        }
    }
    cout<<total_num<<endl;
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