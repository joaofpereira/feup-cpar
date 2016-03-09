using System;

namespace matrix_prod_cs
{
    public class Program
    {
        public static void Main(string[] args)
        {
            int op = 1;

            do
            {
                Console.WriteLine();
                Console.WriteLine("-------------------------");
                Console.WriteLine("1. Multiplication");
                Console.WriteLine("2. Line Multiplication");
                Console.WriteLine();
                Console.WriteLine("0. Exit");
                Console.WriteLine("-------------------------");

                Console.Write("Selection?: ");
                String input = Console.ReadLine();

                if (int.TryParse(input, out op))
                {
                    switch (op)
                    {
                        case 1:
                            break;

                        case 2:
                            break;

                        default:
                            break;
                    }
                }
                else
                {
                    Console.WriteLine("Error: non-numeric input is unsupported, try again.");
                    op = 1;
                }

                Console.WriteLine();
            } while (op != 0);
        }
        
        
            void OnMultLine(int lines, int columns)
            {
                double[] matrixA = new double[lines*columns], matrixB = new double[lines*columns], matrixResult = new double[lines*columns];
                
                // initialize matrix values of matrix A
                for(int i = 0; i < lines; i++)
                {
                    for(int j = 0; j < lines; j++)
                    {
                        matrixA[i*lines + j] = 1.0;
                    }
                }
                
                printMatrix(matrixA, lines, columns);
                
                // initialize matrix values of matrix B
                for(int i = 0; i < columns; i++)
                {
                    for(int j = 0; j < columns; j++)
                    {
                        matrixB[i*columns + j] = 1.0;
                    }
                }
                
                printMatrix(matrixB, lines, columns);
                
                for(int i = 0; i < lines; i++)
                {
                    for(int j = 0; j < columns; j++)
                    {
                        for(int k = 0; k < lines; k++)
                        {
                            matrixResult[i*lines + j] = matrixA[i*lines + k] * matrixB[k*columns + j];
                        }
                    }
                }
                
                printMatrix(matrixResult, lines, columns);
            }
            
            void printMatrix(double[] matrix, int lines, int columns)
            {
                for(int i = 0; i < columns; i++)
                {
                    for(int j = 0; j < lines; j++)
                    {
                        Console.Write(matrix[i*columns + j].ToString());
                    }
                    
                    Console.WriteLine();
                }

            }
    }
}
