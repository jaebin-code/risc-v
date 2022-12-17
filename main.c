#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
void arraychange(char* arr,char a,char b, int i); // save hex in arr
void changeto2(char* arr,int* arr2);  // convert hex to binary in arr2
void jal(int arr1[],int* arr,int* pc); //if opcode is jal(111) go to jal function
void jalr(int arr1[],int* arr,int* pc); //if opcode is jalr(103) go to jalr function
void auipc(int arr1[],int* arr,int* pc); //if opcode is auipc(23) go to auipc function
void lui(int arr1[],int* arr,int* pc); //if opcode is lui(55) go to lui function
void riscb(int arr1[],int* arr,int* pc); //if opcode is b(99) go to riscb function
void riscl(int arr1[],int* arr,char arr3[][3],int* pc,int* signal); //if opcode is l(3) go to riscl function
void riscs(int arr1[],int* arr,char arr3[][3],int* pc,int* signal); //if opcode is s(35) go to riscs function
void risci(int arr1[],int* arr,int* pc); //if opcode is i(19) go to risci function
void riscr(int arr1[],int* arr,int* pc); // if opcode is r(51) go to riscr function
void distop(int arr1[],int* arr2,char arr3[][3],int* pc, int* signal); // calculate opcode and load the fit format


int main(int argc,char* argv[]){
    FILE *fp;
    FILE *fp1;
    int ch;
    int ch1;
    int signal=1;
    int numberofin;
    char textfile[256];
    char textfile2[256];
    if(argc==4){
        sprintf(textfile,"%s",argv[1]);
        sprintf(textfile2,"%s",argv[2]);
        numberofin=atoi(argv[3]);
        fp=fopen(textfile,"rb");
        fp1=fopen(textfile2,"rb");}
    else if(argc==3){
        sprintf(textfile,"%s",argv[1]);
        numberofin=atoi(argv[2]);
        fp=fopen(textfile,"rb");
    }
    int countnum=0;
    char list1[9]={'0','0','0','0','0','0','0','0','\0'};
    int list2[33];
    int list3[32]={0x0,};
    char instlist[0x10000][9];
    char memlist[0x10000][3];
    memset(instlist,'F',sizeof(instlist));
    int leng=6;
    int inst=0;
    int pc=0;
    while((ch)!=EOF){
        for(int i=0;i<4;i++){
            ch=fgetc(fp);
            if((ch)==EOF){break;}
            char word[3];
            sprintf(word,"%02X",ch);
            char a=word[0];
            char b=word[1];
            arraychange(list1,a,b,leng-2*i);
        }
        if((ch)==EOF){break;}
        for(int i=0;i<8;i++){
            instlist[pc/4][i]=list1[i];
        }
        instlist[pc/4][8]='\0';
        pc=pc+4;
        }
    pc=0;
    memset(memlist,'F',sizeof(memlist));
    int memcnt=0;
    if(argc==4){
        while((ch1)!=EOF){
                ch1=fgetc(fp1);
                if((ch1)==EOF){break;}
                char word1[3];
                sprintf(word1,"%02X",ch1);
                char a1=word1[0];
                char b1=word1[1];
                if((ch1)==EOF){break;}
                memlist[memcnt][0]=a1;
                memlist[memcnt][1]=b1;
                memlist[memcnt][2]='\0';
                memcnt=memcnt+1;
                }
        }
    int cntnum=0;
    while(cntnum<numberofin){
            for(int i=0;i<8;i++){
                list1[i]=instlist[pc/4][i];
            }
            if(pc>0x0000FFFC){printf("Memory address error\n");pc=pc+4;break;}
            if(signal==0){printf("Memory address error\n");pc=pc+4;break;}
            if(list1[0]=='F'&&list1[1]=='F'&&list1[2]=='F'&&list1[3]=='F'&&list1[4]=='F'&&list1[5]=='F'&&list1[6]=='F'&&list1[7]=='F'){printf("unknown instruction\n");pc=pc+4;break;}
            
        changeto2(list1,list2);
        distop(list3,list2,memlist,&pc,&signal);
        list3[0]=0;
	cntnum+=1;
    }
    for(int p=0;p<32;p++){
        printf("x%d: 0x%08x\n",p,list3[p]);
    }
    printf("PC: 0x%08x\n",pc);
    fclose(fp);
    if(argc==4){
        fclose(fp1);
        }
    return 0;
    }
   


