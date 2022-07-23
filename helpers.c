#include "helpers.h"
#include <cs50.h>

// Converter imagem em escala de cinza
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
// Percorrer as linhas 
    for (int i = 0; i < height; i++)
    {
 // Percorrer as colunas 
        for (int j = 0; j < width; j++)
        {
         // Obtém valores RGBTriple 
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;
            float red = image[i][j].rgbtRed;
          // Calcula a média
            int average = round((red + blue + green) / 3);
                       // Configura todos os valores para a média 
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i]  [j].rgbtRed = average;
        }
    }    
        return;
}



// Reflete a imagem horizontalmente 
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
 
      // Faz um loop pelas linhas 
    for (int i = 0; i < height; i++)
    {
           // Faz um loop pelas colunas 
        for (int j = 0; j < width / 2; j++)
        {
       // Reflete pixels 
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}
  


// Desfocar imagem 

void blur(int height, int width, RGBTRIPLE image[height][width])
{
        // Criar array 
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
       // Percorre as linhas 
    for (int i = 0; i < height; i++)
    {
        // Percorre as colunas 
        for (int j = 0; j < width; j++)
        {
             // Inicializa os valores 
            float sum_red;
            float sum_blue;
            float sum_green;
            int counter;
            sum_red = sum_blue = sum_green = counter = 0;
            
               // Para cada pixel, faz um loop vertical e horizontal 
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                      // Verifica se o pixel está fora das linhas
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
 // Verifica se o pixel está fora das colunas 
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                     // Caso contrário, adicione às somas 
                    sum_red += temp[i + k][j + l].rgbtRed;
                    sum_blue += temp[i + k][j + l].rgbtBlue;
                    sum_green += temp[i + k][j + l].rgbtGreen;
                    counter++;
                }
            }
              // Obtém a imagem média e desfocada da imagem 
            image[i][j].rgbtRed = round(sum_red / counter);
            image[i][j].rgbtGreen = round(sum_green / counter);
            image[i][j].rgbtBlue = round(sum_blue / counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
      // Create temp array
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    // Initialise Sobel arrays
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    
      // Loop through rows
    for (int i = 0; i < height; i++)
    {
        // Loop through columns
        for (int j = 0; j < width; j++)
        {
            // Initialise ints
            float Gx_red;
            float Gx_blue;
            float Gx_green;
            float Gy_red;
            float Gy_blue;
            float Gy_green;
            Gx_red = Gx_blue = Gx_green = Gy_red = Gy_blue = Gy_green = 0;
            // For each pixel, loop vertical and horizontal
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check if pixel is outside rows
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    // Check if pixel is outside columns
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    // Otherwise add to sums
                    Gx_red += temp[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                    Gx_green += temp[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                    Gx_blue += temp[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                    Gy_red += temp[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                    Gy_green += temp[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                    Gy_blue += temp[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                }
                   // Calculate Sobel operator
            int red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));
            // Cap at 255
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            // Assign new values to pixels
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}
            }
    return;
}
