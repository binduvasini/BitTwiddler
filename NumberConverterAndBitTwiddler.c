#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VALUE_MAX_STR_LEN 64

struct value_st {
	char arg[VALUE_MAX_STR_LEN];
    	unsigned int normalized;
    	int signedDecimal;
    	int bitWidth;
	int indexPosition[2];
    	int indexCounter;
	char range[VALUE_MAX_STR_LEN];
    	char bin_str_literal[VALUE_MAX_STR_LEN];
    	char bin_str_human[VALUE_MAX_STR_LEN];
    	char binary[VALUE_MAX_STR_LEN];
    	char binaryForTwosComp[VALUE_MAX_STR_LEN];
    	char binaryWithSpace[VALUE_MAX_STR_LEN];
    	int binaryInt[VALUE_MAX_STR_LEN];
    	char hexadecimal[VALUE_MAX_STR_LEN];
};


int dec_str_to_unsigned(struct value_st *v_st_p)
{
	int i, len, d;
   	unsigned int x = 0;
    	int factor = 10;
    	len = strlen(v_st_p->arg);
    
    	for (i = 0; i < len; i++) { //v_st_p->arg = '713'
			x = x * factor; //first time: 0 , second : 70, third: 710
        	d = v_st_p->arg[i] - '0'; //for 7, the ascii value is 55. subtracting it with 48 to get the value 7.
       	 	x = x + d;  //first time: 7, second: 71, third: 713
    	}
    	v_st_p->normalized = x;
	if(strcmp(v_st_p->arg,"0")!=0 && x==0) return 1;
	else return 0;
}

int str_to_numb(char *str){
	int i;
	int len;
	int d;
	unsigned int x=0;
	int factor=10;
	len=strlen(str);
	for(i=0;i<len;i++){
		x=x*factor;
		d=str[i]-'0';
		x=x+d;
	}
	return x;
}

int decimal_to_binary(struct value_st *v_st_p){
	int rem;
	char remChar;
	int i;
 	int index;
 	unsigned int res;
 	index=v_st_p->bitWidth-1;
 	res=v_st_p->normalized;
 	for(i=0;i<v_st_p->bitWidth;i++){
  		rem=res%2;
  		res=res/2;
  		remChar=(rem==1)?'1':'0';
  		v_st_p->binary[index]=remChar;
  		index=index-1; 
 	}
	v_st_p->binary[v_st_p->bitWidth]='\0';
 	return 0;
}


int decimal_to_hex(struct value_st *v_st_p){
	int val=v_st_p->normalized;
	int i, res, rem, index, bitSize=(v_st_p->bitWidth/4);
	char remChar;
	index=bitSize-1;
	for(i=0;i<bitSize;i++){
 		rem=val%16;
 		val=val/16;
 		switch(rem){
			case 1: remChar='1'; break;
			case 0: remChar='0'; break;
			case 2: remChar='2'; break;
			case 3: remChar='3'; break;
			case 4: remChar='4'; break;
			case 5: remChar='5'; break;
			case 6: remChar='6'; break;
			case 7: remChar='7'; break;
			case 8: remChar='8'; break;
			case 9: remChar='9'; break;
			case 10: remChar='A'; break;
			case 11: remChar='B'; break;
			case 12: remChar='C'; break;
			case 13: remChar='D'; break;
			case 14: remChar='E'; break;
			case 15: remChar='F'; break;
			default: break;
		}
		v_st_p->hexadecimal[index]=remChar;
		index=index-1;
	}
	v_st_p->hexadecimal[bitSize]='\0';
	return 0;
}

