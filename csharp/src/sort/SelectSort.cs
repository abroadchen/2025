namespace DefaultNamespace;

public class SelectSort
{
    static void SelectSort(int[] arr)
    {
        for (int m = 0; m < arr.Length; m++)
        {
            int index = 0;
            for (int n = 1; n < arr.Length - m; n++)
            {
                if (arr[index] < arr[n])
                {
                    index = n;
                }
            }
            if (index != arr.Length - 1 - m)
            {
                int temp = arr[index];
                arr[index] = arr[arr.Length - 1 - m];
                arr[arr.Length - 1 - m] = temp;
            }
        }
    }
}