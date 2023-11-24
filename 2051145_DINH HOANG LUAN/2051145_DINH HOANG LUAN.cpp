#include <stdio.h>

/* Confirm the picture have already converted into bmp or not */
unsigned char getByte(FILE *fp, int location){
	unsigned char byte;
	fseek(fp,location,SEEK_SET);
	fread(&byte,1,1,fp);
	return byte;
}

/* Move to address 0x12 to take the bitmap width in pixels (signed integer) */
int getwidth(FILE *fp){
	int width;
	fseek(fp,0x12,SEEK_SET);
	fread(&width,1,4,fp);
	return width;
}

/* Move to address 0x16 to take the bitmap height in pixels (signed integer) */
int getheight(FILE *fp){
	int height;
	fseek(fp,0x16,SEEK_SET);
	fread(&height,1,4,fp);
	return height;
}

/* Move to address 0xA to take the offset, starting address of the byte where the bitmap image data (pixel array) can be found. */
int getOffsetToPixelArray(FILE *fp){
	int OffsetToPixelArray;
	fseek(fp,0xA,SEEK_SET);
	fread(&OffsetToPixelArray,1,4,fp);
	return OffsetToPixelArray;
}

/* Move to address 0x1C to take the number of bits per pixel, which is the color depth of the image. Typical values are 1, 4, 8, 16, 24 and 32 */
int getBitPerPixel(FILE *fp){
	int BitPerPixel;
	fseek(fp,0x1C,SEEK_SET);
	fread(&BitPerPixel,1,1,fp);
	return BitPerPixel;
}

/* Print "0" if getByte smaller or equal 127, and print "1" if getByte larger  127 */
void printImage(FILE *fp, int height, int width, int OffsetToPixelArray, int BitPerPixel){
	int RowSize= int(((BitPerPixel*width)+31)/32)*4;
	for(int i= height -1; i>=0; i--){
		for(int j=0; j< width; j++ ){
			if((getByte(fp, OffsetToPixelArray + i*RowSize + j)) <= 127)
				printf("0");
			else
				printf("1");
		}
		printf("\n");
	}
	
}

int main(){
	int a;
	
        printf("###########################################################################\n");
        printf("####                          HELLO PROFESSOR                          ####\n");
        printf("####                                                                   ####\n");
        printf("####                    My name is DINH HOANG LUAN                     ####\n");
        printf("####                                                                   ####\n");
        printf("####                            From TT03                              ####\n");               
        printf("####                                                                   ####\n");
        printf("####                Today, I will present you topic 5                  ####\n");
        printf("####                                                                   ####\n");
        printf("####                                                                   ####\n");
        printf("###########################################################################\n");
   
	
	/* Declare fp */
	FILE *fp=fopen("new.bmp","r");
	
	/* Declare height, width, offset */
	int height = getheight(fp);
	int width = getwidth(fp);
	int OffsetToPixelArray = getOffsetToPixelArray(fp);
	
	int b;
	printf("\n###########################################################################\n");
	printf("#####      Press buttom 0 to check the picture is the bitmap or not    ####\n");
	printf("###########################################################################\n"); 
	printf("           Please select buttom 0: ");
	scanf("%d",&b);
	
	if( b == 0){
	/* If the picture is bitmap type then print out */
		if((getByte(fp,0) != 'B')  || (getByte(fp,1) != 'M'))
			printf("           It is not a bmp!!. Please take another the picture.  ");
		else
			printf("           This is a bitmap picture: %c%c\n", getByte(fp,0), getByte(fp,1));
	}	
	
	int c;
	printf("\n###########################################################################\n");
	printf("#####      Press buttom 1 to see the feature of the picture            ####\n");
	printf("###########################################################################\n"); 
	printf("           Please select buttom 1: ");
	scanf("%d",&c);
	if(c == 1){
	/* Print the width of picture */
	printf("           The width is %d", getwidth(fp));
	
	/* Print the height of picture */
	printf("\n           The height is %d", getheight(fp));
	
	/* Print the offset of picture */
	printf("\n           The byte offset is %d\n", getOffsetToPixelArray(fp));
	}
	
	int d;
	printf("\n###########################################################################\n");	
	printf("#####      Press buttom 2 to check the Bit per Pixel                   ####\n");
	printf("###########################################################################\n"); 
	printf("           Please select buttom 2: ");
	scanf("%d",&d);
	if(d == 2){
	/* If bit per pixel euqal 8 then it legal */
	if(getBitPerPixel(fp) != 8)
		printf("           Invalid picture. Stop");
	else
		printf("           Bit per Pixel is %d\n",getBitPerPixel(fp));
		
	}
	
	int e;
	printf("\n###########################################################################\n");
	printf("#####      Press buttom 3 to print the picture                         ####\n");
	printf("###########################################################################\n");
	printf("           Please select buttom 3: ");
	scanf("%d", &e);
	if (e == 3){
		int BitPerPixel = getBitPerPixel(fp);
		printImage(fp, height, width, OffsetToPixelArray, BitPerPixel);
		}
	return 0;
	
}
