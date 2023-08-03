#include <mutex>

struct Node
{
    int value;
    Node* next;
    std::mutex* node_mutex;
    Node(int value) : value(value), next(nullptr), node_mutex(nullptr) {}
};

class FineGrainedQueue
{
    Node* head;
    std::mutex* queue_mutex;
public:
    void insertIntoMiddle(int value, int position);
};

void FineGrainedQueue::insertIntoMiddle(int value, int pos)
{
    Node* newNode = new Node(value);  // ������� ����� ����

    int currPos = 0;

    queue_mutex->lock();    // ��������� ���� ������ ��� ������ ����, �� ������� ����� �������� ����� ����

    Node* current = head;

    while (currPos < pos - 1 && current->next != nullptr)     // � ����� ���� �� ������ ���� ������ �� ��������
    {
        current = current->next;
        currPos++;
    }
    current->node_mutex->lock();    // ����� ������ ���� �� ������� ����� �������� ����� ���� � ��������� ��������� ����
    queue_mutex->unlock();          // ������������ ������

    Node* next = current->next;     // ������ ��������� �� ��������� ����
                               
    current->next = newNode;
    newNode->next = next;           // ��������� ������ ������� ������ ��������� �� ����, ��������� ����� ������ ����
    current->node_mutex->unlock();  // ������������ ������� ����.
}