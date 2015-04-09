//#include <files.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//#include <image.h>

int sFunc (finalB1L1, finalB1L2, finalW1L1, finalW1L2, finaSoftmaxTheta)
{
  int level = 0.65; // thresholding constant
  int width, height = 0;
  int locx = -1;
  int locy;
  int x, y = 0;
  int flag = 0;
  int i, j, l = 1;
  int z1, z2, z3, z4, total = 0;
  int digits = round(width/height);

  float Image[640][480];
  float oImage[640][480];
  float oImage1[640][480];
  float oImage2[640][480];
  float image[640][480];
  float image1[640][480];

  ////////////////////////////
  // ALL DONE IN VERILOG?!?!//
  ////////////////////////////

  // Img_in(??); //LOAD IMAGE????
  //Img_out(??) if we need/want to ourput the image
  //oImage = tograyscale (Image); // convert to gray scale ?
  //Threshold (oImage, oImage1, level); // convert to binary ?
  // oImage = ~oImage1;

    while (locx = -1)
      {
	i = i++;
	for (j=1; j<=3180; j++)
	  {
	    if(image[i][j]=0)
	      width++;
	    if (width > 200 && flag <1)
	      {
		i = i+3;
		flag = 1;
	      }
	    else
	      {
		if(width>200)
		  {
		    locx = j-width;
		    locy = i;
		    break;
		  }
		else
		  {
		    width = 0;
		  }
	      }
	  }
   
      }
      
      while (oImage[locy + height, locx]== 0)
      		height = height + 1;
      for (y = locy; y <= locy+height; y++)
	{
	  for (x = locx; x= locx+width; x++)
	    {
	      oImage2[y][x] = image[y][x];
	    }
	}

    for (l = 1; l<=digits; l++)
    {
      total = total *10;

//WEIGHT STUFF: DO IN VERILOG?
    /*z1 = 1/(1+exp(-(finalW1L1*image1+finalB1L1))); 
      z2 = 1/(1+exp(-(finalW1L2*z1+finalB1L2)));
      z3 = finalSoftmaxTheta *z2;
      z4 = mod(find(z3 == max(z3)), 10);

      total = total + z4;*/
    }
} 

void bilinear_interpolate(the_image, x, y, rows, cols) // SCALE INFO 
double x, y;
long cols, rows;
short **the_image;
{
double fraction_x, fraction_y,
one_minus_x, one_minus_y,
tmp_double;
int
ceil_x, ceil_y, floor_x, floor_y;
short p1, p2, p3, result;

if(x < 0.0||x >= (double)(cols-1)||y < 0.0||y >= (double)(rows-1))
return(result);
 tmp_double =  floor(x);
 floor_x = tmp_double;
 tmp_double = floor(y);
 floor_y = tmp_double;
  tmp_double = ceil(y);
  ceil_x = tmp_double;
  tmp_double = ceil(y);
  ceil_y = tmp_double;

fraction_x = x - floor(x);
fraction_y = y - floor(y);
one_minus_x = 1.0 - fraction_x;
one_minus_y = 1.0 - fraction_y;

tmp_double = one_minus_x *(double)(the_image[floor_y][floor_x]) +fraction_x *(double)(the_image[floor_y][ceil_x]);
p1= tmp_double;
tmp_double = one_minus_x *(double)(the_image[ceil_y][floor_x]) +fraction_x *(double)(the_image[ceil_y][ceil_x]);
p2= tmp_double;
tmp_double = one_minus_y * (double)(p1) +fraction_y * (double)(p2);
p3= tmp_double;
return(p3);
}