int hex_to_binary(struct value_st *v_st_p){
	int len,i,j,length;
	char binary[VALUE_MAX_STR_LEN],input[VALUE_MAX_STR_LEN],binaryChar[VALUE_MAX_STR_LEN]="";
	len=strlen(v_st_p->hexadecimal);

	for(i=0;i<len;i++)
    	{
        switch(v_st_p->hexadecimal[i]){
            case '0':
		strcat(binaryChar, "0000");
                break;
            case '1':
                strcat(binaryChar, "0001");
                break;
            case '2':
                strcat(binaryChar, "0010");
                break;
            case '3':
                strcat(binaryChar, "0011");
                break;
            case '4':
                strcat(binaryChar, "0100");
                break;
            case '5':
                strcat(binaryChar, "0101");
                break;
            case '6':
                strcat(binaryChar, "0110");
                break;
            case '7':
                strcat(binaryChar, "0111");
                break;
            case '8':
                strcat(binaryChar, "1000");
                break;
            case '9':
                strcat(binaryChar, "1001");
                break;
            case 'a':
            case 'A':
                strcat(binaryChar, "1010");
                break;
            case 'b':
            case 'B':
                strcat(binaryChar, "1011");
                break;
            case 'c':
            case 'C':
                strcat(binaryChar, "1100");
                break;
            case 'd':
            case 'D':
                strcat(binaryChar, "1101");
                break;
            case 'e':
            case 'E':
                strcat(binaryChar, "1110");
                break;
            case 'f':
            case 'F':
                strcat(binaryChar, "1111");
                break;
            default:
                break;
        
	}

    }

    strcpy(binary,binaryChar);

    if(v_st_p->indexCounter>1){
    	int k, index=v_st_p->bitWidth-1;
	int lengthOfSub;
    	length=32-strlen(binary);
    	memmove(binary+length,binary,strlen(binary));
    	for(j=0;j<length;j++){
        	binary[j]='0';
    	}
    	binary[32]='\0';
    	lengthOfSub=strlen(binary);
    	for(k=lengthOfSub-v_st_p->indexPosition[0]-1;k>=lengthOfSub-v_st_p->indexPosition[1]-1;k--){
		input[index]=binary[k];
		index=index-1;
    	}
    	input[v_st_p->bitWidth]='\0';
    	strcpy(v_st_p->binary,input);
    }
    else{
	length=v_st_p->bitWidth-strlen(binary);
	memmove(binary+length,binary,strlen(binary));
	for(j=0;j<length;j++){
		binary[j]='0';
	}
	binary[v_st_p->bitWidth]='\0';
	strcpy(v_st_p->binary,binary);
    }
    return 0;
}

int binary_to_decimal(char *binaryVal){

	int i,val, base=1, dec=0;
	int len=strlen(binaryVal);
	
	for(i=len-1;i>=0;i--){
		val=(binaryVal[i]=='0')?0:1;
		dec=dec+(val*base);
		base=base*2;		
	}
	return dec;
}

int binary_to_hex(struct value_st *v_st_p){
	char binaryNormalized[VALUE_MAX_STR_LEN], *token;
	int i, len, dec, index=0,j=0,bitWidth=v_st_p->bitWidth;
	len=strlen(v_st_p->binary);

	for(i=0;i<len;i++){
		if(i%4==0 && i!=0){
			binaryNormalized[index]=' ';
			index=index+1;
			bitWidth=bitWidth+1;
		}
		binaryNormalized[index]=v_st_p->binary[i];
		index=index+1;
	}
	binaryNormalized[bitWidth]='\0';
	token=strtok(binaryNormalized," ");

	while(token!=NULL){
		dec=binary_to_decimal(token);
		token=strtok(NULL," ");
		char remChar;
		switch(dec){
			case 1: remChar='1'; break;
			case 0: remChar='0'; break;
			case 2: remChar='2'; break;
			case 3: remChar='3'; break;
			case 4: remChar='4'; break;
			case 5: remChar='5'; break;
			case 6: remChar='6'; break;
			case 7: remChar='7'; break;
			case 8: remChar='8'; break;
			case 9: remChar='9'; break;
			case 10: remChar='A'; break;
			case 11: remChar='B'; break;
			case 12: remChar='C'; break;
			case 13: remChar='D'; break;
			case 14: remChar='E'; break;
			case 15: remChar='F'; break;
			default: break;
		}
		v_st_p->hexadecimal[j]=remChar;
		j=j+1;
	}
	v_st_p->hexadecimal[(v_st_p->bitWidth/4)]='\0';
	return 0;
}