void arraychange(char* arr,char a,char b, int i){
    arr[i]=a;
    arr[i+1]=b;
};

void changeto2(char* arr,int* arr2){
    for(int i=0;i<8;i++){
        if(arr[i]=='1'){
            arr2[i*4]=0;
            arr2[i*4+1]=0;
            arr2[i*4+2]=0;
            arr2[i*4+3]=1;
        }
        else if(arr[i]=='2'){
            arr2[i*4]=0;
            arr2[i*4+1]=0;
            arr2[i*4+2]=1;
            arr2[i*4+3]=0;
        }
        else if(arr[i]=='3'){
            arr2[i*4]=0;
            arr2[i*4+1]=0;
            arr2[i*4+2]=1;
            arr2[i*4+3]=1;
        }
        else if(arr[i]=='4'){
            arr2[i*4]=0;
            arr2[i*4+1]=1;
            arr2[i*4+2]=0;
            arr2[i*4+3]=0;
        }
        else if(arr[i]=='5'){
            arr2[i*4]=0;
            arr2[i*4+1]=1;
            arr2[i*4+2]=0;
            arr2[i*4+3]=1;
        }
        else if(arr[i]=='6'){
            arr2[i*4]=0;
            arr2[i*4+1]=1;
            arr2[i*4+2]=1;
            arr2[i*4+3]=0;
        }
        else if(arr[i]=='7'){
            arr2[i*4]=0;
            arr2[i*4+1]=1;
            arr2[i*4+2]=1;
            arr2[i*4+3]=1;
        }
        else if(arr[i]=='8'){
            arr2[i*4]=1;
            arr2[i*4+1]=0;
            arr2[i*4+2]=0;
            arr2[i*4+3]=0;
        }
        else if(arr[i]=='9'){
            arr2[i*4]=1;
            arr2[i*4+1]=0;
            arr2[i*4+2]=0;
            arr2[i*4+3]=1;
        }
        else if(arr[i]=='A'){
            arr2[i*4]=1;
            arr2[i*4+1]=0;
            arr2[i*4+2]=1;
            arr2[i*4+3]=0;
        }
        else if(arr[i]=='B'){
            arr2[i*4]=1;
            arr2[i*4+1]=0;
            arr2[i*4+2]=1;
            arr2[i*4+3]=1;
        }
        else if(arr[i]=='C'){
            arr2[i*4]=1;
            arr2[i*4+1]=1;
            arr2[i*4+2]=0;
            arr2[i*4+3]=0;
        }
        else if(arr[i]=='D'){
            arr2[i*4]=1;
            arr2[i*4+1]=1;
            arr2[i*4+2]=0;
            arr2[i*4+3]=1;
        }
        else if(arr[i]=='E'){
            arr2[i*4]=1;
            arr2[i*4+1]=1;
            arr2[i*4+2]=1;
            arr2[i*4+3]=0;
        }
        else if(arr[i]=='F'){
            arr2[i*4]=1;
            arr2[i*4+1]=1;
            arr2[i*4+2]=1;
            arr2[i*4+3]=1;
        }
        else if(arr[i]=='0'){
            arr2[i*4]=0;
            arr2[i*4+1]=0;
            arr2[i*4+2]=0;
            arr2[i*4+3]=0;
        }
    }}