/*define FLT_MAX 99999999
#define FLT_MIN -99999999

void Scale(struct Image *In, struct Image *Out) // THIS NEEDS TO BE FIXED
{
  float min, max, *InD, *OuD;
  long ImSize, i;

  min = FLT_MAX;
  max = FLT_MIN;
  InD = (float *)In->Data;
  ImSize = In->Rows * In->Cols;

  //Scan input for min/max values
  for(i=0; i<ImSize; ++i)
    {
      if(*InD<min)
	min = *InD;
      if(*InD>max)
	max = *InD;
      ++InD;
    }

  InD = (float *)In->Data;
  OuD = (float *)Out->Data;

  //scale the output
  for(i=0; i<ImSize; ++i)
    *OuD = (255/(max-min))*(*InD-min);
    }*/

 /*/ Parse through and get each W1L1 weight for the nural network
const int* getWeight_W1L1 (input)
{
 int i, j = 1;
 float weight1[640][480];

 for(i= 1; i <= 640; i++)
 {
 	for (j=1; j <=480; j++)
 	{
 		weight1[i][j] = strtok(input, ",");
 	}
 }
}

// Parse through and get each B1L1 weight for the nural network
const int* getBais_B1L1 (input)
{
 int i, j = 1;
 float bais1[640][480];

 for(i= 1; i <= 640; i++)
 {
 	for (j=1; j <=480; j++)
 	{
 		bais1[i][j] = strtok(input, ",");
 	}
 }
}

// Parse through and get each W1L2 weight for the nural network
const int* getWeight_W1L2 (input)
{
 int i = 1;
 float weight2[200];

 for(i= 1; i <= 200; i++)
 {
 	weight2[i] = strtok(input, ",");
 }
}

// Parse through and get each W1L2 weight for the nural network
const int* getBais_B1L2 (input)
{
 int i = 1;
 float bias2[200];

 for(i= 1; i <= 200; i++)
 {
 	bais2[i] = strtok(input, ",");
 }
 }*/





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                           Stuff We Might Not need                                              //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*array tograyscale(img)
{
   unsigned int x, y;
   grayimage timg;// undeclared
   double rc, gc, bc, l;
   unsigned int ofs;
 
   timg = alloc_grayimg(img->width, img->height);
 
   for(x=0; x < img->width; x++)
   {
      for(y=0; y < img->height; y++)
      {
        ofs = (y * img->width) + x;
        rc = (double) img->buf[ofs][0];
        gc = (double) img->buf[ofs][1];
        bc = (double) img->buf[ofs][2];
        l = 0.2126*rc + 0.7152*gc + 0.0722*bc;
        timg->buf[ofs][0] = (luminance) (l+0.5);
      }
   }
   return timg;
}

Threshold(strict Image *IMAGE, stuct Image *IMAGE1, int THRES) //Converts to binary image??
{
	int X, Y, GO, GB;
	GO = 225;
	GB = 0;
	
	for (Y=0; y<=IMAGE->Rows; Y++)
	{
		for(X = 0; X <= IMAGE->Cols; X++)
		{
			if (*(IMAGE1->Data+X+(long)Y*IMAGE->Cols)>THRES)
				*(IMAGE1->Data+X+(long)Y*IMAGE->Cols)= GO;
			else
				*(IMAGE1->Data+X+(long)Y*IMAGE->Cols)= GB;
		}
	}
	
	
}

// Attempt to load image
    void Img_IO (struct *IO[],char *filename[],char dir)

{
	FILE *fp;
	int i, sz_pix;
	
	if(dir)
	  // open (or create) a file for read 
		fp = fopen(filename, "rb");
	
	else
	  // open (or create) a file for write
		fp = fopen(filename, "wb");
	
	switch (IO->Type)
	{
		case BASIC:
			sz_pix = sizeof(unsigned char);
			break;
		
		case UINT:
			sz_pix = sizeof(unsigned int);
			break;
		
		case REAL:
			sz_pix = sizeof(float);
			break;
		
		case CMPLX:
			sz_pix = 2*sizeof(float);
			break;
	}
	
	// process the image by rows
	for (i=0; i<IO->Rows;  ++i)
		if(dir)
			fread(IO->Data + i*IO->Cols, IO->Cols,  sz_pix, fp);
		
		else
			fwrite(IO->Data + i*IO->Cols, IO->Cols, sz_pix, fp);
	
	fclose(fp);
}

//GOT TO DO THIS
void column_sum (image)
{
	int j, i = 1;
	float sum [640] = 0;
	float image[640][480];

	while (i<=640)
	{
		for (j = 1, j<=480, j++)
		{
			sum[i] = sum[i] + image[i][j];

			if (sum[i] = 0) // whole column is white
			{}
			if(sum[i] = 640) // whole column is black
			{}
			if (sum[i] = 160) //region of interest is probably in this column
			{}
		}
		i++
	}
	return(sum);
}*/