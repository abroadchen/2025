namespace DefaultNamespace;

public class BubbleSort
{
    private bool isSort = false;
    static void BubbleSort(int[] arr)
    {
        for (int m = 0; m < arr.Length; m++)
        {
            isSort = false;
            for (int n = 0; n < arr.Length - 1 - m; n++)
            {
                if (arr[n] > arr[n + 1])
                {
                    isSort = true;
                    int temp = arr[n];
                    arr[n] = arr[n + 1];
                    arr[n + 1] = temp;
                }
            }
            if (!isSort)
            {
                break;
            }
        }
    }
}