void jal(int arr1[],int* arr,int* pc){
    int sumrd=0;
    for(int i=24;i>19;i--){
        int mulrd=arr[i];
        for(int j=0;j<24-i;j++){
            mulrd=mulrd*2;
        }
        sumrd=sumrd+mulrd;
    }
    int imm=0;
    for(int i=19;i>11;i--){
        int mulimm=arr[i];
        for(int j=0;j<31-i;j++){
            mulimm=mulimm*2;
        }
        imm=imm+mulimm;
    }
    int mulimm1=arr[11];
    for(int h=0;h<11;h++){
            mulimm1=mulimm1*2;
        }
    imm=imm+mulimm1;
    for(int i=10;i>0;i--){
        int mulimm=arr[i];
        for(int j=0;j<11-i;j++){
            mulimm=mulimm*2;
        }
        imm=imm+mulimm;
    }
    imm=imm-arr[0]*1048576;
    arr1[sumrd]=*pc+4;//printf("jal x%d, %d\n",sumrd,imm);
    *pc=*pc+imm;
}



void jalr(int arr1[],int* arr,int* pc){
    int sumop=0;
    for(int i=19;i>16;i--){
        int mulop=arr[i];
        for(int j=0;j<19-i;j++){
            mulop=mulop*2;
        }
        sumop=sumop+mulop;
    }
    int sumrd=0;
    for(int i=24;i>19;i--){
        int mulrd=arr[i];
        for(int j=0;j<24-i;j++){
            mulrd=mulrd*2;
        }
        sumrd=sumrd+mulrd;
    }
    int sumrs1=0;
    for(int i=16;i>11;i--){
        int mulrs1=arr[i];
        for(int j=0;j<16-i;j++){
            mulrs1=mulrs1*2;
        }
        sumrs1=sumrs1+mulrs1;
    }
    int imm=0;
    for(int i=11;i>0;i--){
        int mulimm=arr[i];
        for(int j=0;j<11-i;j++){
            mulimm=mulimm*2;
        }
        imm=imm+mulimm;
    }
    imm=imm-arr[0]*2048;
    /*if(sumop==0){printf("jalr x%d, %d(x%d)\n",sumrd,imm,sumrs1);}
    else{printf("unknown instruction\n");}*/
    arr1[sumrd]=*pc+4;
    *pc=imm+arr1[sumrs1];
}

void auipc(int arr1[],int* arr,int* pc){
    int sumrd=0;
    for(int i=24;i>19;i--){
        int mulrd=arr[i];
        for(int j=0;j<24-i;j++){
            mulrd=mulrd*2;
        }
        sumrd=sumrd+mulrd;
    }
    int imm=0;
    for(int i=19;i>0;i--){
        int mulimm=arr[i];
        for(int j=0;j<31-i;j++){
            mulimm=mulimm*2;
        }
        imm=imm+mulimm;
    }
    imm=imm-arr[0]*2147483648;
    //printf("auipc x%d, %d\n",sumrd,imm);
    arr1[sumrd]=imm+*pc;
    *pc+=4;
}


void lui(int arr1[],int* arr,int* pc){
    int sumrd=0;
    for(int i=24;i>19;i--){
        int mulrd=arr[i];
        for(int j=0;j<24-i;j++){
            mulrd=mulrd*2;
        }
        sumrd=sumrd+mulrd;
    }
    int imm=0;
    for(int i=19;i>0;i--){
        int mulimm=arr[i];
        for(int j=0;j<31-i;j++){
            mulimm=mulimm*2;
        }
        imm=imm+mulimm;
    }
    imm=imm-arr[0]*2147483648;
    arr1[sumrd]=imm;
    *pc+=4;
}


