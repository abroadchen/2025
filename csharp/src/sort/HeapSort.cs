

namespace DefaultNamespace;

public class HeapSort
{
    /// <summary>
    /// 
    /// </summary>
    /// <param name="array"></param>
    /// <param name="nowIndex">当前作为根节点的索引</param>
    /// <param name="arrayLength">哪些位置没有确定</param>
    /// <returns></returns>
    static void HeapCompare(int[] array, int nowIndex, int arrayLength)
    {
        int left = 2 * nowIndex + 1;
        int right = 2 * nowIndex + 2;
        int biggerIndex = nowIndex;
        if (left < arrayLength && array[left] > array[biggerIndex])
        {
            biggerIndex = left;
        }

        if (right < arrayLength && array[right] > array[biggerIndex])
        {
            biggerIndex = right;
        }

        if (biggerIndex != nowIndex)
        {
            int temp = array[nowIndex];
            array[nowIndex] = array[biggerIndex];
            array[biggerIndex] = temp;
            HeapCompare(array, biggerIndex, arrayLength);
        }
    }

    static void BuildBigHeap(int[] array)
    {
        for (int i = array.Length / 2 - 1; i >= 0; i--)
        {
            HeapCompare(array, i, array.Length);
        }
    }

    static void HeapSort(int[] array)
    {
        BuildBigHeap(array);

        for (int i = array.Length - 1; i > 0; i--)
        {
            int temp = array[0];
            array[0] = array[i];
            array[i] = temp;
            HeapCompare(array, 0, i);
        }
    }
}