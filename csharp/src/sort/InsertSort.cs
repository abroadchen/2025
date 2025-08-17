namespace DefaultNamespace;

public class InsertSort
{
    
    static void InsertSort(int[] arr)
    {
        for (int i = 1; i < arr.Length; i++)
        {
            int sortIndex = i - 1;
            int noSortNum = arr[i];
            while (sortIndex >= 0 && arr[sortIndex] > noSortNum)
            {
                arr[sortIndex + 1] = arr[sortIndex];
                --sortIndex;
            }

            arr[sortIndex + 1] = noSortNum;
        }
    }
}