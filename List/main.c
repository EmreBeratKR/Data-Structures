#include <stdio.h>
#include <stdlib.h>


#define WHITE "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define PURPLE "\033[1;35m"


#define MAX_ELEMENT_COUNT 5
#define DEFAULT_VALUE 0


typedef char* string;
typedef enum { False = 0, True = 1 } bool;

// Just a colorful text
void Highlight(string msg, string color)
{
    printf("%s", color);
    printf("%s", msg);
    printf("%s", WHITE);
}

typedef struct
{
    int elements[MAX_ELEMENT_COUNT];
    int count;

} List;

// Adds the Element at the last spot
// O(1)
void Add(List* list, int element)
{
    if (list->count >= MAX_ELEMENT_COUNT)
    {
        Highlight("The Element cannot be added, The list has already maxed out!\n", RED);
        return;
    }

    list->elements[list->count] = element;
    list->count++;
    Highlight("The Element successfully added!\n", GREEN);
}

// Inserts the Element at the given Index
// O(1)
void Insert(List* list, int index, int element)
{
    if (index >= list->count || index < 0)
    {
        Highlight("Index out of range, Cannot insert the element at that index!\n", RED);
        return;
    }

    list->elements[index] = element;
    Highlight("The Element successfully inserted!\n", GREEN);
}

// Removes the Given Element at first match
// and Slides the following elements left by 1
// We must visit every element
// O(n)
void Remove(List* list, int element)
{
    for (int i = 0; i < list->count; ++i)
    {
        int current = list->elements[i];
        if (current == element)
        {
            for (int j = i; j < list->count; ++j)
            {
                list->elements[j] = list->elements[j+1];
            }
            list->elements[list->count-1] = DEFAULT_VALUE;
            list->count--;
            Highlight("The Element successfully Removed!\n", GREEN);
            return;
        }
    }

    Highlight("Could not found the element, It cannot be removed!\n", RED);
}

// If we found a match, we delete it,
// and we Slide the following elements left by {found} amount until we find another match
// do this cycle over and over until we visited all elements,
// and also the {found} amount increases by 1 for every match
// So, we must visit every element
// O(n)
void RemoveAll(List* list, int element)
{
    int found = 0;
    for (int i = 0; i < list->count; ++i)
    {
        list->elements[i-found] = list->elements[i];
        if (list->elements[i] == element)
        {
            list->elements[i] = DEFAULT_VALUE;
            found++;
        }
    }
    list->count -= found;

    if (found == 0)
    {
        Highlight("Could not found any matching element, Cannot remove any element(s)!\n", RED);
    }
    else
    {
        Highlight("All Element(s) successfully Removed!\n", GREEN);
    }
}

// This does the same thing as Remove() method
// The differences are we just jump directly to index,
// and Sliding only occurs 1 time
// In worst case (index = 0), We must visit every element
// O(n-index)
void RemoveAt(List* list, int index)
{
    if (index >= list->count || index < 0)
    {
        Highlight("Index out of range, Cannot remove an element at that index!\n", RED);
        return;
    }

    for (int j = index; j < list->count; ++j)
    {
        list->elements[j] = list->elements[j+1];
    }
    list->elements[list->count-1] = DEFAULT_VALUE;
    list->count--;
    Highlight("The Element successfully Removed at given index!\n", GREEN);
}

// Same as RemoveAt(index = 0)
// This is the worst case of the RemoveAt() method
// We must visit every element
// O(n)
void RemoveFirst(List* list)
{
    if (list->count == 0)
    {
        Highlight("The list is empty, Cannot remove the first element!\n", RED);
        return;
    }

    for (int j = 0; j < list->count; ++j)
    {
        list->elements[j] = list->elements[j+1];
    }
    list->elements[list->count-1] = DEFAULT_VALUE;
    list->count--;
    Highlight("The First Element successfully Removed from the List!\n", GREEN);
}

// We simply remove the last element
// No Sliding needed
// This is the best case of the RemoveAt() method
// O(1)
void RemoveLast(List* list)
{
    if (list->count == 0)
    {
        Highlight("The list is empty, Cannot remove the last element!\n", RED);
        return;
    }

    list->elements[list->count-1] = DEFAULT_VALUE;
    list->count--;
    Highlight("The Last Element successfully Removed from the List!\n", GREEN);
}

// This is equivalent to indexer []
// O(1)
int GetAt(List* list, int index)
{
    if (index >= list->count || index < 0)
    {
        Highlight("Index out of range, Returning the Default Value!\n", RED);
        return DEFAULT_VALUE;
    }

    Highlight("The Element successfully returned at given index!\n", GREEN);
    printf(PURPLE);
    printf("Value at index(%d) is %d\n", index, list->elements[index]);
    printf(WHITE);
    return list->elements[index];
}

// Same as GetAt(index = 0)
// Reaches the first element
// O(1)
int GetFirst(List* list)
{
    if (list->count == 0)
    {
        Highlight("The list is empty, Cannot get the first element!\n", RED);
        return DEFAULT_VALUE;
    }

    Highlight("The First Element successfully returned!\n", GREEN);
    printf(PURPLE);
    printf("First Value is %d\n", list->elements[0]);
    printf(WHITE);
    return list->elements[0];
}

// Same as GetAt(index = lastIndex)
// Reaches the last element
// O(1)
int GetLast(List* list)
{
    if (list->count == 0)
    {
        Highlight("The list is empty, Cannot get the last element!\n", RED);
        return DEFAULT_VALUE;
    }

    Highlight("The Last Element successfully returned!\n", GREEN);
    printf(PURPLE);
    printf("Last Value is %d\n", list->elements[list->count-1]);
    printf(WHITE);
    return list->elements[list->count-1];
}