void riscb(int arr1[],int* arr,int* pc){
    int sumop=0;
    for(int i=19;i>16;i--){
        int mulop=arr[i];
        for(int j=0;j<19-i;j++){
            mulop=mulop*2;
        }
        sumop=sumop+mulop;
    }
    int sumrs1=0;
    for(int i=16;i>11;i--){
        int mulrs1=arr[i];
        for(int j=0;j<16-i;j++){
            mulrs1=mulrs1*2;
        }
        sumrs1=sumrs1+mulrs1;
    }
    int sumrs2=0;
    for(int i=11;i>6;i--){
        int mulrs2=arr[i];
        for(int j=0;j<11-i;j++){
            mulrs2=mulrs2*2;
        }
        sumrs2=sumrs2+mulrs2;
    }
    int imm=0;
    for(int i=23;i>19;i--){
        int mulrd=arr[i];
        for(int j=0;j<24-i;j++){
            mulrd=mulrd*2;
        }
        imm=imm+mulrd;
    }
    imm=imm+arr[24]*2048;

    for(int i=6;i>0;i--){
        int mulimm=arr[i];
        for(int j=0;j<11-i;j++){
            mulimm=mulimm*2;
        }
        imm=imm+mulimm;
    }
    imm=imm-arr[0]*4096;
    if(sumop==0){
        if(arr1[sumrs1]==arr1[sumrs2]){*pc+=imm;}
        else{
            *pc+=4;
        }
    }//{printf("beq x%d, x%d, %d\n",sumrs1,sumrs2,imm);}
    else if(sumop==1){
        if(arr1[sumrs1]!=arr1[sumrs2]){*pc+=imm;}
        else{
            *pc+=4;
        }
        }//{printf("bne x%d, x%d, %d\n",sumrs1,sumrs2,imm);}
    else if(sumop==4){
        if(arr1[sumrs1]<arr1[sumrs2]){
            *pc+=imm;
        }
        else{
            *pc+=4;
        }
    }//{printf("blt x%d, x%d, %d\n",sumrs1,sumrs2,imm);}
    else if(sumop==5){
        if(arr1[sumrs1]>=arr1[sumrs2]){
            *pc+=imm;
        }
        else{
            *pc+=4;
        }
    }//{printf("bge x%d, x%d, %d\n",sumrs1,sumrs2,imm);}
    else if(sumop==6){
        if((unsigned int)arr1[sumrs1]<(unsigned int)arr1[sumrs2]){
            *pc+=imm;
        }
        else{
            *pc+=4;
        }
    }//{printf("bltu x%d, x%d, %d\n",sumrs1,sumrs2,imm);}
    else if(sumop==7){
        if((unsigned int)arr1[sumrs1]>=(unsigned int)arr1[sumrs2]){
            *pc+=imm;
        }
        else{
            *pc+=4;
        }
    }//{printf("bgeu x%d, x%d, %d\n",sumrs1,sumrs2,imm);}
    else{printf("unknown instruction\n");}
}