int binary_to_signed(struct value_st *v_st_p){
	if(v_st_p->binary[0]=='1'){
		char onesComp[VALUE_MAX_STR_LEN];
		char twosComp[VALUE_MAX_STR_LEN];
		int binaryLen=strlen(v_st_p->binary);
		int i,j,val,base=1,dec=0,twosCompLen;
		int carry;
		for(i=0;i<binaryLen;i++){
			onesComp[i]=(v_st_p->binary[i]=='0')?'1':'0';
		}
		onesComp[binaryLen]='\0';
		for(i=binaryLen-1;i>=0;i--){
			if(onesComp[i]=='1' && carry==1){
				twosComp[i]='0';
			}
			else if(onesComp[i]=='0' && carry==1){
				twosComp[i]='1';
				carry=0;
			}
			else{
				twosComp[i]=onesComp[i];
			}
		}
		twosComp[binaryLen]='\0';
		twosCompLen=strlen(twosComp);
		for(j=twosCompLen-1;j>=0;j--){
			val=(twosComp[j]=='0')?0:1;
			dec=dec+(val*base);
			base=base*2;
		}
		v_st_p->signedDecimal=dec;
	}
	else{
		v_st_p->signedDecimal=v_st_p->normalized;
	}
	return 0;
}

int binary_to_unsigned(struct value_st *v_st_p){
	unsigned int val;
	int i, base=1, dec=0;
	int len=strlen(v_st_p->binary);
	for(i=len-1;i>=0;i--){
		val=(v_st_p->binary[i]=='0')?0:1;
		dec=dec+(val*base);
		base=base*2;
	}
	v_st_p->normalized=dec;
	return 0;
}

int binary_twos_comp(struct value_st *v_st_p){
	char onesComp[VALUE_MAX_STR_LEN], twosComp[VALUE_MAX_STR_LEN];
	int binaryLen,i,j,val,base=1,dec=0,twosCompLen,carry=1,rem,k,index=v_st_p->bitWidth-1;
	char remChar,binary[VALUE_MAX_STR_LEN];
	unsigned int res=v_st_p->normalized;

	for(k=0;k<v_st_p->bitWidth;k++){
		rem=res%2;
	  	res=res/2;
	  	remChar=(rem==1)?'1':'0';
	  	binary[index]=remChar;	
	  	index=index-1; 
	}
	binary[v_st_p->bitWidth]='\0';
	binaryLen=strlen(binary);
	for(i=0;i<binaryLen;i++){
		onesComp[i]=(binary[i]=='0')?'1':'0';
	}
	onesComp[binaryLen]='\0';

	for(i=binaryLen-1;i>=0;i--){
		if(onesComp[i]=='1' && carry==1){
			twosComp[i]='0';
		}
		else if(onesComp[i]=='0' && carry==1){
			twosComp[i]='1';
			carry=0;
		}
		else{
			twosComp[i]=onesComp[i];
		}
	}
	twosComp[binaryLen]='\0';
	strcpy(v_st_p->binary,twosComp);
	return 0;
}

