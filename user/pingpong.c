#include <kernel/types.h>
#include <user/user.h>
#include "kernel/stat.h"
#include "kernel/fs.h"


int main(){
    //pipe1(p1)��д�˸����̣������ӽ���
    //pipe2(p2)��д���ӽ��̣����˸�����
    int p1[2],p2[2];
    //���ش�����ַ����飺һ���ֽ�
    char buffer[] = {'X'};
    //�����ַ�����ĳ���
    long length = sizeof(buffer);
    //������д���ӽ��̶���pipe
    pipe(p1);
    //�ӽ���д�������̶���pipe
    pipe(p2);
    //�ӽ���
    if(fork() == 0){
        //�ص����õ�p1[1]��p2[0]
        close(p1[1]);
        close(p2[0]);
		//�ӽ��̴�pipe1�Ķ��ˣ���ȡ�ַ�����
		if(read(p1[0], buffer, length) != length){
			printf("a--->b read error!");
			exit();
		}
		//��ӡ��ȡ�����ַ�����
		printf("%d: received ping\n", getpid());
		//�ӽ�����pipe2��д�ˣ�д���ַ�����
		if(write(p2[1], buffer, length) != length){
			printf("a<---b write error!");
			exit();
		}
        exit();
    }
    //�ص����õ�p1[0]��p2[1]
    close(p1[0]);
    close(p2[1]);
	//��������pipe1��д�ˣ�д���ַ�����
	if(write(p1[1], buffer, length) != length){
		printf("a--->b write error!");
		exit();
	}
	//�����̴�pipe2�Ķ��ˣ���ȡ�ַ�����
	if(read(p2[0], buffer, length) != length){
		printf("a<---b read error!");
		exit();
	}
	//��ӡ��ȡ���ַ�����
	printf("%d: received pong\n", getpid());
    //�ȴ��������˳�
    wait();
	exit();
}
