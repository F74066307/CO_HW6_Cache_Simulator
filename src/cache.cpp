#include<iostream>
#include<cstdlib>
#include<fstream>
#include<ostream>
#include<string>
#include<cmath>
#include<queue>

using namespace std;

struct lrunode
{
	unsigned long int tag;
	lrunode* next=NULL;
	lrunode* back=NULL;

};

int stoi(string input){
	int ans=0;
		for(int i=0;i<input.size();i++){
			if(input.at(i)>='0'&&input.at(i)<='9'){
				ans=ans*10;
				ans=ans+input.at(i)-'0';
			}
			
		}
//		cout << ans << endl;
		//ans*=10;
	
//	cout << ans << endl;
	return ans;
}

string dectobit(unsigned long int in) {
	string ans = "";
	if (in==0) {
	//	return "0";
	}
	for(int i=0;i<31;i++){
//		cout << ans << endl;;
		if(in%2==1){
			ans="1"+ans;
		}
		else{
			ans="0"+ans;
		}
		//ans = to_string(in % 2)+ans;
		in = in / 2;
	}
	if(in==1){
		ans="1"+ans;
	}
	else if(in==0) {
		ans="0"+ans;
	}
//	cout <<ans <<  endl;
	//ans = to_string(in) + ans;
	return ans;
}

unsigned long int bittodec(string in) {
	unsigned long int ans = 0;
	int time = in.size()-1;
	if (in=="") {
		return 0;
	}
	for (int i = 0;i<in.size();i++) {
		if (in.at(i)=='1') {
			ans = ans + 1*(pow(2,time));
		}
		else {
			ans = ans + 0 * (pow(2,time));
		}
		time--;
	}
	return ans;
}