void validate_input(struct value_st *v_st_p){
	int len,i,sublength,lengthOfSub,j,k,c=0;
	if(strncmp("0b",v_st_p->arg,strlen("0b"))==0){
		char sub[VALUE_MAX_STR_LEN],input[VALUE_MAX_STR_LEN];
		len=strlen(v_st_p->arg);
		for(i=2;i<len;i++){
			if(v_st_p->arg[i]!='0'&&v_st_p->arg[i]!='1'){
				printf("\ninvalid binary input\n");
				exit(-1);
			}
		}
		
		while(c<len){
			sub[c]=v_st_p->arg[3+c-1];
			c=c+1;
		}

		if(v_st_p->indexCounter>1){
			int index=v_st_p->bitWidth-1;
			lengthOfSub=strlen(sub);
			for(k=lengthOfSub-v_st_p->indexPosition[0]-1;k>=lengthOfSub-v_st_p->indexPosition[1]-1;k--){
				input[index]=sub[k];
				index=index-1;
			}
			input[v_st_p->bitWidth]='\0';
			strcpy(v_st_p->binary,input);
		}
		else{
			sublength=v_st_p->bitWidth-strlen(sub);
			memmove(sub+sublength,sub,strlen(sub));
			for(j=0;j<sublength;j++){
				sub[j]='0';
			}
			sub[v_st_p->bitWidth]='\0';
			strcpy(v_st_p->binary,sub);
		}

		if(strlen(v_st_p->binary)>v_st_p->bitWidth){
			printf("\ntoo large binary input\n");
			exit(-1);
		}
		if(binary_to_unsigned(v_st_p)!=0){
			printf("binary to unsigned failed\n");
			exit(-1);
		}
		if(binary_to_signed(v_st_p)!=0){
			printf("binary to signed failed\n");
			exit(-1);
		}
		if(binary_to_hex(v_st_p)!=0){
			printf("binary to hex failed\n");
			exit(-1);
		}
	}
	else if(strncmp("0x",v_st_p->arg,strlen("0x"))==0){
		char sub[VALUE_MAX_STR_LEN],input[VALUE_MAX_STR_LEN];
		len=strlen(v_st_p->arg);
		int bitSize=(v_st_p->bitWidth/4);
		
		while(c<len){
			sub[c]=v_st_p->arg[3+c-1];
			c=c+1;
		}
		strcpy(v_st_p->hexadecimal,sub);

		if(v_st_p->hexadecimal[strspn(v_st_p->hexadecimal,"0123456789abcdefABCDEF")]!=0){
			printf("\ninvalid hexadecimal input\n");
			exit(-1);
		}
		
		if(hex_to_binary(v_st_p)!=0){
			printf("hex to binary failed\n");
			exit(-1);
		}

		if(binary_to_unsigned(v_st_p)!=0){
			printf("binary to unsigned failed\n");
			exit(-1);
		}
		if(binary_to_signed(v_st_p)!=0){
			printf("binary to signed failed\n");
			exit(-1);
		}
		if(strcmp(v_st_p->range,"-r")==0){
			if(binary_to_hex(v_st_p)!=0){
				printf("binary to hex failed\n");
				exit(-1);
			}
		}
	}
	else if(strncmp("-",v_st_p->arg,strlen("-"))==0){
		char sub[VALUE_MAX_STR_LEN];
		len=strlen(v_st_p->arg);
		while(c<len){
			sub[c]=v_st_p->arg[2+c-1];
			c=c+1;
		}
		strncpy(v_st_p->arg,sub,VALUE_MAX_STR_LEN-1);
		if (dec_str_to_unsigned(v_st_p) != 0) {
       	 		printf("dec_str_to_unsigned() failed\n");
        		exit(-1);
    		}
		
		if(binary_twos_comp(v_st_p)!=0){
			printf("binary twos complement failed\n");
			exit(-1);
		}
		if(binary_to_hex(v_st_p)!=0){
			printf("binary to hex failed\n");
			exit(-1);
		}
		if(binary_to_unsigned(v_st_p)!=0){
			printf("binary to unsigned failed\n");
			exit(-1);
		}
		if(binary_to_signed(v_st_p)!=0){
			printf("binary to signed failed\n");
			exit(-1);
		}
	}
	else{
		if (dec_str_to_unsigned(v_st_p) != 0) {
        		printf("invalid input\n");
        		exit(-1);
    		}

		if(decimal_to_binary(v_st_p)!=0){
			printf("decimal to binary failed\n");
			exit(-1);
		}
		if(decimal_to_hex(v_st_p)!=0){
			printf("binary to hex failed\n");
			exit(-1);
		}
		if(binary_to_unsigned(v_st_p)!=0){
			printf(" binary to unsigned failed\n");
			exit(-1);
		}
		if(binary_to_signed(v_st_p)!=0){
			printf("binary to signed failed\n");
			exit(-1);
		}
	}
}