void riscl(int arr1[],int* arr,char arr3[][3],int* pc,int* signal){
    int sumop=0;
    for(int i=19;i>16;i--){
        int mulop=arr[i];
        for(int j=0;j<19-i;j++){
            mulop=mulop*2;
        }
        sumop=sumop+mulop;
    }

    int sumrd=0;
    for(int i=24;i>19;i--){
        int mulrd=arr[i];
        for(int j=0;j<24-i;j++){
            mulrd=mulrd*2;
        }
        sumrd=sumrd+mulrd;
    }

    int sumrs1=0;
    for(int i=16;i>11;i--){
        int mulrs1=arr[i];
        for(int j=0;j<16-i;j++){
            mulrs1=mulrs1*2;
        }
        sumrs1=sumrs1+mulrs1;
    }
    int imm=0;
    for(int i=11;i>0;i--){
        int mulimm=arr[i];
        for(int j=0;j<11-i;j++){
            mulimm=mulimm*2;
        }
        imm=imm+mulimm;
    }
    imm=imm-arr[0]*2048;
    
    if(sumop==0){
        if(arr1[sumrs1]+imm>0x1000ffff){
            *signal=0;
        }
        else{
            char result[3];
            result[0]=arr3[arr1[sumrs1]+imm-0x10000000][0];
            result[1]=arr3[arr1[sumrs1]+imm-0x10000000][1];
            result[2]='\0';
            int word;
            word = strtoul(result, NULL, 16);
            word=word<<24;
            word=word>>24;
            arr1[sumrd]=word;
            *pc+=4;}
    }//{printf("lb x%d, %d(x%d)\n",sumrd,imm,sumrs1);}
    else if(sumop==1){
        if(arr1[sumrs1]+imm>0x1000fffe){
            *signal=0;
        }
        else{
            char result[5];
            result[0]=arr3[arr1[sumrs1]+imm-0x10000000+1][0];
            result[1]=arr3[arr1[sumrs1]+imm-0x10000000+1][1];
            result[2]=arr3[arr1[sumrs1]+imm-0x10000000][0];
            result[3]=arr3[arr1[sumrs1]+imm-0x10000000][1];
            result[4]='\0';
            int word;
            word = strtoul(result, NULL, 16);
            word=word<<16;
            word=word>>16;
            arr1[sumrd]=word;
            *pc+=4;}
    }//{printf("lh x%d, %d(x%d)\n",sumrd,imm,sumrs1);}
    else if(sumop==2){
        if(arr1[sumrs1]+imm>0x1000fffc){
            *signal=0;
        }
        else{
            char result[9];
            result[0]=arr3[arr1[sumrs1]+imm-0x10000000+3][0];
            result[1]=arr3[arr1[sumrs1]+imm-0x10000000+3][1];
            result[2]=arr3[arr1[sumrs1]+imm-0x10000000+2][0];
            result[3]=arr3[arr1[sumrs1]+imm-0x10000000+2][1];
            result[4]=arr3[arr1[sumrs1]+imm-0x10000000+1][0];
            result[5]=arr3[arr1[sumrs1]+imm-0x10000000+1][1];
            result[6]=arr3[arr1[sumrs1]+imm-0x10000000][0];
            result[7]=arr3[arr1[sumrs1]+imm-0x10000000][1];
            result[8]='\0';
            int word;
            word = strtoul(result, NULL, 16);
            arr1[sumrd]=word;
            *pc+=4;}
    }//{printf("lw x%d, %d(x%d)\n",sumrd,imm,sumrs1);}
    else if(sumop==4){
        if(arr1[sumrs1]+imm==0x20000000){
            int user;
            scanf("%d",&user);
            unsigned int user1=user;
            arr1[sumrd]=user1;
            *pc+=4;
        }
        else if(arr1[sumrs1]+imm>0x1000ffff){
            *signal=0;
        }
        else{
            char result[3];
            result[0]=arr3[arr1[sumrs1]+imm-0x10000000][0];
            result[1]=arr3[arr1[sumrs1]+imm-0x10000000][1];
            result[2]='\0';
            int word;
            word = strtoul(result, NULL, 16);
            arr1[sumrd]=word;
            *pc+=4;}
    }//{printf("lbu x%d, %d(x%d)\n",sumrd,imm,sumrs1);}
    else if(sumop==5){
        if(arr1[sumrs1]+imm>0x1000fffe){
            *signal=0;
        }
        else{
            char result[5];
            result[0]=arr3[arr1[sumrs1]+imm-0x10000000+1][0];
            result[1]=arr3[arr1[sumrs1]+imm-0x10000000+1][1];
            result[2]=arr3[arr1[sumrs1]+imm-0x10000000][0];
            result[3]=arr3[arr1[sumrs1]+imm-0x10000000][1];
            result[4]='\0';
            int word;
            word = strtoul(result, NULL, 16);
            arr1[sumrd]=word;
            *pc+=4;
        }
    }//{printf("lhu x%d, %d(x%d)\n",sumrd,imm,sumrs1);}
    else{printf("unknown instruction\n");}
};




