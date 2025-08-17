// See https://aka.ms/new-console-template for more information

//Console.WriteLine("Hello, World!");

using Tetris.Lesson1;

namespace Tetris;

internal class Program
{
    public static void Main(string[] args)
    {
        var g = new Game();
        g.Start();
    }
}