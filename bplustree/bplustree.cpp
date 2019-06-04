#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NOOFCHILDS 4
#define PAGESIZE 32

struct leafpage{
	char pagetype, unused[4];
	int sid[3];
	char name[3][5];
};
struct nonleafpage{
	char pagetype;
	char unused[3];
	int children[4];
	int value[3];
};
struct pageinfo{
	int pageid;
	char pagebuffer[PAGESIZE];
	int used;
	int lastused;
};
void insertleafpages(){
	FILE *inp = fopen("input.txt", "r");
	FILE *out = fopen("output.txt", "wb");
	char buf[PAGESIZE],name[5];
	int sid;
	struct leafpage *leaf = (struct leafpage *)buf;
	for (int i = 0; i < NOOFCHILDS; i++){
		int blocknumber = i;
		leaf->pagetype = 1;
		for (int j = 0; j < 3; j++){
			fscanf(inp, "%d,%s", &sid, name);
			leaf->sid[j]=sid;
			strcpy(leaf->name[j], name);
		}
		fwrite(leaf, PAGESIZE, 1, out);
	}
	fclose(inp);
	fclose(out);
}
int getminofleafpage(int pageno){
	FILE *out = fopen("output.txt", "rb+");
	fseek(out, pageno * PAGESIZE, SEEK_SET);
	char buf[PAGESIZE];
	struct leafpage *leaf = (struct leafpage*)buf;
	fread(leaf, PAGESIZE, 1, out);
	int min = leaf->sid[0];
	for (int i = 1; i < 3; i++){
		if (leaf->sid[i] < min){
			min = leaf->sid[i];
		}
	}
	fclose(out);
	return min;
}
void insertnonleafpage(){
	FILE *out = fopen("output.txt", "rb+");
	char buf[PAGESIZE];
	struct nonleafpage *leaf = (struct nonleafpage *)buf;
	leaf->pagetype = 2;
	leaf->children[0] = 0;
	for (int i = 1; i < 4; i++){
		leaf->children[i] = i;
		leaf->value[i - 1] = getminofleafpage(i);
	}
	fwrite(leaf, PAGESIZE, 1, out);
	fclose(out);
}
int loadpage(int pageid,struct pageinfo *pages,int *timestamp){
	int i,minpage = 0;
	/*for (i = 0; i < 3; i++){
		if (pages[i].used == 1 && pages[i].pageid == pageid){
			return i;
		}
	}
	int min = pages[0].lastused,minpage=0;
	for (i = 1; i < 3; i++){
		if (pages[i].lastused < min){
			min = pages[i].lastused;
			minpage = i;
		}
	}*/
	for (i = 0; i < 3; i++){
		if (pages[i].used == 1 && pages[i].pageid == pageid){
			return i;
		}
	}
	for (i = 0; i < 3; i++){
		if (pages[i].used == 0){
			minpage = i;
			break;
		}
	}
	if (i == 3){
		int min = pages[0].lastused;
		for (i = 1; i < 3; i++){
			if (pages[i].lastused < min){
				min = pages[i].lastused;
				minpage = i;
			}
		}
	}
	FILE *out = fopen("output.txt", "rb+");
	fseek(out, PAGESIZE * pageid, SEEK_SET);
	fread(pages[minpage].pagebuffer, PAGESIZE, 1, out);
	pages[minpage].pageid = pageid;
	pages[minpage].used = 1;
	pages[minpage].lastused = *timestamp;
	*timestamp += 1;
	fclose(out);
	return i;
}
void searchstudent(int sid, struct pageinfo *pages, int *timestamp ){
	FILE *out = fopen("output.txt", "rb"); int found = 0,i;
	int nonleafpageno = loadpage(4,pages,timestamp);
	struct nonleafpage * nonleaf=(struct nonleafpage *)malloc(sizeof(struct nonleafpage));
	memcpy( (void *)nonleaf, pages[nonleafpageno].pagebuffer,32);
	struct leafpage *reqleaf = (struct leafpage *)malloc(sizeof(struct leafpage));
	int leafpageid;
	for ( i = 0; i < 3; i++){
		if (sid < nonleaf->value[i]){
			leafpageid = i;
			break;
		}
	}
	if (i == 3){
		leafpageid = 3;
	}
	int leafbufferpageid = loadpage(leafpageid, pages,timestamp);
	memcpy( (void *)reqleaf, pages[leafbufferpageid].pagebuffer, 32);
	for (int i = 0; i < 3; i++){
		if (reqleaf->sid[i] == sid){
			printf("name:%s\n", reqleaf->name);
			break;
		}
	}
	fclose(out);
}
int main(){
	struct pageinfo pages[3];
	for (int i = 0; i < 3; i++) pages[i].used = 0;
	insertleafpages();
	insertnonleafpage();
	int sid,timestamp = 1;
	while (1){
		printf("search with sid:");
		scanf("%d", &sid);
		searchstudent(sid,pages,&timestamp);
	}
	////page 0
	//leafs->pagetype = 1;
	//leafs->sid[0] = 10;
	//leafs->sid[1] = 20;
	//leafs->sid[2] = 30;
	//strcpy(leafs->name[0], "aman");
	//strcpy(leafs->name[1], "anu");
	//strcpy(leafs->name[2], "bala");
	//fwrite(buf, PAGESIZE, 1, fptr);
	////page 1
	//leafs->pagetype = 1;
	//leafs->sid[0] = 40;
	//leafs->sid[1] = 50;
	//leafs->sid[2] = 60;
	//strcpy(leafs->name[0], "bapu");
	//strcpy(leafs->name[1], "don");
	//strcpy(leafs->name[2], "eega");
	//fwrite(buf, PAGESIZE, 1, fptr);
	////page 2
	//leafs->pagetype = 1;
	//leafs->sid[0] = 70;
	//leafs->sid[1] = 80;
	//leafs->sid[2] = 90;
	//strcpy(leafs->name[0], "fana");
	//strcpy(leafs->name[1], "guna");
	//strcpy(leafs->name[2], "hema");
	//fwrite(buf, PAGESIZE, 1, fptr);
	////page 3
	//leafs->pagetype = 1;
	//leafs->sid[0] = 100;
	//leafs->sid[1] = 110;
	//leafs->sid[2] = 120;
	//strcpy(leafs->name[0], "isac");
	//strcpy(leafs->name[1], "jai");
	//strcpy(leafs->name[2], "sana");
	//fwrite(buf, PAGESIZE, 1, fptr);
	//fclose(fptr);

	///////////reading file

	////page 0
	//fptr = fopen("bplustree", "rb");
	//fread(leafs, PAGESIZE, 1, fptr);
	//printf("%d %s\n", leafs->sid[0], leafs->name[0]);
	//printf("%d %s\n", leafs->sid[1], leafs->name[1]);
	//printf("%d %s\n", leafs->sid[2], leafs->name[2]);
	////page 1
	//

	return 0;
}