void print_converted_values(struct value_st *v_st_p) {
	char binaryWithSpace[VALUE_MAX_STR_LEN];
	char binaryWithoutSpace[VALUE_MAX_STR_LEN]="0b";
	char hexadecimalRepresentation[VALUE_MAX_STR_LEN]="0x";
    	int i, len, index=0,bitWidth=v_st_p->bitWidth;
	len=strlen(v_st_p->binary);
	for(i=0;i<len;i++){
		if(i%4==0 && i!=0){
			binaryWithSpace[index]=' ';
			index=index+1;
			bitWidth=bitWidth+1;
		}
		binaryWithSpace[index]=v_st_p->binary[i];
		index=index+1;
	}
	binaryWithSpace[bitWidth]='\0';
	printf("%s (base 2)\n",binaryWithSpace);
	strcat(binaryWithoutSpace,v_st_p->binary);
	printf("%s (base 2)\n",binaryWithoutSpace);
	strcat(hexadecimalRepresentation,v_st_p->hexadecimal);
	printf("%s (base 16)\n",hexadecimalRepresentation);
	printf("%u (base 10 unsigned)\n",v_st_p->normalized);
	if(v_st_p->binary[0]=='1') printf("-%d (base 10 signed)\n",v_st_p->signedDecimal);
	else printf("%u (base 10 signed)\n",v_st_p->normalized);
	return;
}

int main(int argc, char *argv[])
{
	int i=0,j,index=0,c=0;
	char *token;
    	struct value_st v_st;
	v_st.indexCounter=0;
       
	if(argc>2){
		if(argc==4){
			if(strcmp(argv[1],"-b")==0){
				if(str_to_numb(argv[2])%4==0){
					strncpy(v_st.arg, argv[argc-1], VALUE_MAX_STR_LEN - 1);
					v_st.bitWidth=str_to_numb(argv[2]);
				}
				else{
					printf("bit width must be a multiple of 4");
					exit(-1);
				}
			}
			else{
				printf("invalid arguments");
				exit(-1);
			}
		}
		else if(argc==6){
			if(strcmp(argv[1],"-b")==0){
				if(str_to_numb(argv[2])%4==0){
					if(strcmp(argv[3],"-r")==0){
						token=strtok(argv[4],",");
						v_st.indexCounter=1;
						while(token!=NULL){
							v_st.indexPosition[i]=str_to_numb(token);
							i+=1;
							token=strtok(NULL,",");
							v_st.indexCounter+=1;
						}
						
						strncpy(v_st.arg, argv[argc-1], VALUE_MAX_STR_LEN - 1);
						v_st.bitWidth=str_to_numb(argv[2]);
						strcpy(v_st.range,argv[3]);
					}
					else{
						printf("\ninvalid arguments");
						exit(-1);
					}
				}
				else{
					printf("bit width must be a multiple of 4");
					exit(-1);
				}
			}
			else{
				printf("invalid arguments");
				exit(-1);
			}
		}
		else{
			printf("invalid input");
			exit(-1);
		}
	}
    	else if(argc==2){
		strncpy(v_st.arg, argv[argc-1], VALUE_MAX_STR_LEN - 1);
		v_st.bitWidth=32;
	}
	else{
		printf("no arguments passed");
		exit(-1);
	}
	validate_input(&v_st);
    	print_converted_values(&v_st);
    	return 0;
}
