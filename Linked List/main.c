#include <stdio.h>
#include <stdlib.h>


#define WHITE "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define PURPLE "\033[35m"

#define MAX_STRING_LENGTH 20
#define MAX_NODE_COUNT 5


typedef char* string;
typedef enum { False = 0, True = 1 } bool;

// Just a colorful text
void Highlight(string msg, string color)
{
    printf("%s", color);
    printf("%s", msg);
    printf("%s", WHITE);
}

void Line(string color)
{
    Highlight("------------------------\n", color);
}

void IndexOutOfRange()
{
    Highlight("Index out of range!\n", RED);
}

void ListIsEmpty()
{
    Highlight("List is Empty!\n", RED);
}

typedef struct
{
    string name;
    string school;
    int age;
    double GPA;

} Student;

typedef struct ListNode
{
    Student* data;
    struct ListNode* next;

} ListNode;

typedef struct
{
    ListNode* head;
    ListNode* tail;
    int count;

} List;

// Constructor for a single node
ListNode* NewNode(ListNode* node)
{
    if (node == NULL)
    {
        node = malloc(sizeof(ListNode));
        node->data = (Student*)malloc(sizeof(Student));
        node->data->name = (string)malloc(sizeof(char) * MAX_STRING_LENGTH);
        node->data->school = (string)malloc(sizeof(char) * MAX_STRING_LENGTH);
    }

    node->next = NULL;

    printf("Enter a name >");
    scanf("%s", node->data->name);

    printf("Enter a school name >");
    scanf("%s", node->data->school);

    printf("Enter an age >");
    scanf("%d", &(node->data->age));

    printf("Enter a GPA >");
    scanf("%lf", &(node->data->GPA));

    return node;
}

// Constructor for an empty List
List EmptyList()
{
    List newList;
    newList.head = NULL;
    newList.tail = NULL;
    newList.count = 0;
    return newList;
}

// Deallocates the given node
void FreeNode(ListNode* node)
{
    free(node->data->name);
    free(node->data->school);
    free(node->data);
    free(node);
}

// Deallocates the list completely
// We must visit every node
// O(n)
// n is node count
void Clear(List* list)
{
    if (list->count == 0)
    {
        ListIsEmpty();
        return;
    }

    ListNode* current = list->head;
    ListNode* next;
    while (True)
    {
        next = current->next;
        FreeNode(current);

        if (next == NULL)
        {
            list->head = NULL;
            list->tail = NULL;
            list->count = 0;
            return;
        }

        current = next;
    }
}

// Adds a new node that is linked to old tail
// List tail is updated to the added node
// O(1)
void Add(List* list)
{
    if (list->count >= MAX_NODE_COUNT)
    {
        Highlight("Cannot add any data, List is already maxed out!\n", RED);
        return;
    }

    if (list->count == 0)
    {
        list->head = NewNode(list->head);
        list->tail = list->head;
        list->count++;
        return;
    }

    list->tail->next = NewNode(list->tail->next);
    list->tail = list->tail->next;
    list->count++;
}

// We must visit nodes one by one until we reach the given index
// Old node's data replaced with the new node's data
// O(n)
// n is the given index
void Insert(List* list, int index)
{
    if (index >= list->count || index < 0)
    {
        IndexOutOfRange();
        return;
    }

    if (index == 0)
    {
        if (list->count == 1)
        {
            list->head = NewNode(list->head);
            list->tail = list->head;
            return;
        }

        ListNode* next = list->head->next;
        list->head = NewNode(list->head);
        list->head->next = next;
        return;
    }

    if (index == (list->count-1))
    {
        list->tail = NewNode(list->tail);
        return;
    }

    int counter = 0;
    ListNode* last = NULL;
    ListNode* current = list->head;
    while (True)
    {
        if (counter == index)
        {
            ListNode* next = current->next;
            current = NewNode(current);
            last->next = current;
            current->next = next;
            return;
        }
        last = current;
        current = current->next;
        counter++;
    }
}

// We must visit nodes one by one until we reach the given index
// Reached node will be deallocated
// We must merge left side and right side
// O(n)
// n is the given index
void RemoveAt(List* list, int index)
{
    if (index >= list->count || index < 0)
    {
        IndexOutOfRange();
        return;
    }

    if (index == 0)
    {
        if (list->count == 1)
        {
            FreeNode(list->head);
            Clear(list);
            return;
        }

        ListNode* target = list->head;
        list->head = list->head->next;
        FreeNode(target);
        list->count--;
        return;
    }

    if (index == (list->count-1))
    {
        if (list->count == 1)
        {
            FreeNode(list->tail);
            Clear(list);
            return;
        }

        FreeNode(list->tail);
        list->count--;
        int counter = 0;
        ListNode* current = list->head;
        while (True)
        {
            if (counter == (list->count-1))
            {
                list->tail = current;
                current->next = NULL;
                return;
            }
            current = current->next;
            counter++;
        }
    }

    int counter = 0;
    ListNode* last = NULL;
    ListNode* current = list->head;
    while (True)
    {
        if (counter == index)
        {
            ListNode* next = current->next;
            FreeNode(current);
            last->next = next;
            list->count--;
            return;
        }
        last = current;
        current = current->next;
        counter++;
    }
}

