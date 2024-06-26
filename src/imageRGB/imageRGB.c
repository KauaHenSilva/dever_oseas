
#include "imageRGB.h"
#include <stdio.h>
#include <stdlib.h>

FILE *fileRGB = NULL;

void printDimensoesImage(ImageRGB *img)
{
  printf("A largura e: %d", img->largura);
  printf("A altura e: %d", img->altura);
}

void printPixel(int lin, int col, ImageRGB *img)
{
  int r, g, b;
  r = img->pixel[lin * larguraGlob + col].red;
  g = img->pixel[lin * larguraGlob + col].green;
  b = img->pixel[lin * larguraGlob + col].blue;

  if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    perror("Valores RGB fora do intervalo permitido.\n");

  printf("\033[38;2;%d;%d;%dm**\033[0m", r, g, b);
}

PixelRGB getPixel(int lin, int col, ImageRGB *img)
{
  return img->pixel[lin * larguraGlob + col];
}

void setPixel(int lin, int col, ImageRGB *img)
{
  for (int x = 0; x < lin; x++)
    for (int y = 0; y < col; y++)
    {
      fscanf(fileRGB, "%d", &img->pixel[x * larguraGlob + y].red);
      fscanf(fileRGB, "%d", &img->pixel[x * larguraGlob + y].green);
      fscanf(fileRGB, "%d", &img->pixel[x * larguraGlob + y].blue);
      fgetc(fileRGB);
    }
}

ImageRGB *alocacaoImage()
{
  fileRGB = fopen("./input_image.txt", "r");
  if (!fileRGB)
    perror("Não leu");

  fscanf(fileRGB, "%d", &alturaGlob);
  fscanf(fileRGB, "%d", &larguraGlob);

  ImageRGB *image = (ImageRGB *)malloc(sizeof(ImageRGB));
  if (!image)
    perror("ERRO NA ALOCACAO DE MEMORIA DAS LINHAS DA MATRIZ.");

  image->altura = alturaGlob;
  image->largura = larguraGlob;

  image->pixel = (PixelRGB *)malloc(sizeof(PixelRGB) * alturaGlob * larguraGlob);
  if (!image->pixel)
    perror("ERRO NA ALOCACAO DE MEMORIA DAS LINHAS DA MATRIZ.");

  return image;
}

void printImage(ImageRGB *img)
{
  for (int x = 0; x < img->largura; x++)
  {
    for (int y = 0; y < img->altura; y++)
      printPixel(x, y, img);
    printf("\n");
  }
}

void liberacaodeImage(ImageRGB *img)
{
  free(img->pixel);
  free(img);
}