void riscs(int arr1[],int* arr,char arr3[][3],int* pc,int* signal){
    int sumop=0;
    for(int i=19;i>16;i--){
        int mulop=arr[i];
        for(int j=0;j<19-i;j++){
            mulop=mulop*2;
        }
        sumop=sumop+mulop;
    }
    int sumrs1=0;
    for(int i=16;i>11;i--){
        int mulrs1=arr[i];
        for(int j=0;j<16-i;j++){
            mulrs1=mulrs1*2;
        }
        sumrs1=sumrs1+mulrs1;
    }

    int sumrs2=0;
    for(int i=11;i>6;i--){
        int mulrs2=arr[i];
        for(int j=0;j<11-i;j++){
            mulrs2=mulrs2*2;
        }
        sumrs2=sumrs2+mulrs2;
    }
    int imm=0;
    for(int i=24;i>19;i--){
        int mulrd=arr[i];
        for(int j=0;j<24-i;j++){
            mulrd=mulrd*2;
        }
        imm=imm+mulrd;
    }

    for(int i=6;i>0;i--){
        int mulimm=arr[i];
        for(int j=0;j<11-i;j++){
            mulimm=mulimm*2;
        }
        imm=imm+mulimm;
    }
    imm=imm-arr[0]*2048;
    if(sumop==0){
        if(arr1[sumrs1]+imm==0x20000000){
            printf("%c",arr1[sumrs2]);
            *pc+=4;
        }
        else if(arr1[sumrs1]+imm>0x1000ffff){
            *signal=0;
        }
        else{
            int result=arr1[sumrs2];
            char word[9];
            sprintf(word,"%08X",result);
            arr3[imm+arr1[sumrs1]-0x10000000][0]=word[6];
            arr3[imm+arr1[sumrs1]-0x10000000][1]=word[7];
            *pc+=4;}
    }//{printf("sb x%d, %d(x%d)\n",sumrs2,imm,sumrs1);}
    else if(sumop==1){
        if(arr1[sumrs1]+imm>0x1000fffe){
            *signal=0;
        }
        else{
            int result=arr1[sumrs2];
            char word[9];
            sprintf(word,"%08X",result);
            arr3[imm+arr1[sumrs1]-0x10000000][0]=word[6];
            arr3[imm+arr1[sumrs1]-0x10000000][1]=word[7];
            arr3[imm+arr1[sumrs1]-0x10000000+1][0]=word[4];
            arr3[imm+arr1[sumrs1]-0x10000000+1][1]=word[5];
            *pc+=4;
        }
    }//{printf("sh x%d, %d(x%d)\n",sumrs2,imm,sumrs1);}
    else if(sumop==2){
        if(arr1[sumrs1]+imm>0x1000fffc){
            *signal=0;
        }
        else{
            int result=arr1[sumrs2];
            char word[9];
            sprintf(word,"%08X",result);
            arr3[imm+arr1[sumrs1]-0x10000000][0]=word[6];
            arr3[imm+arr1[sumrs1]-0x10000000][1]=word[7];
            arr3[imm+arr1[sumrs1]-0x10000000+1][0]=word[4];
            arr3[imm+arr1[sumrs1]-0x10000000+1][1]=word[5];
            arr3[imm+arr1[sumrs1]-0x10000000+2][0]=word[2];
            arr3[imm+arr1[sumrs1]-0x10000000+2][1]=word[3];
            arr3[imm+arr1[sumrs1]-0x10000000+3][0]=word[0];
            arr3[imm+arr1[sumrs1]-0x10000000+3][1]=word[1];
            *pc+=4;}
    }//{printf("sw x%d, %d(x%d)\n",sumrs2,imm,sumrs1);}
    else{printf("unknown instruction\n");}
};


