

namespace DefaultNamespace;

public class ShellSort
{
    static void ShellSort(int[] a)
    {
        for (int step = arr.Length / 2; step > 0; step /= 2)
        {
            for (int i = step; i < a.Length; i++)
            {
                int noSortNum = arr[i];
                int sortIndex = i - step;
                while (sortIndex >= 0 && arr[sortIndex] > noSortNum)
                {
                    arr[sortIndex + step] = arr[sortIndex];
                    sortIndex -= step;
                }

                arr[sortIndex + step] = noSortNum;
            }
        }
    }
}