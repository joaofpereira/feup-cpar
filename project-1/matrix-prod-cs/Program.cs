using System;

namespace matrix_prod_cs
{
    public class Program
    {
        public static void OnMult(int m_ar, int m_br)
        {

        }

        public static void OnMultLine(int m_ar, int m_br)
        {

        }

        public static float produtoInterno(float[] v1, float[] v2, int col)
        {
            float sum = 0;

            for (uint i = 0; i < col; i++)
                sum += v1[i] * v2[i];

            return sum;
        }

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

                Console.Write("Selection: ? ");
                string input = Console.ReadLine();

                if (int.TryParse(input, out op))
                {
                    if (op == 1 || op == 2)
                    {
                        Console.Write("Dimensions: lins cols ? ");
                        string[] tokens = Console.ReadLine().Split();

                        int lin, col;
                        if (tokens.Length == 2 && int.TryParse(tokens[0], out lin) && int.TryParse(tokens[1], out col))
                        {
                            switch (op)
                            {
                                case 1:
                                    OnMult(lin, col);
                                    break;

                                case 2:
                                    OnMultLine(lin, col);
                                    break;

                                default:
                                    break;
                            }
                        }
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
    }
}