// If our target element is the last element, We must visit all elements
// In worst case => O(n)
int IndexOf(List* list, int element)
{
    for (int i = 0; i < list->count; ++i)
    {
        if (list->elements[i] == element)
        {
            return i;
        }
    }

    Highlight("The Element could not be found, Returning -1\n", RED);
    return -1;
}

// We must visit all elements
// O(n)
bool Contains(List* list, int element)
{
    for (int i = 0; i < list->count; ++i)
    {
        if (list->elements[i] == element)
        {
            return True;
        }
    }
    return False;
}

// Simple isEqual operation
// O(1)
bool isEmpty(List* list)
{
    return (bool)(list->count == 0);
}

// We must visit all elements
// O(n)
void Print(List* list)
{
    for (int i = 0; i < list->count; ++i)
    {
        printf(GREEN);
        printf("(%d) %d\n", i, list->elements[i]);
        printf(WHITE);
    }
}

// O(1)
void Clear(List* list)
{
    list->count = 0;
}

// Constructor
List* Init(List* list)
{
    list = (List*)malloc(sizeof(list));

    list->count = 0;

    return list;
}



int main()
{
    List* pList = Init(pList);

    int choice;
    while (True)
    {
        Highlight("(0) Exit -> Exits the program\n", YELLOW);
        Highlight("(1) Add -> Adds an int element to the list\n", YELLOW);
        Highlight("(2) Insert -> Inserts an int element at the given index\n", YELLOW);
        Highlight("(3) Remove -> Removes the first matched element from the list\n", YELLOW);
        Highlight("(4) Remove All -> Removes all matched element(s) from the list\n", YELLOW);
        Highlight("(5) Remove At -> Removes the element at the given index\n", YELLOW);
        Highlight("(6) Remove First -> Removes the first element from the list\n", YELLOW);
        Highlight("(7) Remove Last -> Removes the last element from the list\n", YELLOW);
        Highlight("(8) Get At -> Returns the value at given index\n", YELLOW);
        Highlight("(9) Get First -> Returns the First value from the list\n", YELLOW);
        Highlight("(10) Get Last -> Returns the Last value from the list\n", YELLOW);
        Highlight("(11) Index Of -> Returns the first matched element's index\n", YELLOW);
        Highlight("(12) Contains -> Returns if the list Contains given element or not\n", YELLOW);
        Highlight("(13) Count -> Returns the Element Count of the List\n", YELLOW);
        Highlight("(14) Print -> Prints the Element(s) at the List one by one\n", YELLOW);
        Highlight("(15) Clear -> Removes all Element(s) and makes the list empty\n", YELLOW);

        Highlight("Pick an operation (0-13) >", BLUE);
        scanf("%d", &choice);

        if (choice == 0) break;

        if (choice == 1)
        {
            int value = DEFAULT_VALUE;
            Highlight("Type an integer value to Add >", WHITE);
            scanf("%d", &value);
            Add(pList, value);
        }

        if (choice == 2)
        {
            int index = -1;
            int value = DEFAULT_VALUE;
            Highlight("Type the index, where you want to Insert >", WHITE);
            scanf("%d", &index);
            Highlight("Type an integer value to Insert >", WHITE);
            scanf("%d", &value);
            Insert(pList, index, value);
        }

        if (choice == 3)
        {
            int value = DEFAULT_VALUE;
            Highlight("Type an integer value to Remove >", WHITE);
            scanf("%d", &value);
            Remove(pList, value);
        }

        if (choice == 4)
        {
            int value = DEFAULT_VALUE;
            Highlight("Type an integer value to Remove >", WHITE);
            scanf("%d", &value);
            RemoveAll(pList, value);
        }

        if (choice == 5)
        {
            int index = DEFAULT_VALUE;
            Highlight("Type an index, where you want to Remove at >", WHITE);
            scanf("%d", &index);
            RemoveAt(pList, index);
        }

        if (choice == 6) RemoveFirst(pList);

        if (choice == 7) RemoveLast(pList);

        if (choice == 8)
        {
            int index = DEFAULT_VALUE;
            Highlight("Type an index, where you want to Get value >", WHITE);
            scanf("%d", &index);
            GetAt(pList, index);
        }

        if (choice == 9) GetFirst(pList);

        if (choice == 10) GetLast(pList);

        if (choice == 11)
        {
            int value = DEFAULT_VALUE;
            Highlight("Type an integer value to Get its index >", WHITE);
            scanf("%d", &value);
            int result = IndexOf(pList, value);
            if (result != -1)
            {
                printf(PURPLE);
                printf("The element found at index(%d)\n", result);
                printf(WHITE);
            }
        }

        if (choice == 12)
        {
            int value = DEFAULT_VALUE;
            Highlight("Type an integer value to Check if it is in the list or not >", WHITE);
            scanf("%d", &value);
            printf(PURPLE);
            if (Contains(pList, value))
            {
                printf("The list Contains %d", value);
                Highlight(" (True)\n", GREEN);
            }
            else
            {
                printf("The list does not Contain %d", value);
                Highlight(" (False)\n", RED);
            }
            printf(WHITE);
        }

        if (choice == 13)
        {
            printf(PURPLE);
            printf("The List has got %d element(s)\n", pList->count);
            printf(WHITE);
        }

        if (choice == 14)
        {
            if (isEmpty(pList))
            {
                Highlight("The list is empty, Cannot Print the elements\n", RED);
            }
            else
            {
                Print(pList);
            }
        }

        if (choice == 15)
        {
            Clear(pList);
            Highlight("The list has been Cleared!\n", GREEN);
        }
    }
    return 0;
}