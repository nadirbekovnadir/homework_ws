#ifndef LinkedList_H
#define LinkedList_H

template <class T>
class LinkedList
{
    enum NodeType : char
    {
        DATANODE,
        BEGINNODE,
        ENDNODE
    };

    //Методы типа под вопросом большим
    struct Node
    {
        Node *prev = nullptr;
        Node *next = nullptr;
        virtual NodeType Type() = 0;
    };

    struct DataNode : public LinkedList::Node
    {
        virtual NodeType Type() { return DATANODE; }
        T data;
    };

    struct BeginNode : public LinkedList::Node
    {
        virtual NodeType Type() { return BEGINNODE; }
    };

    struct EndNode : public LinkedList::Node
    {
        virtual NodeType Type() { return ENDNODE; }
    };

    int size;
    Node *beginNode;
    Node *endNode;

public:
    class Iterator
    {
        Node *value = nullptr;

    public:
        T operator*()
        {
            if (value->Type() == BEGINNODE)
                operator++();

            if (value->Type() == ENDNODE)
                operator--();

            DataNode *temp = (DataNode *)value;

            return temp->data;
        }

        Iterator &operator++()
        {
            value = value->next;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            operator++();
            return temp;
        }

        Iterator &operator--()
        {
            value = value->prev;
            return *this;
        }

        Iterator operator--(int)
        {
            Iterator temp = *this;
            operator--();
            return temp;
        }

        bool operator==(const Iterator &iter)
        {
            if (iter.value == value)
                return true;

            return false;
        }

        bool operator!=(const Iterator &iter)
        {
            return !operator==(iter);
        }

        friend class LinkedList;
    };

public:
    LinkedList()
    {
        size = 0;

        beginNode = new BeginNode;
        endNode = new EndNode;

        beginNode->next = endNode;
        endNode->prev = beginNode;
    }

    int Size()
    {
        return size;
    }

    //Не буду тратить свое время на выпендреж
    //и использование &&

    //Все методы ниже используют одинаковый метод
    //"связывания" узлов, можно было бы вынести в какой нибудь хитрый Bind,
    //но мне лень...
    void PushBack(T value)
    {
        size++;

        DataNode *temp = new DataNode;
        temp->data = value;

        temp->next = endNode;
        temp->prev = endNode->prev;

        endNode->prev->next = temp;
        endNode->prev = temp;
    }

    Iterator Begin()
    {
        Iterator temp;
        temp.value = beginNode;
        return temp;
    }

    Iterator End()
    {
        Iterator temp;
        temp.value = endNode;
        return temp;
    }

    void PushFront(T value)
    {
        size++;

        DataNode *temp = new DataNode;
        temp->data = value;

        temp->prev = beginNode;
        temp->next = beginNode->next;

        beginNode->next->prev = temp;
        beginNode->next = temp;
    }

    T Front()
    {
        if (size == 0)
            return T();

        return beginNode->next->data;
    }

    T Back()
    {
        if (size == 0)
            return T();

        return (DataNode *)endNode->prev->data;
    }

    T PopFront()
    {
        if (size == 0)
            return T();

        size--;

        DataNode *curr = (DataNode *)beginNode->next;
        T value = curr->data;

        beginNode->next = curr->next;
        curr->next->prev = beginNode;

        delete curr;

        return value;
    }

    T PopBack()
    {
        if (size == 0)
            return T();

        size--;

        DataNode *curr = (DataNode *)endNode->prev;
        T value = curr->data;

        endNode->prev = curr->prev;
        curr->prev->next = endNode;

        delete curr;

        return value;
    }

    //Хитрая и глупая мысль о перестановке значений закралась...
    void Swap(int first, int second)
    {
        Node *fNode = GetNode(first);
        Node *sNode = GetNode(second);

        Swap(fNode, sNode);
    }

    void Sort()
    {
        if (size < 1)
            return;

        QuickSort(++Begin(), --End());
    }

private:
    void Swap(Node *fNode, Node *sNode)
    {
        if (fNode == sNode)
            return;

        Node *temp;

        temp = fNode->prev;

        fNode->prev = sNode->prev;
        fNode->prev->next = fNode;

        sNode->prev = temp;
        sNode->prev->next = sNode;

        temp = fNode->next;

        fNode->next = sNode->next;
        fNode->next->prev = fNode;

        sNode->next = temp;
        sNode->next->prev = sNode;
    }

    void SwapIter(Iterator &one, Iterator &two)
    {
        auto fNode = one.value;
        auto sNode = two.value;

        Swap(fNode, sNode);
        one.value = sNode;
        two.value = fNode;
    }

    void QuickSort(Iterator first, Iterator last)
    {
        if (first == last)
            return;

        auto left = first;
        auto right = last;
        auto pivot = left++;

        if (left == right)
        {
            if (*(--left) < *right)
                SwapIter(left, right);

            return;
        }

        while (true)
        {
            while (*right < *pivot && left != right)
            {
                right--;
            }

            if (left == right)
            {
                if (*left > *pivot)
                {
                    SwapIter(left, pivot);
                    right++;

                    if (last == pivot)
                        last = right;

                    pivot++;
                    left--;
                }
                else
                {
                    left--;
                    if (left != first)
                        left--;
                }
                break;
            }

            SwapIter(left, right);
            SwapIter(left, pivot);

            if (left == first)
                first = pivot;

            if (last == pivot)
                last = right;

            pivot++;
            left++;
        }

        QuickSort(first, left);
        QuickSort(right, last);
    }

    //Метод поиска пусть все же будет
    Node *GetNode(int pos)
    {
        if (pos > size - 1)
            throw;

        Node *temp;
        if (pos > (size - 1) / 2)
        {
            temp = endNode->prev;
            for (int i = size - 1; i != pos; i--)
                temp = temp->prev;
        }
        else
        {
            temp = beginNode->next;
            for (int i = 0; i != pos; i++)
                temp = temp->next;
        }

        return temp;
    }
};

#endif