void risci(int arr1[],int* arr,int* pc){
    int sumop=0;
    for(int i=19;i>16;i--){
        int mulop=arr[i];
        for(int j=0;j<19-i;j++){
            mulop=mulop*2;
        }
        sumop=sumop+mulop;
    }

    int sumrd=0;
    for(int i=24;i>19;i--){
        int mulrd=arr[i];
        for(int j=0;j<24-i;j++){
            mulrd=mulrd*2;
        }
        sumrd=sumrd+mulrd;
    }

    int sumrs1=0;
    for(int i=16;i>11;i--){
        int mulrs1=arr[i];
        for(int j=0;j<16-i;j++){
            mulrs1=mulrs1*2;
        }
        sumrs1=sumrs1+mulrs1;
    }

    int sumsha=0;
    for(int i=11;i>6;i--){
        int mulsha=arr[i];
        for(int j=0;j<11-i;j++){
            mulsha=mulsha*2;
        }
        sumsha=sumsha+mulsha;
    }
    unsigned int sha;
    sha=sumsha;
    sha=sha<<27;
    sha=sha>>27;
    sumsha=sha;
    int imm=0;
    for(int i=11;i>0;i--){
        int mulimm=arr[i];
        for(int j=0;j<11-i;j++){
            mulimm=mulimm*2;
        }
        imm=imm+mulimm;
    }
    imm=imm-arr[0]*2048;
    if(sumop==0){//printf("addi x%d, x%d, %d\n",sumrd,sumrs1,imm); 
    arr1[sumrd]=arr1[sumrs1]+imm;}
    else if(sumop==1&&arr[1]==0){//printf("slli x%d, x%d, %d\n",sumrd,sumrs1,sumsha);
    arr1[sumrd]=arr1[sumrs1]<<sumsha;}
    else if(sumop==2){//printf("slti x%d, x%d, %d\n",sumrd,sumrs1,imm);
    if(arr1[sumrs1]<imm)arr1[sumrd]=1;
    else arr1[sumrd]=0;}
    else if(sumop==3){//printf("sltiu x%d, x%d, %d\n",sumrd,sumrs1,imm);
    if((unsigned int)arr1[sumrs1]<imm)arr1[sumrd]=1;
    else arr1[sumrd]=0;}
    else if(sumop==4){//printf("xori x%d, x%d, %d\n",sumrd,sumrs1,imm);
    arr1[sumrd]=arr1[sumrs1]^imm;}
    else if(sumop==5&&arr[1]==0){//printf("srli x%d, x%d, %d\n",sumrd,sumrs1,sumsha);
    unsigned int res=arr1[sumrs1];
    int res1=res>>sumsha;
    arr1[sumrd]=res1;}
    else if(sumop==5&&arr[1]==1){//printf("srai x%d, x%d, %d\n",sumrd,sumrs1,sumsha);
    arr1[sumrd]=arr1[sumrs1]>>sumsha;}
    else if(sumop==6){//printf("ori x%d, x%d, %d\n",sumrd,sumrs1,imm);
    arr1[sumrd]=arr1[sumrs1]|imm;}
    else if(sumop==7){//printf("andi x%d, x%d, %d\n",sumrd,sumrs1,imm);
    arr1[sumrd]=arr1[sumrs1]&imm;}
    else{printf("unknown instruction\n");}
    *pc+=4;
};