int main(int argc,char* argv[]) {
	ifstream in(argv[1]);
	ofstream out(argv[2]);
	int cachesize;
	int blocksize=1;
	int as;
	int algo;
	string input="";
	unsigned long address;
	unsigned long int tag;
	unsigned long int index;
	unsigned long int data;
	int hit = 0;
	int miss = 0;
	int to_change = 0;
	lrunode* head=new lrunode;
	head->next=NULL;
	lrunode* search = new lrunode;
	//lrunode** head4 = new lrunode*[4];
	int check = 0;
	int data_in = 0;

    //in.open();
	getline(in,input);
//  cout << input.size() << endl;
	cachesize = stoi(input) * 1024;
//	cout << cachesize/1024 << endl;
	getline(in, input);
//  cout << input << endl;
	blocksize = stoi(input);
//	cout << blocksize << endl;
	getline(in, input);
	as = stoi(input);
//	cout << as << endl;
	getline(in, input);
    algo = stoi(input);
//	cout << algo << endl;

	int blocknum = cachesize / blocksize;
	int blockoffset = log2(blocksize);
	int indexnum;
	int set;
//	int data = 1;
	if (as==0) {
		indexnum = log2(blocknum);
		set = 1;//[valid][tag][data]
	}
	else if (as==1) {
		blocknum /= 4;
		indexnum = log2(blocknum);
		set = 4;//[valid][tag][data]*4
	/*	lrunode** head4 = new lrunode*[blocknum];

		for(int i=0;i<blocknum;i++){
			head4[i]=new lrunode;
			head4[i]->next=NULL;
			head4[i]->back=NULL;
		}*/
	}
	else {
		set=blocknum;
		blocknum = 1;
		indexnum = 0;
		//set = blocknum ;//[valid][tag][data]*blocknum
	}
	int tagnum = 32 - indexnum - blockoffset;

	unsigned long int** cache = new unsigned long int*[blocknum];
	for (int i = 0;i<blocknum;i++) {
		cache[i] = new unsigned long int[set*3];
	}
	for (int i = 0;i<blocknum;i++) {
		for (int j = 0;j<set*3;j++) {
			cache[i][j] = 0;
		}
	}
int cc=0;
char inputchar[10];
lrunode** head4 = new lrunode*[blocknum];

 for(int i=0;i<blocknum;i++){
     head4[i]=new lrunode;
     head4[i]->next=NULL;
     head4[i]->back=NULL;
    }

	while (in >> inputchar) {
		cc++;
//		cout << cc << endl;

		check = 0;

		data_in = 0;

		for(int i=0;i<10;i++){
//			cout << inputchar[i];
		}
		//cout << endl;
		address = strtoul(inputchar,NULL,0);
//		cout << address << endl;
		string bitaddress = dectobit(address);
		string bittag="";
		bittag = bittag.append(bitaddress,0,tagnum);
		tag = bittodec(bittag);
//    cout << tag << " ";
		string bitindex = "";
		bitindex = bitindex.append(bitaddress,tagnum,indexnum);
		index = bittodec(bitindex);
  //  cout << index << " ";
		string bitdata = "";
		bitdata = bitdata.append(bitaddress,tagnum+indexnum,blockoffset);
		data = bittodec(bitdata);
//    cout << data << endl;
		lrunode* node = new lrunode;
		node->back = NULL;
		node->next = NULL;
		node->tag = tag;
		
		if (as==1) {
			if (head4[index]!=NULL) {
				search = head4[index]->next;

			}
			else {
				head4[index]->next = node;
				node->back = head4[index];
				cout <<  index << " " << tag << endl;
				while (search->next != NULL)
				{
					if (search->tag == tag) {
						search->next->back=search->    back;

						search->back->next=search->    next;

						search->next = head4[index]->next;
						head4[index]->next->back = search;
						head4[index]->next = search;
						search->back = head4[index];
						check = 1;
					}
					else
					{
						search = search->next;
					}
				}
				if (check != 1) {
					node->next = head4[index]->next;
					head4[index]->next->back = search;
					head4[index]->next = node;
					node->back = head4[index];
				}
			}
		}
		else if(as==2){

			if (head->next != NULL) {
				search = head->next;
				/*for(int i=0;i<set;i++){
					if (search->tag == tag) {
						search->back->next=search->next;
						search->next->back=search->back;
						search->next = head->next;
					    head->next->back = search;
					    head->next = search;
					    search->back = head;
					    check = 1;
					    search=search->next;
					    break;
					}
					else{
						search=search->next;
					}
				}*/
				while (search->next != NULL)
				{
					if (search->tag == tag) {
						search->back->next=search->    next;

						search->next->back=search->    back;

						search->next = head->next;
						head->next->back = search;
						head->next = search;
						search->back = head;
						check = 1;
						search=search->next;
						break;
					}
					else
					{
						search = search->next;
					}
					
				}
				if (check != 1) {
					//cout << "here" << endl;
					node->next = head->next;
					head->next->back = node;
					head->next = node;
					node->back = head;
				}
			}
			else {
				head->next = node;
				node->back = head;
			}
		}

		for (int j = 0;j<set*3;j=j+3) {
			if (cache[index][j]==0) {
				//valid bit=0
				cache[index][j+2] = data;
				cache[index][j+1] = tag;
				cache[index][j] = 1;
				miss++;
				out << -1 << endl;
				data_in = 1;
				break;
			}
			else if (cache[index][j] != 0&& cache[index][j+1] == tag) {
				//hit
				hit++;
				out << -1 << endl;
				//cache[index][j + 2] = data;
				data_in = 1;
				break;
			}
		}
		if (data_in!=1) {
			miss++;
			if (as==0) {
				out << cache[index][0 + 1] << endl;
				cache[index][0 + 2] = data;
				cache[index][0+1] = tag;
				
			}
			else if (as==1||as==2) {
				if (algo==0||algo==2) {
					out << cache[index][to_change+1] << endl;
					cache[index][to_change+1] = tag;
					cache[index][to_change + 2] = data;
					to_change += 3;
					if (to_change>=set*3) {
						to_change -= set * 3;
					}
				}
				else if (algo==1) {
					if (as==1) {
						search = head4[index]->next;
						for(int i=0;i<set;i++){
							if(search->next==NULL){
								break;
							}
							search=search->next;
						}
						for (int i = 0;i<set*3;i=1+3) {
							if (cache[index][i + 1] == search->tag) {
								out << cache[index][i+1] << endl;
								cache[index][i + 1] = tag;
								cache[index][i+2] = data;
								//out << tag << endl;
							}
						}
					}
					else if(as==2) {
						search = head->next;
						for(int i=0;i<set;i++){
							if(search->next==NULL){
								break;
							}
							else{
								search=search->next;
							}
						}
						
						for (int i = 0; i<set * 3; i=i+3) {
							if (cache[index][i + 1] == search->tag) {
								out << cache[index][i+1] << endl;
								cache[index][i + 1] = tag;
								cache[index][i + 2] = data;
//								out << tag << endl;
							}
						}
					}
				}
			}
		}
	}

//	in.close();
//	out.close();
	//float miss_rate = miss / (miss + hit);
}
