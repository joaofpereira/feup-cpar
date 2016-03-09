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
    }
}