// Old head is replaced with new one
// Old head will be deallocated
// O(1)
void RemoveFirst(List* list)
{
    if (list->count == 0)
    {
        ListIsEmpty();
        return;
    }

    if (list->count == 1)
    {
        FreeNode(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->count = 0;
        return;
    }

    ListNode* target = list->head;
    list->head = list->head->next;
    FreeNode(target);
    list->count--;
}

// Old Tail is replaced with new one
// Old Tail will be deallocated
// New Tail's next should be set as NULL
// We need to access the new Tail
// O(n)
// n is Node count
void RemoveLast(List* list)
{
    if (list->count == 0)
    {
        ListIsEmpty();
        return;
    }

    if (list->count == 1)
    {
        FreeNode(list->tail);
        list->head = NULL;
        list->tail = NULL;
        list->count = 0;
        return;
    }

    FreeNode(list->tail);
    list->count--;
    int counter = 0;
    ListNode* current = list->head;
    while (True)
    {
        if (counter == (list->count-1))
        {
            list->tail = current;
            current->next = NULL;
            return;
        }
        current = current->next;
        counter++;
    }
}

// We must visit nodes one by one until we reach the given index
// We just return its data
// O(n)
// n is the given index
Student* GetAt(List* list, int index)
{
    if (index >= list->count || index < 0)
    {
        IndexOutOfRange();
        return NULL;
    }

    if (index == 0) return list->head->data;

    if (index == (list->count-1)) return list->tail->data;

    int counter = 0;
    ListNode* current = list->head;
    while (True)
    {
        if (counter == index) return current->data;

        current = current->next;
        counter++;
    }
}

// We just simply return head's data
// O(1)
Student* GetFirst(List* list)
{
    if (list->count == 0)
    {
        ListIsEmpty();
        return NULL;
    }

    return list->head->data;
}

// We just simply return tail's data
// O(1)
Student* GetLast(List* list)
{
    if (list->count == 0)
    {
        ListIsEmpty();
        return NULL;
    }

    return list->tail->data;
}

// Student data has got a fixed amount of data types
// So it is constant time job
// O(1)
void PrintStudent(Student* data)
{
    if (data == NULL) return;

    Line(GREEN);
    printf("Name: %s\n", data->name);
    printf("School Name: %s\n", data->school);
    printf("Age: %d\n", data->age);
    printf("GPA: %lf\n", data->GPA);
    Line(GREEN);
}

// We must visit every node
// O(n)
// n is node count
void PrintList(List* list)
{
    if (list->count == 0)
    {
        ListIsEmpty();
        return;
    }

    ListNode* current = list->head;
    while (True)
    {
        if (current == NULL) return;

        PrintStudent(current->data);
        current = current->next;
    }
}

int main()
{
    List list = EmptyList();

    int choice;
    while (True)
    {
        Highlight("(0) Exit -> Exits the program\n", YELLOW);
        Highlight("(1) Add -> Adds a new Student Data to the list\n", YELLOW);
        Highlight("(2) Insert -> Inserts a Student Data at the given index\n", YELLOW);
        Highlight("(3) Remove At -> Removes the Student Data at the given index\n", YELLOW);
        Highlight("(4) Remove First -> Removes the first Student Data from the list\n", YELLOW);
        Highlight("(5) Remove Last -> Removes the last Student Data from the list\n", YELLOW);
        Highlight("(6) Get At -> Returns the Student Data at given index\n", YELLOW);
        Highlight("(7) Get First -> Returns the First Student Data from the list\n", YELLOW);
        Highlight("(8) Get Last -> Returns the Last Student Data from the list\n", YELLOW);
        Highlight("(9) Count -> Returns the Student Data Count of the List\n", YELLOW);
        Highlight("(10) Print -> Prints the all Student Data(s) at the List one by one\n", YELLOW);
        Highlight("(11) Clear -> Removes all Student Data(s) and makes the list empty\n", YELLOW);

        Highlight("Pick an operation (0-11) >", BLUE);
        scanf("%d", &choice);

        if (choice == 0) break;

        if (choice == 1) Add(&list);

        if (choice == 2)
        {
            int index = 0;
            printf("Please type an index >");
            scanf("%d", &index);
            Insert(&list, index);
        }

        if (choice == 3)
        {
            int index = 0;
            printf("Please type an index >");
            scanf("%d", &index);
            RemoveAt(&list, index);
        }

        if (choice == 4) RemoveFirst(&list);

        if (choice == 5) RemoveLast(&list);

        if (choice == 6)
        {
            int index = 0;
            printf("Please type an index >");
            scanf("%d", &index);
            Student* data = GetAt(&list, index);
            if (data != NULL)
            {
                printf("Data at %d\n", index);
                PrintStudent(data);
            }
        }

        if (choice == 7) PrintStudent(GetFirst(&list));

        if (choice == 8) PrintStudent(GetLast(&list));

        if (choice == 9) printf("Data count in list = %d\n", list.count);

        if (choice == 10) PrintList(&list);

        if (choice == 11) Clear(&list);
    }
    return 0;
}