void riscr(int arr1[],int* arr,int* pc){
    int sumop=0;
    for(int i=19;i>16;i--){
        int mulop=arr[i];
        for(int j=0;j<19-i;j++){
            mulop=mulop*2;
        }
        sumop=sumop+mulop;
    }

    int sumrd=0;
    for(int i=24;i>19;i--){
        int mulrd=arr[i];
        for(int j=0;j<24-i;j++){
            mulrd=mulrd*2;
        }
        sumrd=sumrd+mulrd;
    }

    int sumrs1=0;
    for(int i=16;i>11;i--){
        int mulrs1=arr[i];
        for(int j=0;j<16-i;j++){
            mulrs1=mulrs1*2;
        }
        sumrs1=sumrs1+mulrs1;
    }

    int sumrs2=0;
    for(int i=11;i>6;i--){
        int mulrs2=arr[i];
        for(int j=0;j<11-i;j++){
            mulrs2=mulrs2*2;
        }
        sumrs2=sumrs2+mulrs2;
    }
    int sha=arr1[sumrs2];
    unsigned int sha1;
    sha1=sha;
    sha1=sha1<<27;
    sha1=sha1>>27;
    sha=sha1;
    if((sumop==0)&&arr[1]==0){//printf("add x%d, x%d, x%d\n",sumrd,sumrs1,sumrs2);
    arr1[sumrd]=arr1[sumrs1]+arr1[sumrs2];}
    else if((sumop==0)&&arr[1]==1){//printf("sub x%d, x%d, x%d\n",sumrd,sumrs1,sumrs2);
    arr1[sumrd]=arr1[sumrs1]-arr1[sumrs2];}
    else if((sumop==1)&&arr[1]==0){//printf("sll x%d, x%d, x%d\n",sumrd,sumrs1,sumrs2);
    arr1[sumrd]=arr1[sumrs1]<<sha;}
    else if((sumop==2)&&arr[1]==0){//printf("slt x%d, x%d, x%d\n",sumrd,sumrs1,sumrs2);
    if(arr1[sumrs1]<arr1[sumrs2])arr1[sumrd]=1;
    else arr1[sumrd]=0;}
    else if((sumop==3)&&arr[1]==0){//printf("sltu x%d, x%d, x%d\n",sumrd,sumrs1,sumrs2);
    if((unsigned int)arr1[sumrs1]<(unsigned int)arr1[sumrs2]) arr1[sumrd]=1;
    else arr[sumrd]=0;}
    else if((sumop==4)&&arr[1]==0){//printf("xor x%d, x%d, x%d\n",sumrd,sumrs1,sumrs2);
    arr1[sumrd]=arr1[sumrs1]^arr1[sumrs2];}
    else if((sumop==5)&&arr[1]==0){//printf("srl x%d, x%d, x%d\n",sumrd,sumrs1,sumrs2);
    unsigned int res=arr1[sumrs1];
    int res1=res>>sha;
    arr1[sumrd]=res1;}
    else if((sumop==5)&&arr[1]==1){//printf("sra x%d, x%d, x%d\n",sumrd,sumrs1,sumrs2);
    arr1[sumrd]=arr1[sumrs1]>>sha;}
    else if((sumop==6)&&arr[1]==0){//printf("or x%d, x%d, x%d\n",sumrd,sumrs1,sumrs2);
    arr1[sumrd]=arr1[sumrs1]|arr1[sumrs2];}
    else if((sumop==7)&&arr[1]==0){//printf("and x%d, x%d, x%d\n",sumrd,sumrs1,sumrs2);
    arr1[sumrd]=arr1[sumrs1]&arr1[sumrs2];}
    else{printf("unknown instruction\n");}
    *pc+=4;
};

void distop(int arr1[],int* arr2,char arr3[][3],int* pc,int* signal){
    int sumop=0;
    for(int i=31;i>24;i--){
        int mulop=arr2[i];
        for(int j=0;j<31-i;j++){
            mulop=mulop*2;
        }
        sumop=sumop+mulop;
    }
    if(sumop==51){riscr(arr1,arr2,pc);}
    else if(sumop==19){risci(arr1,arr2,pc);}
    else if(sumop==35){riscs(arr1,arr2,arr3,pc,signal);}
    else if(sumop==3){riscl(arr1,arr2,arr3,pc,signal);}
    else if(sumop==99){riscb(arr1,arr2,pc);}
    else if(sumop==23){auipc(arr1,arr2,pc);}
    else if(sumop==55){lui(arr1,arr2,pc);}
    else if(sumop==103){jalr(arr1,arr2,pc);}
    else if(sumop==111){jal(arr1,arr2,pc);}
    else{printf("unknown instruction\n");}
}
