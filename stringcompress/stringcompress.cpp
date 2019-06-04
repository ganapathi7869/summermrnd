#include<stdio.h>
#include<stdlib.h>
int writenumber(char *str, int number, int write){
	char strnum[100];
	int i = 0;
	while (number > 0){
		strnum[i++] = number % 10 + '0';
		number /= 10;
	}
	for (int j = i - 1; j > -1; j--){
		str[write++] = strnum[j];
	}
	return write;
}
void compress(char *str){
	int i = 0;
	int write = 0;
	char prev = str[0];
	int prevcn = 0;
	while (str[i] != '\0'){
		if (prev == str[i]){
			prevcn++;
			i++; continue;
		}
		if (prevcn == 1){
			str[write++] = prev;
			prev = str[i];
			prevcn = 1; i++;
		}
		else if (prevcn > 1){
			str[write++] = prev;
			prev = str[i];
			write=writenumber(str, prevcn,write);
			prevcn = 1; i++;
		}
	}
	if (prevcn){
		str[write++] = prev;
		if (prevcn > 1) write = writenumber(str, prevcn, write);
	}
	str[write] = '\0';
}
int main(){
	char inpstr[] = "aaabcccccccccc";
	compress(inpstr);
	printf("%s", inpstr);
	return 0;
}
